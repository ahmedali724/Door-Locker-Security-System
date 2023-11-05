/*
 ============================================================================
 Name        : uart.h
 Author      : Ahmed Ali
 Module Name : UART
 Layer       : MCAL
 Date        : 15 Oct 2023
 Description : Header file for the AVR UART driver
 ============================================================================
 */

#ifndef UART_H_
#define UART_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	ASYNCHRONOUS, SYNCHRONOUS
} UART_ModeType;

typedef enum
{
	DISABLED_PARITY = 0, EVEN_PARITY = 2, ODD_PARITY = 3
} UART_ParityType;

typedef enum
{
	STOP_1_BIT, STOP_2_BIT
} UART_StopBitType;

typedef enum
{
	DATA_5_BIT, DATA_6_BIT, DATA_7_BIT, DATA_8_BIT
} UART_CharacterSizeType;

typedef enum
{
	BAUD_RATE_2400 = 2400,
	BAUD_RATE_4800 = 4800,
	BAUD_RATE_9600 = 9600,
	BAUD_RATE_14400 = 14400,
	BAUD_RATE_19200 = 19200,
	BAUD_RATE_28800 = 28800,
	BAUD_RATE_38400 = 38400,
	BAUD_RATE_57600 = 57600,
	BAUD_RATE_76800 = 76800,
	BAUD_RATE_115200 = 115200,
	BAUD_RATE_230400 = 230400,
	BAUD_RATE_250000 = 250000,
} UART_BaudRateType;

typedef struct
{
	UART_ModeType mode;
	UART_ParityType parity;
	UART_StopBitType stopBit;
	UART_CharacterSizeType characterSize;
	UART_BaudRateType baudRate;
} UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str);

#endif /* UART_H_ */
