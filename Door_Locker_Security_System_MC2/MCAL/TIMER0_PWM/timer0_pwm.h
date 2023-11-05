/*
 ============================================================================
 Name        : pwm.h
 Author      : Ahmed Ali
 Module Name : TIMER0 PWM
 Layer       : MCAL
 Date        : 10 Oct 2023
 Description : Header file for the AVR timer0 PWM driver
 ============================================================================
 */

#ifndef TIMER0_PWM_H_
#define TIMER0_PWM_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define OC0_PORTID		PORTB_ID
#define OC0_PINID 		PIN3_ID

#define OC0_MAX_VALUE 	255

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the PWM driver.
 */
void PWM_Timer0_init(void);

/*
 * Description:
 * 1. The function responsible for trigger the Timer0 with the PWM Mode.
 * 2. Setup the PWM mode with Non-Inverting.
 * 3. Setup the prescaler with F_CPU/8.
 * 4. Setup the compare value based on the required input duty cycle
 * 5. Setup the direction for OC0 as output pin through the GPIO driver.
 * 6. The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(uint8 a_dutyCycle);

#endif /* MCAL_PWM_PWM_H_ */
