/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-09-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermMonitor.C
;
*/

/*
LEDs:
	R - wrong polarity, see Polarity.C
	G - Voltage - communication from master/thermostat to slave/controller
	B - interrupt duration
	Y - Current - communication from slave/controller to master/thermostat
	
*/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include "..\App\TestTool.H"
#include "..\App\Counter.H"						// uwCounter_SerialData_GetAndClear(), uwCounter_ResponseTime_Get(), uwCounter_TimeStamp_GetAndClear(), Counter_ResponseTime_Clear()
#include "..\Hal\Led.H"							// LED_...
#include "..\Mod\OpenThermReceiver.H"			// bOpenThermReceiver_IsReady(), OpenThermReceiver_Free(), ulOpenThermReceiver_Frame_Get(), bOpenThermReceiver_CheckParity(), bOpenThermReceiver_InProgress()
#include ".\OpenThermMonitor.H"					// OWN header


//*****************************************************************************
// VARIABLE DEFINITION
//*****************************************************************************
OpenThermReceiver_t msMonitor_ReceiverCurrent;
OpenThermReceiver_t msMonitor_ReceiverVoltage;
bool mbMonitor_HistoricalCurrent;
bool mbMonitor_HistoricalVoltage;
	
uint16_t muwMonitor_TimeStamp;
uint16_t muwMonitor_ResponseTime;
uint16_t muwMonitor_SerialDataTime;
uint16_t muwMonitor_MidBitInfo;

/******************************************************************************
; Procedure     : OpenThermMonitor_Init()
; Description   : 
; Input         : -
; Output        : -
;*****************************************************************************/
void OpenThermMonitor_Init(void)
{
	OpenThermReceiver_Free(&msMonitor_ReceiverCurrent);
	OpenThermReceiver_Free(&msMonitor_ReceiverVoltage);
	LED_MONITOR_G_OFF;
	LED_MONITOR_Y_OFF;
}

/******************************************************************************
; Procedure     : OpenThermMonitor_MainLoop()
; Description   : Call in case of TESTTOOL_MODE_MONITOR
; Input         : p - received message from PC; p->ubLength is zero if no message received
; Output        : p - message to transmit; p->ubLength is zero if no message to be transmitted
;*****************************************************************************/
void OpenThermMonitor_MainLoop(TestToolMessage_t * p)
{
	uint32_t lulFrame;
	
	// Current - communication from slave/controller to master/thermostat
	if (bOpenThermReceiver_IsReady(&msMonitor_ReceiverCurrent))
	{
		// we have a Frame
		// Read the frame
		lulFrame = ulOpenThermReceiver_Frame_Get(&msMonitor_ReceiverCurrent);
		// Free the receiver
		OpenThermReceiver_Free(&msMonitor_ReceiverCurrent);
		// send received data to UART
		p->ubMode			=TESTTOOL_MODE_MONITOR_RECEIVED_MESSAGE;
		p->ubPort			=TESTTOOL_PORT_MESSAGE_FROM_SLAVE_IDLE_LOW;
		p->uwTimeStamp		=uwCounter_SerialData_GetAndClear();
		p->ulMessage		=lulFrame;
		p->ubMidbitInfo		=muwMonitor_MidBitInfo;
		p->uwResponseTime	=muwMonitor_ResponseTime;
		p->ubLength			=TESTTOOL_FRAME_SIZE;	// whole frame
	}
	
	// Voltage - communication from master/thermostat to slave/controller
	else if (bOpenThermReceiver_IsReady(&msMonitor_ReceiverVoltage))
	{
		// we have a Frame
		lulFrame = ulOpenThermReceiver_Frame_Get(&msMonitor_ReceiverVoltage);
		OpenThermReceiver_Free(&msMonitor_ReceiverVoltage);
		// send received data to UART
		p->ubMode			=TESTTOOL_MODE_MONITOR_RECEIVED_MESSAGE;
		p->ubPort			=TESTTOOL_PORT_MESSAGE_FROM_MASTER_IDLE_LOW;
		p->uwTimeStamp		=muwMonitor_TimeStamp;
		p->ulMessage		=lulFrame;
		p->ubMidbitInfo		=muwMonitor_MidBitInfo;
		p->uwResponseTime	=0u;
		p->ubLength			=TESTTOOL_FRAME_SIZE;	// whole frame
	}
	else
	{
		p->ubLength = 0u;	// Nothing to send
	}
}

/******************************************************************************
; Procedure     : OpenThermMonitor_100us()
; Description   : 100us interrupt
; Input         : luwTimeStamp - 1 us time stamp for measuring OpenTherm edge to edge time
; Input         : lbCurrent - 0/1 - communication from slave/controller to master/thermostat
; Input         : lbVoltage - 0/1 - communication from master/thermostat to slave/controller
; Output        : -
;*****************************************************************************/
void OpenThermMonitor_100us(uint16_t luwTimeStamp, bool lbCurrentMonitor, bool lbVoltageMonitor)
{
	LED_MONITOR_B_ON;
	
	// Current - communication from slave/controller to master/thermostat
	{
		// Edge detector
		if (mbMonitor_HistoricalCurrent != lbCurrentMonitor)
		{
			// edge detected
			mbMonitor_HistoricalCurrent = lbCurrentMonitor;
			uint8_t lubMonitorCurrent_StateBefore = msMonitor_ReceiverCurrent.ubState;
			OpenThermReceiver_PinChange(&msMonitor_ReceiverCurrent, luwTimeStamp);
			uint8_t lubMonitorCurrent_StateAfter = msMonitor_ReceiverCurrent.ubState;
			if ((lubMonitorCurrent_StateBefore == 1u) && (lubMonitorCurrent_StateAfter == 2u))
			{
				muwMonitor_ResponseTime = uwCounter_ResponseTime_Get();
			}
			else if (lubMonitorCurrent_StateAfter >= 68u)
			{
				uint32_t lulFrame = ulOpenThermReceiver_Frame_Get(&msMonitor_ReceiverCurrent);
				if (bOpenThermReceiver_CheckParity(lulFrame))
				{
					muwMonitor_MidBitInfo = 0x22u;
				}
				else
				{
					muwMonitor_MidBitInfo = 0u;
				}
			}
			else 
			{}
		}
		// Tick - to detect timeout
		OpenThermReceiver_100us(&msMonitor_ReceiverCurrent);
		// LED handling
		if (bOpenThermReceiver_InProgress(&msMonitor_ReceiverCurrent))
		{
			LED_MONITOR_Y_ON;
		}
		else
		{
			LED_MONITOR_Y_OFF;
		}
	}
	
	// Voltage - communication from master/thermostat to slave/controller
	{	
		// Edge detector
		if (mbMonitor_HistoricalVoltage != lbVoltageMonitor)
		{
			// edge detected
			mbMonitor_HistoricalVoltage = lbVoltageMonitor;
			uint8_t lubMonitorVoltage_StateBefore = msMonitor_ReceiverVoltage.ubState;
			OpenThermReceiver_PinChange(&msMonitor_ReceiverVoltage, luwTimeStamp);
			uint8_t lubMonitorVoltage_StateAfter = msMonitor_ReceiverVoltage.ubState;
			if ((lubMonitorVoltage_StateBefore == 1u) && (lubMonitorVoltage_StateAfter == 2u))
			{
				muwMonitor_TimeStamp = uwCounter_TimeStamp_GetAndClear();
			}
			else if (lubMonitorVoltage_StateAfter >= 68u)
			{
				Counter_ResponseTime_Clear();
				uint32_t lulFrame = ulOpenThermReceiver_Frame_Get(&msMonitor_ReceiverVoltage);
				if (bOpenThermReceiver_CheckParity(lulFrame))
				{
					muwMonitor_MidBitInfo = 0x22u;
				}
				else
				{
					muwMonitor_MidBitInfo = 0u;
				}
			}
			else 
			{}
		}
		OpenThermReceiver_100us(&msMonitor_ReceiverVoltage);
		
		if (bOpenThermReceiver_InProgress(&msMonitor_ReceiverVoltage))
		{
			LED_MONITOR_G_ON;
		}
		else
		{
			LED_MONITOR_G_OFF;
		}
	}
	
	LED_MONITOR_B_OFF;
}