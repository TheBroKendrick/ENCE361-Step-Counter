/*
 * task_blinky.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include "gpio.h"


void LED_task_execute()
{
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}


