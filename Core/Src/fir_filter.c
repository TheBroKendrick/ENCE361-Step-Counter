/*
 * fir_filter.c
 *
 *  Created on: 1/05/2026
 *      Author: Liam du Plessis - ldu60
 */

#include <stdint.h>

#include "fir_filter.h"
#include "task_accel.h"

/*
 * @brief Initialises the FIR filter.
 * @param given_filter Pointer to the filter object to be used. Consists of an array and an index.
 */
void filter_init (Filter *given_filter)
{
	for (uint8_t i = 0; i < DATA_ARRAY_LENGTH; i++ ) {
		given_filter->data[i] = 0;
	}

	given_filter->current_index = 0;
}

/*
 * @brief Executes the FIR filtering.
 * @param given_filter Pointer to the filter object to be used. Consists of an array and an index.
 * @param new_val The value of the new sample.
 * @return The average of the current data within the filter array.
 */
int16_t filter_data (Filter *given_filter, int16_t new_val)
{
	int32_t sum_data = 0;
	given_filter->data[given_filter->current_index] = new_val;

	for (uint8_t i = 0; i < DATA_ARRAY_LENGTH; i++) {
		sum_data += given_filter->data[i];
	}

	given_filter->current_index = (given_filter->current_index + 1) % DATA_ARRAY_LENGTH;
	return sum_data / DATA_ARRAY_LENGTH;
}
