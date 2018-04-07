/*
 * SSD1306.c
 *
 *  Created on: Dec 10, 2017
 *      Author: Brian Vuong
 */

#include "SSD1306.h"
#include "I2C_Driver.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 * Private Global Variables
 */
static uint8_t SSD1306_displayBuffer[SSD1306_DISPLAY_BUFFER_SIZE_BYTES] = {

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // Page 0 (Top Most)
    0x80,0xC0,0x40,0x60,0x20,0x20,0x20,0x20,0x60,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0xF8,0x7C,0x86,
    0xF6,0x1E,0x04,0x0C,0xF8,0xE0,0xC0,0x30,0x88,0xCC,0x24,0x26,0x06,0x06,0xFC,0xF0,
    0x00,0x00,0x80,0xC0,0x80,0xC0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x60,0xFC,0x0C,0x7A,0x0F,0x81,0x03,0x02,0x06,0x0C,0x1C,
    0x07,0x00,0xC0,0x43,0x01,0x01,0x03,0x04,0x00,0x21,0x3F,0x1E,0x18,0x08,0x0C,0x08,
    0x0C,0xC8,0x18,0x18,0x70,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x80,0xC0,0x60,0xE0,0xC0,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x3C,0xF6,0xC2,0xA3,0x61,0xC1,0xC1,0x81,0x03,0x03,0x06,0x1F,0x3A,0x21,
    0x81,0x00,0x00,0x00,0x07,0x7F,0xFF,0x1E,0x02,0x00,0x00,0xE0,0x70,0x3E,0x0F,0x06,
    0x83,0x81,0xC1,0x60,0x60,0x70,0x78,0x39,0x27,0x73,0x20,0x60,0xC0,0xC0,0x00,0x00,

    0x00,0x00,0x00,0x00,0x80,0xC0,0x31,0x1B,0x0E,0x0C,0x1C,0x00,0x18,0x10,0x30,0x30,
    0x00,0x00,0x83,0xFE,0x3C,0x18,0x18,0x70,0xE0,0x30,0x00,0x00,0x18,0x00,0x00,0x08,
    0x08,0x00,0x0C,0x4E,0xDB,0x30,0x30,0x60,0xC0,0x80,0x00,0x00,0x00,0xC0,0xA0,0x98,
    0xA4,0xB4,0xAC,0x08,0x30,0x30,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xD0,0x38,
    0x0E,0x0E,0x07,0x07,0x00,0x00,0x00,0x0F,0x07,0x02,0x33,0x99,0xEF,0x0B,0x00,0x00,
    0x00,0x80,0xC0,0x60,0x30,0x19,0x0B,0x0B,0x0E,0x06,0x0E,0x44,0x06,0x06,0x06,0x86,
    0x84,0x8C,0xEC,0xF8,0x0C,0xE6,0xB7,0x86,0x04,0x0C,0x79,0xF8,0x88,0x0C,0x02,0x86,
    0x05,0x00,0x00,0x02,0xC2,0xE1,0xE1,0xE1,0xA3,0xB2,0x30,0x10,0x18,0x1F,0x07,0x00,

    0x00,0x00,0x00,0x00,0x0F,0x39,0x70,0x60,0xC0,0xC0,0xC0,0xE0,0x00,0x00,0x80,0x10,
    0x18,0x0C,0x06,0x07,0x06,0x04,0x7E,0x67,0x07,0x06,0x04,0x0C,0x0C,0x0C,0x48,0x40,
    0xE0,0x72,0x60,0x62,0x23,0x31,0x30,0x18,0x0F,0x03,0x00,0x00,0x01,0x07,0x01,0x01,
    0x00,0x00,0x01,0x03,0x06,0x9C,0x60,0x01,0x06,0xDC,0x70,0x00,0x00,0xED,0xBF,0xE0,
    0xE0,0xF0,0x70,0x68,0x38,0x1C,0x16,0x0C,0x0D,0x06,0x02,0x03,0x00,0x00,0x00,0x00,
    0x0E,0x1F,0x18,0x30,0x31,0x33,0xF2,0x7A,0x19,0x1C,0x0C,0x8C,0x86,0x02,0x21,0x01,
    0x00,0x90,0x19,0x07,0x06,0x9C,0xF8,0x18,0x18,0x1C,0x1E,0x33,0xE1,0x81,0x01,0x03,
    0x07,0x06,0x0E,0x0C,0x18,0x70,0xE0,0x80,0x80,0x81,0x83,0x83,0xC6,0x7E,0x38,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x39,0x30,0x30,0x21,0x30,
    0x30,0x30,0x30,0x20,0x30,0x1E,0x1E,0x3E,0xF8,0xF0,0xF4,0xF4,0xF4,0xF6,0xB0,0x1C,
    0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0xE2,0x5F,0x9A,0xAA,0x5F,0xC1,0xF8,0xFB,0x4E,0x23,0x8F,
    0xC3,0x60,0x30,0x90,0xD8,0xC8,0xEC,0xA4,0xE4,0xA6,0xE4,0x8C,0x8C,0x98,0x30,0xE0,
    0x00,0x00,0x00,0x00,0x00,0x0F,0x1C,0x30,0x31,0x13,0x19,0x0D,0xAC,0xFE,0x07,0x01,
    0x01,0x00,0x00,0x00,0xE0,0xFE,0xED,0x80,0x00,0x00,0x00,0x00,0x00,0x07,0x7F,0xFE,
    0x18,0x18,0x30,0x30,0x20,0x30,0x19,0x1F,0x05,0x01,0x01,0x01,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x80,0xC0,0x60,0x60,0x20,0x30,0x20,0x20,0x30,0x20,0x30,0x20,0x20,
    0x20,0x60,0x60,0xC0,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x00,0xEB,0x7F,0x00,
    0x00,0x80,0xC0,0x40,0x60,0x20,0x90,0x18,0x08,0x08,0x88,0xCC,0x6C,0x34,0x1C,0x08,
    0x00,0x00,0x00,0x00,0xEC,0xBF,0x01,0xF1,0xFF,0xFE,0xFF,0xBB,0x7E,0x1E,0x0E,0x05,
    0x02,0x01,0x01,0x01,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x03,0x07,0x07,
    0x00,0x00,0x00,0x70,0xE0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x04,
    0x04,0x06,0x02,0x03,0x00,0x0F,0xFF,0x9F,0x3F,0xFE,0x0C,0x06,0x02,0x02,0x03,0x01,
    0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x03,0x01,0x03,0x03,0x03,0x03,0x03,0x02,0x06,0x06,0x06,0x0C,0x18,0x18,0x70,
    0xEC,0x9E,0x9E,0x7C,0xF9,0xB3,0xC6,0x8C,0x38,0xE0,0xFF,0x81,0xF8,0x7F,0x98,0xC6,
    0xE3,0x78,0x3C,0x1C,0x8E,0xC3,0x61,0x18,0x0C,0x03,0x01,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x05,0x1F,0xFC,0xFF,0xCF,0x39,0x07,0x01,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x1F,0x78,0xC1,0xC1,0x01,0x0B,0x33,0x12,0x42,0x42,0x46,0xC6,
    0xC6,0x84,0x0C,0x18,0x30,0xE0,0xD9,0xFB,0xFA,0xEF,0x60,0x30,0x10,0x18,0x18,0x8C,
    0x0C,0xE4,0x06,0x06,0x03,0xE3,0x3F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,        // Page 7 (bottom)
    0x00,0x00,0x03,0x03,0x0F,0x0D,0x1B,0x1B,0x33,0x32,0x37,0x2F,0x33,0x32,0x13,0x11,
    0x18,0x0C,0x06,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x06,0x0C,0x08,0x18,0x30,0x30,
    0x60,0x60,0x61,0xE6,0xEC,0x7E,0x7F,0x47,0x9B,0xCC,0x84,0x86,0xC2,0x43,0x41,0x61,
    0x20,0x30,0x1C,0x06,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};


/*
 * Private Functions
 */



/*
 * Brief: Draws a bitmap to the buffer starting at (x,y)
 */
static void ssd1306_drawBitmap(uint8_t *buffer, uint8_t *bitmap, uint8_t x, uint8_t y, uint8_t bitmap_width, uint8_t bitmap_height)
{
	for(uint8_t index=0; index<bitmap_height; index++)
	{
		ssd1306_drawPixel(buffer, x, y+index);
	}
}

/*
 * Public Functions
 */

// Returns a handle (pointer) to the display buffer
uint8_t *SSD1306_getDisplayBufferHandle(void)
{
    return SSD1306_displayBuffer;
}

// Brief: Sends the contents of the display buffer to the display
void SSD1306_drawDataBuffer(uint8_t *data, uint16_t dataLength)
{
	SSD1306_sendCommand(SSD1306_CMD_SET_COLUMN_ADDRESS);
	SSD1306_sendCommand(SSD1306_CMD_SET_COLUMN_START_ADDRESS);
	SSD1306_sendCommand(SSD1306_CMD_SET_COLUMN_END_ADDRESS);

	SSD1306_sendCommand(SSD1306_CMD_SET_PAGE_ADDRESS);
	SSD1306_sendCommand(SSD1306_CMD_SET_PAGE_START_ADDRESS);
	SSD1306_sendCommand(SSD1306_CMD_SET_PAGE_END_ADDRESS);

	SSD1306_sendData(data, dataLength);
}

/*
 * SSD1306_Init
 */
void SSD1306_init(void)
{
    // Sends the init commands to the display
    SSD1306_displayOff();

    SSD1306_sendCommand(SSD1306_CMD_LOW_COLUMN_START_ADDR | SSD1306_CMD_LOW_COLUMN_START_VALUE);
    SSD1306_sendCommand(SSD1306_CMD_HI_COLUMN_START_ADDR | SSD1306_CMD_HI_COLUMN_START_VALUE);

    SSD1306_sendCommand(SSD1306_CMD_SET_DISPLAY_START_LINE | SSD1306_CMD_SET_DISPLAY_START_VALUE);

    SSD1306_sendCommand(SSD1306_CMD_SET_CONTRAST);
    SSD1306_sendCommand(SSD1306_CMD_SET_CONTRAST_VAL);

    SSD1306_sendCommand(SSD1306_CMD_SEG_REMAP);
    SSD1306_sendCommand(SSD1306_CMD_COM_SCAN_DEC);

    SSD1306_sendCommand(SSD1306_CMD_NORM_DISPLAY);

    SSD1306_sendCommand(SSD1306_CMD_DISPLAY_ALL_ON_RESUME);

    SSD1306_sendCommand(SSD1306_CMD_SET_MUX_RATIO);
    SSD1306_sendCommand(SSD1306_CMD_SET_MUX_RATIO_VALUE);

    SSD1306_sendCommand(SSD1306_CMD_SET_DISPLAY_OFFSET);
    SSD1306_sendCommand(SSD1306_CMD_SET_DISPLAY_OFFSET_VAL);

    SSD1306_sendCommand(SSD1306_CMD_SET_DISPLAY_CLK_DIV);
    SSD1306_sendCommand(SSD1306_CMD_SET_DISPLAY_CLK_DIV_VAL);

    SSD1306_sendCommand(SSD1306_CMD_SET_PRECHARGE_PERIOD);
    SSD1306_sendCommand(SSD1306_CMD_SET_PRECHARGE_PERIOD_VAL);

    SSD1306_sendCommand(SSD1306_CMD_SET_COM_PINS_CONFIG);
    SSD1306_sendCommand(SSD1306_CMD_SET_COM_PINS_CONFIG_VAL);

    SSD1306_sendCommand(SSD1306_CMD_SET_VCOM_REG_OUTPUT);
    SSD1306_sendCommand(SSD1306_CMD_SET_VCOM_REG_OUTPUT_VAL);

    SSD1306_sendCommand(SSD1306_CMD_SET_MEMORY_ADDRESS_MODE);
    SSD1306_sendCommand(SSD1306_CMD_SET_MEMORY_ADDRESS_MODE_HORIZONTAL);

    SSD1306_sendCommand(SSD1306_CMD_SET_DISPLAY_START_LINE | SSD1306_CMD_SET_DISPLAY_START_LINE_0);

    SSD1306_sendCommand(SSD1306_CMD_SET_CHARGE_PUMP);
    SSD1306_sendCommand(SSD1306_CMD_SET_CHARGE_PUMP_SETTING);

    SSD1306_sendCommand(SSD1306_CMD_TURN_ON_REGULAR_MODE);

    SSD1306_displayOn();
}

// Brief: Draws a pixel to the buffer at coordinate (x,y)
void SSD1306_drawPixel(uint8_t xCoord, uint8_t yCoord)
{
    uint8_t *buffer = SSD1306_getDisplayBufferHandle();
    uint8_t local_x, local_y;

    local_x = SSD1306_WIDTH_PX - xCoord - 1;
    local_y = SSD1306_HEIGHT_PX - yCoord -1;

    buffer[local_x+ (local_y/8)*SSD1306_WIDTH_PX] |=  (1 << (local_y&7));
}
