/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-05           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: RawInput.C
;
*/

/*
Reading of digital inputs.

HW PwmBoard STM32F446 Revision A:

Port C
*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"	// LL_GPIO_PIN_ALL
#include "..\Hal\GPIO.H"					// GPIO_Input_PullNo()
#include ".\RawInput.H"						// OWN header

//=======================================================================================================================================================
//				Init
//=======================================================================================================================================================

/**
  * @brief Initial settings for digital inputs
  * @param None
  * @retval None
  */
void RawInput_Init(void)
{
	GPIO_Input_PullUp(GPIOC, LL_GPIO_PIN_ALL);
}

/**
  * @brief Reading of raw inputs
  * @param None
  * @retval x
  *
  * Called from main.C
  */
uint16_t RawInput_Read(void)
{
	return GPIOC->IDR;
}

