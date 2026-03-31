/*
 * states.h
 *
 *  Created on: 31/03/2026
 *      Author: ldu60
 */

#ifndef INC_STATES_H_
#define INC_STATES_H_

#include <stdint.h>

typedef enum {
	CURRENT_STEPS_STATE,
	GOAL_PROGRESS_STATE,
	DISTANCE_TRAVELLED_STATE,
	SET_GOAL_STATE
} State;

typedef enum {
	NORMAL_MODE,
	TEST_MODE,
	SET_GOAL_MODE
} Mode;

State get_state(void);
Mode get_mode(void);

void change_mode (void);
void change_state(void);

#endif /* INC_STATES_H_ */
