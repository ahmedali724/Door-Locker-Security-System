/*
 ============================================================================
 Name        : HMI_ECU.c
 Author      : Ahmed Ali
 Layer       : APP
 Date        : 25 Oct 2023
 Description : The main function of project
 ============================================================================
 */

#include "HAL/LCD/lcd.h" /* to use LCD functions */
#include "HAL/KEYPAD/keypad.h" /* to use KEYPAD functions */
#include "MCAL/UART/uart.h" /* to use UART functions */
#include "MCAL/TIMER1/timer1.h" /* to use TIMER1 init function */
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

#define START_COMMNUCATION			    0x15
#define CTC_VALUE_FOR_ONE_SECOND 		31250
#define CTC_INITIAL_VALUE 				0
#define PASSWORD_CORRECT            	0xAA
#define PASSWORD_INCORRECT          	0xBB
#define CRETAE_PASSWORD_ACTION      	0xCC
#define CHECK_PASSWORD_ACTION       	0xDD
#define CHANGE_PASSWORD_MODE        	0xEE
#define OPEN_DOOR_MODE              	0xFF
#define BUZZER_ON                   	0x68
#define BUZZER_OFF               	   	0x69
#define PASSWORD_LENGTH					5
#define DOOR_UNLOKING_PERIOD        	15
#define DOOR_LOKING_PERIOD          	15
#define DOOR_HOLD_PERIOD            	3
#define NUMBER_OF_TRIES_FOR_PASSWORD 	3
#define BUZZER_ACTIVE_PERIOD			60

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description :
 * Function to create password and save it to EEPROM following this steps:
 * 1. Take password and confirm password from user.
 * 2. Compare the two passwords.
 * 3. If the two passwords are matched, then send it through UART
 * 	  to control ECU and save it to EEPROM.
 * 4. If the two passwords are not matched, then repeat step1.
 * Function input:  void.
 * Function output: void.
 */
uint8 createPassword(void);

/*
 * Description :
 * Function to active keypad to get input number from it.
 * Function input:  array of uint8 to save numbers from keypad on it.
 * Function output: void.
 */
void getPasswordFromKeyPad(uint8 password[]);

/*
 * Description :
 * Function to take confirm password then compare it with password and return if matched or not.
 * Function input:  two arrays of uint8 to compare between them.
 * Function output: uint8 flag that indicate the matching of passwords.
 */
uint8 comparePasswords(uint8 password[], uint8 confirmPassword[]);

/*
 * Description :
 * Function to send password through UART to control ECU.
 * Function input:  array of uint8 to send it to control ECU.
 * Function output: void.
 */
void sendPasswordToControlECU(uint8 password[]);

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
	uint8 temp, try, passwordIsCreated, passwordIsChanged;
	uint8 password[5];
	/* select the configuration of UART */
	UART_ConfigType UART_config =
	{ ASYNCHRONOUS, DISABLED_PARITY, STOP_1_BIT, DATA_8_BIT, BAUD_RATE_9600 };

	/* passing the configuration to initialization function of UART */
	UART_init(&UART_config);
	/* call the initialization function of LCD */
	LCD_init();

	LCD_clearScreen();
	LCD_displayString("  Final Project ");
	LCD_moveCursor(1, 0);
	LCD_displayString("Edges Diploma 79");
	_delay_ms(250);
	LCD_clearScreen();
	LCD_displayString("     Made By    ");
	LCD_moveCursor(1, 0);
	LCD_displayString("    Ahmed Ali   ");
	_delay_ms(250);
	while (1)
	{
		/*
		 * select the action of create password at the start of program.
		 * the byte which sent to control ECU tell him to be ready to receive password
		 * after check matching here.
		 */
		UART_sendByte(CRETAE_PASSWORD_ACTION);
		/* at first we don't create any password */
		passwordIsCreated = FALSE;
		/* loop until the password is created and saved successfully to EEPROM */
		while (passwordIsCreated == FALSE)
		{
			passwordIsCreated = createPassword();
		}

		/* the main menu of program which contain open door and change password options */
		while (1)
		{
			LCD_clearScreen();
			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1, 0);
			LCD_displayString("- : Change Pass");
			/* get the option from user using keypad */
			temp = KEYPAD_getPressedKey();
			/* if choosing first option => open door */
			if (temp == '+')
			{
				/* variable which count the number of tries for user for enter password */
				try = 0;
				/*
				 * select the action of check password.
				 * the byte which sent to control ECU tell him to be ready to check
				 * the received password with the password in EEPROM.
				 */
				UART_sendByte(CHECK_PASSWORD_ACTION);
				/*
				 * select the mode of open door.
				 * the byte which sent to control ECU tell him to be ready for
				 * open door mode.
				 */
				UART_sendByte(OPEN_DOOR_MODE);
				while (1)
				{
					LCD_clearScreen();
					LCD_displayString("plz enter pass:");
					LCD_moveCursor(1, 0);
					/* take the password from user using keypad */
					getPasswordFromKeyPad(password);
					/* send the password to control ECU to check if correct or not */
					sendPasswordToControlECU(password);
					/* the control ECU will replay with a byte which indicate if password correct or not */
					if (UART_recieveByte() == PASSWORD_CORRECT)
					{
						/* the password is correct, then start open door mode */
						LCD_clearScreen();
						LCD_displayString("    Door is     ");
						LCD_moveCursor(1, 0);
						LCD_displayString("   Unlocking    ");
						/* waiting for 15 seconds until the door is unlocking */
						timer1DelaySecond(DOOR_UNLOKING_PERIOD);
						/* waiting for 3 seconds the hold period of the door */
						timer1DelaySecond(DOOR_HOLD_PERIOD);
						LCD_clearScreen();
						LCD_displayString("    Door is     ");
						LCD_moveCursor(1, 0);
						LCD_displayString("    locking     ");
						/* waiting for 15 seconds until the door is locking */
						timer1DelaySecond(DOOR_LOKING_PERIOD);
						/* reset the tries variable */
						try = 0;
						break;
					}
					else
					{
						LCD_clearScreen();
						LCD_displayString("Wrong Password");
						_delay_ms(250);
						/* each time the entered password is incorrect, the try variable increment by 1 */
						try++;
						/* if the tries reach to 3, send to control ECU to enable the buzzer */
						if (try == NUMBER_OF_TRIES_FOR_PASSWORD)
						{
							UART_sendByte(BUZZER_ON);
						}
						else
						{
							UART_sendByte(BUZZER_OFF);
						}
					}
					/* if the tries reach to 3, display error massage on LCD */
					if (try == NUMBER_OF_TRIES_FOR_PASSWORD)
					{
						LCD_clearScreen();
						LCD_displayString("     ERROR      ");
						LCD_moveCursor(1, 0);
						LCD_displayString(" WRONG 3 TRIES  ");
						/* waiting for 1 minute for the */
						timer1DelaySecond(BUZZER_ACTIVE_PERIOD);
						/* reset the tries variable */
						try = 0;
						break;
					}
				}
			}
			/* if choosing second option => change password */
			else if (temp == '-')
			{
				/* variable which count the number of tries for user for enter password */
				try = 0;
				/*
				 * select the action of check password.
				 * the byte which sent to control ECU tell him to be ready to check
				 * the received password with the password in EEPROM.
				 */
				UART_sendByte(CHECK_PASSWORD_ACTION);
				/*
				 * select the mode of open door.
				 * the byte which sent to control ECU tell him to be ready for
				 * change password mode.
				 */
				UART_sendByte(CHANGE_PASSWORD_MODE);
				while (1)
				{
					LCD_clearScreen();
					LCD_displayString("plz enter pass:");
					LCD_moveCursor(1, 0);
					/* take the password from user using keypad */
					getPasswordFromKeyPad(password);
					/* send the password to control ECU to check if correct or not */
					sendPasswordToControlECU(password);
					/* the control ECU will replay with a byte which indicate if password correct or not */
					if (UART_recieveByte() == PASSWORD_CORRECT)
					{
						LCD_clearScreen();
						LCD_displayString("Correct Password");
						_delay_ms(250);
						passwordIsChanged = FALSE;
						/* loop until the password is changed and saved successfully to EEPROM */
						while (passwordIsChanged == FALSE)
						{
							passwordIsChanged = createPassword();
						}
						LCD_clearScreen();
						LCD_displayString("Password Changed");
						LCD_moveCursor(1, 0);
						LCD_displayString("  Successfully  ");
						_delay_ms(250);
						/* reset the tries variable */
						try = 0;
						break;
					}
					else
					{
						LCD_clearScreen();
						LCD_displayString("Wrong Password");
						_delay_ms(250);
						/* each time the entered password is incorrect, the try variable increment by 1 */
						try++;
						/* if the tries reach to 3, send to control ECU to enable the buzzer */
						if (try == NUMBER_OF_TRIES_FOR_PASSWORD)
						{
							UART_sendByte(BUZZER_ON);
						}
						else
						{
							UART_sendByte(BUZZER_OFF);
						}
					}
					/* if the tries reach to 3, display error massage on LCD */
					if (try == NUMBER_OF_TRIES_FOR_PASSWORD)
					{
						LCD_clearScreen();
						LCD_displayString("     ERROR      ");
						LCD_moveCursor(1, 0);
						LCD_displayString(" WRONG 3 TRIES  ");
						/* waiting for 1 minute for the */
						timer1DelaySecond(BUZZER_ACTIVE_PERIOD);
						/* reset the tries variable */
						try = 0;
						break;
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
 * Function to create password and save it to EEPROM following this steps:
 * 1. Take password and confirm password from user.
 * 2. Compare the two passwords.
 * 3. If the two passwords are matched, then send it through UART
 * 	  to control ECU and save it to EEPROM.
 * 4. If the two passwords are not matched, then repeat step1.
 * Function input:  void.
 * Function output: void.
 */
uint8 createPassword()
{
	uint8 password[5]; /* array to save password on it */
	uint8 confirmPassword[5]; /* array to save confirm password on it */
	uint8 flag; /* flag to indicate the matching of two passwords */
	while (1)
	{
		LCD_clearScreen();
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1, 0);
		/* take the password form keypad and save it to password array */
		getPasswordFromKeyPad(password);
		LCD_clearScreen();
		LCD_displayString("plz re-enter pass the:");
		LCD_moveCursor(1, 0);
		LCD_displayString("same pass: ");
		LCD_moveCursor(1, 11);
		/* take the confirm password form keypad and compare it with password */
		flag = comparePasswords(password, confirmPassword);
		/* if flag became true, that mean the two passwords are matched */
		if (flag == TRUE)
		{
			/* then send password to control ECU to save it in EEPROM */
			sendPasswordToControlECU(password);
			LCD_clearScreen();
			LCD_displayString("The 2 Passwords");
			LCD_moveCursor(1, 0);
			LCD_displayString("Are Equal :)");
			_delay_ms(250);
			/* return true to not repeat this step as password created successfully */
			return TRUE;
			break;
		}
		else
		{
			LCD_clearScreen();
			LCD_displayString("The 2 Passwords");
			LCD_moveCursor(1, 0);
			LCD_displayString("Are Not Equal :(");
			_delay_ms(250);
			/* return false to repeat this step as password is not created successfully */
			return FALSE;
		}
	}
}

/*
 * Description :
 * Function to active keypad to get input number from it.
 * Function input:  array of uint8 to save numbers from keypad on it.
 * Function output: void.
 */
void getPasswordFromKeyPad(uint8 password[])
{
	uint8 i, temp;
	i = 0; /* the index and counter for the loop and equal 5 as password is 5 numbers */
	while (i < PASSWORD_LENGTH)
	{
		/* take the input number form keypad */
		temp = KEYPAD_getPressedKey();
		/* wait 250msec before getting a new press from the keypad buttons, Press time is 250msec */
		_delay_ms(250);
		/* if the input is not a number form 0 to 9 then repeat taking input step */
		/* ^ for the keys don't have a number or # or - or + */
		if (temp == '^' || temp == '#' || temp == '-' || temp == '+')
		{
			continue;
		}
		/* the input is a number, then save it to its index in array */
		password[i] = temp;
		/* display the * char in LCD */
		LCD_displayCharacter('*');
		/* increment the index */
		i++;
	}
	/* waiting for pressing enter key */
	while (KEYPAD_getPressedKey() != '#')
		;
}

/*
 * Description :
 * Function to take confirm password then compare it with password and return if matched or not.
 * Function input:  two arrays of uint8 to compare between them.
 * Function output: uint8 flag that indicate the matching of passwords.
 */
uint8 comparePasswords(uint8 password[], uint8 confirmPassword[])
{
	uint8 i, temp, matchingFlag = TRUE;
	i = 0;
	while (i < PASSWORD_LENGTH)
	{
		/* take the input number form keypad */
		temp = KEYPAD_getPressedKey();
		/* wait 250msec before getting a new press from the keypad buttons, Press time is 250msec */
		_delay_ms(250);
		/* if the input is not a number form 0 to 9 then repeat taking input step */
		if (temp == '^' || temp == '#' || temp == '-' || temp == '+')
		{
			continue;
		}
		/* the input is a number, then save it to its index in array */
		confirmPassword[i] = temp;
		/* check each element of both array if equal or not */
		if (confirmPassword[i] != password[i])
		{
			/* if not equal then two passwords are not matched and flag become false */
			matchingFlag = FALSE;
		}
		/* display the * char in LCD */
		LCD_displayCharacter('*');
		/* increment the index */
		i++;
	}
	/* waiting for pressing enter key */
	while (KEYPAD_getPressedKey() != '#')
		;
	/* return the matching flag */
	return matchingFlag;
}

/*
 * Description :
 * Function to send password through UART to control ECU.
 * Function input:  array of uint8 to send it to control ECU.
 * Function output: void.
 */
void sendPasswordToControlECU(uint8 password[])
{
	uint8 i;
	i = 0;
	while (i < PASSWORD_LENGTH)
	{
		/* send the password byte by byte to control ECU through UART  */
		UART_sendByte(password[i]);
		i++;
		/* waiting the replay from control that it is ready to receive again */
		while (UART_recieveByte() != START_COMMNUCATION)
			;
	}
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
