/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-05           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: HalfWaveFilter.C
;


/*
Filtering of Half wave rectified 50 / 60 Hz signal.
Filter calculates its result from last 20 samples, sample time 1ms.
*/

#include ".\HalfWaveFilter.H"					// OWN header

/******************************************************************************
; VARIABLE DEFINITION
;******************************************************************************/

static uint32_t mulFilter[NUMBER_OF_INPUTS];

#define FILTER_LEN		20		// calculate filter result from last 20 samples, sample time 1ms

//=======================================================================================================================================================
//				Local methods
//=======================================================================================================================================================

/**
  * @brief Insert raw data to filter buffer.
  * @param mulFilter, luwRawData
  * @retval mulFilter
  */
static void Filter_Insert(uint16_t luwRawData)
{
	for(uint8_t i=0; i<NUMBER_OF_INPUTS; i++)
	{
		mulFilter[i] <<= 1;
		mulFilter[i] |= luwRawData&BIT0;
		luwRawData >>= 1;
	}
}

/**
  * @brief Calculate filter result for one digital input.
  * @param lulBuffer
  * @retval 0 or 1
  * 
  * In comapring with number 4 is showed filter. Value 4 was chosed by oscilloscope measurement to make 50 Hz and 60 Hz filter.
  */
static bool bFilter_One(uint32_t lulBuffer)
{
	uint8_t lubOnes = 0;
	for(uint8_t i=0; i<FILTER_LEN; i++)
	{
		if (lulBuffer&1)
		{
			lubOnes++;
		}
		lulBuffer>>=1;
	}
	return (lubOnes >= 4) ? 1 : 0;
}

/**
  * @brief Filtering of all 16 digital inputs
  * @param mulFilter[]
  * @retval filtered data
  */
static uint16_t uwFilter_All(void)
{
	uint16_t luwResult = 0;
	uint16_t luwMask = 1;
	
	for(uint8_t i=0; i<NUMBER_OF_INPUTS; i++)
	{
		if (bFilter_One(mulFilter[i]))
		{
			luwResult |= luwMask;
		}
		luwMask <<= 1;
	}
	return luwResult;
}

//=======================================================================================================================================================
//				Public methods
//=======================================================================================================================================================

/**
  * @brief Refresh of filtered and non-filtered data
  * @param luwRawInput
  * @retval Filtered data
  *
  * Call every 1 ms.
  */
uint16_t uwHalfWaveFilter_Filter(uint16_t luwRawInput)
{
	Filter_Insert(luwRawInput);
	return uwFilter_All();
}

