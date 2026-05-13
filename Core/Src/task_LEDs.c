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


#define THRESHOLD_1 25
#define THRESHOLD_2 50
#define THRESHOLD_3 75
#define THRESHOLD_4 100

#define MAX_DUTY_CYCE 		100
#define PERCENTAGE_SCALE 	100

#define COUNTER_LIMIT 50

static uint8_t blink_counter = 0;

/*
 * @brief Function to execute the LED task.
 *
 * A single LED will light up for every 25% of the step count goal achieved (LEDs DS1 - DS4).
 * When no LEDs are lit, LED DS3 will gradually get brighter in proportion to how much
 * of the first 25% has been achieved.
 */
void LED_task_execute()
{
	int16_t goal_percentage = get_goal_progress_percentage();

	blink_counter++;

	if (blink_counter >= COUNTER_LIMIT) {
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		blink_counter = 0;
	}

	if (goal_percentage >= THRESHOLD_1
	 && goal_percentage < THRESHOLD_2)
	{
		how_many_leds(1, goal_percentage);
	}
	else if (goal_percentage >= THRESHOLD_2
		  && goal_percentage < THRESHOLD_3)
	{
		how_many_leds(2, goal_percentage);
	}
	else if (goal_percentage >= THRESHOLD_3
		  && goal_percentage < THRESHOLD_4)
	{
		how_many_leds(3, goal_percentage);
	}
	else if (goal_percentage >= THRESHOLD_4)
	{
		how_many_leds(4, goal_percentage);
	}
	else
	{
		how_many_leds(0, goal_percentage);
	}
}

/*
 * @brief This function sets the number of LEDs that will light up on the RCAP board.
 * @param num_leds Number of LEDs to be lit up
 * @param goal_percentage The percentage of the step count goal that has been achieved
 */
void how_many_leds(int num_leds, int16_t goal_percentage)
{
	switch(num_leds)
	{
		case 0:
			uint8_t duty_cycle = (goal_percentage * PERCENTAGE_SCALE) / THRESHOLD_1;
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty_cycle);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 1 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, MAX_DUTY_CYCE);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 2 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, MAX_DUTY_CYCE);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 3 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, MAX_DUTY_CYCE);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_SET);
			break;
		case 4 :
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, MAX_DUTY_CYCE);
			HAL_GPIO_WritePin(GPIOC, RGB_DS4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RGB_DS2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RGB_DS1_GPIO_Port, RGB_DS1_Pin, GPIO_PIN_RESET);
			break;
	}
}

