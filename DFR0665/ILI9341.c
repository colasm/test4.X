
#include <libpic30.h>
#include "../mcc_generated_files/spi_host/spi1.h"
#include "ILI9341.h"
#include "../mcc_generated_files/system/pins.h"
#include "TouchScreenInterface.h"
#include "SPIBus.h"

#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left
#define ILI9341_WRITE16(x) do{\
                        spi->ByteWrite((uint8_t)(x>>8));\
                        spi->ByteWrite((uint8_t)(x&0x00FF));\
                        }while(0)\



static const uint8_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,                    // LCD_POWERB (Power control B)
  0xED, 4, 0x64, 0x03, 0x12, 0x81,              // LCD_POWER_SEQ (Power on sequence control)
  0xE8, 3, 0x85, 0x00, 0x78,                    // LCD_DTCA (Driver timing control A)
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,        // LCD_POWERA (Power control A)
  0xF7, 1, 0x20,                                // LCD_PRC (Pump ratio control)
  0xEA, 2, 0x00, 0x00,                          // LCD_DTCB (Driver timing control B)
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_PIXFMT  , 1, 0x55,             // Pixel formats RGB565
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_DISPON  , 0x80,                // Display on
  0x00                                   // End of list
};

static uint16_t _width,_height;
static uint8_t _orientation=0;
static const struct SPI_HOST_INTERFACE *spi;



static void _ILI9341SendCommand(uint8_t cmd,const uint8_t * args,size_t numArgs);
static void _ILI9341_CommandWrite(uint8_t cmd);
static void _ILI9341WritePixels(RGB565 *colors, size_t len);
static void _ILI9341ReadPixels(RGB *buffer, size_t len);
static void _ILI9341Select(void);


void _ILI9341Select(){
    // si pas déja sélectionné
    if(CS_LCD_GetValue()){
        spi->Close(); // arrêt SPI1
        SPIBus_DisableAllCS();// déselection
        spi->Open(ILLI9341);  // ouverture SPI1 sur ILI9341
        CS_LCD_SetLow(); // s�lection esclave
    }

}

void ILI9341Init(const struct SPI_HOST_INTERFACE *host){

  spi = host;
  uint8_t cmd, x, numArgs,i=0;
 
  const uint8_t *addr = initcmd;
  
  
 // set brightness on 
 BLK_SetHigh(); 
  // let's reset chip
 RESET_SetLow();
  __delay_ms(150UL);
 RESET_SetHigh();
  __delay_ms(10UL);           // wait before sending commands : Datasheet p230
  
  _ILI9341Select();
   while (addr[i] > 0) {
      cmd = addr[i++];
      x =  addr[i++];
      numArgs = x&0x7F;
      _ILI9341SendCommand(cmd, &addr[i], numArgs);
      i += numArgs;
        if (x & 0x80) __delay_ms(150UL);
  }
  _width = ILI9341_TFTWIDTH;
  _height = ILI9341_TFTHEIGHT;
}


/**
 * @Brief Send a command with parameters to the DFR screen
 * @param cmd
 * @param args
 * @param numArgs
 */
void _ILI9341SendCommand(uint8_t cmd,const uint8_t * args,size_t numArgs){
    
    _ILI9341_CommandWrite(cmd);
    spi->BufferWrite((uint8_t *) args,numArgs);
    while(spi->OnTransaction());
    
}



/**
 *  @brief Set a window on screen memory just prior to write into it
 * 
 * @param x1 : upper top pixel col
 * @param y1 : upper top pixel row
 * @param w :  window width
 * @param h :  window height
 */
void _ILI9341SetAddressWindow(uint16_t x1,uint16_t y1,uint16_t w,uint16_t h){
     static uint16_t old_x1 = 0xffff, old_x2 = 0xffff;
     static uint16_t old_y1 = 0xffff, old_y2 = 0xffff;
     
    uint16_t x2 = (x1 + w - 1), y2 = (y1 + h - 1);
    
  if (x1 != old_x1 || x2 != old_x2) {
    _ILI9341_CommandWrite(ILI9341_CASET); // Column address set
    ILI9341_WRITE16(x1);
    ILI9341_WRITE16(x2);
    old_x1 = x1;
    old_x2 = x2;
  }
  if (y1 != old_y1 || y2 != old_y2) {
    _ILI9341_CommandWrite(ILI9341_PASET); // Row address set
    ILI9341_WRITE16(y1);
    ILI9341_WRITE16(y2);
    old_y1 = y1;
    old_y2 = y2;
  }
  _ILI9341_CommandWrite(ILI9341_RAMWR); // Write to RAM
 // CS_LCD_SetHigh();

}

/**
 * Send a command to the DFR0655 Screen
 * @param cmd command to be sent
 */
void _ILI9341_CommandWrite(uint8_t cmd){
    while(spi->OnTransaction());
    _ILI9341Select();
    DC_SetLow();            // Command mode
    spi->ByteWrite(cmd); // Row address set
    DC_SetHigh();
}



/**
 * @Brief Set origin of (0,0) and orientation of TFT display
 * @param m rotation index (between 0 and 3)
 */
void ILI9341SetRotation(uint8_t m) {
  int rotation = m % 4; // can't be higher than 3
  _orientation = m;
  uint8_t byte_to_send = 0;
  _ILI9341Select();
  switch (rotation) {
  case 0: //(portrait)
    byte_to_send = (MADCTL_MX | MADCTL_BGR);
    _width = ILI9341_TFTWIDTH;
    _height = ILI9341_TFTHEIGHT;
    break;
  case 1: // counter clock lanscape
    byte_to_send = (MADCTL_MV | MADCTL_BGR);
    _width = ILI9341_TFTHEIGHT;
    _height = ILI9341_TFTWIDTH;
    break;
  case 2: // reversed portrait
    byte_to_send = (MADCTL_MY | MADCTL_BGR);
    _width = ILI9341_TFTWIDTH;
    _height = ILI9341_TFTHEIGHT;
    break;
  case 3: // counterwise lansdcape
    byte_to_send = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    _width = ILI9341_TFTHEIGHT;
    _height = ILI9341_TFTWIDTH;
    break;
  }

  _ILI9341SendCommand(ILI9341_MADCTL, &byte_to_send, 1);
}


/**
 * @brief send pixels to DFR0665's screen at format RBG565
 * @param colors : pixels color to write (16 bits)
 * @param len
 * @note This function must be used after setDFR0665AddressWindow
 */
static void _ILI9341WritePixels(RGB565 *colors, size_t len){
    
   uint8_t * colorsBytes = (uint8_t *) colors;
   DC_SetLow();
   spi->BufferWrite((uint8_t *) colorsBytes,2*len);
}


/**
 * @brief read length pixels from the current window position
 * @param buffer dimensionned as 3 bytes per pixel
 * @param len : number of pixels to read (must be less or equal to predefined window)
 */
static void _ILI9341ReadPixels(RGB *buffer, size_t len){
    uint8_t dummy __attribute__((unused));
    _ILI9341_CommandWrite(ILI9341_RAMRD);
    uint8_t * pbuffer =(uint8_t *)buffer; 
    
    dummy = spi->ByteRead();

    pbuffer++;
    for(uint32_t index = 0;index<len;index++){
        spi->BufferRead(pbuffer,3);
        pbuffer+=4;
    }
}


/**
 * Read TFT memory area between x1,y1 and x1+w-1,y1+h-1
 * @param x1
 * @param y1
 * @param w
 * @param h
 * @param buffer
 */
void ILI9341GetArea(uint16_t x1,uint16_t y1,uint16_t w,uint16_t h, RGB * buffer){
    _ILI9341Select();
    _ILI9341SetAddressWindow(x1,y1,w,h);
    // TODO
}


/**
 * @Brief convert RGB values given in format XRGB on 32 bits to RBG565 on 16 bits where X is considered as dummy byte
 * @param[in,out] tab (input) XRGB data, (output) RGB565 data
 * @param len length of the XRG buffer in 32 bits words
 * @note side effet : tab is modified 
 */
static void _convertRGBtoRGB565(void * tab,size_t len){
    uint16_t R5,G6,B5;
    uint16_t * outTab=tab;
    uint32_t * inTab=tab;
    uint16_t readIndex=0,writeIndex=0;
    for(readIndex=0;readIndex<len;readIndex++) {
        R5 = (uint16_t)((inTab[readIndex]&0x00FFFFFF)>>19); //R on 5 bits
        G6 = (uint16_t)((inTab[readIndex]&0x0000FFFF)>>10);
        B5 = (uint16_t)((inTab[readIndex]&0x000000FF)>>3);
        outTab[writeIndex++]= (R5<<11)|(G6<<5)|B5;
    }
    
}


/**
 * @brief Screen dimension getter
 * @return Width of screen in pixel
 */
uint16_t ILI9341GetWidth(){
    return _width;
}

/**
 * @brief Screen dimension getter
 * @return Height of screen in pixel
 */
uint16_t ILI9341GetHeight(){
    return _height;
}

/**
 * @brief Screen rotation index getter  
 * @return the index (0 : portrait, 1 :90� counterclock, 2 : 180�, 3:90� clockwise)
 */
uint8_t ILI9341GetOrientation(){
    return _orientation;
}


/**
 * @brief Fill a rectangular area with RGB565 data
 * @param x first column
 * @param y first row
 * @param w area width
 * @param h area height
 * @param data pointer to RGB565 pixels
 */
void ILI9341FillAreaWithColorsRGB(uint16_t x, uint16_t y,uint16_t w,uint16_t h,RGB * data){
    
    _ILI9341Select();
    _ILI9341SetAddressWindow(x,y,w,h);
    _convertRGBtoRGB565(data,w*h);
    _ILI9341WritePixels((RGB565 *)data, w*h);    
}



/**
 * @brief Fill a rectangular area with RGB565 data
 * @param x first column
 * @param y first row
 * @param w area width
 * @param h area height
 * @param color used to fill area
 */
void ILI9341FillAreaWithSingleColorRGB(uint16_t x, uint16_t y,uint16_t w,uint16_t h,RGB color){
    uint16_t c;
    _ILI9341Select();
    _convertRGBtoRGB565(&color,1);
     c = (uint16_t) color;
    _ILI9341SetAddressWindow(x,y,w,h);
    
    for(uint32_t it= 0;it<h*w;it++)
        ILI9341_WRITE16(c);

}


// interface for GFX
const GFXDriver ILI9341Driver={
    .fillAreaWithColorRGB = &ILI9341FillAreaWithSingleColorRGB,
    .fillAreaWithPixelsRGB= &ILI9341FillAreaWithColorsRGB,
    .readAreaPixelsRGB = &ILI9341GetArea,
    .getScreenWidth = &ILI9341GetWidth,
    .getScreenHeight = &ILI9341GetHeight
};

// Interface for XPT2046
const TouchScreenInterface ILI9341ScreenInterface={
    .getScreenWidth = &ILI9341GetWidth,
    .getScreenHeight = &ILI9341GetHeight,
    .getScreenOrientation = &ILI9341GetOrientation
};


