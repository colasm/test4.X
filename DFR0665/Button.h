/* 
 * File:   Button.h
 * Author: Maxime COLAS
 *
 * Created on 20 juillet 2025, 16:43
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "gfx.h"
#include "TouchScreenInterface.h"
#include <stdbool.h>

#define PADDING 2
#define MAXBUTTON 5

typedef enum{
    PUSH,
    TOGGLE,
}Mechanical;



typedef struct{
    Rect pos;
    Rect dim;
    char * onText;
    char * offText;
    Pen onPen;
    Pen offPen;
    Mechanical mech;
    void (*onClickCallback)(TouchEvent a, int16_t b);
}Button;

typedef struct{
    bool active;
    bool state;
    Button button;
}ButtonTable;


int16_t addButton(Button * bt,bool state);
void adaptButton(Button *bt);
int16_t registerButton(Button * bt,bool state);
void unRegisterButton(int16_t id);
void redrawButton(int16_t id);
void buttonsCallbackLooper(Rect pos);


#endif	/* BUTTON_H */

