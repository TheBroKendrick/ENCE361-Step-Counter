/*
 * task_buttons.h
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#ifndef INC_TASK_BUTTONS_H_
#define INC_TASK_BUTTONS_H_

void buttons_task_init (void);
void button_task_execute(void);
void poll_buttons (void);

void toggle_pwm(void);
void toggle_uart(void);

bool getTestMode(void);

#endif /* INC_TASK_BUTTONS_H_ */
