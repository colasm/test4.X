
/**
 * SPI2 Generated Driver Header File
 * 
 * @file        spi2.h
 * 
 * @ingroup     spiclientdriver
 * 
 * @brief       This is the generated driver header file for the SPI2 driver
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

#ifndef SPI2_H
#define SPI2_H

// Section: Included Files
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "spi_client_interface.h"

// Section: Data Type Definitions

/**
 @ingroup   spiclientdriver
 @brief     Structure object of type SPI_CLIENT_INTERFACE assigned with name 
            displayed in the Melody Driver User interface. A structure pointer can be used to achieve portability
            across the SPI CLIENT having same interface structure.
*/

extern const struct SPI_CLIENT_INTERFACE SPI2_Client;
      
/**
 * @ingroup  spidriver
 * @brief    This macro defines the Custom Name for \ref SPI2_Initialize API
 */
#define SPI2_Client_Initialize SPI2_Initialize
/**
 * @ingroup  spidriver
 * @brief    This macro defines the Custom Name for \ref SPI2_Deinitialize API
 */
#define SPI2_Client_Deinitialize SPI2_Deinitialize
/**
 * @ingroup  spidriver
 * @brief    This macro defines the Custom Name for \ref SPI2_Close API
 */
#define SPI2_Client_Close SPI2_Close
/**
 * @ingroup  spidriver
 * @brief    This macro defines the Custom Name for \ref SPI2_Open API
 */
#define SPI2_Client_Open SPI2_Open
/**
 * @ingroup  spidriver
 * @brief    This macro defines the Custom Name for \ref SPI2_ByteExchange API
 */

/**
@ingroup spiclientdriver
@enum SPI2_CLIENT_USER_CONFIG
@brief Enum list is the Custom names for the SPI2 CLIENT multiple configuration, 
       configured by user in MCC Melody user interface. 
@note The enum list in the Help document might be just a reference to illustrate multiple configuration.
      Generated enum list is based on the configuration done by user in the MCC Melody user interface
*/

enum SPI2_CLIENT_USER_CONFIG{
     /**Custom name for configuration setting:
    SPI Mode : Mode 1**/
    AD74111,
    
};

// Section: Driver Interface Function


/**
 * @ingroup spiclientdriver
 * @brief   Initializes SPI2 module, using the given initialization data. 
 *          This function must be called before any other SPI2 function is called.
 * @param   none
 * @return  none  
 */
void SPI2_Initialize (void);


/**
 * @ingroup spiclientdriver
 * @brief   Deinitializes the SPI2 to POR values.
 * @param   none
 * @return  none  
 */
void SPI2_Deinitialize(void);


/**
 * @ingroup spiclientdriver
 * @brief   Disables the SPI2 module. 
 * @pre     The \ref SPI2_Open function must be called before calling this function.
 * @param   none
 * @return  none  
 */
void SPI2_Close (void);


/**
 * @ingroup     spiclientdriver
 * @brief       Configures SPI2 module with user defined unique configuration. 
 * @param[in]   spiConfigIndex    - \ref SPI2_USER_CONFIG Enum value 
 * @return bool true   -   SPI2 is configured successfully.
 * @return bool false  -   SPI2 is not configured successfully.  
 */
bool SPI2_Open(uint8_t spiConfigIndex);

/**
 * get a word from SPI interface
 * @return : the word that is read.
 */
int16_t SPI2_WordRead(void);

/**
 * write a word to the SPI interface
 * @param data : the word to write
 */
void SPI2_WordWrite(int16_t data);


/**
 * return true if the transmission of both words previously written in FIFO is finished
 * @return true if finished
 */
bool SPI2_isTxOk(void);


/**
 * Install the interrupt callback and enable RX interrupt
 * @param RXInterruptHandler : interrupt callback function
 */
void SPI2_SetRXInterruptHandler(void (* RXInterruptHandler)(void));

#endif //SPI2_H



