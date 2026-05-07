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
#define POTEN_ADC_MIN 115
#define POTEN_RANGE POTEN_ADC_MAX - POTEN_ADC_MIN

#define N_INCRIMENTS 290
#define GOAL_MAX 15000
#define GOAL_MIN 500
#define INCREMENT_STEP (GOAL_MAX - GOAL_MIN) / N_INCRIMENTS

static uint16_t goal_range[N_INCRIMENTS + 1];
static uint16_t raw_adc[3];

//const uint16_t values[] = {
//    1, 2, 5, 10, 20, 50, 100
//};
//
//#define NUM_VALUES (sizeof(values)/sizeof(values[0]))
//
//uint16_t adc; // 0–4095
//
//uint8_t index = (adc * 	) / 4096;
//
//if (index >= NUM_VALUES)
//    index = NUM_VALUES - 1;
//
//uint16_t output = values[index];

void poten_task_init (void)
{
	for (uint16_t i = 0; i < N_INCRIMENTS + 1; i++) {
		goal_range[i] = GOAL_MIN + (i * INCREMENT_STEP);
	}
}

void poten_task_execute(void)
{
	  switch (get_mode()) {
		  case NORMAL_MODE:
			  break;

		  case TEST_MODE:
			  break;

		  case SET_GOAL_MODE:
			  poten_adc_update();
			  break;
	  }
}

void poten_adc_update (void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
}

uint16_t get_new_goal(void)
{
	uint16_t index = ((raw_adc[0] - POTEN_ADC_MIN) * N_INCRIMENTS ) / (POTEN_RANGE);

	if (index >= N_INCRIMENTS) {
		index = N_INCRIMENTS;
	}

	return goal_range[index];
}

uint16_t get_poten_raw_adc (void)
{
	return raw_adc[0];
}
