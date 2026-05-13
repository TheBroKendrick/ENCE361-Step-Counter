/*
 * task_buttons.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "rgb.h"
#include "buttons.h"
#include "task_buttons.h"
#include "pwm.h"
#include "tim.h"
#include "uart_print.h"
#include "steps.h"
#include "states.h"


#define DOUBLE_CLICK_TICK_THRESHOLD 20


static uint8_t 	clicks 		= 0;
static uint32_t ticksSinceLastClick = 0;

/*
 * @brief Function to initialise GPIO pins utilised by the RCAP buttons.
 */
void buttons_task_init (void)
{
	buttons_init();
}

/*
 * @brief Function to execute button task.
 */
void button_task_execute(void)
{
	  switch (get_mode()) {
		  case NORMAL_MODE:
			  poll_buttons();
			  break;

		  case TEST_MODE:
			  poll_buttons();
			  break;

		  case SET_GOAL_MODE:
			  break;
	  }
}

/*
 * @brief Function that polls button presses and detects double clicks in the DOWN button.
 */
void poll_buttons (void)
{
	// Toggles UART serial communications used for debugging.
	if (buttons_checkButton(UP) == PUSHED)
	{
		toggle_uart();
	}

	if (buttons_checkButton(DOWN) == PUSHED)
	{
		ticksSinceLastClick = 0;
		clicks++;
	}

	if (ticksSinceLastClick >= DOUBLE_CLICK_TICK_THRESHOLD)
	{
		clicks = 0;
	}

	if (clicks == 2 && ticksSinceLastClick < DOUBLE_CLICK_TICK_THRESHOLD)
	{
		clicks = 0;
		toggle_mode();
	}


	if (buttons_checkButton(LEFT) == PUSHED)
	{
		addSteps(7);
	}


	ticksSinceLastClick++;
	buttons_update();
}


