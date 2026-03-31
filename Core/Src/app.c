/*
 * app.c
 *
 *  Created on: 26/02/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdbool.h>

#include "app.h"
#include "rgb.h"
#include "buttons.h"
#include "states.h"
#include "tim.h"
#include "ssd1306.h"
#include "task_joystick.h"
#include "task_buttons.h"
#include "task_blinky.h"
#include "task_display.h"


#define TICK_FREQUENCY_HZ 1000
#define BLINKY_FREQUENCY 2
#define BUTTON_FREQUENCY 100
#define JOYSTICK_FREQUENCY 50
#define DISPLAY_FREQUENCY 4

#define BLINKY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BLINKY_FREQUENCY) // = 500 Ticks
#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_FREQUENCY) // = 40 Ticks
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/JOYSTICK_FREQUENCY) // = 500 Ticks
#define DISPLAY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/DISPLAY_FREQUENCY) // = 250 Ticks

static uint32_t BlinkyNextRun = 0;
static uint32_t ButtonNextRun = 0;
static uint32_t JoystickNextRun = 0;
static uint32_t DisplayNextRun = 0;


void app_main(void)
{
	buttons_init();
	display_init();
	rgb_colour_all_on();

	BlinkyNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	ButtonNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	JoystickNextRun = HAL_GetTick() + JOYSTICK_TASK_PERIOD_TICKS;
	DisplayNextRun = HAL_GetTick() + DISPLAY_TASK_PERIOD_TICKS;

	while (true)
	{
		  uint32_t ticks = HAL_GetTick();
		  Mode mode = get_mode();

		  if(ticks > BlinkyNextRun)
		  {
			  blinky_task_execute();
			  BlinkyNextRun += BLINKY_TASK_PERIOD_TICKS;
		  }

		  if (ticks > ButtonNextRun)
		  {
			  button_task_execute();
			  ButtonNextRun += BUTTON_TASK_PERIOD_TICKS;
		  }

		  if (ticks > JoystickNextRun)
		  {
			  switch (mode) {
				  case NORMAL_MODE:
					  joystick_task_execute();
					  break;

				  case TEST_MODE:
					  test_mode_joystick_task_execute();
					  break;

				  case SET_GOAL_MODE:
					  break;
			  }

			  JoystickNextRun += JOYSTICK_TASK_PERIOD_TICKS;
		  }

		  if (ticks > DisplayNextRun)
		  {
			  switch (mode) {
				  case NORMAL_MODE:
					  display_task_execute();
					  break;

				  case TEST_MODE:
					  test_mode_display_task_execute();
					  break;

				  case SET_GOAL_MODE:
					  break;

			  }

			  DisplayNextRun += DISPLAY_TASK_PERIOD_TICKS;
		  }
	}
}
