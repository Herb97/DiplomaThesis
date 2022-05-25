/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-11           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: DutyCycle.C
;
*/


#include ".\DutyCycle.H"					// OWN header

#define NUMBER_OF_INPUTS 16
#define SAMPLING_FREQUENCY	200000U		// 5 us alias 200 kHz
#define STEADY (SAMPLING_FREQUENCY)		// 1 second
#define COMPENSATION	0		// No compensation, tPHL and tPLH are the same

typedef struct
{
	uint16_t uwInput;		// last input state 0/1
	uint32_t ulCounter;		// duration of last input state (cannot overflow, maximum 0x7FFFFFFF)
	uint32_t ulLo;			// duration of Lo part, maximum 0x7FFFFFFF
	uint32_t ulHi;			// duration of Hi part, maximum 0x7FFFFFFF
	uint32_t ulEdges;		// edge counter (can overflow)
} DutyCycle_t;

DutyCycle_t mDutyCycle[NUMBER_OF_INPUTS];


/**
  * @brief Duty cycle measurement interrupt, takes roughly 3 us, every 5 us
  * @param None
  * @retval None
  */

void DutyCycle_5us(uint16_t luwPort)
{
	// all channels
	for (uint32_t i=0; i<NUMBER_OF_INPUTS; i++)
	{
		uint16_t luwMask = 1<<i;
		uint16_t luwPin = luwPort&luwMask;
		
		if (mDutyCycle[i].uwInput^luwPin)
		{
			// input changed
			mDutyCycle[i].uwInput = luwPin;
			mDutyCycle[i].ulEdges++;
			if (luwPin)
			{
				// change from 0 to 1, save how long 0 lasted
				mDutyCycle[i].ulLo = mDutyCycle[i].ulCounter;
			}
			else
			{
				// change from 1 to 0, save how long 1 lasted
				mDutyCycle[i].ulHi = mDutyCycle[i].ulCounter;
			}
			mDutyCycle[i].ulCounter = 1;
		}
		else
		{
			// input steady, limit maximum to 0x7FFFFFFF
			if (mDutyCycle[i].ulCounter < 0x7FFFFFFFu)
			{
				mDutyCycle[i].ulCounter++;
			}
		}
	}
}



/**
  * @brief Duty cycle measurement init
  * @param None
  * @retval None
  */

void DutyCycle_Init(void)
{
	// all channels
	for (uint32_t i=0; i<NUMBER_OF_INPUTS; i++)
	{
		mDutyCycle[i].uwInput	= 0;
		mDutyCycle[i].ulCounter	= 0;
		mDutyCycle[i].ulLo		= 0;
		mDutyCycle[i].ulHi		= 0;
		mDutyCycle[i].ulEdges	= 0;
	}
}


// simple evaluation of last Lo and Hi
// Includes compensation of different tPHL and tPLH
// 32 bit core and buses, no need to read twice
float32_t fDutyCycle_Get(uint8_t lubInputIndex)
{
	DutyCycle_t lDutyCycle = mDutyCycle[lubInputIndex];
	if ((lDutyCycle.ulCounter > STEADY)||(0==lDutyCycle.ulLo)||(0==lDutyCycle.ulHi))
	{
		// input is steady longer than STEADY, return 0 or 100 % duty cycle
		if (lDutyCycle.uwInput)
		{
			return 1.0f;
		}
		else
		{
			return 0.0f;
		}
	}
	else
	{
		// Compensation of different tPHL and tPLH
		if (lDutyCycle.ulHi > COMPENSATION)
		{
			lDutyCycle.ulHi -= COMPENSATION;
			lDutyCycle.ulLo += COMPENSATION;
		}
		
		// calculation of duty cycle 0..1
		float32_t f;
		f = lDutyCycle.ulLo;	// polarity inversion
		f /= (lDutyCycle.ulHi+lDutyCycle.ulLo);
		return f;
	}
}

// simple evaluation of last Lo and Hi
// 32 bit core and buses, no need to read twice
float32_t fFrequency_Get(uint8_t lubInputIndex)
{
	DutyCycle_t lDutyCycle = mDutyCycle[lubInputIndex];
	if ((lDutyCycle.ulCounter > STEADY)||(0==lDutyCycle.ulLo)||(0==lDutyCycle.ulHi))
	{
		// input is steady longer than STEADY, return 0 Hz frequency
		return 0.0f;
	}
	else
	{
		float32_t f;
		f = SAMPLING_FREQUENCY;
		f /= (lDutyCycle.ulHi + lDutyCycle.ulLo);
		return f;
	}
}

uint16_t uwDutyCycle_Get(uint8_t lubInputIndex)
{
	float32_t f;
	f = fDutyCycle_Get(lubInputIndex) * 1000;		// Convert to permille 0..1000
	return (uint16_t)f;
}

uint16_t uwFrequency_Get(uint8_t lubInputIndex)
{
	return (uint16_t)fFrequency_Get(lubInputIndex);
}

uint32_t ulDutyCycle_Edges_Get(uint8_t lubInputIndex)
{
	return mDutyCycle[lubInputIndex].ulEdges;
}

