/*
 * Graphics.h
 *
 *  Created on: Apr 6, 2018
 *      Author: brianvuong
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "SSD1306.h"
#include "font.h"

/*
 * Typedefs
 */
typedef struct
{
    Font_t  activeFont;
}GFX_S;

extern GFX_S GFX;

/*
 * Public Functions
 */
void Graphics_Init(void);

void Graphics_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

void Graphics_DrawCircle(uint8_t xCenter, uint8_t yCenter, uint8_t innerRadius, uint8_t outerRadius);
void Graphics_DrawCircleOutline(uint8_t xCenter, uint8_t yCenter, uint8_t outerRadius);

void Graphics_DrawChar(uint8_t x, uint8_t page, char charToDraw);   // TODO: Add font parameter
void Graphics_DrawString(uint8_t x, uint8_t pageNum, char *string);
/*
 * Private Inline Functions
 */
static inline void Graphics_DrawPixel(uint8_t xCoord, uint8_t yCoord)
{
    SSD1306_drawPixel(xCoord, yCoord);
}

#endif /* GRAPHICS_H_ */
