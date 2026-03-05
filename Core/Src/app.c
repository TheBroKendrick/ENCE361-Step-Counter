/*
 * app.c
 *
 *  Created on: 26/02/2026
 *      Author: ldu60
 */

#include <stdbool.h>

#include "gpio.h"
#include "app.h"
#include "rgb.h"
#include "buttons.h"


void app_main(void)
{
	buttons_init();

	rgb_colour_all_on();
	while (true)
	{
		  HAL_Delay(20);
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

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

}
