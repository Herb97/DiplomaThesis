/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date:                      Author:                                 *
;******************************************************************************
;
; File: fifo.c
;
;******************************************************************************
; SVN header
;  $Id: Fifo.C 114914 2021-09-23 07:57:16Z Stepanek, Michal $
;******************************************************************************
; MODULE SPECIFICATION
;******************************************************************************
; 1. PURPOSE
;
; 2. USAGE
;	fifo size:
;		#define OURFIFOSIZE 3
;	declaration:
;		FIFO(OURFIFOSIZE) ourfifo;
;	initialization:
;		FifoInit(&ourfifo,OURFIFOSIZE);
;
******************************************************************************/

//*****************************************************************************
// INCLUDE FILES
//*****************************************************************************
#include ".\Fifo.H"						// OWN definition file


//*****************************************************************************
// GLOBAL FUNCTIONS
//*****************************************************************************

/******************************************************************************
; Procedure     : FifoInit
; Description   : Initializes FIFO in memory
; Input         : *fifoheader=pointer to FIFO, ->ubSize=must be equal to allocated ->ubSize
; Output        : --
;*****************************************************************************/
void FifoInit(void *fifoheader, uint8_t lubSize)
{
	fifo_header *fifo;

	fifo=fifoheader; // retype back to correct type
	fifo->ubHead=lubSize;
	fifo->ubTail=lubSize;
	fifo->ubSize=lubSize+1; // the defined lubSize must be equal to allocated lubSize!!!
}


/******************************************************************************
; Procedure     : FifoPut
; Description   : Puts one byte to FIFO
; Input         : *fifoheader=pointer to FIFO, c=byte to be put
; Output        : --
;*****************************************************************************/
void FifoPut(void *fifoheader, uint8_t c)
{
	uint8_t next_tail;
	fifo_header *fifo;

	fifo=fifoheader; // retype back to correct type
	next_tail=fifo->ubTail;
	if(next_tail==0)
	{
		next_tail=fifo->ubSize;
	}
	next_tail--;
	
	if(next_tail!=fifo->ubHead)
	{
		fifo->ubBuffer[fifo->ubTail]=c;
		fifo->ubTail=next_tail;
	}
	else
	{
		// no free space in buffer - wait() if multitasking
	}
}


/******************************************************************************
; Procedure     : ubFifoGet
; Description   : Gets one byte from FIFO
; Input         : *fifoheader=pointer to FIFO
; Output        : byte from FIFO = check for available bytes first!
;*****************************************************************************/
uint8_t ubFifoGet(void *fifoheader)
{
	uint8_t c;
	fifo_header *fifo;

	fifo=fifoheader; // retype back to correct type
	if(fifo->ubHead!=fifo->ubTail)
	{
		c=fifo->ubBuffer[fifo->ubHead];
		if(fifo->ubHead==0)
		{
			fifo->ubHead=fifo->ubSize;
		}
		fifo->ubHead--;
	}
	else
	{
		// no characters waiting in the buffer - wait() if multitasking
		c=0; // not neccessary - just to define a return value (we can also return (int)(-1) in this case)
	}
	return c;
}


/******************************************************************************
; Procedure     : FifoPutMultiple
; Description   : Puts multiple bytes to FIFO
; Input         : *fifoheader=pointer to FIFO, *buffer=array in ram, lubSize=bytecount
; Output        : --
;*****************************************************************************/
void FifoPutMultiple(void *fifoheader, uint8_t const *buffer, uint8_t lubSize)
{
	for(;lubSize;lubSize--)
	{
		FifoPut(fifoheader,*buffer);
		buffer=buffer+1;
	}
}


/******************************************************************************
; Procedure     : FifoGetMultiple
; Description   : Gets multiple bytes from FIFO
; Input         : *fifoheader=pointer to FIFO, *buffer=array in ram, lubSize=bytecount
; Output        : --
;*****************************************************************************/
void FifoGetMultiple(void *fifoheader, void *buffer, uint8_t lubSize)
{
	for(;lubSize;lubSize--)
	{
		*((uint8_t *)buffer)=ubFifoGet(fifoheader);
		buffer=((uint8_t *)buffer)+1;
	}
}


/******************************************************************************
; Procedure     : ubFifoFull
; Description   : Checks how many bytes are waiting in FIFO
; Input         : *fifoheader=pointer to FIFO
; Output        : bytes in FIFO
;*****************************************************************************/
uint8_t ubFifoFull(void *fifoheader)
{
	uint8_t c;
	fifo_header *fifo;

	fifo=fifoheader; // retype back to correct type
	if( fifo->ubHead >= fifo->ubTail)
	{
		c = fifo->ubHead - fifo->ubTail;
	}
	else
	{
		c = fifo->ubHead - fifo->ubTail + fifo->ubSize;
	}

	return c;
}


/******************************************************************************
; Procedure     : ubFifoFree
; Description   : Checks how many bytes are free in FIFO
; Input         : *fifoheader=pointer to FIFO
; Output        : free bytes in FIFO
;*****************************************************************************/
uint8_t ubFifoFree(void *fifoheader)
{
	uint8_t c;
	fifo_header *fifo;

	fifo=fifoheader; // retype back to correct type
	//Need to know how many bytes are free
	c = fifo->ubSize - 1 - ubFifoFull(fifo);

	return c;
}

//*****************************************************************************
// LOCAL PROTOTYPES
//*****************************************************************************

