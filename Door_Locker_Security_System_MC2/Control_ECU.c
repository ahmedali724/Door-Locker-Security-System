/*
 ============================================================================
 Name        : Control_ECU.c
 Author      : Ahmed Ali
 Date        : 25 Oct 2023
 Layer       : APP
 Description : The main function of project
 ============================================================================
 */

#include "HAL/BUZZER/buzzer.h" /* to use buzzer functions */
#include "HAL/MOTOR/motor.h" /* to use motor functions */
#include "HAL/EXTERNAL_EEPROM/external_eeprom.h" /* to use EEPROM functions */
#include "MCAL/UART/uart.h"/* to use UART functions */
#include "MCAL/TIMER1/timer1.h" /* to use TIMER1 init function */
#include "MCAL/I2C/twi.h" /* to use TWI init function */
#include "MCAL/TIMER0_PWM/timer0_pwm.h" /* to use PWM TIMER0 init function */
#include "MCAL/GPIO/gpio_private.h" /* to use the declaration of SREG register */
#include "LIB/std_types.h" /* to use standard types */
#include <util/delay.h> /* to use delay functions */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile uint8 g_ticks = 0;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define EEPROM_FIRST_ADDRESS_VALUE  0x0015
#define START_COMMNUCATION 			0x15
#define CTC_VALUE_FOR_ONE_SECOND 	31250
#define CTC_INITIAL_VALUE 			0
#define PASSWORD_CORRECT            0xAA
#define PASSWORD_INCORRECT          0xBB
#define CRETAE_PASSWORD_ACTION      0xCC
#define CHECK_PASSWORD_ACTION       0xDD
#define CHANGE_PASSWORD_MODE        0xEE
#define OPEN_DOOR_MODE              0xFF
#define BUZZER_ON                   0x68
#define BUZZER_OFF                  0x69
#define PASSWORD_LENGTH				5
#define DOOR_UNLOKING_PERIOD        15
#define DOOR_LOKING_PERIOD          15
#define DOOR_HOLD_PERIOD            3
#define BUZZER_ACTIVE_PERIOD		60

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description :
 * Function to save the received password through UART to EEPROM.
 * Function input:  void.
 * Function output: void.
 */
void savePasswordToEEPROM(void);

/*
 * Description :
 * Function to receive password through UART and check
 * it with the one in EEPROM .
 * Function input:  void.
 * Function output: uint8 flag which indicate password correct.
 */
uint8 recivePasswordAndCheck(void);

/*
 * Description :
 * Function to count a number of seconds which passed to it.
 * Function input:  number of seconds.
 * Function output: void.
 */
void timer1DelaySecond(uint8 n);

/*
 * Description :
 * This is the call back function which will be executed each interrupt in timer1.
 * Function input:  void.
 * Function output: void.
 */
void countOneSecond(void);

int main(void)
{
	/* Configuration and initialization functions */
	/* enable global interrupt */
	SREG_REG.Bits.I_Bit = 1;
	uint8 flag, action, mode;
	/* select the configuration of UART */
	UART_ConfigType UART_config =
	{ ASYNCHRONOUS, DISABLED_PARITY, STOP_1_BIT, DATA_8_BIT, BAUD_RATE_9600 };

	/* select the configuration of TWI */
	TWI_ConfigType TWI_config =
	{ MC_ADDRESS, TWI_PRESCALER_1 };

	/* passing the configuration to initialization function of TWI */
	TWI_init(&TWI_config);
	/* passing the configuration to initialization function of UART */
	UART_init(&UART_config);
	/* call the initialization function of PWM TIMER0 */
	PWM_Timer0_init();
	/* call the initialization function of BUZZER */
	Buzzer_init();
	/* call the initialization function of DC-MOTOR */
	DcMotor_Init();
	while (1)
	{
		/* receive the action from HMI ECU through UART */
		action = UART_recieveByte();
		/* if the action is create password, then receive and save it */
		if (action == CRETAE_PASSWORD_ACTION)
		{
			savePasswordToEEPROM();
		}
		if (action == CHECK_PASSWORD_ACTION)
		{
			/* the action is check password */
			/* receive the mode from HMI ECU through UART */
			mode = UART_recieveByte();
			if (mode == OPEN_DOOR_MODE)
			{
				/* mode is open door mode */
				while (1)
				{
					/* receive the password and check if equal to the one in EEPROM */
					flag = recivePasswordAndCheck();
					if (flag == TRUE)
					{
						/* the password is correct and send to HMI that password is correct */
						UART_sendByte(PASSWORD_CORRECT);
						/* turn on motor at max speed with clock wise direction */
						DcMotor_Rotate(CLOCK_Wise, MOTOR_MAX_SPEED);
						/* waiting for 15 seconds until the door is unlocking */
						timer1DelaySecond(DOOR_UNLOKING_PERIOD);
						/* hold the motor */
						DcMotor_Rotate(STOP, MOTOR_MAX_SPEED);
						/* waiting for 3 seconds the hold period of the door */
						timer1DelaySecond(DOOR_HOLD_PERIOD);
						/* turn on motor at max speed with anti clock wise direction */
						DcMotor_Rotate(ANTI_CLOCK_WISE, MOTOR_MAX_SPEED);
						/* waiting for 15 seconds until the door is locking  */
						timer1DelaySecond(DOOR_LOKING_PERIOD);
						/* stop the dc motor */
						DcMotor_Rotate(STOP, 0);
						break;
					}
					else
					{
						/* the password is incorrect and send to HMI that password is incorrect */
						UART_sendByte(PASSWORD_INCORRECT);
						/* wait for replay from HMI ECU to take an action of incorrect password */
						if (UART_recieveByte() == BUZZER_ON)
						{
							/* if receiving buzzer on byte, that mean the 3 tries is made */
							/* turn on the buzzer */
							Buzzer_on();
							/* waiting for 1 minute */
							timer1DelaySecond(BUZZER_ACTIVE_PERIOD);
							/* turn off the buzzer */
							Buzzer_off();
							break;
						}
						else
						{
							continue;
						}
					}
				}
			}
			else if (mode == CHANGE_PASSWORD_MODE)
			{
				/* mode is change password mode */
				while (1)
				{
					/* receive the password and check if equal to the one in EEPROM */
					flag = recivePasswordAndCheck();

					if (flag == TRUE)
					{
						/* the password is correct and send to HMI that password is correct */
						UART_sendByte(PASSWORD_CORRECT);
						/* start the action of change password */
						savePasswordToEEPROM();
						break;
					}
					else
					{
						/* the password is incorrect and send to HMI that password is incorrect */
						UART_sendByte(PASSWORD_INCORRECT);
						if (UART_recieveByte() == BUZZER_ON)
						{
							/* if receiving buzzer on byte, that mean the 3 tries is made */
							/* turn on the buzzer */
							Buzzer_on();
							/* waiting for 1 minute */
							timer1DelaySecond(BUZZER_ACTIVE_PERIOD);
							/* turn off the buzzer */
							Buzzer_off();
							break;
						}
						else
						{
							continue;
						}
					}
				}
			}
		}
	}
}

/*******************************************************************************
 *                           Functions Definitions                            *
 *******************************************************************************/

/*
 * Description :
 * Function to save the received password through UART to EEPROM.
 * Function input:  void.
 * Function output: void.
 */
void savePasswordToEEPROM(void)
{
	uint8 i, temp;
	i = 0;
	while (i < PASSWORD_LENGTH)
	{
		/* revive password byte by byte through the UART */
		temp = UART_recieveByte();
		/* write byte by byte to the EEPROM */
		EEPROM_writeByte(EEPROM_FIRST_ADDRESS_VALUE + i, temp);
		_delay_ms(10);
		i++;
		/* send to HMI ECU that the control ECU is ready to receive the next byte */
		UART_sendByte(START_COMMNUCATION);
	}
}

/*
 * Description :
 * Function to receive password through UART and check
 * it with the one in EEPROM .
 * Function input:  void.
 * Function output: uint8 flag which indicate password correct.
 */
uint8 recivePasswordAndCheck()
{
	uint8 i, temp, temp2, flag;
	i = 0;
	/* we suppose at first the password is correct */
	flag = TRUE;
	while (i < PASSWORD_LENGTH)
	{
		/* revive password byte by byte through the UART */
		temp = UART_recieveByte();
		/* read byte by byte from the EEPROM */
		EEPROM_readByte(EEPROM_FIRST_ADDRESS_VALUE + i, &temp2);
		/* compare the received byte with the byte in EEPROM */
		if (temp != temp2)
		{
			/* if not equal then two passwords are not equal and flag become false */
			flag = FALSE;
		}
		i++;
		/* send to HMI ECU that the control ECU is ready to receive the next byte */
		UART_sendByte(START_COMMNUCATION);
	}
	return flag;
}

/*
 * Description :
 * Function to count a number of seconds which passed to it.
 * Function input:  number of seconds.
 * Function output: void.
 */
void timer1DelaySecond(uint8 n)
{
	/* select the configuration of TIMER1 */
	TIMER1_ConfigType TIMER1_config =
	{ CTC_INITIAL_VALUE, CTC_VALUE_FOR_ONE_SECOND, CTC_MODE,
			TIMER1_PRESCALER_256 };
	/* setup the call back function */
	Timer1_setCallBack(countOneSecond);
	/* passing the configuration to initialization function of TIMER1 */
	Timer1_init(&TIMER1_config);
	/* waiting for 15 seconds until the door is unlocking */
	while (g_ticks < n)
		;
	/* reset the global variable of ticks */
	g_ticks = 0;
	/* stop the timer1 */
	Timer1_deInit();
}

/*
 * Description :
 * This is the call back function which will be executed each interrupt in timer1.
 * Function input:  void.
 * Function output: void.
 */
void countOneSecond()
{
	/* this function is executed each 1 second as the configuration that passed to timer1*/
	g_ticks++;
}
