/*
 * I2C_Driver.h
 *
 *  Created on: Dec 8, 2017
 *      Author: brianvuong
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// Typedefs

// Macros
#define SSD1306_7BIT_ADDR	0x3C
#define SSD1306_WIDTH_PX	128
#define SSD1306_HEIGHT_PX	64

// Public Functions

void SSD1306_init(I2C_HandleTypeDef *hi2c, uint8_t ssd1306_slave_address);
void SSD1306_writeDataBuffer(I2C_HandleTypeDef *hi2c, uint8_t ssd1306_slave_address, uint8_t *data, uint16_t dataLength);

#endif /* SSD1306_H_ */
