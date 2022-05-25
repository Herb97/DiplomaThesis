/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: NVIC.C
;
*/

/*
USART1	TestTool
USART2	Modbus
TIM7	100 us tick
*/


#include ".\NVIC.H"							// OWN header



/**
  * @brief NVIC Configuration
  * @retval None
  */
void NVIC_Configuration(void)
{
	/* USART1 interrupt Init */
	NVIC_SetPriority(USART1_IRQn, 0);
	NVIC_EnableIRQ(USART1_IRQn);

	/* USART2 interrupt Init */
	NVIC_SetPriority(USART2_IRQn, 0);
	NVIC_EnableIRQ(USART2_IRQn);

//	/* External interrupts Init*/
//	NVIC_SetPriority(EXTI4_15_IRQn, 1);
//	NVIC_EnableIRQ(EXTI4_15_IRQn);

	/* TIM6 interrupt Init */
	NVIC_SetPriority(TIM6_DAC_IRQn, 0);	// 0 = the highest priority
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	NVIC_SetPriority(TIM7_IRQn, 0);
	NVIC_EnableIRQ(TIM7_IRQn);
}

