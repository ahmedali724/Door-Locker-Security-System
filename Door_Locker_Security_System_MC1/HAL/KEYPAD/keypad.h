/*
 ============================================================================
 File Name   : keypad.h
 Author      : Ahmed Ali
 Module      : KEYPAD
 Layer       : HAL
 Date        : 26 Sept 2023
 Description : Header file for the Keypad driver
 ============================================================================
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIB/std_types.h"

/*
 * If using driver in eta32_mini kit, then define this
 *
 * #define STANDARD_KEYPAD
 */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN4_ID

#define KEYPAD_COL_PORT_ID                PORTD_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN2_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
