/*
 * u8g_arm.h
 *
 *  Created on: Dec 28, 2017
 *      Author: brianvuong
 */

#ifndef U8G_ARM_H_
#define U8G_ARM_H_


#include "u8g.h"
#include "stm32f4xx_hal.h"

// Macros
#define DATA_BUFFER_SIZE    1000
#define I2C_TIMEOUT         10000
#define DEVICE_ADDRESS      0x78    // Todo: Reuse address in SSD1306.h
#define I2C_HANDLER         hi2c1

extern I2C_HandleTypeDef    hi2c1;  // TODO: Use my handle

// Public Functions
uint8_t u8g_com_hw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);

#endif /* U8G_ARM_H_ */
