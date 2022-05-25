/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-04-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: main.C
;
*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_cortex.h"	// LL_SYSTICK_IsActiveCounterFlag()
#include "..\Common\Drv\SystemControl\SystemControl.H"			// SystemControl_SetErrorCode(), SystemControl_SetInitDone()
#include "..\Common\Mod\Modbus\ModbusSerial.H"	// ModbusSerialLineDataLink_Enable(), ModbusSerialLineDataLink_ReceiveState(), ModbusSerialLineDataLink_Transmit(), ModbusSerialLineDataLink_Rx_Buffer,ModbusSerialLineDataLink_Rx_Len, MODBUS_SERIAL_BUFFER_SIZE
#include "..\Common\Mod\Modbus\ModbusAdu.H"	// ModbusAdu_Do()
#include "..\Hal\ADC.H"						// ADC_Init()
#include "..\Hal\DAC.H"						// DAC_Init()
#include "..\Hal\Led.H"						// Led_Init()
#include "..\Hal\GPIO.H"					// GPIO_Init()
#include "..\Hal\ModbusAddress.H"			// ModbusAddress_Init()
#include "..\Hal\NVIC.H"					// NVIC_Configuration()
#include "..\Hal\RawInput.H"				// RawInput_Init(), RawInput_Read()
#include "..\Hal\SPI1.H"					// Spi1_Init()
#include "..\Hal\SystemClock.H"				// SystemClock_Config()
#include "..\Hal\Timer.H"					// Timer_Init()
#include "..\Hal\TPIC6C595.H"				// TPIC6C595_Init()
#include "..\Hal\USART1.H"					// Usart1_Init()
#include "..\App\DigitalInput.H"			// uwDigitalInput_FilteredData_Get(), DigitalInput_Every1ms()
#include "..\App\DutyCycle.H"				// DutyCycle_Init()
#include "..\App\OutputType.H"				// OutputType_MainLoop()
#include "..\App\OutputVoltage.H"			// OutputVoltage_Init()	
#include "..\App\PwmOutput.H"				// PwmOutput_Init()
#include "..\App\InputThreshold.H"			// Threshold_Init(), Threshold_MainLoop()

static uint16_t volatile muwTick;

void main(void)
{
	// Reset Error code
	SystemControl_ErrorCodeSet(0);

	// GPIO configuration
	GPIO_Init();			// GPIO Ports Clock Enable

	// system clock configuration
	SystemClock_Config();
	
	// ADC init, ADC is used to get Modbus address.
	ADC_Init();
	DAC_Init();
	
	// GPIO configuration
	Led_Init();
	OutputVoltage_Init();	// Regulated power supply Initialization
	ModbusAddress_Init();	// MODBUS address related GPIO Initialization
	RawInput_Init();	// DigitalInput related GPIO Initialization
	DutyCycle_Init();
	
	// SPI1 configuration
	Spi1_Init();
	TPIC6C595_Init();
	
	// USART1 configuration
	Usart1_Init();
	
	// TIM6 and TIM7 configuration
	Timer_Init();
	
	// Reset Error code
	SystemControl_InitDoneSet(1);

	// Nested vectored interrupt controller (NVIC) configuration
	NVIC_Configuration();
	
	ModbusSerialLineDataLink_Enable();
	
	// PWM signal timers configuration
	PwmOutput_Init();
	
	__enable_interrupt();
	
	while (1)
	{
		if (ModbusSerialLineDataLink_ReceiveState())
		{	// Received Modbus packet from serial line.
			uint8_t len;
			len=ModbusAdu_Do(ModbusSerialLineDataLink_Rx_Buffer,ModbusSerialLineDataLink_Rx_Len, MODBUS_SERIAL_BUFFER_SIZE);
			ModbusSerialLineDataLink_Transmit(/*ModbusSerialLineDataLink_Buffer, */len); // Odešleme odpovìï a nebo jen uvolníme pøíjem.
		}
		// Call regularly every ms.
		if (LL_SYSTICK_IsActiveCounterFlag())
		{
			muwTick++;
			if (muwTick&0x01)
			{
				LED4_ON;
			}
			else
			{
				LED4_OFF;
			}

			uint16_t luwDigitalInput_RawData = RawInput_Read();
			// Add data after 1 ms into filter buffer.
			DigitalInput_Every1ms(luwDigitalInput_RawData);
			
			OutputType_MainLoop();
			InputThreshold_MainLoop();
			OutputVoltage_StateMachine();
			uwADC_ADC_PB1_Get();

		} 
		
	}
}
