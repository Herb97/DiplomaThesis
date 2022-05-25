/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2021-08-10           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Global.H
;
;******************************************************************************
; SVN header
;  $Id: Global.H 116376 2022-01-17 16:08:00Z Stepanek, Michal $
******************************************************************************/

#include "stm32f4xx.h"
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
#define BIT16 (0x00010000UL)
#define BIT17 (0x00020000UL)
#define BIT18 (0x00040000UL)
#define BIT19 (0x00080000UL)
#define BIT20 (0x00100000UL)
#define BIT21 (0x00200000UL)
#define BIT22 (0x00400000UL)
#define BIT23 (0x00800000UL)
#define BIT24 (0x01000000UL)
#define BIT25 (0x02000000UL)
#define BIT26 (0x04000000UL)
#define BIT27 (0x08000000UL)
#define BIT28 (0x10000000UL)
#define BIT29 (0x20000000UL)
#define BIT30 (0x40000000UL)
#define BIT31 (0x80000000UL)

#define HSE_VALUE    ((uint32_t)24000000U) /*!< Value of the External oscillator in Hz */

#define NUMBER_OF_INPUTS		16		// 16 digital input cahnnels
#define NUMBER_OF_OUTPUTS		12		// 12 digital output cahnnels
