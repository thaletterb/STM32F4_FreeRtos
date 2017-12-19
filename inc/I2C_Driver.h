/*
 * I2C_Driver.h
 *
 *  Created on: Dec 8, 2017
 *      Author: brianvuong
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// Typedefs

// Macros

// Public Functions

I2C_HandleTypeDef *I2C_returnHandlePtr(void);
uint8_t I2C_initPeripheral(void);
uint8_t I2C_transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);


#endif /* I2C_DRIVER_H_ */
