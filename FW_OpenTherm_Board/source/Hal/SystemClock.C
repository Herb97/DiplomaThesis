/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: SystemClock.C
;
*/

/*

Clock source HSE XTAL 24 MHz
SYSCLK is 32 Mhz
HCLK is 32MHz

*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_bus.h"	// LL_APB2_GRP1_EnableClock(), LL_APB1_GRP1_EnableClock()
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_system.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_pwr.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_rcc.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_utils.h"
#include ".\SystemClock.H"					// OWN header


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
	
	if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
	{
		//Error_Handler();  
	}
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	LL_RCC_HSE_Enable();
	
	/* Wait till HSE is ready */
	while(LL_RCC_HSE_IsReady() != 1)
	{
	  
	}
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLL_MUL_4, LL_RCC_PLL_DIV_3);
	LL_RCC_PLL_Enable();
	
	 /* Wait till PLL is ready */
	while(LL_RCC_PLL_IsReady() != 1)
	{
	  
	}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	
	 /* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	
	}
	
	// System tick 100us
	LL_InitTick(32000000U, 10000U);
	
	LL_SetSystemCoreClock(32000000);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
}