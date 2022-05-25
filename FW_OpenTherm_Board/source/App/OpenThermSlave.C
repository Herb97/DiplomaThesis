/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-22           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermSlave.C
;
*/

/*
Slave (gas boiler), schematic page 4
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
#include "..\App\Counter.H"						// uwCounter_ResponseTime_Get(), uwCounter_TimeStamp_GetAndClear(), Counter_ResponseTime_Clear()
#include "..\Hal\Led.H"							// LED_...
#include "..\Mod\OpenThermReceiver.H"			// bOpenThermReceiver_IsReady(), OpenThermReceiver_Free(), ulOpenThermReceiver_Frame_Get(), bOpenThermReceiver_CheckParity(), bOpenThermReceiver_InProgress()
#include "..\Mod\OpenThermTransmitter.H"		// OpenThermTransmitter_HalfBitTime()
#include "..\Mod\Tick1ms.H"						// ulTick1ms_Get(), bTick1ms_Expired()
#include ".\OpenThermSlave.H"					// OWN header


//*****************************************************************************
// VARIABLE DEFINITION
//*****************************************************************************
OpenThermReceiver_t msSlave_ReceiverVoltage;
OpenThermTransmitter_t  msSlave_TransmitterCurrent;
bool mbSlave_HistoricalVoltage;
bool mbSlave_Sending = false;
bool mbSlaveTestTool_Response = true;
bool mbSlaveTestTool_MessageDone = false;

uint16_t muwSlave_TimeStamp;
uint16_t muwSlave_ResponseTime = 0u;
//uint16_t muwSlave_SerialDataTime;
uint16_t muwSlave_MidBitInfo;

uint32_t mulSlave_TransmitOrigin = 0u;	// transmit time origin in step of 1 ms.
uint16_t muwSlave_TransmitDelay = 0u;		// Delay from trasmit to transmit, zero in idle
uint32_t mulSlave_MessageToBeSend;


/******************************************************************************
; Procedure     : OpenThermSlave_Init()
; Description   : 
; Input         : -
; Output        : -
;*****************************************************************************/
void OpenThermSlave_Init(void)
{
	OpenThermReceiver_Free(&msSlave_ReceiverVoltage);
	OpenThermTransmitter_Init(&msSlave_TransmitterCurrent);
	LED_SLAVE_G_OFF;
	LED_SLAVE_Y_OFF;
}


/******************************************************************************
; Procedure     : ResponseTime_Set()
; Description   : 
; Input         : 
; Output        : -
;*****************************************************************************/
void ResponseTime_Set(uint16_t f)
{
	muwSlave_ResponseTime = f;
}


/******************************************************************************
; Procedure     : OpenThermSlave_Transmit_StateMachine()
; Description   : It sends massages to OpenTherm regularly if muwTransmitDelay is set
; Input         : -
; Output        : -
;*****************************************************************************/
void OpenThermSlave_Transmit_StateMachine(void)
{
	if (muwSlave_TransmitDelay)
	{
		// there is a message to be transmitted
		if (false == bOpenThermTransmitter_InProgress(&msSlave_TransmitterCurrent))
		{
			// OpenTherm transmitter is available
			if (bTick1ms_Expired(mulSlave_TransmitOrigin, muwSlave_TransmitDelay))
			{
				// Delay from trasmit to transmit expired
				mulSlave_TransmitOrigin = ulTick1ms_Get();		// mark new origin
				msSlave_TransmitterCurrent.ulFrame = mulSlave_MessageToBeSend;
				OpenThermTransmitter_Send(&msSlave_TransmitterCurrent);	// transmit packet
				muwSlave_TransmitDelay = 0u; // packet is transmitted, waiting for next request
			}
		}
	}
}


/******************************************************************************
; Procedure     : OpenThermSlave_Transmit_Trigger()
; Description   : 
; Input         : lulMessage - OpenTherm message to send
; Input         : luwDelay
; Output        : -
;*****************************************************************************/
void OpenThermSlave_Transmit_Trigger(uint32_t lulMessage, uint16_t luwDelay)
{
	if (0u == muwSlave_TransmitDelay)
	{
		mulSlave_TransmitOrigin = ulTick1ms_Get();		// mark new origin
	}
	mulSlave_MessageToBeSend = lulMessage;
	muwSlave_TransmitDelay = luwDelay;
}


/******************************************************************************
; Procedure     : OpenThermSlave_MainLoop()
; Description   : Call in case of TESTTOOL_MODE_SLAVE
; Input         : p - received message from PC; p->ubLength is zero if no message received
; Output        : p - message to transmit; p->ubLength is zero if no message to be transmitted
;*****************************************************************************/
void OpenThermSlave_MainLoop(TestToolMessage_t * p)
{
	OpenThermSlave_Transmit_StateMachine();
	if (TESTTOOL_FRAME_SIZE == p->ubLength)
	{
		OpenThermSlave_Transmit_Trigger(p->ulMessage, p->uwResponseTime);
		// send ACK
		p->ubMode = TESTTOOL_MODE_ACKNOWLEDGE_SLAVE;
		mbSlaveTestTool_Response = false;
	}
	else if (0u == p->ubLength)
	{
		if (mbSlave_Sending)
		{
			p->ubMode = TESTTOOL_MODE_ACKNOWLEDGE_CONTROL_IS_STILL_LIVE;	// E
			p->ubPort = TESTTOOL_PORT_MASTER_SLAVE_MESSAGE_SEND_BY_CONTROL;	// E
			p->uwTimeStamp = 0x010B;	
			p->ubLength = TESTTOOL_SIZE_MODE_PORT_TIMESTAMP;
			mbSlave_Sending = false;
		}
		else if (bOpenThermReceiver_IsReady(&msSlave_ReceiverVoltage))
		{
			// we have a Frame
			// Read the frame
			uint32_t lulFrame = ulOpenThermReceiver_Frame_Get(&msSlave_ReceiverVoltage);
			// Free the receiver
			OpenThermReceiver_Free(&msSlave_ReceiverVoltage);
			// send received data to UART
			p->ubMode			=TESTTOOL_MODE_SLAVE_RECEIVED_MESSAGE;
			p->ubPort			=TESTTOOL_PORT_MESSAGE_FROM_MASTER_IDLE_LOW;
			p->uwTimeStamp		=muwSlave_TimeStamp;
			p->ulMessage		=lulFrame;
			p->ubMidbitInfo		=muwSlave_MidBitInfo;
			p->uwResponseTime	=0u;
			p->ubLength			=TESTTOOL_FRAME_SIZE;	// whole frame
			mbSlaveTestTool_MessageDone = true;
		}
		else if (mbSlaveTestTool_MessageDone)
		{

			p->ubMode			=TESTTOOL_MODE_ACKNOWLEDGE_SLAVE;
			p->ubLength			=TESTTOOL_FRAME_SIZE;	// whole frame
			mbSlaveTestTool_MessageDone = false;
			mbSlaveTestTool_Response = false;
		}
		else if (!mbSlaveTestTool_Response)
		{
			p->ubMode			=TESTTOOL_MODE_ACKNOWLEDGE_SLAVE;
			p->ubPort			=TESTTOOL_PORT_MESSAGE_FROM_MASTER_IDLE_LOW;
			p->uwTimeStamp		=muwSlave_TimeStamp;
			p->ubMidbitInfo		=0u;
			p->ubLength			=TESTTOOL_FRAME_SIZE;	// whole frame
			mbSlaveTestTool_Response = true;
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
; Procedure     : OpenThermSlave_100us()
; Description   : Receiver 100us interrupt
; Input         : luwTimeStamp - 1 us time stamp for measuring OpenTherm edge to edge time
; Input         : lbCurrent - 0/1
; Input         : lbVoltage - 0/1 - communication from master/thermostat to slave/controller
; Output        : -
;*****************************************************************************/
void OpenThermSlave_100us(uint16_t luwTimeStamp, bool lbVoltage)
{
	LED_SLAVE_B_ON;
	
	// Voltage - communication from master/thermostat to slave/controller
	{	
		
		if (mbSlave_HistoricalVoltage != lbVoltage)
		{
			// edge detected
			mbSlave_HistoricalVoltage = lbVoltage;
			uint8_t lubSlaveVoltage_StateBefore = msSlave_ReceiverVoltage.ubState;
			OpenThermReceiver_PinChange(&msSlave_ReceiverVoltage, luwTimeStamp);
			uint8_t lubSlaveVoltage_StateAfter = msSlave_ReceiverVoltage.ubState;
			if ((lubSlaveVoltage_StateBefore == 0u) && (lubSlaveVoltage_StateAfter == 1u))
			{
				muwSlave_TimeStamp = uwCounter_TimeStamp_GetAndClear();
			}
			else if (lubSlaveVoltage_StateAfter >= 68u)
			{
				muwSlave_ResponseTime = uwCounter_ResponseTime_Get();
				uint32_t lulFrame = ulOpenThermReceiver_Frame_Get(&msSlave_ReceiverVoltage);
				if (bOpenThermReceiver_CheckParity(lulFrame))
				{
					muwSlave_MidBitInfo = 0x22u;
				}
				else
				{
					muwSlave_MidBitInfo = 0u;
				}
			}
			else 
			{}
		}
		OpenThermReceiver_100us(&msSlave_ReceiverVoltage);
		
		if (bOpenThermReceiver_InProgress(&msSlave_ReceiverVoltage))
		{
			LED_SLAVE_G_ON;
		}
		else
		{
			LED_SLAVE_G_OFF;
		}
	}

	LED_SLAVE_B_OFF;
}


/******************************************************************************
; Procedure     : bOpenThermMaster_HalfBitTime()
; Description   : Transmitter HalfBitTime (500 us) interrupt; Current - communication from slave/controller to master/thermostat
; Input         : -
; Output        : 0/1
;*****************************************************************************/
bool bOpenThermSlave_HalfBitTime(void)
{
	if (bOpenThermTransmitter_InProgress(&msSlave_TransmitterCurrent))
	{
		LED_SLAVE_Y_ON;
	}
	else
	{
		LED_SLAVE_Y_OFF;
	}
	// transmitting start
	if (bOpenThermTransmitter_SendingDone(&msSlave_TransmitterCurrent))
	{
		//muwMaster_TimeStamp = uwCounter_TimeStamp_GetAndClear();
		Counter_ResponseTime_Clear(); 
	}
	if (bOpenThermTransmitter_Sending(&msSlave_TransmitterCurrent))
	{
		mbSlave_Sending = true;	// inform PC about sending
	}
	return bOpenThermTransmitter_HalfBitTime(&msSlave_TransmitterCurrent);
}

