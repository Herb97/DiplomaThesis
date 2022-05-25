/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-03-27           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: USART1.C
;
*/

/*

HW Pwm board STM32F446 revision A

  PA12	------> USART1_DE USART1_RTS
  PA9	------> USART1_TX
  PA10	------> USART1_RX	PULL_UP

115 200Bd 8E1

*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_bus.h"	// LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"	// LL_GPIO_Init()
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_usart.h"	// LL_USART_...()
#include "..\Common\Mod\Modbus\ModbusSerial.H"
#include "..\Hal\GPIO.H"					// GPIO_Output_PushPull_FreqLow()
#include ".\USART1.H"						// OWN header
//#include ".\Led.H"


/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void Usart1_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

  /* PA12 */
  GPIO_Output_PushPull_FreqLow(GPIOA, LL_GPIO_PIN_12);

  /**USART1 GPIO Configuration
  PA9   ------> USART1_TX
  PA10   ------> USART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_EVEN;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_RTS;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief Writing byte to USART1
  * @param Byte to write to transmit register
  * @retval None
  */
void Usart1_PutChar(uint8_t c)
{
	USART1->DR = c;
}

/**
  * @brief Reading of received byte from USART1
  * @param None
  * @retval Received byte from USART1
  */
uint8_t ubUsart1_GetChar(void)
{
	return USART1->DR;
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)		
{
	uint32_t cr1 = USART1->CR1;
	uint32_t isr = USART1->SR;
	if((isr & USART_SR_RXNE)&&(cr1 & USART_CR1_RXNEIE))
	{
		ModbusSerialLineDataLink_Receive_Char(ubUsart1_GetChar());
		//Led(RECEIVE);
	}
	if((isr & USART_SR_TXE)&&(cr1 & USART_CR1_TXEIE))
	{	
		ModbusSerialLineDataLink_Transmit_Char();
        //Led(TRANSMIT);
	}
}

/**
  * @brief Activate RS-485 Driver Output Enable
  */
void Usart1_DriverEnable(void)
{
	GPIOA->BSRR = BIT12;
}

/**
  * @brief Deactivate RS-485 Driver Output Enable
  */
void Usart1_DriverDisable(void)
{
	GPIOA->BSRR = BIT12<<16u;
}

