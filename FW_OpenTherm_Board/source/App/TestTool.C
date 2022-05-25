/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-09-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: TestTool.C
;
*/

#include ".\TestTool.H"						// OWN header
#include "..\Common\Mod\Ascii\Ascii.H"		// ubAsciiFromNibble()
#include "..\App\OpenThermMonitor.H"		// OpenThermMonitor_Init(), OpenThermMonitor_MainLoop()
#include "..\App\OpenThermMaster.H"			// OpenThermMaster_Init(), OpenThermMaster_MainLoop()
#include "..\App\OpenThermSlave.H"			// OpenThermSlave_Init(), OpenThermSlave_MainLoop()
#include "..\Hal\USART1.H"					// Usart1_PutMultiple()
#include "..\App\TestToolReceiver.H"		// bTestToolReceiver_ProcessMessage(), TestToolReceiver_DecodeFrame()
#include "..\Hal\Threshold.H"				//
#include "..\Hal\Timer.H"					//

TestToolMode_t mubMode = TESTTOOL_MODE_STOP; 

void TestTool_Send(TestToolMessage_t * p)
{
	uint8_t lubBuffer[22];
	if ((0 < p->ubLength) && (p->ubLength <= sizeof(lubBuffer)))
	{
		lubBuffer[0] = 0x02u;
		lubBuffer[1] = p->ubMode;
		lubBuffer[2] = p->ubPort;
		lubBuffer[3] = ubAsciiFromNibble(p->uwTimeStamp>>12);
		lubBuffer[4] = ubAsciiFromNibble(p->uwTimeStamp>>8);
		lubBuffer[5] = ubAsciiFromNibble(p->uwTimeStamp>>4);
		lubBuffer[6] = ubAsciiFromNibble(p->uwTimeStamp);
		lubBuffer[7] = ubAsciiFromNibble(p->ulMessage>>28);
		lubBuffer[8] = ubAsciiFromNibble(p->ulMessage>>24);
		lubBuffer[9] = ubAsciiFromNibble(p->ulMessage>>20);
		lubBuffer[10] = ubAsciiFromNibble(p->ulMessage>>16);
		lubBuffer[11] = ubAsciiFromNibble(p->ulMessage>>12);
		lubBuffer[12] = ubAsciiFromNibble(p->ulMessage>>8);
		lubBuffer[13] = ubAsciiFromNibble(p->ulMessage>>4);
		lubBuffer[14] = ubAsciiFromNibble(p->ulMessage);
		lubBuffer[15] = ubAsciiFromNibble(p->ubMidbitInfo>>4);
		lubBuffer[16] = ubAsciiFromNibble(p->ubMidbitInfo);
		lubBuffer[17] = ubAsciiFromNibble(p->uwResponseTime>>12);
		lubBuffer[18] = ubAsciiFromNibble(p->uwResponseTime>>8);
		lubBuffer[19] = ubAsciiFromNibble(p->uwResponseTime>>4);
		lubBuffer[20] = ubAsciiFromNibble(p->uwResponseTime);
		lubBuffer[p->ubLength-1] = 0x03u;
		
		Usart1_PutMultiple(&lubBuffer[0], p->ubLength);
	}
}

void TestTool_Send_Mode(TestToolMode_t lubMode)
{
	TestToolMessage_t lMessage;
	
	lMessage.ubMode = lubMode;
	lMessage.ubLength = 3u;
	TestTool_Send(&lMessage);
}

void TestTool_MainLoop(void)
{
	TestToolMessage_t lMessage;
	if (bTestToolReceiver_ProcessMessage())
	{
		// message received
		TestToolReceiver_DecodeFrame(&lMessage);
		switch (lMessage.ubMode)
		{
			case TESTTOOL_MODE_MONITOR:
				mubMode = TESTTOOL_MODE_MONITOR;
				TestTool_Send_Mode(TESTTOOL_MODE_ACKNOWLEDGE_MONITOR);
				OpenThermMaster_Init();
				OpenThermSlave_Init();
			break;
			case TESTTOOL_MODE_MASTER:
				mubMode = TESTTOOL_MODE_MASTER;
				BitTime_Set(lMessage.uwTimeStamp);
				OpenThermMaster_MainLoop(&lMessage);
				OpenThermMonitor_Init();
				OpenThermSlave_Init();
			break;
			case TESTTOOL_MODE_SLAVE:
				mubMode = TESTTOOL_MODE_SLAVE;
				BitTime_Set(lMessage.uwTimeStamp);
				ResponseTime_Set(lMessage.uwResponseTime);
				OpenThermSlave_MainLoop(&lMessage);
				OpenThermMonitor_Init();
				OpenThermMaster_Init();
			break;
			case TESTTOOL_MODE_STOP:
				mubMode = TESTTOOL_MODE_STOP;
				TestTool_Send_Mode(TESTTOOL_MODE_ACKNOWLEDGE_STOP);
				OpenThermMonitor_Init();
				OpenThermMaster_Init();
				OpenThermSlave_Init();
			break;
			case TESTTOOL_MODE_CONTROL_IS_STILL_LIVE:
				TestTool_Send_Mode(TESTTOOL_MODE_ACKNOWLEDGE_CONTROL_IS_STILL_LIVE);
			break;
			default:
			break;
		}
	}
	lMessage.ubLength = 0u;
	switch (mubMode)
	{
		case TESTTOOL_MODE_MONITOR:
			OpenThermMonitor_MainLoop(&lMessage);
		break;
		case TESTTOOL_MODE_MASTER:
			OpenThermMaster_MainLoop(&lMessage);
		break;
		case TESTTOOL_MODE_SLAVE:
			OpenThermSlave_MainLoop(&lMessage);
		break;
		default:
		break;
	}
	TestTool_Send(&lMessage);
}

TestToolMode_t ubTestTool_Mode_Get(void)
{
	return mubMode;
}