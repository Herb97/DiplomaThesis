/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2017-11-06           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: CrcA001.C
;
;******************************************************************************
; SVN header
;  $Id: CrcA001.H 106828 2020-03-29 11:06:45Z Stepanek, Michal $
******************************************************************************/

/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
uint16_t uwCrcA001_Get (uint8_t *ptr, uint16_t len);
uint16_t uwCrcA001_Update (uint16_t crc, uint8_t c);

// pokud kontrolujeme crc na bufferu, kde je na konci crc v poøadí LsbMsb, pak je výsledek 0x0000
// pokud je CRC na zaèátku, tak je to jinak

