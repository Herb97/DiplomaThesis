/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-09-16           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OpenThermHal.C
;
*/

/*
	PA2	ADC_IN2		MASTER		ADC_CURRENT_CONTROLLER
	PA3	ADC_IN3		MASTER		ADC_VOLTAGE_CONTROLLER
	PA4 DAC_OUT1	MASTER		DAC_VOLTAGE
	PA5	DAC_OUT2	SLAVE		DAC_CURRENT_THERMOSTAT
	PB0	ADC_IN8		SLAVE		ADC_CURRENT_THERMOSTAT
	PB1	ADC_IN9		SLAVE		ADC_VOLTAGE_THERMOSTAT
	PC0	ADC_IN10	MONITOR		ADC_VOLTAGE_MONITOR
	PC1	ADC_IN11	MONITOR		ADC_CURRENT_MONITOR

LEDs:
	R - wrong polarity, see Polarity.C
	G - Voltage monitor - communication from master/thermostat to slave/controller
	B - interrupt duration
	Y - Current monitor - communication from slave/controller to master/thermostat
	
*/

/******************************************************************************
; INCLUDE FILES
;******************************************************************************/
#include <stdlib.h>								// abs()
#include "..\Common\Drv\Mcu\STM32L0xx\stm32l0xx_ll_tim.h"	
#include "..\Hal\ADC.H"							// uwADC_Data_Get()	
#include "..\Hal\DAC.H"							// bDAC_CH1Value_Set(), bDAC_CH2Value_Set()
#include "..\Hal\Timer.H"						// uwTimer_TimeStamp_1us_Get()
#include "..\App\OpenThermMonitor.H"			// OpenThermMonitor_100us()
#include "..\App\OpenThermMaster.H"				// OpenThermMaster_100us(), bOpenThermMaster_HalfBitTime()
#include "..\App\OpenThermSlave.H"				// OpenThermSlave_100us(), bOpenThermSlave_HalfBitTime()
#include "..\App\TestTool.H"					// TestToolMode_t, ubTestTool_Mode_Get()
#include "..\Hal\Threshold.H"					// uwLevel_Get()
#include ".\OpenThermHal.H"						// OWN header


/**
  * @brief 100 us timer interrupt handler 
  * @param None
  * @retval None
**/

void OpenThermHal_100us(void)
{
	bool lbCurrent;
	bool lbVoltage;
	int16_t lswCurrent;
	uint16_t luwCurrent;
	uint16_t luwVoltage;
	uint16_t luwTimeStamp = uwTimer_TimeStamp_1us_Get();
	switch (ubTestTool_Mode_Get())
	{
		case TESTTOOL_MODE_MONITOR:
			// Monitor, schematic page 6
			//	PC0	ADC_IN10	ADC_VOLTAGE_MONITOR
			//	PC1	ADC_IN11	ADC_CURRENT_MONITOR
			lswCurrent = abs(uwADC_Data_Get(ADC_CHSELR_CHSEL11)-2048u);	// 0..4095
			luwVoltage = uwADC_Data_Get(ADC_CHSELR_CHSEL10);	// 0..4095
			// Convert to logical level
			lbCurrent = (lswCurrent > uwLevel_Get(MONITOR_CURRENT_THRESHOLD)) ? 1u : 0u;		// threshold 12.5 mA 3072u-2048u
			lbVoltage = (luwVoltage > uwLevel_Get(MONITOR_VOLTAGE_THRESHOLD)) ? 1u : 0u;		// threshold 11.0 V 1800u
			OpenThermMonitor_100us(luwTimeStamp, lbCurrent, lbVoltage);
		break;
		case TESTTOOL_MODE_MASTER:
			// Master (thermostat), schematic page 5
			//	PA2	ADC_IN2		ADC_CURRENT_CONTROLLER
			//	PA3	ADC_IN3		ADC_VOLTAGE_CONTROLLER
			//	PA4 DAC_OUT1	DAC_VOLTAGE
			luwCurrent = uwADC_Data_Get(ADC_CHSELR_CHSEL2);	// 0..4095
//			luwVoltage = uwADC_Data_Get(ADC_CHSELR_CHSEL3);	// 0..4095
			// Convert to logical level
			lbCurrent = (luwCurrent > uwLevel_Get(MASTER_CURRENT_THRESHOLD)) ? 1u : 0u;		// threshold 12.5 mA 2000u uwLevel_SlaveCurrentHigh_Get()
			OpenThermMaster_100us(luwTimeStamp, lbCurrent);
		break;
		case TESTTOOL_MODE_SLAVE:
			// Slave (gas boiler), schematic page 4
			//	PB0	ADC_IN8		ADC_CURRENT_THERMOSTAT
			//	PB1	ADC_IN9		ADC_VOLTAGE_THERMOSTAT
			//	PA5	DAC_OUT2	DAC_CURRENT_THERMOSTAT
//			luwCurrent = uwADC_Data_Get(ADC_CHSELR_CHSEL8);	// 0..4095
			luwVoltage = uwADC_Data_Get(ADC_CHSELR_CHSEL9);	// 0..4095
			lbVoltage = (luwVoltage > uwLevel_Get(SLAVE_VOLTAGE_THRESHOLD)) ? 1u : 0u;		// threshold 11.0 V uwLevel_MasterVoltageHigh_Get()
			OpenThermSlave_100us(luwTimeStamp, lbVoltage);
		break;
		default:
		break;
	}
}


/******************************************************************************
; Procedure     : OpenThermHal_HalfBitTime()
; Description   : HalfBitTime interrupt
; Input         : -
; Output        : -
;*****************************************************************************/
void OpenThermHal_HalfBitTime(void)
{
	uint16_t luwVoltage;
	uint16_t luwCurrent;
	switch (ubTestTool_Mode_Get())
	{
		case TESTTOOL_MODE_MASTER:
			// Master (thermostat), schematic page 5
			//	PA4 DAC_OUT1	DAC_VOLTAGE
			if (bOpenThermMaster_HalfBitTime())
			{
				luwVoltage = uwLevel_Get(MASTER_VOLTAGE_HIGH);
			}
			else
			{
				luwVoltage = uwLevel_Get(MASTER_VOLTAGE_LOW);
			}
			bDAC_CH1Value_Set(luwVoltage);
		break;
		case TESTTOOL_MODE_SLAVE:
			// Slave (gas boiler), schematic page 4
			// 	PA5	DAC_OUT2	DAC_CURRENT_THERMOSTAT
			// convert logical value to DAC value (current)
			if (bOpenThermSlave_HalfBitTime())
			{
				luwCurrent = uwLevel_Get(SLAVE_CURRENT_HIGH);
			}
			else
			{
				luwCurrent = uwLevel_Get(SLAVE_CURRENT_LOW);
			}
			
			bDAC_CH2Value_Set(luwCurrent);
		break;
		default:
		break;
	}
}
