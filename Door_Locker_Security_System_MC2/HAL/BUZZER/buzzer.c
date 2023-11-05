/*
 ============================================================================
 Name        : buzzer.c
 Author      : Ahmed Ali
 Module Name : BUZZER
 Layer       : HAL
 Date        : 17 Oct 2023
 Description : Source file for the buzzer driver
 ============================================================================
 */

#include "buzzer.h"
#include "../../MCAL/GPIO/gpio.h"

/*
 * Description :
 * 1. Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * 2. Turn off the buzzer through the GPIO.
 */
void Buzzer_init()
{
	/* Setup the direction for the buzzer pin as output */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

	/* Turn off the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * Function to enable the Buzzer through the GPIO
 */
void Buzzer_on(void)
{
	/* Turn on the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/*
 * Description :
 * Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void)
{
	/* Turn off the buzzer */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
