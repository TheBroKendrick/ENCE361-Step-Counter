/*
 * states.h
 *
 *  Created on: 31/03/2026
 *      Author: Liam du Plessis - ldu60
 */

#ifndef INC_STATES_H_
#define INC_STATES_H_

#include <stdint.h>

typedef enum {
	CURRENT_STEPS_STATE,
	GOAL_PROGRESS_STATE,
	DISTANCE_TRAVELLED_STATE,
} State;

typedef enum {
	NORMAL_MODE,
	TEST_MODE,
	SET_GOAL_MODE
} Mode;

typedef enum {
	STEPS,
	PERCENTAGE_OF_GOAL,
	KILOMETERS,
	YARDS,
	ERR	// Indicates issue for debugging
} Unit;

State get_state(void);
Mode get_mode(void);

void toggle_mode(void);
void enter_set_goal_mode(void);
void change_state(void);

void toggle_units(void);
Unit get_units(void);

#endif /* INC_STATES_H_ */
