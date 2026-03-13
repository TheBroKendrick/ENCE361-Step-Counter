/*
 * task_joystick.c
 *
 *  Created on: 6/03/2026
 *      Author: kmd119
 */

#include <stdlib.h>

#include "adc.h"
#include "gpio.h"
#include "task_joystick.h"

#define X_MIDPOINT 2196
#define X_MAX 3938
#define X_MIN 421

#define Y_MIDPOINT 2245
#define Y_MAX 4095
#define Y_MIN 261

static uint16_t raw_adc[2];


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}

void joystick_task_execute(void)
{
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
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
	int16_t x_percentage = ((raw_adc[1] - X_MIDPOINT) / (X_MAX - X_MIDPOINT)) * 100;

	if (abs(x_percentage) >= 100) {
		return 100;
	} else {
		return x_percentage;
	}
}

int16_t get_percentage_y(void)
{
	int16_t y_percentage = ((raw_adc[0] - Y_MIDPOINT) / (Y_MAX - Y_MIDPOINT)) * 100;

	if (abs(y_percentage) >= 100) {
		return 100;
	} else {
		return y_percentage;
	}
}
