/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-03-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: ADC.C
;
*/

/*

HW OpenTherm board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS21xxxx/210003

  PA2   ------> ADC_IN2
  PA3   ------> ADC_IN3
  PB0   ------> ADC_IN8
  PB1   ------> ADC_IN9
  PC0   ------> ADC_IN10
  PC1   ------> ADC_IN11

A/D converter initalization and run

*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_adc.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"		// LL_GPIO_PIN_...
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_dma.h"
#include "..\Hal\GPIO.H"
#include ".\ADC.H"						// OWN header



static uint16_t muwADC_CH2_Div;
static uint16_t muwADC_CH2_mV;
static uint16_t muwADC_CH3_Div;
static uint16_t muwADC_CH3_mV;
static uint16_t muwADC_CH8_Div;
static uint16_t muwADC_CH8_mV;
static uint16_t muwADC_CH9_Div;
static uint16_t muwADC_CH9_mV;
static uint16_t muwADC_CH10_Div;
static uint16_t muwADC_CH10_mV;
static uint16_t muwADC_CH11_Div;
static uint16_t muwADC_CH11_mV;

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
void ADC_Init(void)
{
  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_InitTypeDef ADC_InitStruct = {0};


  /**ADC GPIO Configuration
  PA2   ------> ADC_IN2
  PA3   ------> ADC_IN3
  PB0   ------> ADC_IN8
  PB1   ------> ADC_IN9
  PC0   ------> ADC_IN10
  PC1   ------> ADC_IN11
  */
	GPIO_Analog(GPIOA, LL_GPIO_PIN_2|LL_GPIO_PIN_3);
	GPIO_Analog(GPIOB, LL_GPIO_PIN_0|LL_GPIO_PIN_1);
	GPIO_Analog(GPIOC, LL_GPIO_PIN_0|LL_GPIO_PIN_1);

  /* ADC DMA Init */

  /* ADC Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMA_REQUEST_0);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);

  /* ADC interrupt Init */
  NVIC_SetPriority(ADC1_COMP_IRQn, 0);
  NVIC_EnableIRQ(ADC1_COMP_IRQn);

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_2);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_3);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_8);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_9);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_10);
  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_11);
  /** Common config
  */
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;	// LL_ADC_REG_CONV_CONTINUOUS; 
  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
  ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_OVERWRITTEN;
  
  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_160CYCLES_5);
  LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
  LL_ADC_REG_SetSequencerScanDirection(ADC1, LL_ADC_REG_SEQ_SCAN_DIR_FORWARD);
  LL_ADC_SetCommonFrequencyMode(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_FREQ_MODE_HIGH);
  LL_ADC_DisableIT_EOC(ADC1);
  LL_ADC_DisableIT_EOS(ADC1);
  ADC_InitStruct.Clock = LL_ADC_CLOCK_SYNC_PCLK_DIV2;
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
  LL_ADC_Init(ADC1, &ADC_InitStruct);


  /* Enable ADC internal voltage regulator */
  LL_ADC_EnableInternalRegulator(ADC1);
  /* Delay for ADC internal voltage regulator stabilization. */
  /* Compute number of CPU cycles to wait for, from delay in us. */
  /* Note: Variable divided by 2 to compensate partially */
  /* CPU processing cycles (depends on compilation optimization). */
  /* Note: If system core clock frequency is below 200kHz, wait time */
  /* is only a few CPU processing cycles. */
  uint32_t wait_loop_index;
  wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  /* USER CODE BEGIN ADC_Init 2 */
  
  /* Run ADC self calibration */
  LL_ADC_StartCalibration(ADC1);
  /* Poll for ADC effectively calibrated */
  while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
  {
  }
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
          /* Enable ADC */
          LL_ADC_Enable(ADC1);
  }
  /* Poll for ADCs ready to convert */
  while (LL_ADC_IsActiveFlag_ADRDY(ADC1) == 0)
  {
  }
  
  /* USER CODE END ADC_Init 2 */

  ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2;
}

/**
  * @brief Read data from A/D converter
  * @param None
  * @retval ADC1->DR Readed value from A/D converter
**/
uint16_t uwADC_Data_Get(uint32_t lulChselr)
{
  ADC1->CHSELR = lulChselr;
  ADC1->CR |= ADC_CR_ADSTART; /* start the ADC conversion */
  do {} while ((ADC1->ISR & ADC_ISR_EOC) == 0);
  return ADC1->DR;
}

// Convert 0..4095 div to 0..2500 mV
static uint16_t uwConvert_Div_To_mV(uint16_t luwDiv)
{
	uint32_t x;
	x = luwDiv;
	x = x * 2500 / 4095;
	return x;
}

uint16_t uwADC_ADC_Current_Get(void)
{
  muwADC_CH2_Div = (uint32_t)uwADC_Data_Get(ADC_CHSELR_CHSEL2);
  muwADC_CH2_mV = uwConvert_Div_To_mV(muwADC_CH2_Div);
  return muwADC_CH2_mV;
}


uint16_t uwADC_ADC_Voltage_Get(void)
{
  muwADC_CH3_Div = uwADC_Data_Get(ADC_CHSELR_CHSEL3);
  muwADC_CH3_mV = uwConvert_Div_To_mV(muwADC_CH3_Div);
  return muwADC_CH3_mV;
}

uint16_t uwADC_ADC_Current_Thermostat_Get(void)
{
  muwADC_CH8_Div = uwADC_Data_Get(ADC_CHSELR_CHSEL8);
  muwADC_CH8_mV = uwConvert_Div_To_mV(muwADC_CH8_Div);
  return muwADC_CH8_mV;
}

uint16_t uwADC_ADC_Voltage_Thermostat_Get(void)
{
  muwADC_CH9_Div = uwADC_Data_Get(ADC_CHSELR_CHSEL9);
  muwADC_CH9_mV = uwConvert_Div_To_mV(muwADC_CH9_Div);
  return muwADC_CH9_mV;
}

uint16_t uwADC_ADC_Voltage_Monitor_Get(void)
{
  muwADC_CH10_Div = uwADC_Data_Get(ADC_CHSELR_CHSEL10);
  muwADC_CH10_mV = uwConvert_Div_To_mV(muwADC_CH10_Div);
  return muwADC_CH10_mV;
}


uint16_t uwADC_ADC_Current_Monitor_Get(void)
{
  muwADC_CH11_Div = uwADC_Data_Get(ADC_CHSELR_CHSEL11);
  muwADC_CH11_mV = uwConvert_Div_To_mV(muwADC_CH11_Div);
  return muwADC_CH11_mV;
}

