/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-06-23           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: SystemTick.C
;
;******************************************************************************
; SVN header
;  $Id: SystemTick.C 108226 2020-06-23 15:39:49Z Stepanek, Michal $
******************************************************************************/

/*
	IN 6.5.2014
	- Pokud je doba èekání nulová, vrátíme, že timer dobìhl.
	IN 3.6.2009 14:50:10
	- Modul pro èítání systémové tiku s pøídavkem vyhodnocení ubìhnutého èasu.
*/

#include ".\SystemTick.H"

uint32_t mulCounter = 0;

/**
  * @brief Reading of system tick counter
  * @param None
  * @retval Counter
  *
  * Call regularly every ms.
  */
uint32_t SystemTick_Get(void)
{
	return mulCounter;
}

/**
  * @brief Tick
  * @param None
  * @retval None
  *
  * Call regularly every ms.
  */
void SystemTick_Tick(void)
{
	mulCounter++;
}

/**
  * @brief Update relays.
  * @param lulStart		Poèáteèní èas v ticích.
  * @param lulDelay		Doba v ticích, kterou mìøíme.
  * @retval TRUE		èas wait ubìhl od startTime.
  *
  * Called from main loop
  */
bool SystemTick_Expired(uint32_t lulStart, uint32_t lulDelay)
{
	return (((mulCounter - lulStart) > lulDelay) || (lulDelay == 0));
}
