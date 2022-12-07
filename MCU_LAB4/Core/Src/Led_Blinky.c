/*
 * Led_Blinky.c
 *
 *  Created on: Dec 7, 2022
 *      Author: LUUVINHLOI
 */

#include "main.h"
#include "Led_Blinky.h"

void Led_Red(void) {
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

void Led_Yellow(void) {
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}

void Led_Blue(void) {
	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
}

void Led_Green(void) {
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}
