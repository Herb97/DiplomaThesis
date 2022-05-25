/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OutputVoltage.H
;
;******************************************************************************
; SVN header
;  $Id: OutputVoltage.H 117385 2022-03-11 17:22:37Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void OutputVoltage_Init(void);

void OutputVoltage_StateMachine(void);

bool bOutputVoltage_Set(float32_t lfOutputVoltage);
bool bOutputVoltage_Set_mV(uint16_t luwOutputVoltage);

float32_t fOutputVoltage_Read(void);
uint16_t uwOutputVoltage_Read(void);

