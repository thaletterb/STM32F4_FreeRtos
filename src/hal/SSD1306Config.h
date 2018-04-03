/*
 * SSD1306Config.h
 *
 *  Created on: Apr 3, 2018
 *      Author: brianvuong
 */

#ifndef HAL_SSD1306CONFIG_H_
#define HAL_SSD1306CONFIG_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "I2C_Driver.h"

/*
 * Macros
 */
#define SSD1306_7BIT_ADDR                               0x3C
#define SSD1306_8BIT_ADDR                               (SSD1306_7BIT_ADDR << 1)

#define SSD1306_WIDTH_PX                                128
#define SSD1306_HEIGHT_PX                               64
#define SSD1306_DISPLAY_BUFFER_SIZE_BYTES               (SSD1306_WIDTH_PX * SSD1306_HEIGHT_PX)/8    // Bytes

#define SSD1306_CMD_BYTE                                0x00
#define SSD1306_DATA_BYTE                               0x40

#define SSD1306_CMD_NUM_BYTES                           2

/*
 * Inline Functions
 */
static inline uint8_t SSD1306_sendCommand(const uint8_t command)
{
    uint8_t txBuf[SSD1306_CMD_NUM_BYTES] = { SSD1306_CMD_BYTE, command };

    return I2C_transmit_blocking(I2C_returnHandlePtr(), SSD1306_8BIT_ADDR, txBuf, SSD1306_CMD_NUM_BYTES, 1000); // TODO: Hacky use of handle!
}

static inline uint8_t SSD1306_sendData(const uint8_t *data, const uint16_t numDataBytes)
{
    uint8_t retCode;

    for(uint16_t index=0; index < numDataBytes; index++)
    {
        uint8_t txBuf[SSD1306_CMD_NUM_BYTES] = { SSD1306_DATA_BYTE, data[index] };

        retCode &= I2C_transmit_blocking(I2C_returnHandlePtr(), SSD1306_8BIT_ADDR, txBuf, SSD1306_CMD_NUM_BYTES, 1000);
    }

    return retCode;
}

#endif /* HAL_SSD1306CONFIG_H_ */
