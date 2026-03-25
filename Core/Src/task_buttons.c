/*
 * task_buttons.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>
#include <stdio.h>

#include "rgb.h"
#include "buttons.h"
#include "task_buttons.h"
#include "pwm.h"
#include "tim.h"
#include "usart.h"
#include "steps.h"

#define DOUBLE_CLICK_TICKS 100000

static uint8_t dutyCycle = 0;
static uint32_t ticksSinceLastClick = 0;
static uint8_t clicks = 0;

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

void button_task_execute(void)
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

	  if (clicks == 2 && ticksSinceLastClick < DOUBLE_CLICK_TICKS)
	  {
		  addSteps(1);
		  clicks = 0;
	  }

	  if (buttons_checkButton(RIGHT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_RIGHT);
	  }


	  if (buttons_checkButton(LEFT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_LEFT);
	  }

	  ticksSinceLastClick++;
	  buttons_update();
}
