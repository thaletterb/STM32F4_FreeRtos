/*
 * font.h
 *
 *  Created on: Apr 10, 2018
 *      Author: brianvuong
 */

#ifndef FONTS_FONT_H_
#define FONTS_FONT_H_

#include "stdint.h"

typedef struct Font_t
{
    uint8_t         widthPx;
    uint8_t         heightPx;
    const uint8_t   (*fontChars)[5];
}Font_t;

#include "font_5x8.h"

#endif /* FONTS_FONT_H_ */
