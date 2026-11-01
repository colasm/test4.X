#include "DFR0665/Button.h"
#include "DFR0665/XPT2046.h"
#include <xc.h>
#include <stdio.h>
#include <libpic30.h>

void onDecClick(TouchEvent te,int16_t src);
void onIncClick(TouchEvent te,int16_t src);
void onModeClick(TouchEvent te,int16_t src);

volatile int16_t audioMode; // id of the currently selected mode radio button (Passthrough/Sinus/Filtre)

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

const Pen groupPen =  {.strokeColor = 0xFFFFFF,
            .fillColor = 0x00000000,
            .strokeWidth= 1,
            .font = & calibri_12ptFontInfo,
            .style = STROKE
};


Button dec = {.dim = {.x=80,.y=40},
              .mech = PUSH,
              .offText = "Minus",
              .onText = "Minus",
              .onPen = btOnPen,
              .offPen = btOffPen,
              .pos = {.x=75,.y=70},
              .onClickCallback = &onDecClick
               };

Button inc = {.dim = {.x=80,.y=40},
              .mech = PUSH,
              .offText = "Plus",
              .onText = "Plus",
              .onPen = btOnPen,
              .offPen = btOffPen,
              .pos = {.x=75,.y=170},
              .onClickCallback = &onIncClick
               };

Button passthroughBt = {.dim = {.x=60,.y=36},
              .mech = RADIO,
              .group = 0,
              .offText = "Passthrough",
              .onText = "Passthrough",
              .onPen = btOnPen,
              .offPen = btOffPen,
              .pos = {.x=225,.y=78},
              .onClickCallback = &onModeClick
               };

Button sineBt = {.dim = {.x=60,.y=36},
              .mech = RADIO,
              .group = 0,
              .offText = "Sinus",
              .onText = "Sinus",
              .onPen = btOnPen,
              .offPen = btOffPen,
              .pos = {.x=225,.y=120},
              .onClickCallback = &onModeClick
               };

Button filterBt = {.dim = {.x=60,.y=36},
              .mech = RADIO,
              .group = 0,
              .offText = "Filter",
              .onText = "Filter",
              .onPen = btOnPen,
              .offPen = btOffPen,
              .pos = {.x=225,.y=162},
              .onClickCallback = &onModeClick
               };

int16_t volume = 20;

void onDecClick(TouchEvent event,int16_t src){
char buff[5];
if(volume>0)
    volume --;
sprintf(buff,"%d",volume);
drawRect(75,100,115,130,defaultPen);
Rect dimText = getStringBox(buff,textPen);
setCursorPos(75,115+dimText.y/2+4);
writeStr(buff,textPen);
}

void onIncClick(TouchEvent event,int16_t src){
char buff[5];
if(volume<31)
    volume ++;

sprintf(buff,"%d",volume);
drawRect(75,100,115,130,defaultPen);
Rect dimText = getStringBox(buff,textPen);
setCursorPos(75,115+dimText.y/2+4);
writeStr(buff,textPen);
}

void onModeClick(TouchEvent event,int16_t src){
    audioMode = src;
}






void appMain(){
    Rect coord;

    // size the 3 radio buttons identically, wide enough for the longest label
    Rect pBox = getStringBox(passthroughBt.onText,passthroughBt.onPen);
    Rect sBox = getStringBox(sineBt.onText,sineBt.onPen);
    Rect fBox = getStringBox(filterBt.onText,filterBt.onPen);
    uint16_t modeBtWidth = pBox.x;
    if(sBox.x>modeBtWidth) modeBtWidth = sBox.x;
    if(fBox.x>modeBtWidth) modeBtWidth = fBox.x;
    modeBtWidth += 2*PADDING;
    passthroughBt.dim.x = modeBtWidth;
    sineBt.dim.x = modeBtWidth;
    filterBt.dim.x = modeBtWidth;

    // frame the 3 radio buttons together to show they form one group
    const uint16_t groupMargin = 8;
    uint16_t groupX1 = passthroughBt.pos.x - modeBtWidth/2 - groupMargin;
    uint16_t groupX2 = passthroughBt.pos.x + modeBtWidth/2 + groupMargin;
    uint16_t groupY1 = passthroughBt.pos.y - passthroughBt.dim.y/2 - groupMargin;
    uint16_t groupY2 = filterBt.pos.y + filterBt.dim.y/2 + groupMargin;
    drawRect(groupX1,groupY1,groupX2,groupY2,groupPen);

    addButton(& dec,false);
    addButton(& inc,false);
    audioMode = addButton(& passthroughBt,true);
    addButton(& sineBt,false);
    addButton(& filterBt,false);

    
    
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