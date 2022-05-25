/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-21           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Timer.C
;
*/

/*
Timer clock 32 MHz
TIM3 1 MHz time stamp is used for time measurement
TIM7 100 us is used for sampling OpenTherm signals
TIM6 500 us(adjustable) is used for OpenTherm Tx
*/


//*****************************************************************************
// INCLUDE FILES
//*****************************************************************************
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_tim.h"
#include "..\Mod\Tick1ms.H"					// Tick1ms_Tick()
#include "..\App\Counter.H"					// Counter_100us()
#include "..\Hal\DAC.H"					// DAC_Test()
#include "..\Hal\OpenThermHal.H"			// OpenThermHal_100us(), OpenThermHal_HalfBitTime()
#include ".\Timer.H"						// OWN header


//*****************************************************************************
// VARIABLE DEFINITION
//*****************************************************************************
static volatile uint8_t mubDivider_500us_1ms = 0u;

/**
  * @brief timer initialization 1 MHz
  * @param None
  * @retval None
  */

static void Timer3_Init(void)
{
      LL_TIM_InitTypeDef TIM_InitStruct = {0};
      // Timer set to 1 MHz
      TIM_InitStruct.Prescaler = 31u;	// 32 MHz / (31+1) = 1 MHz
      TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
      TIM_InitStruct.Autoreload = 65535u;
      TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
      LL_TIM_Init(TIM3, &TIM_InitStruct);
      LL_TIM_DisableARRPreload(TIM3);
      LL_TIM_DisableMasterSlaveMode(TIM3);
      LL_TIM_EnableIT_UPDATE(TIM3);	
      LL_TIM_EnableCounter(TIM3);
      return;
}

/**
  * @brief timer initialization 2 kHz
  * @param None
  * @retval None
**/

static void Timer6_Init(void)
{
      LL_TIM_InitTypeDef TIM_InitStruct = {0};
      
      TIM_InitStruct.Prescaler = 319u;		// 32 MHz / (319+1) = 100 kHz
      TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
      TIM_InitStruct.Autoreload = 49u;		// 100 kHz / (49+1) = 2 kHz
      LL_TIM_Init(TIM6, &TIM_InitStruct);
      LL_TIM_DisableARRPreload(TIM6);
      LL_TIM_DisableMasterSlaveMode(TIM6);
      LL_TIM_EnableCounter(TIM6);
      LL_TIM_EnableIT_UPDATE(TIM6);	
}

/**
  * @brief timer initialization 10 kHz
  * @param None
  * @retval None
**/

static void Timer7_Init(void)
{
      LL_TIM_InitTypeDef TIM_InitStruct = {0};
      
      TIM_InitStruct.Prescaler = 127u;		// 32 MHz / (127+1) = 250 kHz
      TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
      TIM_InitStruct.Autoreload = 24u;		// 250 kHz / (24+1) = 10 kHz
      LL_TIM_Init(TIM7, &TIM_InitStruct);
      LL_TIM_DisableARRPreload(TIM7);
      LL_TIM_DisableMasterSlaveMode(TIM7);
      LL_TIM_EnableCounter(TIM7);
      LL_TIM_EnableIT_UPDATE(TIM7);	
}


void Timer_Init(void)
{
	// initialize timers
	Timer3_Init();
	Timer6_Init();
	Timer7_Init();
}

/**
  * @brief 10 us timer interrupt handler 
  * @param None
  * @retval None
**/

void TIM6_IRQHandler(void)
{
	OpenThermHal_HalfBitTime();
	TIM6->SR  = 0x00u;
}

/**
  * @brief 100 us timer interrupt handler 
  * @param None
  * @retval None
**/

void TIM7_IRQHandler(void)
{
	OpenThermHal_100us();
	Counter_100us();
	if (0u == mubDivider_500us_1ms)
	{
		Tick1ms_Tick();
	}
	//DAC_Test();
	mubDivider_500us_1ms++;
	if (mubDivider_500us_1ms >= 10u)
	{
		mubDivider_500us_1ms = 0u;
	}
	TIM7->SR  = 0x00u;
}



/**
  * @brief Free running counter from 0 to 65535, incremented every 1 us
  * @param None
  * @retval TimeStamp
**/
uint16_t uwTimer_TimeStamp_1us_Get(void)
{
	return TIM3->CNT;
}


void BitTime_Set(uint16_t uwBitTime)
{
	uint16_t luwARR = uwBitTime*13u; // 154
	LL_TIM_SetPrescaler(TIM6, 7);
	LL_TIM_SetAutoReload(TIM6, luwARR - 1);
}