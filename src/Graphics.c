/*
 * Graphics.c
 *
 *  Created on: Apr 6, 2018
 *      Author: brianvuong
 */

#include "Graphics.h"

/*
 * Macros
 */
#define ABS(a, b)   ((a>b) ? (a-b) : (b-a))

GFX_S GFX;

/*
 * Predeclare private functions
 */
static void graphics_drawXLine(uint8_t x1, uint8_t x2, uint8_t y);
static void graphics_drawYLine(uint8_t x, uint8_t y1, uint8_t y2);

/*
 * Public Functions
 */
void Graphics_Init(void)
{
    memset(&GFX, 0, sizeof(GFX));

    GFX.activeFont = Font_5x8;
}

// Draws a line from (x1, y1) to (x2, y2) by implementing Bresenham line algorithm
// http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
void Graphics_DrawLine(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
    uint8_t delta_x = ABS(x1, x2);
    uint8_t delta_y = ABS(y2, y1);

    uint8_t swap_x = ((x1<x2) ? 1 : -1);
    uint8_t swap_y = ((y1<y2) ? 1 : -1);

    uint8_t err = ((delta_x>delta_y) ? delta_x : -delta_y)/2;
    uint8_t e2;

    for(;;)
    {
        Graphics_DrawPixel(x1, y1);
        if (x1==x2 && y1==y2)
        {
            break;
        }

        e2 = err;

        if (e2 >-delta_x)
        {
            err -= delta_y;
            x1 += swap_x;
        }
        if (e2 < delta_y)
        {
            err += delta_x;
            y1 += swap_y;
        }
    }
}

// Draws a circle centered at (x,y) and filled between inner and outer radii
void Graphics_DrawCircle(uint8_t xCenter, uint8_t yCenter, uint8_t innerRadius, uint8_t outerRadius)
{
    int xo = outerRadius;
    int xi = innerRadius;
    int y = 0;
    int erro = 1 - xo;
    int erri = 1 - xi;

    while(xo >= y)
    {
        graphics_drawXLine(xCenter + xi, xCenter + xo, yCenter + y);
        graphics_drawYLine(xCenter + y,  yCenter + xi, yCenter + xo);
        graphics_drawXLine(xCenter - xo, xCenter - xi, yCenter + y);
        graphics_drawYLine(xCenter - y,  yCenter + xi, yCenter + xo);
        graphics_drawXLine(xCenter - xo, xCenter - xi, yCenter - y);
        graphics_drawYLine(xCenter - y,  yCenter - xo, yCenter - xi);
        graphics_drawXLine(xCenter + xi, xCenter + xo, yCenter - y);
        graphics_drawYLine(xCenter + y,  yCenter - xo, yCenter - xi);

        y++;

        if (erro < 0) {
            erro += 2 * y + 1;
        } else {
            xo--;
            erro += 2 * (y - xo + 1);
        }

        if (y > innerRadius) {
            xi = y;
        } else {
            if (erri < 0) {
                erri += 2 * y + 1;
            } else {
                xi--;
                erri += 2 * (y - xi + 1);
            }
        }

    }
}

// Draws a one pixel thick circle centered at (xCenter, yCenter)
void Graphics_DrawCircleOutline(uint8_t xCenter, uint8_t yCenter, uint8_t outerRadius)
{
    Graphics_DrawCircle(xCenter, yCenter, outerRadius, outerRadius);
}

// Draws a char at X inside of pageNum
void Graphics_DrawChar(uint8_t x, uint8_t pageNum, char charToDraw)
{
    uint8_t *buffer = SSD1306_getDisplayBufferHandle();
    uint16_t whichByteInBuffer = x + ((pageNum) * 128);

    for(uint8_t widthIndex = 0; widthIndex < GFX.activeFont.widthPx; widthIndex++)
    {
        buffer[whichByteInBuffer + widthIndex] = GFX.activeFont.fontChars[charToDraw][widthIndex];
    }
}

void Graphics_DrawString(uint8_t x, uint8_t pageNum, char *string)
{
    uint8_t stringIndex = 0;

    while(string[stringIndex] != '\0')
    {
        Graphics_DrawChar(x+(FONT_5_BY_8_WIDTH_PX*stringIndex), pageNum, string[stringIndex++]);
    }
}


/*
 * Private Functions
 */
// @brief: draws a horizontal line between x1 and x2 at y
static void graphics_drawXLine(uint8_t x1, uint8_t x2, uint8_t y)
{
    while(x1<=x2)
    {
        Graphics_DrawPixel(x1++, y);
    }
}

// @brief: draws a vertical line between y1 and y2 at x
static void graphics_drawYLine(uint8_t x, uint8_t y1, uint8_t y2)
{
    while(y1<=y2)
    {
        Graphics_DrawPixel(x, y1++);
    }
}
