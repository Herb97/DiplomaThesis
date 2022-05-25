/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: InputThreshold.C
;
*/


/*
PWM input threshold

TODO:
Driving of DACs
*/

#include "..\Hal\DAC.H"
#include ".\InputThreshold.H"				// OWN header

float32_t mfInputThreshold[2] = {2.5f, 2.5f};	// Threshold in Volts, seen from input connector

/**
  * @brief ...
  * @param none
  * @retval ...
  */
float32_t fInputThreshold_Get_0(void)
{
	return mfInputThreshold[0];
}

/**
  * @brief ...
  * @param none
  * @retval ...
  */
float32_t fInputThreshold_Get_1(void)
{
	return mfInputThreshold[1];
}

/**
  * @brief ...
  * @param ...
  * @param ...
  * @param ...
  * @retval ...
  */
static float fLimit(float lfValue, float lfMin, float lfMax)
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
	{
		// empty
	}
	return lfValue;
}

/**
  * @brief ...
  * @param ...
  * @retval ...
  */
static uint16_t ubDataTypesConversion_float_to_u8(float f)
{
	f = f*256.0f;
	f = fLimit(f, 0.0f, 4095.0f);
	return (uint16_t)(f);
}

/**
  * @brief ...
  * @param ...
  * @retval ...
  */
bool bInputThreshold_Set_0(float32_t x)
{
	mfInputThreshold[0] = x;
	return true;
}

/**
  * @brief ...
  * @param ...
  * @retval ...
  */
bool bInputThreshold_Set_1(float32_t x)
{
	mfInputThreshold[1] = x;
	return true;
}

/**
  * @brief Call regulary to update DACs.
  * @param none
  * @retval none
  */
void InputThreshold_MainLoop(void)
{
	bDAC_CH1Value_Set(ubDataTypesConversion_float_to_u8(mfInputThreshold[0]));
	bDAC_CH2Value_Set(ubDataTypesConversion_float_to_u8(mfInputThreshold[1]));
}


/*
following function are just for debugging with u16, when float is not available
no limits used here
*/

/**
  * @brief Bridge to fInputThreshold_Get_0()
  * @param none
  * @retval Output in mV, whole number 16 bits wide
  */
uint16_t uwInputThreshold_Get_0(void)
{
	float32_t f;
	f = fInputThreshold_Get_0()*1000.0f;	// Convert from V to mV
	return (uint16_t)f;
}

/**
  * @brief Bridge to fInputThreshold_Get_1()
  * @param none
  * @retval Output in mV, whole number 16 bits wide
  */
uint16_t uwInputThreshold_Get_1(void)
{
	float32_t f;
	f = fInputThreshold_Get_1()*1000.0f;	// Convert from V to mV
	return (uint16_t)f;
}

/**
  * @brief Bridge to bInputThreshold_Set_0()
  * @param Input in mV, whole number 16 bits wide
  * @retval see bInputThreshold_Set_0()
  */
bool bInputThreshold_Set_0_u16(uint16_t x)
{
	float32_t f = x;
	f /= 1000.0f; // Convert from mV to V
	return bInputThreshold_Set_0(f);
}

/**
  * @brief Bridge to bInputThreshold_Set_1()
  * @param Input in mV, whole number 16 bits wide
  * @retval see bInputThreshold_Set_1()
  */
bool bInputThreshold_Set_1_u16(uint16_t x)
{
	float32_t f = x;
	f /= 1000.0f; // Convert from mV to V
	return bInputThreshold_Set_1(f);
}
