/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-22           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermMonitor.H
;
;******************************************************************************
; SVN header
;  $Id: OpenThermMonitor.H 118384 2022-05-05 13:54:05Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void OpenThermMonitor_Init(void);
void OpenThermMonitor_100us(uint16_t luwTimeStamp, bool lbCurrentMonitor, bool lbVoltageMonitor);

#ifdef TestTool_H
void OpenThermMonitor_MainLoop(TestToolMessage_t * p);
#endif

