/*
 * task_imu.c
 *
 *  Created on: 5/05/2026
 *      Author: kenmi
 */
#include <stdint.h>
#include <stdbool.h>

#include "imu_lsm6ds.h"
#include "steps.h"
static bool data_ready = false;

void imu_init(void)
{
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);
	imu_lsm6ds_write_byte(INT1_CTRL, INT1_CTRL_ENABLE);
	imu_lsm6ds_write_byte(CTRL10_C, CTRL10_C_RESET);
	imu_lsm6ds_write_byte(CTRL10_C, CTRL10_C_ENABLE);

}

void imu_task_execute(void)
{
	int16_t steps = ((imu_lsm6ds_read_byte(STEP_COUNTER_H) << 8) | imu_lsm6ds_read_byte(STEP_COUNTER_L));
	update_steps(steps);
	data_ready = false;
}
