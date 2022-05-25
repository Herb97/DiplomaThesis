/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: PwmInput.C
;
*/


#include "..\App\DutyCycle.H"
#include".\PwmInput.H"						// OWN header


float32_t fPwmInput_DutyCycle_Get_0(void){return fDutyCycle_Get(0x00);}
float32_t fPwmInput_DutyCycle_Get_1(void){return fDutyCycle_Get(0x01);}
float32_t fPwmInput_DutyCycle_Get_2(void){return fDutyCycle_Get(0x02);}
float32_t fPwmInput_DutyCycle_Get_3(void){return fDutyCycle_Get(0x03);}
float32_t fPwmInput_DutyCycle_Get_4(void){return fDutyCycle_Get(0x04);}
float32_t fPwmInput_DutyCycle_Get_5(void){return fDutyCycle_Get(0x05);}
float32_t fPwmInput_DutyCycle_Get_6(void){return fDutyCycle_Get(0x06);}
float32_t fPwmInput_DutyCycle_Get_7(void){return fDutyCycle_Get(0x07);}
float32_t fPwmInput_DutyCycle_Get_8(void){return fDutyCycle_Get(0x08);}
float32_t fPwmInput_DutyCycle_Get_9(void){return fDutyCycle_Get(0x09);}
float32_t fPwmInput_DutyCycle_Get_A(void){return fDutyCycle_Get(0x0A);}
float32_t fPwmInput_DutyCycle_Get_B(void){return fDutyCycle_Get(0x0B);}
float32_t fPwmInput_DutyCycle_Get_C(void){return fDutyCycle_Get(0x0C);}
float32_t fPwmInput_DutyCycle_Get_D(void){return fDutyCycle_Get(0x0D);}
float32_t fPwmInput_DutyCycle_Get_E(void){return fDutyCycle_Get(0x0E);}
float32_t fPwmInput_DutyCycle_Get_F(void){return fDutyCycle_Get(0x0F);}
float32_t fPwmInput_Frequency_Get_0(void){return fFrequency_Get(0x00);}
float32_t fPwmInput_Frequency_Get_1(void){return fFrequency_Get(0x01);}
float32_t fPwmInput_Frequency_Get_2(void){return fFrequency_Get(0x02);}
float32_t fPwmInput_Frequency_Get_3(void){return fFrequency_Get(0x03);}
float32_t fPwmInput_Frequency_Get_4(void){return fFrequency_Get(0x04);}
float32_t fPwmInput_Frequency_Get_5(void){return fFrequency_Get(0x05);}
float32_t fPwmInput_Frequency_Get_6(void){return fFrequency_Get(0x06);}
float32_t fPwmInput_Frequency_Get_7(void){return fFrequency_Get(0x07);}
float32_t fPwmInput_Frequency_Get_8(void){return fFrequency_Get(0x08);}
float32_t fPwmInput_Frequency_Get_9(void){return fFrequency_Get(0x09);}
float32_t fPwmInput_Frequency_Get_A(void){return fFrequency_Get(0x0A);}
float32_t fPwmInput_Frequency_Get_B(void){return fFrequency_Get(0x0B);}
float32_t fPwmInput_Frequency_Get_C(void){return fFrequency_Get(0x0C);}
float32_t fPwmInput_Frequency_Get_D(void){return fFrequency_Get(0x0D);}
float32_t fPwmInput_Frequency_Get_E(void){return fFrequency_Get(0x0E);}
float32_t fPwmInput_Frequency_Get_F(void){return fFrequency_Get(0x0F);}


uint16_t uwPwmInput_DutyCycle_Get_0(void){return uwDutyCycle_Get(0x00);}
uint16_t uwPwmInput_DutyCycle_Get_1(void){return uwDutyCycle_Get(0x01);}
uint16_t uwPwmInput_DutyCycle_Get_2(void){return uwDutyCycle_Get(0x02);}
uint16_t uwPwmInput_DutyCycle_Get_3(void){return uwDutyCycle_Get(0x03);}
uint16_t uwPwmInput_DutyCycle_Get_4(void){return uwDutyCycle_Get(0x04);}
uint16_t uwPwmInput_DutyCycle_Get_5(void){return uwDutyCycle_Get(0x05);}
uint16_t uwPwmInput_DutyCycle_Get_6(void){return uwDutyCycle_Get(0x06);}
uint16_t uwPwmInput_DutyCycle_Get_7(void){return uwDutyCycle_Get(0x07);}
uint16_t uwPwmInput_DutyCycle_Get_8(void){return uwDutyCycle_Get(0x08);}
uint16_t uwPwmInput_DutyCycle_Get_9(void){return uwDutyCycle_Get(0x09);}
uint16_t uwPwmInput_DutyCycle_Get_A(void){return uwDutyCycle_Get(0x0A);}
uint16_t uwPwmInput_DutyCycle_Get_B(void){return uwDutyCycle_Get(0x0B);}
uint16_t uwPwmInput_DutyCycle_Get_C(void){return uwDutyCycle_Get(0x0C);}
uint16_t uwPwmInput_DutyCycle_Get_D(void){return uwDutyCycle_Get(0x0D);}
uint16_t uwPwmInput_DutyCycle_Get_E(void){return uwDutyCycle_Get(0x0E);}
uint16_t uwPwmInput_DutyCycle_Get_F(void){return uwDutyCycle_Get(0x0F);}
uint16_t uwPwmInput_Frequency_Get_0(void){return uwFrequency_Get(0x00);}
uint16_t uwPwmInput_Frequency_Get_1(void){return uwFrequency_Get(0x01);}
uint16_t uwPwmInput_Frequency_Get_2(void){return uwFrequency_Get(0x02);}
uint16_t uwPwmInput_Frequency_Get_3(void){return uwFrequency_Get(0x03);}
uint16_t uwPwmInput_Frequency_Get_4(void){return uwFrequency_Get(0x04);}
uint16_t uwPwmInput_Frequency_Get_5(void){return uwFrequency_Get(0x05);}
uint16_t uwPwmInput_Frequency_Get_6(void){return uwFrequency_Get(0x06);}
uint16_t uwPwmInput_Frequency_Get_7(void){return uwFrequency_Get(0x07);}
uint16_t uwPwmInput_Frequency_Get_8(void){return uwFrequency_Get(0x08);}
uint16_t uwPwmInput_Frequency_Get_9(void){return uwFrequency_Get(0x09);}
uint16_t uwPwmInput_Frequency_Get_A(void){return uwFrequency_Get(0x0A);}
uint16_t uwPwmInput_Frequency_Get_B(void){return uwFrequency_Get(0x0B);}
uint16_t uwPwmInput_Frequency_Get_C(void){return uwFrequency_Get(0x0C);}
uint16_t uwPwmInput_Frequency_Get_D(void){return uwFrequency_Get(0x0D);}
uint16_t uwPwmInput_Frequency_Get_E(void){return uwFrequency_Get(0x0E);}
uint16_t uwPwmInput_Frequency_Get_F(void){return uwFrequency_Get(0x0F);}