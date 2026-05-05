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
#include <stdbool.h>

void joystick_task_execute (void);
void joystick_task_normal_mode (void);
void joystick_task_test_mode (void);
void joystick_task_set_goal_mode (void);

void increment_step_count (void);

uint16_t get_joystick_adc_x (void);
uint16_t get_joystick_adc_y (void);

int16_t get_percentage_x (void);
int16_t get_percentage_y (void);

void poll_joystick_x (void);
void poll_joystick_y (void);
void poll_joystick_press (void);
void test_mode_poll_joystick_y (void);

bool get_is_pressed (void);

#endif /* INC_TASK_JOYSTICK_H_ */
