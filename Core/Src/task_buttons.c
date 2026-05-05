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
#include "usart.h"
#include "steps.h"
#include "states.h"


#define DOUBLE_CLICK_TICK_THRESHOLD 20

static uint8_t 	dutyCycle 	= 0;
static uint8_t 	clicks 		= 0;
static uint32_t ticksSinceLastClick = 0;


void buttons_task_init (void)
{
	buttons_init();
	rgb_colour_all_on();
}

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

void poll_buttons (void)
{
	  if (buttons_checkButton(UP) == PUSHED)
	  {
		  toggle_pwm();
	  }

	  if (buttons_checkButton(DOWN) == PUSHED)
	  {
		  rgb_led_toggle(RGB_DOWN);
		  toggle_uart();
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

	  if (buttons_checkButton(RIGHT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_RIGHT);
	  }


	  if (buttons_checkButton(LEFT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_LEFT);
		  addSteps(7);
	  }


	  ticksSinceLastClick++;
	  buttons_update();
}

void toggle_pwm(void)
{
	  if (dutyCycle < 100)
	  {
		  dutyCycle += 10;
		  pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, dutyCycle);
	  }
	  else {
		  dutyCycle = 0;
		  pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, dutyCycle);
	  }
}

void toggle_uart(void)
{
	HAL_UART_StateTypeDef state = HAL_UART_GetState(&huart2);
	if (state == HAL_UART_STATE_RESET)
	{
		HAL_UART_Init(&huart2);
	}
	else
	{
		HAL_UART_DeInit(&huart2);
	}
}

