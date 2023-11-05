/*
 ============================================================================
 Name        : uart_private.h
 Author      : Ahmed Ali
 Module Name : UART
 Layer       : MCAL
 Date        : 15 Oct 2023
 Description : Private file for the AVR UART driver
 ============================================================================
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                 UART Registers type structure declarations                  *
 *******************************************************************************/

/* Bitmap structure for UCSRA register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 MPCM_Bit :1; /* MPCM bit 0 */
		uint8 U2X_Bit :1; /* U2X bit 1 */
		uint8 PE_Bit :1; /* PE bit 2 */
		uint8 DOR_Bit :1; /* DOR bit 3 */
		uint8 FE_Bit :1; /* FE bit 4 */
		uint8 UDRE_Bit :1; /* UDRE bit 5 */
		uint8 TXC_Bit :1; /* TXC bit 6 */
		uint8 RXC_Bit :1; /* RXC bit 7 */
	} Bits;
} UART_UCSRA_Type;

/* Bitmap structure for UCSRB register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TXB8_Bit :1; /* TXB8 bit 0 */
		uint8 RXB8_Bit :1; /* RXB8 bit 1 */
		uint8 UCSZ2_Bit :1; /* UCSZ2 bit 2 */
		uint8 TXEN_Bit :1; /* TXEN bit 3 */
		uint8 RXEN_Bit :1; /* RXEN bit 4 */
		uint8 UDRIE_Bit :1; /* UDRIE bit 5 */
		uint8 TXCIE_Bit :1; /* TXCIE bit 6 */
		uint8 RXCIE_Bit :1; /* RXCIE bit 7 */
	} Bits;
} UART_UCSRB_Type;

/* Bitmap structure for UCSRC register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 UCPOL_Bit :1; /* UCPOL bit 0 */
		uint8 UCSZ0_Bit :1; /* UCSZ0 bit 1 */
		uint8 UCSZ1_Bit :1; /* UCSZ1 bit 2 */
		uint8 USBS_Bit :1; /* USBS bit 3 */
		uint8 UPM0_Bit :1; /* UPM0 bit 4 */
		uint8 UPM1_Bit :1; /* UPM1 bit 5 */
		uint8 UMSEL_Bit :1; /* UMSEL bit 6 */
		uint8 URSEL_Bit :1; /* URSEL bit 7 */
	} Bits;
} UART_UCSRC_Type;

/*******************************************************************************
 *                         UART Registers Definitions                          *
 *******************************************************************************/

/* definition for UCSRA register */
#define UCSRA_REG (*(volatile UART_UCSRA_Type *const) 0x2B)

/* definition for UCSRA register */
#define UCSRB_REG (*(volatile UART_UCSRB_Type *const) 0x2A)

/* definition for UCSRC register */
#define UCSRC_REG (*(volatile UART_UCSRC_Type *const) 0x40)

/* definition for UDR register */
#define UDR_REG (*(volatile uint8 *const)   0x2C)

/* definition for UBRRL register */
#define UBRRL_REG (*(volatile uint8 *const) 0x29)

/* definition for UBRRL register */
#define UBRRH_REG (*(volatile uint8 *const) 0x40)

#endif /* UART_PRIVATE_H_ */
