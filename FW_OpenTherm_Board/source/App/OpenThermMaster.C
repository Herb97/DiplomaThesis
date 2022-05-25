/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-22           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermMaster.C
;
*/

/*
Master (thermostat), schematic page 5
*/

/*
LEDs:
	R - wrong polarity, see Polarity.C
	G - Voltage - communication from master/thermostat to slave/controller
	B - interrupt duration
	Y - Current - communication from slave/controller to master/thermostat
	
*/

//*****************************************************************************
// INCLUDE FILES
//*****************************************************************************
#include "..\App\TestTool.H"
#include "..\App\Counter.H"						// uwCounter_ResponseTime_Get(), uwCounter_TimeStamp_GetAndClear(), Counter_ResponseTime_Clear()
#include "..\Hal\Led.H"							// LED_...
#include "..\Mod\Tick1ms.H"						// ulTick1ms_Get(), bTick1ms_Expired()
#include "..\Mod\OpenThermReceiver.H"			// bOpenThermReceiver_IsReady(), OpenThermReceiver_Free(), ulOpenThermReceiver_Frame_Get(), bOpenThermReceiver_CheckParity(), bOpenThermReceiver_InProgress()
#include "..\Mod\OpenThermTransmitter.H"		// OpenThermTransmitter_500us()
#include ".\OpenThermMaster.H"					// OWN header


//*****************************************************************************
// VARIABLE DEFINITION
//*****************************************************************************
OpenThermReceiver_t msMaster_ReceiverCurrent;
OpenThermTransmitter_t  msMaster_TransmitterVoltage;
bool mbMaster_HistoricalCurrent;
bool mbMaster_Sending = 0u;
bool mbMasterTestTool_Response = true;

uint16_t muwMaster_TimeStamp;
uint16_t muwMaster_ResponseTime;
//uint16_t muwMaster_SerialDataTime;
uint16_t muwMaster_MidBitInfo;

uint32_t mulTransmitOrigin = 0u;	// transmit time origin in step of 1 ms.
uint16_t muwTransmitDelay = 0u;		// Delay from trasmit to transmit, zero in idle
uint32_t mulMessageToBeSend;


/******************************************************************************
; Procedure     : OpenThermMaster_Init()
; Description   : 
; Input         : -
; Output        : -
;*****************************************************************************/
void OpenThermMaster_Init(void)
{
	muwTransmitDelay = 0u;		// idle
	OpenThermReceiver_Free(&msMaster_ReceiverCurrent);
	OpenThermTransmitter_Init(&msMaster_TransmitterVoltage);
	LED_MASTER_G_OFF;
	LED_MASTER_Y_OFF;
}


/******************************************************************************
; Procedure     : OpenThermMaster_Transmit_StateMachine()
; Description   : It sends massages to OpenTherm regularly if muwTransmitDelay is set
; Input         : -
; Output        : -
;*****************************************************************************/
void OpenThermMaster_Transmit_StateMachine(void)
{
	if (muwTransmitDelay)
	{
		// there is a message to be transmitted
		if (false == bOpenThermTransmitter_InProgress(&msMaster_TransmitterVoltage))
		{
			// OpenTherm transmitter is available
			if (bTick1ms_Expired(mulTransmitOrigin, muwTransmitDelay))
			{
				// Delay from trasmit to transmit expired
				mulTransmitOrigin = ulTick1ms_Get();		// mark new origin
				msMaster_TransmitterVoltage.ulFrame = mulMessageToBeSend;
				OpenThermTransmitter_Send(&msMaster_TransmitterVoltage);	// transmit packet
			}
		}
	}
}


/******************************************************************************
; Procedure     : OpenThermMaster_Transmit_Trigger()
; Description   : 
; Input         : lulMessage - OpenTherm message to send
; Input         : luwDelay
; Output        : -
;*****************************************************************************/
void OpenThermMaster_Transmit_Trigger(uint32_t lulMessage, uint16_t luwDelay)
{
	if (0u == muwTransmitDelay)
	{
		mulTransmitOrigin = ulTick1ms_Get();		// mark new origin
	}
	mulMessageToBeSend = lulMessage;
	muwTransmitDelay = luwDelay;
}


/******************************************************************************
; Procedure     : OpenThermMaster_MainLoop()
; Description   : Call in case of TESTTOOL_MODE_MASTER
; Input         : p - received message from PC; p->ubLength is zero if no message received
; Output        : p - message to transmit; p->ubLength is zero if no message to be transmitted
;*****************************************************************************/
void OpenThermMaster_MainLoop(TestToolMessage_t * p)
{
	OpenThermMaster_Transmit_StateMachine();
	if (TESTTOOL_FRAME_SIZE == p->ubLength)
	{
		OpenThermMaster_Transmit_Trigger(p->ulMessage, p->uwResponseTime);
		// send ACK
		p->ubMode = TESTTOOL_MODE_ACKNOWLEDGE_MASTER;
		mbMasterTestTool_Response = false;
	}
	else if (0u == p->ubLength)
	{
		if (mbMaster_Sending)
		{
			p->ubMode = TESTTOOL_MODE_ACKNOWLEDGE_CONTROL_IS_STILL_LIVE;	// E
			p->ubPort = TESTTOOL_PORT_MASTER_SLAVE_MESSAGE_SEND_BY_CONTROL;	// E
			p->uwTimeStamp = 99u;	
			p->ubLength = TESTTOOL_SIZE_MODE_PORT_TIMESTAMP;
			mbMaster_Sending = false;
		}
		else if (bOpenThermReceiver_IsReady(&msMaster_ReceiverCurrent))
		{
			// we have a Frame
			// Read the frame
			uint32_t lulFrame = ulOpenThermReceiver_Frame_Get(&msMaster_ReceiverCurrent);
			// Free the receiver
			OpenThermReceiver_Free(&msMaster_ReceiverCurrent);
			// send received data to UART
			p->ubMode			=TESTTOOL_MODE_MASTER_RECEIVED_MESSAGE;
			p->ubPort			=TESTTOOL_PORT_MESSAGE_FROM_SLAVE_IDLE_LOW;
			p->uwTimeStamp		=muwMaster_TimeStamp; 
			p->ulMessage		=lulFrame;
			p->ubMidbitInfo		=muwMaster_MidBitInfo; 
			p->uwResponseTime	=muwMaster_ResponseTime; 
			p->ubLength			=TESTTOOL_FRAME_SIZE;	// whole frame
		}
		else if (!mbMasterTestTool_Response)
		{
			p->ubMode			=TESTTOOL_MODE_ACKNOWLEDGE_MASTER;
			p->ubPort			=TESTTOOL_PORT_MESSAGE_FROM_SLAVE_IDLE_LOW;
			p->uwTimeStamp		=muwMaster_TimeStamp;
			p->ubMidbitInfo		=0u;
			p->ubLength			=TESTTOOL_FRAME_SIZE;	// whole frame
			mbMasterTestTool_Response = true;
		}
		else
		{
			p->ubLength = 0u;	// Nothing to send
		}
	}
	else
	{
		p->ubLength = 0u;	// Nothing to send
	}
}


/******************************************************************************
; Procedure     : OpenThermMaster_100us()
; Description   : Receiver 100us interrupt;
; Input         : luwTimeStamp - 1 us time stamp for measuring OpenTherm edge to edge time
; Input         : lbCurrent - 0/1 - communication from slave/controller to master/thermostat
; Input         : lbVoltage - 0/1
; Output        : -
;*****************************************************************************/
void OpenThermMaster_100us(uint16_t luwTimeStamp, bool lbCurrent)
{
	
	LED_MASTER_B_ON;
	// Current - communication from slave/controller to master/thermostat
	{
		// Edge detector
		if (mbMaster_HistoricalCurrent != lbCurrent)
		{
			// edge detected
			mbMaster_HistoricalCurrent = lbCurrent;
			uint8_t lubMasterCurrent_StateBefore = msMaster_ReceiverCurrent.ubState;
			OpenThermReceiver_PinChange(&msMaster_ReceiverCurrent, luwTimeStamp);
			uint8_t lubMasterCurrent_StateAfter = msMaster_ReceiverCurrent.ubState;
			if ((lubMasterCurrent_StateBefore == 1u) && (lubMasterCurrent_StateAfter == 2u))
			{
				muwMaster_ResponseTime = uwCounter_ResponseTime_Get();
			}
			else if (lubMasterCurrent_StateAfter >= 68u)
			{
				uint32_t lulFrame = ulOpenThermReceiver_Frame_Get(&msMaster_ReceiverCurrent);
				if (bOpenThermReceiver_CheckParity(lulFrame))
				{
					muwMaster_MidBitInfo = 0x22u;
				}
				else
				{
					muwMaster_MidBitInfo = 0u;
				}
			}
			else 
			{}
		}
		// Tick - to detect timeout
		OpenThermReceiver_100us(&msMaster_ReceiverCurrent);
		// LED handling
		if (bOpenThermReceiver_InProgress(&msMaster_ReceiverCurrent))
		{
			LED_MASTER_Y_ON;
		}
		else
		{
			LED_MASTER_Y_OFF;
		}
	}

	LED_MASTER_B_OFF;
}


/******************************************************************************
; Procedure     : bOpenThermMaster_HalfBitTime()
; Description   : Transmitter HalfBitTime (500 us) interrupt; Voltage - communication from master/thermostat to slave/controller
; Input         : -
; Output        : 0/1
;*****************************************************************************/
bool bOpenThermMaster_HalfBitTime(void)
{
	if (bOpenThermTransmitter_InProgress(&msMaster_TransmitterVoltage))
	{
		LED_MASTER_G_ON;
	}
	else
	{
		LED_MASTER_G_OFF;
	}
	// transmitting is done
	if (bOpenThermTransmitter_SendingDone(&msMaster_TransmitterVoltage))
	{
		muwMaster_TimeStamp = uwCounter_TimeStamp_GetAndClear();
		Counter_ResponseTime_Clear();
	}
	// transmitting started
	if (bOpenThermTransmitter_Sending(&msMaster_TransmitterVoltage))
	{
		mbMaster_Sending = true;	// inform PC about sending	
	}
	return bOpenThermTransmitter_HalfBitTime(&msMaster_TransmitterVoltage);
}

