/*
 * loop.c
 *
 *  Created on: Mar 7, 2024
 *      Author: Camille Chevrier
 */

#include "main.h"

#include <stdbool.h>

#include "loop.h"
#include "Infrared.h"
#include "pcb_config.h"

/* Loop Process States */

Loop_State loop_state_process = LOOP_INIT;
uint8_t is_loop_continue = 0;
uint8_t is_loop_process_on_started = 0;
uint8_t is_loop_process_off_started = 0;
static unsigned long loop_time = 0;

void loop_process(void)
{
	/* State Machine switch */
	switch (loop_state_process)
	{
	case LOOP_INIT:
	{
		/* Next state -> NO_LOOP */
		loop_state_process = NO_LOOP;

		/* By default, loop is not continue */
		is_loop_continue = 0;
		is_loop_process_on_started = 0;
		is_loop_process_off_started = 0;

		break;
	}
	case NO_LOOP:
	{
		is_loop_process_on_started = 0;
		is_loop_process_off_started = 0;

		if (Motion_Is_Detected())
		{
			/* Next state -> LOOP_PROCESS_ON */
			loop_state_process = LOOP_PROCESS_ON;
		}

		break;
	}
	case LOOP_PROCESS_ON:
	{
		if (is_loop_process_on_started == 0)
		{
			if (pcb_config.sSetIRON[0] - '0')
			{
				IRSend_NEC(true);
			}
			if (pcb_config.sSetRS232ON[0] - '0')
			{
				Send_RS232_Command_ON();
			}

			/* Get t0 */
			loop_time = HAL_GetTick();

			is_loop_process_on_started = 1;
		}
		else if (is_loop_process_on_started == 1)
		{
			if (pcb_config.loopon == 1 && pcb_config.looptime >= 1)
			{
				/* If looptime has passed since t0 */
				if (((HAL_GetTick() - loop_time) >= (pcb_config.looptime * 1000)) && Motion_Is_Detected() != false)
				{
					if (pcb_config.sSetIRON[0] - '0')
					{
						IRSend_NEC(true);
					}
					if (pcb_config.sSetRS232ON[0] - '0')
					{
						Send_RS232_Command_ON();
					}

					/* Reinitialize timer */
					loop_time = HAL_GetTick();
				}
				else if (Motion_Is_Detected() == false)
				{
					/* Next state -> LOOP_PROCESS_OFF */
					loop_state_process = LOOP_PROCESS_OFF;

					is_loop_process_on_started = 0;
				}
			}
			else
			{
				/* Next state -> LOOP_PROCESS_OFF */
				loop_state_process = LOOP_PROCESS_OFF;

				is_loop_process_on_started = 0;
			}
		}

		break;
	}
	case LOOP_PROCESS_OFF:
	{
		if (is_loop_process_off_started == 0)
		{
			if (pcb_config.sSetIRON[0] - '0')
			{
				IRSend_NEC(false);
			}
			if (pcb_config.sSetRS232ON[0] - '0')
			{
				Send_RS232_Command_OFF();
			}

			/* Get t0 */
			loop_time = HAL_GetTick();

			is_loop_process_off_started = 1;
		}
		else if (is_loop_process_off_started == 1)
		{
			if (pcb_config.loopoff == 1 && pcb_config.looptime >= 1)
			{
				/* If looptime has passed since t0 */
				if (((HAL_GetTick() - loop_time) >= (pcb_config.looptime * 1000)) && Motion_Is_Detected() != true)
				{
					if (pcb_config.sSetIRON[0] - '0')
					{
						IRSend_NEC(false);
					}
					if (pcb_config.sSetRS232ON[0] - '0')
					{
						Send_RS232_Command_OFF();
					}

					/* Reinitialize timer */
					loop_time = HAL_GetTick();
				}
				else if (Motion_Is_Detected() == true)
				{
					/* Next state -> NO_LOOP */
					loop_state_process = NO_LOOP;

					is_loop_process_off_started = 0;
				}
			}
			else
			{
				/* Next state -> LOOP_PROCESS_OFF */
				loop_state_process = NO_LOOP;

				is_loop_process_off_started = 0;
			}
		}
		break;
	}
	default:
		loop_state_process = LOOP_INIT;
	}
}
