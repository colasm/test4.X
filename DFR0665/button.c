
#include <stddef.h>
#include <stdbool.h>
#include "gfx.h"
#include "Button.h"


static ButtonTable buttons[MAXBUTTON];

/**
 * @brief Draw a Button centered at pos 
 * @param str button text 
 * @param pos : center of button
 * @param dim : button size
 * @param pen : pointer to tab containing on and off pencils
 * @param onClickCallback
 */
int16_t addButton(Button * bt,bool state){
    int16_t id;
    adaptButton(bt);
    id=registerButton(bt,state);
    redrawButton(id);
    return id;
}


void adaptButton(Button *bt){
    
    Rect dimTextOn = getStringBox(bt->onText,bt->onPen);
    Rect dimTextOff = getStringBox(bt->offText,bt->offPen);

    bt->dim.x = (bt->dim.x<=dimTextOn.x+2*PADDING)?dimTextOn.x+2*PADDING:bt->dim.x;
    bt->dim.y = (bt->dim.y<=dimTextOn.y+2*PADDING)?dimTextOn.y+2*PADDING:bt->dim.y;
    bt->dim.x = (bt->dim.x<=dimTextOff.x+2*PADDING)?dimTextOff.x+2*PADDING:bt->dim.x;
    bt->dim.y = (bt->dim.y<=dimTextOff.y+2*PADDING)?dimTextOff.y+2*PADDING:bt->dim.y;
}

int16_t registerButton(Button * bt,bool state){
    int16_t id;
    for(id = 0; id<MAXBUTTON;id++)
    if(!buttons[id].active) break;

    if((id==(MAXBUTTON-1))&&buttons[id].active)
        return -1;
    
    buttons[id].active = true;
    buttons[id].state = state;
    buttons[id].button = *bt; 
    return id;
}


void unRegisterButton(int16_t id){
    buttons[id].active = false;
}




void redrawButton(int16_t id){
    uint16_t x1,x2,y1,y2;

    x1 = buttons[id].button.pos.x-buttons[id].button.dim.x/2;
    x2 = buttons[id].button.pos.x+buttons[id].button.dim.x/2;
    y1 = buttons[id].button.pos.y-buttons[id].button.dim.y/2;
    y2 = buttons[id].button.pos.y+buttons[id].button.dim.y/2;
    bool state = buttons[id].state;
    drawRect(x1,y1,x2,y2,state?buttons[id].button.onPen:buttons[id].button.offPen);
    
    Rect dimText = state?getStringBox(buttons[id].button.onText,buttons[id].button.onPen):getStringBox(buttons[id].button.offText,buttons[id].button.offPen);
    char * str = state?buttons[id].button.onText:buttons[id].button.offText;
    Pen pen = state?buttons[id].button.onPen:buttons[id].button.offPen;
    

    uint16_t x= buttons[id].button.pos.x-dimText.x/2;
    uint16_t y= buttons[id].button.pos.y+dimText.y/2;
   
    setCursorPos(x,y);
    writeStr(str,pen);
}

/**
 * @brief Exectute the callback of clicked button
 * 
 * If buttons overlap, the launched callback is that with lower id. 
 * @param pos : click coordinates
 */
void buttonsCallbackLooper(Rect pos){
    int16_t id;
    uint16_t x1,x2,y1,y2;
    
    for(id = 0; id<MAXBUTTON;id++){
        if(buttons[id].active){
            x1 = buttons[id].button.pos.x-buttons[id].button.dim.x/2;
            x2 = buttons[id].button.pos.x+buttons[id].button.dim.x/2;
            if((x1<=pos.x)&&(x2>=pos.x)){
                y1 = buttons[id].button.pos.y-buttons[id].button.dim.y/2;
                y2 = buttons[id].button.pos.y+buttons[id].button.dim.y/2;  
                if((y1<=pos.y)&&(y2>=pos.y)){
                    switch(buttons[id].button.mech){
                        case TOGGLE:
                            if(touchEvent == DOWN)
                            buttons[id].state = !buttons[id].state;
                            break;
                        case PUSH:
                            buttons[id].state = (touchEvent==DOWN);
                            break;
                        default:
                            break;
                    }
                    
                    if(buttons[id].state) buttons[id].button.onClickCallback(touchEvent,id);
                    redrawButton(id);
                    break;
                }
            }
            
        }
    }
    
}
