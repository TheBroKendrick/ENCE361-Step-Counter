/*
 * task_buzzer.c
 *
 *  Created on: 23/04/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>
#include <stdbool.h>

#include "task_buzzer.h"
#include "task_display.h"
#include "gpio.h"
#include "steps.h"


#define BUZZER_TICKS_PERIOD 2000


static uint16_t buzzer_ticks 	= 0;
static bool buzzed 				= false;

/*
 * @brief Function to execute the buzzer task
 *
 * Buzzer only sounds for 2000 ticks when the goal is reached.
 */
void buzzer_task_execute (void)
{
	if (get_goal_reached())
	{
		if (buzzer_ticks == 0 && !buzzed) {
			toggle_display_goal_completed();
		}

		if ((buzzer_ticks < BUZZER_TICKS_PERIOD) && !buzzed) {
			HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
			buzzer_ticks++;
		} else if (buzzer_ticks >= BUZZER_TICKS_PERIOD) {
			buzzer_ticks = 0;
			buzzed = true;
			toggle_display_goal_completed();
			HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
		}
	}
	else
	{
		buzzed = false;
	}
}
