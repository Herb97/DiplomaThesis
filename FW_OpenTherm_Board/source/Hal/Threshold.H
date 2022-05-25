/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-04-01           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Threshold.H
;
;******************************************************************************
; SVN header
;  $Id: Threshold.H 117763 2022-03-31 16:17:16Z Herbrych, Vojtech $
******************************************************************************/


/******************************************************************************
; TYPEDEF
;*****************************************************************************/
typedef enum
{
	MASTER_CURRENT_THRESHOLD	,
	MONITOR_CURRENT_THRESHOLD	,
	SLAVE_CURRENT_LOW			,
	SLAVE_CURRENT_HIGH			,
	MASTER_VOLTAGE_LOW			,
	MASTER_VOLTAGE_HIGH			,
	MONITOR_VOLTAGE_THRESHOLD	,
	SLAVE_VOLTAGE_THRESHOLD		,
} Level_Index_t;

#define LEVEL_COUNT 8u

/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void Level_Init(void);

bool bLevel_Set(float32_t f, Level_Index_t lubIndex);
uint16_t uwLevel_Get(Level_Index_t lubIndex);
float32_t fLevel_Get(Level_Index_t lubIndex);
