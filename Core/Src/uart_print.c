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
#include "task_accel.h"
#include "fir_filter.h"


void print_acc_to_uart(void)
{
	int16_t* acc_xyz = get_acc();

	char acc_buffer[60];

	snprintf(acc_buffer, sizeof(acc_buffer), "X: %d | Y: %d | Z: %d\r\n", acc_xyz[0], acc_xyz[1], acc_xyz[2]);
	HAL_UART_Transmit(&huart2, (uint8_t*) acc_buffer, strlen(acc_buffer), 100);
}

void print_filtered_acc_to_uart(void)
{
	int16_t* filtered_acc_xyz = get_filtered_acc();

	char acc_buffer[20];

	snprintf(acc_buffer, sizeof(acc_buffer), "X: %d\r\n", filtered_acc_xyz[0]);
	HAL_UART_Transmit(&huart2, (uint8_t*) acc_buffer, strlen(acc_buffer), 100);
}
