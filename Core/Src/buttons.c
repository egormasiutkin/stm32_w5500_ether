/*
 * motion_detect.c
 *
 *  Created on: Apr 5, 2021
 *      Author: yanik.richard
 */

#include "../Inc/buttons.h"
// #include "stm32f0xx_hal_gpio.h"
#include <stdbool.h>
#include "main.h"
#include "pcb_config.h"
#include "usart.h"
/* Process States */
typedef enum
{
	INIT,
	BTN_NO_PRESS,
	BTN_PRESS
} BTN_State;
static BTN_State btn1_state_process = INIT;
static BTN_State btn2_state_process = INIT;
//static BTN_State btn3_state_process = INIT;
/* Variables */
static unsigned long btn1_time = 0;
static unsigned long btn2_time = 0;
//static unsigned long btn3_time = 0;
static int btn1_counter = 0;
static int btn2_counter = 0;
//static int btn3_counter = 0;

static const unsigned long NUMBER_OF_COUNTS = 12;		   // 100 MS
static const unsigned long NUMBER_OF_COUNTS_NO_MOTION = 5; // 1s
static const unsigned long TIME_INTERVAL = 20;			   // 10 ms
int BTN_Delay_ON = NUMBER_OF_COUNTS;
int BTN_Delay_OFF = NUMBER_OF_COUNTS_NO_MOTION;

/* Output*/
bool btn1_pressed = false;
bool btn2_pressed = false;
bool btn3_pressed = false;

void Btn1_Process()
{
	/* State Machine switch */
	switch (btn1_state_process)
	{
	case INIT:
	{

		/* Next state -> NO_WATER */
		btn1_state_process = BTN_NO_PRESS;

		/* By default, no water is detected */
		btn1_pressed = false;

		/* Get t0 */
		btn1_time = HAL_GetTick();

		break;
	}

	case BTN_NO_PRESS:
	{
		/* If 100 ms has passed since t0 (10 Hz sampling) */
		if ((HAL_GetTick() - btn1_time) >= TIME_INTERVAL)
		{
			/* Reinitialize timer */
			btn1_time = HAL_GetTick();

			/* If Freq < LOW_FREQ water is present : increment counter */
			if ((HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == GPIO_PIN_RESET))
			{
				btn1_counter++;
				btn1_state_process = BTN_NO_PRESS;
			}

			/* Else restart the measuring */
			else
			{
				btn1_counter = 0;
				// btn1_pressed = false;

				btn1_state_process = BTN_NO_PRESS;
			}

			/* When 5 consecutive readings are lower than LOW_FREQ water is present */

			if (btn1_counter >= BTN_Delay_ON)
			{
				btn1_pressed = true;
				btn1_state_process = BTN_PRESS;
				btn1_counter = 0;

				// Send_Version_Data(); //reply through uart
				// HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			}
		}

		break;
	}

	case BTN_PRESS:
	{
		/* If 100 ms has passed since t0 (10 Hz sampling) */
		if ((HAL_GetTick() - btn1_time) >= TIME_INTERVAL)
		{

			/* Reinitialize timer */
			btn1_time = HAL_GetTick();

			/* If Freq > LOW_FREQ no water is present : increment counter */
			if ((HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin) == GPIO_PIN_SET))
			{
				btn1_counter++;
				btn1_state_process = BTN_PRESS;
			}

			/* Else restart the measuring */
			else
			{
				btn1_counter = 0;
				//	btn1_pressed = true;
				btn1_state_process = BTN_PRESS;
			}

			/* When 20 consecutive readings are higher than HIGH_FREQ water is not present */

			if (btn1_counter >= BTN_Delay_OFF)
			{
				btn1_pressed = false;
				btn1_state_process = BTN_NO_PRESS;
				btn1_counter = 0;

				//	Send_Version_Data(); //reply through uart
				//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			}
		}

		break;
	}

	default:
		btn1_state_process = INIT;

	} /* switch ( motion_state_process ) */
}

void Btn2_Process()
{
	/* State Machine switch */
	switch (btn2_state_process)
	{
	case INIT:
	{

		/* Next state -> NO_WATER */
		btn2_state_process = BTN_NO_PRESS;

		/* By default, no water is detected */
		btn2_pressed = false;

		/* Get t0 */
		btn2_time = HAL_GetTick();

		break;
	}

	case BTN_NO_PRESS:
	{
		/* If 100 ms has passed since t0 (10 Hz sampling) */
		if ((HAL_GetTick() - btn2_time) >= TIME_INTERVAL)
		{
			/* Reinitialize timer */
			btn2_time = HAL_GetTick();

			/* If Freq < LOW_FREQ water is present : increment counter */
			if ((HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == GPIO_PIN_RESET))
			{
				btn2_counter++;
				btn2_state_process = BTN_NO_PRESS;
			}

			/* Else restart the measuring */
			else
			{
				btn2_counter = 0;
				// btn2_pressed = false;

				btn2_state_process = BTN_NO_PRESS;
			}

			/* When 5 consecutive readings are lower than LOW_FREQ water is present */

			if (btn2_counter >= BTN_Delay_ON)
			{
				btn2_pressed = true;
				btn2_state_process = BTN_PRESS;
				btn2_counter = 0;

				// Send_Version_Data(); //reply through uart
				// HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			}
		}

		break;
	}

	case BTN_PRESS:
	{
		/* If 100 ms has passed since t0 (10 Hz sampling) */
		if ((HAL_GetTick() - btn2_time) >= TIME_INTERVAL)
		{

			/* Reinitialize timer */
			btn2_time = HAL_GetTick();

			/* If Freq > LOW_FREQ no water is present : increment counter */
			if ((HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin) == GPIO_PIN_SET))
			{
				btn2_counter++;
				btn2_state_process = BTN_PRESS;
			}

			/* Else restart the measuring */
			else
			{
				btn2_counter = 0;
				// btn2_pressed = true;
				btn2_state_process = BTN_PRESS;
			}

			/* When 20 consecutive readings are higher than HIGH_FREQ water is not present */

			if (btn2_counter >= BTN_Delay_OFF)
			{
				btn2_pressed = false;
				btn2_state_process = BTN_NO_PRESS;
				btn2_counter = 0;

				//	Send_Version_Data(); //reply through uart
				//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			}
		}

		break;
	}

	default:
		btn2_state_process = INIT;

	} /* switch ( motion_state_process ) */
}

// void Btn3_Process()
//{
//	  /* State Machine switch */
//	  switch( btn3_state_process )
//	  {
//	  			  case INIT:
//	  			  {
//
//	  		        /* Next state -> NO_WATER */
//	  				btn3_state_process = BTN_NO_PRESS;
//
//	  				/* By default, no water is detected */
//	  				btn3_pressed = false;
//
//	  		        /* Get t0 */
//	  				btn3_time = HAL_GetTick();
//
//
//	  		        break;
//
//	  		      }
//
//	  		      case BTN_NO_PRESS:
//	  		      {
//	  		    	  /* If 100 ms has passed since t0 (10 Hz sampling) */
//	  		    	  if((HAL_GetTick() - btn3_time) >= TIME_INTERVAL)
//	  		    	  {
//	  		    		  /* Reinitialize timer */
//	  		    		btn3_time = HAL_GetTick();
//
//	  		    		  /* If Freq < LOW_FREQ water is present : increment counter */
//	  		    		  if ((HAL_GPIO_ReadPin(BTN_3_GPIO_Port,BTN_3_Pin) == GPIO_PIN_RESET))
//	  		  			  {
//	  		    			  btn3_counter++;
//	  		    			  btn3_state_process = BTN_NO_PRESS;
//	  		  			  }
//
//	  		    		  /* Else restart the measuring */
//	  		  		  	  else
//	  		  			  {
//	  		  		  		  btn3_counter = 0;
//	  		  		  		 // btn2_pressed = false;
//
//	  		  		  		  btn3_state_process = BTN_NO_PRESS;
//	  		  			  }
//
//	  		    		  /* When 5 consecutive readings are lower than LOW_FREQ water is present */
//
//
//
//	  		  		  	  if (btn3_counter >= BTN_Delay_ON)
//	  		  		  	  {
//	  		  		  		  btn3_pressed = true;
//	  		  		  	btn3_state_process = BTN_PRESS;
//	  		  		  	      btn3_counter = 0;
//
//	  		  		  	      //Send_Version_Data(); //reply through uart
//	  		  		  	//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	  		  		  	  }
//	  		    	  }
//
//	  		    	break;
//
//	  		      }
//
//	  		    case BTN_PRESS:
//	  		  	{
//	  		  		/* If 100 ms has passed since t0 (10 Hz sampling) */
//	  		  		if((HAL_GetTick() - btn3_time) >= TIME_INTERVAL)
//	  		  	  	{
//
//	  		  			/* Reinitialize timer */
//	  		  			btn3_time = HAL_GetTick();
//
//	  		  			/* If Freq > LOW_FREQ no water is present : increment counter */
//	  		  		if ((HAL_GPIO_ReadPin(BTN_3_GPIO_Port,BTN_3_Pin) == GPIO_PIN_SET))
//	  		  	  		{
//	  		  				btn3_counter++;
//	  		  				btn3_state_process = BTN_PRESS;
//	  		  	  		}
//
//	  		  			/* Else restart the measuring */
//	  		  	  		else
//	  		  	  		{
//	  		  	  			btn3_counter = 0;
//	  		  	  			//btn2_pressed = true;
//	  		  	  			btn3_state_process = BTN_PRESS;
//	  		  	  		}
//
//	  		  			/* When 20 consecutive readings are higher than HIGH_FREQ water is not present */
//
//	  		  	  		if (btn3_counter >= BTN_Delay_OFF)
//	  		  	  		{
//							btn3_pressed = false;
//							btn3_state_process = BTN_NO_PRESS;
//	  		  	  		    btn3_counter = 0;
//
//						//	Send_Version_Data(); //reply through uart
//						//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	  		  	  		}
//
//	  		  	  	}
//
//	  		  	  break;
//
//	  		  	 }
//
//	  		      default:
//	  		    	btn3_state_process = INIT;
//
//	  } /* switch ( motion_state_process ) */
//
// }
//
// void Btn3_Process()
//{
//	  /* State Machine switch */
//	  switch( btn3_state_process )
//	  {
//	  			  case INIT:
//	  			  {
//
//	  		        /* Next state -> NO_WATER */
//	  				btn3_state_process = BTN_NO_PRESS;
//
//	  				/* By default, no water is detected */
//	  				btn3_pressed = false;
//
//	  		        /* Get t0 */
//	  				btn3_time = HAL_GetTick();
//
//
//	  		        break;
//
//	  		      }
//
//	  		      case BTN_NO_PRESS:
//	  		      {
//	  		    	  /* If 100 ms has passed since t0 (10 Hz sampling) */
//	  		    	  if((HAL_GetTick() - btn3_time) >= TIME_INTERVAL)
//	  		    	  {
//	  		    		  /* Reinitialize timer */
//	  		    		btn3_time = HAL_GetTick();
//
//	  		    		  /* If Freq < LOW_FREQ water is present : increment counter */
//	  		    		  if ((HAL_GPIO_ReadPin(BTN_3_GPIO_Port,BTN_3_Pin) == GPIO_PIN_RESET))
//	  		  			  {
//	  		    			  btn3_counter++;
//	  		    			  btn3_state_process = BTN_NO_PRESS;
//	  		  			  }
//
//	  		    		  /* Else restart the measuring */
//	  		  		  	  else
//	  		  			  {
//	  		  		  		  btn3_counter = 0;
//	  		  		  		 // btn2_pressed = false;
//
//	  		  		  		  btn3_state_process = BTN_NO_PRESS;
//	  		  			  }
//
//	  		    		  /* When 5 consecutive readings are lower than LOW_FREQ water is present */
//
//
//
//	  		  		  	  if (btn3_counter >= BTN_Delay_ON)
//	  		  		  	  {
//	  		  		  		  btn3_pressed = true;
//	  		  		  	btn3_state_process = BTN_PRESS;
//	  		  		  	      btn3_counter = 0;
//
//	  		  		  	      //Send_Version_Data(); //reply through uart
//	  		  		  	//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	  		  		  	  }
//	  		    	  }
//
//	  		    	break;
//
//	  		      }
//
//	  		    case BTN_PRESS:
//	  		  	{
//	  		  		/* If 100 ms has passed since t0 (10 Hz sampling) */
//	  		  		if((HAL_GetTick() - btn3_time) >= TIME_INTERVAL)
//	  		  	  	{
//
//	  		  			/* Reinitialize timer */
//	  		  			btn3_time = HAL_GetTick();
//
//	  		  			/* If Freq > LOW_FREQ no water is present : increment counter */
//	  		  		if ((HAL_GPIO_ReadPin(BTN_3_GPIO_Port,BTN_3_Pin) == GPIO_PIN_SET))
//	  		  	  		{
//	  		  				btn3_counter++;
//	  		  				btn3_state_process = BTN_PRESS;
//	  		  	  		}
//
//	  		  			/* Else restart the measuring */
//	  		  	  		else
//	  		  	  		{
//	  		  	  			btn3_counter = 0;
//	  		  	  			//btn2_pressed = true;
//	  		  	  			btn3_state_process = BTN_PRESS;
//	  		  	  		}
//
//	  		  			/* When 20 consecutive readings are higher than HIGH_FREQ water is not present */
//
//	  		  	  		if (btn3_counter >= BTN_Delay_OFF)
//	  		  	  		{
//							btn3_pressed = false;
//							btn3_state_process = BTN_NO_PRESS;
//	  		  	  		    btn3_counter = 0;
//
//						//	Send_Version_Data(); //reply through uart
//						//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	  		  	  		}
//
//	  		  	  	}
//
//	  		  	  break;
//
//	  		  	 }
//
//	  		      default:
//	  		    	btn3_state_process = INIT;
//
//	  } /* switch ( motion_state_process ) */
//
// }
//
// void SW3_Process()
//{
//	  /* State Machine switch */
//	  switch( sw3_state_process )
//	  {
//	  			  case INIT:
//	  			  {
//
//	  		        /* Next state -> NO_WATER */
//	  				sw3_state_process = BTN_NO_PRESS;
//
//	  				/* By default, no water is detected */
//	  				sw3_pressed = false;
//
//	  		        /* Get t0 */
//	  				sw3_time = HAL_GetTick();
//
//
//	  		        break;
//
//	  		      }
//
//	  		      case BTN_NO_PRESS:
//	  		      {
//	  		    	  /* If 100 ms has passed since t0 (10 Hz sampling) */
//	  		    	  if((HAL_GetTick() - sw3_time) >= TIME_INTERVAL)
//	  		    	  {
//	  		    		  /* Reinitialize timer */
//	  		    		sw3_time = HAL_GetTick();
//
//	  		    		  /* If Freq < LOW_FREQ water is present : increment counter */
//	  		    		  if ((HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin) == GPIO_PIN_RESET))
//	  		  			  {
//	  		    			  sw3_counter++;
//	  		    			  sw3_state_process = BTN_NO_PRESS;
//	  		  			  }
//
//	  		    		  /* Else restart the measuring */
//	  		  		  	  else
//	  		  			  {
//	  		  		  		  sw3_counter = 0;
//	  		  		  		  sw3_state_process = BTN_NO_PRESS;
//	  		  			  }
//
//	  		    		  /* When 5 consecutive readings are lower than LOW_FREQ water is present */
//
//
//
//	  		  		  	  if (sw3_counter >= BTN_Delay_ON)
//	  		  		  	  {
//	  		  		  		  sw3_pressed = true;
//	  		  		  		  sw3_state_process = BTN_PRESS;
//	  		  		  	      sw3_counter = 0;
//
//	  		  		  	  }
//	  		    	  }
//
//	  		    	break;
//
//	  		      }
//
//	  		    case BTN_PRESS:
//	  		  	{
//	  		  		/* If 100 ms has passed since t0 (10 Hz sampling) */
//	  		  		if((HAL_GetTick() - btn3_time) >= TIME_INTERVAL)
//	  		  	  	{
//
//	  		  			/* Reinitialize timer */
//	  		  			btn3_time = HAL_GetTick();
//
//	  		  			/* If Freq > LOW_FREQ no water is present : increment counter */
//	  		  		if ((HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin) == GPIO_PIN_SET))
//	  		  	  		{
//	  		  				sw3_counter++;
//	  		  				sw3_state_process = BTN_PRESS;
//	  		  	  		}
//
//	  		  			/* Else restart the measuring */
//	  		  	  		else
//	  		  	  		{
//	  		  	  			sw3_counter = 0;
//	  		  	  			//btn2_pressed = true;
//	  		  	  			sw3_state_process = BTN_PRESS;
//	  		  	  		}
//
//	  		  			/* When 20 consecutive readings are higher than HIGH_FREQ water is not present */
//
//	  		  	  		if (sw3_counter >= BTN_Delay_OFF)
//	  		  	  		{
//							sw3_pressed = false;
//							sw3_state_process = BTN_NO_PRESS;
//	  		  	  		    sw3_counter = 0;
//
//						//	Send_Version_Data(); //reply through uart
//						//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	  		  	  		}
//
//	  		  	  	}
//
//	  		  	  break;
//
//	  		  	 }
//
//	  		      default:
//	  		    	sw3_state_process = INIT;
//
//	  } /* switch ( motion_state_process ) */
//
// }
bool BTN1_Is_Pressed()
{
	return btn1_pressed;
}
bool BTN2_Is_Pressed()
{
	return btn2_pressed;
}
bool BTN3_Is_Pressed()
{
	return btn3_pressed; // return true;
}
void SetBtnPress(bool trueorfalse, int btn)
{
	if (btn == 1)
		btn1_pressed = trueorfalse;
	else if (btn == 2)
		btn2_pressed = trueorfalse;
	else
		btn3_pressed = trueorfalse;
}
