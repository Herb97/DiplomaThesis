/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: GPIO.C
;
*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"
#include ".\GPIO.H"

/**
  * @brief GPIO Ports Clock Enable
  * @param None
  * @retval None
  */
void GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN|RCC_IOPENR_GPIOBEN|RCC_IOPENR_GPIOCEN|RCC_IOPENR_GPIODEN|RCC_IOPENR_GPIOEEN|RCC_IOPENR_GPIOHEN;
}

// Configure I/O pin(s) as very high speed digital output.
void GPIO_Output_PushPull(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// Configure I/O pin(s) as low speed digital output.
void GPIO_Output_PushPull_FreqLow(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// Configure I/O pin(s) as digital input with pull-up.
void GPIO_Input_PullUp(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  	
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// Configure I/O pin(s) as digital input without any pull-up or pull-down.
void GPIO_Input_PullNo(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  	
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

// Configure I/O pin(s) as analog.
void GPIO_Analog(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  	
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
