
#include "XPT2046.h"
#include "../mcc_generated_files/system/pins.h"
#include "../mcc_generated_files/spi_host/spi1.h"
#include "TouchScreenInterface.h"
#include <xc.h>
#include <libpic30.h>
#include <stdbool.h>


 #define X_DIR  0xD0  // get X values
 #define Y_DIR  0x90  // get Y values
 #define Z1_DIR 0xB1 // get Z1 value
 #define Z2_DIR 0xC1 // get Z2 value
 #define MSB_BIT_MASK    0x7F // Bit mask for MSB byte
 #define Z_THRESHOLD     400




bool touchFlag; //action semaphore for screen update.
TouchEvent touchEvent = NO;

const TouchScreenInterface * xptInterface;
unsigned int ScreenRotation = 1; //screen rotation
int TOUCH_FLAG = 0;
static Cal calibrationData;


/* *************************************************************************************
 * EMULATED EEPROM 
 * WARNING : Flash write operation should only be done with parcimony as 
 * it shorten the life of IC.
 * 
   ************************************************************************************* */

// Mainly declared to prevent linker to allocate other constants in this area
// non written memory should be read as 0xFFFFs
// Memory is reserved from 81F000 to 81FFFF (ie end of flash) as an exlusion area for ICD.
// It is supposed that calibration is always done in screen mode 0.
const __attribute__((space(prog),address(0x81F000),section("eeprom"))) int32_t nvmStorage[1024];//={0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};


void setXCalibration(int16_t X1Touch,int16_t X1Pixel,int16_t X2Touch,int16_t X2Pixel){
     calibrationData.dXTouch = (int32_t)X2Touch-X1Touch;
     calibrationData.dXPixel = (int32_t)X2Pixel-X1Pixel;
     calibrationData.XOffset = (int32_t)X1Pixel*X2Touch-(int32_t)X1Touch*X2Pixel;
 }
 
 void setYCalibration(uint16_t Y1Touch,uint16_t Y1Pixel,uint16_t Y2Touch,uint16_t Y2Pixel){
     calibrationData.dYTouch = (int32_t)Y2Touch-Y1Touch;
     calibrationData.dYPixel = (int32_t)Y2Pixel-Y1Pixel;
     calibrationData.YOffset = (int32_t)Y1Pixel*Y2Touch-(int32_t)Y1Touch*Y2Pixel;
 }
 
 /* void calibrationIsValid(){
     calibrationData.notValid = false;
 }*/
 
 /**
  * Store the calibration data in the flash.
  * @return storage did not complete due to Write error. 
  */
 bool storeCalibrationNVM(){
   
     // first erase page
     NVMADR = (uint32_t)nvmStorage ;
     NVMCON = 0x4003;
     NVMCONbits.WR = 1;
     while (NVMCONbits.WR == 1);
     NVMCONbits.WREN = 0;
     if(NVMCONbits.WRERR) {
         NVMCONbits.WRERR = 0;
         return false;
     }
         
    
    NVMADR = (uint32_t)nvmStorage;
    NVMDATA0 = calibrationData.XOffset;
    NVMDATA1 = calibrationData.dXTouch;
    NVMDATA2 = calibrationData.dXPixel;
    NVMDATA3 = 0xA5A5A5A5;      // validity word
    NVMCON = 0x4001;
    NVMCONbits.WR = 1;
    while (NVMCONbits.WR == 1);
    NVMCONbits.WREN = 0;
    if(NVMCONbits.WRERR) {
        NVMCONbits.WRERR = 0;
        return false;
    }
    
    NVMADR = (uint32_t)(nvmStorage+4) ;
    NVMDATA0 = calibrationData.YOffset;
    NVMDATA1 = calibrationData.dYTouch;
    NVMDATA2 = calibrationData.dYPixel;
    NVMDATA3 = 0xA5A5A5A5;      // validity word
    NVMCON = 0x4001;
    NVMCONbits.WR = 1;
    while (NVMCONbits.WR == 1);
    NVMCONbits.WREN = 0;
    if(NVMCONbits.WRERR) {
        NVMCONbits.WRERR = 0;
        return false;
    }
     return true;
     
 }
 
 /**
  * Get stored data calibration values.
  * @return false if no calibration data stored 
  */
 bool getCalibrationNVM(){
     if(nvmStorage[7]!=0xA5A5A5A5)
         return false;
     calibrationData.XOffset = nvmStorage[0];
     calibrationData.dXTouch = nvmStorage[1];
     calibrationData.dXPixel = nvmStorage[2];
     calibrationData.YOffset = nvmStorage[4];
     calibrationData.dYTouch = nvmStorage[5];
     calibrationData.dYPixel = nvmStorage[6];
     return true;
 }
 

 static uint8_t screenMode =0;
 
 void setScreenMode(uint8_t mode){
    screenMode = mode; 
 }
 
 uint8_t getScreenMode(){
     return screenMode;
 }
 


void IT_TOUCH_CallBack(void)
{
    touchEvent = IT_TOUCH_GetValue() == 1?UP:DOWN; 
    //touchFlag = true;
}


void _XPT2046Select(){
    // si pas déja sélectionné
    if(CS_TOUCH_GetValue()){
        SPI1_Close(); // arrêt SPI1
        SPI1_DisableAllCS();// déselection 
        SPI1_Open(XPT2046);  // ouverture SPI1 sur XPT2046
        CS_TOUCH_SetLow(); // sélection esclave  
    }
    
}


 void XPT2046Init(){
 }

 
 

 
 static inline Rect _toPixel(Rect touchPos){
     Rect coord;
     uint16_t swap;

          
     int32_t Xp=((touchPos.x*calibrationData.dXPixel + calibrationData.XOffset)/calibrationData.dXTouch);
     int32_t Yp=((touchPos.y*calibrationData.dYPixel + calibrationData.YOffset)/calibrationData.dYTouch);


          // apply coord transformation 
     switch(xptInterface->getScreenOrientation())
     {
        case 1 : //90° ccw
            swap=Yp;
            Yp = xptInterface->getScreenHeight()-Xp;
            Xp = Yp;
            break;
        case 2 : //180°
           Yp = xptInterface->getScreenWidth()-Yp;
           Xp = xptInterface->getScreenHeight()-Xp;
            
            break;
        case 3 : //90° cw
           swap=Yp;
           Yp = Xp;
           Xp = xptInterface->getScreenWidth()-swap;
            break;
         default:
             break;
     }
     
     // ensure limits
     Xp=Xp<0?0:Xp;
     Yp=Yp<0?0:Yp;
     Xp=(Xp>=xptInterface->getScreenWidth())?xptInterface->getScreenWidth()-1:Xp;
     Yp=(Yp>=xptInterface->getScreenHeight())?xptInterface->getScreenHeight()-1:Yp;
     coord.x=(uint16_t)Xp;
     coord.y=(uint16_t)Yp;
     
          
     
     return coord;
 }
 
uint16_t _Read_State(uint8_t direction){
   uint8_t MSB =0,LSB =0;
   SPI1_Host_ByteWrite(direction); // send command byte twice to dump first reading
   MSB = SPI1_ByteRead();
   LSB = SPI1_ByteRead();
   return (((MSB & MSB_BIT_MASK) << 8)+ LSB) >> 3;
}


Rect XPT2046_GetPos(){
    Rect unCalPos = XPT2046_Read_XY();
    
    return(_toPixel(unCalPos));
}



Rect XPT2046_Read_XY()  {     // read 12 bit data from SPI bus after sending a command byte
 
   Rect coord;
   _XPT2046Select();
   __delay_us(10UL);
   coord.x = _Read_State(X_DIR);
   coord.y = _Read_State(Y_DIR);
   
   return coord;
   
  }




CoordXYZ XPT2046_Read_XYZ()  {  // read 12 bit data from SPI bus after sending a command byte for X,Y,Z1&Z2 measurements
   
  CoordXYZ coord; 
  uint16_t resultz1, resultz2;
  _XPT2046Select();
   __delay_us(20UL);     
   /////////////////////Gather Z pressure readings////////////////////////////////////
   resultz1 = _Read_State(Z1_DIR);
   resultz2 = _Read_State(Z2_DIR);
   coord.z =  resultz1 + 4095 - resultz2; 
   
   /////////////////////////////////////////////////////////
   if(coord.z >= Z_THRESHOLD) {  // if we have more than the pressure threshold then read X&Y data
        coord.x = _Read_State(X_DIR);
        coord.y = _Read_State(Y_DIR);
    }
      return coord;
}


void attachXPT2046Screen(const TouchScreenInterface * pScreenInterface){
    xptInterface = pScreenInterface;
}