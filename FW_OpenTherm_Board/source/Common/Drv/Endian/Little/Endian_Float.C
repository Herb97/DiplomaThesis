/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2008-01-30           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: Endian_Float.C
;
;******************************************************************************
; SVN header
;  $Id: Endian_Float.C 116376 2022-01-17 16:08:00Z Stepanek, Michal $
******************************************************************************/

/*
Funkce pro práci s float32_t jsou compiler specific
Little endian (MSP430, ARM Cortex-M3)
*/

#include "..\Endian.H"

float32_t fEndian_MsbLsbToFloat(uint8_t * ptr)
{
	float32_t f;
	*(((uint8_t *)&f)+3)=ptr[0];
	*(((uint8_t *)&f)+2)=ptr[1];
	*(((uint8_t *)&f)+1)=ptr[2];
	*(((uint8_t *)&f)+0)=ptr[3];
	return f;
}

void Endian_FloatToMsbLsb(float32_t f, uint8_t * ptr)
{
	ptr[0]=*(((uint8_t *)&f)+3);
	ptr[1]=*(((uint8_t *)&f)+2);
	ptr[2]=*(((uint8_t *)&f)+1);
	ptr[3]=*(((uint8_t *)&f)+0);
}

uint16_t Endian_FloatToMsbLsbH(float32_t f, uint8_t * ptr)
{
	uint16_t result;
  	ptr[0]=*(((uint8_t *)&f)+3);
	ptr[1]=*(((uint8_t *)&f)+2);
	result=ptr[0];
	result<<=8;
	result|=ptr[1];
	return result;
}

uint16_t Endian_FloatToMsbLsbL(float32_t f, uint8_t * ptr)
{
	uint16_t result;
  	ptr[0]=*(((uint8_t *)&f)+1);
	ptr[1]=*(((uint8_t *)&f)+0);
	result=ptr[0];
	result<<=8;
	result|=ptr[1];
	return result;
}

float64_t Endian_MsbLsbToDouble(uint8_t * ptr)
{
	float64_t f;
	*(((uint8_t *)&f)+7)=ptr[0];
	*(((uint8_t *)&f)+6)=ptr[1];
	*(((uint8_t *)&f)+5)=ptr[2];
	*(((uint8_t *)&f)+4)=ptr[3];
	*(((uint8_t *)&f)+3)=ptr[4];
	*(((uint8_t *)&f)+2)=ptr[5];
	*(((uint8_t *)&f)+1)=ptr[6];
	*(((uint8_t *)&f)+0)=ptr[7];
	return f;
}

void Endian_DoubleToMsbLsb(float64_t f, uint8_t * ptr)
{
	ptr[0]=*(((uint8_t *)&f)+7);
	ptr[1]=*(((uint8_t *)&f)+6);
	ptr[2]=*(((uint8_t *)&f)+5);
	ptr[3]=*(((uint8_t *)&f)+4);
	ptr[4]=*(((uint8_t *)&f)+3);
	ptr[5]=*(((uint8_t *)&f)+2);
	ptr[6]=*(((uint8_t *)&f)+1);
	ptr[7]=*(((uint8_t *)&f)+0);
}

float32_t fEndian_LsbMsbToFloat(uint8_t * ptr)
{
	float32_t f;
	*(((uint8_t *)&f)+0)=ptr[0];
	*(((uint8_t *)&f)+1)=ptr[1];
	*(((uint8_t *)&f)+2)=ptr[2];
	*(((uint8_t *)&f)+3)=ptr[3];
	return f;
}

void Endian_FloatToLsbMsb(float32_t f, uint8_t * ptr)
{
	ptr[0]=*(((uint8_t *)&f)+0);
	ptr[1]=*(((uint8_t *)&f)+1);
	ptr[2]=*(((uint8_t *)&f)+2);
	ptr[3]=*(((uint8_t *)&f)+3);
}

float64_t Endian_LsbMsbToDouble(uint8_t * ptr)
{
	float64_t f;
	*(((uint8_t *)&f)+0)=ptr[0];
	*(((uint8_t *)&f)+1)=ptr[1];
	*(((uint8_t *)&f)+2)=ptr[2];
	*(((uint8_t *)&f)+3)=ptr[3];
	*(((uint8_t *)&f)+4)=ptr[4];
	*(((uint8_t *)&f)+5)=ptr[5];
	*(((uint8_t *)&f)+6)=ptr[6];
	*(((uint8_t *)&f)+7)=ptr[7];
	return f;
}

void Endian_DoubleToLsbMsb(float64_t f, uint8_t * ptr)
{
	ptr[0]=*(((uint8_t *)&f)+0);
	ptr[1]=*(((uint8_t *)&f)+1);
	ptr[2]=*(((uint8_t *)&f)+2);
	ptr[3]=*(((uint8_t *)&f)+3);
	ptr[4]=*(((uint8_t *)&f)+4);
	ptr[5]=*(((uint8_t *)&f)+5);
	ptr[6]=*(((uint8_t *)&f)+6);
	ptr[7]=*(((uint8_t *)&f)+7);
}

// zde musí být binární porovnání, jinak by porovnání dvou úplnì stejných NaN skonèilo chybnì
bool Endian_FloatCompareMsbLsb(float32_t f, uint8_t * ptr)
{
	if((ptr[0]==*(((uint8_t *)&f)+3))&&(ptr[1]==*(((uint8_t *)&f)+2))&&(ptr[2]==*(((uint8_t *)&f)+1))&&(ptr[3]==*(((uint8_t *)&f)+0)))
	{
		return false;	// the same
	}
	else
	{
		return true;	// changed
	}
}

