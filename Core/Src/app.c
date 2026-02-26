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


void app_main(void)
{
	rgb_colour_all_on();
	while (true)
	{
		  HAL_Delay(200);
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		  {
			  rgb_led_on(RGB_UP); // DS3 <- UP
		  }
		  else
		  {
		  	  rgb_led_off(RGB_UP);
		  }

		  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))
		  {
			  rgb_led_on(RGB_DOWN); // DS3 <- UP
		  }
		  else
		  {
		  	  rgb_led_off(RGB_DOWN);
		  }

		  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10))
		  {
			  rgb_led_on(RGB_RIGHT); // DS3 <- UP
		  }
		  else
		  {
		  	  rgb_led_off(RGB_RIGHT);
		  }

		  if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
		  {
			  rgb_led_on(RGB_LEFT); // DS3 <- UP
		  }
		  else
		  {
		  	  rgb_led_off(RGB_LEFT);
		  }
	}
}
