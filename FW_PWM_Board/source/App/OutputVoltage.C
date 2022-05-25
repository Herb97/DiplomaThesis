/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OutputVoltage.C
;
*/


/*
TODO:
Add driving of DC/DC converter output voltage.
Add reading back of real output voltage.
*/


#include ".\OutputVoltage.H"				// OWN header
#include "..\Common\Drv\Mcu\STM32F4xx\stm32f4xx_ll_gpio.h"	// LL_GPIO_PIN_..
#include "..\Hal\GPIO.H"					// GPIO_Output_PushPull_FreqLow()
#include "..\Hal\ADC.H"						// ADC_Init(), uwADC_Data_Get()

/******************************************************************************
;
; Variables
;
******************************************************************************/

enum
{
	OUTPUTVOLTAGE_OFF,		// output is OFF
	OUTPUTVOLTAGE_IDLE,		// output is Requested state
	OUTPUTVOLTAGE_WAIT,		// wait for decrease of voltage at the output of step-up converter (which is off right now)
	
} mOutputVoltage_State = OUTPUTVOLTAGE_OFF;

uint8_t mubOutputVoltage_Requested = 0u/*OFF*/;
uint8_t mubOutputVoltage_Current = 0u/*OFF*/;

/******************************************************************************
;
; HW related part
;
******************************************************************************/
/*

DCDC_Set0 PB15
DCDC_Set1 PB13
DCDC_Set2 PB12
DCDC_Set3 PB10
DCDC_Set4 PB2
PWR_EN PA11

*/

#define SET0_ON		do {GPIOB->BSRR = BIT15;}while(0)
#define SET1_ON		do {GPIOB->BSRR = BIT13;}while(0)
#define SET2_ON		do {GPIOB->BSRR = BIT12;}while(0)
#define SET3_ON		do {GPIOB->BSRR = BIT10;}while(0)
#define SET4_ON		do {GPIOB->BSRR = BIT2;}while(0)

#define SET0_OFF	do {GPIOB->BSRR = BIT15<<16;}while(0)
#define SET1_OFF	do {GPIOB->BSRR = BIT13<<16;}while(0)
#define SET2_OFF	do {GPIOB->BSRR = BIT12<<16;}while(0)
#define SET3_OFF	do {GPIOB->BSRR = BIT10<<16;}while(0)
#define SET4_OFF	do {GPIOB->BSRR = BIT2<<16;}while(0)

#define PWR_ON		do {GPIOA->BSRR = BIT11;}while(0)
#define PWR_OFF		do {GPIOA->BSRR = BIT11<<16;}while(0)

/**
  * @brief 
  * @param ...
  * @retval ...
  */

void OutputVoltage_Init(void)
{
	GPIO_Output_PushPull_FreqLow(GPIOB,
		LL_GPIO_PIN_2 |
		LL_GPIO_PIN_10 | 
		LL_GPIO_PIN_12 |
		LL_GPIO_PIN_13 | 
		LL_GPIO_PIN_15 );
	
	GPIO_Output_PushPull_FreqLow(GPIOA,
		LL_GPIO_PIN_11 );
	
	PWR_OFF;
}

static void MakeModification(uint8_t lubRequest)
{
	// only BIT4..0 are considered
	if (lubRequest > 31u)
	{
		lubRequest = 31u;
	}
	mubOutputVoltage_Current = lubRequest;

	if (0u == lubRequest)
	{
		PWR_OFF;
	}
	else
	{
		if((lubRequest & BIT4)){
            SET4_ON;
        } else {
            SET4_OFF;
        }
        if((lubRequest & BIT3)){
            SET3_ON;
        } else {
            SET3_OFF;
        }
        if((lubRequest & BIT2)){
            SET2_ON;
        } else {
            SET2_OFF;
        }
        if((lubRequest & BIT1)){
            SET1_ON;
        } else {
            SET1_OFF;
        }
        if((lubRequest & BIT0)){
            SET0_ON;
        } else {
            SET0_OFF;
        }
        PWR_ON;
    }
}


/******************************************************************************
;
; Output volatage measurement
;
******************************************************************************/

/**
  * @brief Measuring of output voltage
  * @param none
  * @retval Output in Volts
  */
float32_t fOutputVoltage_Read(void)
{
	float32_t f = (float32_t)uwADC_Data_Get(9);
	f = f/4095.0f*3.3f*12.0f;	// full scale 4095[div] .. 3.3[V] at ADC input .. divider 1:12, maximum measured voltage 12*3.3=39.6[V]
	return f;
}

/**
  * @brief Bridge to fOutputVoltage_Read()
  * @param none
  * @retval Output in mV, whole number 16 bits wide
  */
uint16_t uwOutputVoltage_Read(void)
{
	float32_t f;
	f = fOutputVoltage_Read()*1000.0f;	// Convert from V to mV
	return (uint16_t)f;
}



/******************************************************************************
;
; Conversion between CODE for DCDC_Set4 to DCDC_Set0 and Voltage
;

Coding:
	BIT4..0
		code	Voltage (see ..\SVN_DATA_ROOT\PCB\CS21xxxx\210012\PowerSupply Simulation\PwmBoard_StepUp_V2.xlsx)
		 0		1,2  	(used also for output switch OFF)
		 1		1,95 
		 2		2,7  
		 3		3,45 
		 4		4,2  
		 5		4,95 
		 6		5,7  
		 7		6,45 
		 8		7,2  
		 9		7,95 
		10		8,7  
		11		9,45 
		12		10,2 
		13		10,95
		14		11,7 
		15		12,45
		16		13,2 
		17		13,95
		18		14,7 
		19		15,45
		20		16,2 
		21		16,95
		22		17,7 
		23		18,45
		24		19,2 
		25		19,95
		26		20,7 
		27		21,45
		28		22,2 
		29		22,95
		30		23,7 
		31		24,45

******************************************************************************/

static uint8_t ubCodeFromVoltage(float lfVoltage)
{
	float32_t f = (lfVoltage - 1.2f)/0.75f;
	uint8_t lubCode = (uint8_t)f;
	if (lubCode > 31)
	{
		lubCode = 31;
	}
	return lubCode;
}

static float32_t fVoltageFromCode(uint8_t lubCode)
{
	return ((float32_t)lubCode)*0.75f+1.2f;
}

/******************************************************************************
;
; Output volatage STATE MACHINE
;
******************************************************************************/
void OutputVoltage_StateMachine(void)
{
	switch (mOutputVoltage_State)
	{
		case OUTPUTVOLTAGE_IDLE:		// output is Requested state
			if (mubOutputVoltage_Requested == 0u)
			{
				// there is request to switch OFF the step-up converter
				MakeModification(0);
				mOutputVoltage_State = OUTPUTVOLTAGE_OFF;
			}
			else if (mubOutputVoltage_Requested != mubOutputVoltage_Current)
			{
				// there is request to change output voltage, switch OFF and go to OUTPUTVOLTAGE_WAIT
				MakeModification(0);
				mOutputVoltage_State = OUTPUTVOLTAGE_WAIT;
			}
			else
			{
				// no request to change
				// stay in OUTPUTVOLTAGE_IDLE
			}
		break;
		case OUTPUTVOLTAGE_WAIT:		// wait for decrease of voltage at the output of step-up converter (which is off right now)
		{
			float32_t lfExpectedVoltage = fVoltageFromCode(mubOutputVoltage_Requested);
			float32_t lfMeasuredVoltage = fOutputVoltage_Read();
			if (lfMeasuredVoltage < lfExpectedVoltage)
			{
				MakeModification(mubOutputVoltage_Requested);
				mOutputVoltage_State = OUTPUTVOLTAGE_IDLE;
			}
			else
			{
				// wait for output voltage to drop
				// stay in OUTPUTVOLTAGE_WAIT
			}
		}
		break;
		case OUTPUTVOLTAGE_OFF:		// output is OFF
		default:
			if (mubOutputVoltage_Requested > 0u)
			{
				mOutputVoltage_State = OUTPUTVOLTAGE_WAIT;
				// there is request to switch on the step-up converter
			}
			else
			{
				// stay in OUTPUTVOLTAGE_OFF state
			}
		break;
	}
}

bool bOutputVoltage_Set(float32_t lfOutputVoltage)
{
    if((lfOutputVoltage >= 4.0f) & (lfOutputVoltage <= 26.0f))
    {
		mubOutputVoltage_Requested = ubCodeFromVoltage(lfOutputVoltage);
		return true;
	}
	else
	{
		return false;
	}
}

bool bOutputVoltage_Set_mV(uint16_t luwOutputVoltage)
{
	float32_t f = luwOutputVoltage;
	f /= 1000.0f; // Convert from mV to V
	return bOutputVoltage_Set(f);
}

