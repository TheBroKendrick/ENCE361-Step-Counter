/*
 * task_potentiometer.c
 *
 *  Created on: 14/04/2026
 *      Author: Liam du Plessis - ldu60
 *      		Kendrick Dela Cruz - kmd119
 */

#include <stdint.h>

#include "task_poten.h"
#include "adc.h"
#include "states.h"
#include "task_display.h"


#define POTEN_ADC_MAX 4095
#define POTEN_ADC_MIN 145
#define POTEN_RANGE POTEN_ADC_MAX - POTEN_ADC_MIN

#define N_INCRIMENTS 290
#define GOAL_MAX 15000
#define GOAL_MIN 500
#define INCREMENT_STEP (GOAL_MAX - GOAL_MIN) / N_INCRIMENTS


static uint16_t goal_range[N_INCRIMENTS + 1];
static uint16_t raw_adc[3];

/*
 * @brief Function to initialise the potentiometer task.
 */
void poten_task_init (void)
{
	for (uint16_t i = 0; i < N_INCRIMENTS + 1; i++) {
		goal_range[i] = GOAL_MIN + (i * INCREMENT_STEP);
	}
}

/*
 * @brief Function to execute the potentiometer task.
 *
 * This task is only active when in SET GOAL MODE
 */
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

/*
 * @brief Updates the potentiometer readings by reading the ADC.
 */
void poten_adc_update (void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
}

/*
 * @brief Fetches the value of the new goal
 * @return The value of the new goal
 */
uint16_t get_new_goal(void)
{
	uint16_t index = ((raw_adc[0] - POTEN_ADC_MIN) * N_INCRIMENTS ) / (POTEN_RANGE);

	if (index >= N_INCRIMENTS) {
		index = N_INCRIMENTS;
	}

	return goal_range[index];
}

/*
 * @brief Fetches the raw value of the potentiometer output from the ADC.
 * @return The raw ADC value from the potentiometer.
 */
uint16_t get_poten_raw_adc (void)
{
	return raw_adc[0];
}
