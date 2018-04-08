/*
 * font_5x8.h
 *
 *  Created on: Apr 10, 2018
 *      Author: brianvuong
 */

#ifndef FONTS_FONT_5X8_H_
#define FONTS_FONT_5X8_H_

#include "font.h"

#define FONT_5_BY_8_WIDTH_PX        5       // Define Font Width
#define FONT_5_BY_8_HEIGHT_PX       8       // Define Font Height
#define FONT_5_BY_8_ASCII_OFFSET    0

// Public Data
extern const uint8_t fontChars_5x8[][(FONT_5_BY_8_WIDTH_PX * FONT_5_BY_8_HEIGHT_PX) /8];

extern const Font_t Font_5x8;

#endif /* FONTS_FONT_5X8_H_ */
