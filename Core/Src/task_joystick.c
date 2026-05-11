/*
 * task_joystick.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "task_joystick.h"
#include "adc.h"
#include "gpio.h"
#include "steps.h"
#include "states.h"

#define X_MIDPOINT 	2180
#define X_MAX 		3900
#define X_MIN 		446
#define X_MED_HIGH 	X_MIDPOINT + ((X_MAX - X_MIDPOINT) / 2)
#define X_MED_LOW 	X_MIDPOINT - ((X_MIDPOINT - X_MIN) / 2)

#define Y_MIDPOINT 	2231
#define Y_MAX 		4095
#define Y_MIN 		266
#define Y_MED_HIGH 	Y_MIDPOINT + ((Y_MAX - Y_MIDPOINT) / 2)
#define Y_MED_LOW 	Y_MIDPOINT - ((Y_MIDPOINT - Y_MIN) / 2)

#define MIN_DISPLACEMENT_THRESHOLD 	5
#define JOYSTICK_HOLD_PERIOD 		50

#define JS_TICKS_PERIOD 10

#define JS_TASK_PERIOD 		0.02 * JS_TICKS_PERIOD
#define REACH_GOAL_LIMIT 	4
#define GOAL_SCALER			JS_TASK_PERIOD / REACH_GOAL_LIMIT

static uint16_t raw_adc[3];
static uint16_t JoystickTicksX 			= 0;
static uint16_t JoystickTicksY 			= 0;
static uint16_t JoystickTicksPressed 	= 0;

static uint16_t medium_step_increment 	= 25;
static uint16_t max_step_increment		= 50;

static bool JoystickPressLocked = false; // Var to prevent constant toggle when holding JS press
static bool JoystickIsPressed 	= false;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}

void joystick_task_execute (void)
{
	  switch (get_mode()) {
		  case NORMAL_MODE:
			  joystick_task_normal_mode();
			  break;

		  case TEST_MODE:
			  joystick_task_test_mode();
			  break;

		  case SET_GOAL_MODE:
			  joystick_task_set_goal_mode();
			  break;
	  }
}

void joystick_task_normal_mode (void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
	poll_joystick_y();
	poll_joystick_x();

	if (JoystickTicksY >= JS_TICKS_PERIOD) {
		toggle_units();
		JoystickTicksY = 0;
	}

	if (JoystickTicksX >= 10) {
		change_state();
		JoystickTicksX = 0;
	}

	if (get_state() == GOAL_PROGRESS_STATE) {
		poll_joystick_press();

		if (JoystickTicksPressed >= JOYSTICK_HOLD_PERIOD) {
			JoystickPressLocked = true;
			JoystickTicksPressed = 0;
			toggle_mode();
		}
	}
}

void joystick_task_test_mode (void)
{
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
	 test_mode_poll_joystick_y();
	 increment_step_count();
	 poll_joystick_x();

	 if (JoystickTicksX >= JS_TICKS_PERIOD) {
		 change_state();
		 JoystickTicksX = 0;
	 }

	if (get_state() == GOAL_PROGRESS_STATE) {
		poll_joystick_press();

		if (JoystickTicksPressed >= JOYSTICK_HOLD_PERIOD) {
			JoystickPressLocked = true;
			JoystickTicksPressed = 0;
			toggle_mode();
		}
	}
}

void joystick_task_set_goal_mode (void)
{
	poll_joystick_press();

	if (JoystickTicksPressed >= JOYSTICK_HOLD_PERIOD) {
		JoystickTicksPressed = 0;
		set_goal();

		max_step_increment = get_step_count_goal() * GOAL_SCALER;
		medium_step_increment = max_step_increment / 2;

		toggle_mode();
	} else if (JoystickTicksPressed < JOYSTICK_HOLD_PERIOD && JoystickTicksPressed > 0 && !JoystickIsPressed) {
		JoystickTicksPressed = 0;

		max_step_increment = get_step_count_goal() * GOAL_SCALER;
		medium_step_increment = max_step_increment / 2;

		toggle_mode();
	}
}

void increment_step_count (void)
{
	  int16_t percentage_y = get_percentage_y();

	  if (JoystickTicksY >= JS_TICKS_PERIOD) {
		  if (percentage_y < 0 && percentage_y > -60) {
			  addSteps(1);
		  }
		  else if (percentage_y <= -60 && percentage_y > -90) {
			  addSteps(medium_step_increment);
		  }
		  else if (percentage_y <= -90) {
			  addSteps(max_step_increment);
	  	  }
		  else if (percentage_y > 0 && percentage_y < 60) {
			  addSteps(-1);
		  }
		  else if (percentage_y >= 60 && percentage_y < 90) {
			  addSteps(-medium_step_increment);
		  }
		  else if (percentage_y >= 90) {
			  addSteps(-max_step_increment);
		  }

		  JoystickTicksY = 0;
	  }
}

uint16_t get_joystick_adc_x (void)
{
	return raw_adc[2];
}

uint16_t get_joystick_adc_y (void)
{
	return raw_adc[1];
}

int16_t get_percentage_x (void)
{
    int16_t x_percentage = ((raw_adc[2] - X_MIDPOINT) * 100) / (X_MAX - X_MIDPOINT);

    if (x_percentage >= 100) {
        return 100;
    } else if (x_percentage <= -100) {
    	return -100;
    } else {
        return x_percentage;
    }
}

int16_t get_percentage_y (void)
{
	int16_t y_percentage = ((raw_adc[1] - Y_MIDPOINT) * 100) / (Y_MAX - Y_MIDPOINT);

	if (y_percentage >= 100) {
		return 100;
	} else if (y_percentage <= -100) {
    	return -100;
    } else {
		return y_percentage;
	}
}

void poll_joystick_x (void)
{
	int16_t percentage = get_percentage_x();
	if (abs(percentage) >= 90 || abs(percentage) == 100)
	{
		JoystickTicksX++;
	}
}

void poll_joystick_y (void)
{
	int16_t percentage = get_percentage_y();
	if (percentage <= -90 || percentage == -100)
	{
		JoystickTicksY++;
	}
}

void poll_joystick_press (void)
{
	Mode mode = get_mode();

	if (mode == SET_GOAL_MODE) {
		if (HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin) && !JoystickPressLocked)
		{
			JoystickTicksPressed++;
			JoystickIsPressed = true;
		} else if (HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin) == 0) {
			JoystickPressLocked = false;
			JoystickIsPressed = false;
		}
	} else {
		if (HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin) && !JoystickPressLocked)
		{
			JoystickTicksPressed++;
			JoystickIsPressed = true;
		} else if (!HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin)) {
			JoystickTicksPressed = 0;
			JoystickPressLocked = false;
			JoystickIsPressed = false;
		}
	}
}

void test_mode_poll_joystick_y (void)
{
	int16_t percentage = get_percentage_y();
	if (abs(percentage) > MIN_DISPLACEMENT_THRESHOLD)
	{
		JoystickTicksY++;
	}
}

bool get_is_pressed (void)
{
	return JoystickIsPressed;
}


