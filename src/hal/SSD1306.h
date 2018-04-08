/*
 * I2C_Driver.h
 *
 *  Created on: Dec 8, 2017
 *      Author: brianvuong
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include "SSD1306Config.h"

/*
 * Typedefs
 */

/*
 * Macros
 */
#define SSD1306_CMD_DISPLAY_OFF                         0xAE
#define SSD1306_CMD_DISPLAY_ON                          0xAF

#define SSD1306_CMD_SET_CONTRAST                        0x81    // Set Contrast 0x81
#define SSD1306_CMD_SET_CONTRAST_VAL                    0xCF    // Set Contrast Value (0x00 - 0xFF)

#define SSD1306_CMD_SEG_NO_REMAP                        0xA0    // Seg-remap
#define SSD1306_CMD_SEG_REMAP                           0xA1

#define SSD1306_CMD_COM_SCAN_DEC                        0xC8    // COM scan direction descending
#define SSD1306_CMD_COM_SCAN_ASC                        0xC0    // COM scan direction ascending

#define SSD1306_CMD_NORM_DISPLAY                        0xA6
#define SSD1306_CMD_INVERT_DISPLAY                      0xA7

#define SSD1306_CMD_LOW_COLUMN_START_ADDR               0x00
#define SSD1306_CMD_LOW_COLUMN_START_VALUE              0x00
#define SSD1306_CMD_HI_COLUMN_START_ADDR                0x10
#define SSD1306_CMD_HI_COLUMN_START_VALUE               0x00

#define SSD1306_CMD_SET_DISPLAY_START_LINE              0x40
#define SSD1306_CMD_SET_DISPLAY_START_VALUE             0x00    // Range between 0-63 decimal

#define SSD1306_CMD_DISPLAY_ALL_ON_RESUME               0xA4

#define SSD1306_CMD_SET_MUX_RATIO                       0xA8
#define SSD1306_CMD_SET_MUX_RATIO_VALUE                 0x3F

#define SSD1306_CMD_SET_DISPLAY_OFFSET                  0xD3
#define SSD1306_CMD_SET_DISPLAY_OFFSET_VAL              0x00

#define SSD1306_CMD_SET_DISPLAY_CLK_DIV                 0xD5
#define SSD1306_CMD_SET_DISPLAY_CLK_DIV_VAL             0x80

#define SSD1306_CMD_SET_PRECHARGE_PERIOD                0xD9
#define SSD1306_CMD_SET_PRECHARGE_PERIOD_VAL            0xF1

#define SSD1306_CMD_SET_COM_PINS_CONFIG                 0xDA
#define SSD1306_CMD_SET_COM_PINS_CONFIG_VAL             0x12

#define SSD1306_CMD_SET_VCOM_REG_OUTPUT                 0xDB
#define SSD1306_CMD_SET_VCOM_REG_OUTPUT_VAL             0x40

#define SSD1306_CMD_SET_MEMORY_ADDRESS_MODE             0x20
#define SSD1306_CMD_SET_MEMORY_ADDRESS_MODE_HORIZONTAL  0x00

#define SSD1306_CMD_SET_DISPLAY_START_LINE              0x40
#define SSD1306_CMD_SET_DISPLAY_START_LINE_0            0x00

#define SSD1306_CMD_SET_CHARGE_PUMP                     0x8D
#define SSD1306_CMD_SET_CHARGE_PUMP_SETTING             0x14

#define SSD1306_CMD_TURN_ON_ALL_PIXELS                  0xA5            
#define SSD1306_CMD_TURN_ON_REGULAR_MODE                0xA4            

#define SSD1306_CMD_SET_COLUMN_ADDRESS                  0x21    // Triple Byte Command
#define SSD1306_CMD_SET_COLUMN_START_ADDRESS            0x00    // 0
#define SSD1306_CMD_SET_COLUMN_END_ADDRESS              0x7F    // 127

#define SSD1306_CMD_SET_PAGE_ADDRESS                    0x22    // Triple Byte command
#define SSD1306_CMD_SET_PAGE_START_ADDRESS              0x00    // 0
#define SSD1306_CMD_SET_PAGE_END_ADDRESS                0x07    // 7

/*
 * Inline Functions
 */
static inline void SSD1306_displayOff(void)
{
    SSD1306_sendCommand(SSD1306_CMD_DISPLAY_OFF);
}

static inline void SSD1306_displayOn(void)
{
    SSD1306_sendCommand(SSD1306_CMD_DISPLAY_ON);
}

/*
 * Public Functions
 */
uint8_t *SSD1306_getDisplayBufferHandle(void);

// Initialization
void SSD1306_init(void);

// Configuration

// Runtime
void SSD1306_clearDataBuffer(void);

void SSD1306_drawDataBuffer(uint8_t *data, uint16_t dataLength);
void SSD1306_drawPixel(uint8_t xCoord, uint8_t yCoord);

#endif /* SSD1306_H_ */
