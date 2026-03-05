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

void joystick_task_execute(void)
{
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}
