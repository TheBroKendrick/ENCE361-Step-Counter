/*
 * uart_print.h
 *
 *  Created on: 1/05/2026
 *      Author: ldu60
 */

#ifndef INC_UART_PRINT_H_
#define INC_UART_PRINT_H_

void print__acc_mag (void);
void print_joystick (void);
void print_acc_to_uart(void);
void print_filtered_acc_to_uart(void);
void print_steps_to_uart(void);
void print_poten_to_uart (void);
void toggle_uart(void);

#endif /* INC_UART_PRINT_H_ */
