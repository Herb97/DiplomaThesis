/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date:                      Author:                                 *
;******************************************************************************
;
; File: fifo.h
;
;******************************************************************************
; SVN header
;  $Id: Fifo.H 114914 2021-09-23 07:57:16Z Stepanek, Michal $
******************************************************************************/

//*****************************************************************************
// HEADER DEFINITION
//*****************************************************************************
#ifndef __FIFO_H
#define __FIFO_H

//*****************************************************************************
// TYPEDEF
//*****************************************************************************
typedef struct {
	uint8_t ubSize;
	uint8_t ubHead;
	uint8_t ubTail;
	uint8_t ubBuffer[1/*variable-size*/];
} fifo_header;

//*****************************************************************************
// #DEFINE MACROS
//*****************************************************************************
// FIFO wastes one byte in the buffer
// maximal size is 254 character entries, occupying 258 bytes of RAM including pointers
#define FIFO(size) struct {fifo_header; uint8_t fifo_space[size+1];}

//*****************************************************************************
// GLOBAL FUNCTION PROTOTYPES
//*****************************************************************************
void FifoInit(void  *fifoheader, uint8_t lubSize);
void FifoPut(void  *fifoheader, uint8_t c);
uint8_t ubFifoGet(void  *fifoheader);
uint8_t ubFifoFull(void  *fifoheader);
uint8_t ubFifoFree(void  *fifoheader);
void FifoPutMultiple(void  *fifoheader, uint8_t const *buffer, uint8_t lubSize);
void FifoGetMultiple(void  *fifoheader, void  *buffer, uint8_t lubSize);

//*****************************************************************************
// END OF HEADER DEFINITION
//*****************************************************************************
#endif  /* __TEMPLATE_H */
