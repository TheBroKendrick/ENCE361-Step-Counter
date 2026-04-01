/*
 * steps.h
 *
 *  Created on: 23/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#ifndef INC_STEPS_H_
#define INC_STEPS_H_

int16_t get_step_count(void);
int16_t get_goal_progress(void);
int32_t get_distance_travelled(void);

void addSteps(int16_t steps);

#endif /* INC_STEPS_H_ */
