/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-09-15           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermReceiver.C
;
;******************************************************************************
; SVN header
;  $Id: OpenThermReceiver.C 117825 2022-04-05 08:18:46Z Herbrych, Vojtech $
******************************************************************************/

#include ".\OpenThermReceiver.H"				// OWN header

//*****************************************************************************
// #DEFINE CONSTANTS
//*****************************************************************************
// timings at 2kHz basis (500 us)
//#define OPENTHERM_2MS         4

// timings at 10kHz basis (100 us)
#define OPENTHERM_2MS         20

// timings at TIMER basis (1 us)
// nominal 500 us
#define OPENTHERM_HALFBIT_MIN   250		// 250 us
#define OPENTHERM_HALFBIT_MAX   750		// 750 us
// nominal 1000 us
#define OPENTHERM_FULLBIT_MIN   750		// 750 us
#define OPENTHERM_FULLBIT_MAX   1250	// 1250 us


/******************************************************************************
; Procedure     : ulOpenTherm_Parity()
; Description   : XORs MSB according to parity of lower 31 bits
; Input         : frame
; Output        : frame + calculated parity at BIT31 position
;*****************************************************************************/
uint32_t ulOpenTherm_Parity(uint32_t  lulFrame)
{
	// xor 4 bytes from pointer position except parity (total 31 bites considered)
	uint32_t temp = lulFrame & 0x7FFFFFFF;
	// xor all bits in the byte, shifting to MSB
	temp ^= temp<<16;
	temp ^= temp<<8;
	temp ^= temp<<4;
	temp ^= temp<<2;
	temp ^= temp<<1;

	// attach the parity bit
	// receiving routine expects to xor out existing parity bit, so resulting parity must be 0
	// sending routine expects on entry having parity cleared, so now we attach the parity bit
	return lulFrame ^ (temp & 0x80000000U);
}


/**
  * @brief Restart frame decoding in case of timeout.
  * @param OpenThermReceiver_t pointer
  * @param luwTimeStamp 1 us time base
  * @retval None
  */

void OpenThermReceiver_PinChange(OpenThermReceiver_t * p, uint16_t luwTimeStamp)
{
	uint16_t luwEdgeToEdge;
	
	luwEdgeToEdge = luwTimeStamp - p->uwPrevTimeStamp;
	p->uwPrevTimeStamp = luwTimeStamp;
	
	if (0 == p->ubState)
	{
		// first edge
		p->ubState = 1;
	}
	else if (68 == p->ubState)
	{
		// whole packet received
	}
	else
	{
		if ((luwEdgeToEdge>=OPENTHERM_HALFBIT_MIN) && (luwEdgeToEdge<=OPENTHERM_HALFBIT_MAX))
		{
			// half bit
			if (1 == p->ubState)
			{
				// 1
				p->ubState += 1;
				p->ulFrame = 0x0001;	// first parity 
			}
			else if (1 == (p->ubState & BIT0))
			{
				// 3, 5, ... 67
				uint16_t luwBitPeriod = p->uwPrevEdgeToEdge + luwEdgeToEdge;
				if ((luwBitPeriod>=OPENTHERM_FULLBIT_MIN) && (luwBitPeriod<=OPENTHERM_FULLBIT_MAX))
				{
					p->ubState += 1;
					// save bit
					if (p->ubState<68)
					{
						// store the same bit as before
						if (p->ulFrame & 0x0001)
						{
							p->ulFrame <<=1;
							p->ulFrame ++;
						}
						else
						{
							p->ulFrame <<=1;
						}
					}
				}
				else
				{
					p->ubState = 0;		// restart decoding
				}
			}
			else
			{
				// 2, 4, 6, ... 68
				p->ubState += 1;
			}
		}
		else if ((luwEdgeToEdge>=OPENTHERM_FULLBIT_MIN) && (luwEdgeToEdge<=OPENTHERM_FULLBIT_MAX))
		{
			// full bit
			if (1 == p->ubState)
			{
				// 1
				p->ubState = 0;		// restart decoding
			}
			else if (1 == (p->ubState & BIT0))
			{
				// 3, 5, ... 67
				p->ubState = 0;		// restart decoding
			}
			else
			{
				// 2, 4, 6, ... 68
				p->ubState += 2;
				// save bit
				if (p->ubState<68)
				{
					// store the negative bit
					if (p->ulFrame & 0x0001)
					{
						p->ulFrame <<=1;
					}
					else
					{
						p->ulFrame <<=1;
						p->ulFrame ++;
					}
				}
			}
		}
		else
		{
			p->ubState = 0;		// restart decoding
		}
	}
	p->uwPrevEdgeToEdge = luwEdgeToEdge;
	p->ubRxBitIdle = 0;
}


/**
  * @brief Restart frame decoding in case of timeout.
  * @param OpenThermReceiver_t pointer
  * @retval None
  */

void OpenThermReceiver_100us(OpenThermReceiver_t *pOpenTherm)
{
	if (pOpenTherm->ubRxBitIdle < 0xFF)
	{
		pOpenTherm->ubRxBitIdle++;
	}
	if ((pOpenTherm->ubRxBitIdle > OPENTHERM_2MS) && (pOpenTherm->ubState < 68))
	{
		pOpenTherm->ubState = 0;
	}
}

/**
  * @brief Check whether frame is received.
  * @param OpenThermReceiver_t pointer
  * @retval True if frame is received.
  */

bool bOpenThermReceiver_IsReady(OpenThermReceiver_t * p)
{
	return (p->ubState >= 68) ? true : false;
}


uint8_t ubOpenThermReceiver_State_Get(OpenThermReceiver_t * p)
{
	return p->ubState;
}

/**
  * @brief Free the receiver
  * @param OpenThermReceiver_t pointer
  * @retval None
  */

void OpenThermReceiver_Free(OpenThermReceiver_t * p)
{
	volatile uint8_t lubState;
	do
	{
		p->ubState = 0;
	}
	while(ubOpenThermReceiver_State_Get(p));
}


/**
  * @brief Get received frame
  * @param OpenThermReceiver_t pointer
  * @retval received frame
  */

uint32_t ulOpenThermReceiver_Frame_Get(OpenThermReceiver_t * p)
{
	return p->ulFrame;
}


/**
  * @brief Check parity.
  * @param Received frame
  * @retval True if parity is correct
  */

bool bOpenThermReceiver_CheckParity(uint32_t lulFrame)
{
	if (0==(ulOpenTherm_Parity(lulFrame)&0x80000000U))
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
  * @brief Check whether receiving is in progress.
  * @param OpenThermReceiver_t pointer
  * @retval True if receiving is in progress
  */

bool bOpenThermReceiver_InProgress(OpenThermReceiver_t * p)
{
	if ((p->ubState>0)&&(p->ubState<67))
	{
		return true;
	}
	else
	{
		return false;
	}
}

