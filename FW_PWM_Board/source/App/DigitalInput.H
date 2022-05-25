/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-04-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: DigitalInput.H
;
;******************************************************************************
; SVN header
;  $Id: DigitalInput.H 114353 2021-08-10 15:19:03Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/

void DigitalInput_Every1ms(uint16_t luwRawInput);

bool bDigitalInput_Polarity_Set(uint16_t luwPolarity);
uint16_t uwDigitalInput_Polarity_Get(void);

uint16_t uwDigitalInput_RawData_Get(void);		// direct read + polarity
uint16_t uwDigitalInput_FilteredData_Get(void);


