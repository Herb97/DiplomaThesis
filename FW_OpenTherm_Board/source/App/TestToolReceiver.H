/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: TestToolReceiver.H
;
;******************************************************************************
; SVN header
;  $Id: TestToolReceiver.H 117605 2022-03-24 07:57:34Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void TestToolReceiver_ProcessByte(uint8_t lubReceivedByte);
bool bTestToolReceiver_Ready(void);
bool bTestToolReceiver_ProcessMessage(void);

#ifdef TestTool_H
void TestToolReceiver_DecodeFrame(TestToolMessage_t *pMessage);
#endif
