/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-05-06           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Counter.H
;
;******************************************************************************
; SVN header
;  $Id: Counter.H 118392 2022-05-06 06:29:41Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void Counter_100us(void);

uint16_t uwCounter_TimeStamp_GetAndClear(void);
/*uint16_t TimeStampCounter_Get(void);
void TimeStampCounter_Clear(void);*/
uint16_t uwCounter_ResponseTime_Get(void);
void Counter_ResponseTime_Clear(void);
uint16_t uwCounter_SerialData_GetAndClear(void);
