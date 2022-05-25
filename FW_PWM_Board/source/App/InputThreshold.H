/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: InputThreshold.H
;
;******************************************************************************
; SVN header
;  $Id: InputThreshold.H 116629 2022-02-01 13:42:46Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
float32_t	fInputThreshold_Get_0(void);
float32_t	fInputThreshold_Get_1(void);

bool	bInputThreshold_Set_0(float32_t x);
bool	bInputThreshold_Set_1(float32_t x);

void InputThreshold_MainLoop(void);

uint16_t	uwInputThreshold_Get_0(void);
uint16_t	uwInputThreshold_Get_1(void);

bool	bInputThreshold_Set_0_u16(uint16_t x);
bool	bInputThreshold_Set_1_u16(uint16_t x);
