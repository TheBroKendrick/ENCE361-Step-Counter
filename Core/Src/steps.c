/*
 * steps.c
 *
 *  Created on: 23/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>

#include "steps.h"


#define AVERGAGE_STEP_DISTANCE 80 // In centimeters

static int16_t step_count = 0;
static int16_t step_count_goal = 1000;


int16_t get_step_count(void)
{
	return step_count;
}

int16_t get_goal_progress(void)
{
	return (step_count * 100) / step_count_goal;
}

int32_t get_distance_travelled(void)
{
	return step_count * AVERGAGE_STEP_DISTANCE;
}

void addSteps(int16_t steps)
{
	step_count += steps;
	if (step_count < 0)
	{
		step_count = 0;
	}
}
