/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: DutyCycle.H
;
;******************************************************************************
; SVN header
;  $Id: DutyCycle.H 116376 2022-01-17 16:08:00Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void DutyCycle_Init(void);
void DutyCycle_5us(uint16_t luwPort);


float32_t fDutyCycle_Get(uint8_t lubInputIndex);
float32_t fFrequency_Get(uint8_t lubInputIndex);
uint16_t uwDutyCycle_Get(uint8_t lubInputIndex);
uint16_t uwFrequency_Get(uint8_t lubInputIndex);

uint32_t ulDutyCycle_Edges_Get(uint8_t lubInputIndex);

