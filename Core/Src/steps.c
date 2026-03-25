/*
 * steps.c
 *
 *  Created on: 23/03/2026
 *      Author: kmd119
 */

#include <stdint.h>

#include "steps.h"

static int32_t stepCount = 0;
static int32_t stepCountGoal = 1000;

int32_t getStepCount(void)
{
	return stepCount;
}

void addSteps(int32_t steps)
{
	stepCount += steps;
	if (stepCount < 0)
	{
		stepCount = 0;
	}
}
