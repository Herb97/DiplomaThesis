/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-03-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: USART1.C
;
*/

/*

HW OpenTherm
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS20xxxx/210004

  PA9   ------> USART2_TX
  PA10   ------> USART2_RX	PULL_UP

57 600 Bd 8N1

*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_bus.h"	// LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"	// LL_GPIO_Init()
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_usart.h"	// LL_USART_...()
#include "..\Mod\Fifo.H"						// FifoInit(), ubFifoFull(), ubFifoGet(), FifoPutMultiple()
#include "..\App\Counter.H"						// uwCounter_SerialData_GetAndClear()
#include ".\USART1.H"							// OWN header


FIFO(250) msFifoRx1;
FIFO(250) msFifoTx1;


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void Usart1_Init(void)
{
	FifoInit(&msFifoRx1, 250);
	FifoInit(&msFifoTx1, 250);

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	
	// PA9   ------> USART1_TX AF4
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// PA10   ------> USART1_RX AF4	PULL_UP
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	
	LL_USART_InitTypeDef USART_InitStruct = {0};
	
	USART_InitStruct.BaudRate = 57600;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;		// 8 data bits
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART1, &USART_InitStruct);
	LL_USART_EnableDEMode(USART1);
	LL_USART_SetDESignalPolarity(USART1, LL_USART_DE_POLARITY_HIGH);
	LL_USART_SetDEAssertionTime(USART1, 0);
	LL_USART_SetDEDeassertionTime(USART1, 0);
	LL_USART_ConfigAsyncMode(USART1);
	SET_BIT(USART1->CR3, USART_CR3_OVRDIS);		// Disable overrun detection
//	MODIFY_REG(USART1->RTOR, USART_RTOR_RTO, 201);	// Timeout 1.75 ms = 201/115200
//	SET_BIT(USART1->CR2, USART_CR2_RTOEN);		// Enable Receiver Timeout
//	SET_BIT(USART1->CR1, USART_CR1_RTOIE);		// Enable Receiver Timeout Interrupt
	LL_USART_Enable(USART1);
}


/**
  * @brief This function handles USART2 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)		
{
	uint32_t cr1 = USART1->CR1;
	uint32_t isr = USART1->ISR;
	if((isr & USART_ISR_RXNE)&&(cr1 & USART_CR1_RXNEIE))
	{
		FifoPut(&msFifoRx1, USART1->RDR);
		
	}
//	if((isr & USART_ISR_TXE)&&(cr1 & USART_CR1_TXEIE))
//	{	
//		ModbusSerialLineDataLink_Transmit_Char();
//	}
//	if((isr & USART_ISR_ORE)&&(cr1 & USART_CR1_RXNEIE))
//	{
//		// Overrun error detected
//		//UART1RX_INTERRUPT;
//		WRITE_REG(USART2->ICR, USART_ICR_ORECF);
//	}
//	if ((isr & USART_ISR_RTOF)&&(cr1 & USART_CR1_RTOIE))
//	{
//		WRITE_REG(USART1->ICR, USART_ICR_RTOCF);	// Clear Receiver Time Out Flag
//		ModbusSerialLineDataLink_ReceiveDone();
//	}
}


/**
  * @brief Returns number of bytes in RX FIFO
  * @param None
  * @retval Number of bytes in RX FIFO
  */

uint8_t ubUsart1_Rx_Quantity(void)
{
	return ubFifoFull(&msFifoRx1);
}


/**
  * @brief Gets one byte from RX FIFO
  * @param None
  * @retval Byte from RX FIFO
  */

uint8_t ubUsart1_Rx_Get(void)
{
	return ubFifoGet(&msFifoRx1);
}


/**
  * @brief Sending data to UART1 in main loop
  * @param None
  * @retval None
  */

void Usart1_MainLoop(void)
{
	if (USART1->ISR&USART_ISR_TXE)
	{
		if (ubFifoFull(&msFifoTx1))
		{
			uint8_t lubDataToTransmit = ubFifoGet(&msFifoTx1);
			USART1->TDR = lubDataToTransmit;
			uwCounter_SerialData_GetAndClear();
		}
	}
}


/**
  * @brief 
  * @param 
  * @retval None
  */

void Usart1_PutMultiple(uint8_t const * pSrc, uint8_t lubSize)
{
	FifoPutMultiple(&msFifoTx1, pSrc, lubSize);
}




