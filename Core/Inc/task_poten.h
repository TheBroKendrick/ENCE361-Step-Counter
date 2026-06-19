/*
 * task_poten.h
 *
 *  Created on: 14/04/2026
 *      Author: Liam du Plessis - ldu60
                Kendrick Dela Cruz - kmd119
 */

#ifndef INC_TASK_POTEN_H_
#define INC_TASK_POTEN_H_

void poten_task_init (void);
void joystick_task_set_goal_mode (void);
void poten_task_execute(void);
void poten_adc_update (void);

uint16_t get_new_goal(void);
uint16_t get_poten_raw_adc (void);

#endif /* INC_TASK_POTEN_H_ */
