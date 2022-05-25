/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-09-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermReceiver.H
;
;******************************************************************************
; SVN header
;  $Id: OpenThermTransmitter.H 118393 2022-05-06 06:44:17Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; TYPEDEF
;*****************************************************************************/
typedef struct
{
  uint32_t	ulFrame;		// Transmitted frame
  uint16_t	uwTxCounter;
  bool		bTxPower;		// 0 = low power; 1 = medium and high power
  bool		bTxBit;
} OpenThermTransmitter_t;


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void OpenThermTransmitter_Init(OpenThermTransmitter_t *p);
bool bOpenThermTransmitter_HalfBitTime(OpenThermTransmitter_t *p);
void OpenThermTransmitter_Send(OpenThermTransmitter_t *p);
bool bOpenThermTransmitter_InProgress(OpenThermTransmitter_t * p);
bool bOpenThermTransmitter_Sending(OpenThermTransmitter_t * p);
//bool bOpenThermTransmitter_SendingStart(OpenThermTransmitter_t * p);
bool bOpenThermTransmitter_SendingDone(OpenThermTransmitter_t * p);
