/******************************************************************************
; Resideo Residential Thermal Solutions                                       *
; Turanka 96/1236                                                             *
; 627 00 Brno, Czech Republic                                                 *
;                                                                             *
; Creation date: 2020-03-27           Author: Stepanek, Michal                *
;******************************************************************************
;
; File: ModbusSerial.H
;
;******************************************************************************
; SVN header
;  $Id: ModbusSerial.H 114361 2021-08-11 15:31:19Z Stepanek, Michal $
******************************************************************************/


#define MODBUS_SERIAL_BUFFER_SIZE 255	// up to 255


/******************************************************************************
; GLOBAL FUNCTIONS
;*****************************************************************************/
void ModbusSerialLineDataLink_Enable(void);
void ModbusSerialLineDataLink_Disable(void);
//void ModbusSerialLineDataLink_UART_Set(uint32_t baudrate, int receiverTimeout);

void ModbusSerialLineDataLink_Receive_Char(uint8_t c);
uint8_t ModbusSerialLineDataLink_ReceiveState(void);
void ModbusSerialLineDataLink_ReceiveDone(void);

extern uint8_t ModbusSerialLineDataLink_Rx_Len;
extern uint8_t ModbusSerialLineDataLink_Rx_Buffer[];

void ModbusSerialLineDataLink_Transmit(/*uint8_t * Ptr, */uint8_t lubLen);
void ModbusSerialLineDataLink_Transmit_Char(void);
//extern uint8_t ModbusSerialLineDataLink_Tx_Len;
//extern uint8_t ModbusSerialLineDataLink_Tx_Buffer[];

void ModbusSerialLineDataLink_Timeout(void);

uint32_t ModbusSerialLineDataLink_RxPacketCounter_Get(void);
uint32_t ModbusSerialLineDataLink_TxPacketCounter_Get(void);

