/**
 * SPI1 Generated Driver Source File
 * 
 * @file        spi1.c
 * 
 * @ingroup     spihostdriver
 * 
 * @brief       This is the generated driver source file for SPI1 driver.
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
#include "../spi1.h"
#include "../../system/pins.h"

// Section: File specific data type definitions

/** 
 @ingroup spidriver
  @brief Dummy data to be sent for half duplex communication.
*/
#define SPI1_DUMMY_DATA 0x0



static bool SPI1_Transaction = false;
static uint16_t SPI1_TxRemain = 0;
static uint8_t * SPI1_TxBuffer = NULL;

//Defines an object for SPI_HOST_INTERFACE.

const struct SPI_HOST_INTERFACE SPI1_Host = {
    .Initialize         = &SPI1_Initialize,
    .Deinitialize       = &SPI1_Deinitialize,
    .Close              = &SPI1_Close,
    .Open               = &SPI1_Open,
    .BufferExchange     = &SPI1_BufferExchange,
    .BufferRead         = &SPI1_BufferRead,
    .BufferWrite        = &SPI1_BufferWrite,
    .ByteExchange       = &SPI1_ByteExchange,
    .ByteRead           = &SPI1_ByteRead,    
    .ByteWrite          = &SPI1_ByteWrite,
    .IsRxReady          = &SPI1_IsRxReady,
    .IsTxReady          = &SPI1_IsTxReady,
};
        

/**
 @ingroup spihostdriver
 @struct SPI1_CONFIG 
 @brief Defines the SPI1 configuration.
*/
struct SPI1_HOST_CONFIG
{ 
    uint32_t controlRegister1; //SPI1BRG
    uint32_t controlRegister2; //SPI1CON1
};

static const struct SPI1_HOST_CONFIG config[] = {  
                                        { 
                                            /*Configuration setting for ILLI9341.
                                            SPI Mode : Mode 0, Sampled at : Middle, Data Width : 8 Clock Frequency : 25000 kHz*/
                                            0x1,//SPI1BRG
                                            0x120,//SPI1CON1, no enhanced buffer
                                        },
                                        { 
                                            /*Configuration setting for XPT2046.
                                            SPI Mode : Mode 0, Sampled at : Middle, Data Width : 8 Clock Frequency : 2000 kHz*/
                                            0x18,//SPI1BRG
                                            0x120,//SPI1CON1, no enhanced buffer
                                        },
                                    };




/* User defined functions */

/* Interrupt service function for the SPI1 reception */
/* Each reception corresponds to a transmitted data so if the whole buffer has not been 
   transmitted yet, send next byte else reset transaction*/
void __attribute__ (( interrupt, no_auto_psv )) _SPI1RXInterrupt (void)
{
    volatile uint8_t __attribute((unused))dummy;
    IFS1bits.SPI1RXIF = 0;   
    if(SPI1STATbits.SPIRBF)
        dummy = SPI1BUF;
    if(SPI1_TxRemain>0){ 
    SPI1BUF = *(SPI1_TxBuffer++);
    SPI1_TxRemain--;
    }else{
        SPI1_Transaction = false;
        IEC1bits.SPI1RXIE = 0;
    }
      
}



inline void SPI1_DisableAllCS(){
    CS_LCD_SetHigh();
    CS_TOUCH_SetHigh();
    CS_SD_SetHigh();
}




// Section: Driver Interface Function Definitions

void SPI1_Initialize (void)
{
    // WLENGTH 0x0; 
    SPI1CON2 = 0x0;
    // SPIRBF disabled; SPITBF disabled; SPITBE enabled; SPIRBE enabled; SPIROV disabled; SRMT disabled; SPITUR disabled; SPIBUSY disabled; FRMERR disabled; TXELM disabled; RXELM disabled; 
    SPI1STAT = 0x28;
    // SPIBUF 0x0; 
    SPI1BUF = 0x0;
    // SPIBRG 1; 
    SPI1BRG = 0x1;
    // SPIURDT 0x0; 
    SPI1URDT = 0x0; 
    // ENHBUF enabled; SPIFE Frame Sync pulse precedes; MCLKEN Standard Speed Peripheral Clock; DISSCK disabled; DISSDI disabled; MSTEN Host; CKP Idle:Low, Active:High; SSEN disabled; CKE Active to Idle; SMP Middle; MODE16 disabled; MODE32 disabled; DISSDO disabled; SIDL disabled; ON disabled; FRMCNT 0x0; FRMSYPW One clock wide; MSSEN disabled; FRMPOL disabled; FRMSYNC disabled; FRMEN disabled; AUDMOD I2S; URDTEN disabled; AUDMONO stereo; IGNTUR disabled; IGNROV disabled; SPISGNEXT not sign-extended; AUDEN disabled; 
    SPI1CON1 = 0x120;
    
    SPI1IMSKbits.SPIRBFEN = 1;
    IPC7bits.SPI1RXIP = 4;
    SPI1_DisableAllCS();
    
}

void SPI1_Deinitialize (void)
{
    SPI1_Close();
    SPI1IMSKbits.SPIRBFEN = 0;
    IPC7bits.SPI1RXIP = 0;    
    SPI1CON1 = 0x0;
    SPI1CON2 = 0x0;
    SPI1STAT = 0x28;
    SPI1BUF = 0x0;
    SPI1BRG = 0x0;
    SPI1URDT = 0x0;
}

void SPI1_Close(void)
{ 
    while(SPI1_OnTransaction());
    IEC1bits.SPI1RXIE = 0; //Disable RX interrupt
    SPI1_Transaction = false;
    SPI1CON1bits.ON = 0U;
}

bool SPI1_Open(uint8_t spiConfigIndex)
{
    bool status = false;
    if(!SPI1CON1bits.ON)
    {
        SPI1BRG = config[spiConfigIndex].controlRegister1;
        SPI1CON1 = config[spiConfigIndex].controlRegister2;
        SPI1CON1bits.ON = 1U;
        
        status = true;
    }
    return status;
}

uint8_t SPI1_ByteExchange(uint8_t byteData)
{
    volatile uint8_t inByteData;
    IEC1bits.SPI1RXIE = 0; //Disable RX interrupt
    SPI1BUF = byteData;
    while(SPI1STATbits.SPIRBF==0);
    inByteData = SPI1BUF;
       
          
    return inByteData;
}

void SPI1_BufferExchange(void *bufferData, size_t bufferSize)
{
    
}

void SPI1_BufferWrite(void *bufferData, size_t bufferSize)
{   
     
    if(bufferSize>0){
        while(SPI1_Transaction);
        SPI1_Transaction = true;
        IFS1bits.SPI1RXIF = 0;
        IEC1bits.SPI1RXIE = 1; //Enable RX interrupt
        SPI1_TxRemain = bufferSize;
        SPI1_TxBuffer = bufferData;
        IFS1bits.SPI1RXIF = 1; // start interrupt
    }
}

void SPI1_BufferRead(void *bufferData, size_t bufferSize)
{  
}

void SPI1_ByteWrite(uint8_t byteData)
{
    SPI1_ByteExchange(byteData);
}

uint8_t SPI1_ByteRead(void)
{
   return SPI1_ByteExchange(SPI1_DUMMY_DATA);
}

bool SPI1_IsRxReady(void)
{    
    return (!SPI1STATbits.SPIRBE);
}

bool SPI1_IsTxReady(void)
{    
    return (!SPI1STATbits.SPITBF);
}

bool SPI1_OnTransaction(){
    return SPI1_Transaction;
}
