/*
 ============================================================================
 Name        : uart.c
 Author      : Ahmed Ali
 Module Name : UART
 Layer       : MCAL
 Date        : 15 Oct 2023
 Description : Source file for the AVR UART driver
 ============================================================================
 */

#include "uart.h"
#include "uart_private.h"

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr)
{
	uint16 ubrr_value = 0;
	/* U2X = 1 for double transmission speed */
	UCSRA_REG.Bits.U2X_Bit = 1;

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB_REG.Bits.TXEN_Bit = 1;
	UCSRB_REG.Bits.RXEN_Bit = 1;

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC_REG.Bits.URSEL_Bit = 1;
	UCSRC_REG.Bits.UCPOL_Bit = 0;

	/*
	 * insert the required mode in UMSEL bit of UCSRC Register
	 */
	UCSRC_REG.Bits.UMSEL_Bit = Config_Ptr->mode;

	/*
	 * insert the required parity mode in UPM1 bit (UPM0 and UPM1) of UCSRC Register
	 */
	UCSRC_REG.Byte = (UCSRC_REG.Byte & 0xCF) | ((Config_Ptr->parity) << 4);

	/*
	 * insert the required stop bit in USBS bit of UCSRC Register
	 */
	UCSRC_REG.Bits.USBS_Bit = Config_Ptr->stopBit;

	/*
	 * insert the required character size in UCSZ bits(UCSZ0, UCSZ1 and UCSZ2) of UCSRC and UCSRB Register
	 */
	UCSRC_REG.Byte = (UCSRC_REG.Byte & 0xF9)
			| (((Config_Ptr->characterSize) << 1) & 0x06);

	/* Calculate the UBRR register value */
	ubrr_value = (uint16) (((F_CPU / ((Config_Ptr->baudRate) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH_REG = ubrr_value >> 8;
	UBRRL_REG = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while (UCSRA_REG.Bits.UDRE_Bit == 0)
	{
	}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR_REG = data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while (UCSRA_REG.Bits.RXC_Bit == 0)
	{
	}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR_REG;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while (Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while (Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
