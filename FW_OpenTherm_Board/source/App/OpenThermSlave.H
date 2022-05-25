/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-22           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermSlave.H
;
;******************************************************************************
; SVN header
;  $Id: OpenThermSlave.H 118384 2022-05-05 13:54:05Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void OpenThermSlave_Init(void);
void ResponseTime_Set(uint16_t f);
void OpenThermSlave_Transmit_StateMachine(void);
void OpenThermSlave_Transmit_Trigger(uint32_t lulMessage, uint16_t luwDelay);
void OpenThermSlave_100us(uint16_t luwTimeStamp, bool lbVoltage);
bool bOpenThermSlave_HalfBitTime(void);


#ifdef TestTool_H
void OpenThermSlave_MainLoop(TestToolMessage_t * p);
#endif
