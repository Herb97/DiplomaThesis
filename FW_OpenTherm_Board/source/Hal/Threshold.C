/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-04-01           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Threshold.C
;
*/

/*
Handling of ADC threshold levels or DAC low/high levels
*/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include <math.h>							// NAN
#include "..\Common\Mod\DataTypes\DataTypesConversion.H"	// uwDataTypesConversion_float_to_u16()
#include ".\Threshold.H"					// OWN header

/*
	Voltage ADC values:

	Low level    (0-7V):		 0u -  1136u
	High level (15-18V):	  2433u -  2920u

	Current ADC values (master/slave) - INA186A2 reference voltage = 0V:

	Low level    (5-9mA):	   811u -  1460u
	High level (17-23mA):	  2758u -  3731u

	Current ADC values (monitor) - INA186A2 reference voltage = 0.5*TL431 reference:

	Low level    (5-9mA):     2454u -  2778u
	High level (17-23mA):	  3427u -  3914u
*/

/*
	page 5	PA2	ADC_IN2		MASTER		ADC_CURRENT_MASTER
	page 5	PA3	ADC_IN3		MASTER		ADC_VOLTAGE_MASTER
	page 5	PA4 DAC_OUT1	MASTER		DAC_VOLTAGE_MASTER
	page 4	PA5	DAC_OUT2	SLAVE		DAC_CURRENT_SLAVE
	page 4	PB0	ADC_IN8		SLAVE		ADC_CURRENT_SLAVE
	page 4	PB1	ADC_IN9		SLAVE		ADC_VOLTAGE_SLAVE
	page 6	PC0	ADC_IN10	MONITOR		ADC_VOLTAGE_MONITOR
	page 6	PC1	ADC_IN11	MONITOR		ADC_CURRENT_MONITOR
*/

#define		ADC_FULL_SCALE		4095.0f
#define		ADC_FULL_VOlTAGE	25.0f	// 25 V
#define		ADC_FULL_CURRENT	25.0f	// 25 mA
#define		DAC_FULL_SCALE		4095.0f
#define		DAC_FULL_VOlTAGE	25.0f	// 25 V
#define		DAC_FULL_CURRENT	25.0f	// 25 mA
#define		REFERENCE_VOLTAGE	2.5f

// [div/Volt]
// [div/mA]

// master
#define		ADC_CURRENT_MASTER		(ADC_FULL_SCALE/ADC_FULL_CURRENT)	// divider 1:10, range 0..25 mA
#define		ADC_VOLTAGE_MASTER		(ADC_FULL_SCALE/ADC_FULL_VOlTAGE)	// divider 1:10, range 0..25 V
#define		DAC_VOLTAGE_MASTER		(DAC_FULL_SCALE/DAC_FULL_VOlTAGE)	// range 0..25 V

// slave
#define		DAC_CURRENT_SLAVE		(DAC_FULL_SCALE/DAC_FULL_CURRENT)	// range 0..25 mA
#define		ADC_CURRENT_SLAVE		(ADC_FULL_SCALE/ADC_FULL_CURRENT)	// divider 1:10, range 0..25 mA
#define		ADC_VOLTAGE_SLAVE		(ADC_FULL_SCALE/ADC_FULL_VOlTAGE)	// divider 1:10, range 0..25 V

// monitor
#define		ADC_VOLTAGE_MONITOR		(ADC_FULL_SCALE/ADC_FULL_VOlTAGE)	// divider 1:10, range 0..25 V
#define		ADC_CURRENT_MONITOR		((ADC_FULL_SCALE/2.0f)/ADC_FULL_CURRENT)	// divider 1:10, range -25..+25 mA


uint16_t muwLevel[LEVEL_COUNT];


typedef struct {
	float32_t	fConversion	;	// [div/V] or [div/mA]
	float32_t	fMin		;	// [V] or [mA]
	float32_t	fMax		;	// [V] or [mA]
	float32_t	fDefault	;	// [V] or [mA]
} const LEVEL_TABLE;

LEVEL_TABLE LevelTable[LEVEL_COUNT]=
{
//	conversion				min			max			default after power up
	{ADC_CURRENT_MASTER	,	 5.0f	,	23.0f	,	12.5f},	//	MASTER_CURRENT_THRESHOLD
	{ADC_CURRENT_MONITOR,	 5.0f	,	23.0f	,	12.5f},	//	MONITOR_CURRENT_THRESHOLD
	{DAC_CURRENT_SLAVE	,	 5.0f	,	 9.0f	,	 7.5f},	//	SLAVE_CURRENT_LOW
	{DAC_CURRENT_SLAVE	,	17.0f	,	23.0f	,	20.0f},	//	SLAVE_CURRENT_HIGH
	{DAC_VOLTAGE_MASTER	,	 0.0f	,	 7.0f	,	 6.0f},	//	MASTER_VOLTAGE_LOW
	{DAC_VOLTAGE_MASTER	,	15.0f	,	18.0f	,	16.5f},	//	MASTER_VOLTAGE_HIGH
	{ADC_VOLTAGE_MONITOR,	 0.0f	,	18.0f	,	11.0f},	//	MONITOR_VOLTAGE_THRESHOLD
	{ADC_VOLTAGE_SLAVE	,	 0.0f	,	18.0f	,	11.0f},	//	SLAVE_VOLTAGE_THRESHOLD
};


/******************************************************************************
; Procedure     : uwLevel_Get()
; Description   : Return ADC threshold level or DAC low/high level
; Input         : Level_Index_t
; Output        : Level [div]
;*****************************************************************************/
uint16_t uwLevel_Get(Level_Index_t lubIndex)
{
	if (lubIndex < LEVEL_COUNT)
	{
		return muwLevel[lubIndex];
	}
	else
	{
		return 0u;
	}
}


/******************************************************************************
; Procedure     : bLevel_Set()
; Description   : Set ADC threshold level or DAC low/high level - Modbus interface
; Input         : [V] or [mA]
; Input         : Level_Index_t
; Output        : true/false
;*****************************************************************************/
bool bLevel_Set(float32_t f, Level_Index_t lubIndex)
{
	if (lubIndex < LEVEL_COUNT)
	{
		if ((f >= LevelTable[lubIndex].fMin) && (f <= LevelTable[lubIndex].fMax))
		{
			f *= LevelTable[lubIndex].fConversion;
			muwLevel[lubIndex] = uwDataTypesConversion_float_to_u16(f);
			return true;
		}
	}
	return false;
}


/******************************************************************************
; Procedure     : fLevel_Get()
; Description   : Set ADC threshold level or DAC low/high level - Modbus interface
; Input         : Level_Index_t
; Output        : [V] or [mA]
;*****************************************************************************/
float32_t fLevel_Get(Level_Index_t lubIndex)
{
	if (lubIndex < LEVEL_COUNT)
	{
		return muwLevel[lubIndex]/LevelTable[lubIndex].fConversion;
	}
	return NAN;
}


/******************************************************************************
; Procedure     : Level_Init()
; Description   : Initialize all levels
; Input         : -
; Output        : -
;*****************************************************************************/
void Level_Init(void)
{
	for (Level_Index_t lubIndex = (Level_Index_t)0u; lubIndex < LEVEL_COUNT; lubIndex++)
	{
		bLevel_Set(LevelTable[lubIndex].fDefault, lubIndex);
	}
}

