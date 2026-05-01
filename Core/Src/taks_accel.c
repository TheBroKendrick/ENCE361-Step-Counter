/*
 * taks_accel.c
 *
 *  Created on: 1/05/2026
 *      Author: ldu60
 */

#include <stdint.h>

#include "app.h"
#include "task_accel.h"
#include "imu_lsm6ds.h"
#include "spi.h"


static int16_t acc_x;


void accel_init (void)
{
	// Enable accelerometer with high performance
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);
}

void accel_task_execute (void)
{
	uint8_t acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL);
	uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL);
	acc_x = (int16_t)((acc_x_high << 8) | acc_x_low);
}

int16_t get_acc_x (void)
{
	return acc_x;
}
