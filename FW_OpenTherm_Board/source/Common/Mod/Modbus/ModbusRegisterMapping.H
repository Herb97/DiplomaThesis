/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-07-20           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: ModbusRegisterMapping.H
;
;******************************************************************************
; SVN header
;  $Id: ModbusRegisterMapping.H 108834 2020-07-20 12:08:18Z Stepanek, Michal $
******************************************************************************/

// internal enumeration
typedef enum
{
	MBR_U8,		// unsigned 8 bits
	MBR_U16,	// unsigned 16 bits
	MBR_U32,	// unsigned 32 bits
	MBR_U64,	// unsigned 64 bits
	MBR_FLOAT,	// float 32 bits
//	MBR_S8,
	MBR_S16,	// signed 16 bits
//	MBR_S32,
//	MBR_S64,
//	MBR_DOUBLE,
//	MBR_TEXT,
//	MBR_STRCP,
//	MBR_ENUM,
//	MBR_BOOL,
}
MBR_FORMAT;

// Tabulka
typedef struct {
	uint16_t	uwStartingAddress;
	uint8_t		ubQuantityOfRegisters;
	MBR_FORMAT	ubFormat;
	union
	{
		void *pRead;
		uint8_t  (*pRead_uint8 )(void);
		uint16_t (*pRead_uint16)(void);
		uint32_t (*pRead_uint32)(void);
		float32_t(*pRead_float )(void);
		int16_t  (*pRead_int16 )(void);
		
	};
	union
	{
		void * pWrite;
		bool (*pWrite_uint8 )(uint8_t  x);
		bool (*pWrite_uint16)(uint16_t x);
		bool (*pWrite_uint32)(uint32_t x);
		bool (*pWrite_float )(float32_t x);
		bool (*pWrite_int16 )(int16_t  x);
	};
} const MODBUS_TABLE;


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/

MODBUS_TABLE * pModbusTable_Row_Get(uint16_t luwStartingAddress);
uint8_t ubModbusRegisterMapping_ReadMultipleRegisters(uint16_t luwStartingAddress, uint8_t lubQuantityOfRegisters, uint8_t * lpubValue);
uint8_t ubModbusRegisterMapping_WriteMultipleRegisters(uint16_t luwStartingAddress, uint8_t lubQuantityOfRegisters, uint8_t * lpubValue);

