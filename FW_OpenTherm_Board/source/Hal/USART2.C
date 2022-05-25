/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: USART2.C
;
*/

/*

OpenTherm board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS21xxxx/210003

  PD4   ------> USART2_DE
  PD5   ------> USART2_TX
  PD6   ------> USART2_RX	PULL_UP

115 200Bd 8E1

*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_bus.h"	// LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"	// LL_GPIO_Init()
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_usart.h"	// LL_USART_...()
#include "..\Common\Mod\Modbus\ModbusSerial.H"
#include ".\USART2.H"						// OWN header


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void Usart2_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	
	// PD5   ------> USART2_TX AF4
	GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// PD6   ------> USART2_RX AF4	PULL_UP
	GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	// PD4   ------> USART2_DE AF4
	GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	
	LL_USART_InitTypeDef USART_InitStruct = {0};
	
	USART_InitStruct.BaudRate = 115200;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;		// 8 data bits + parity
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_EVEN;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART2, &USART_InitStruct);
	LL_USART_EnableDEMode(USART2);
	LL_USART_SetDESignalPolarity(USART2, LL_USART_DE_POLARITY_HIGH);
	LL_USART_SetDEAssertionTime(USART2, 0);
	LL_USART_SetDEDeassertionTime(USART2, 0);
	LL_USART_ConfigAsyncMode(USART2);
	SET_BIT(USART2->CR3, USART_CR3_OVRDIS);		// Disable overrun detection
	MODIFY_REG(USART2->RTOR, USART_RTOR_RTO, 201);	// Timeout 1.75 ms = 201/115200
	SET_BIT(USART2->CR2, USART_CR2_RTOEN);		// Enable Receiver Timeout
	SET_BIT(USART2->CR1, USART_CR1_RTOIE);		// Enable Receiver Timeout Interrupt
	LL_USART_Enable(USART2);}

/**
  * @brief Writing byte to USART2
  * @param Byte to write to transmit register
  * @retval None
  */
void Usart2_PutChar(uint8_t c)
{
	USART2->TDR = c;
}

/**
  * @brief Reading of received byte from USART2
  * @param None
  * @retval Received byte from USART1
  */
uint8_t ubUsart2_GetChar(void)
{
	return USART2->RDR;
}

/**
  * @brief This function handles USART2 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART2_IRQHandler(void)		
{
	uint32_t cr1 = USART2->CR1;
	uint32_t isr = USART2->ISR;
	if((isr & USART_ISR_RXNE)&&(cr1 & USART_CR1_RXNEIE))
	{
		ModbusSerialLineDataLink_Receive_Char(ubUsart2_GetChar());
	}
	if((isr & USART_ISR_TXE)&&(cr1 & USART_CR1_TXEIE))
	{	
		ModbusSerialLineDataLink_Transmit_Char();
	}
//	if((isr & USART_ISR_ORE)&&(cr1 & USART_CR1_RXNEIE))
//	{
//		// Overrun error detected
//		//UART1RX_INTERRUPT;
//		WRITE_REG(USART2->ICR, USART_ICR_ORECF);
//	}
	if ((isr & USART_ISR_RTOF)&&(cr1 & USART_CR1_RTOIE))
	{
		WRITE_REG(USART2->ICR, USART_ICR_RTOCF);	// Clear Receiver Time Out Flag
		ModbusSerialLineDataLink_ReceiveDone();
	}
}

