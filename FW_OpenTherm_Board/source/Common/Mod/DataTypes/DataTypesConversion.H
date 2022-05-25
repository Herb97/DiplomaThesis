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
;  $Id: DataTypesConversion.H 118384 2022-05-05 13:54:05Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
uint8_t ubDataTypesConversion_u16_to_u8(uint16_t luwValue);
uint8_t ubDataTypesConversion_s16_to_u8(int16_t lswValue);
int8_t sbDataTypesConversion_s16_to_s8(int16_t lswValue);
uint8_t ubDataTypesConversion_u32_to_u8(uint32_t lulValue);
uint16_t uwDataTypesConversion_u32_to_u16(uint32_t lulValue);
uint16_t uwDataTypesConversion_float_to_u16(float32_t f);
int16_t swDataTypesConversion_float_to_s16(float32_t f);
uint8_t ubDataTypesConversion_float_to_u8(float32_t f);
void DataTypesConversion_u32_to_string(uint32_t lulInputNumber, uint8_t *pOutputString);
