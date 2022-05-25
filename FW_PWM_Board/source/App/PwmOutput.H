/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: PwmOutput.H
;
;******************************************************************************
; SVN header
;  $Id: PwmOutput.H 117315 2022-03-07 12:30:14Z Herbrych, Vojtech $
******************************************************************************/


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void PwmOutput_Init(void);

float32_t fPwmOutput_Frequency_Get_0(void);
float32_t fPwmOutput_Frequency_Get_1(void);
float32_t fPwmOutput_Frequency_Get_2(void);
float32_t fPwmOutput_Frequency_Get_3(void);
float32_t fPwmOutput_Frequency_Get_4(void);
float32_t fPwmOutput_Frequency_Get_5(void);
float32_t fPwmOutput_Frequency_Get_6(void);
float32_t fPwmOutput_Frequency_Get_7(void);
float32_t fPwmOutput_Frequency_Get_8(void);
float32_t fPwmOutput_Frequency_Get_9(void);
float32_t fPwmOutput_Frequency_Get_A(void);
float32_t fPwmOutput_Frequency_Get_B(void);

float32_t fPwmOutput_DutyCycle_Get_0(void);
float32_t fPwmOutput_DutyCycle_Get_1(void);
float32_t fPwmOutput_DutyCycle_Get_2(void);
float32_t fPwmOutput_DutyCycle_Get_3(void);
float32_t fPwmOutput_DutyCycle_Get_4(void);
float32_t fPwmOutput_DutyCycle_Get_5(void);
float32_t fPwmOutput_DutyCycle_Get_6(void);
float32_t fPwmOutput_DutyCycle_Get_7(void);
float32_t fPwmOutput_DutyCycle_Get_8(void);
float32_t fPwmOutput_DutyCycle_Get_9(void);
float32_t fPwmOutput_DutyCycle_Get_A(void);
float32_t fPwmOutput_DutyCycle_Get_B(void);

bool bPwmOutput_Frequency_Set_0(float32_t f);
bool bPwmOutput_Frequency_Set_1(float32_t f);
bool bPwmOutput_Frequency_Set_2(float32_t f);
bool bPwmOutput_Frequency_Set_3(float32_t f);
bool bPwmOutput_Frequency_Set_4(float32_t f);
bool bPwmOutput_Frequency_Set_5(float32_t f);
bool bPwmOutput_Frequency_Set_6(float32_t f);
bool bPwmOutput_Frequency_Set_7(float32_t f);
bool bPwmOutput_Frequency_Set_8(float32_t f);
bool bPwmOutput_Frequency_Set_9(float32_t f);
bool bPwmOutput_Frequency_Set_A(float32_t f);
bool bPwmOutput_Frequency_Set_B(float32_t f);

bool bPwmOutput_Frequency_Set_4_u16(uint16_t in);
bool bPwmOutput_DutyCycle_Set_4_u16(uint16_t in);

bool bPwmOutput_DutyCycle_Set_0(float32_t f);
bool bPwmOutput_DutyCycle_Set_1(float32_t f);
bool bPwmOutput_DutyCycle_Set_2(float32_t f);
bool bPwmOutput_DutyCycle_Set_3(float32_t f);
bool bPwmOutput_DutyCycle_Set_4(float32_t f);
bool bPwmOutput_DutyCycle_Set_5(float32_t f);
bool bPwmOutput_DutyCycle_Set_6(float32_t f);
bool bPwmOutput_DutyCycle_Set_7(float32_t f);
bool bPwmOutput_DutyCycle_Set_8(float32_t f);
bool bPwmOutput_DutyCycle_Set_9(float32_t f);
bool bPwmOutput_DutyCycle_Set_A(float32_t f);
bool bPwmOutput_DutyCycle_Set_B(float32_t f);

uint16_t uwPwmOutput_Enable_Get_0(void);
uint16_t uwPwmOutput_Enable_Get_1(void);
uint16_t uwPwmOutput_Enable_Get_2(void);
uint16_t uwPwmOutput_Enable_Get_3(void);
uint16_t uwPwmOutput_Enable_Get_4(void);
uint16_t uwPwmOutput_Enable_Get_5(void);
uint16_t uwPwmOutput_Enable_Get_6(void);
uint16_t uwPwmOutput_Enable_Get_7(void);
uint16_t uwPwmOutput_Enable_Get_8(void);
uint16_t uwPwmOutput_Enable_Get_9(void);
uint16_t uwPwmOutput_Enable_Get_A(void);
uint16_t uwPwmOutput_Enable_Get_B(void);

bool bPwmOutput_Enable_Set_0(uint16_t x);

bool bPwmOutput_En_Set_0(void);

bool bPwmOutput_Enable_Set_1(uint16_t x);
bool bPwmOutput_Enable_Set_2(uint16_t x);
bool bPwmOutput_Enable_Set_3(uint16_t x);
bool bPwmOutput_Enable_Set_4(uint16_t x);
bool bPwmOutput_Enable_Set_5(uint16_t x);
bool bPwmOutput_Enable_Set_6(uint16_t x);
bool bPwmOutput_Enable_Set_7(uint16_t x);
bool bPwmOutput_Enable_Set_8(uint16_t x);
bool bPwmOutput_Enable_Set_9(uint16_t x);
bool bPwmOutput_Enable_Set_A(uint16_t x);
bool bPwmOutput_Enable_Set_B(uint16_t x);
