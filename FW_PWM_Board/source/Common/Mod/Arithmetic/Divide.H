/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2019-10-08           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: Divide.H
;
;******************************************************************************
; SVN header
;  $Id: Divide.H 115770 2021-12-02 06:25:55Z Stepanek, Michal $
******************************************************************************/

/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
/*s16 swDivideRoundNearest_100(s16 x);
s32 slDivideRoundNearest_100(s32 x);
s16 swDivideRoundNearest_10(s16 x);
s32 slDivideRoundNearest_10(s32 x);
s32 slDivideRoundNearest_1000(s32 x);*/

uint32_t ulDivideRoundUpFromFloat(float32_t lflDivident, float32_t lflDivisor);
uint32_t ulDivideRoundNearestFromFloat(float32_t lflDivident, float32_t lflDivisor);
uint32_t ulRoundNearestFromFloat(float32_t lflDivident);

uint32_t ulDivideRoundUp(uint32_t lulDivident, uint32_t lulDivisor);
uint32_t ulDivideRoundNearest(uint32_t lulDivident, uint32_t lulDivisor);
uint16_t uwDivideRoundNearest(uint16_t luwDivident, uint16_t luwDivisor);

#define ulDivideRoundNearest_10000(x)	ulDivideRoundNearest((x),10000U)
#define ulDivideRoundNearest_1000(x)	ulDivideRoundNearest((x),1000U)
#define ulDivideRoundNearest_100(x)		ulDivideRoundNearest((x),100U)

#define uwDivideRoundNearest_100(x)	uwDivideRoundNearest((x),100U)
#define uwDivideRoundNearest_10(x)	uwDivideRoundNearest((x),10U)
