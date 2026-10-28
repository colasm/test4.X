
#include <stdint.h>
#include "gfx.h"
#include "fonts.h"
#include <stdbool.h>
#include "GFXDriverInterface.h"

const GFXDriver * gfxDriver;

#define _swap_uint16_t(a, b)                                                    \
  do{                                                                            \
    uint16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }while(0)


static Rect coord = {.x=0,.y=0};

// used to clear screen
Pen defaultPen = {   
                .strokeColor=0x00000000,
                .fillColor=0x00000000,
                .strokeWidth=1,
                .style=FILLSTROKE};

static Pen currentPen = {
                .strokeColor=0x00000000,
                .fillColor=0x00000000,
                .strokeWidth=1,
                .style=FILLSTROKE};

void setCurrentPenFillColor(RGB color){
    currentPen.fillColor = color;    
}

void setCurrentPenStrokeColor(RGB color){
    currentPen.strokeColor = color;    
}


void setCurrentPenWidth(uint8_t width){
    currentPen.strokeWidth = width;
}




void drawRect(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,Pen pen){
    
        uint16_t absdx=x2>x1?x2-x1:x1-x2;
        uint16_t absdy=y2>y1?y2-y1:y1-y2;
        
    
      // horizontal or vertical line
        if(x1>x2) _swap_uint16_t(x1,x2);
        if(y1>y2) _swap_uint16_t(y1,y2);
        
        if(pen.style&FILL_MASK)
            gfxDriver->fillAreaWithColorRGB(x1,y1,absdx+1,absdy+1,pen.fillColor);
        if(pen.style&STROKE_MASK){
            drawLine(x1,y1,x1,y2,pen);
            drawLine(x2,y1,x2,y2,pen);
            drawLine(x1,y1,x2,y1,pen);
            drawLine(x1,y2,x2,y2,pen);
        }
        return; 
}



void drawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,Pen pencil){
    
        uint16_t absdx=x2>x1?x2-x1:x1-x2;
        uint16_t absdy=y2>y1?y2-y1:y1-y2;
        uint8_t XBoxDelta=0;
        uint8_t YBoxDelta=0;
        

        // if 1 pixel only
        if((absdx==0)&&(absdy==0)){
            XBoxDelta=pencil.strokeWidth-1;
            YBoxDelta=pencil.strokeWidth-1;
        }else{
            // else
            if(absdy>2*absdx){ //vertical like
                XBoxDelta=pencil.strokeWidth-1;
                YBoxDelta=0;
            }
            else if(absdx>2*absdy){ //horizontal like
                XBoxDelta=0;
                YBoxDelta=pencil.strokeWidth-1;
            }else{

             uint8_t dim = ((pencil.strokeWidth)*10)/15; 
             XBoxDelta=dim;
             YBoxDelta=dim;
            }
            }


       
    
      // horizontal or vertical line
    if(y1==y2||x1==x2){
        if(x1>x2){
            _swap_uint16_t(x1,x2);
            _swap_uint16_t(y1,y2);
        }  
        gfxDriver->fillAreaWithColorRGB(x1-XBoxDelta,y1-YBoxDelta,absdx+1+2*XBoxDelta,absdy+1+2*YBoxDelta,pencil.strokeColor);
        return;
    } 
    
    // apply bresenham algorithm
    
    bool highSlope = false;
    // first inverse x and y if slope>1
    if(absdy>absdx){
        highSlope = true;
        _swap_uint16_t(x1,y1);
        _swap_uint16_t(x2,y2);
    }
    // ensure draw from left to right or bottom to top if slope>1
    if(x1>x2){
        _swap_uint16_t(x1,x2);
        _swap_uint16_t(y1,y2);
    }
    
    int16_t dy=(((int16_t)y2)-((int16_t)y1));
    int16_t dx=(((int16_t)x2)-((int16_t)x1));
    
    int16_t dir = dy>0?1:-1;
    
    uint16_t y=y1;
    int16_t error = -dx;
    
    uint16_t index = x1;
    while(index<=x2){
        if(error>0){
            y+=dir;
            error-=2*dx;
        }
        error+= 2*dy*dir;
        if(highSlope)
            gfxDriver->fillAreaWithColorRGB(y-XBoxDelta,(index++)-YBoxDelta,1+2*XBoxDelta,1+2*YBoxDelta,pencil.strokeColor);
        else
            gfxDriver->fillAreaWithColorRGB((index++)-XBoxDelta,y-YBoxDelta,1+2*XBoxDelta,1+2*YBoxDelta,pencil.strokeColor);
    } 
}

void setCursorPos(uint16_t x,uint16_t y){
    coord.x = x;
    coord.y = y;
}



void _writeCharNext(char c,Pen pen){
    // get char width
    int16_t width = pen.font->fontDescriptor[((int16_t)(c-pen.font->startChar))].width;
    int16_t space = pen.font->horizontalInterCharSpace;
    int16_t spaceCharWidth = pen.font->spaceWidth;
    int16_t offset = pen.font->fontDescriptor[((int16_t)(c-pen.font->startChar))].offset;
    int16_t nByte = (width+7)/8;
    
    if(c==' '||width==0){
       coord.x+=(spaceCharWidth+space);
       return;
    }
    
    
    for(int16_t indexRow=pen.font->charHeight-1;indexRow>=0;indexRow--){
        int16_t offsetIn = offset+nByte*(pen.font->charHeight-1-indexRow);
        for (int16_t bitCol =0;bitCol<width;bitCol++){
            uint8_t ch = pen.font->font[offsetIn+bitCol/8];
            if((ch>>(7-(bitCol%8)))&1){
                    gfxDriver->fillAreaWithColorRGB(coord.x+bitCol,coord.y-indexRow,1,1,pen.strokeColor);
                }               
        }
    }
    
    coord.x+=(width+space);
  
}


Rect getStringBox(char * str,Pen pen){
    Rect box;
    box.y=pen.font->charHeight;
    box.x = 0;
    while(*str){
        if(*str==' ')
            box.x+=pen.font->spaceWidth;
        else
            box.x+=(pen.font->fontDescriptor[*(str)-pen.font->startChar].width+pen.font->horizontalInterCharSpace);
        str++;
    }
    box.x-=pen.font->horizontalInterCharSpace;
    return box;
}


void writeStr(char * str,Pen pen){
    while(*str!=0)
        _writeCharNext(* str++,pen);
}


void setGFXDriver(const GFXDriver * pDriver){
    gfxDriver = pDriver;
}

void clearScreen(void){
    drawRect(0,0,gfxDriver->getScreenWidth()-1,gfxDriver->getScreenHeight()-1,defaultPen);
}
