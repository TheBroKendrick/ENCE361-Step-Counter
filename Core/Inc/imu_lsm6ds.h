/*
 * imu_lsm6ds.h
 *
 *  Created on: Nov 27, 2024
 *      Author: fsy13
 */

#ifndef INC_IMU_LSM6DS_H_
#define INC_IMU_LSM6DS_H_

#include <stdint.h>

typedef enum {
	// Embedded functions CFG register
	FUNC_CFG_ACCESS = 0x01,

	// Sensor Sync configuration registers
	SENSOR_SYNC_TIME_FRAME = 0x04,
	SENSOR_SYNC_RES_RATIO,

	// FIFO configuration registers
	FIFO_CTRL1,
	FIFO_CTRL2,
	FIFO_CTRL3,
	FIFO_CTRL4,
	FIFO_CTRL5,


	DRDY_PULSE_CFG_G,

	// INT Pin controls
	INT1_CTRL = 0x0D,
	INT2_CTRL,

	// Who I am ID
	WHO_AM_I,

	// Accelerometer and gyroscope control registers
	CTRL1_XL,
	CTRL2_G,
	CTRL3_C,
	CTRL4_C,
	CTRL5_C,
	CTRL6_C,
	CTRL7_G,
	CTRL8_XL,
	CTRL9_XL,
	CTRL10_C,

	// I2C Master Config register
	MASTER_CONFIG,

	// Interrupt Registers
	WAKE_UP_SRC,
	TAP_SRC,
	D6D_SRC,

	// Status data register for user interface
	STATUS_REG,

	// Temperature output data registers
	OUT_TEMP_L = 0x20,
	OUT_TEMP_H,


	// Gyroscope output registers for user interface
	OUTX_L_G,
	OUTX_H_G,
	OUTY_L_G,
	OUTY_H_G,
	OUTZ_L_G,
	OUTZ_H_G,

	// Accelerometer output registers
	OUTX_L_XL,
	OUTX_H_XL,
	OUTY_L_XL,
	OUTY_H_XL,
	OUTZ_L_XL,
	OUTZ_H_XL,

	// Sensor hub output registers
	SENSORHUB1_REG,
	SENSORHUB2_REG,
	SENSORHUB3_REG,
	SENSORHUB4_REG,
	SENSORHUB5_REG,
	SENSORHUB6_REG,
	SENSORHUB7_REG,
	SENSORHUB8_REG,
	SENSORHUB9_REG,
	SENSORHUB10_REG,
	SENSORHUB11_REG,
	SENSORHUB12_REG,

	// FIFO status registers
	FIFO_STATUS1,
	FIFO_STATUS2,
	FIFO_STATUS3,
	FIFO_STATUS4,

	// FIFO data output registers
	FIFO_DATA_OUT_L,
	FIFO_DATA_OUT_H,

	// Timestamp output registers
	TIMESTAMP0_REG,
	TIMESTAMP1_REG,
	TIMESTAMP2_REG,

	// Step counter timestamp registers
	STEP_TIMESTAMP_L = 0x49,
	STEP_TIMESTAMP_H,

	// Step counter output registers
	STEP_COUNTER_L,
	STEP_COUNTER_H,

	// Sensor hub output registers
	SENSORHUB13_REG,
	SENSORHUB14_REG,
	SENSORHUB15_REG,
	SENSORHUB16_REG,
	SENSORHUB17_REG,
	SENSORHUB18_REG,

	// Interrupt registers
	FUNC_SRC1,
	FUNC_SRC2,
	WRIST_TILT_IA,
	TAP_CFG = 0x58,
	TAP_THS_6D,
	INT_DUR2,
	WAKE_UP_THS,
	WAKE_UP_DUR,
	FREE_FALL,
	MD1_CFG,
	MD2_CFG,

	MASTER_CMD_CODE,
	SENS_SYNC_SPI_ERROR_CODE,

	// External magnetometer raw data output registers
	OUT_MAG_RAW_X_L = 0x66,
	OUT_MAG_RAW_X_H,
	OUT_MAG_RAW_Y_L,
	OUT_MAG_RAW_Y_H,
	OUT_MAG_RAW_Z_L,
	OUT_MAG_RAW_Z_H,

	// Accelerometer user output correction
	X_OFS_USR= 0x73,
	Y_OFS_USR,
	Z_OFS_USR
} imu_register_t;

// Standard options
#define CTRL1_XL_HIGH_PERFORMANCE 0xA0U
#define CTRL10_C_RESET 0b00010110
#define CTRL10_C_ENABLE 0b00010100
#define INT1_CTRL_ENABLE 0b10000000

void imu_lsm6ds_write_byte(imu_register_t register_address, uint8_t value);

uint8_t imu_lsm6ds_read_byte(imu_register_t register_address);
void imu_init(void);

#endif /* INC_IMU_LSM6DS_H_ */
