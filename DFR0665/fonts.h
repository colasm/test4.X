/* 
 * File:   fonts.h
 * Author: Maxime COLAS
 *
 * Created on 4 juillet 2025, 16:07
 */

#ifndef FONTS_H
#define	FONTS_H

#include <stdint.h>


typedef struct {
    uint8_t  width;     // Largeur du caractère en pixels
    uint16_t   offset;    // Décalage dans le tableau des données bitmap
} FONT_CHAR_INFO;


typedef struct {
    const uint8_t charHeight;
    const uint8_t verticalInterCharSpace;
    const uint8_t startChar;
    const uint8_t endChar;
    const uint8_t horizontalInterCharSpace;
    const uint8_t spaceWidth;
    const FONT_CHAR_INFO * fontDescriptor;
    const uint8_t * font;
} FONT_INFO;

extern const FONT_INFO calibri_12ptFontInfo;

#endif	/* FONTS_H */

