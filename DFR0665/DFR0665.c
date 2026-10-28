#include <xc.h>
#include <stdbool.h>
#include "DFR0665.h"
#include "gfx.h"
#include "XPT2046.h"
#include "fonts.h"
#include <libpic30.h>


#define TFTWIDTH 240U  ///< max TFT width
#define TFTHEIGHT 320U ///< max TFT height



void DFR0665CalibrateTouchScreen(uint8_t mode)
{
    Rect tcoord1, tcoord2;
    
    // screen coord used for calibration
    Rect scoord1 = {.x=20,.y=50};
    Rect scoord2 = {.x=220,.y=270};
    
    // adapt to screen orientation
    uint16_t swap;
    if (mode==1||mode==3)
        {
        swap = scoord1.x;
        scoord1.x=scoord1.y;
        scoord1.y = swap;
        swap = scoord2.x;
        scoord2.x=scoord2.y;
        scoord2.y = swap;
    }
    
    Pen pen = {
      .strokeColor = 0x00FF0000,
      .fillColor = 0x00000000,
      .strokeWidth = 2,
      .font = & calibri_12ptFontInfo,
      .style = FILLSTROKE
    };
    clearScreen();
    setCursorPos(30, 150);
    writeStr("Procedure de calibration", pen);

    __delay_ms(2000UL);
    //drawRect(30, 150, 220, 130, pen);
    setCursorPos(30, 150);
    clearScreen();
    writeStr("Touchez la croix", pen);
    drawLine(scoord1.x-10, scoord1.y, scoord1.x+10, scoord1.y, pen);
    drawLine(scoord1.x, scoord1.y-10, scoord1.x, scoord1.y+10, pen);
    
    
    while (!(touchEvent==DOWN));
    IEC3bits.CNCIE = 0;     // disable touch interrupts
    tcoord1 = XPT2046_Read_XY();    
    touchEvent = NO;
    clearScreen();
    setCursorPos(30, 150);
    writeStr("Encore", pen);
    drawLine(scoord2.x-10, scoord2.y, scoord2.x+10, scoord2.y, pen);
    drawLine(scoord2.x, scoord2.y-10, scoord2.x, scoord2.y+10, pen);
    __delay_ms(1000);
    IFS3bits.CNCIF = 0;  // enable touch interrupts
    CNFCbits.CNFC0 = 0;
    IEC3bits.CNCIE = 1;
    
    while (!(touchEvent==DOWN));
    IEC3bits.CNCIE = 0; // disable touch interrupts
    touchFlag = false;
    tcoord2 = XPT2046_Read_XY();


    // estimate calibration values in Portrait base
    switch(mode){
        case 0:
            setXCalibration(tcoord1.x,scoord1.x,tcoord2.x,scoord2.x);
            setYCalibration(tcoord1.y,scoord1.y,tcoord2.y,scoord2.y);
            break;
        case 1: //90° counterclockwise : Ys=X    ,Xs=TFTWIDTH-Y
            setXCalibration(tcoord1.x,TFTWIDTH-scoord1.y,tcoord2.x,TFTWIDTH-scoord2.y);
            setYCalibration(tcoord1.y,scoord1.x,tcoord2.y,scoord2.x);
            break;
        case 2: //180° Ys=TFTHEIGHT-Y,Xs=TFTWIDTH-X
            setXCalibration(tcoord1.x,TFTWIDTH-scoord1.x,tcoord2.x,TFTWIDTH-scoord2.x);
            setYCalibration(tcoord1.y,TFTHEIGHT-scoord1.y,tcoord2.y,TFTHEIGHT-scoord2.y);
            break;
        case 3: // 90° clockwise : Ys=TFTHEIGHT-X, Xs=Y
            setXCalibration(tcoord1.x,scoord1.y,tcoord2.x,scoord2.y);
            setYCalibration(tcoord1.y,TFTHEIGHT-scoord1.x,tcoord2.y,TFTHEIGHT-scoord2.x);
            break;
        default:
            break;
    }
            
    // record calibration value in non volatile memory : not operational 
    // in prototype version probably due to pin AVDD not beeing connected ?
    storeCalibrationNVM();
    __delay_ms(1000);
    clearScreen();
    setCursorPos(60, 150);
    writeStr("Calibration enregistree !",pen);
    __delay_ms(1000);
   
    
    IFS3bits.CNCIF = 0;  // enable interrupt
    CNFCbits.CNFC0 = 0;
    IEC3bits.CNCIE = 1;

}




