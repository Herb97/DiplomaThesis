//   _______
// _/ About \_______________________________________________________
//|                                                                 |

/* HOW IT WORKS:

Pøíjem:
Modul je defaultnì ve stavu pøíjmu (RX_ENABLED).
Pøijaté bajty jsou zpracovávány funkcí ModbusSerialLineDataLink_Receive_Char(),
která spouští timer Timer_ModbusSerialLineDataLink_Run(), ke zjišìní konce paketu.
Vypršení èasovaèe zavolá ModbusSerialLineDataLink_ReceiveDone().
Èas musí odpovídat 3.5*délka_bajtu, pøièem 1bajt=11bitù.
Po pøijetí paketu se zmìní stav na RX_COMPLETE. Modul v nìm setrvává
dokud není zavoláno ModbusSerialLineDataLink_Free() nebo ModbusSerialLineDataLink_Transmit().

Vysílání:
Zahajuje se zavoláním ModbusSerialLineDataLink_Transmit().
Odesílání bajtù v pøerušení zajišuje ModbusSerialLineDataLink_Transmit_Char().
Spolu se zavoláním funkce PUT_CHAR() je nutno
nastavit pin DE (øízení smìru) a také timer, kterı zajistí jeho vynulování.
Vypršení èasovaèe vynuluje pin DE a zavolá ModbusSerialLineDataLink_Free(). */

/*
21.9.2015 14:35:18 MiŠ
Doplnìny èítaèe pøijatıch a odeslanıcha paketù.
Pøijatı paket hlášen jen pøi nenulové délce. Eliminuje chybnì nastavenou vlajku èítaèe.

3.12.2014 14:37:55 MiŠ
Doplnìn novı stav DISABLED, aby bylo korektnì ošetøeno vypnutí MODBUS povelem z MODBUS.
Bez této úpravy se automat dostal do stavu TX_PROGRESS a tam u visel nevìky.

6.10.2009 15:22:04 MiŠ
Doplnìna podpora RS485
Pøechod do stavu RX_ENABLED a po deaktivaci signálu DE na sbìrnici RS485
Je tedy nutno volat funkci ModbusSerialLineDataLink_Free() v pøíslušném UARTx_HW.H

2.7.2009 15:35:05 MiŠ
Doplnìna direktiva volatile k ModbusSerialLineDataLink_Tx_Counter, její absence
zpùsobovala obèasné odeslání paketù s poøadím bajtù: 0, 0, 2, 3, 4, ...

11.5.2009 10:25:28 MiŠ
V reimu SLAVE sdílíme jeden buffer pro pøíjem i vysílání.
V reimu MASTER je samostatnı buffer pro pøíjem a samostatnı buffer
pro vysílání.
Vysvìtlení:
V reimu SLAVE je volána funkce ModbusSerialLineDataLink_Transmit jako odpovìï
na pøíchozí paket a automat je ve stavu RX_COMPLETE a nemùe tedy
dojít k pøepisu jediného pøijímacího-vysílacího bufferu následnım
pøíjmem, protoe pøíjem je ve stavu RX_COMPLETE blokován.
V reimu MASTER mùe bıt pøi plnìní vysílacího bufferu automat ve stavu
RX_ENABLED, proto je nutné pøijímací a vysílací buffer oddìlit (nebo
jinak zabránit nechtìnému pøepisu vysílacího bufferu).

27.11.2008 9:16:23 MiŠ
Po zpracování pøijatého paketu je nutno vdy zavolat funkci
pro odvysílání, pokud není co vysílat, pøedáváme jako délku 0.
Pøíjmovı buffer je pouit i pro vysílání.
Ovládání pinu RS485 by mìla asi øešit vrstva UARTu. Je to hw závislé!
Ovládání bude muset bıt øešeno pomocí timeru.

6.3.2008 13:26:26 IN
MODBUS protocol, serial link layer.
Pøíjem a vysílání protokolu Modbud prostøednictvím sériové linky.
Øešeno jako dotaz-odpovìï. Po detekci pøijatého paketu se paket pøedává
na zpracování v aplikaci. Uvolnìní pøíjmu se provádí a po odvysílání
celé odpovìdi.
*/

//   ________________________
// _/ Define, constants, ... \______________________________________
//|                                                                 |
#define SLAVE 0
#define MASTER 1
#include <string.h>
#include ".\ModbusSerial.H"
#include "ModbusSerial.CFG"

uint8_t ModbusSerialLineDataLink_Rx_Buffer[MODBUS_SERIAL_BUFFER_SIZE];
uint8_t ModbusSerialLineDataLink_Rx_Len=0;								// Èítaè pøijatıch bytù

#if ModbusSerial==SLAVE
#define ModbusSerialLineDataLink_Tx_Buffer ModbusSerialLineDataLink_Rx_Buffer
#elif ModbusSerial==MASTER
uint8_t ModbusSerialLineDataLink_Tx_Buffer[MODBUS_SERIAL_BUFFER_SIZE];	// odkaz na vysílací buffer
#else
ERROR // musí bıt definován MASTER nebo SLAVE
#endif
uint8_t ModbusSerialLineDataLink_Tx_Len;								// poèet bajtù k odvysílání
volatile uint8_t ModbusSerialLineDataLink_Tx_Counter;					// interní èítaè odvysílanıch byte

typedef enum
{
	MB_DISABLED	= 0,
	RX_ENABLED	= 1,							// pøíjem povolen
	RX_COMPLETE	= 2,							// pøijat paket
	TX_PROGRESS	= 3								// probíhá vysílání
} ModbusSerialLineDataLink_State_TypeDef;

static ModbusSerialLineDataLink_State_TypeDef ModbusSerialLineDataLink_State=MB_DISABLED;		// stav pøíjmu a vysílání

// diagnostické èítaèe
uint32_t ModbusSerialLineDataLink_RxPacketCounter = 0;
uint32_t ModbusSerialLineDataLink_TxPacketCounter = 0;

//   ________
// _/ Source \______________________________________________________
//|                                                                 |

// *********** P ø í j e m *********************

// Pøerušení vyvolané pøijímaèem.
void ModbusSerialLineDataLink_Receive_Char(uint8_t c)
{
	if (RX_ENABLED == ModbusSerialLineDataLink_State)
	{	// Pøíjem je volnı.
		if (ModbusSerialLineDataLink_Rx_Len < MODBUS_SERIAL_BUFFER_SIZE)
		{	// Místo v bufferu je, uloíme.
			ModbusSerialLineDataLink_Rx_Buffer[ModbusSerialLineDataLink_Rx_Len] = c;
			ModbusSerialLineDataLink_Rx_Len++;
		}
		RECEIVER_TIMEOUT_START;				// spustíme mìøení, které identifikuje konec paketu
	}
}

// Ukonèení, voláno po vypršení timeoutu
void ModbusSerialLineDataLink_ReceiveDone(void)
{
	if ((RX_ENABLED == ModbusSerialLineDataLink_State)&&(ModbusSerialLineDataLink_Rx_Len))
	{
		ModbusSerialLineDataLink_RxPacketCounter++;
		ModbusSerialLineDataLink_State = RX_COMPLETE; // Nastavení flagu o ukonèeném pøíjmu.
	}
}

// Dotaz na pøijatou odpovìï.
uint8_t ModbusSerialLineDataLink_ReceiveState(	// 1 = máme pøijatı paket
	void
	)
{
	if (ModbusSerialLineDataLink_State == RX_COMPLETE)
	{
		return 1;
	}
	else
	{
		return 0; // Nebyla pøijata ádná zpráva.
	}
}

/*
Uvolnìní pøíjmu, volá se buïto
- po zpracování pøijatého paketu, kdy není co vysílat nebo
- po deaktivaci signálu DE na sbìrnici RS485, kterı je deaktivován po timeoutu na konci vysílání
*/
static void ModbusSerialLineDataLink_Free(void)
{
	ModbusSerialLineDataLink_Rx_Len = 0;
	ModbusSerialLineDataLink_State=RX_ENABLED;					// uvolníme pøíjem
}	

// *********** V y s í l á n í *****************

// Odešleme odpovìï od ptr s délkou lubLen a na závìr uvolníme pøíjem.
void ModbusSerialLineDataLink_Transmit(/*uint8_t * Ptr, */uint8_t lubLen)
{
	if (MB_DISABLED != ModbusSerialLineDataLink_State)
	{
		if (lubLen > 0)
		{
			ModbusSerialLineDataLink_Tx_Len=lubLen;
			//ModbusSerialLineDataLink_Tx_Buffer=Ptr;
			ModbusSerialLineDataLink_State=TX_PROGRESS;
			ModbusSerialLineDataLink_Tx_Counter=1;	// next index of transmitted byte
			PUT_CHAR(ModbusSerialLineDataLink_Tx_Buffer[0]);
			INTERRUPT_TRANSMIT_ENABLE;	// pøidáno kvùli STM32F107
			ModbusSerialLineDataLink_TxPacketCounter++;
		}
		else
		{
			ModbusSerialLineDataLink_Free();					// uvolníme pøíjem, kdy nebudeme nic vysílat
		}
	}
}

// Pøerušení vyvolané vysílaèem.
void ModbusSerialLineDataLink_Transmit_Char(void)
{
	if (ModbusSerialLineDataLink_Tx_Counter < ModbusSerialLineDataLink_Tx_Len)
	{	// Ještì jsme neovysílali vše, posíláme další byte.
		PUT_CHAR(ModbusSerialLineDataLink_Tx_Buffer[ModbusSerialLineDataLink_Tx_Counter]);
		ModbusSerialLineDataLink_Tx_Counter++;
	}

	else
	{	// Pøerušeno od posledního vysílaného bytu odpovìdi -> základní stav komunikace.
		// pøidáno kvùli STM32F107 - protoe vyuíváme pøíznak Empty, co jinak vedlo ke stálému volání pøerušení
		INTERRUPT_TRANSMIT_DISABLE;
	}
}

void ModbusSerialLineDataLink_Timeout(void)
{
	// ModbusSerialLineDataLink_Timeout
	if(ModbusSerialLineDataLink_State==TX_PROGRESS)
	{
		// vysílání
		DRIVER_OUTPUT_DISABLE;	/* deaktivujeme signál DE */
		ModbusSerialLineDataLink_Free();
	}
	else
	{
		// pøíjem
		ModbusSerialLineDataLink_ReceiveDone();
	}
}

// Nastavení rychlosti.
//void ModbusSerialLineDataLink_UART_Set(uint32_t baudrate, int receiverTimeout)
//{
//	UART_Set(baudrate, receiverTimeout);
//}

// mùe bıt voláno pouze ve stavu DISABLED
void ModbusSerialLineDataLink_Enable(void)
{
	if (MB_DISABLED==ModbusSerialLineDataLink_State)
	{
		ModbusSerialLineDataLink_State = RX_ENABLED;
		ModbusSerialLinePhysical_Enable;
	}
}

void ModbusSerialLineDataLink_Disable(void)
{
	ModbusSerialLineDataLink_State=MB_DISABLED;
	//ModbusSerialLinePhysical_Disable();
}

uint32_t ModbusSerialLineDataLink_RxPacketCounter_Get(void)
{
	return ModbusSerialLineDataLink_RxPacketCounter;
}

uint32_t ModbusSerialLineDataLink_TxPacketCounter_Get(void)
{
	return ModbusSerialLineDataLink_TxPacketCounter;
}
