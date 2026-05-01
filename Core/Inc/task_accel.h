/*
 * task_accel.h
 *
 *  Created on: 1/05/2026
 *      Author: ldu60
 */

#ifndef INC_TASK_ACCEL_H_
#define INC_TASK_ACCEL_H_

void accel_init (void);
void accel_task_execute (void);

void update_acc_x (void);
void update_acc_y (void);
void update_acc_z (void);

int16_t* get_acc (void);
int16_t* get_filtered_acc (void);

#endif /* INC_TASK_ACCEL_H_ */
