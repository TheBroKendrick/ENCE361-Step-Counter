/*
 * task_display.c
 *
 *  Created on: 12/03/2026
 *      Author: ldu60
 */

#include "task_display.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"

void display_init (void)
{
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Hello world", Font_7x10, White);
}

void display_task_execute(void)
{
	ssd1306_UpdateScreen();
}
