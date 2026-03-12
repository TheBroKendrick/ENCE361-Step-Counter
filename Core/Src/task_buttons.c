/*
 * task_buttons.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 */

#include "rgb.h"
#include "buttons.h"
#include "task_buttons.h"
#include "pwm.h"


void button_task_execute(void)
{
	  if (buttons_checkButton(UP) == PUSHED)
	  {
		  rgb_led_toggle(RGB_UP);
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
