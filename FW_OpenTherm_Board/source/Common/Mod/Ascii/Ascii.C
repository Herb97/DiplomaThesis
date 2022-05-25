/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2022-02-14           Author: Herbrych, Vojtech               *
;******************************************************************************
;
; File: Ascii.C
;
;******************************************************************************
; SVN header
;  $Id: Ascii.C 117530 2022-03-21 12:12:45Z Stepanek, Michal $
******************************************************************************/


//*****************************************************************************
// INCLUDE FILES
//*****************************************************************************
#include ".\Ascii.H"						// OWN header



/******************************************************************************
; Procedure     : ubAsciiFromNibble()
; Description   : Hexadecimal to ASCII conversion utility
; Input         : uint8_t, hexadecimal data, low nibble
; Output        : uint8_t, converted ASCI value

In		Out
0x00	'0'
0x01	'1'
0x02	'2'
0x03	'3'
0x04	'4'
0x05	'5'
0x06	'6'
0x07	'7'
0x08	'8'
0x09	'9'
0x0A	'A'
0x0B	'B'
0x0C	'C'
0x0D	'D'
0x0E	'E'
0x0F	'F'

;******************************************************************************/
uint8_t ubAsciiFromNibble(uint8_t lubData)
{
    // convert to ASCII
    lubData &= 0x0Fu;
    if (lubData > 9u)
    {
      lubData += 'A' - 10u;
    }
    else
    {
      lubData += '0';
    }
    return lubData;
}


/******************************************************************************
; Procedure     : ubAsciiToHex()
; Description   : ASCII to Hexadecimal conversion utility
; Input         : uint8_t, ASCII data
; Output        : uint8_t, converted hexadecimal value

In		Out
'0'		0x00
'1'		0x01
'2'		0x02
'3'		0x03
'4'		0x04
'5'		0x05
'6'		0x06
'7'		0x07
'8'		0x08
'9'		0x09
'A'		0x0A
'B'		0x0B
'C'		0x0C
'D'		0x0D
'E'		0x0E
'F'		0x0F

;******************************************************************************/
uint8_t ubAsciiToHex(uint8_t lubData)
{
    // convert to ASCII
    if (lubData > '9')    // '9' => 0x39
    {
      lubData -= 'A' - 10u;
    }
    else
    {
      lubData -= '0';
    }
    return lubData&0x0Fu;
}


