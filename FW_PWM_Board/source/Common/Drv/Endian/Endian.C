/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2006-12-05           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: Endian.C
;
;******************************************************************************
; SVN header
;  $Id: Endian.C 110620 2020-11-26 10:08:10Z Stepanek, Michal $
******************************************************************************/

/*
Modul pro konverzi øazení bytù v int a long, pro little i big endian
*/

#include ".\Endian.H"

uint16_t uwEndian_LsbMsbToU16(uint8_t * ptr)
{
	uint16_t result;
	result=ptr[1];
	result<<=8;
	result|=ptr[0];
	return result;
}

uint16_t uwEndian_MsbLsbToU16(uint8_t * ptr)
{
	uint16_t result;
	result=ptr[0];
	result<<=8;
	result|=ptr[1];
	return result;
}

uint32_t ulEndian_MsbLsbToU24(uint8_t * ptr)
{
	uint32_t result;
	result=ptr[0];
	result<<=8;
	result|=ptr[1];
	result<<=8;
	result|=ptr[2];
	return result;
}

uint32_t ulEndian_LsbMsbToU32(uint8_t * ptr)
{
	uint32_t result;
	result=ptr[3];
	result<<=8;
	result|=ptr[2];
	result<<=8;
	result|=ptr[1];
	result<<=8;
	result|=ptr[0];
	return result;
}

uint32_t ulEndian_MsbLsbToU32(uint8_t * ptr)
{
	uint32_t result;
	result=ptr[0];
	result<<=8;
	result|=ptr[1];
	result<<=8;
	result|=ptr[2];
	result<<=8;
	result|=ptr[3];
	return result;
}

void Endian_U16ToLsbMsb(uint16_t i, uint8_t * ptr)
{
	ptr[0]=0x00FF&i;
	ptr[1]=(i>>8);
}

void Endian_U16ToMsbLsb(uint16_t i, uint8_t * ptr)
{
	ptr[0]=(i>>8);
	ptr[1]=0x00FF&i;
}

void Endian_U24ToMsbLsb(uint32_t l, uint8_t * ptr)
{
	ptr[0]=0x000000FF&(l>>16);
	ptr[1]=0x000000FF&(l>>8);
	ptr[2]=0x000000FF&l;
}

void Endian_U32ToLsbMsb(uint32_t l, uint8_t * ptr)
{
	ptr[0]=0x000000FF&l;
	ptr[1]=0x000000FF&(l>>8);
	ptr[2]=0x000000FF&(l>>16);
	ptr[3]=0x000000FF&(l>>24);
}

void Endian_U32ToMsbLsb(uint32_t l, uint8_t * ptr)
{
	ptr[0]=0x000000FF&(l>>24);
	ptr[1]=0x000000FF&(l>>16);
	ptr[2]=0x000000FF&(l>>8);
	ptr[3]=0x000000FF&l;
}

uint32_t ulEndian_U16sToU32(uint16_t lsb, uint16_t msb)
{
	return ((((uint32_t)(msb))<<16)|(lsb));
}

uint16_t uwEndian_U8sToU16(uint8_t lsb, uint8_t msb)
{
	uint16_t x;
	x = msb;
	x <<= 8;
	x |= lsb;
	return x;
}

uint16_t uwEndian_MsbLsb2U16(uint8_t msb, uint8_t lsb)
{
	uint16_t x;
	x = msb;
	x <<= 8;
	x |= lsb;
	return x;
}
