/*
 * GPIO_Driver.c
 *
 *  Created on: Dec 8, 2017
 *      Author: brianvuong
 */

#include "GPIO_Driver.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_initPeripheral(void)
{
	// Enable clock to GPIOD peripheral
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// GPIOD Configuration
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin 	= GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed 	= GPIO_SPEED_MEDIUM; //GPIO_Speed_50MHz;
	GPIO_InitStruct.Pull 	= GPIO_PULLUP; //GPIO_PuPd_UP;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
