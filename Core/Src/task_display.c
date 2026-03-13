/*
 * task_display.c
 *
 *  Created on: 12/03/2026
 *      Author: ldu60
 */

#include <stdlib.h>

#include <stdio.h>
#include <stdint.h>

#include "task_display.h"
#include "task_joystick.h"
#include "usart.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"

static char adc_buffer[12];
static size_t adc_buffer_length = sizeof(adc_buffer);

static char percentage_buffer[22];
static size_t percentage_buffer_length = sizeof(percentage_buffer);


void display_init (void)
{
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Starting ...", Font_7x10, White);
}

void display_task_execute(void)
{
	ssd1306_Fill(Black);

	print_header();
	print_to_uart();
	display_percentage();

	ssd1306_UpdateScreen();
}

void print_header(void)
{
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Joystick Position:", Font_7x10, White);
}

void print_to_uart(void)
{
	uint16_t joystick_adc_x = get_joystick_adc_x();
	uint16_t joystick_adc_y = get_joystick_adc_y();

	snprintf(adc_buffer, adc_buffer_length, "X: %d\r\n", joystick_adc_x);
	HAL_UART_Transmit(&huart2, (const uint8_t*)adc_buffer, sizeof(adc_buffer) - 1, 100);

	snprintf(adc_buffer, adc_buffer_length, "Y: %d\r\n", joystick_adc_y);
	HAL_UART_Transmit(&huart2, (const uint8_t*)adc_buffer, sizeof(adc_buffer) - 1, 100);
}

void display_percentage(void)
{
	int16_t x_signed_percentage = get_percentage_x();
	int16_t y_signed_percentage = get_percentage_y();

	ssd1306_SetCursor(0, 20);

	if (x_signed_percentage > 0) {
		snprintf(percentage_buffer, percentage_buffer_length, "X: %d (LEFT)\r\n", abs(x_signed_percentage));
	} else if (x_signed_percentage < 0) {
		snprintf(percentage_buffer, percentage_buffer_length, "X: %d (RIGHT)\r\n", abs(x_signed_percentage));
	} else {
		snprintf(percentage_buffer, percentage_buffer_length, "X: %d (REST)\r\n", abs(x_signed_percentage));
	}

	ssd1306_WriteString(percentage_buffer, Font_7x10, White);


	ssd1306_SetCursor(0, 40);

	if (y_signed_percentage > 0) {
			snprintf(percentage_buffer, percentage_buffer_length, "Y: %d (DOWN)\r\n", abs(y_signed_percentage));
	} else if (y_signed_percentage < 0) {
		snprintf(percentage_buffer, percentage_buffer_length, "Y: %d (UP)\r\n", abs(y_signed_percentage));
	} else {
		snprintf(percentage_buffer, percentage_buffer_length, "Y: %d (REST)\r\n", abs(y_signed_percentage));
	}

	ssd1306_WriteString(percentage_buffer, Font_7x10, White);
}
