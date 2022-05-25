/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-11-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Led.H
;



/*

HW Pwm board with STM32F446 revision A

DCDC_SETx outputs temporary used for debugging.

*/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void Led_Init(void);

#define LED1_ON		do {}while(0)
#define LED2_ON		do {}while(0)
#define LED3_ON		do {}while(0)
#define LED4_ON		do {}while(0)

#define LED1_OFF	do {}while(0)
#define LED2_OFF	do {}while(0)
#define LED3_OFF	do {}while(0)
#define LED4_OFF	do {}while(0)

