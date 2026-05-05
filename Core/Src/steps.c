/*
 * steps.c
 *
 *  Created on: 23/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "steps.h"
#include "states.h"
#include "task_poten.h"
#include "usart.h"
#include "imu_lsm6ds.h"
#include "string.h"

#define AVERGAGE_STEP_DISTANCE_KILOMETERS 0.00080
#define AVERGAGE_STEP_DISTANCE_YARDS 0.87489
#define INCREMENT_GOAL_OFFSET 10 	// Can't increment above goal - 10

static uint16_t step_count = 0;
static uint16_t step_count_goal = 1000;
static bool data_ready = false;

uint16_t get_step_count_goal(void)
{
	return step_count_goal;
}

uint16_t get_step_count(void)
{
	return step_count;
}

uint16_t get_goal_progress_percentage(void)
{
	return (step_count * 100) / step_count_goal;
}

float get_distance_travelled(void)
{
	Unit units = get_units();

	if (units == YARDS) {
		return step_count * AVERGAGE_STEP_DISTANCE_YARDS;
	} else {
		return step_count * AVERGAGE_STEP_DISTANCE_KILOMETERS;
	}
}

void addSteps(int16_t steps)
{
	Mode mode = get_mode();
	step_count += steps;

	if (step_count < 0) {
		step_count = 0;
	} else if ((step_count > (step_count_goal - INCREMENT_GOAL_OFFSET)) && (mode == TEST_MODE)) {
		step_count = step_count_goal - INCREMENT_GOAL_OFFSET;
	} else if (step_count > step_count_goal) {
		step_count = step_count_goal;
	}
}

void set_goal(void)
{
	step_count_goal = get_new_goal();
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	data_ready = true;
}

void print_steps_to_uart(void)
{
	if (data_ready)
	{
		step_count = ((imu_lsm6ds_read_byte(STEP_COUNTER_H) << 8) | imu_lsm6ds_read_byte(STEP_COUNTER_L));
		data_ready = false;
	}
	char StepCount_buffer[40];

	snprintf(StepCount_buffer, sizeof(StepCount_buffer), "%d\r\n", step_count);
	HAL_UART_Transmit(&huart2, (uint8_t*) StepCount_buffer, strlen(StepCount_buffer), 100);
}
