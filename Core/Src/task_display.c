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
	uint16_t joystick_adc_x = get_joystick_adc_x();
	uint16_t joystick_adc_y = get_joystick_adc_y();

	char buffer[12];
	size_t max_length = sizeof(buffer);

	ssd1306_SetCursor(0, 20);
	snprintf(buffer, max_length, "X: %d\r\n", joystick_adc_x);
	ssd1306_WriteString(buffer, Font_7x10, White);

	HAL_UART_Transmit(&huart2, (const uint8_t*)buffer, sizeof(buffer) - 1, 100);

	ssd1306_SetCursor(0, 40);
	snprintf(buffer, max_length, "Y: %d\r\n\n", joystick_adc_y);
	ssd1306_WriteString(buffer, Font_7x10, White);

	HAL_UART_Transmit(&huart2, (const uint8_t*)buffer, sizeof(buffer) - 1, 100);

	ssd1306_UpdateScreen();
}
