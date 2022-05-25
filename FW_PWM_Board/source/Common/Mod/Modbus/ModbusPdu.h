/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-03-27           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: ModbusPdu.h
;
;******************************************************************************
; SVN header
;  $Id: ModbusPdu.h 106864 2020-03-30 16:02:58Z Stepanek, Michal $
******************************************************************************/


// Exception Codes (page 48)
#define	MODBUS_EXCEPTIONCODE_01_ILLEGALFUNCTION				0x01
#define	MODBUS_EXCEPTIONCODE_02_ILLEGALDATAADDRESS			0x02
#define	MODBUS_EXCEPTIONCODE_03_ILLEGALDATAVALUE			0x03
#define	MODBUS_EXCEPTIONCODE_04_DEVICEFAILURE				0x04


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
uint8_t ModbusPdu_Do(uint8_t * pPdu, uint8_t lubRequestSize, uint8_t lubResponseSizeMax);


