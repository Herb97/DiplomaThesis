/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-30           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Tick1ms.C
;
;******************************************************************************
; SVN header
;  $Id: Tick1ms.C 117724 2022-03-30 14:04:31Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include "Tick1ms.H"	// OWN header


//*****************************************************************************
// VARIABLE DEFINITION
//*****************************************************************************
static volatile uint32_t mulCounter = 0u;


/******************************************************************************
; Procedure		: ulTick1ms_Get()
; Description	: Returns real time in step of 1 ms.
; Input			: -
; Output		: real time in step of 1 ms.
;******************************************************************************/
uint32_t ulTick1ms_Get(void)
{
	return mulCounter;
}

/******************************************************************************
; Procedure		: Tick1ms_Tick()
; Description	: Call every 1 ms.
; Input			: -
; Output		: -
;******************************************************************************/
void Tick1ms_Tick(void)
{
	mulCounter++;
}

/******************************************************************************
; Procedure		: bTick1ms_Expired()
; Description	: Returns true if requested time elapsed.
; Input			: lulOrigin Poèáteèní èas v ticích.
; Input			: lulDelay Doba v ticích, kterou mìøíme.
; Output		: true/flase
;******************************************************************************/
bool bTick1ms_Expired(uint32_t lulOrigin, uint32_t lulDelay)
{
	uint32_t lulElapsed;
	uint32_t lulCurrent;
	
	lulCurrent = ulTick1ms_Get();
	lulElapsed = lulCurrent - lulOrigin;
	if (lulElapsed > lulDelay)
	{
		// requested time elapsed
		return true;
	}
	else
	{
		return false;
	}
}
