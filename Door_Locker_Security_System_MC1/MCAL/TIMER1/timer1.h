/*
 ============================================================================
 Name        : timer1.h
 Author      : Ahmed Ali
 Module Name : TIMER1
 Layer       : MCAL
 Date        : 16 Oct 2023
 Description : Header file for the AVR TIMER1 driver
 ============================================================================
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NORMAL_MODE = 0, CTC_MODE = 4
} TIMER1_ModeType;

typedef enum
{
	TIMER1_NO_CLOCK_SOURCE,
	TIMER1_PRESCALER_1,
	TIMER1_PRESCALER_8,
	TIMER1_PRESCALER_64,
	TIMER1_PRESCALER_256,
	TIMER1_PRESCALER_1024
} TIMER1_PrescalerType;

typedef struct
{
	uint16 initial_value;
	uint16 compare_value; /* for CTC mode only */
	TIMER1_ModeType mode;
	TIMER1_PrescalerType prescaler;
} TIMER1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the Timer driver.
 */
void Timer1_init(const TIMER1_ConfigType *Config_Ptr);

/*
 * Description :
 * Function to disable the Timer1.
 */
void Timer1_deInit(void);

/*
 * Description :
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void (*a_ptr)(void));

#endif /* TIMER1_H_ */
