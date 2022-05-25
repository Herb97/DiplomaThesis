/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: OutputType.C
;
*/


/*
Add driving of PWM Output Type: Open Drain versus Push-Pull.
Use one or two (depending on number of outputs) 74HCT595 connected to SPI1.
Use the TLP222A solid state relay on every PWM output.

Todo: correct assignment of muwOutputType bits to PWMx_SELECT, see schematic.

*/


#include"..\Hal\TPIC6C595.H"				// TPIC6C595_WriteWord()
#include".\OutputType.H"					// OWN header


uint16_t muwOutputType = 0;

uint16_t uwOutputType_Get_0(void){return 1u&(muwOutputType>>0x00);}
uint16_t uwOutputType_Get_1(void){return 1u&(muwOutputType>>0x01);}
uint16_t uwOutputType_Get_2(void){return 1u&(muwOutputType>>0x02);}
uint16_t uwOutputType_Get_3(void){return 1u&(muwOutputType>>0x03);}
uint16_t uwOutputType_Get_4(void){return 1u&(muwOutputType>>0x04);}
uint16_t uwOutputType_Get_5(void){return 1u&(muwOutputType>>0x05);}
uint16_t uwOutputType_Get_6(void){return 1u&(muwOutputType>>0x06);}
uint16_t uwOutputType_Get_7(void){return 1u&(muwOutputType>>0x07);}
uint16_t uwOutputType_Get_8(void){return 1u&(muwOutputType>>0x08);}
uint16_t uwOutputType_Get_9(void){return 1u&(muwOutputType>>0x09);}
uint16_t uwOutputType_Get_A(void){return 1u&(muwOutputType>>0x0A);}
uint16_t uwOutputType_Get_B(void){return 1u&(muwOutputType>>0x0B);}

bool bOutputType_Set(uint16_t luwValueToWrite, uint8_t lubIndex)
{
	if (luwValueToWrite)
	{
		// set
		muwOutputType|=1u<<lubIndex;
	}
	else
	{
		// reset
		muwOutputType&=~(1u<<lubIndex);
	}
	return true;
}

bool bOutputType_Set_0(uint16_t x){return bOutputType_Set(x,0x00);}
bool bOutputType_Set_1(uint16_t x){return bOutputType_Set(x,0x01);}
bool bOutputType_Set_2(uint16_t x){return bOutputType_Set(x,0x02);}
bool bOutputType_Set_3(uint16_t x){return bOutputType_Set(x,0x03);}
bool bOutputType_Set_4(uint16_t x){return bOutputType_Set(x,0x04);}
bool bOutputType_Set_5(uint16_t x){return bOutputType_Set(x,0x05);}
bool bOutputType_Set_6(uint16_t x){return bOutputType_Set(x,0x06);}
bool bOutputType_Set_7(uint16_t x){return bOutputType_Set(x,0x07);}
bool bOutputType_Set_8(uint16_t x){return bOutputType_Set(x,0x08);}
bool bOutputType_Set_9(uint16_t x){return bOutputType_Set(x,0x09);}
bool bOutputType_Set_A(uint16_t x){return bOutputType_Set(x,0x0A);}
bool bOutputType_Set_B(uint16_t x){return bOutputType_Set(x,0x0B);}

/**
  * @brief Refresh each of the OutputType
  * @param None
  * @retval None
  *
  * Called from main loop
  */
void OutputType_MainLoop(void)
{

/*
	IC7
	
	BIT0 - QA - NC
	BIT1 - QB - PWM0
	BIT2 - QC - PWM1
	BIT3 - QD - PWM2
	BIT4 - QE - PWM3
	BIT5 - QF - PWM4
	BIT6 - QG - PWM5
	BIT7 - QH - PWM6

	IC8

	BIT8  - QA - NC
	BIT9  - QB - PWM7
	BIT10 - QC - PWM8
	BIT11 - QD - PWM9
	BIT12 - QE - PWM10
	BIT13 - QF - PWM11
	BIT14 - QG - NC
	BIT15 - QH - NC
*/

	uint16_t luwResult;
	luwResult =
	((muwOutputType&BIT0)?BIT1:0)| 
	((muwOutputType&BIT1)?BIT2:0)| 
	((muwOutputType&BIT2)?BIT3:0)|
	((muwOutputType&BIT3)?BIT4:0)|
	((muwOutputType&BIT4)?BIT5:0)|
	((muwOutputType&BIT5)?BIT6:0)|
	((muwOutputType&BIT6)?BIT7:0)|
	((muwOutputType&BIT7)?BIT9:0)|
	((muwOutputType&BIT8)?BIT10:0)|
	((muwOutputType&BIT9)?BIT11:0)|
	((muwOutputType&BIT10)?BIT12:0)|
	((muwOutputType&BIT11)?BIT13:0); // rearrange bits
	
	TPIC6C595_WriteWord(luwResult);
}
