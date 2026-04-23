/*
 * app.c
 *
 *  Created on: 26/02/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdbool.h>

#include "app.h"
#include "dma.h"
#include "rgb.h"
#include "buttons.h"
#include "states.h"
#include "tim.h"
#include "ssd1306.h"
#include "task_joystick.h"
#include "task_buttons.h"
#include "task_buzzer.h"
#include "task_blinky.h"
#include "task_display.h"
#include "task_poten.h"


#define TICK_FREQUENCY_HZ 1000
#define BLINKY_FREQUENCY 2
#define BUTTON_FREQUENCY 100
#define BUZZER_FREQUENCY 200
#define JOYSTICK_FREQUENCY 50
#define DISPLAY_FREQUENCY 4
#define POTEN_FREQUENCY 100

#define BLINKY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BLINKY_FREQUENCY) // = 500 Ticks
#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_FREQUENCY) // = 10 Ticks
#define BUZZER_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUZZER_FREQUENCY) // = 10 Ticks
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/JOYSTICK_FREQUENCY) // = 20 Ticks
#define DISPLAY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/DISPLAY_FREQUENCY) // = 250 Ticks
#define POTEN_TAST_PERIOD_TICKS (TICK_FREQUENCY_HZ/POTEN_FREQUENCY) // 10 Ticks

static uint32_t BlinkyNextRun = 0;
static uint32_t ButtonNextRun = 0;
static uint32_t JoystickNextRun = 0;
static uint32_t DisplayNextRun = 0;
static uint32_t PotenNextRun = 0;
static uint32_t BuzzerNextRun = 0;


void app_main(void)
{
	buttons_init();
	display_init();
	rgb_colour_all_on();

	BlinkyNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	ButtonNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	JoystickNextRun = HAL_GetTick() + JOYSTICK_TASK_PERIOD_TICKS;
	DisplayNextRun = HAL_GetTick() + DISPLAY_TASK_PERIOD_TICKS;
	PotenNextRun = HAL_GetTick() + POTEN_TAST_PERIOD_TICKS;
	BuzzerNextRun = HAL_GetTick() + BUZZER_TASK_PERIOD_TICKS;

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
			  switch (mode) {
				  case NORMAL_MODE:
					  button_task_execute();
					  break;

				  case TEST_MODE:
					  button_task_execute();
					  break;

				  case SET_GOAL_MODE:
					  break;
			  }

			  ButtonNextRun += BUTTON_TASK_PERIOD_TICKS;
		  }

		  if (ticks > BuzzerNextRun)
		  {
			  buzzer_task_execute();
			  BuzzerNextRun += BUZZER_TASK_PERIOD_TICKS;
		  }

		  if (ticks > PotenNextRun)
		  {
			  switch (mode) {
				  case NORMAL_MODE:
					  break;

				  case TEST_MODE:
					  break;

				  case SET_GOAL_MODE:
					  poten_task_execute();
					  break;
			  }

			  PotenNextRun += POTEN_TAST_PERIOD_TICKS;
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
					  set_goal_mode_joystick_task_execute();
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
					  set_goal_mode_display_task_execute();
					  break;
			  }

			  DisplayNextRun += DISPLAY_TASK_PERIOD_TICKS;
		  }
	}
}
