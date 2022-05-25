/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: ModbusTable.C
;
*/

/*

*/

#include "..\Common\Mod\Modbus\ModbusRegisterMapping.H"	// MBR_FORMAT, MODBUS_TABLE
#include "..\Common\Drv\Endian\Endian.H"				// Endian_U16ToMsbLsb(), uwEndian_MsbLsbToU16()
#include "..\Common\Drv\SystemControl\SystemControl.H"	// uwSystemControl_DeviceSignatureGet(), uwSystemControl_HardwareRevisionGet(), uwSystemControl_FirmwareRevisionGet(), uwSystemControl_SystemClockGet(), ubSystemControl_DeviceStatusGet(), SystemControl_ErrorCodeGet()
#include "..\Hal\ADC.H"									// uwADC_ADC_Current_Get(), uwADC_ADC_Voltage_Get(), uwADC_ADC_Current_Thermostat_Get(), uwADC_ADC_Voltage_Thermostat_Get(), uwADC_ADC_Voltage_Monitor_Get(), uwADC_ADC_Current_Monitor_Get()
#include "..\Hal\DAC.H"									// bDAC_CH1Value_Set(), bDAC_CH2Value_Set()
#include "..\Hal\ModbusAddress.H"			        	// ubModbusAddress_Get()
#include "..\Hal\Threshold.H"							// fLevel_Get(), bLevel_Set()
#include "..\App\TestTool.H"							// bVoltage_HighLevel, bVoltage_LowLevel, bCurrent_HighLevel, bCurrent_LowLevel 



static bool bLevel_MaCuTh_Set(float32_t f){return bLevel_Set(f,	MASTER_CURRENT_THRESHOLD	);}
static bool bLevel_MoCuTh_Set(float32_t f){return bLevel_Set(f,	MONITOR_CURRENT_THRESHOLD	);}
static bool bLevel_SlCuLo_Set(float32_t f){return bLevel_Set(f,	SLAVE_CURRENT_LOW			);}
static bool bLevel_SlCuHi_Set(float32_t f){return bLevel_Set(f,	SLAVE_CURRENT_HIGH			);}
static bool bLevel_MaVoLo_Set(float32_t f){return bLevel_Set(f,	MASTER_VOLTAGE_LOW			);}
static bool bLevel_MaVoHi_Set(float32_t f){return bLevel_Set(f,	MASTER_VOLTAGE_HIGH			);}
static bool bLevel_MoVoTh_Set(float32_t f){return bLevel_Set(f,	MONITOR_VOLTAGE_THRESHOLD	);}
static bool bLevel_SlVoTh_Set(float32_t f){return bLevel_Set(f,	SLAVE_VOLTAGE_THRESHOLD		);}
static float32_t fLevel_MaCuTh_Get(void){return fLevel_Get(	MASTER_CURRENT_THRESHOLD	);}
static float32_t fLevel_MoCuTh_Get(void){return fLevel_Get(	MONITOR_CURRENT_THRESHOLD	);}
static float32_t fLevel_SlCuLo_Get(void){return fLevel_Get(	SLAVE_CURRENT_LOW			);}
static float32_t fLevel_SlCuHi_Get(void){return fLevel_Get(	SLAVE_CURRENT_HIGH			);}
static float32_t fLevel_MaVoLo_Get(void){return fLevel_Get(	MASTER_VOLTAGE_LOW			);}
static float32_t fLevel_MaVoHi_Get(void){return fLevel_Get(	MASTER_VOLTAGE_HIGH			);}
static float32_t fLevel_MoVoTh_Get(void){return fLevel_Get(	MONITOR_VOLTAGE_THRESHOLD	);}
static float32_t fLevel_SlVoTh_Get(void){return fLevel_Get(	SLAVE_VOLTAGE_THRESHOLD		);}


MODBUS_TABLE RegisterTable[]=
{
	//				ubQuantityOfRegisters
	//	uwStartingAddress	ubFormat	,	Get() or NULL													Set() or NULL
	{	0x0000	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_DeviceSignatureGet	}	,	{NULL											}	},
	{	0x0001	,	1	,	MBR_U16		,	{.pRead_uint8	=	ubModbusAddress_Get					}	,	{NULL											}	},
	{	0x0002	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_HardwareRevisionGet	}	,	{NULL											}	},
	{	0x0103	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_FirmwareRevisionGet	}	,	{NULL											}	},
	{	0x0107	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_SystemClockGet		}	,	{NULL											}	},
	{	0x0108	,	1	,	MBR_U16		,	{.pRead_uint8	=	ubSystemControl_DeviceStatusGet		}	,	{NULL											}	},
	{	0x0109	,	1	,	MBR_U16		,	{.pRead_uint8	=	SystemControl_ErrorCodeGet			}	,	{NULL											}	},
	{	0x0601	,	1	,	MBR_U16		,	{NULL													}	,	{.pWrite_uint16	=	bDAC_CH1Value_Set			}	},
	{	0x0602	,	1	,	MBR_U16		,	{NULL													}	,	{.pWrite_uint16	=	bDAC_CH2Value_Set			}	},
	{	0x0603	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwADC_ADC_Current_Get				}	,	{NULL											}	},
	{	0x0604	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwADC_ADC_Voltage_Get				}	,	{NULL											}	},
	{	0x0605	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwADC_ADC_Current_Thermostat_Get	}	,	{NULL											}	},
	{	0x0606	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwADC_ADC_Voltage_Thermostat_Get	}	,	{NULL											}	},
	{	0x0607	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwADC_ADC_Voltage_Monitor_Get		}	,	{NULL											}	},
	{	0x0608	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwADC_ADC_Current_Monitor_Get		}	,	{NULL											}	},
	{	0x0610	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_MaVoLo_Get					}	,	{.pWrite_float	=	bLevel_MaVoLo_Set			}	},
	{	0x0612	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_MaVoHi_Get					}	,	{.pWrite_float	=	bLevel_MaVoHi_Set			}	},								
	{	0x0614	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_SlCuLo_Get					}	,	{.pWrite_float	=	bLevel_SlCuLo_Set			}	},							
	{	0x0616	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_SlCuHi_Get					}	,	{.pWrite_float	=	bLevel_SlCuHi_Set			}	},
	{	0x0618	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_MaCuTh_Get					}	,	{.pWrite_float	=	bLevel_MaCuTh_Set			}	},
	{	0x061A	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_MoCuTh_Get					}	,	{.pWrite_float	=	bLevel_MoCuTh_Set			}	},								
	{	0x061C	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_MoVoTh_Get					}	,	{.pWrite_float	=	bLevel_MoVoTh_Set			}	},							
	{	0x061E	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fLevel_SlVoTh_Get					}	,	{.pWrite_float	=	bLevel_SlVoTh_Set			}	},
};

#define LINES_IN_MODBUS_TABLE sizeof(RegisterTable)/sizeof(MODBUS_TABLE)

MODBUS_TABLE * pModbusTable_Row_Get(uint16_t luwStartingAddress)
{
	for(int16_t luwRow=0;luwRow!=LINES_IN_MODBUS_TABLE;luwRow++)
	{
		if (RegisterTable[luwRow].uwStartingAddress==luwStartingAddress)
		{
			return &RegisterTable[luwRow];
		}
	}
	return NULL;	// luwStartingAddress not found in RegisterTable[]
}
	



