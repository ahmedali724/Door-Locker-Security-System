/*
 ============================================================================
 Name        : twi.c
 Author      : Ahmed Ali
 Module Name : TWI(I2C)
 Layer       : MCAL
 Date        : 24 Oct 2023
 Description : Source file for the AVR TWI(I2C) driver
 ============================================================================
 */

#include "../I2C/twi.h"
#include "../I2C/twi_private.h"

/*
 * Description : Function to initialize the TWI driver
 * 	1. Set the required address.
 * 	2. Set the required Prescaler.
 * 	3. Set the required Prescaler bit_rate.
 * 	4. Enable TWI.
 */
void TWI_init(const TWI_ConfigType *Config_Ptr)
{
	/*
	 * Bit Rate: 400.000 kbps and F_CPU=8Mhz
	 * Insert the prescaler in (TWPS0 and TWPS1) Bits in TWSR register.
	 */
	switch (Config_Ptr->Prescaler)
	{
	case TWI_PRESCALER_1:
		TWBR_REG.Byte = 0x02;
		TWSR_REG.Bits.TWPS0_Bit = 0;
		TWSR_REG.Bits.TWPS1_Bit = 0;
		break;
	case TWI_PRESCALER_4:
		TWBR_REG.Byte = 0x00;
		TWSR_REG.Bits.TWPS0_Bit = 1;
		TWSR_REG.Bits.TWPS1_Bit = 0;
		break;
	case TWI_PRESCALER_16:
		TWBR_REG.Byte = 0x00;
		TWSR_REG.Bits.TWPS0_Bit = 0;
		TWSR_REG.Bits.TWPS1_Bit = 1;
		break;
	case TWI_PRESCALER_64:
		TWBR_REG.Byte = 0x00;
		TWSR_REG.Bits.TWPS0_Bit = 1;
		TWSR_REG.Bits.TWPS1_Bit = 1;
		break;
	}

	/* Insert the required address in TWAR salve address register */
	TWAR_REG.Byte = ((Config_Ptr->address) << 1);

	/* Enable TWI */
	TWCR_REG.Bits.TWEN_Bit = 1;
}

/*
 * Description : Function to send start bit to the frame.
 */
void TWI_start(void)
{
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in generate start condition mode
	 * TWSTA  = 1 generating start condition
	 * TWEA   = 0 We don't need to generate acknowledge pulse in generate start condition mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR_REG.Byte = 0xA4;

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (TWCR_REG.Bits.TWINT_Bit == 0)
		;
}

/*
 * Description : Function to send stop bit to the frame.
 */
void TWI_stop(void)
{
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 1 generating stop condition
	 * TWSTA  = 0 We don't need to generate start condition in generate stop condition mode
	 * TWEA   = 0 We don't need to generate acknowledge pulse in generate stop condition mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR_REG.Byte = 0x94;
}

/*
 * Description : Function to write a data on TWI data Register and send it.
 */
void TWI_writeByte(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR_REG.Byte = data;

	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in send data mode
	 * TWSTA  = 0 We don't need to generate start condition in send data mode
	 * TWEA   = 0 We don't need to generate acknowledge pulse in send data mode
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR_REG.Byte = 0x84;

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (TWCR_REG.Bits.TWINT_Bit == 0)
		;
}

/*
 * Description : Function to read a data and send ACK after reading.
 */
uint8 TWI_readByteWithACK(void)
{
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in receive mode
	 * TWSTA  = 0 We don't need to generate start condition in receive mode
	 * TWEA   = 1 generating acknowledge pulse
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR_REG.Byte = 0XC4;

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (TWCR_REG.Bits.TWINT_Bit == 0)
		;
	/* Read Data */
	return (TWDR_REG.Byte);
}

/*
 * Description : Function to read a data and send NACK after reading.
 */
uint8 TWI_readByteWithNACK(void)
{
	/************************** TWCR Description **************************
	 * TWIE   = 0 Disable TWI Interrupt
	 * TWEN   = 1 Enable TWI Module
	 * TWSTO  = 0 We don't need to generate stop condition in receive mode
	 * TWSTA  = 0 We don't need to generate start condition in receive mode
	 * TWEA   = 0 We don't need to generate acknowledge pulse as we are in receive mode with NACK
	 * TWINT  = 1 Clear the TWINT flag before reading the data
	 ***********************************************************************/
	TWCR_REG.Byte = 0x84;

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (TWCR_REG.Bits.TWINT_Bit == 0)
		;
	/* Read Data */
	return (TWDR_REG.Byte);
}

/*
 * Description : Function to get the TWSR register value(status).
 */
uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = (TWSR_REG.Byte) & 0xF8;
	return status;
}
