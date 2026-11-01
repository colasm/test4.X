/* 
 * File:   XPT2046.h
 * Author: Maxime COLAS
 *
 * Created on 15 juillet 2025, 14:37
 */

#ifndef XPT2046_H
#define	XPT2046_H

#include <stdint.h>
#include <stdbool.h>
#include "TouchScreenInterface.h"
#include "commonStructs.h"
#include "../spi/host/spi_host_interface.h"

typedef struct{
    int32_t XOffset;
    int32_t YOffset;
    int32_t dXTouch;
    int32_t dXPixel;
    int32_t dYTouch;
    int32_t dYPixel;     
    bool    notValid;
} Cal;



extern bool touchFlag;


 void XPT2046Init(const struct SPI_HOST_INTERFACE *host);
 

 
 /**
  * Calibrated pos Read
  * @return X and Y coordinates of touched pixel
  */
 Rect XPT2046_GetPos(void);
 
 
 CoordXYZ XPT2046_Read_XYZ(void);
 
 /**
  * Uncalibrated Read : only used for calibration
  * @return 
  */
 Rect XPT2046_Read_XY(void);
 
 
 
 void attachXPT2046Screen(const TouchScreenInterface * pScreenInterface);
 void setXCalibration(int16_t X1Touch,int16_t X1Pixel,int16_t X2Touch,int16_t X2Pixel);
 void setYCalibration(uint16_t Y1Touch,uint16_t Y1Pixel,uint16_t Y2Touch,uint16_t Y2Pixel);
 void setCalibrationMode(uint8_t mode);
 bool storeCalibrationNVM();
 bool getCalibrationNVM();
 //void calibrationIsValid();
#endif	/* XPT2046_H */

