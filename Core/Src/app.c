/*
 * app.c
 *
 *  Created on: 26/02/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdbool.h>

#include "app.h"
//#include "dma.h"
#include "uart_print.h"
#include "tim.h"
#include "steps.h"
#include "task_accel.h"
#include "task_joystick.h"
#include "task_buttons.h"
#include "task_buzzer.h"
#include "task_blinky.h"
#include "task_display.h"
#include "task_poten.h"
#include "imu_lsm6ds.h"


#define TICK_FREQUENCY_HZ 	1000
#define BLINKY_FREQUENCY 	2
#define BUTTON_FREQUENCY 	100
#define BUZZER_FREQUENCY 	1000
#define JOYSTICK_FREQUENCY 	50
#define DISPLAY_FREQUENCY 	4
#define POTEN_FREQUENCY 	100
#define ACCEL_FREQUENCY 	100
#define UART_FREQ 4

#define BLINKY_TASK_PERIOD_TICKS 	(TICK_FREQUENCY_HZ/BLINKY_FREQUENCY) 	// = 500 Ticks
#define BUTTON_TASK_PERIOD_TICKS 	(TICK_FREQUENCY_HZ/BUTTON_FREQUENCY) 	// = 10 Ticks
#define BUZZER_TASK_PERIOD_TICKS 	(TICK_FREQUENCY_HZ/BUZZER_FREQUENCY) 	// = 10 Ticks
#define JOYSTICK_TASK_PERIOD_TICKS 	(TICK_FREQUENCY_HZ/JOYSTICK_FREQUENCY) 	// = 20 Ticks
#define DISPLAY_TASK_PERIOD_TICKS 	(TICK_FREQUENCY_HZ/DISPLAY_FREQUENCY) 	// = 250 Ticks
#define POTEN_TASK_PERIOD_TICKS 	(TICK_FREQUENCY_HZ/POTEN_FREQUENCY) 	// 10 Ticks
#define ACCEL_TASK_PERIOD_TICKS 	(TICK_FREQUENCY_HZ/ACCEL_FREQUENCY) 	// 20 Ticks
#define UART_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/UART_FREQ)

static uint32_t BlinkyNextRun 	= 0;
static uint32_t ButtonNextRun 	= 0;
static uint32_t JoystickNextRun = 0;
static uint32_t DisplayNextRun 	= 0;
static uint32_t PotenNextRun 	= 0;
static uint32_t BuzzerNextRun 	= 0;
static uint32_t AccelNextRun 	= 0;
static uint32_t UartNextRun	= 0;

void app_main(void)
{
	buttons_task_init();
	display_init();
	accel_init();
	imu_init();
	poten_task_init();

	BlinkyNextRun 	= HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	ButtonNextRun 	= HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	JoystickNextRun = HAL_GetTick() + JOYSTICK_TASK_PERIOD_TICKS;
	DisplayNextRun 	= HAL_GetTick() + DISPLAY_TASK_PERIOD_TICKS;
	PotenNextRun 	= HAL_GetTick() + POTEN_TASK_PERIOD_TICKS;
	BuzzerNextRun 	= HAL_GetTick() + BUZZER_TASK_PERIOD_TICKS;
	AccelNextRun 	= HAL_GetTick() + ACCEL_TASK_PERIOD_TICKS;
	UartNextRun = HAL_GetTick() + UART_TASK_PERIOD_TICKS;

	while (true)
	{
		  uint32_t ticks = HAL_GetTick();

		  if (ticks > AccelNextRun)
		  {
			  accel_task_execute();
			  AccelNextRun += ACCEL_TASK_PERIOD_TICKS;
		  }

		  if (ticks > BlinkyNextRun)
		  {
			  blinky_task_execute();
			  BlinkyNextRun += BLINKY_TASK_PERIOD_TICKS;
		  }

		  if (ticks > ButtonNextRun)
		  {
			  button_task_execute();
			  ButtonNextRun += BUTTON_TASK_PERIOD_TICKS;
		  }

		  if (ticks > BuzzerNextRun)
		  {
			  buzzer_task_execute();
			  BuzzerNextRun += BUZZER_TASK_PERIOD_TICKS;
		  }

		  if (ticks > PotenNextRun)
		  {
			  poten_task_execute();
			  PotenNextRun += POTEN_TASK_PERIOD_TICKS;
		  }

		  if (ticks > JoystickNextRun)
		  {
			  joystick_task_execute();
			  JoystickNextRun += JOYSTICK_TASK_PERIOD_TICKS;
		  }

		  if (ticks > DisplayNextRun)
		  {
			  display_task_execute();
			  DisplayNextRun += DISPLAY_TASK_PERIOD_TICKS;
		  }

		  if (ticks > UartNextRun)
		  {
			  print_poten_to_uart();
			  UartNextRun += UART_TASK_PERIOD_TICKS;
		  }
	}
}
