/* 
 * File:   XPT2046ScreenInterface.h
 * Author: Maxime COLAS
 *
 * Created on July 19, 2025, 2:30 PM
 */

#ifndef TOUCHSCREENINTERFACE_H
#define	TOUCHSCREENINTERFACE_H

// Driver interface
typedef struct {
 uint16_t (*getScreenWidth)(void);
 uint16_t (*getScreenHeight)(void);
 uint8_t (*getScreenOrientation)(void);
}TouchScreenInterface;

typedef enum{ NO, DOWN, UP} TouchEvent;


extern TouchEvent touchEvent;

#endif	/* TOUCHSCREENINTERFACE_H */

