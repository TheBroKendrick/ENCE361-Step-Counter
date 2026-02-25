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
	while (true)
	{
		  HAL_Delay(200);
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		  {
			  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
		  }
		  else
		  {
			  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
		  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
		  }
	}
}
