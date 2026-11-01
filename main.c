/*
� [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
/*
    Main application
*/

#include "signal/AD74111.h"
#include "DFR0665/ILI9341.h"
#include "DFR0665/XPT2046.h"
#include "DFR0665/gfx.h"
#include "App.h"
#include "DFR0665/DFR0665.h"
#include "DFR0665/SPIBus.h"
#include "signal/dsp.h"
#include "mcc_generated_files/spi_host/spi1.h"
#include "mcc_generated_files/spi_client/spi2.h"
#include <libpic30.h>
#include <xc.h>



/*
    Main application
 */

#define SCREEN_MODE     3



int main(void) {
    SYSTEM_Initialize();
    SPIBus_DisableAllCS(); // all CS lines reset low at power-up; deselect everyone before any transaction

    ILI9341Init(&SPI1_Host);
    ILI9341SetRotation(SCREEN_MODE);
    setGFXDriver(&ILI9341Driver);
    attachXPT2046Screen(&ILI9341ScreenInterface);
    XPT2046Init(&SPI1_Host);

    
    
    // perform calibration if not already done
    if(!getCalibrationNVM())
        DFR0665CalibrateTouchScreen(SCREEN_MODE);
    
    initCyclicBuffers();
    AD74111Init(&SPI2_Client);
    
    clearScreen();
    //debugSPI();
    appMain();
    
    while(1);
    

}