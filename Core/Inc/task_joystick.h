/*
 * task_joystick.h
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#ifndef INC_TASK_JOYSTICK_H_
#define INC_TASK_JOYSTICK_H_

#include <stdint.h>

void joystick_task_execute(void);
void test_mode_joystick_task_execute(void);
void increment_step_count(void);

uint16_t get_joystick_adc_x(void);
uint16_t get_joystick_adc_y(void);

int16_t get_percentage_x(void);
int16_t get_percentage_y(void);

void poll_joystick_x(void);
void poll_joystick_y(void);
void test_mode_poll_joystick_y(void);

#endif /* INC_TASK_JOYSTICK_H_ */
