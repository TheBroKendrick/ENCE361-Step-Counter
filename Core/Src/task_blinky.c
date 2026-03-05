/*
 * task_blinky.c
 *
 *  Created on: 6/03/2026
 *      Author: ldu60
 */

#include "gpio.h"


void blinky_task_execute()
{
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}
