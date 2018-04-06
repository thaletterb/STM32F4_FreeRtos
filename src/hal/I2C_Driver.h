/*
 * I2C_Driver.h
 *
 *  Created on: Dec 8, 2017
 *      Author: brianvuong
 *
 *  Notes: http://blog.atollic.com/device-driver-development-the-ultimate-guide-for-embedded-system-developers
 */

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 * Macros
 */

/*
 * Typedefs
 */
typedef struct I2C_device_t
{
    I2C_HandleTypeDef   *hi2c;
    uint16_t            deviceAddress;    // 7 bit slave
} I2C_device_t;


/*
 * Public Functions
 */
I2C_HandleTypeDef *I2C_returnHandlePtr(void);

// Initialization:
uint8_t I2C_initPeripheral_defaults(void);

// Configuration:

// Runtime control:
// TODO: Add non-blocking interrupt/DMA based versions!
uint8_t I2C_transmit_blocking(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
uint8_t I2C_receive_blocking(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

// Shutdown


#endif /* I2C_DRIVER_H_ */
