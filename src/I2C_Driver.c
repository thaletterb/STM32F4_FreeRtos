/*
 * I2C_Driver.c
 *
 *  Created on: Dec 8, 2017
 *      Author: Brian Vuong
 */

#include "I2C_Driver.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 * I2C_initPeripheral()
 *
 * Initializes I2C1 peripheral
 */
void I2C_initPeripheral(void)
{
	// Enable I2C Peripheral clock
	__HAL_RCC_I2C1_CLK_ENABLE();

	// I2C Init
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.AddressingMode 	= I2C_ADDRESSINGMODE_7BIT;
	I2C_InitStruct.ClockSpeed 		= 400000;	// (Hz)
	I2C_InitStruct.DualAddressMode	= I2C_DUALADDRESS_DISABLED;

	//I2C handle
	I2C_HandleTypeDef I2C_handle;

	I2C_handle.Instance 			= I2C1;
	I2C_handle.Init 				= I2C_InitStruct;

	HAL_I2C_Init(&I2C_handle);
}
