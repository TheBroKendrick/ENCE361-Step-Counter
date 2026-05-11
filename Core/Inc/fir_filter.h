/*
 * fir_filter.h
 *
 *  Created on: 1/05/2026
 *      Author: ldu60
 */

#ifndef INC_FIR_FILTER_H_
#define INC_FIR_FILTER_H_

#define DATA_ARRAY_LENGTH 60

typedef struct {
	int16_t data[DATA_ARRAY_LENGTH];
	uint8_t current_index;
} Filter;

void filter_init (Filter *given_filter);

int16_t filter_data (Filter *given_filter, int16_t new_val);

#endif /* INC_FIR_FILTER_H_ */
