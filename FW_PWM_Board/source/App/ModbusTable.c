/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: ModbusTable.C
;
;******************************************************************************
; SVN header
;  $Id: ModbusTable.c 117357 2022-03-09 14:40:36Z Herbrych, Vojtech $
******************************************************************************/

/*
It is not a final solution, it can be rearanged to simplify multiple read or write.
*/

#include "..\Common\Mod\Modbus\ModbusRegisterMapping.H"	// MBR_FORMAT, MODBUS_TABLE
#include "..\Common\Drv\SystemControl\SystemControl.H"	// uwSystemControl_DeviceSignatureGet(), uwSystemControl_HardwareRevisionGet(), uwSystemControl_FirmwareRevisionGet(), uwSystemControl_SystemClockGet(), ubSystemControl_DeviceStatusGet(), SystemControl_ErrorCodeGet()
#include "..\Hal\ModbusAddress.H"			// ubModbusAddress_Get()
#include "..\App\DigitalInput.H"			// uwDigitalInput_RawData_Get(), uwDigitalInput_FilteredData_Get(), uwDigitalInput_Polarity_Get(), bDigitalInput_Polarity_Set()
#include "..\App\DutyCycle.H"				// fDutyCycle_Get(), fFrequency_Get(), uwDutyCycle_Get(), uwFrequency_Get()
#include "..\App\PwmInput.H"
#include "..\App\PwmOutput.H"
#include "..\App\InputThreshold.H"
#include "..\App\OutputVoltage.H"
#include "..\App\OutputType.H"

MODBUS_TABLE RegisterTable[]=
{
	//				ubQuantityOfRegisters
	//	uwStartingAddress	ubFormat	,	Get() or NULL													Set() or NULL

	{	0x0000	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_DeviceSignatureGet	}	,	{NULL										}},
	{	0x0001	,	1	,	MBR_U8		,	{.pRead_uint8	=	ubModbusAddress_Get					}	,	{NULL										}},
	{	0x0002	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_HardwareRevisionGet	}	,	{NULL										}},

	{	0x0101	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwDigitalInput_RawData_Get			}	,	{NULL										}	},
	{	0x0102	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwDigitalInput_FilteredData_Get		}	,	{NULL										}	},

	{	0x0103	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_FirmwareRevisionGet	}	,	{NULL										}},
	{	0x0107	,	1	,	MBR_U16		,	{.pRead_uint16	=	uwSystemControl_SystemClockGet		}	,	{NULL										}},
	{	0x0108	,	1	,	MBR_U8		,	{.pRead_uint8	=	ubSystemControl_DeviceStatusGet		}	,	{NULL										}},
	{	0x0109	,	1	,	MBR_U8		,	{.pRead_uint8	=	SystemControl_ErrorCodeGet			}	,	{NULL										}},

	{	0x0430	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_0					}	,	{.pWrite_uint16	=	bOutputType_Set_0		}},
	{	0x0431	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_1					}	,	{.pWrite_uint16	=	bOutputType_Set_1		}},
	{	0x0432	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_2					}	,	{.pWrite_uint16	=	bOutputType_Set_2		}},
	{	0x0433	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_3					}	,	{.pWrite_uint16	=	bOutputType_Set_3		}},
	{	0x0434	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_4					}	,	{.pWrite_uint16	=	bOutputType_Set_4		}},
	{	0x0435	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_5					}	,	{.pWrite_uint16	=	bOutputType_Set_5		}},
	{	0x0436	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_6					}	,	{.pWrite_uint16	=	bOutputType_Set_6		}},
	{	0x0437	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_7					}	,	{.pWrite_uint16	=	bOutputType_Set_7		}},
	{	0x0438	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_8					}	,	{.pWrite_uint16	=	bOutputType_Set_8		}},
	{	0x0439	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_9					}	,	{.pWrite_uint16	=	bOutputType_Set_9		}},
	{	0x043A	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_A					}	,	{.pWrite_uint16	=	bOutputType_Set_A		}},
	{	0x043B	,	1	,	MBR_U16	    ,	{.pRead_uint16	=	uwOutputType_Get_B					}	,	{.pWrite_uint16	=	bOutputType_Set_B		}},

	{	0x0440	,	2	,	MBR_FLOAT   ,	{.pRead_float	=	fOutputVoltage_Read					}	,	{NULL}},
	{	0x0442	,	2	,	MBR_FLOAT	,	{NULL													}	,	{.pWrite_float	=	bOutputVoltage_Set		}},

	{	0x0450	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fInputThreshold_Get_0				}	,	{.pWrite_float	=	bInputThreshold_Set_0	}},
	{	0x0452	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fInputThreshold_Get_1				}	,	{.pWrite_float	=	bInputThreshold_Set_1	}},

	{	0x0480	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_0			}	,	{NULL										}},
	{	0x0482	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_1			}	,	{NULL										}},
	{	0x0484	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_2			}	,	{NULL										}},
	{	0x0486	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_3			}	,	{NULL										}},
	{	0x0488	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_4			}	,	{NULL										}},
	{	0x048A	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_5			}	,	{NULL										}},
	{	0x048C	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_6			}	,	{NULL										}},
	{	0x048E	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_7			}	,	{NULL										}},
	{	0x0490	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_8			}	,	{NULL										}},
	{	0x0492	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_9			}	,	{NULL										}},
	{	0x0494	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_A			}	,	{NULL										}},
	{	0x0496	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_B			}	,	{NULL										}},
	{	0x0498	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_C			}	,	{NULL										}},
	{	0x049A	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_D			}	,	{NULL										}},
	{	0x049C	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_E			}	,	{NULL										}},
	{	0x049E	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_DutyCycle_Get_F			}	,	{NULL										}},

	{	0x04A0	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_0			}	,	{NULL										}},
	{	0x04A2	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_1			}	,	{NULL										}},
	{	0x04A4	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_2			}	,	{NULL										}},
	{	0x04A6	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_3			}	,	{NULL										}},
	{	0x04A8	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_4			}	,	{NULL										}},
	{	0x04AA	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_5			}	,	{NULL										}},
	{	0x04AC	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_6			}	,	{NULL										}},
	{	0x04AE	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_7			}	,	{NULL										}},
	{	0x04B0	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_8			}	,	{NULL										}},
	{	0x04B2	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_9			}	,	{NULL										}},
	{	0x04B4	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_A			}	,	{NULL										}},
	{	0x04B6	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_B			}	,	{NULL										}},
	{	0x04B8	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_C			}	,	{NULL										}},
	{	0x04BA	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_D			}	,	{NULL										}},
	{	0x04BC	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_E			}	,	{NULL										}},
	{	0x04BE	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmInput_Frequency_Get_F			}	,	{NULL										}},

	{	0x04C0	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_0			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_0	}},
	{	0x04C2	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_1			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_1	}},
	{	0x04C4	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_2			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_2	}},
	{	0x04C6	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_3			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_3	}},
	{	0x04C8	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_4			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_4	}},
	{	0x04CA	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_5			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_5	}},
	{	0x04CC	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_6			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_6	}},
	{	0x04CE	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_7			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_7	}},
	{	0x04D0	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_8			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_8	}},
	{	0x04D2	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_9			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_9	}},
	{	0x04D4	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_A			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_A	}},
	{	0x04D6	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_Frequency_Get_B			}	,	{.pWrite_float	=	bPwmOutput_Frequency_Set_B	}},

	{	0x04E0	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_0			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_0	}},
	{	0x04E2	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_1			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_1	}},
	{	0x04E4	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_2			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_2	}},
	{	0x04E6	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_3			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_3	}},
	{	0x04E8	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_4			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_4	}},
	{	0x04EA	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_5			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_5	}},
	{	0x04EC	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_6			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_6	}},
	{	0x04EE	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_7			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_7	}},
	{	0x04F0	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_8			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_8	}},
	{	0x04F2	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_9			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_9	}},
	{	0x04F4	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_A			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_A	}},
	{	0x04F6	,	2	,	MBR_FLOAT	,	{.pRead_float	=	fPwmOutput_DutyCycle_Get_B			}	,	{.pWrite_float	=	bPwmOutput_DutyCycle_Set_B	}},
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
	



