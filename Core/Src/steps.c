/*
 * steps.c
 *
 *  Created on: 23/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>

#include "steps.h"
#include "states.h"
#include "task_poten.h"


#define AVERGAGE_STEP_DISTANCE_KILOMETERS 0.00080
#define AVERGAGE_STEP_DISTANCE_YARDS 0.87489
#define INCRIMENT_GOAL_OFFSET 10 	// Can't increment above goal - 10

static int16_t step_count = 0;
static uint16_t step_count_goal = 1000;

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
	} else if (step_count > step_count_goal - INCRIMENT_GOAL_OFFSET && mode == TEST_MODE) {
		step_count = step_count_goal - INCRIMENT_GOAL_OFFSET;
	} else if (step_count > step_count_goal) {
		step_count = step_count_goal;
	}
}

void set_goal(void)
{
	step_count_goal = get_new_goal();
}
