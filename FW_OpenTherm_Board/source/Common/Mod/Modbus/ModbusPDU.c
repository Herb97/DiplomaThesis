/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2008-01-25           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: ModbusPDU.c
;
;******************************************************************************
; SVN header
;  $Id: ModbusPDU.c 108832 2020-07-20 11:09:28Z Stepanek, Michal $
******************************************************************************/

/*
MODBUS protocol, Protocol Data Unit (PDU).
****************************
*                 *        *
*  Function code  *  Data  *
*                 *        *
****************************

DESCRIPTION:	Contains the implementation of the following MODBUS functionalities:
				0x03 - Read Holding Registers
				0x06 - Write Single Register
				0x10 - Write Multiple Registers

Made by state diagrams in Modbus_Application_Protocol_V1_1b.pdf
*/

#include <stdint.h>
#include "..\..\Drv\Endian\Endian.H"
#include ".\ModbusRegisterMapping.H"		// ubModbusRegisterMapping_ReadMultipleRegisters(), ubModbusRegisterMapping_WriteMultipleRegisters()
#include ".\ModbusFunctionCodes.H"
#include ".\ModbusPdu.h"					// OWN header



/******************************************************************************
; VARIABLE DEFINITION
;******************************************************************************/
static uint8_t mubExceptionStatus;



static uint8_t Error(uint8_t lubExceptionCode, uint8_t * pPdu)
{
	pPdu[0] |= 0x80;
	pPdu[1] = lubExceptionCode;
	return 2;	// Response length
}

uint8_t ModbusPdu_Do(uint8_t * pPdu, uint8_t lubRequestSize, uint8_t lubResponseSizeMax)
{
	if (lubResponseSizeMax<2)
	{
		return 0;	// Response length
	}
	else
	{
		switch (pPdu[0])	// Check Function Code
		{
			case MODBUS_FUNCTION_CODE_READ_HOLDING_REGISTERS:		// 6.3 03 (0x03) Read Holding Registers, strana 15
			{
				/*
				*N = Quantity of Registers
				Request
					Function code			1 Byte			0x03
					Starting Address		2 Bytes			0x0000 to 0xFFFF
					Quantity of Registers	2 Bytes			1 to 125 (0x7D)
				Response
					Function code			1 Byte			0x03
					Byte count				1 Byte			2 x N*
					Register value			N* x 2 Bytes
				Error
					Error code				1 Byte			0x83
					Exception code			1 Byte			01 or 02 or 03 or 04
				*/
				uint16_t luwStartingAddress		= uwEndian_MsbLsbToU16(&pPdu[1]);
				uint16_t luwQuantityOfRegisters	= uwEndian_MsbLsbToU16(&pPdu[3]);
				if ((lubRequestSize!=5)||(luwQuantityOfRegisters<1)||(luwQuantityOfRegisters>125)||(luwQuantityOfRegisters > ((lubResponseSizeMax-2)/2)))	// Check the correct range of required register count
				{
					return Error(MODBUS_EXCEPTIONCODE_03_ILLEGALDATAVALUE, pPdu);
				}
				else
				{
					uint8_t lubExceptionCode;
					lubExceptionCode = ubModbusRegisterMapping_ReadMultipleRegisters(luwStartingAddress, luwQuantityOfRegisters, /*Response Register value*/&pPdu[2]);
					if (lubExceptionCode)
					{
						return Error(lubExceptionCode, pPdu);
					}
					else
					{
						uint8_t lubByteCount = 2*luwQuantityOfRegisters;
						// pPdu[0]				Function code stays unchanged
						pPdu[1] = lubByteCount;
						return 2+lubByteCount;	// Response length
					}
				}	
			}
			break;
			case MODBUS_FUNCTION_CODE_WRITE_SINGLE_REGISTER:		// 6.6 06 (0x06) Write Single Register
			{
				/*
				Request
					Function code			1 Byte			0x06
					Register Address		2 Bytes			0x0000 to 0xFFFF
					Register Value			2 Bytes			0x0000 to 0xFFFF
				Response
					Function code			1 Byte			0x06
					Register Address		2 Bytes			0x0000 to 0xFFFF
					Register Value			2 Bytes			0x0000 to 0xFFFF
				Error
					Error code				1 Byte			0x86
					Exception code			1 Byte			01 or 02 or 03 or 04
				*/
				uint16_t luwRegisterAddress	= uwEndian_MsbLsbToU16(&pPdu[1]);
				if ((lubResponseSizeMax<5)||(lubRequestSize<5))		// Check the correct ranges
				{
					return Error(MODBUS_EXCEPTIONCODE_03_ILLEGALDATAVALUE, pPdu);
				}
				else
				{
					uint8_t lubExceptionCode;
					lubExceptionCode = ubModbusRegisterMapping_WriteMultipleRegisters(luwRegisterAddress,1,/*Request Register Value*/&pPdu[3]);
					if (lubExceptionCode)
					{
						return Error(lubExceptionCode, pPdu);
					}
					else
					{
						return 5;	// Response length: Function code, Register Address, Register Value - stay unchanged
					}
				}
			}
			break;
			case MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_REGISTERS:		// 6.12 16 (0x10) Write Multiple registers, strana 30
			{
				/*
				*N = Quantity of Registers
				Request:
					Function code			1 Byte			0x10
					Starting Address		2 Bytes			0x0000 to 0xFFFF
					Quantity of Registers	2 Bytes			0x0001 to 0x007B
					Byte Count				1 Byte			2 x N*
					Registers Value			N* x 2 Bytes	value
				Response
					Function code			1 Byte			0x10
					Starting Address		2 Bytes			0x0000 to 0xFFFF
					Quantity of Registers	2 Bytes			1 to 123 (0x7B)
				Error                 
				Error code					1 Byte			0x90
				Exception code				1 Byte			01 or 02 or 03 or 04
				*/
				
				uint16_t luwStartingAddress		= uwEndian_MsbLsbToU16(&pPdu[1]);
				uint16_t luwQuantityOfRegisters	= uwEndian_MsbLsbToU16(&pPdu[3]);
				uint8_t  lubByteCount			= pPdu[5];
				if ((lubResponseSizeMax<5)||(lubRequestSize<6)||(luwQuantityOfRegisters<1)||(luwQuantityOfRegisters>0x7B)||(lubByteCount!=(luwQuantityOfRegisters*2)))	// Check the correct range of register count and data bytes
				{
					return Error(MODBUS_EXCEPTIONCODE_03_ILLEGALDATAVALUE, pPdu);
				}
				else
				{
					uint8_t lubExceptionCode;
					lubExceptionCode = ubModbusRegisterMapping_WriteMultipleRegisters(luwStartingAddress,luwQuantityOfRegisters,/*Request Registers Value*/&pPdu[6]);
					if (lubExceptionCode)
					{
						return Error(lubExceptionCode, pPdu);
					}
					else
					{
						return 5;	// Response length: Function code, Starting Address, Quantity of Registers - stay unchanged
					}
				}
			}
			break;
			case MODBUS_FUNCTION_CODE_READ_EXCEPTION_STATUS:		// 6.7 07 (0x07) Read Exception Status (Serial Line only)
			{
				/*
				Request
					Function code			1 Byte			0x07
				Response
					Function code			1 Byte			0x07
					Output Data				1 Byte			0x00 to 0xFF
				*/
				// pPdu[0]						// Function code stays unchanged
				pPdu[1] = mubExceptionStatus;	// Output Data
				return 2;						// Response length
			}
			break;
			default:
			{
				// Funtion code not supported
				return Error(MODBUS_EXCEPTIONCODE_01_ILLEGALFUNCTION, pPdu);
			}
			break;	
		}
	}
}

