/*
 ============================================================================
 File Name   : external_eeprom.h
 Author      : Ahmed Ali
 Module      : EEPROM
 Layer       : HAL
 Date        : 24 Oct 2023
 Description : Header file for the External EEPROM Memory
 ============================================================================
 */

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);

#endif /* EXTERNAL_EEPROM_H_ */
