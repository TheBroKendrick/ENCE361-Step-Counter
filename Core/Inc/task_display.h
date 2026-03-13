/*
 * task_display.h
 *
 *  Created on: 12/03/2026
 *      Author: ldu60
 */

#ifndef INC_TASK_DISPLAY_H_
#define INC_TASK_DISPLAY_H_

#include <stdint.h>

void display_init (void);
void display_task_execute(void);

void print_to_uart(void);
void display_percentage(void);

#endif /* INC_TASK_DISPLAY_H_ */
