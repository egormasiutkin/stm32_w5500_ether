/*
 * motion_detect.c
 *
 *  Created on: Apr 5, 2021
 *      Author: yanik.richard
 */

#include "../Inc/motion_detect.h"
// #include "stm32f0xx_hal_gpio.h"
#include <stdbool.h>
#include "main.h"
#include "pcb_config.h"
#include "usart.h"
#include "Infrared.h"
/* Process States */

Motion_State motion_state_process = INITMOT;

/* Variables */
static unsigned long motion_time = 0;
static int motion_counter = 0;

static const unsigned long NUMBER_OF_COUNTS = 10;			  // 100 MS
static const unsigned long NUMBER_OF_COUNTS_NO_MOTION = 2000; // 1s
static const unsigned long TIME_INTERVAL = 10;				  // 10 ms
int PIR_Delay_ON = NUMBER_OF_COUNTS;
int PIR_Delay_OFF = NUMBER_OF_COUNTS_NO_MOTION;
/* Output*/
bool motion_detected = false;

void Set_PIR_Delay_OFF(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	PIR_Delay_ON = (uint32_t)(byte1 << 24) + (uint32_t)(byte2 << 16) + (uint32_t)(byte3 << 8) + byte4;
	;
}
void Set_PIR_Delay_ON(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	PIR_Delay_OFF = (uint32_t)(byte1 << 24) + (uint32_t)(byte2 << 16) + (uint32_t)(byte3 << 8) + byte4;
	;
}

void Motion_Detection_Process()
{
	/* State Machine switch */
	switch (motion_state_process)
	{
	case INITMOT:
	{

		/* Next state -> NO_WATER */
		motion_state_process = NO_MOTION;

		/* By default, no water is detected */
		motion_detected = false;

		/* Get t0 */
		motion_time = HAL_GetTick();

		break;
	}

	case NO_MOTION:
	{
		/* If 100 ms has passed since t0 (10 Hz sampling) */
		if ((HAL_GetTick() - motion_time) >= TIME_INTERVAL)
		{
			/* Reinitialize timer */
			motion_time = HAL_GetTick();

			/* If Freq < LOW_FREQ water is present : increment counter */
			if ((HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) == GPIO_PIN_SET))
			{
				motion_counter++;
				motion_state_process = NO_MOTION;
			}

			/* Else restart the measuring */
			else
			{
				motion_counter = 0;
				motion_detected = false;

				motion_state_process = NO_MOTION;
			}

			/* When 5 consecutive readings are lower than LOW_FREQ water is present */

			int decthousand_min = (pcb_config.sPIRDelayON[0] - '0') * 1000;
			int dechundred_min = (pcb_config.sPIRDelayON[1] - '0') * 100;
			int decten_min = (pcb_config.sPIRDelayON[2] - '0') * 10;
			int dec_min = (pcb_config.sPIRDelayON[3] - '0');
			PIR_Delay_ON = decthousand_min + dechundred_min + decten_min + dec_min;

			if (motion_counter >= PIR_Delay_ON)
			{
				motion_detected = true;
				motion_state_process = MOTION;
				motion_counter = 0;
				IRSend_Var_True();
				Send_Motion_Data(); // reply through uart
				// HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			}
		}

		break;
	}

	case MOTION:
	{
		/* If 100 ms has passed since t0 (10 Hz sampling) */
		if ((HAL_GetTick() - motion_time) >= TIME_INTERVAL)
		{

			/* Reinitialize timer */
			motion_time = HAL_GetTick();

			/* If Freq > LOW_FREQ no water is present : increment counter */
			if ((HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) == GPIO_PIN_RESET))
			{
				motion_counter++;
				motion_state_process = MOTION;
			}

			/* Else restart the measuring */
			else
			{
				motion_counter = 0;
				motion_detected = true;
				motion_state_process = MOTION;
			}

			/* When 20 consecutive readings are higher than HIGH_FREQ water is not present */

			int decthousand_min = (pcb_config.sPIRDelayOFF[0] - '0') * 1000;
			int dechundred_min = (pcb_config.sPIRDelayOFF[1] - '0') * 100;
			int decten_min = (pcb_config.sPIRDelayOFF[2] - '0') * 10;
			int dec_min = (pcb_config.sPIRDelayOFF[3] - '0');
			PIR_Delay_OFF = (decthousand_min + dechundred_min + decten_min + dec_min) * 6;
			if (motion_counter >= PIR_Delay_OFF)
			{
				motion_detected = false;
				motion_state_process = NO_MOTION;
				motion_counter = 0;
				IRSend_Var_True();
				Send_Motion_Data(); // reply through uart
				//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			}
		}

		break;
	}

	default:
		motion_state_process = INITMOT;

	} /* switch ( motion_state_process ) */
}

bool Motion_Is_Detected()
{
	return motion_detected;
}
