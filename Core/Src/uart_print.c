/*
 * uart_print.c
 *
 *  Created on: 1/05/2026
 *      Author: ldu60
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "usart.h"
#include "uart_print.h"
#include "task_accel.h"
#include "task_poten.h"
#include "task_joystick.h"
#include "fir_filter.h"
#include "imu_lsm6ds.h"
#include "steps.h"


void print_joystick (void)
{
	uint16_t adc_x = get_joystick_adc_x;
	uint16_t adc_y = get_joystick_adc_y;
}

void print_acc_to_uart(void)
{
	int16_t* acc_xyz = get_filtered_acc();

	char acc_buffer[60];

	snprintf(acc_buffer, sizeof(acc_buffer), "X: %d | Y: %d | Z: %d\r\n", acc_xyz[0], acc_xyz[1], acc_xyz[2]);
	HAL_UART_Transmit(&huart2, (uint8_t*) acc_buffer, strlen(acc_buffer), 100);
}

void print_filtered_acc_to_uart(void)
{
	int16_t* filtered_acc_xyz = get_filtered_acc();
	int16_t* acc_xyz = get_acc();

	char acc_buffer[40];

	snprintf(acc_buffer, sizeof(acc_buffer), "%d,%d\r\n", acc_xyz[0], filtered_acc_xyz[0]);
	HAL_UART_Transmit(&huart2, (uint8_t*) acc_buffer, strlen(acc_buffer), 100);
}

void print_steps_to_uart(void)
{

	char StepCount_buffer[40];

	snprintf(StepCount_buffer, sizeof(StepCount_buffer), "%d\r\n", get_step_count());
	HAL_UART_Transmit(&huart2, (uint8_t*) StepCount_buffer, strlen(StepCount_buffer), 100);
}

void print_poten_to_uart (void)
{
	poten_adc_update ();
	int16_t poten_adc = get_new_goal();

	char poten_buffer[20];

	snprintf(poten_buffer, sizeof(poten_buffer), "%d\r\n", poten_adc);
	HAL_UART_Transmit(&huart2, (uint8_t*) poten_buffer, strlen(poten_buffer), 100);
}

void toggle_uart(void)
{
	HAL_UART_StateTypeDef state = HAL_UART_GetState(&huart2);
	if (state == HAL_UART_STATE_RESET)
	{
		HAL_UART_Init(&huart2);
	}
	else
	{
		HAL_UART_DeInit(&huart2);
	}
}
