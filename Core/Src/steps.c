/*
 * steps.c
 *
 *  Created on: 23/03/2026
 *      Author: kmd119
 */

#include <stdint.h>

#include "steps.h"

static int32_t stepCount = 0;

int32_t getStepCount()
{
	return stepCount;
}

void addSteps(int32_t steps)
{
	stepCount += steps;
}
