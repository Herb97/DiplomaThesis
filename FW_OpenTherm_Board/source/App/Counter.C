/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-05-06           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Counter.C
;
*/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include ".\Counter.H"						// OWN header


//*****************************************************************************
// VARIABLE DEFINITION
//*****************************************************************************
static volatile uint16_t muwTimeStampCounter_100us = 0u;
static volatile uint16_t muwResponseTimeCounter_100us = 0u;
static volatile uint16_t muwSerialDataTimeCounter_100us = 0u;


/**
  * @brief 100 us timer
  * @param None
  * @retval None
**/
void Counter_100us(void)
{
	muwTimeStampCounter_100us++;
	muwResponseTimeCounter_100us++;
	muwSerialDataTimeCounter_100us++;
}


/*uint16_t TimeStampCounter_Get(void)
{
	return (muwTimeStampCounter_100us/5u);
}*/


/**
  * @brief Clearing TimeStamp counter
  * @param None
  * @retval None
**/
/*void uTimeStampCounter_Clear(void)
{
	muwTimeStampCounter_100us = 0u;
}*/


/**
  * @brief 
  * @param None
  * @retval Resolution 500 us
**/
uint16_t uwCounter_TimeStamp_GetAndClear(void)
{
	uint16_t x = muwTimeStampCounter_100us;
	muwTimeStampCounter_100us = 0u;
	return x/5u;
}


/**
  * @brief Clearing ResponseTime counter
  * @param None
  * @retval Resolution 500 us
**/
uint16_t uwCounter_ResponseTime_Get(void)
{
	return (muwResponseTimeCounter_100us/5u);
}


/**
  * @brief 
  * @param None
  * @retval None
**/
void Counter_ResponseTime_Clear(void)
{
	muwResponseTimeCounter_100us = 0u;
}


/**
  * @brief 
  * @param None
  * @retval Resolution 500 us
**/
uint16_t uwCounter_SerialData_GetAndClear(void)
{
	uint16_t x = muwSerialDataTimeCounter_100us;
	muwSerialDataTimeCounter_100us = 0u;
	return x/5u;
}

