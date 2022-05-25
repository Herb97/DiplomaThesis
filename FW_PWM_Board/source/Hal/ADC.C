/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-11-19           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: ADC.C
;
*/

/*

HW Pwm board with STM32F446 revision A

  PA1   ------> ADC_IN1
  PA3   ------> ADC_IN3
  PB1   ------> ADC_IN9

A/D converter initalization and run

*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_adc.h"
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"		// LL_GPIO_PIN_...
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_bus.h"
#include "..\Hal\GPIO.H"					// GPIO_Analog()
#include ".\ADC.H"							// OWN header



static volatile uint16_t muwADC_CH9_Div;
static volatile uint16_t muwADC_CH9_mV;

void ADC_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  LL_ADC_InitTypeDef ADC_InitStruct = {0};
  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

  /**ADC1 GPIO Configuration
  PA1   ------> ADC1_IN1
  PA3   ------> ADC1_IN3
  PB1   ------> ADC1_IN9
  */
  GPIO_Analog(GPIOA, LL_GPIO_PIN_1|LL_GPIO_PIN_3);
  GPIO_Analog(GPIOB, LL_GPIO_PIN_1);

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
  LL_ADC_Init(ADC1, &ADC_InitStruct);
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
  LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_UNITARY_CONV);
  ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV4;
  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_1);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_3CYCLES);
  /* USER CODE BEGIN ADC1_Init 2 */
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_28CYCLES);	// to have enough time to charge 4 pF sampling capacitor from 10 kOhm
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_3, LL_ADC_SAMPLINGTIME_28CYCLES);	// to have enough time to charge 4 pF sampling capacitor from 10 kOhm
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_9, LL_ADC_SAMPLINGTIME_3CYCLES);
	LL_ADC_Enable(ADC1);
  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief Read data from A/D converter
  * @param None
  * @retval ADC->DR Readed value from A/D converter
**/
uint16_t uwADC_Data_Get(uint32_t lulChselr)
{
  ADC1->SQR3 = lulChselr;
  LL_ADC_REG_StartConversionSWStart(ADC1); /* start the ADC conversion */
  do {} while ((ADC1->SR & ADC_SR_EOC) == 0);
  return ADC1->DR;
}

// Convert 0..4095 div to 0..3300 mV
static uint16_t uwConvert_Div_To_mV(uint16_t luwDiv)
{
	uint32_t x;
	x = luwDiv;
	x = x * 3300 / 4095;
	return x;
}

uint16_t uwADC_ADC_PB1_Get(void)
{
  muwADC_CH9_Div = uwADC_Data_Get(ADC_CHANNEL_9_NUMBER);
  muwADC_CH9_mV = uwConvert_Div_To_mV(muwADC_CH9_Div);
  return muwADC_CH9_mV;
}


