/*
 * task_display.h
 *
 *  Created on: 12/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#ifndef INC_TASK_DISPLAY_H_
#define INC_TASK_DISPLAY_H_

#include <stdint.h>

void display_init (void);
void display_task_execute(void);
void test_mode_display_task_execute(void);

void display_state(void);

void display_current_steps(void);
void display_goal_progress(void);
void display_distance_travelled(void);

void print_to_uart(void);
void display_percentage(void);

#endif /* INC_TASK_DISPLAY_H_ */
