/*
 ============================================================================
 Name        : twi_private.h
 Author      : Ahmed Ali
 Module Name : TWI(I2C)
 Layer       : MCAL
 Date        : 24 Oct 2023
 Description : Private file for the AVR TWI(I2C) driver
 ============================================================================
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                 TWI Registers type structure declarations                   *
 *******************************************************************************/

/* Bitmap structure for TWBR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TWBR0_Bit :1; /* TWBR0 bit 0 */
		uint8 TWBR1_Bit :1; /* TWBR1 bit 1 */
		uint8 TWBR2_Bit :1; /* TWBR2 bit 2 */
		uint8 TWBR3_Bit :1; /* TWBR3 bit 3 */
		uint8 TWBR4_Bit :1; /* TWBR4 bit 4 */
		uint8 TWBR5_Bit :1; /* TWBR5 bit 5 */
		uint8 TWBR6_Bit :1; /* TWBR6 bit 6 */
		uint8 TWBR7_Bit :1; /* TWBR7 bit 7 */
	} Bits;
} TWI_TWBR_Type;

/* Bitmap structure for TWCR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TWIE_Bit :1; /* TWIE bit 0 */
		uint8 :1; /* Reserved bit 1 */
		uint8 TWEN_Bit :1; /* TWEN bit 2 */
		uint8 TWWC_Bit :1; /* TWWC bit 3 */
		uint8 TWSTO_Bit :1; /* TWSTO bit 4 */
		uint8 TWSTA_Bit :1; /* TWSTA bit 5 */
		uint8 TWEA_Bit :1; /* TWEA bit 6 */
		uint8 TWINT_Bit :1; /* TWINT bit 7 */
	} Bits;
} TWI_TWCR_Type;

/* Bitmap structure for TWSR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TWPS0_Bit :1; /* TWIE bit 0 */
		uint8 TWPS1_Bit :1; /* TWPS1 bit 1 */
		uint8 :1; /* Reserved bit 2 */
		uint8 TWS3_Bit :1; /* TWS3 bit 3 */
		uint8 TWS4_Bit :1; /* TWS4 bit 4 */
		uint8 TWS5_Bit :1; /* TWS5 bit 5 */
		uint8 TWS6_Bit :1; /* TWS6 bit 6 */
		uint8 TWS7_Bit :1; /* TWS7 bit 7 */
	} Bits;
} TWI_TWSR_Type;

/* Bitmap structure for TWDR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TWD0_Bit :1; /* TWD0 bit 0 */
		uint8 TWD1_Bit :1; /* TWD1 bit 1 */
		uint8 TWD2_Bit :1; /* TWD2 bit 2 */
		uint8 TWD3_Bit :1; /* TWD3 bit 3 */
		uint8 TWD4_Bit :1; /* TWD4 bit 4 */
		uint8 TWD5_Bit :1; /* TWD5 bit 5 */
		uint8 TWD6_Bit :1; /* TWD6 bit 6 */
		uint8 TWD7_Bit :1; /* TWD7 bit 7 */
	} Bits;
} TWI_TWDR_Type;

/* Bitmap structure for TWAR register */
typedef union
{
	uint8 Byte; /* All register bits */
	struct
	{
		uint8 TWGCE_Bit :1; /* TWGCE bit 0 */
		uint8 TWA0_Bit :1; /* TWA0 bit 1 */
		uint8 TWA1_Bit :1; /* TWA1 bit 2 */
		uint8 TWA2_Bit :1; /* TWA2 bit 3 */
		uint8 TWA3_Bit :1; /* TWA3 bit 4 */
		uint8 TWA4_Bit :1; /* TWA4 bit 5 */
		uint8 TWA5_Bit :1; /* TWA5 bit 6 */
		uint8 TWA6_Bit :1; /* TWA6 bit 7 */
	} Bits;
} TWI_TWAR_Type;

/*******************************************************************************
 *                         TWI Registers Definitions                           *
 *******************************************************************************/

/* definition for TWBR registers */
#define TWBR_REG (*(volatile TWI_TWBR_Type *const) 0x20)

/* definition for TWSR registers */
#define TWSR_REG (*(volatile TWI_TWSR_Type *const) 0x21)

/* definition for TWAR registers */
#define TWAR_REG (*(volatile TWI_TWAR_Type *const) 0x22)

/* definition for TWDR registers */
#define TWDR_REG (*(volatile TWI_TWDR_Type *const) 0x23)

/* definition for TWCR registers */
#define TWCR_REG (*(volatile TWI_TWCR_Type *const) 0x56)

#endif /* TWI_PRIVATE_H_ */
