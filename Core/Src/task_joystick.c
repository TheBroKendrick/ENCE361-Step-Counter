/*
 * task_joystick.c
 *
 *  Created on: 6/03/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>
#include <stdlib.h>

#include "task_joystick.h"
#include "adc.h"
#include "gpio.h"
#include "steps.h"


#define X_MIDPOINT 2180
#define X_MAX 3900
#define X_MIN 446

#define Y_MIDPOINT 2231
#define Y_MAX 4095
#define Y_MIN 266

#define MIN_DISPLACEMENT_LOW_THRESHOLD 5
#define MIN_DISPLACEMENT_MAX_THRESHOLD 25
#define JOYSTICK_DISPLACEMENT_SCALER 10

static uint16_t raw_adc[2];
static uint16_t JoystickTicks = 0;



void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}

void joystick_task_execute(void)
{
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}

void joystick_task_test(void)
{
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
	 poll_joystick_y();
	 int16_t percentage_y = get_percentage_y();
	  if (JoystickTicks >= 10)
	  {
		  if (percentage_y < 0)
		  {
			  addSteps(1);
		  }
		  else
		  {
			  addSteps(-1);
		  }

		  JoystickTicks = 0;
	  }
	  else if (abs(percentage_y) > MIN_DISPLACEMENT_MAX_THRESHOLD)
	  {
		  addSteps(-percentage_y/JOYSTICK_DISPLACEMENT_SCALER);
	  }
}


uint16_t get_joystick_adc_x(void)
{
	return raw_adc[1];
}

uint16_t get_joystick_adc_y(void)
{
	return raw_adc[0];
}

int16_t get_percentage_x(void)
{
    int16_t x_percentage = ((raw_adc[1] - X_MIDPOINT) * 100) / (X_MAX - X_MIDPOINT);

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
	int16_t y_percentage = ((raw_adc[0] - Y_MIDPOINT) * 100) / (Y_MAX - Y_MIDPOINT);

	if (y_percentage >= 100) {
		return 100;
	} else if (y_percentage <= -100) {
    	return -100;
    } else {
		return y_percentage;
	}
}

void poll_joystick_y(void)
{
	int16_t percentage = get_percentage_y();
	if ((MIN_DISPLACEMENT_LOW_THRESHOLD < abs(percentage)) && (abs(percentage) <= MIN_DISPLACEMENT_MAX_THRESHOLD))
	{
		JoystickTicks++;
	}
}
