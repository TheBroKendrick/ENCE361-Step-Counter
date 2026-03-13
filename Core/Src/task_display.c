/*
 * task_display.c
 *
 *  Created on: 12/03/2026
 *      Author: ldu60
 */

#include <stdio.h>
#include <stdint.h>

#include "task_display.h"
#include "task_joystick.h"
#include "usart.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"

void display_init (void)
{
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Hello world", Font_7x10, White);
}

void display_task_execute(void)
{
	print_to_uart();
	display_percentage();

	ssd1306_UpdateScreen();
}

void print_to_uart(void)
{
	uint16_t joystick_adc_x = get_joystick_adc_x();
	uint16_t joystick_adc_y = get_joystick_adc_y();

	char adc_buffer[12];
	size_t max_length = sizeof(adc_buffer);

	snprintf(adc_buffer, max_length, "X: %d\r\n", joystick_adc_x);
	HAL_UART_Transmit(&huart2, (const uint8_t*)adc_buffer, sizeof(adc_buffer) - 1, 100);

	snprintf(adc_buffer, max_length, "Y: %d\r\n\n", joystick_adc_y);
	HAL_UART_Transmit(&huart2, (const uint8_t*)adc_buffer, sizeof(adc_buffer) - 1, 100);
}

void display_percentage(void)
{
	int16_t x_percentage = get_percentage_x();
	int16_t y_percentage = get_percentage_y();

	char percentage_buffer[12];
	size_t max_length = sizeof(percentage_buffer);

	ssd1306_SetCursor(0, 20);
	snprintf(percentage_buffer, max_length, "X: %d\r\n", x_percentage);
	ssd1306_WriteString(percentage_buffer, Font_7x10, White);

	ssd1306_SetCursor(0, 40);
	snprintf(percentage_buffer, max_length, "Y: %d\r\n", y_percentage);
	ssd1306_WriteString(percentage_buffer, Font_7x10, White);
}
