/* 
 * File:   GFXDriverInterface.h
 * Author: Maxime COLAS
 *
 * Created on 13 juillet 2025, 20:52
 */

#ifndef GFXDRIVERINTERFACE_H
#define	GFXDRIVERINTERFACE_H

typedef uint32_t RGB;

// Driver interface
typedef struct {
 void (* fillAreaWithPixelsRGB)(uint16_t x, uint16_t y,uint16_t w,uint16_t h,RGB * data);
 void (* fillAreaWithColorRGB)(uint16_t x, uint16_t y,uint16_t w,uint16_t h,RGB color);
 void (*readAreaPixelsRGB)(uint16_t x1,uint16_t y1,uint16_t w,uint16_t h,RGB * buffer);
 uint16_t (*getScreenWidth)(void);
 uint16_t (*getScreenHeight)(void);
}GFXDriver;


#endif	/* GFXDRIVERINTERFACE_H */

