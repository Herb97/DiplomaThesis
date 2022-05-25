/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-06-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: SPI1.C
;
*/

/*
HW Pwm board with STM32F446 revision A

PB3   ------> SPI1_SCK
PB5   ------> SPI1_MOSI 


SPI1 driver configured for 74HCT595

LL_SPI_DATAWIDTH_16BIT;
LL_SPI_POLARITY_LOW; CPOL = 0;
LL_SPI_PHASE_1EDGE; CPHA = 0;
LL_SPI_NSS_SOFT;
LL_SPI_BAUDRATEPRESCALER_DIV256;	32 MHz / 4 = 8 MHz
LL_SPI_MSB_FIRST;


SCLK ___/---\___/---\___/---\___/---\___/---\___/---\___/---\___/---\___
        |       |       |       |       |       |       |       |
MOSI X777777X6666666X5555555X4444444X3333333X2222222X1111111X0000000X

*/


#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_bus.h"
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_spi.h"
#include ".\SPI1.H"							// OWN header


/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
void Spi1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  LL_SPI_InitTypeDef SPI_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

  /**SPI1 GPIO Configuration
  PB3   ------> SPI1_SCK
  PB5   ------> SPI1_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3|LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_16BIT;//LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 10;
  LL_SPI_Init(SPI1, &SPI_InitStruct);
  LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
  /* USER CODE BEGIN SPI1_Init 2 */
	LL_SPI_Enable(SPI1);
  /* USER CODE END SPI1_Init 2 */

}


/**
  * @brief Write and read 16 bits. SPI has to be configured in advance.
  * @param lubDataToWrite Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @retval RxData Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
uint16_t uwSpi1_Word(uint16_t luwDataToWrite)
{
	/*!< Loop while DR register in not empty */
	do {} while (READ_BIT(SPI1->SR, SPI_SR_TXE) == 0);
	/*!< Send byte through the SPI1 peripheral */
	SPI1->DR = luwDataToWrite;
	/*!< Wait to receive a byte */
	do {} while (READ_BIT(SPI1->SR, SPI_SR_RXNE) == 0);
	/*!< Return the byte read from the SPI bus */
	return SPI1->DR;
}
