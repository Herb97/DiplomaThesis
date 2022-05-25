/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: WatchDog.C
;
*/


/*
Watchdog initialization.

Calculated by (1/LSI) * PRESCALER * ReloadCounter

LSI = 37000
PRESCALER = 4
ReloadCounter = 500

Watchdog time = (1/37000)*4*500 = 54 ms

Source: RM0367 STMicroelectronics
*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_iwdg.h"
#include "WatchDog.H"

/**
  * @brief Watchdog Configuration
  * @retval None
  */

void Watchdog_Init(void)
{
  LL_IWDG_Enable(IWDG);
  LL_IWDG_EnableWriteAccess(IWDG);
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_4);
  LL_IWDG_SetReloadCounter(IWDG, 500);
  while (LL_IWDG_IsReady(IWDG) != 1)
  {
  }
  LL_IWDG_SetWindow(IWDG, 500);
  LL_IWDG_ReloadCounter(IWDG);
}

/**
  * @brief Watchdog feed
  * @retval None
  */

void Watchdog_Feed(void)
{
	LL_IWDG_ReloadCounter(IWDG);
}

