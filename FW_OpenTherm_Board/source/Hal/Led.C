/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Led.C
;
*/

/*

OpenTherm board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS21xxxx/210003

Monitor
	Green	PD7
	Red		PB3
	Blue	PB4
	Yellow	PB5

Controller
	Green	PE2
	Red		PE3
	Blue	PE4
	Yellow	PE5

Thermostat
	Green	PA6
	Red		PA7
	Blue	PC4
	Yellow	PC5

*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"	// LL_GPIO_PIN_...
#include "..\Hal\GPIO.H"					// GPIO_Output_PushPull_FreqLow()
#include ".\Led.H"							// OWN header

/**
  * @brief Led related GPIO Initialization Function
  * @param None
  * @retval None
  */
void Led_Init(void)
{
	GPIO_Output_PushPull_FreqLow(GPIOA,LL_GPIO_PIN_6|LL_GPIO_PIN_7);
	GPIO_Output_PushPull_FreqLow(GPIOB,LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5);
	GPIO_Output_PushPull_FreqLow(GPIOC,LL_GPIO_PIN_4|LL_GPIO_PIN_5);
	GPIO_Output_PushPull_FreqLow(GPIOD,LL_GPIO_PIN_7);
	GPIO_Output_PushPull_FreqLow(GPIOE,LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5);

	// Switch OFF all LEDs
	GPIOA->BSRR = LL_GPIO_PIN_6|LL_GPIO_PIN_7;
	GPIOB->BSRR = LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5;
	GPIOC->BSRR = LL_GPIO_PIN_4|LL_GPIO_PIN_5;
	GPIOD->BSRR = LL_GPIO_PIN_7;
	GPIOE->BSRR = LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5;
}

