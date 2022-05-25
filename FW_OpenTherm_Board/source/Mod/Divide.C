/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2019-10-08           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: Divide.C
;
;******************************************************************************
; SVN header
;  $Id: Divide.C 116819 2022-02-10 14:16:36Z Stepanek, Michal $
******************************************************************************/

/*
2021-05-15 Michal Stepanek
Extended valid input range
*/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
//#include "..\..\..\Cfg\types.h"
#include ".\Divide.H"						// OWN header
#include <math.h>	// fmod

/*// Valid input range from -32768 (0x8000) to +32767 (0x7FFF)
s16 swDivideRoundNearest_100(s16 x)
{
	if (x == -32768)
	{
		// -32768/100
		return -328;
	}
	else if (x >= 0)
	{
		return uwDivideRoundNearest(x, 100u);
	}
	else
	{
		x = uwDivideRoundNearest(-x, 100u);
		return -x;
	}
}

// Valid input range from -2147483648 (0x80000000) to +2147483647 (0x7FFFFFFF)
s32 slDivideRoundNearest_100(s32 x)
{
	if (x == -2147483648)
	{
		// -2147483648/100
		return -21474836;
	}
	else if (x >= 0)
	{
		return ulDivideRoundNearest(x, 100u);
	}
	else
	{
		x = ulDivideRoundNearest(-x, 100u);
		return -x;
	}
}

// Valid input range from -32768 (0x8000) to +32767 (0x7FFF)
s16 swDivideRoundNearest_10(s16 x)
{
	if (x == -32768)
	{
		// -32768/10
		return -3277;
	}
	else if (x >= 0)
	{
		return uwDivideRoundNearest(x, 10u);
	}
	else
	{
		x = uwDivideRoundNearest(-x, 10u);
		return -x;
	}
}

// Valid input range from -2147483648 (0x80000000) to +2147483647 (0x7FFFFFFF)
s32 slDivideRoundNearest_10(s32 x)
{
	if (x == -2147483648)
	{
		// -2147483648/10
		return -214748365;
	}
	else if (x >= 0)
	{
		return ulDivideRoundNearest(x, 10u);
	}
	else
	{
		x = ulDivideRoundNearest(-x, 10u);
		return -x;
	}
}

// Valid input range from -2147483648 (0x80000000) to +2147483647 (0x7FFFFFFF)
s32 slDivideRoundNearest_1000(s32 x)
{
	if (x == -2147483648)
	{
		// -2147483648/1000
		return -2147484;
	}
	else if (x >= 0)
	{
		return ulDivideRoundNearest(x, 1000u);
	}
	else
	{
		x = ulDivideRoundNearest(-x, 1000u);
		return -x;
	}
}*/

uint32_t ulDivideRoundUp(uint32_t lulDivident, uint32_t lulDivisor)
{
	uint32_t lulRemainder = lulDivident % lulDivisor;
	uint32_t lulQuotient = lulDivident / lulDivisor;
	if (lulRemainder)
	{
		lulQuotient++;
	}
	return lulQuotient;
}

// for positive numbers only
uint32_t ulDivideRoundUpFromFloat(float32_t lflDivident, float32_t lflDivisor)
{
	float32_t lflRemainder = fmodf(lflDivident, lflDivisor);
	float32_t lfQuotient = lflDivident / lflDivisor;
	uint32_t lulQuotient = (uint32_t)lfQuotient;
	if (lflRemainder)
	{
		lulQuotient++;
	}
	return lulQuotient;
}

uint32_t ulDivideRoundNearest(uint32_t lulDivident, uint32_t lulDivisor)
{
	uint32_t lulRemainder = lulDivident % lulDivisor;
	uint32_t lulQuotient = lulDivident / lulDivisor;
	if (lulRemainder >= (lulDivisor/2u))
	{
		lulQuotient++;
	}
	return lulQuotient;
}

// for positive numbers only
/*uint32_t ulDivideRoundNearestFromFloat(float32_t lflDivident, float32_t lflDivisor)
{
	float32_t lflRemainder = fmod(lflDivident, lflDivisor);
	float32_t lfQuotient = lflDivident / lflDivisor;
	uint32_t lulQuotient = (uint32_t)lfQuotient;
	if (lflRemainder >= (lflDivisor/2.0f))
	{
		lulQuotient++;
	}
	return lulQuotient;
}*/

// for positive numbers only
uint32_t ulRoundNearestFromFloat(float32_t lflDivident)
{
	float32_t lflRemainder = fmodf(lflDivident, 1);
	float32_t lfQuotient = lflDivident / 1;
	uint32_t lulQuotient = (uint32_t)lfQuotient;
	if (lflRemainder >= (0.5))
	{
		lulQuotient++;
	}
	return lulQuotient;
}

uint16_t uwDivideRoundNearest(uint16_t luwDivident, uint16_t luwDivisor)
{
	uint16_t luwRemainder = luwDivident % luwDivisor;
	uint16_t luwQuotient = luwDivident / luwDivisor;
	if (luwRemainder >= (luwDivisor/2u))
	{
		luwQuotient++;
	}
	return luwQuotient;
}

/*
static u32 ulDivideRoundNearest_Test(u32 x)
{
	return (x+5)/10;
}

void Test(void)
{
	u16 i=0;
	do
	{
		__watchdog_reset();
		
		u16 x = uwDivideRoundNearest(i, 10);
		u16 y = ulDivideRoundNearest_Test(i);
		if (x != y)
		{
			while(1);
		}
		i++;
	}
	while(i);
}
*/
