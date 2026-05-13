/*
 * taks_accel.c
 *
 *  Created on: 1/05/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>
#include <math.h>

#include "app.h"
#include "task_accel.h"
#include "imu_lsm6ds.h"
#include "spi.h"
#include "fir_filter.h"


static int16_t acc_mag;
static int16_t accel_xyz[3];
static int16_t filtered_accel_xyz[3];

static Filter filters_xyz[3];


/*
 * @brief Function to initialize accelerometer module
 *
 * Run once before use.
 */
void accel_init (void)
{
	// Enable accelerometer with high performance
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);

	// Initialise filter for x vals
	filter_init (&filters_xyz[0]);
	filter_init (&filters_xyz[1]);
	filter_init (&filters_xyz[2]);
}

/*
 * @brief Function to update module
 * 			- Updates the accelerometer reading
 * 			- Adds value to initialized FIR filter
 * 			- Updates accelerometer magnitude.
 */
void accel_task_execute (void)
{
	update_acc_x();
	update_acc_y();
	update_acc_z();

	filtered_accel_xyz[0] = filter_data(&filters_xyz[0], accel_xyz[0]);
	filtered_accel_xyz[1] = filter_data(&filters_xyz[1], accel_xyz[1]);
	filtered_accel_xyz[2] = filter_data(&filters_xyz[2], accel_xyz[2]);

	acc_mag = sqrt(filtered_accel_xyz[0] * filtered_accel_xyz[0]
				 + filtered_accel_xyz[1] * filtered_accel_xyz[1]
		         + filtered_accel_xyz[2] * filtered_accel_xyz[2]);
}

/*
 * @brief Function to update accelerometer X reading
 */
void update_acc_x (void)
{
	uint8_t acc_x_low  = imu_lsm6ds_read_byte(OUTX_L_XL);
	uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL);

	accel_xyz[0] = (int16_t)((acc_x_high << 8) | acc_x_low);
}

/*
 * @brief Function to update accelerometer Y reading
 */
void update_acc_y (void)
{
	uint8_t acc_y_low  = imu_lsm6ds_read_byte(OUTY_L_XL);
	uint8_t acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL);

	accel_xyz[1] = (int16_t)((acc_y_high << 8) | acc_y_low);
}

/*
 * @brief Function to update accelerometer Z reading
 */
void update_acc_z (void)
{
	uint8_t acc_z_low  = imu_lsm6ds_read_byte(OUTZ_L_XL);
	uint8_t acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL);

	accel_xyz[2] = (int16_t)((acc_z_high << 8) | acc_z_low);
}

/*
 * @brief Getter function.
 * 			- Returns unfiltered accelerometer readings
 */
int16_t* get_acc (void)
{
	return accel_xyz;
}

/*
 * @brief Getter function.
 * 			- Returns filtered accelerometer readings
 */
int16_t* get_filtered_acc (void)
{
	return filtered_accel_xyz;
}

/*
 * @brief Getter function.
 * 			- Returns accelerometer magnitude
 */
int16_t get_acc_mag (void)
{
	return acc_mag;
}



