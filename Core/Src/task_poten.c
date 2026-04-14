/*
 * task_potentiometer.c
 *
 *  Created on: 14/04/2026
 *      Author: ldu60
 */

#include "task_poten.h"
#include "adc.h"
#include "states.h"
#include "task_display.h"


static uint16_t poten_raw_adc[1];


void poten_task_execute(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)poten_raw_adc, 1);
}
