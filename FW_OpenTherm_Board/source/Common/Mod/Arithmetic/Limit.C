/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2017-04-11           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: Limit.C
;
;******************************************************************************
; SVN header
;  $Id: Limit.C 118384 2022-05-05 13:54:05Z Stepanek, Michal $
******************************************************************************/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include ".\Limit.H"						// OWN header

//=======================================================================================================================================================
//				PUBLIC METHODS
//=======================================================================================================================================================

/******************************************************************************
; Procedure		: ubLess()
; Input			: x, y - unsigned byte
; Output		: lower of (x ,y)
;******************************************************************************/
uint8_t ubLess(uint8_t x, uint8_t y)
{
	return (x<y)?x:y;
}

/******************************************************************************
; Procedure		: ubGreater()
; Input			: x, y - unsigned byte
; Output		: greater of (x ,y)
;******************************************************************************/
uint8_t ubGreater(uint8_t x, uint8_t y)
{
	return (x>y)?x:y;
}

/******************************************************************************
; Procedure		: uwLess()
; Input			: x, y - unsigned word
; Output		: lower of (x ,y)
;******************************************************************************/
uint16_t uwLess(uint16_t x, uint16_t y)
{
	return (x<y)?x:y;
}

/******************************************************************************
; Procedure		: uwGreater()
; Input			: x, y - unsigned word
; Output		: greater of (x ,y)
;******************************************************************************/
uint16_t uwGreater(uint16_t x, uint16_t y)
{
	return (x>y)?x:y;
}

/******************************************************************************
; Procedure		: ulLess()
; Input			: x, y - unsigned long
; Output		: lower of (x ,y)
;******************************************************************************/
uint32_t ulLess(uint32_t x, uint32_t y)
{
	return (x<y)?x:y;
}

/******************************************************************************
; Procedure		: ulGreater()
; Input			: x, y - unsigned long
; Output		: greater of (x ,y)
;******************************************************************************/
uint32_t ulGreater(uint32_t x, uint32_t y)
{
	return (x>y)?x:y;
}

/******************************************************************************
; Procedure		: sbLess()
; Input			: x, y - signed byte
; Output		: lower of (x ,y)
;******************************************************************************/
int8_t sbLess(int8_t x, int8_t y)
{
	return (x<y)?x:y;
}

/******************************************************************************
; Procedure		: sbGreater()
; Input			: x, y - signed byte
; Output		: greater of (x ,y)
;******************************************************************************/
int8_t sbGreater(int8_t x, int8_t y)
{
	return (x>y)?x:y;
}

/******************************************************************************
; Procedure		: swLess()
; Input			: x, y - signed word
; Output		: lower of (x ,y)
;******************************************************************************/
int16_t swLess(int16_t x, int16_t y)
{
	return (x<y)?x:y;
}

/******************************************************************************
; Procedure		: swGreater()
; Input			: x, y - signed word
; Output		: greater of (x ,y)
;******************************************************************************/
int16_t swGreater(int16_t x, int16_t y)
{
	return (x>y)?x:y;
}

/******************************************************************************
; Procedure		: slLess()
; Input			: x, y - signed word
; Output		: lower of (x ,y)
;******************************************************************************/
int32_t slLess(int32_t x, int32_t y)
{
	return (x<y)?x:y;
}

/******************************************************************************
; Procedure		: slGreater()
; Input			: x, y - signed word
; Output		: greater of (x ,y)
;******************************************************************************/
int32_t slGreater(int32_t x, int32_t y)
{
	return (x>y)?x:y;
}

/******************************************************************************
; Procedure		: ubLimit()
; Input			: lubValue 
; Input			: lubMin 
; Input			: lubMax 
; Output		: corrected lubValue to fit in <lubMin,lubMax> range
;******************************************************************************/
uint8_t ubLimit(uint8_t lubValue, uint8_t lubMin, uint8_t lubMax)
{
	if( lubValue < lubMin )
	{
		lubValue = lubMin;
	}
	else if( lubValue > lubMax )
	{
		lubValue = lubMax;
	}
	else
	{}
	return lubValue;
}

/******************************************************************************
; Procedure		: sbLimit()
; Input			: lsbValue 
; Input			: lsbMin 
; Input			: lsbMax 
; Output		: corrected lsbValue to fit in <lsbMin,lsbMax> range
;******************************************************************************/
int8_t sbLimit(int8_t lsbValue, int8_t lsbMin, int8_t lsbMax)
{
	if( lsbValue < lsbMin )
	{
		lsbValue = lsbMin;
	}
	else if( lsbValue > lsbMax )
	{
		lsbValue = lsbMax;
	}
	else
	{}
	return lsbValue;
}

/******************************************************************************
; Procedure		: uwLimit()
; Input			: luwValue 
; Input			: luwMin 
; Input			: luwMax 
; Output		: corrected luwValue to fit in <luwMin,luwMax> range
;******************************************************************************/
uint16_t uwLimit(uint16_t luwValue, uint16_t luwMin, uint16_t luwMax)
{
	if( luwValue < luwMin )
	{
		luwValue = luwMin;
	}
	else if( luwValue > luwMax )
	{
		luwValue = luwMax;
	}
	else
	{}
	return luwValue;
}

/******************************************************************************
; Procedure		: swLimit()
; Input			: lswValue 
; Input			: lswMin 
; Input			: lswMax 
; Output		: corrected lswValue to fit in <lswMin,lswMax> range
;******************************************************************************/
int16_t swLimit(int16_t lswValue, int16_t lswMin, int16_t lswMax)
{
	if( lswValue < lswMin )
	{
		lswValue = lswMin;
	}
	else if( lswValue > lswMax )
	{
		lswValue = lswMax;
	}
	else
	{}
	return lswValue;
}

/******************************************************************************
; Procedure		: ulLimit()
; Input			: lulValue 
; Input			: lulMin 
; Input			: lulMax 
; Output		: corrected lulValue to fit in <lulMin,lulMax> range
;******************************************************************************/
uint32_t ulLimit(uint32_t lulValue, uint32_t lulMin, uint32_t lulMax)
{
	if( lulValue < lulMin )
	{
		lulValue = lulMin;
	}
	else if( lulValue > lulMax )
	{
		lulValue = lulMax;
	}
	else
	{}
	return lulValue;
}

/******************************************************************************
; Procedure		: slLimit()
; Input			: lslValue 
; Input			: lslMin 
; Input			: lslMax 
; Output		: corrected lslValue to fit in <lslMin,lslMax> range
;******************************************************************************/
int32_t slLimit(int32_t lslValue, int32_t lslMin, int32_t lslMax)
{
	if( lslValue < lslMin )
	{
		lslValue = lslMin;
	}
	else if( lslValue > lslMax )
	{
		lslValue = lslMax;
	}
	else
	{}
	return lslValue;
}

/******************************************************************************
; Procedure		: fLimit()
; Input			: lfValue 
; Input			: lfMin 
; Input			: lfMax 
; Output		: corrected lfValue to fit in <lfMin,lfMax> range
;******************************************************************************/
float32_t fLimit(float32_t lfValue, float32_t lfMin, float32_t lfMax)
{
	if( lfValue < lfMin )
	{
		lfValue = lfMin;
	}
	else if( lfValue > lfMax )
	{
		lfValue = lfMax;
	}
	else
	{}
	return lfValue;
}
