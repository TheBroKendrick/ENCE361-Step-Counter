/*
 * fir_filter.c
 *
 *  Created on: 1/05/2026
 *      Author: ldu60
 */

#include <stdint.h>

#include "fir_filter.h"
#include "task_accel.h"


#define DATA_ARRAY_LENGTH 10


void filter_init (Filter *given_filter)
{
	int16_t data_array[DATA_ARRAY_LENGTH] = {0};

	given_filter->data = data_array;
	given_filter->current_index = 0;
}

int16_t filter_data (Filter *given_filter, int16_t new_val)
{
	uint8_t sum_data = 0;
	given_filter->data[given_filter->current_index] = new_val;

	for (uint8_t i = 0; i < DATA_ARRAY_LENGTH; i++) {
		sum_data += given_filter->data[(given_filter->current_index - i + DATA_ARRAY_LENGTH)];
	}

	given_filter->current_index = (given_filter->current_index + 1) % DATA_ARRAY_LENGTH;
	return sum_data / DATA_ARRAY_LENGTH;
}
