/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-03-27           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: USART1.H
;
;******************************************************************************
; SVN header
;  $Id: USART1.H 114353 2021-08-10 15:19:03Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void Usart1_Init(void);
void Usart1_PutChar(uint8_t c);
uint8_t ubUsart1_GetChar(void);
void Usart1_DriverEnable(void);
void Usart1_DriverDisable(void);
