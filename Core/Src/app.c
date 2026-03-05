/*
 * app.c
 *
 *  Created on: 26/02/2026
 *      Author: kmd119, ldu60
 */

#include <stdbool.h>

#include "gpio.h"
#include "app.h"
#include "rgb.h"
#include "buttons.h"
#include "adc.h"


#define TICK_FREQUENCY_HZ 1000
#define BLINKY_FREQUENCY 2
#define BUTTON_FREQUENCY 50

#define BLINKY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BLINKY_FREQUENCY) // = 500 Ticks
#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_FREQUENCY) // = 20 Ticks

static uint32_t BlinkyNextRun = 0;
static uint32_t ButtonNextRun = 0;

static uint16_t raw_adc[2];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}
void blinky_task_execute()
{
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}

void button_task_execute(void)
{
	  if (buttons_checkButton(UP) == PUSHED)
	  {
		  rgb_led_toggle(RGB_UP);
	  }

	  if (buttons_checkButton(DOWN) == PUSHED)
	  {
		  rgb_led_toggle(RGB_DOWN);
	  }

	  if (buttons_checkButton(RIGHT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_RIGHT);
	  }

	  if (buttons_checkButton(LEFT) == PUSHED)
	  {
		  rgb_led_toggle(RGB_LEFT);
	  }

	  buttons_update();
}

void app_main(void)
{
	buttons_init();
	rgb_colour_all_on();

	BlinkyNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	ButtonNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	while (true)
	{
		  uint32_t ticks = HAL_GetTick();
		  if(ticks > BlinkyNextRun)
		  {
			  blinky_task_execute();
			  BlinkyNextRun += BLINKY_TASK_PERIOD_TICKS;
		  }

		  if (ticks > ButtonNextRun)
		  {
			  button_task_execute();
			  ButtonNextRun += BUTTON_TASK_PERIOD_TICKS;
		  }

		  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);

	}
}
