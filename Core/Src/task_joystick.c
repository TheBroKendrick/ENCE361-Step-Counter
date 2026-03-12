/*
 * task_joystick.c
 *
 *  Created on: 6/03/2026
 *      Author: kmd119
 */

#include "adc.h"
#include "gpio.h"
#include "task_joystick.h"

static uint16_t raw_adc[2];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}

uint16_t get_joystick_adc_x(void)
{
	return raw_adc[1];
}

uint16_t get_joystick_adc_y(void)
{
	return raw_adc[0];
}

void joystick_task_execute(void)
{
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}
