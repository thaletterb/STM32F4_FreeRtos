/*
 * I2C_Driver.c
 *
 *  Created on: Dec 8, 2017
 *      Author: Brian Vuong
 */

#include "I2C_Driver.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// Local Variables
static I2C_HandleTypeDef I2C_handle;

///////////////////
// Public Functions
///////////////////

/*
 * I2C_returnHandlePtr()
 *
 * Returns the pointer to the I2C handle
 *
 * TODO: Currently no guarantee that the handle has been Init'd
 */
I2C_HandleTypeDef *I2C_returnHandlePtr(void)
{
	return &I2C_handle;
}

/*
 * I2C_initPeripheral()
 *
 * Initializes I2C1 peripheral
 * PB8: SCL
 * PB9: SDA
 *
 * Need to also initialize clocks to GPIOB
 * and remap AF
 */
uint8_t I2C_initPeripheral(void)
{

	// Enable I2C Peripheral clock
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();

	I2C1->CR1 |= 0x8000;
	I2C1->CR1 &= (uint16_t) ~((uint16_t) 0x8000);

	// GPIO Init
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin 		= (GPIO_PIN_8 | GPIO_PIN_9);
	GPIO_InitStruct.Mode 		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed		= GPIO_SPEED_MEDIUM;
	GPIO_InitStruct.Alternate	= GPIO_AF4_I2C1;
	GPIO_InitStruct.Pull		= GPIO_NOPULL;	// TODO: Verify this

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// I2C Init
	//I2C_InitTypeDef I2C_InitStruct;

	I2C_handle.Init.AddressingMode 	= I2C_ADDRESSINGMODE_7BIT;
	I2C_handle.Init.OwnAddress1		= 0x00;		// Not relevant in master (?)
	I2C_handle.Init.DutyCycle		= I2C_DUTYCYCLE_16_9;
	I2C_handle.Init.ClockSpeed 		= 400000;	// (Hz)
	I2C_handle.Init.DualAddressMode	= I2C_DUALADDRESS_DISABLED;
	I2C_handle.Instance 			= I2C1;

	I2C_handle.Mode					= HAL_I2C_MODE_MASTER;   /*!< I2C communication is in Master Mode       */

	return (HAL_I2C_Init(&I2C_handle) == HAL_OK);
}


uint8_t I2C_transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return (HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size, Timeout) == HAL_OK);
}
