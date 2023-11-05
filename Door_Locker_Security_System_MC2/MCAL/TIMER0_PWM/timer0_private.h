/*
 ============================================================================
 Name        : timer_private.h
 Author      : Ahmed Ali
 Module Name : TIMER0 PWM
 Layer       : MCAL
 Date        : 8 Oct 2023
 Description : Private file for the AVR TIMER0 driver
 ============================================================================
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                Timer0 Registers type structure declarations                 *
 *******************************************************************************/

/* Bitmap structure for TCCR0 register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 CS00_Bit :1; /* CS00 bit 0 */
		uint8 CS01_Bit :1; /* CS01 bit 1 */
		uint8 CS02_Bit :1; /* CS02 bit 2 */
		uint8 WGM01_Bit :1; /* WGM01 bit 3 */
		uint8 COM00_Bit :1; /* COM00 bit 4 */
		uint8 COM01_Bit :1; /* COM01 bit 5 */
		uint8 WGM00_Bit :1; /* WGM00 bit 6 */
		uint8 FOC0_Bit :1; /* FOC0 bit 7 */
	} Bits;
} Timer0_TCCR0_Type;

/*******************************************************************************
 *                        Timer0 Registers Definitions                         *
 *******************************************************************************/

/* definition for TCCR0 register */
#define TCCR0_REG (*(volatile Timer0_TCCR0_Type *const) 0x53)

/* definition for TCNT0 registers */
#define TCNT0_REG (*(volatile uint8 *const) 0x52)

/* definition for OCR0 registers */
#define OCR0_REG  (*(volatile uint8 *const) 0x5C)

/*******************************************************************************
 *            Timers Interrupt Register type structure declarations            *
 *******************************************************************************/

/* Bitmap structure for TIMSK register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TOIE0_Bit :1; /* TOIE0 bit 0 */
		uint8 OCIE0_Bit :1; /* OCIE0 bit 1 */
		uint8 TOIE1_Bit :1; /* TOIE1 bit 2 */
		uint8 OCIE1B_Bit :1; /* OCIE1B bit 3 */
		uint8 OCIE1A_Bit :1; /* OCIE1A bit 4 */
		uint8 TICIE1_Bit :1; /* TICIE1 bit 5 */
		uint8 TOIE2_Bit :1; /* TOIE2 bit 6 */
		uint8 OCIE2_Bit :1; /* OCIE2 bit 7 */
	} Bits;
} Timers_TIMSK_Type;

/* Bitmap structure for TIFR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TOV0_Bit :1; /* TOV0 bit 0 */
		uint8 OCF0_Bit :1; /* OCF0 bit 1 */
		uint8 TOV1_Bit :1; /* TOV1 bit 2 */
		uint8 OCF1B_Bit :1; /* OCF1B bit 3 */
		uint8 OCF1A_Bit :1; /* OCF1A bit 4 */
		uint8 ICF1_Bit :1; /* ICF1 bit 5 */
		uint8 TOV2_Bit :1; /* TOV2 bit 6 */
		uint8 OCF2_Bit :1; /* OCF2 bit 7 */
	} Bits;
} Timers_TIFR_Type;

/*******************************************************************************
 *                    Timers Interrupt Register Definitions                    *
 *******************************************************************************/

/* definition for TIMSK register */
#define TIMSK_REG (*(volatile Timers_TIMSK_Type *const) 0x59)

/* definition for TIFR register */
#define TIFR_REG  (*(volatile Timers_TIFR_Type *const)  0x58)

#endif /* TIMER_PRIVATE_H_ */
