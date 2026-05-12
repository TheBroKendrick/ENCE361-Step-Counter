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
#include <string.h>

#include "task_display.h"
#include "states.h"
#include "task_joystick.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "steps.h"
#include "task_poten.h"


#define LINE_1 0
#define LINE_2 15
#define LINE_3 30
#define LINE_4 50

#define CURSOR_COL_MARGIN_1 0
#define CURSOR_COL_MARGIN_2 20

static char numbers_buffer[40];
static char units_buffer[20];


void display_init (void)
{
	ssd1306_Init();
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
}


/*
 * @brief Function to execute the display task on for RCAP's display.
 *
 * The mode determines the layout of the display.
 */
void display_task_execute (void)
{
	ssd1306_Fill(Black);

	switch (get_mode()) {
		case NORMAL_MODE:
			ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
			if (get_goal_reached()) {
				ssd1306_WriteString("GOAL REACHED!!", Font_7x10, White);
			} else {
				ssd1306_WriteString("STEP COUNTER", Font_7x10, White);
			}

			display_state();
			break;

		case TEST_MODE:
			ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
			ssd1306_WriteString("TEST MODE", Font_7x10, White);

			display_state();
			break;

		case SET_GOAL_MODE:
			ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_1);
			ssd1306_WriteString("GOAL SET MODE", Font_7x10, White);

			display_goal_set();
			break;
	}

	// Display units
	ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_4);
	ssd1306_WriteString(units_buffer, Font_7x10, White);

	ssd1306_UpdateScreen();
}

/*
 * @brief Displays the state under NORMAL_MODE
 */
void display_state (void)
{
	State state = get_state();

	switch (state) {
		case CURRENT_STEPS_STATE:
			display_current_steps();

			ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_3);
			break;

		case GOAL_PROGRESS_STATE:
			display_goal_progress();

			ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_3);
			break;

		case DISTANCE_TRAVELLED_STATE:
			display_distance_travelled();

			ssd1306_SetCursor(CURSOR_COL_MARGIN_2, LINE_3);
			break;
	}

	ssd1306_WriteString(numbers_buffer, Font_11x18, White);
}

void display_current_steps(void)
{
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString("Step Count:", Font_7x10, White);

	Unit units = get_units();

	if (units == PERCENTAGE_OF_GOAL) {
		// Config numbers & units buffers
		int16_t progress = get_goal_progress_percentage();
		snprintf(numbers_buffer, sizeof(numbers_buffer), "%d\r\n", progress);
		snprintf(units_buffer, sizeof(units_buffer), "[%%]");
	} else {
		// Config numbers & units buffers
		int16_t steps = get_step_count();
		snprintf(numbers_buffer, sizeof(numbers_buffer), "%d\r\n", steps);
		snprintf(units_buffer, sizeof(units_buffer), "[steps]");
	}
}

void display_goal_progress(void)
{
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString("Goal Progress:", Font_7x10, White);

	// Config numbers & units buffers
	int16_t steps = get_step_count();
	int16_t goal = get_step_count_goal();
	snprintf(numbers_buffer, sizeof(numbers_buffer), "%u/%u\r\n", steps, goal);
	snprintf(units_buffer, sizeof(units_buffer), "[steps]");
}

void display_distance_travelled(void)
{
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString("Distance:", Font_7x10, White);

	Unit units = get_units();
	float distance = get_distance_travelled();
	uint16_t whole_distance = (uint16_t)distance;
	uint16_t fraction_distance = (uint16_t)((distance - whole_distance) * 100);

	if (units == YARDS) {
		// Config numbers & units buffers
		snprintf(numbers_buffer, sizeof(numbers_buffer), "%d.%02d\r\n", whole_distance, fraction_distance);
		snprintf(units_buffer, sizeof(units_buffer), "[Yards]");
	} else {
		// Config numbers & units buffers
		snprintf(numbers_buffer, sizeof(numbers_buffer), "%d.%02d\r\n", whole_distance, fraction_distance);
		snprintf(units_buffer, sizeof(units_buffer), "[Kilometers]");
	}
}

/*
 * @brief Displays the state under SET_GOAL_MODE
 */
void display_goal_set(void)
{
	uint16_t prev_goal = get_step_count_goal();
	uint16_t new_goal = get_new_goal();

	static char prev_goal_buffer[32];
	static char new_goal_buffer[32];

	// Config numbers & units buffers
	snprintf(prev_goal_buffer, sizeof(prev_goal_buffer), "Goal: %u\r\n", prev_goal);
	snprintf(new_goal_buffer, sizeof(new_goal_buffer), "New goal: %u\r\n", new_goal);
	snprintf(units_buffer, sizeof(units_buffer), "[steps]");

	// Display numbers
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_2);
	ssd1306_WriteString(prev_goal_buffer, Font_7x10, White);

	// Display numbers
	ssd1306_SetCursor(CURSOR_COL_MARGIN_1, LINE_3);
	ssd1306_WriteString(new_goal_buffer, Font_7x10, White);
}
