/* 
 * File:   gfx.h
 * Author: Maxime COLAS
 *
 * Created on 6 juillet 2025, 12:57
 */

#ifndef GFX_H
#define	GFX_H
#include <stdint.h>
#include "fonts.h"
#include "GFXDriverInterface.h"
#include "commonStructs.h"


typedef uint16_t RGB565;
typedef uint32_t RGB;

typedef enum{
        STROKE = 1,        
        FILL,
        FILLSTROKE
} PenStyle;

#define FILL_MASK    2
#define STROKE_MASK  1


typedef struct{
    RGB strokeColor;
    RGB fillColor;
    uint8_t strokeWidth;
    const FONT_INFO * font;
    PenStyle style;
} Pen;


extern Pen defaultPen;

/**
 * @brief Set the fill color of current Pen
 * 
 * Actually not used : futur feature
 * @param color
 */
void setCurrentPenfillColor(RGB color);


/**
 * @brief Set the stroke color of current Pen
 * 
 * Actually not used : futur feature
 * @param color
 */
void setCurrentPenstrokeColor(RGB color);


/**
 * @brief Set the width of current Pen
 *
 * Actually not used : futur feature
 * @param width
 */
void setCurrentPenstrokeWidth(uint8_t width);


void drawRect(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,Pen pencil);
void drawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,Pen pencil);
void setCursorPos(uint16_t x,uint16_t y);
Rect getStringBox(char * str,Pen pen);
void writeStr(char * str,Pen pen);
void setGFXDriver(const GFXDriver * pDriver);
void clearScreen(void);

#endif	/* GFX_H */

