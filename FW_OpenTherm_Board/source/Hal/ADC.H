/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-03-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: ADC.H
;
;******************************************************************************
; SVN header
;  $Id: ADC.H 114843 2021-09-18 04:34:03Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void ADC_Init(void);
uint16_t uwADC_Data_Get(uint32_t lulChselr);

uint16_t uwADC_ADC_Current_Get(void);
uint16_t uwADC_ADC_Voltage_Get(void);
uint16_t uwADC_ADC_Current_Thermostat_Get(void);
uint16_t uwADC_ADC_Voltage_Thermostat_Get(void);
uint16_t uwADC_ADC_Voltage_Monitor_Get(void);
uint16_t uwADC_ADC_Current_Monitor_Get(void);