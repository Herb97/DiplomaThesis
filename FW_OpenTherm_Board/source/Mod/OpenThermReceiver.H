/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-09-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermReceiver.H
;
;******************************************************************************
; SVN header
;  $Id: OpenThermReceiver.H 117544 2022-03-22 08:17:08Z Stepanek, Michal $
******************************************************************************/


/******************************************************************************
; TYPEDEF
;*****************************************************************************/
typedef struct
{
	uint8_t		ubState;			// Receiver state
	uint8_t		ubRxBitIdle;		// How long is the RX pin unchanged, to detect end of frame
	uint16_t	uwPrevTimeStamp;	// Previous time stamp
	uint16_t	uwPrevEdgeToEdge;	// Previous edge to edge time
	uint32_t	ulFrame;			// decoded frame
} OpenThermReceiver_t;


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
bool OpenThermReceiver_MainLoop(OpenThermReceiver_t *pOpenTherm);
void OpenThermReceiver_PinChange(OpenThermReceiver_t * p, uint16_t luwTimeStamp);
void OpenThermReceiver_100us(OpenThermReceiver_t *pOpenTherm);


bool bOpenThermReceiver_IsReady(OpenThermReceiver_t * p);
void OpenThermReceiver_Free(OpenThermReceiver_t * p);
uint32_t ulOpenThermReceiver_Frame_Get(OpenThermReceiver_t * p);
bool bOpenThermReceiver_CheckParity(uint32_t lulFrame);
bool bOpenThermReceiver_InProgress(OpenThermReceiver_t * p);

uint32_t ulOpenTherm_Parity(uint32_t  lulFrame);

