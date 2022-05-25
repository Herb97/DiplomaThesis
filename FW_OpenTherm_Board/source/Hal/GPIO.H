/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: GPIO.H
;
;******************************************************************************
; SVN header
;  $Id: GPIO.H 114844 2021-09-18 06:45:57Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void GPIO_Init(void);
void GPIO_Output_PushPull(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Output_PushPull_FreqLow(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Input_PullUp(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Input_PullNo(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Analog(GPIO_TypeDef *GPIOx, uint32_t Pin);

