/*
 * steps.h
 *
 *  Created on: 23/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#ifndef INC_STEPS_H_
#define INC_STEPS_H_

uint16_t get_step_count_goal(void);
uint16_t get_step_count(void);
uint16_t get_goal_progress_percentage(void);
float get_distance_travelled(void);

void addSteps(int16_t steps);
void set_goal(void);
void update_steps(uint16_t steps);


#endif /* INC_STEPS_H_ */
