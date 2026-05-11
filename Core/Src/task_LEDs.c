/*
 * task_blinky.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */
#include <stdint.h>

#include "task_LEDs.h"
#include "gpio.h"
#include "tim.h"
#include "pwm.h"
#include "steps.h"


void LED_task_execute()
{
	int16_t goal_percentage = get_goal_progress_percentage();

	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

	if (goal_percentage >= 25 && goal_percentage < 50) {
		how_many_leds(1, goal_percentage);
	} else if (goal_percentage >= 50 && goal_percentage < 75) {
		how_many_leds(2, goal_percentage);
	} else if (goal_percentage >= 75 && goal_percentage < 100) {
		how_many_leds(3, goal_percentage);
	} else if (goal_percentage >= 100) {
		how_many_leds(4, goal_percentage);
	} else {
		how_many_leds(0, goal_percentage);
	}
}

void how_many_leds(int num_leds, int16_t goal_percentage)
{
	switch(num_leds)
	{
		case 0:
			uint8_t duty_cycle = (goal_percentage * 100) / 25;
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty_cycle);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 1 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, 100);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 2 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, 100);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 3 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, 100);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 4 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, 100);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_RESET);
			break;
	}
}

