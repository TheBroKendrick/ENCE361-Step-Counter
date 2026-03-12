/*
 * task_buttons.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 */

#include <stdint.h>
#include "rgb.h"
#include "buttons.h"
#include "task_buttons.h"
#include "pwm.h"
#include "tim.h"


static uint8_t dutyCycle = 0;
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

void button_task_execute(void)
{
	  if (buttons_checkButton(UP) == PUSHED)
	  {
		  toggle_pwm();
	  }

	  if (buttons_checkButton(DOWN) == PUSHED)
	  {
		  rgb_led_toggle(RGB_DOWN);
	  }

	  if (buttons_checkButton(RIGHT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_RIGHT);
	  }

	  if (buttons_checkButton(LEFT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_LEFT);
	  }

	  buttons_update();
}
