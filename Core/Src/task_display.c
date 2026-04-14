/*
 * task_display.c
 *
 *  Created on: 12/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "task_display.h"
#include "states.h"
#include "task_joystick.h"
#include "usart.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "steps.h"
#include "task_poten.h"


#define LINE_1 0
#define LINE_2 20
#define LINE_3 35
#define LINE_4 50

#define CURSOR_COL_MARGIN_1 0
#define CURSOR_COL_MARGIN_2 20

static char adc_buffer[12];
static size_t adc_buffer_length = sizeof(adc_buffer);

static char percentage_buffer[22];
static size_t percentage_buffer_length = sizeof(percentage_buffer);


void display_init (void)
{
	ssd1306_Init();
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
}

void display_task_execute(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
	ssd1306_WriteString("NORMAL MODE", Font_7x10, White);

	display_state();
	ssd1306_UpdateScreen();
}

void test_mode_display_task_execute(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
	ssd1306_WriteString("TEST MODE", Font_7x10, White);

	display_state();
	ssd1306_UpdateScreen();
}

void set_goal_mode_display_task_execute (void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
	ssd1306_WriteString("GOAL SET MODE", Font_7x10, White);

	display_goal_set();
	ssd1306_UpdateScreen();
}

void display_state(void)
{
	State state = get_state();

	switch (state) {
		case CURRENT_STEPS_STATE:
			display_current_steps();
			break;

		case GOAL_PROGRESS_STATE:
			display_goal_progress();
			break;

		case DISTANCE_TRAVELLED_STATE:
			display_distance_travelled();
			break;
	}
}

void display_current_steps(void)
{
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString("Step Count:", Font_7x10, White);

	Unit units = get_units();

	if (units == PERCENTAGE_OF_GOAL) {
		int16_t progress = get_goal_progress_percentage();
		static char progress_buffer[32];
		size_t progress_buffer_length = sizeof(progress_buffer);
		snprintf(progress_buffer, progress_buffer_length, "%u\r\n", progress);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_3);
		ssd1306_WriteString(progress_buffer, Font_7x10, White);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_4);
		ssd1306_WriteString("[%]", Font_7x10, White);
	} else {
		int16_t steps = get_step_count();
		static char step_buffer[32];
		size_t step_buffer_length = sizeof(step_buffer);
		snprintf(step_buffer, step_buffer_length, "%u\r\n", steps);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_3);
		ssd1306_WriteString(step_buffer, Font_7x10, White);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_4);
		ssd1306_WriteString("[steps]", Font_7x10, White);
	}
}

void display_goal_progress(void)
{
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString("Goal Progress:", Font_7x10, White);

	int16_t steps = get_step_count();
	int16_t goal = get_step_count_goal();
	static char progress_buffer[32];
	size_t progress_buffer_length = sizeof(progress_buffer);
	snprintf(progress_buffer, progress_buffer_length, "%u / %u\r\n", steps, goal);

	ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_3);
	ssd1306_WriteString(progress_buffer, Font_7x10, White);

	ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_4);
	ssd1306_WriteString("[steps]", Font_7x10, White);
}

void display_distance_travelled(void)
{
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString("Distance:", Font_7x10, White);

	Unit units = get_units();

	if (units == YARDS) {
		float distance = get_distance_travelled();
		uint16_t whole_distance = (uint16_t)distance;
		uint16_t fraction_distance = (uint16_t)((distance - whole_distance) * 100);

		static char distance_buffer[40];
		size_t distance_buffer_length = sizeof(distance_buffer);
		snprintf(distance_buffer, distance_buffer_length, "%d.%02d\r\n", whole_distance, fraction_distance);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_3);
		ssd1306_WriteString(distance_buffer, Font_7x10, White);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_4);
		ssd1306_WriteString("[Yards]", Font_7x10, White);
	} else {
		float distance = get_distance_travelled();
		uint16_t whole_distance = (uint16_t)distance;
		uint16_t fraction_distance = (uint16_t)((distance - whole_distance) * 100);

		static char distance_buffer[40];
		size_t distance_buffer_length = sizeof(distance_buffer);
		snprintf(distance_buffer, distance_buffer_length, "%d.%02d\r\n", whole_distance, fraction_distance);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_3);
		ssd1306_WriteString(distance_buffer, Font_7x10, White);

		ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_4);
		ssd1306_WriteString("[Kilometers]", Font_7x10, White);
	}
}

void display_goal_set(void)
{
	int16_t prev_goal = get_step_count_goal();
	static char prev_goal_buffer[32];
	size_t prev_goal_buffer_length = sizeof(prev_goal_buffer);
	snprintf(prev_goal_buffer, prev_goal_buffer_length, "Goal: %u\r\n", prev_goal);

	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString(prev_goal_buffer, Font_7x10, White);

	int16_t new_goal = get_new_goal();
	static char new_goal_buffer[32];
	size_t new_goal_buffer_length = sizeof(new_goal_buffer);
	snprintf(new_goal_buffer, new_goal_buffer_length, "New goal: %u\r\n", new_goal);

	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_3);
	ssd1306_WriteString(new_goal_buffer, Font_7x10, White);

	ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_4);
	ssd1306_WriteString("[steps]", Font_7x10, White);
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

	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);

	if (x_signed_percentage > 0) {
		snprintf(percentage_buffer, percentage_buffer_length, "X: %d%% (LEFT)\r\n", abs(x_signed_percentage));
	} else if (x_signed_percentage < 0) {
		snprintf(percentage_buffer, percentage_buffer_length, "X: %d%% (RIGHT)\r\n", abs(x_signed_percentage));
	} else {
		snprintf(percentage_buffer, percentage_buffer_length, "X: %d%% (REST)\r\n", abs(x_signed_percentage));
	}

	ssd1306_WriteString(percentage_buffer, Font_7x10, White);


	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_3);

	if (y_signed_percentage > 0) {
			snprintf(percentage_buffer, percentage_buffer_length, "Y: %d%% (DOWN)\r\n", abs(y_signed_percentage));
	} else if (y_signed_percentage < 0) {
		snprintf(percentage_buffer, percentage_buffer_length, "Y: %d%% (UP)\r\n", abs(y_signed_percentage));
	} else {
		snprintf(percentage_buffer, percentage_buffer_length, "Y: %d%% (REST)\r\n", abs(y_signed_percentage));
	}

	ssd1306_WriteString(percentage_buffer, Font_7x10, White);
}

