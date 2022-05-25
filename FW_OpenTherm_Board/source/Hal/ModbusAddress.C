/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: ModbusAddress.C
;
;******************************************************************************
; SVN header
;  $Id: ModbusAddress.C 114015 2021-07-09 11:46:49Z Stepanek, Michal $
******************************************************************************/

/*
OpenTherm board revision A
https://subversion.resideo.com/ECC/CombustionEMEA/Root/PCB/CS21xxxx/210003

INPUT PULL_UP:
BIT 0	PD14	inverted
BIT 1	PD12	inverted
BIT 2	PD15	inverted
BIT 3	PD13	inverted

Modbus_over_serial_line_V1_02.pdf page 7:
	Each MODBUS slave must have an unique address (from 1 to 247) so that it can be addressed independently from other nodes.
*/

#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_gpio.h"
#include "..\Hal\GPIO.H"					// GPIO_Input_PullUp()
#include ".\ModbusAddress.H"				// OWN header


/**
  * @brief MODBUS address related GPIO Initialization Function
  * @param None
  * @retval None
  */
void ModbusAddress_Init(void)
{
	GPIO_Input_PullUp(GPIOD, LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15);
}

/**
  * @brief Reading of MODBUS address from pins PD8..11
  * @param None
  * @retval MODBUS address 1..16	(0 on switch is decoded as 16)
  */
uint8_t ubModbusAddress_Get(void)
{
	uint16_t x;
	x = ~GPIOD->IDR;		// inversion
	x = ((x&BIT14)?BIT0:0)|((x&BIT12)?BIT1:0)|((x&BIT15)?BIT2:0)|((x&BIT13)?BIT3:0);		// rearrange bits
	if (0==x)
	{
		x = 16;		// slave address 0 is not allowed
	}
	return x;
}
