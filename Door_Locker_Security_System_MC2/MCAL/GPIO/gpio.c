/*
 ============================================================================
 File Name   : gpio.c
 Author      : Ahmed Ali
 Module      : GPIO
 Layer       : MCAL
 Date        : 23 Sept 2023
 Description : Source file for the AVR GPIO driver
 ============================================================================
 */

#include "gpio.h"
#include "../../LIB/common_macros.h" /* To use the macros like SET_BIT */
#include "../../MCAL/GPIO/gpio_private.h" /* To use the IO Ports Registers */

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch (port_num)
		{
		case PORTA_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA_REG.Byte, pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA_REG.Byte, pin_num);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB_REG.Byte, pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB_REG.Byte, pin_num);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC_REG.Byte, pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC_REG.Byte, pin_num);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD_REG.Byte, pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD_REG.Byte, pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin value as required */
		switch (port_num)
		{
		case PORTA_ID:
			if (value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTA_REG.Byte, pin_num);
			}
			else
			{
				SET_BIT(PORTA_REG.Byte, pin_num);
			}
			break;
		case PORTB_ID:
			if (value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTB_REG.Byte, pin_num);
			}
			else
			{
				SET_BIT(PORTB_REG.Byte, pin_num);
			}
			break;
		case PORTC_ID:
			if (value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTC_REG.Byte, pin_num);
			}
			else
			{
				SET_BIT(PORTC_REG.Byte, pin_num);
			}
			break;
		case PORTD_ID:
			if (value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTD_REG.Byte, pin_num);
			}
			else
			{
				SET_BIT(PORTD_REG.Byte, pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 value = LOGIC_LOW;
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Return the pin value */
		switch (port_num)
		{
		case PORTA_ID:
			if (BIT_IS_SET(PINA_REG.Byte, pin_num))
			{
				value = LOGIC_HIGH;
			}
			else
			{
				value = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if (BIT_IS_SET(PINB_REG.Byte, pin_num))
			{
				value = LOGIC_HIGH;
			}
			else
			{
				value = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if (BIT_IS_SET(PINC_REG.Byte, pin_num))
			{
				value = LOGIC_HIGH;
			}
			else
			{
				value = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if (BIT_IS_SET(PIND_REG.Byte, pin_num))
			{
				value = LOGIC_HIGH;
			}
			else
			{
				value = LOGIC_LOW;
			}
			break;
		}
	}
	return value;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch (port_num)
		{
		case PORTA_ID:
			DDRA_REG.Byte = direction;
			break;
		case PORTB_ID:
			DDRB_REG.Byte = direction;
			break;
		case PORTC_ID:
			DDRC_REG.Byte = direction;
			break;
		case PORTD_ID:
			DDRD_REG.Byte = direction;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port value as required */
		switch (port_num)
		{
		case PORTA_ID:
			PORTA_REG.Byte = value;
			break;
		case PORTB_ID:
			PORTB_REG.Byte = value;
			break;
		case PORTC_ID:
			PORTC_REG.Byte = value;
			break;
		case PORTD_ID:
			PORTD_REG.Byte = value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_num >= NUM_OF_PORTS)
	{
		return 0;
	}
	else
	{
		/* Return the pin value */
		switch (port_num)
		{
		case PORTA_ID:
			value = PINA_REG.Byte;
			break;
		case PORTB_ID:
			value = PINB_REG.Byte;
			break;
		case PORTC_ID:
			value = PINC_REG.Byte;
			break;
		case PORTD_ID:
			value = PIND_REG.Byte;
			break;
		}
	}
	return value;
}
