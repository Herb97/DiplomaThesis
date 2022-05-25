/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-03-22           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermTransmitter.C
;
;******************************************************************************
; SVN header
;  $Id: OpenThermTransmitter.C 118393 2022-05-06 06:44:17Z Stepanek, Michal $
******************************************************************************/

//*****************************************************************************
// INCLUDE FILES
//*****************************************************************************
#include ".\OpenThermReceiver.H"			// ulOpenTherm_Parity()
#include ".\OpenThermTransmitter.H"			// OWN definition file


#define SIZEOF_START_FRAME_STOP		68u		// (1 start + 32 bits + 1 stop) * 2 = 68

/******************************************************************************
; Procedure     : bOpenThermTransmitter_HalfBitTime()
; Description   : Manages sending and smartpower transitions and timings
; Input         : p pointer to structure instance, RX pin value
; Output        : bit to transmit
;*****************************************************************************/
bool bOpenThermTransmitter_HalfBitTime(OpenThermTransmitter_t *p)
{
	if (p->uwTxCounter)
	{
		// transmitting tasks
		if (p->uwTxCounter > SIZEOF_START_FRAME_STOP)
		{
			// delay to achieve minimal delay of 20ms before response
		}
		else
		{
			// we are sending packet
			if (0u == (p->uwTxCounter&1u))
			{
				// first phase of manchester
				if ((p->uwTxCounter >= 3)&&(p->uwTxCounter <= 66))
				{
					// bit of packet
					if (p->ulFrame & 0x80000000uL)
					{
						// signal for bitvalue 1
						p->bTxBit = !p->bTxPower;
					}
					else
					{
						// signal for bitvalue 0
						p->bTxBit = p->bTxPower;
					}
					// shift to the next bit
					p->ulFrame <<= 1;
				}
				else
				{
					// start or stop bit (value 1)
					p->bTxBit = !p->bTxPower;
				}
			}
			else
			{
				// second phase of manchester
				p->bTxBit = !p->bTxBit;
			}
		}

		// next phase
		p->uwTxCounter--;
	}
	return p->bTxBit;
}


/******************************************************************************
; Procedure     : OpenThermTransmitter_Send
; Description   : Setup packet for sending, parity has to calculated in advance.
; Input         : p - pointer to structure instance
; Output        : -
;*****************************************************************************/
void OpenThermTransmitter_Send(OpenThermTransmitter_t *p)
{
	if (0 == p->uwTxCounter)
	{
		// clear parity
		//p->ulFrame &= 0x7FFFFFFFu;
		// calculate parity
		//p->ulFrame = ulOpenTherm_Parity(p->ulFrame);
		// initial value for the bit
		p->bTxBit = p->bTxPower;
		// start sending trigger - the very last action
		p->uwTxCounter = SIZEOF_START_FRAME_STOP;	// (1 start + 32 bits + 1 stop) * 2 = 68
	}
}


/******************************************************************************
; Procedure     : OpenThermTransmitter_Init
; Description   : Initialization of structures - call it once
; Input         : p pointer to structure instance
; Output        : -
;*****************************************************************************/
void OpenThermTransmitter_Init(OpenThermTransmitter_t *p)
{
	do
	{
		p->uwTxCounter = 0u;	// idle
	}
	while(bOpenThermTransmitter_InProgress(p));
	p->bTxPower = 0u;		// low power
	p->bTxBit = 0u;
}


/**
  * @brief Check whether transmitting is in progress.
  * @param OpenThermTransmitter_t pointer
  * @retval True if transmitting is in progress
  */

bool bOpenThermTransmitter_InProgress(OpenThermTransmitter_t * p)
{
	if (p->uwTxCounter > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
  * @brief Inform PC about sending
  * @param OpenThermTransmitter_t pointer
  * @retval True if transmitting just started
  */

bool bOpenThermTransmitter_Sending(OpenThermTransmitter_t * p)
{
	if (SIZEOF_START_FRAME_STOP == p->uwTxCounter)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
  * @brief Check whether transmitting just started 
  * @param OpenThermTransmitter_t pointer
  * @retval True if transmitting just started
  */

/*bool bOpenThermTransmitter_SendingStart(OpenThermTransmitter_t * p)
{
	if ((p->uwTxCounter > 0) && (p->uwTxCounter < 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}*/


/**
  * @brief Check whether transmitting just started 
  * @param OpenThermTransmitter_t pointer
  * @retval True if transmitting just started
  */

bool bOpenThermTransmitter_SendingDone(OpenThermTransmitter_t * p)
{
	if ((p->uwTxCounter > 0) && (p->uwTxCounter < 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}
