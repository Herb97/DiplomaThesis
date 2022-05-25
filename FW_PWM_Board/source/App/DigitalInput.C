/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-04-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: DigitalInput.C
;


/*
Processing of digital inputs.
*/

#include ".\HalfWaveFilter.H"				// uwHalfWaveFilter_Filter()
#include ".\DigitalInput.H"					// OWN header

/******************************************************************************
; VARIABLE DEFINITION
;******************************************************************************/

static uint16_t muwDigitalInput_RawData = 0;
static uint16_t muwDigitalInput_FilteredData = 0;
static uint16_t muwDigitalInput_Polarity = 0;


//=======================================================================================================================================================
//				Public methods
//=======================================================================================================================================================

/**
  * @brief Refresh of filtered and non-filtered data
  * @param luwRawInput
  * @retval None
  *
  * Called from main loop every 1 ms.
  */
void DigitalInput_Every1ms(uint16_t luwRawInput)
{
	muwDigitalInput_RawData = luwRawInput;
	muwDigitalInput_FilteredData = uwHalfWaveFilter_Filter(luwRawInput);
}

/**
  * @brief Reading of inverted state of input pins via MODBUS
  * @param None
  * @retval x
  *
  * Called from MODBUS
  */

uint16_t uwDigitalInput_RawData_Get(void)
{
	return muwDigitalInput_RawData ^ muwDigitalInput_Polarity;
}

/**
  * @brief Reading of inverted filtered state of input pins via MODBUS
  * @param None
  * @retval x
  *
  * Called from MODBUS
  */

uint16_t uwDigitalInput_FilteredData_Get(void)
{
	return muwDigitalInput_FilteredData ^ muwDigitalInput_Polarity;
}

/**
  * @brief Reading of inverted state
  * @param None
  * @retval x
  *
  * Called from MODBUS
  */
uint16_t uwDigitalInput_Polarity_Get(void)
{
	return muwDigitalInput_Polarity;
}

/**
  * @brief Set of inverted state of input pins
  * @param None
  * @retval true
  *
  * Called from MODBUS
  */
bool bDigitalInput_Polarity_Set(uint16_t luwPolarity)
{
	muwDigitalInput_Polarity = luwPolarity;
	return true;
}

