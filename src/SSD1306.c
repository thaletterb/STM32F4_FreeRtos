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

// Private Functions

/*
 * Brief: Used to send command command followed by data byte to display
 */
static void ssd1306_sendCommand(I2C_HandleTypeDef *hi2c, uint8_t ssd1306_7bit_address, uint8_t command)
{
	const uint8_t commandByte 	= 0x00;
	uint8_t buffer[2] 			= { commandByte, command };
	I2C_transmit_blocking(hi2c, ((ssd1306_7bit_address) << 1), buffer, 2, 1000);
}

/*
 * Brief: Used to send data command followed by data byte to display
 */
static void ssd1306_sendData(I2C_HandleTypeDef *hi2c, uint8_t ssd1306_7bit_address, uint8_t *data, uint16_t dataLength)
{
	const uint8_t dataByte 		= 0x40;
	const uint16_t bufferSize 	= dataLength + 1;

	const uint8_t testByte		= 0xAA;

	for(uint16_t index=0; index < dataLength; index++)
	{
		uint8_t buffer[2] = { dataByte, data[index] };

		I2C_transmit_blocking(hi2c, (ssd1306_7bit_address << 1), buffer, 2, 1000);
	}
}

/*
 * Brief: Draws a pixel to the buffer at coordinate (x,y)
 */
static void ssd1306_drawPixel(uint8_t *buffer, uint8_t x, uint8_t y)
{
	uint8_t local_x, local_y;

	local_x = SSD1306_WIDTH_PX - x - 1;
	local_y = SSD1306_HEIGHT_PX - y -1;

	buffer[local_x+ (local_y/8)*SSD1306_WIDTH_PX] |=  (1 << (local_y&7));
}

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

// Public Functions
/*
 * Brief: Sends the contents of the display buffer to the display
 */
void SSD1306_writeDataBuffer(I2C_HandleTypeDef *hi2c, uint8_t slaveAddress, uint8_t *data, uint16_t dataLength)
{
	// TODO: Move this
	#define SSD1306_COLUMNADDR  0x21
	#define SSD1306_PAGEADDR    0x22
	#define SSD_DATA_BYTE       0x40

	ssd1306_sendCommand(hi2c, slaveAddress, SSD1306_COLUMNADDR);
	ssd1306_sendCommand(hi2c, slaveAddress, 0x00);            // Column Start address
	ssd1306_sendCommand(hi2c, slaveAddress, 127);             // Column end address

	ssd1306_sendCommand(hi2c, slaveAddress, SSD1306_PAGEADDR);
	ssd1306_sendCommand(hi2c, slaveAddress, 0x00);            // Page Start address
	ssd1306_sendCommand(hi2c, slaveAddress, 0x07);            // Page end address

	ssd1306_sendData(hi2c, slaveAddress, data, dataLength);
}

/*
 * SSD1306_Init
 */
void SSD1306_init(I2C_HandleTypeDef *hi2c, uint8_t ssd1306_slave_address)
{
// Sends the init commands to the display
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xAE);

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x00 | 0x0);      // low col = 0

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x10 | 0x0);      // hi col = 0
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x40 | 0x0);      // line #0

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x81);            // Set Contrast 0x81
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xCF);
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xA1);            // Segremap - 0xA1
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xC8);            // COMSCAN DEC 0xC8 C0
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xA6);            // Normal Display 0xA6 (Invert A7)

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xA4);            // DISPLAY ALL ON RESUME - 0xA4
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xA8);            // Set Multiplex 0xA8
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x3F);            // 1/64 Duty Cycle

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xD3);            // Set Display Offset 0xD3
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x0);             // no offset

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xD5);            // Set Display Clk Div 0xD5
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x80);            // Recommneded resistor ratio 0x80

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xD9);            // Set Precharge 0xd9
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xF1);

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xDA);            // Set COM Pins0xDA
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x12);

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xDB);            // Set VCOM Detect - 0xDB
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x40);

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x20);            // Set Memory Addressing Mode
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x00);            // 0x00 - Horizontal

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x40 | 0x0);      // Set start line at line 0 - 0x40

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x8D);            // Charge Pump -0x8D
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0x14);

    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xA4);            //--turn on all pixels - A5. Regular mode A4
    ssd1306_sendCommand(hi2c, ssd1306_slave_address, 0xAF);            //--turn on oled panel - AF

}
