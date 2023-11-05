/*
 ============================================================================
 Name        : twi.h
 Author      : Ahmed Ali
 Module Name : TWI(I2C)
 Layer       : MCAL
 Date        : 24 Oct 2023
 Description : Header file for the AVR TWI(I2C) driver
 ============================================================================
 */

#ifndef TWI_H_
#define TWI_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef uint8 TWI_Address_Type;

typedef enum
{
	TWI_PRESCALER_1, TWI_PRESCALER_4, TWI_PRESCALER_16, TWI_PRESCALER_64
} TWI_Prescaler_Type;

typedef struct
{
	TWI_Address_Type address;
	TWI_Prescaler_Type Prescaler;
} TWI_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START        	0x08 /* start has been sent */
#define TWI_REP_START   	0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK 	0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK 	0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK  	0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   	0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  	0x58 /* Master received data but doesn't send ACK to slave. */

#define MC_ADDRESS 			0x01

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the TWI driver
 * 	1. Set the required address.
 * 	2. Set the required Prescaler.
 * 	3. Set the required bit_rate.
 * 	4. Enable TWI.
 */
void TWI_init(const TWI_ConfigType *Config_Ptr);

/*
 * Description : Function to send start bit to the frame.
 */
void TWI_start(void);

/*
 * Description : Function to send stop bit to the frame.
 */
void TWI_stop(void);

/*
 * Description : Function to write a data on TWI data Register and send it.
 */
void TWI_writeByte(uint8 data);

/*
 * Description : Function to read a data and send ACK after reading.
 */
uint8 TWI_readByteWithACK(void);

/*
 * Description : Function to read a data and send NACK after reading.
 */
uint8 TWI_readByteWithNACK(void);

/*
 * Description : Function to get the TWSR register value(status).
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
