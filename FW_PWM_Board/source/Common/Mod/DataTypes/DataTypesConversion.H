/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2018-07-04           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: DataTypesConversion.H
;
;******************************************************************************
; SVN header
;  $Id: DataTypesConversion.H 116952 2022-02-16 16:53:49Z Stepanek, Michal $
******************************************************************************/

/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
u8 ubDataTypesConversion_u16_to_u8(u16 luwValue);
u8 ubDataTypesConversion_s16_to_u8(s16 lswValue);
s8 sbDataTypesConversion_s16_to_s8(s16 lswValue);
u8 ubDataTypesConversion_u32_to_u8(u32 lulValue);
u16 uwDataTypesConversion_u32_to_u16(u32 lulValue);
u16 uwDataTypesConversion_float_to_u16(float32_t f);
s16 swDataTypesConversion_float_to_s16(float32_t f);
u8 ubDataTypesConversion_float_to_u8(float32_t f);
void DataTypesConversion_u32_to_string(u32 lulInputNumber, u8 *pOutputString);
