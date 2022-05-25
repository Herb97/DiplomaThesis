/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-11-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Led.C
;
*/

/*

HW Pwm board with STM32F446 revision A

DCDC_SETx outputs temporary used for debugging.

*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"	// LL_GPIO_PIN_..
#include "..\Hal\GPIO.H"					// GPIO_Output_PushPull_FreqLow()
#include ".\Led.H"							// OWN header

/**
  * @brief Led related GPIO Initialization Function
  * @param None
  * @retval None
  */
void Led_Init(void)
{

}

