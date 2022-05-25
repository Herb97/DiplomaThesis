/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: main.C
;
*/


/*

OpenTherm board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS21xxxx/210003

*/


/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_cortex.h"	// LL_SYSTICK_IsActiveCounterFlag()
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_dac.h"	// LL_DAC_Enable()
#include "..\Common\Mod\Modbus\ModbusSerial.H"	// ModbusSerialLineDataLink_Enable(), ModbusSerialLineDataLink_ReceiveState(), ModbusSerialLineDataLink_Transmit(), ModbusSerialLineDataLink_Rx_Buffer,ModbusSerialLineDataLink_Rx_Len, MODBUS_SERIAL_BUFFER_SIZE
#include "..\Common\Mod\Modbus\ModbusAdu.H"		// ModbusAdu_Do()
#include "..\Hal\ADC.H"							// ADC_Init()	
#include "..\Hal\DAC.H"							// DAC_Init()
#include "..\Hal\GPIO.H"						// GPIO_Init()
#include "..\Hal\Led.H"							// Led_Init()
#include "..\Hal\ModbusAddress.H"				// ModbusAddress_Init()
#include "..\Hal\NVIC.H"						// NVIC_Configuration()
#include "..\Hal\Polarity.H"					// Polarity_Init(), Polarity_MainLoop()
#include "..\Hal\SystemClock.H"					// SystemClock_Config()
#include "..\Hal\Timer.H"						// Timer_Init()
#include "..\Hal\USART1.H"						// Usart1_Init(), Usart1_MainLoop()
#include "..\Hal\USART2.H"						// Usart2_Init()
#include "..\Hal\WatchDog.H"					// WatchDog_Init()
#include "..\App\TestTool.H"					// TestTool_MainLoop()
#include "..\App\OpenThermMonitor.H"			// OpenThermMonitor_Init()
#include "..\App\OpenThermMaster.H"				// OpenThermMaster_Init()
#include "..\App\OpenThermSlave.H"				// OpenThermSlave_Init()
#include "..\Hal\Threshold.H"					// Level_Init()



void main(void)
{
	// system clock configuration
	SystemClock_Config();
	
	// GPIO configuration
	// inicializace jednotlivých pinu presunout do CFG
	GPIO_Init();			// GPIO Ports Clock Enable
	ModbusAddress_Init();	        // MODBUS address related GPIO Initialization
	
	Led_Init();	                // Led related GPIO Initialization
	Polarity_Init();			// Polarity related GPIO Initialization
	
	// USART1 configuration
	Usart1_Init();		// TestTool
	Usart2_Init();		// Modbus
	
	// Nested vectored interrupt controller (NVIC) configuration
	NVIC_Configuration();
        
	ADC_Init();                     // ADC Init
	DAC_Init();                     // DAC Init
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_1);
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_2);
        
	ModbusSerialLineDataLink_Enable();
	SET_BIT(USART1->CR1, USART_CR1_RXNEIE);		// Enable USART1 RX interrupt

	Timer_Init();
	
	OpenThermMonitor_Init();
	OpenThermMaster_Init();
	OpenThermSlave_Init();
	Level_Init();
	
	__enable_interrupt();
		
    
	while (1)
	{
		if (ModbusSerialLineDataLink_ReceiveState())
		{	// Prijali jsme Modbus paket ze seriove linky.
			uint8_t len;
			len=ModbusAdu_Do(ModbusSerialLineDataLink_Rx_Buffer,ModbusSerialLineDataLink_Rx_Len, MODBUS_SERIAL_BUFFER_SIZE);
			ModbusSerialLineDataLink_Transmit(/*ModbusSerialLineDataLink_Buffer, */len); // Odesleme odpoved a nebo jen uvolníme prijem.
		}
		
                
		if (LL_SYSTICK_IsActiveCounterFlag())
		{

		}
                
		Polarity_MainLoop();
		TestTool_MainLoop();
		Usart1_MainLoop();
		
	}
}

