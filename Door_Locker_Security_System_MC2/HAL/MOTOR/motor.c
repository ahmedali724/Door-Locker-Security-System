/*
 ============================================================================
 Name        : motor.c
 Author      : Ahmed Ali
 Module Name : MOTOR
 Layer       : HAL
 Date        : 10 Oct 2023
 Description : Source file for the motor driver
 ============================================================================
 */

#include "motor.h"
#include "../../LIB/common_macros.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/TIMER0_PWM/timer0_pwm.h"

/*
 * Description :
 * 1. The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * 2. Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	/* Set IN1 and IN2 pins direction as output */
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, PIN_OUTPUT);

	/* Stop motor as initial state */
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * 1. The function responsible for rotate the DC Motor CW/
 *    or A-CW or stop the motor based on the state input state value.
 * 2. Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State a_state, uint8 a_speed)
{
	switch (a_state)
	{
	case CLOCK_Wise:
		/* Clock wise mode => (IN1 = 1 and INT2 = 0) */
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	case ANTI_CLOCK_WISE:
		/* Anti clock wise mode => (IN1 = 0 and INT2 = 1) */
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_HIGH);
		break;
	default:
		/* Any case else, the motor be in stop mode */
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	}
	/* Call the PWM function and give it the speed */
	PWM_Timer0_Start(a_speed);
}
