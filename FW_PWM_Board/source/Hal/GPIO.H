/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-03-27           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: GPIO.H
;
;******************************************************************************
; SVN header
;  $Id: GPIO.H 115584 2021-11-19 10:43:50Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void GPIO_Init(void);
void GPIO_Output_PushPull(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Output_PushPull_FreqLow(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Output_OpenDrain_PullUp_FreqLow(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Input_PullUp(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Input_PullNo(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Analog(GPIO_TypeDef *GPIOx, uint32_t Pin);

