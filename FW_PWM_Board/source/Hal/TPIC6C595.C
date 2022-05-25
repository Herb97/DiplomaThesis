/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: TPIC6C595.C
;
*/

/*

HW Pwm board with STM32F446 revision A

SCK					SRCK											SHCP
MOSI				SERIN											DS
PB7		TPIC6C595	RCK		OUTPUT_PUSHPULL				74HCT595	STCP	OUTPUT_PUSHPULL
PD2		TPIC6C595	G		OUTPUT_OPENDRAIN			74HCT595	OE		OUTPUT_PUSHPULL

*/

#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"	// LL_GPIO_PIN_..
#include "..\Hal\GPIO.H"					// GPIO_Output_PushPull(), GPIO_Output_OpenDrain_PullUp_FreqLow()
#include "..\Hal\SPI1.H"					// uwSpi1_Word()
#include ".\TPIC6C595.H"					// OWN header



#define TPIC6C595_RCK_1		do {GPIOB->BSRR = BIT7;}while(0)
#define TPIC6C595_RCK_0		do {GPIOB->BSRR = BIT7<<16;}while(0)
#define TPIC6C595_G_0		do {GPIOD->BSRR = BIT2<<16;}while(0)



/**
  * @brief TPIC6C595 related GPIO Initialization Function
  * @param None
  * @retval None
  */
void TPIC6C595_Init(void)
{
	/* PB7 OUTPUT_PUSHPULL */
	GPIO_Output_PushPull(GPIOB, LL_GPIO_PIN_7);
	
	/* PD2 OUTPUT_OPENDRAIN */
	GPIO_Output_OpenDrain_PullUp_FreqLow(GPIOD, LL_GPIO_PIN_2);
	
	TPIC6C595_RCK_0;
}

/**
  * @brief Write 16 bits to two cascaded TPIC6C595.
  * @param luwDataToWrite
  * @retval None
  */
void TPIC6C595_WriteWord(uint16_t luwDataToWrite)
{
	uwSpi1_Word(luwDataToWrite);

	// 200 ns delay 36 nop @ 180 MHz
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();

	TPIC6C595_RCK_1;
	
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	
	TPIC6C595_RCK_0;

	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();
	__no_operation();

	TPIC6C595_G_0;
}