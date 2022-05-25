/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-07-09           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Global.H
;
;******************************************************************************
; SVN header
;  $Id: Global.H 118385 2022-05-05 14:06:06Z Stepanek, Michal $
******************************************************************************/

#include "stm32l0xx.h"
#include <stdbool.h> // bool
#include <intrinsics.h>
#include <stddef.h>		// NULL 
typedef float float32_t;
typedef double float64_t;

#define BIT0  (0x0001u)
#define BIT1  (0x0002u)
#define BIT2  (0x0004u)
#define BIT3  (0x0008u)
#define BIT4  (0x0010u)
#define BIT5  (0x0020u)
#define BIT6  (0x0040u)
#define BIT7  (0x0080u)
#define BIT8  (0x0100u)
#define BIT9  (0x0200u)
#define BIT10 (0x0400u)
#define BIT11 (0x0800u)
#define BIT12 (0x1000u)
#define BIT13 (0x2000u)
#define BIT14 (0x4000u)
#define BIT15 (0x8000u)
#define BIT16 (0x00010000uL)
#define BIT17 (0x00020000uL)
#define BIT18 (0x00040000uL)
#define BIT19 (0x00080000uL)
#define BIT20 (0x00100000uL)
#define BIT21 (0x00200000uL)
#define BIT22 (0x00400000uL)
#define BIT23 (0x00800000uL)
#define BIT24 (0x01000000uL)
#define BIT25 (0x02000000uL)
#define BIT26 (0x04000000uL)
#define BIT27 (0x08000000uL)
#define BIT28 (0x10000000uL)
#define BIT29 (0x20000000uL)
#define BIT30 (0x40000000uL)
#define BIT31 (0x80000000uL)

#define HSE_VALUE    ((uint32_t)24000000u) /*!< Value of the External oscillator in Hz */

#define ENTER_CRITICAL_REGION	{ uint32_t volatile __backup_primask_reg = __get_PRIMASK(); __disable_interrupt();
#define LEAVE_CRITICAL_REGION	__set_PRIMASK(__backup_primask_reg); }
 