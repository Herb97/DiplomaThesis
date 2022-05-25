/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-03-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: DAC.C
;
*/

/*

HW Flame Simulator board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS20xxxx/210004

D/A converter initalization and run

*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_dac.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_bus.h"
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_dma.h"
#include "..\Common\Mod\Modbus\ModbusSerial.H"
#include ".\DAC.H"						// OWN header

#define DAC_VOLTAGE_Pin LL_GPIO_PIN_4
#define DAC_VOLTAGE_GPIO_Port GPIOA
#define DAC_CURRENT_Pin LL_GPIO_PIN_5
#define DAC_CURRENT_GPIO_Port GPIOA

uint8_t mubCounter = 0u;


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

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  /**DAC GPIO Configuration
  PA4   ------> DAC_OUT1
  PA5   ------> DAC_OUT2
  */
  GPIO_InitStruct.Pin = DAC_VOLTAGE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(DAC_VOLTAGE_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = DAC_CURRENT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(DAC_CURRENT_GPIO_Port, &GPIO_InitStruct);

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
  
  /* USER CODE END DAC_Init 2 */

}

bool bDAC_CH1Value_Set(uint16_t luwDAC_CH1_Val)
{
  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, luwDAC_CH1_Val);
  return true;
}

bool bDAC_CH2Value_Set(uint16_t luwDAC_CH2_Val)
{
  LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, luwDAC_CH2_Val);
  return true;
}

/*void DAC_Test(void)
{
	mubCounter++;
	if (mubCounter & 1u)
	{
		bDAC_CH1Value_Set(0x3FFu);
		bDAC_CH2Value_Set(0xBFFu);
	}
	else
	{
		bDAC_CH1Value_Set(0xBFFu);
		bDAC_CH2Value_Set(0x3FFu);
	}
}*/
	