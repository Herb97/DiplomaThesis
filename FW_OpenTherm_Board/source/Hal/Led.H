/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Led.H
;
;******************************************************************************
; SVN header
;  $Id: Led.H 117554 2022-03-22 12:45:01Z Stepanek, Michal $
******************************************************************************/


/*

OpenTherm board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS21xxxx/210003

Monitor
	Green	PD7
	Red		PB3
	Blue	PB4
	Yellow	PB5

Master
	Green	PE2
	Red		PE3
	Blue	PE4
	Yellow	PE5

Slave
	Green	PA6
	Red		PA7
	Blue	PC4
	Yellow	PC5

*/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void Led_Init(void);


#define LED_MONITOR_G_ON	do {GPIOD->BRR = BIT7;}while(0)
#define LED_MONITOR_R_ON	do {GPIOB->BRR = BIT3;}while(0)
#define LED_MONITOR_B_ON	do {GPIOB->BRR = BIT4;}while(0)
#define LED_MONITOR_Y_ON	do {GPIOB->BRR = BIT5;}while(0)
#define LED_MASTER_G_ON		do {GPIOE->BRR = BIT2;}while(0)
#define LED_MASTER_R_ON		do {GPIOE->BRR = BIT3;}while(0)
#define LED_MASTER_B_ON		do {GPIOE->BRR = BIT4;}while(0)
#define LED_MASTER_Y_ON		do {GPIOE->BRR = BIT5;}while(0)
#define LED_SLAVE_G_ON		do {GPIOA->BRR = BIT6;}while(0)
#define LED_SLAVE_R_ON		do {GPIOA->BRR = BIT7;}while(0)
#define LED_SLAVE_B_ON		do {GPIOC->BRR = BIT4;}while(0)
#define LED_SLAVE_Y_ON		do {GPIOC->BRR = BIT5;}while(0)

#define LED_MONITOR_G_OFF	do {GPIOD->BSRR = BIT7;}while(0)
#define LED_MONITOR_R_OFF	do {GPIOB->BSRR = BIT3;}while(0)
#define LED_MONITOR_B_OFF	do {GPIOB->BSRR = BIT4;}while(0)
#define LED_MONITOR_Y_OFF	do {GPIOB->BSRR = BIT5;}while(0)
#define LED_MASTER_G_OFF	do {GPIOE->BSRR = BIT2;}while(0)
#define LED_MASTER_R_OFF	do {GPIOE->BSRR = BIT3;}while(0)
#define LED_MASTER_B_OFF	do {GPIOE->BSRR = BIT4;}while(0)
#define LED_MASTER_Y_OFF	do {GPIOE->BSRR = BIT5;}while(0)
#define LED_SLAVE_G_OFF		do {GPIOA->BSRR = BIT6;}while(0)
#define LED_SLAVE_R_OFF		do {GPIOA->BSRR = BIT7;}while(0)
#define LED_SLAVE_B_OFF		do {GPIOC->BSRR = BIT4;}while(0)
#define LED_SLAVE_Y_OFF		do {GPIOC->BSRR = BIT5;}while(0)

