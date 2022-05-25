/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-03-29           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: ModbusAddress.C
;
*/

/*
HW Pwm Board STM32F446 Revision A

Modbus Slave address switch connected to ADC

Modbus_over_serial_line_V1_02.pdf page 7:
	Each MODBUS slave must have an unique address (from 1 to 247) so that it can be addressed independently from other nodes.
*/

#include "..\Hal\ADC.H"						// uwADC_ADC_PA1_Get(), uwADC_ADC_PA3_Get()
#include ".\ModbusAddress.h"				// OWN header


/**
  * @brief MODBUS address related GPIO Initialization Function
  * @param None
  * @retval None
  */
void ModbusAddress_Init(void)
{
    
}


/*
ADC1_IN1		ADC1_IN3

1		8		4		2		Voltage		Division
=============================================
0		0		0		0		3.30		4095
0		1		0		1		2.20		2730
1		0		1		0		1.65		2047
1		1		1		1		1.32		1638
*/
static uint8_t ubDivisionToCouple(uint16_t luwDiv)
{
	if (luwDiv>3412)
	{
		return 0;
	}
	else if(luwDiv>2388)
	{
		return 1;
	}
	else if(luwDiv>1842)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}


/**
  * @brief Reading of MODBUS address
  * @param None
  * @retval MODBUS address 1..16	(0 on switch is decoded as 16)
  */
uint8_t ubModbusAddress_Get(void)
{
	uint8_t lubAddress;
	uint8_t Bit_1_8 = ubDivisionToCouple(uwADC_Data_Get(1));	// PA1   ------> ADC1_IN1
	uint8_t Bit_4_2 = ubDivisionToCouple(uwADC_Data_Get(3));	// PA3   ------> ADC1_IN3
	lubAddress = Bit_4_2<<1;
	if (Bit_1_8&BIT0)
	{
		lubAddress += 8;
	}
	if (Bit_1_8&BIT1)
	{
		lubAddress += 1;
	}
	if (0==lubAddress)
	{
		lubAddress = 16;		// slave address 0 is not allowed
	}
	return lubAddress;
}

