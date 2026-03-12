/*
 * task_joystick.h
 *
 *  Created on: 6/03/2026
 *      Author: kmd119
 */

#ifndef INC_TASK_JOYSTICK_H_
#define INC_TASK_JOYSTICK_H_

void joystick_task_execute(void);

uint16_t get_joystick_adc_x(void);
uint16_t get_joystick_adc_y(void);

#endif /* INC_TASK_JOYSTICK_H_ */
