/*
 ============================================================================
 Name        : timer_private.h
 Author      : Ahmed Ali
 Module Name : TIMER1
 Layer       : MCAL
 Date        : 8 Oct 2023
 Description : Private file for the AVR TIMER1 driver
 ============================================================================
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                Timer1 Registers type structure declarations                 *
 *******************************************************************************/

/* Bitmap structure for TCCR1A register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 WGM10_Bit :1; /* WGM10 bit 0 */
		uint8 WGM11_Bit :1; /* WGM11 bit 1 */
		uint8 FOC1B_Bit :1; /* FOC1B bit 2 */
		uint8 FOC1A_Bit :1; /* FOC1A bit 3 */
		uint8 COM1B0_Bit :1; /* COM1B0 bit 4 */
		uint8 COM1B1_Bit :1; /* COM1B1 bit 5 */
		uint8 COM1A0_Bit :1; /* COM1A0 bit 6 */
		uint8 COM1A1_Bit :1; /* COM1A1 bit 7 */
	} Bits;
} Timer1_TCCR1A_Type;

/* Bitmap structure for TCCR1B register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 CS10_Bit :1; /* CS10 bit 0 */
		uint8 CS11_Bit :1; /* CS11 bit 1 */
		uint8 CS12_Bit :1; /* CS12 bit 2 */
		uint8 WGM12_Bit :1; /* WGM12 bit 3 */
		uint8 WGM13_Bit :1; /* WGM13 bit 4 */
		uint8 :1; /* Reserved bit 5 */
		uint8 ICES1_Bit :1; /* ICES1 bit 6 */
		uint8 ICNC1_Bit :1; /* ICNC1 bit 7 */
	} Bits;
} Timer1_TCCR1B_Type;

/*******************************************************************************
 *                        Timer1 Registers Definitions                         *
 *******************************************************************************/
/* definition for TCCR1A register */
#define TCCR1A_REG (*(volatile Timer1_TCCR1A_Type *const) 0x4F)

/* definition for TCCR1B register */
#define TCCR1B_REG (*(volatile Timer1_TCCR1B_Type *const) 0x4E)

/* definition for TCNT1 registers */
#define TCNT1H_REG (*(volatile uint8 *const)  0x4D)

#define TCNT1L_REG (*(volatile uint8 *const)  0x4C)

#define TCNT1_REG  (*(volatile uint16 *const) 0x4C)

/* definition for OCR1A registers */
#define OCR1AH_REG (*(volatile uint8 *const)  0x4B)

#define OCR1AL_REG (*(volatile uint8 *const)  0x4A)

#define OCR1A_REG  (*(volatile uint16 *const) 0x4A)

/* definition for OCR1B registers */
#define OCR1BH_REG (*(volatile uint8 *const)  0x49)

#define OCR1BL_REG (*(volatile uint8 *const)  0x48)

#define OCR1B_REG  (*(volatile uint16 *const) 0x48)

/* definition for ICR1 registers */
#define ICR1H_REG (*(volatile uint8 *const)  0x47)

#define ICR1L_REG (*(volatile uint8 *const)  0x46)

#define ICR1_REG  (*(volatile uint16 *const) 0x46)

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
