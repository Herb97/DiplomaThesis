/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-09-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Polarity.C
;
*/

/*

Switch ON red LED in case of wrong polarity

OpenTherm board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS21xxxx/210003

INPUT PULL_UP:
PB6		Polarity monitor
PE6		Polarity controller
PE11	Polarity thermostat

*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"	// LL_GPIO_PIN_...
#include "..\Hal\GPIO.H"					// GPIO_Input_PullUp()
#include "..\Hal\Led.H"						// LED_...
#include ".\Polarity.H"						// OWN header


/**
  * @brief Polarity related GPIO Initialization Function
  * @param None
  * @retval None
  */
void Polarity_Init(void)
{
	GPIO_Input_PullUp(GPIOB, LL_GPIO_PIN_6);
	GPIO_Input_PullUp(GPIOE, LL_GPIO_PIN_6|LL_GPIO_PIN_11);
}


void Polarity_MainLoop(void)
{
	// Polarity monitor
	// PB6
	if (0==(GPIOB->IDR&BIT6))
	{
		// wrong polarity
		LED_MONITOR_R_ON;
	}
	else
	{
		LED_MONITOR_R_OFF;
	}
	
	// Polarity controller
	// PE6
	if (0==(GPIOE->IDR&BIT6))
	{
		// wrong polarity
		LED_MASTER_R_ON;
	}
	else
	{
		LED_MASTER_R_OFF;
	}
	
	// Polarity thermostat
	// PE11
	if (0==(GPIOE->IDR&BIT11))
	{
		// wrong polarity
		LED_SLAVE_R_ON;
	}
	else
	{
		LED_SLAVE_R_OFF;
	}
}