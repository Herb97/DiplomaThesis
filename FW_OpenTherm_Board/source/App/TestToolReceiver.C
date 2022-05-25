/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: TestToolReceiver.C
;
*/

/*
See documentation:
OpenTherm TestTool V2.4
Chapter 6. Communication interface
Figure 1 Standard RS232 massage frame

Message frame size from 3 to 22 bytes

Every received byte is checked for its validity. If invalid, the receiver state machine is restarted and checking for TESTTOOL_START.
*/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include ".\TestTool.H"						// TestToolMessage_t
#include "..\Common\Mod\Ascii\Ascii.H"		// ubAsciiToHex()
#include "..\Hal\USART1.H"					// ubUsart1_Rx_Quantity(), ubUsart1_Rx_Get()
#include ".\TestToolReceiver.H"				// OWN header


/******************************************************************************
; LOCAL DEFINITIONS
;******************************************************************************/

//Defines for MICROCOM protocol
#define TESTTOOL_START			0x02u
#define TESTTOOL_STOP			0x03u


/******************************************************************************
; TYPEDEF
;*****************************************************************************/
typedef struct
{
	uint8_t ubNumber;						// number of received bytes, BIT7 is set if complete
	uint8_t ubBuffer[TESTTOOL_FRAME_SIZE];	// including Start and Stop
} TestToolReceiver_t;


//*****************************************************************************
// VARIABLE DEFINITION
//*****************************************************************************
TestToolReceiver_t mReceiver;



/******************************************************************************
; Procedure		: uwDecode2()
; Description	: Decodes pattern of four ASCII
; Input			: pointer to ASCII
; Output		: Decoded number
;******************************************************************************/
static uint8_t ubDecode2(uint8_t * pAscii)
{
	uint8_t lubResult = 0u;
	for (uint8_t i=0u; i < 2; i++)
	{
		lubResult <<= 4;
		lubResult |= ubAsciiToHex(pAscii[i]);
	}
	return lubResult;
}

/******************************************************************************
; Procedure		: uwDecode4()
; Description	: Decodes pattern of four ASCII
; Input			: pointer to ASCII
; Output		: Decoded number
;******************************************************************************/
static uint16_t uwDecode4(uint8_t * pAscii)
{
	uint16_t luwResult = 0u;
	for (uint8_t i=0u; i < 4; i++)
	{
		luwResult <<= 4;
		luwResult |= ubAsciiToHex(pAscii[i]);
	}
	return luwResult;
}

/******************************************************************************
; Procedure		: uwDecode8()
; Description	: Decodes pattern of four ASCII
; Input			: pointer to ASCII
; Output		: Decoded number
;******************************************************************************/
static uint32_t ulDecode8(uint8_t * pAscii)
{
	uint32_t lulResult = 0u;
	for (uint8_t i=0u; i < 8; i++)
	{
		lulResult <<= 4;
		lulResult |= ubAsciiToHex(pAscii[i]);
	}
	return lulResult;
}

/******************************************************************************
; Procedure		: bIsValidAsc()
; Description	: Returns TRUE, if input byte is ASCII coded (0x30-0x39 and 0x41-0x46).
; Input			: checked byte
; Output		: TRUE / FALSE
;******************************************************************************/
static bool bIsValidAsc(uint8_t lub)
{
	return (((0x30u<=lub)&&(lub<=0x39u))||((0x41u<=lub)&&(lub<=0x46u))) ? true : false;
}

/******************************************************************************
; Procedure		: StoreValidByte()
; Description	: Stores valid byte
; Input			: valid byte
;******************************************************************************/
static void StoreValidByte(uint8_t lubReceivedByte)
{
	if (mReceiver.ubNumber < TESTTOOL_FRAME_SIZE)
	{
		mReceiver.ubBuffer[mReceiver.ubNumber] = lubReceivedByte;
		mReceiver.ubNumber++;	// number of received bytes
		if (TESTTOOL_STOP == lubReceivedByte)
		{
			mReceiver.ubNumber |= BIT7;
		}
	}
}

/******************************************************************************
; Procedure		: CheckStart()
; Description	: restarts state machine and check Start
; Input			: received byte
;******************************************************************************/
static void CheckStart(uint8_t lubReceivedByte)
{
	// restart state machine
	mReceiver.ubNumber = 0;
	// check Start
	if (TESTTOOL_START == lubReceivedByte)
	{
		StoreValidByte(lubReceivedByte);
	}
}

/******************************************************************************
; Procedure		: TestToolReceiver_ProcessByte()
; Description	: Processing of received bytes, optimized to be called from USART receive interrupt
; Input			: received byte
;******************************************************************************/
void TestToolReceiver_ProcessByte(uint8_t lubReceivedByte)
{
	if (BIT7 & mReceiver.ubNumber)
	{
		// Whole frame received, wait here until picked up
	}
	else
	{
		switch(mReceiver.ubNumber)
		{
			case 0:
				CheckStart(lubReceivedByte);
			break;
			case 1:
				// check if ASCII coded
				if (bIsValidAsc(lubReceivedByte))
				{
					// store valid byte
					StoreValidByte(lubReceivedByte);
				}
				else
				{
					// restart state machine and check Start
					CheckStart(lubReceivedByte);
				}
			break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				// check TESTTOOL_STOP
				if (TESTTOOL_STOP == lubReceivedByte)
				{
					// store valid byte
					StoreValidByte(lubReceivedByte);
				}
				else
				{
					// check if ASCII coded
					if (bIsValidAsc(lubReceivedByte))
					{
						// store valid byte
						StoreValidByte(lubReceivedByte);
					}
					else
					{
						// restart state machine and check Start
						CheckStart(lubReceivedByte);
					}
				}
			break;
			case 21:
				// check TESTTOOL_STOP
				if (TESTTOOL_STOP == lubReceivedByte)
				{
					// store valid byte
					StoreValidByte(lubReceivedByte);
				}
				else
				{
					// restart state machine and check Start
					CheckStart(lubReceivedByte);
				}
			break;
			default:
				CheckStart(lubReceivedByte);
			break;
		}
	}
}

/******************************************************************************
; Procedure		: bTestToolReceiver_Ready()
; Description	: Returns TRUE, if whole frame received
; Output		: TRUE / FALSE
;******************************************************************************/
bool bTestToolReceiver_Ready(void)
{
	return (mReceiver.ubNumber & BIT7) ? true : false;
}

/******************************************************************************
; Procedure		: TestToolReceiver_Free()
; Description	: Enable (restart) receiver
;******************************************************************************/
static void TestToolReceiver_Free(void)
{
	mReceiver.ubNumber = 0u;
}

/******************************************************************************
; Procedure		: bTestToolReceiver_ProcessMessage()
; Description	: Processing of received bytes. Returns TRUE, if whole frame received
; Output		: TRUE / FALSE
;******************************************************************************/
bool bTestToolReceiver_ProcessMessage(void)
{
	while(ubUsart1_Rx_Quantity())
	{
		// something received
		TestToolReceiver_ProcessByte(ubUsart1_Rx_Get());
		if (bTestToolReceiver_Ready())
		{
			// received whole frame
			return true;
		}
	}
	return false;
}

/******************************************************************************
; Procedure		: TestToolReceiver_DecodeFrame()
; Description	: Decodes received data, call after bTestToolReceiver_Ready() returns TRUE
; Input			: pointer to TestTool_t structure
; Output		: filled TestTool_t structure
;******************************************************************************/
void TestToolReceiver_DecodeFrame(TestToolMessage_t *pMessage)
{
	pMessage->ubStart		= mReceiver.ubBuffer[0];
	pMessage->ubMode		= (TestToolMode_t)mReceiver.ubBuffer[1];
	pMessage->ubPort		= (TestToolPort_t)mReceiver.ubBuffer[2];
	pMessage->uwTimeStamp	= uwDecode4(&mReceiver.ubBuffer[3]);	// 3, 4, 5, 6
	pMessage->ulMessage		= ulDecode8(&mReceiver.ubBuffer[7]);	// 7, 8, 9, 10, 11, 12, 13, 14
	pMessage->ubMidbitInfo	= ubDecode2(&mReceiver.ubBuffer[15]);	// 15, 16
	pMessage->uwResponseTime= uwDecode4(&mReceiver.ubBuffer[17]);	// 17, 18, 19, 20
	pMessage->ubStop		= mReceiver.ubBuffer[21];
	pMessage->ubLength		= 0x7Fu & mReceiver.ubNumber;
	TestToolReceiver_Free();
}

