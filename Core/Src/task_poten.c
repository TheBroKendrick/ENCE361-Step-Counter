/*
 * task_potentiometer.c
 *
 *  Created on: 14/04/2026
 *      Author: ldu60
 */

#include <stdint.h>

#include "task_poten.h"
#include "adc.h"
#include "states.h"
#include "task_display.h"


#define POTEN_ADC_MAX 4095
#define POTEN_ADC_MIN 145

#define CONVERSION_SLOPE 3.67
#define CONVERSION_OFFSET 32

static uint16_t raw_adc[3];


void poten_task_execute(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
}

uint16_t get_new_goal(void)
{
	return (CONVERSION_SLOPE * raw_adc[0]) - CONVERSION_OFFSET;
}
