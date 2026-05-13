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


#define AVERGAGE_STEP_DISTANCE_KILOMETERS 	0.00080
#define AVERGAGE_STEP_DISTANCE_YARDS 		0.87489
#define INCREMENT_GOAL_OFFSET 				10 	// Can't increment above goal - 10


static int16_t step_count 		= 0;
static uint16_t step_count_goal = 1000;
static bool goal_reached 		= false;

/*
 * @brief Returns the current value of the step count goal.
 * @return step count goal
 */
uint16_t get_step_count_goal(void)
{
	return step_count_goal;
}

/*
 * @brief Returns the current step count.
 * @return current step count
 */
uint16_t get_step_count(void)
{
	return step_count;
}

/*
 * @brief Returns the step count as a percentage of the current step count goal.
 * @return percentage of step count goal completed
 */
uint16_t get_goal_progress_percentage(void)
{
	return (step_count * 100) / step_count_goal;
}

/*
 * @brief Converts the step count to a the current unit being displayed using average step distances.
 * @return step count converted to the current unit displayed
 */
float get_distance_travelled(void)
{
	Unit units = get_units();

	if (units == YARDS) {
		return step_count * AVERGAGE_STEP_DISTANCE_YARDS;
	} else {
		return step_count * AVERGAGE_STEP_DISTANCE_KILOMETERS;
	}
}

/*
 * @brief Adds steps to the current step count.
 * @param steps Steps to be added to the current step count
 */
void addSteps(int16_t steps)
{
	Mode mode = get_mode();
	step_count += steps;

	if (step_count < 0) {
		step_count = 0;
	} else if ((step_count > (step_count_goal - INCREMENT_GOAL_OFFSET)) && (mode == TEST_MODE)) {
		step_count = step_count_goal - INCREMENT_GOAL_OFFSET;
	}

	if (step_count < step_count_goal) {
		goal_reached = false;
	} else if (step_count >= step_count_goal) {
		goal_reached = true;
	}
}

/*
 * @brief Returns a boolean value depending on whether the step count goal has been achieved.
 * @return a boolean variable that is true when the step goal has been achieved
 */
bool get_goal_reached (void)
{
	return goal_reached;
}

/*
 * @brief Sets a new value for the step count goal.
 */
void set_goal(void)
{
	step_count_goal = get_new_goal();
}
