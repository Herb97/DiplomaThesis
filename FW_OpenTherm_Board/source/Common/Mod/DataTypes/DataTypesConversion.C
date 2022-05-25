/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2018-07-04           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: DataTypesConversion.C
;
;******************************************************************************
; SVN header
;  $Id: DataTypesConversion.C 118384 2022-05-05 13:54:05Z Stepanek, Michal $
******************************************************************************/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include "..\Arithmetic\Limit.H"			// fLimit()
#include ".\DataTypesConversion.H"			// OWN header

/******************************************************************************
; Procedure     : ubDataTypesConversion_u16_to_u8()
; Description   : Limits luwValue from top to fit uint8_t
;******************************************************************************/
uint8_t ubDataTypesConversion_u16_to_u8(uint16_t luwValue)
{
	return (luwValue>0xFFu)?0xFFu:luwValue;
}

/******************************************************************************
; Procedure     : ubDataTypesConversion_s16_to_u8()
; Description   : Limits luwValue from top to fit uint8_t
;******************************************************************************/
uint8_t ubDataTypesConversion_s16_to_u8(int16_t lswValue)
{
	if( lswValue < 0 )
	{
		lswValue = 0;
	}
	else if( lswValue > 255 )
	{
		lswValue = 255;
	}
	else
	{}
	return (uint8_t)lswValue;
}

/******************************************************************************
; Procedure     : sbDataTypesConversion_s16_to_s8()
; Description   : Limits lswValue to fit int8_t
;******************************************************************************/
int8_t sbDataTypesConversion_s16_to_s8(int16_t lswValue)
{
	if( lswValue < -128 )
	{
		lswValue = -128;
	}
	else if( lswValue > 0x7F )
	{
		lswValue = 0x7F;
	}
	else
	{}
	return (int8_t)lswValue;
}

/******************************************************************************
; Procedure     : ubDataTypesConversion_u32_to_u8()
; Description   : Limits lulValue from top to fit uint8_t
;******************************************************************************/
uint8_t ubDataTypesConversion_u32_to_u8(uint32_t lulValue)
{
	return (lulValue>0xFFu)?0xFFu:lulValue;
}

/******************************************************************************
; Procedure     : uwDataTypesConversion_u32_to_u16()
; Description   : Limits lswValue to fit uint16_t
;******************************************************************************/
uint16_t uwDataTypesConversion_u32_to_u16(uint32_t lulValue)
{
	return (lulValue>0xFFFF)?0xFFFF:lulValue;
}


/******************************************************************************
; Procedure		: uwDataTypesConversion_float_to_u16()
; Description	: Converison of float32_t to uint16_t, rounding to nearest
; Input			: float32_t
; Output		: uint16_t
;******************************************************************************/
uint16_t uwDataTypesConversion_float_to_u16(float32_t f)
{
	f+=0.5f;	// rounding to nearest
	f = fLimit(f, 0.0f, 65535.0f);
	return (uint16_t)(f);
}


/******************************************************************************
; Procedure		: swDataTypesConversion_float_to_s16()
; Description	: Converison of float32_t to int16_t, rounding to nearest
; Input			: float32_t
; Output		: int16_t
;******************************************************************************/
int16_t swDataTypesConversion_float_to_s16(float32_t f)
{
	if(f >= 0)
	{
		f+=0.5f;	// rounding to nearest
	}
	else
	{
		f-=0.5f;	// rounding to nearest
	}
	f = fLimit(f, -32768.0f, 32767.0f);
	return (int16_t)(f);
}

/******************************************************************************
; Procedure		: ubDataTypesConversion_float_to_u8()
; Description	: Converison of float32_t to uint8_t, rounding to nearest
; Input			: float32_t
; Output		: uint8_t
;******************************************************************************/
uint8_t ubDataTypesConversion_float_to_u8(float32_t f)
{
	f += 0.5f;	// rounding to nearest
	f = fLimit(f, 0.0f, 255.0f);
	return (int16_t)(f);
}

/******************************************************************************
; Procedure		: DataTypesConversion_u32_to_string()
; Description	: Converison of uint32_t to string, radix is 10.
					From	0x00000000	0
					To		0xFFFFFFFF	4294967295
; Input			: unsigned 32 bits wide number
; Output		: string (up to 10 characters + trailing zero)
; Inspired by	: https://searchcode.com/codesearch/view/20251605/
				  https://www.microchip.com/forums/m687600.aspx
;******************************************************************************/
void DataTypesConversion_u32_to_string(uint32_t lulInputNumber, uint8_t *pOutputString)
{
	uint8_t temp[10];		// length of 4294967295 without trailing zero (4294967295 ... 0xFFFFFFFF)
	uint8_t lubIndex = 0u;

	//construct a backward string of the number.
	do
	{
		temp[lubIndex] = lulInputNumber % 10u;
		lubIndex++;
		lulInputNumber /= 10u;
	} while (lulInputNumber > 0u);

	//now reverse the string.
	while (lubIndex > 0)
	{
		// while there are still characters
		--lubIndex;
		*pOutputString = temp[lubIndex] + '0';
		pOutputString++;
	}
	*pOutputString = 0x00u; // add null termination.
}