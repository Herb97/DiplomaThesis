/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-03-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: USART1.H
;
;******************************************************************************
; SVN header
;  $Id: USART1.H 117605 2022-03-24 07:57:34Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void Usart1_Init(void);

// RX
uint8_t ubUsart1_Rx_Quantity(void);
uint8_t ubUsart1_Rx_Get(void);

// TX
void Usart1_MainLoop(void);
void Usart1_PutMultiple(uint8_t const * pSrc, uint8_t lubSize);
