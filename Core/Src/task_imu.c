/*
 * task_imu.c
 *
 *  Created on: 5/05/2026
 *      Author: kenmi
 */
#include <stdint.h>
#include <stdbool.h>

#include "task_imu.h"
#include "imu_lsm6ds.h"
#include "steps.h"

static int16_t previous_steps = 0;


void imu_init(void)
{
	imu_lsm6ds_write_byte(FUNC_CFG_ACCESS, ENABLE_EMBEDDED_BANK_A);
	imu_lsm6ds_write_byte(PEDO_DEB_REG, MIN_NUM_OF_STEPS);
	imu_lsm6ds_write_byte(FUNC_CFG_ACCESS, 0x00);

	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);
	imu_lsm6ds_write_byte(INT1_CTRL, INT1_CTRL_ENABLE);
	imu_lsm6ds_write_byte(CTRL10_C, CTRL10_C_RESET);
	imu_lsm6ds_write_byte(CTRL10_C, CTRL10_C_ENABLE);
}

void imu_task_execute(void)
{
	int16_t steps = ((imu_lsm6ds_read_byte(STEP_COUNTER_H) << 8) | imu_lsm6ds_read_byte(STEP_COUNTER_L));
	int16_t step_difference = steps - previous_steps;
	addSteps(step_difference);
	previous_steps = steps;
}
