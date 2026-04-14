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


#define X_MIDPOINT 2180
#define X_MAX 3900
#define X_MIN 446

#define Y_MIDPOINT 2231
#define Y_MAX 4095
#define Y_MIN 266

#define MIN_DISPLACEMENT_LOW_THRESHOLD 5
#define MIN_DISPLACEMENT_MAX_THRESHOLD 25
#define JOYSTICK_DISPLACEMENT_SCALER 10
#define JOYSTICK_HOLD_PERIOD 50

static uint16_t raw_adc[3];
static uint16_t JoystickTicksX = 0;
static uint16_t JoystickTicksY = 0;
static uint16_t JoystickTicksPressed = 0;

static bool joystock_press_locked = false; // Var to prevent constant toggle when holdin JS press
static bool JoystickIsPressed = false;


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}

void joystick_task_execute(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
	poll_joystick_y();
	poll_joystick_x();

	if (JoystickTicksY >= 10) {
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
			joystock_press_locked = true;
			JoystickTicksPressed = 0;
			toggle_mode();
		}
	}

}

void test_mode_joystick_task_execute(void)
{
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
	 test_mode_poll_joystick_y();
	 poll_joystick_x();

	 increment_step_count();

	 if (JoystickTicksX >= 5) {
		 change_state();
		 JoystickTicksX = 0;
	 }

	if (get_state() == GOAL_PROGRESS_STATE) {
		poll_joystick_press();

		if (JoystickTicksPressed >= JOYSTICK_HOLD_PERIOD) {
			joystock_press_locked = true;
			JoystickTicksPressed = 0;
			toggle_mode();
		}
	}
}

void set_goal_mode_joystick_task_execute (void)
{
	poll_joystick_press();

	uint16_t ticks = JoystickTicksPressed;

	if (JoystickTicksPressed >= JOYSTICK_HOLD_PERIOD) {
		JoystickTicksPressed = 0;
		set_goal();
		toggle_mode();
	} else if (JoystickTicksPressed < JOYSTICK_HOLD_PERIOD && JoystickTicksPressed > 0 && !JoystickIsPressed) {
		JoystickTicksPressed = 0;
		toggle_mode();
	}
}

void increment_step_count(void)
{
	  int16_t percentage_y = get_percentage_y();

	  if (JoystickTicksY >= 10) {
		  if (percentage_y < 0) {
			  addSteps(1);
		  } else {
			  addSteps(-1);
		  }
		  JoystickTicksY = 0;
	  } else if (abs(percentage_y) > MIN_DISPLACEMENT_MAX_THRESHOLD) {
		  addSteps(-percentage_y/JOYSTICK_DISPLACEMENT_SCALER);
	  }
}

uint16_t get_joystick_adc_x(void)
{
	return raw_adc[1];
}

uint16_t get_joystick_adc_y(void)
{
	return raw_adc[2];
}

int16_t get_percentage_x(void)
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

int16_t get_percentage_y(void)
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

void poll_joystick_x(void)
{
	int16_t percentage = get_percentage_x();
	if (abs(percentage) >= 90 || abs(percentage) == 100)
	{
		JoystickTicksX++;
	}
}

void poll_joystick_y(void)
{
	int16_t percentage = get_percentage_y();
	if (percentage <= -90 || percentage == -100)
	{
		JoystickTicksY++;
	}
}

void poll_joystick_press(void)
{
	Mode mode = get_mode();

	if (mode == SET_GOAL_MODE) {
		if (HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin) && !joystock_press_locked)
		{
			JoystickTicksPressed++;
			JoystickIsPressed = true;
		} else if (HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin) == 0) {
			joystock_press_locked = false;
			JoystickIsPressed = false;
		}
	} else {
		if (HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin) && !joystock_press_locked)
		{
			JoystickTicksPressed++;
			JoystickIsPressed = true;
		} else if (HAL_GPIO_ReadPin(JOYSTICK_PRESS_GPIO_Port, JOYSTICK_PRESS_Pin) == 0) {
			JoystickTicksPressed = 0;
			joystock_press_locked = false;
			JoystickIsPressed = false;
		}
	}
}

void test_mode_poll_joystick_y(void)
{
	int16_t percentage = get_percentage_y();
	if ((MIN_DISPLACEMENT_LOW_THRESHOLD < abs(percentage)) && (abs(percentage) <= MIN_DISPLACEMENT_MAX_THRESHOLD))
	{
		JoystickTicksY++;
	}
}

bool get_is_pressed(void)
{
	return JoystickIsPressed;
}


