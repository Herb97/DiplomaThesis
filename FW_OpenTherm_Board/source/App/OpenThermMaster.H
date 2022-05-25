/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-22           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermMaster.H
;
;******************************************************************************
; SVN header
;  $Id: OpenThermMaster.H 118384 2022-05-05 13:54:05Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void OpenThermMaster_Init(void);
void OpenThermMaster_100us(uint16_t luwTimeStamp, bool lbCurrent);
bool bOpenThermMaster_HalfBitTime(void);

#ifdef TestTool_H
void OpenThermMaster_MainLoop(TestToolMessage_t * p);
#endif

