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
void display_task_test(void);

void print_header(void);
void print_to_uart(void);
void display_percentage(void);
void display_steps(int line);
void display_goal(void);
void display_distance_travelled(void);


#endif /* INC_TASK_DISPLAY_H_ */
