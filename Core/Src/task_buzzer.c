/*
 * task_buzzer.c
 *
 *  Created on: 23/04/2026
 *      Author: ldu60
 */

#include <stdint.h>
#include <stdbool.h>

#include "task_buzzer.h"
#include "gpio.h"
#include "steps.h"

#define BUZZER_TICKS_PERIOD 1000

static uint16_t buzzer_ticks = 0;
static bool buzzed = false;

void buzzer_task_execute (void)
{
	if (get_goal_reached()) {
		if ((buzzer_ticks < BUZZER_TICKS_PERIOD) && !buzzed) {
			HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
			buzzer_ticks++;
		} else if (buzzer_ticks >= BUZZER_TICKS_PERIOD) {
			buzzer_ticks = 0;
			buzzed = true;
			HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
		}
	}
	else {
		buzzed = false;
	}

//	  if ((get_step_count() == get_step_count_goal()) && (buzzer_ticks < BUZZER_TICKS_PERIOD) && !buzzed) {
//		  HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
//		  buzzer_ticks++;
//	  } else if ((buzzer_ticks >= BUZZER_TICKS_PERIOD) && (get_step_count() == get_step_count_goal()) ) {
//		  buzzer_ticks = 0;
//		  buzzed = true;
//		  HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
//	  } else if (get_step_count() != get_step_count_goal()) {
//		  buzzed = false;
//	  }
}
