/*
 * states.c
 *
 *  Created on: 31/03/2026
 *      Author: Liam du Plessis - ldu60
 */

#include <stdint.h>

#include "states.h"
#include "task_joystick.h"

static State current_state = CURRENT_STEPS_STATE;
static Mode current_mode = NORMAL_MODE;

static Unit current_goal_unit = STEPS;
static Unit current_steps_unit =  STEPS;
static Unit current_distance_unit = KILOMETERS;

static Mode stored_mode;

// To allow state/mode 'check' outside of module
State get_state(void)
{
	return current_state;
}

Mode get_mode(void)
{
	return current_mode;
}

// To allow state/mode 'change' outside of module
void change_state(void)
{
	int16_t percentage_x = get_percentage_x();

	switch (current_state) {
		case CURRENT_STEPS_STATE:
			if (percentage_x < 0) { // JS being held RIGHT
				current_state = GOAL_PROGRESS_STATE;
			} else {				// JS being held LEFT
				current_state = DISTANCE_TRAVELLED_STATE;
			}
			break;

		case GOAL_PROGRESS_STATE:
			if (percentage_x < 0) { // JS being held RIGHT
				current_state = DISTANCE_TRAVELLED_STATE;
			} else {				// JS being held LEFT
				current_state = CURRENT_STEPS_STATE;
			}
			break;

		case DISTANCE_TRAVELLED_STATE:
			if (percentage_x < 0) { // JS being held RIGHT
				current_state = CURRENT_STEPS_STATE;
			} else {				// JS being held LEFT
				current_state = GOAL_PROGRESS_STATE;
			}
			break;
	}

}

void toggle_mode (void)
{
	switch (current_mode) {
		case NORMAL_MODE:
			if (get_is_pressed()) {
				stored_mode = current_mode;
				current_mode = SET_GOAL_MODE;
			} else {
				current_mode = TEST_MODE;
			}
			break;

		case TEST_MODE:
			if (get_is_pressed()) {
				stored_mode = current_mode;
				current_mode = SET_GOAL_MODE;
			} else {
				current_mode = NORMAL_MODE;
			}
			break;

		case SET_GOAL_MODE:
			current_mode = stored_mode;
			break;
	}
}

void toggle_units(void)
{
	switch (current_state) {
	case CURRENT_STEPS_STATE:		// Toggle between STEPS & PERCENTAGE
		if (current_goal_unit == STEPS) {
			current_goal_unit = PERCENTAGE_OF_GOAL;
		} else {
			current_goal_unit = STEPS;
		}
		break;

	case GOAL_PROGRESS_STATE:		// Only one unit available
		current_steps_unit = STEPS;
		break;

	case DISTANCE_TRAVELLED_STATE:	// Toggle between KILOMETERS & YARDS
		if (current_distance_unit == KILOMETERS) {
			current_distance_unit = YARDS;
		} else {
			current_distance_unit = KILOMETERS;
		}
		break;
	}
}

Unit get_units(void)
{
	switch (current_state) {
	case CURRENT_STEPS_STATE:
		return current_goal_unit;
		break;

	case GOAL_PROGRESS_STATE:
		return current_goal_unit;
		break;

	case DISTANCE_TRAVELLED_STATE:
		return current_distance_unit;
		break;
	}

	return ERR;
}

