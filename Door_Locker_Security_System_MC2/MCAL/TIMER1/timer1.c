/*
 ============================================================================
 Name        : timer1.c
 Author      : Ahmed Ali
 Module Name : TIMER1
 Layer       : MCAL
 Date        : 16 Oct 2023
 Description : Source file for the AVR TIMER1 driver
 ============================================================================
 */

#include "timer1.h"
#include "timer1_private.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
	if (g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the Timer driver.
 */
void Timer1_init(const TIMER1_ConfigType *Config_Ptr)
{
	/************************** TCCR1A Description **************************
	 * COM1A1:0 = 00  Normal port operation, OC1A disconnected
	 * COM1B1:0 = 00  Normal port operation, OC1B disconnected
	 * FOC1A    = 1   Force Output Compare for Compare unit A (non-PWM mode)
	 * FOC1B    = 1   Force Output Compare for Compare unit B (non-PWM mode)
	 * WGM11:0        Waveform Generation Mode, selected in configuration
	 ***********************************************************************/

	TCCR1A_REG.Bits.FOC1A_Bit = 1;
	TCCR1A_REG.Bits.FOC1B_Bit = 1;

	/*
	 * insert the required mode in WGM bits (WGM10 and WGM11) of TCCR1A Register
	 * and (WGM12 and WGM13) of TCCR1B Register
	 */
	if (Config_Ptr->mode == NORMAL_MODE)
	{
		TCCR1A_REG.Bits.WGM10_Bit = 0;
		TCCR1A_REG.Bits.WGM11_Bit = 0;
		TCCR1B_REG.Bits.WGM12_Bit = 0;
		TCCR1B_REG.Bits.WGM13_Bit = 0;
	}
	else if (Config_Ptr->mode == CTC_MODE)
	{
		TCCR1A_REG.Bits.WGM10_Bit = 0;
		TCCR1A_REG.Bits.WGM11_Bit = 0;
		TCCR1B_REG.Bits.WGM12_Bit = 1;
		TCCR1B_REG.Bits.WGM13_Bit = 0;
	}

	/************************** TCCR1B Description **************************
	 * ICNC1    = 0   Input Capture Noise Canceller
	 * ICES1    = 0   Input Capture Edge Select
	 * WGM13:2        Waveform Generation Mode, selected in configuration
	 * CS12:0   = 0   Clock Select, selected in configuration
	 ***********************************************************************/
	TCCR1B_REG.Byte = (TCCR1B_REG.Byte & 0xF8) | (Config_Ptr->prescaler);

	TCNT1_REG = Config_Ptr->initial_value;

	OCR1A_REG = Config_Ptr->compare_value;

	/* Enable Timer/Counter1 Output Compare A match interrupt */
	TIMSK_REG.Bits.OCIE1A_Bit = 1;

	/* Enable Timer/Counter1 Overflow Interrupt */
	TIMSK_REG.Bits.TOIE1_Bit = 1;
}

/*
 * Description :
 * Function to disable the Timer1.
 */
void Timer1_deInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A_REG.Byte = 0;
	TCCR1B_REG.Byte = 0;
	TCNT1_REG = 0;
	OCR1A_REG = 0;

	/* Disable the Output Compare A match and Overflow interrupt */
	TIMSK_REG.Bits.OCIE1A_Bit = 1;
	TIMSK_REG.Bits.TOIE1_Bit = 1;

	/* Reset the global pointer value */
	g_callBackPtr = NULL_PTR;
}

/*
 * Description :
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void (*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
