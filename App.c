#include "DFR0665/Button.h"
#include "DFR0665/XPT2046.h"
#include <xc.h>
#include <stdio.h>
#include <libpic30.h>

void onDecClick(TouchEvent te,int16_t src);
void onIncClick(TouchEvent te,int16_t src);

const Pen textPen =  {.strokeColor = 0xFFFFFF,
            .fillColor = 0x00FF00,
            .strokeWidth= 1,
            .font = & calibri_12ptFontInfo,
            .style = FILLSTROKE
};

const Pen btOnPen =  {.strokeColor = 0xFFFFFF,
            .fillColor = 0x00FF00,
            .strokeWidth= 1,
            .font = & calibri_12ptFontInfo,
            .style = FILLSTROKE
};

const Pen btOffPen =  {.strokeColor = 0xFFFFFF,
            .fillColor = 0x0000FF,
            .strokeWidth= 1,
            .font = & calibri_12ptFontInfo,
            .style = FILLSTROKE
};


Button dec = {.dim = {.x=80,.y=40},
              .mech = PUSH,
              .offText = "Moins",
              .onText = "Moins",
              .onPen = btOnPen,
              .offPen = btOffPen,
              .pos = {.x=120,.y=100},
              .onClickCallback = &onDecClick
               };

Button inc = {.dim = {.x=80,.y=40},
              .mech = PUSH,
              .offText = "Plus",
              .onText = "Plus",
              .onPen = btOnPen,
              .offPen = btOffPen,
              .pos = {.x=120,.y=200},
              .onClickCallback = &onIncClick
               };
int16_t volume = 20;

void onDecClick(TouchEvent event,int16_t src){
char buff[5];
if(volume>0)
    volume --;
sprintf(buff,"%d",volume);
drawRect(120,130,160,160,defaultPen);
setCursorPos(120,150);
writeStr(buff,textPen);
}

void onIncClick(TouchEvent event,int16_t src){
char buff[5];
if(volume<31)
    volume ++;

sprintf(buff,"%d",volume);
drawRect(120,130,160,160,defaultPen);
setCursorPos(120,150);
writeStr(buff,textPen);
}






void appMain(){
    Rect coord;
    addButton(& dec,false);
    addButton(& inc,false);

    
    
    while(1){
        while (!touchEvent);
        __delay_ms(1L);
        IEC3bits.CNCIE = 0;     // disable touch interrupts
        if(touchEvent==DOWN){
        coord = XPT2046_GetPos();
        }
        buttonsCallbackLooper(coord);
        touchEvent = NO;
        __delay_ms(10L);
        IFS3bits.CNCIF = 0;  // enable touch interrupts
        CNFCbits.CNFC0 = 0;
        IEC3bits.CNCIE = 1;
    }
}

        
        

/* uint16_t state=0xFFFF;
void debugSPI(){
    char strBuffer[30];
    static uint16_t lastState = 0;
    char * label[]={"FRMERR=%d","BUSY=%d","SPITUR=%d","SPIROV=%d","SPIRBE=%d"};
    int16_t index[]={12,11,8,6,5};
   
    while(1){
        state &=0b1100101100000;
        if((lastState^state)!=0)
        {
            //affichage sur changement uniquement
            clearScreen();
            for(int k=0;k<5;k++){
                setCursorPos(50, 12*k+30);
                sprintf(strBuffer, label[k],(state>>index[k])&1);
                writeStr(strBuffer,textPen);
            }   
            __delay_ms(20L);
        }
        lastState = state;
    }
}*/


/*void testCode(){
char strBuffer[20];
    Rect coord;
    Pen pen = {
      .strokeColor = 0x00FFFFFF,
      .fillColor = 0x00000000,
      .strokeWidth = 2,
      .font = & calibri_12ptFontInfo,
      .style = FILLSTROKE
    };
while (1) {
        if (touchEvent) {
            IEC3bits.CNCIE = 0; //TODO : disable for some time
            //coord = XPT2046_GetPos();
            __delay_ms(1L);
            coord = XPT2046_Read_XY();
            clearScreen();
            setCursorPos(50, 120);
            sprintf(strBuffer, "X = %d", coord.x);
            writeStr(strBuffer, pen);

            setCursorPos(50, 140);
            sprintf(strBuffer, "Y = %d", coord.y);
            writeStr(strBuffer, pen);
            touchEvent = NO;
            //        }
            __delay_ms(10L);
            IFS3bits.CNCIF = 0;
            CNFCbits.CNFC0 = 0;
            IEC3bits.CNCIE = 1;
         }

    }

}*/