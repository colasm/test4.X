/**
 * SPI2 Generated Driver Source File
 * 
 * @file        spi2.c
 * 
 * @ingroup     spiclientdriver
 * 
 * @brief       This is the generated driver source file for SPI2 driver.
 *
 * @skipline @version     PLIB Version 1.2.2
 *
 * @skipline    Device : dsPIC33AK128MC105
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

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

// Section: Included Files
#include <xc.h>
#include "../spi2.h"

// Section: File specific data type definitions

/** 
 @ingroup spidriver
  @brief Dummy data to be sent for half duplex communication.
*/
#define SPI2_DUMMY_DATA 0x0

//Defines an object for SPI_CLIENT_INTERFACE.

const struct SPI_CLIENT_INTERFACE SPI2_Client = {
    .Initialize         = &SPI2_Initialize,
    .Deinitialize       = &SPI2_Deinitialize,
    .Close              = &SPI2_Close,
    .Open               = &SPI2_Open,
    .WordRead = &SPI2_WordRead,
    .WordWrite = &SPI2_WordWrite,
    .IsTxOk = &SPI2_isTxOk,
    .SetRXInterruptHandler = &SPI2_SetRXInterruptHandler
};
        

/**
 @ingroup spiclientdriver
 @struct SPI2_CONFIG 
 @brief Defines the SPI2 configuration.
*/
struct SPI2_CLIENT_CONFIG
{ 
    uint32_t controlRegister1; //SPI2CON1
};

static const struct SPI2_CLIENT_CONFIG config[] = {  
                                        { 
                                            /*Configuration setting for AD74111.
                                             * 31    : 0 : Non audio protocol
                                             * 30    : 0 : No sign extension
                                             * 29-28 : 00 : over and underrun dont stop spi
                                             * 27 :    0 : data is stereo (but inactive in non audio mode)
                                             * 26 :    0 : transmit last data if underrun (but spi stops)
                                             * 25-24 : 00 : audio coding in I2S
                                             * 23-21 : 111 : Framed client active high mode (SS pin used as FSYNC input)
                                             * 20 :    0 : automatic SS in host mode (but we're in client mode)
                                             * 19 :    0 : FSYNC is one clock wise
                                             * 18-16 : 000 : each 16bit word preceded by FSYNC (16 bits mixed mode used)
                                             * 15 :    0 : SPI is kept in off mode
                                             * 14 :    0 : unused
                                             * 13 :    0 : Stopped in idle mode
                                             * 12 :    0 : SDO used
                                             * 11-10 : 01 : 16 bits communication
                                             * 9 :     0 : SMP phase is not tunable in client mode
                                             * 8 :     0 : CKE = 0 (sample on falling edge, send on rising)
                                             * 7 :     0 : SS not used in client mode to select dspic (SS not used in framed mode)
                                             * 6 :     0 : idle state of clock is low (not used in framed mode)
                                             * 5 :     0 : client mode
                                             * 4 :     0 : SDI is used
                                             * 3 :     0 : SCK controlled by module
                                             * 2 :     0 : clock source (in client mode, does not matter)
                                             * 1 :     0 : FSYNC precede first bit
                                             * 0       1 : enhanced buffer used 
                                             * */
                                            0x00E00401// 00000000 11100000 00000100 00000001             
                                        },
                                    };



// Section: Driver Interrupt managment

static void (*SPI2_RXInterruptHandler)(void) = NULL;




void SPI2_SetRXInterruptHandler(void (* RXInterruptHandler)(void))
{ 
    IEC2bits.SPI2RXIE = 0; //Disable CNAI interrupt
    IFS2bits.SPI2RXIF = 0;
    SPI2_RXInterruptHandler = RXInterruptHandler; 
    SPI2IMSKbits.RXMSK = 2;
    SPI2IMSKbits.RXWIEN = 1;
    if(SPI2STATbits.SPIROV) 
        SPI2STATbits.SPIROV = 0;
    IEC2bits.SPI2RXIE = 1;
}


void __attribute__ (( interrupt, no_auto_psv )) _SPI2RXInterrupt(){

    if(SPI2_RXInterruptHandler!=NULL){
       SPI2_RXInterruptHandler(); 
    }
    IFS2bits.SPI2RXIF = 0;
}






// Section: Driver Interface Function Definitions
void SPI2_Initialize (void)
{
    // WLENGTH 0x0 -> controlled by SPI2CON1 (bits 10-11); 
    SPI2CON2 = 0x00;
    // SPIRBF disabled; SPITBF disabled; SPITBE enabled; SPIRBE enabled; SPIROV disabled; SRMT disabled; SPITUR disabled; SPIBUSY disabled; FRMERR disabled; TXELM disabled; RXELM disabled; 
    SPI2STAT = 0x28;
    SPI2BUF = 0x0;
    SPI2BRG = 0x0;
    SPI2URDT = 0x0;
    SPI2CON1 = 0x00E00401;
}

void SPI2_Deinitialize (void)
{
    SPI2_Close();
    
    SPI2CON1 = 0x0;
    SPI2CON2 = 0x0;
    SPI2STAT = 0x28;
    SPI2BUF = 0x0;
    SPI2BRG = 0x0;
    SPI2URDT = 0x0;
}

void SPI2_Close(void)
{
    SPI2CON1bits.ON = 0U;
}

bool SPI2_Open(uint8_t spiConfigIndex)
{
    bool status = false;
    if(!SPI2CON1bits.ON)
    {
        SPI2CON1 = config[spiConfigIndex].controlRegister1;
        SPI2CON1bits.ON = 1U;
        status = true;
    }
    return status;
}


void SPI2_WordWrite(int16_t data){
    SPI2BUF = data;
}

int16_t SPI2_WordRead(void){
    return SPI2BUF;
}


bool SPI2_isTxOk(void){
    volatile uint16_t dummy __attribute__((unused));
    if(SPI2STATbits.RXELM<2) return false;
    dummy = SPI2BUF;
    dummy = SPI2BUF;
    return true;
}
