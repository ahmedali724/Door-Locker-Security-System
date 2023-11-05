/*
 ============================================================================
 Name        : pwm.c
 Author      : Ahmed Ali
 Module Name : TIMER0 PWM
 Layer       : MCAL
 Date        : 10 Oct 2023
 Description : Source file for the AVR timer0 PWM driver
 ============================================================================
 */

#include "../../MCAL/GPIO/gpio.h"
#include "timer0_private.h"
#include "timer0_pwm.h"

/*
 * Description :
 * Function responsible for initialize the PWM driver.
 */
void PWM_Timer0_init(void)
{
	/* Set OC0 pin direction as output */
	GPIO_setupPinDirection(OC0_PORTID, OC0_PINID, PIN_OUTPUT);

	/* TCCR0 Register Bits Description:
	 * FOC0     = 0   we don't use overflow mode or compare match mode, then reset this bit
	 * WGM01:0  = 11  fast PWM mode
	 * COM01:0  = 10  non-inverting fast PWM mode
	 * CS02:0   = 010 pre-scaler 8 => F_CPU/8
	 */

	/* Fast PWM mode */
	TCCR0_REG.Bits.WGM00_Bit = 1;
	TCCR0_REG.Bits.WGM01_Bit = 1;
	/* non inverting fast PWM */
	TCCR0_REG.Bits.COM01_Bit = 1;
	/* pre-scaler 8 */
	TCCR0_REG.Bits.CS01_Bit = 1;
	/* OCR0 value is 0 as initial */
	OCR0_REG = 0;
}

/*
 * Description:
 * 1. The function responsible for trigger the Timer0 with the PWM Mode.
 * 2. Setup the PWM mode with Non-Inverting.
 * 3. Setup the prescaler with F_CPU/8.
 * 4. Setup the compare value based on the required input duty cycle
 * 5. Setup the direction for OC0 as output pin through the GPIO driver.
 * 6. The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(uint8 a_dutyCycle)
{
	/* If the input duty cycle greater than 100, then set it to 100 */
	if (a_dutyCycle > 100)
	{
		a_dutyCycle = 100;
	}
	/* If the input duty cycle less than 0, then set it to 0 */
	if (a_dutyCycle < 0)
	{
		a_dutyCycle = 0;
	}
	OCR0_REG = (uint8) ((uint16) a_dutyCycle * OC0_MAX_VALUE / 100);
}
