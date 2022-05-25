/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-11-19           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: DAC.C
;
*/

/*

HW Pwm board with STM32F446 revision A

D/A converter initalization and run

*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_dac.h"
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_bus.h"
#include "..\Hal\GPIO.H"					// GPIO_Analog()
#include ".\DAC.H"							// OWN header



/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
void DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  LL_DAC_InitTypeDef DAC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);

  /**DAC GPIO Configuration
  PA4   ------> DAC_OUT1
  PA5   ------> DAC_OUT2
  */
  GPIO_Analog(GPIOA, LL_GPIO_PIN_4|LL_GPIO_PIN_5);

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */
  /** DAC channel OUT1 config
  */
  DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
  DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;
  LL_DAC_Init(DAC, LL_DAC_CHANNEL_1, &DAC_InitStruct);
  /** DAC channel OUT2 config
  */
  LL_DAC_Init(DAC, LL_DAC_CHANNEL_2, &DAC_InitStruct);
  /* USER CODE BEGIN DAC_Init 2 */
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_1);
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_2);
  /* USER CODE END DAC_Init 2 */

}

// luwDAC_CH1_Val from 0 to 4095 relates to voltage from 0 to 3.3V
bool bDAC_CH1Value_Set(uint16_t luwDAC_CH1_Val)
{
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, luwDAC_CH1_Val);
	return true;
}

// luwDAC_CH2_Val from 0 to 4095 relates to voltage from 0 to 3.3V
bool bDAC_CH2Value_Set(uint16_t luwDAC_CH2_Val)
{
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, luwDAC_CH2_Val);
	return true;
}