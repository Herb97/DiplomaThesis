/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2008-01-25           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: ModbusAdu.C
;
;******************************************************************************
; SVN header
;  $Id: ModbusAdu.C 106865 2020-03-30 16:39:03Z Stepanek, Michal $
******************************************************************************/

/*
MODBUS protocol, Application Data Unit (ADU).

General MODBUS frame (ADU)
 ****************************************
*                    *     *             *
* Additional address * PDU * Error check *
*                    *     *             *
 ****************************************

Modbus_Application_Protocol_V1_1b.pdf
*/

#include ".\ModbusAdu.H"					// OWN header
#include ".\ModbusPDU.h"					// ModbusPdu_Do()
#include "..\Crc\CrcA001.H"					// uwCrcA001_Get()
#include "..\..\Drv\Endian\Endian.H"		// Endian_U16ToLsbMsb()
uint8_t ubModbusAddress_Get(void);



#define SIZEOF_ADDITIONAL_ADDRESS	1
#define SIZEOF_ERROR_CHECK			2
#define OFFSET_ADDITIONAL_ADDRESS	0
#define OFFSET_PDU					1



/**
  * @brief  Processing of General MODBUS frame (ADU)
  * @param  pAdu Pointer to MODBUS frame (ADU) request/response
  * @param  lubRequestSize Length of incoming MODBUS frame (ADU)
  * @param  lubResponseSizeMax Maximum length of returned response
  * @retval Response length including Additional address and Error check
  *         0 = No response
  */
uint8_t ModbusAdu_Do(uint8_t * pAdu, uint8_t lubRequestSize, uint8_t lubResponseSizeMax)
{
	if (lubRequestSize > (SIZEOF_ADDITIONAL_ADDRESS+SIZEOF_ERROR_CHECK))
	{
		if (pAdu[OFFSET_ADDITIONAL_ADDRESS] == ubModbusAddress_Get())	// Check of Additional address
		{
			if (0x0000 == uwCrcA001_Get(pAdu, lubRequestSize))	// Check of Error check
			{
				uint8_t lubResponseSize;
				uint16_t luwErrorCheck;
				lubResponseSize = ModbusPdu_Do(&pAdu[OFFSET_PDU], (lubRequestSize-(SIZEOF_ADDITIONAL_ADDRESS+SIZEOF_ERROR_CHECK)), lubResponseSizeMax-(SIZEOF_ADDITIONAL_ADDRESS+SIZEOF_ERROR_CHECK));
				lubResponseSize += SIZEOF_ADDITIONAL_ADDRESS;
				luwErrorCheck = uwCrcA001_Get(pAdu,lubResponseSize);	// Error check calculated also from Additional address
				Endian_U16ToLsbMsb(luwErrorCheck,&pAdu[lubResponseSize]);	// Store Error check at the end of General MODBUS frame (ADU)
				lubResponseSize += SIZEOF_ERROR_CHECK;
				return lubResponseSize;	// Response length including Additional address and Error check
			}
		}
	}
	return 0;	// No response
}

