/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Timer.C
;
*/


/*
INCOMPLETE - it doesn't work.
*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_bus.h"		// LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6)
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_tim.h"
#include "..\Common\Mod\Modbus\ModbusSerial.H"	// ModbusSerialLineDataLink_Timeout()
#include "..\App\DutyCycle.H"					// DutyCycle_80us()
#include "..\Hal\Led.H"
#include ".\Timer.H"							// OWN header


static uint8_t volatile mbStart;
static uint8_t volatile mbInterrupt;

/*
run timer for 1.5 times byte interval
1 byte = 11 bits
1 bit interval @ 115200 Bd is 8.68 us
timeout should be 143 us

Use Timer 7
*/
void Timer_ModbusSerialLineDataLink_Run(void)
{

	
	LL_TIM_DisableCounter(TIM7);
	LL_TIM_SetCounter(TIM7, 0);
//	LL_TIM_SetAutoReload(TIM7, 143U);	// Start 143 us timeout (1.5 times byte interval)
	LL_TIM_SetAutoReload(TIM7, 334U);	// Start 334 us timeout (3.5 times byte interval)
	LL_TIM_EnableCounter(TIM7);
	
	mbStart++;
	if (mbStart&0x01)
	{
		LED2_ON;
	}
	else
	{
		LED2_OFF;
	}
	
	// Once elapsed call ModbusSerialLineDataLink_Timeout()
	
}

/**
  * @brief  Configuration of timer TIM6 - Used for DutyCycle measurement.
  * @param  None
  * @retval None
  */

void TIM6_Init(void)
{
	// APB1 timer clock 90 MHz
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
	LL_TIM_SetPrescaler(TIM6, 90-1);	// divide from 90 to 1 MHz
	LL_TIM_SetAutoReload(TIM6, 5-1);	// to get 5 us
//	TIM6->CR1 TIM_AUTORELOAD_PRELOAD_DISABLE
	LL_TIM_SetUpdateSource(TIM6, LL_TIM_UPDATESOURCE_COUNTER);
	LL_TIM_GenerateEvent_UPDATE(TIM6);
	LL_TIM_EnableCounter(TIM6);
	LL_TIM_EnableIT_UPDATE(TIM6);	
}

/**
  * @brief  Configuration of timer TIM7 - Used for MODBUS.
  * @param  None
  * @retval None
  */

void TIM7_Init(void)
{
	// APB1 timer clock 90 MHz
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
	LL_TIM_SetPrescaler(TIM7,90-1);	// divide from 90 to 1 MHz
	LL_TIM_SetUpdateSource(TIM7, LL_TIM_UPDATESOURCE_COUNTER);
	LL_TIM_GenerateEvent_UPDATE(TIM7);
	LL_TIM_SetOnePulseMode(TIM7, LL_TIM_ONEPULSEMODE_SINGLE);
	LL_TIM_EnableIT_UPDATE(TIM7);	
}

void TIM6_DAC_IRQHandler(void)
{
	if (LL_TIM_IsActiveFlag_UPDATE(TIM6))
	{
		//LED3_ON;
		DutyCycle_5us(GPIOC->IDR);
		//LED3_OFF;
		LL_TIM_ClearFlag_UPDATE(TIM6);
	}
}

void TIM7_IRQHandler(void)
{
	if (LL_TIM_IsActiveFlag_UPDATE(TIM7))
	{
		LL_TIM_ClearFlag_UPDATE(TIM7);
		ModbusSerialLineDataLink_Timeout();
		mbInterrupt++;
		if (mbInterrupt&0x01)
		{
			LED1_ON;
		}
		else
		{
			LED1_OFF;
		}
	}
}

void Timer_Init(void)
{
	TIM6_Init();
	TIM7_Init();
}
