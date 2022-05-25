/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: NVIC.C
;
*/

/*

HW PwmBoard with STM32F446 Revision A

It is a question what timer should be used for measuring of duty cycle. Maybe SYSTICK?

0 = the highest priority

	TIM7_IRQn		(duty cycle and frequency measurement)

*/

#include ".\NVIC.H"							// OWN header



/**
  * @brief NVIC Configuration
  * @retval None
  */
void NVIC_Configuration(void)
{
	// Duty cycle measurement on 16 channels
	NVIC_SetPriority(TIM6_DAC_IRQn, 0);		// every X.X us
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	NVIC_SetPriority(TIM7_IRQn, 0);		// every X.X us
	NVIC_EnableIRQ(TIM7_IRQn);

	/* USART1 interrupt Init */
	NVIC_SetPriority(USART1_IRQn, 0);	// every 95 us
	NVIC_EnableIRQ(USART1_IRQn);
}

