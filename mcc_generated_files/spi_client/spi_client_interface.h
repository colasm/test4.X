
/**
 * SPI Generated Driver Interface Header File
 * 
 * @file        spi_client_interface.h
 * 
 * @defgroup    spiclientdriver SPI Client Driver
 * 
 * @brief       Serial Peripheral Interface (SPI) CLIENT Driver using dsPIC MCUs
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

#ifndef SPI_CLIENT_INTERFACE_H
#define SPI_CLIENT_INTERFACE_H

// Section: Included Files
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Section: Data Type Definitions
        

/**
 @ingroup spiclientdriver
 @struct SPI_CLIENT_INTERFACE
 @brief Structure containing the function pointers of SPI CLIENT driver.
*/
struct SPI_CLIENT_INTERFACE
{   
    void (*Initialize)(void); 
    ///< Pointer to SPIx_Initialize e.g. \ref SPI2_Initialize
    
    void (*Deinitialize)(void);
    ///< Pointer to SPIx_Deinitialize e.g. \ref SPI2_Deinitialize
    
    void (*Close)(void);
    ///< Pointer to SPIx_Close e.g. \ref SPI2_Close
    
    bool (*Open)(uint8_t spiConfigIndex);
    ///< Pointer to SPIx_Open e.g. \ref SPI2_Open


    int16_t (*WordRead)(void);
    ///< Pointer to SPIx_WordRead e.g. \ref SPI2_WordRead

    void (*WordWrite)(int16_t);
    ///< Pointer to SPIx_WordWrite e.g. \ref SPI2_WordWrite
    
    bool (*IsTxOk)(void);
    ///< Pointer to SPIx_isTxOk e.g. \ref SPI2__isTxOk
    
    void (*SetRXInterruptHandler)(void (* RXInterruptHandler)(void));
    //< Pointer to SPIx_SetInterruptHandler e.g. \ref SPI2__SetInterruptHandler
};

#endif //SPI_CLIENT_INTERFACE_H


