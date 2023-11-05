/*
 ============================================================================
 File Name   : gpio_private.h
 Author      : Ahmed Ali
 Module      : GPIO
 Layer       : MCAL
 Date        : 19 Sept 2023
 Description : Private file for the AVR GPIO driver
 ============================================================================
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                 GPIO Registers type structure declarations                  *
 *******************************************************************************/

/* Bitmap structure for PORTA register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 PA0_Bit :1; /* Register bit 0 */
		uint8 PA1_Bit :1; /* Register bit 1 */
		uint8 PA2_Bit :1; /* Register bit 2 */
		uint8 PA3_Bit :1; /* Register bit 3 */
		uint8 PA4_Bit :1; /* Register bit 4 */
		uint8 PA5_Bit :1; /* Register bit 5 */
		uint8 PA6_Bit :1; /* Register bit 6 */
		uint8 PA7_Bit :1; /* Register bit 7 */
	} Bits;
} GPIO_PORTA_Type;

/* Bitmap structure for PORTB register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 PB0_Bit :1; /* Register bit 0 */
		uint8 PB1_Bit :1; /* Register bit 1 */
		uint8 PB2_Bit :1; /* Register bit 2 */
		uint8 PB3_Bit :1; /* Register bit 3 */
		uint8 PB4_Bit :1; /* Register bit 4 */
		uint8 PB5_Bit :1; /* Register bit 5 */
		uint8 PB6_Bit :1; /* Register bit 6 */
		uint8 PB7_Bit :1; /* Register bit 7 */
	} Bits;
} GPIO_PORTB_Type;

/* Bitmap structure for PORTC register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 PC0_Bit :1; /* Register bit 0 */
		uint8 PC1_Bit :1; /* Register bit 1 */
		uint8 PC2_Bit :1; /* Register bit 2 */
		uint8 PC3_Bit :1; /* Register bit 3 */
		uint8 PC4_Bit :1; /* Register bit 4 */
		uint8 PC5_Bit :1; /* Register bit 5 */
		uint8 PC6_Bit :1; /* Register bit 6 */
		uint8 PC7_Bit :1; /* Register bit 7 */
	} Bits;
} GPIO_PORTC_Type;

/* Bitmap structure for PORTD register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 PD0_Bit :1; /* Register bit 0 */
		uint8 PD1_Bit :1; /* Register bit 1 */
		uint8 PD2_Bit :1; /* Register bit 2 */
		uint8 PD3_Bit :1; /* Register bit 3 */
		uint8 PD4_Bit :1; /* Register bit 4 */
		uint8 PD5_Bit :1; /* Register bit 5 */
		uint8 PD6_Bit :1; /* Register bit 6 */
		uint8 PD7_Bit :1; /* Register bit 7 */
	} Bits;
} GPIO_PORTD_Type;

/*******************************************************************************
 *                  SREG Register type structure declarations                  *
 *******************************************************************************/

/* Bitmap structure for SREG register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 C_Bit :1; /* C bit 0 */
		uint8 Z_Bit :1; /* Z bit 1 */
		uint8 N_Bit :1; /* N bit 2 */
		uint8 V_Bit :1; /* V bit 3 */
		uint8 S_Bit :1; /* S bit 4 */
		uint8 H_Bit :1; /* H bit 5 */
		uint8 T_Bit :1; /* T bit 6 */
		uint8 I_Bit :1; /* I bit 7 */
	} Bits;
} SREG_Type;

/*******************************************************************************
 *                         GPIO Registers Definitions                          *
 *******************************************************************************/

/* definition for PORTA registers */
#define PORTA_REG (*(volatile GPIO_PORTA_Type *const)     0x3B)
#define DDRA_REG (*(volatile GPIO_PORTA_Type *const)      0x3A)
#define PINA_REG (*(volatile const GPIO_PORTA_Type *const)0x39)

/* definition for PORTB registers */
#define PORTB_REG (*(volatile GPIO_PORTB_Type *const)     0x38)
#define DDRB_REG (*(volatile GPIO_PORTB_Type *const)      0x37)
#define PINB_REG (*(volatile const GPIO_PORTB_Type *const)0x36)

/* definition for PORTC registers */
#define PORTC_REG (*(volatile GPIO_PORTC_Type *const)     0x35)
#define DDRC_REG (*(volatile GPIO_PORTC_Type *const)      0x34)
#define PINC_REG (*(volatile const GPIO_PORTC_Type *const)0x33)

/* definition for PORTD registers */
#define PORTD_REG (*(volatile GPIO_PORTD_Type *const)     0x32)
#define DDRD_REG (*(volatile GPIO_PORTD_Type *const)      0x31)
#define PIND_REG (*(volatile const GPIO_PORTD_Type *const)0x30)

/*******************************************************************************
 *                         SREG Register Definitions                           *
 *******************************************************************************/

/* definition for SREG registers */
#define SREG_REG (*(volatile SREG_Type *const) 0x5F)

#endif /* GPIO_PRIVATE_H_ */
