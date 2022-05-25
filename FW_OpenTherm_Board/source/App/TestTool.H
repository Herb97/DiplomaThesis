/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: TestTool.H
;
;******************************************************************************
; SVN header
;  $Id: TestTool.H 117763 2022-03-31 16:17:16Z Herbrych, Vojtech $
******************************************************************************/

/******************************************************************************
; HEADER DEFINITION
;*****************************************************************************/
#ifndef TestTool_H
#define TestTool_H


#define TESTTOOL_FRAME_SIZE					22u
#define TESTTOOL_SIZE_MODE					3u
#define TESTTOOL_SIZE_MODE_PORT_TIMESTAMP	8u



/******************************************************************************
; TYPEDEF
;*****************************************************************************/
typedef enum
{
	// from PC to tester
	TESTTOOL_MODE_MONITOR				= '0',
	TESTTOOL_MODE_MASTER				= '1',
	TESTTOOL_MODE_SLAVE					= '2',
	TESTTOOL_MODE_SMART_POWER_SETTINGS	= '3',
	TESTTOOL_MODE_LITE_MASTER			= '4',
	TESTTOOL_MODE_LITE_SLAVE			= '5',
	TESTTOOL_MODE_CONTROL_IS_STILL_LIVE	= '6',
	TESTTOOL_MODE_STOP					= '7',
	// from tester to PC
	TESTTOOL_MODE_MONITOR_RECEIVED_MESSAGE			= '0',
	TESTTOOL_MODE_MASTER_RECEIVED_MESSAGE			= '1',
	TESTTOOL_MODE_SLAVE_RECEIVED_MESSAGE			= '2',
	TESTTOOL_MODE_ACKNOWLEDGE_MONITOR				= '8',
	TESTTOOL_MODE_ACKNOWLEDGE_MASTER				= '9',
	TESTTOOL_MODE_ACKNOWLEDGE_SLAVE					= 'A',
	TESTTOOL_MODE_ACKNOWLEDGE_SMART_POWER_SETTINGS	= 'B',
	TESTTOOL_MODE_ACKNOWLEDGE_LITE_MASTER			= 'C',
	TESTTOOL_MODE_ACKNOWLEDGE_LITE_SLAVE			= 'D',
	TESTTOOL_MODE_ACKNOWLEDGE_CONTROL_IS_STILL_LIVE	= 'E',
	TESTTOOL_MODE_ACKNOWLEDGE_STOP					= 'F',
}TestToolMode_t;

typedef enum
{
	TESTTOOL_PORT_MESSAGE_FROM_MASTER_IDLE_LOW			= '0',
	TESTTOOL_PORT_MESSAGE_FROM_SLAVE_IDLE_LOW			= '1',
	TESTTOOL_PORT_MESSAGE_FROM_MASTER_IDLE_HIGH			= '8',
	TESTTOOL_PORT_MESSAGE_FROM_SLAVE_IDLE_HIGH			= '9',

	TESTTOOL_PORT_REPLY_RECEIVED_IN_TIME_IDLE_LOW		= '0',
	TESTTOOL_PORT_REPLY_RECEIVED_IN_TIME_IDLE_HIGH		= '2',
	TESTTOOL_PORT_REPLY_RECEIVED_TOO_LATE_IDLE_LOW		= 'D',
	TESTTOOL_PORT_REPLY_RECEIVED_TOO_LATE_IDLE_HIGH		= 'F',

	TESTTOOL_PORT_SLAVE_IDLE_FROM_HIGH_TO_LOW			= '8',
	TESTTOOL_PORT_SLAVE_IDLE_FROM_LOW_TO_HIGH			= '9',
	TESTTOOL_PORT_LIVE_CHECK_FIRMWARE_VERSION			= 'A',
	TESTTOOL_PORT_MASTER_IDLE_FROM_HIGH_TO_LOW			= 'B',
	TESTTOOL_PORT_MASTER_IDLE_FROM_LOW_TO_HIGH			= 'C',
	TESTTOOL_PORT_MASTER_SLAVE_MESSAGE_SEND_BY_CONTROL	= 'E',
	TESTTOOL_PORT_SERIAL_MESSAGE_INCORRECT				= 'F',
}TestToolPort_t;

typedef struct
{
	uint8_t			ubStart			;
	TestToolMode_t	ubMode			;
	TestToolPort_t	ubPort			;
	uint16_t		uwTimeStamp		;
	uint32_t		ulMessage		;
	uint8_t			ubMidbitInfo	;
	uint16_t		uwResponseTime	;
	uint8_t			ubStop			;
	uint8_t			ubLength		;
}TestToolMessage_t;

void TestTool_Send(TestToolMessage_t * p);
void TestTool_MainLoop(void);
TestToolMode_t ubTestTool_Mode_Get(void);

bool bCurrent_HighLevel_Set(float32_t f);
float32_t fCurrent_HighLevel_Set(void);
bool bCurrent_LowLevel_Set(float32_t f);
float32_t fCurrent_LowLevel_Set(void);
bool bVoltage_HighLevel_Set(float32_t f);
float32_t fVoltage_HighLevel_Set(void);
bool bVoltage_LowLevel_Set(float32_t f);
float32_t fVoltage_LowLevel_Set(void);

float32_t fCurrent_HighLevel_Get(void);
float32_t fCurrent_LowLevel_Get(void);
float32_t fVoltage_HighLevel_Get(void);
float32_t fVoltage_LowLevel_Get(void);

/******************************************************************************
; END OF HEADER DEFINITION
;*****************************************************************************/
#endif // TestTool_H