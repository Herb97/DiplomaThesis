/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-07-20           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: ModbusRegisterMapping.C
;
;******************************************************************************
; SVN header
;  $Id: ModbusRegisterMapping.C 108834 2020-07-20 12:08:18Z Stepanek, Michal $
******************************************************************************/

/*
Access to "Registers Value" field in Modbus frame
*/


#include "..\Common\Drv\Endian\Endian.H"	// Endian_U16ToMsbLsb(), Endian_U32ToMsbLsb(), Endian_FloatToMsbLsb(), uwEndian_MsbLsbToU16(), ulEndian_MsbLsbToU32(), Endian_MsbLsbToFloat()
#include ".\ModbusRegisterMapping.H"		// OWN header


/*
Vyète poèet registrù lubQuantityOfRegisters z pamìti
zdrojový ukazatel luwStartingAddress
cílový ukazatel lpubValue (MsbLsb)
*/
uint8_t ubModbusRegisterMapping_ReadMultipleRegisters(uint16_t luwStartingAddress, uint8_t lubQuantityOfRegisters, uint8_t * lpubValue)
{
	while (lubQuantityOfRegisters)
	{
		// find the StartingAddress in MODBUS_TABLE
		MODBUS_TABLE * lpRow = pModbusTable_Row_Get(luwStartingAddress);
		if (NULL != lpRow)
		{
			// found lpRow with desired luwStartingAddress
			if (lubQuantityOfRegisters >= lpRow->ubQuantityOfRegisters)
			{
				// there is enough QuantityOfRegisters
				if (NULL != lpRow->pRead)
				{
					// read function exists
					switch(lpRow->ubFormat)
					{
						case MBR_U8:
							Endian_U16ToMsbLsb(lpRow->pRead_uint8(),lpubValue);
						break;
						case MBR_U16:
							Endian_U16ToMsbLsb(lpRow->pRead_uint16(),lpubValue);
						break;
						case MBR_U32:
							Endian_U32ToMsbLsb(lpRow->pRead_uint32(),lpubValue);
						break;
						case MBR_FLOAT:
							Endian_FloatToMsbLsb(lpRow->pRead_float(),lpubValue);
						break;
						case MBR_S16:
							Endian_U16ToMsbLsb(lpRow->pRead_int16(),lpubValue);
						break;
						default:
							// not supported MBR_FORMAT in RegisterTable[]
							return 4;	// Exception SLAVE DEVICE FAILURE
						break;
					}
					// move to next item
					uint8_t lubRegistersInRow = lpRow->ubQuantityOfRegisters;
					luwStartingAddress			+= lubRegistersInRow;
					lubQuantityOfRegisters		-= lubRegistersInRow;
					lpubValue					+= lubRegistersInRow*2;
				}
				else
				{
					// read function not defined in RegisterTable[]
					return 4;	// Exception SLAVE DEVICE FAILURE
				}
			}
			else
			{
				// wrong QuantityOfRegisters
				return 4;	// Exception SLAVE DEVICE FAILURE
			}
		}
		else
		{
			// StartingAddress not found
			return 4;	// Exception SLAVE DEVICE FAILURE
		}
	}
	return 0;	// OK, no exception
}

/*
Zapíše poèet registrù lubQuantityOfRegisters do pamìti
cílový ukazatel luwStartingAddress
zdrojový ukazatel lpubValue (MsbLsb)
*/
uint8_t ubModbusRegisterMapping_WriteMultipleRegisters(uint16_t luwStartingAddress, uint8_t lubQuantityOfRegisters, uint8_t * lpubValue)
{
	while (lubQuantityOfRegisters)
	{
		// find the StartingAddress in MODBUS_TABLE
		MODBUS_TABLE * lpRow = pModbusTable_Row_Get(luwStartingAddress);
		if (NULL != lpRow)
		{
			// found lpRow with desired luwStartingAddress
			if (lubQuantityOfRegisters >= lpRow->ubQuantityOfRegisters)
			{
				// there is enough QuantityOfRegisters
				if (NULL != lpRow->pWrite)
				{
					// write function exists
					switch(lpRow->ubFormat)
					{
						case MBR_U8:
							if (false == lpRow->pWrite_uint8(uwEndian_MsbLsbToU16(lpubValue)))
							{
								// written value out of limit
								return 4;	// Exception SLAVE DEVICE FAILURE
							}
						break;
						case MBR_U16:
							if (false == lpRow->pWrite_uint16(uwEndian_MsbLsbToU16(lpubValue)))
							{
								// written value out of limit
								return 4;	// Exception SLAVE DEVICE FAILURE
							}
						break;
						case MBR_U32:
							if (false == lpRow->pWrite_uint32(ulEndian_MsbLsbToU32(lpubValue)))
							{
								// written value out of limit
								return 4;	// Exception SLAVE DEVICE FAILURE
							}
						break;
						case MBR_FLOAT:
							if (false == lpRow->pWrite_float(fEndian_MsbLsbToFloat(lpubValue)))
							{
								// written value out of limit
								return 4;	// Exception SLAVE DEVICE FAILURE
							}
						break;
						case MBR_S16:
							if (false == lpRow->pWrite_int16(uwEndian_MsbLsbToU16(lpubValue)))
							{
								// written value out of limit
								return 4;	// Exception SLAVE DEVICE FAILURE
							}
						break;
						default:
							// not supported MBR_FORMAT in RegisterTable[]
							return 4;	// Exception SLAVE DEVICE FAILURE
						break;
					}
					// move to next item
					uint8_t lubRegistersInRow = lpRow->ubQuantityOfRegisters;
					luwStartingAddress			+= lubRegistersInRow;
					lubQuantityOfRegisters		-= lubRegistersInRow;
					lpubValue					+= lubRegistersInRow*2;
				}
				else
				{
					// write function not defined in RegisterTable[]
					return 4;	// Exception SLAVE DEVICE FAILURE
				}
			}
			else
			{
				// wrong QuantityOfRegisters
				return 4;	// Exception SLAVE DEVICE FAILURE
			}
		}
		else
		{
			// StartingAddress not found
			return 4;	// Exception SLAVE DEVICE FAILURE
		}
	}
	return 0;	// OK, no exception
}
