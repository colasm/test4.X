/**
 * PINS Generated Driver Header File 
 * 
 * @file      pins.h
 *            
 * @defgroup  pinsdriver Pins Driver
 *            
 * @brief     The Pin Driver directs the operation and function of 
 *            the selected device pins using dsPIC MCUs.
 *
 * @skipline @version   PLIB Version 1.0.5
 *
 * @skipline  Device : dsPIC33AK128MC105
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

#ifndef PINS_H
#define PINS_H
// Section: Includes
#include <xc.h>

/**
 * @ingroup  pinsdriver
 * @brief    Locks all the Peripheral Remapping registers and cannot be written.
 * @return   none  
 */
#define PINS_PPSLock()           (RPCONbits.IOLOCK = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Unlocks all the Peripheral Remapping registers and can be written.
 * @return   none  
 */
#define PINS_PPSUnlock()         (RPCONbits.IOLOCK = 0)

// Section: Device Pin Macros
/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA2 GPIO Pin which has a custom name of LED3 to High
 * @pre      The RA2 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define LED3_SetHigh()          (_LATA2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA2 GPIO Pin which has a custom name of LED3 to Low
 * @pre      The RA2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED3_SetLow()           (_LATA2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA2 GPIO Pin which has a custom name of LED3
 * @pre      The RA2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED3_Toggle()           (_LATA2 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA2 GPIO Pin which has a custom name of LED3
 * @param    none
 * @return   none  
 */
#define LED3_GetValue()         _RA2

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA2 GPIO Pin which has a custom name of LED3 as Input
 * @param    none
 * @return   none  
 */
#define LED3_SetDigitalInput()  (_TRISA2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA2 GPIO Pin which has a custom name of LED3 as Output
 * @param    none
 * @return   none  
 */
#define LED3_SetDigitalOutput() (_TRISA2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA3 GPIO Pin which has a custom name of LED2 to High
 * @pre      The RA3 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define LED2_SetHigh()          (_LATA3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA3 GPIO Pin which has a custom name of LED2 to Low
 * @pre      The RA3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED2_SetLow()           (_LATA3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA3 GPIO Pin which has a custom name of LED2
 * @pre      The RA3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED2_Toggle()           (_LATA3 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA3 GPIO Pin which has a custom name of LED2
 * @param    none
 * @return   none  
 */
#define LED2_GetValue()         _RA3

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA3 GPIO Pin which has a custom name of LED2 as Input
 * @param    none
 * @return   none  
 */
#define LED2_SetDigitalInput()  (_TRISA3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA3 GPIO Pin which has a custom name of LED2 as Output
 * @param    none
 * @return   none  
 */
#define LED2_SetDigitalOutput() (_TRISA3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA4 GPIO Pin which has a custom name of LED1 to High
 * @pre      The RA4 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define LED1_SetHigh()          (_LATA4 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA4 GPIO Pin which has a custom name of LED1 to Low
 * @pre      The RA4 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED1_SetLow()           (_LATA4 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA4 GPIO Pin which has a custom name of LED1
 * @pre      The RA4 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define LED1_Toggle()           (_LATA4 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA4 GPIO Pin which has a custom name of LED1
 * @param    none
 * @return   none  
 */
#define LED1_GetValue()         _RA4

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA4 GPIO Pin which has a custom name of LED1 as Input
 * @param    none
 * @return   none  
 */
#define LED1_SetDigitalInput()  (_TRISA4 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA4 GPIO Pin which has a custom name of LED1 as Output
 * @param    none
 * @return   none  
 */
#define LED1_SetDigitalOutput() (_TRISA4 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA6 GPIO Pin which has a custom name of RESET_MB to High
 * @pre      The RA6 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define RESET_MB_SetHigh()          (_LATA6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA6 GPIO Pin which has a custom name of RESET_MB to Low
 * @pre      The RA6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RESET_MB_SetLow()           (_LATA6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA6 GPIO Pin which has a custom name of RESET_MB
 * @pre      The RA6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RESET_MB_Toggle()           (_LATA6 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA6 GPIO Pin which has a custom name of RESET_MB
 * @param    none
 * @return   none  
 */
#define RESET_MB_GetValue()         _RA6

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA6 GPIO Pin which has a custom name of RESET_MB as Input
 * @param    none
 * @return   none  
 */
#define RESET_MB_SetDigitalInput()  (_TRISA6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA6 GPIO Pin which has a custom name of RESET_MB as Output
 * @param    none
 * @return   none  
 */
#define RESET_MB_SetDigitalOutput() (_TRISA6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA7 GPIO Pin which has a custom name of SW1 to High
 * @pre      The RA7 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define SW1_SetHigh()          (_LATA7 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA7 GPIO Pin which has a custom name of SW1 to Low
 * @pre      The RA7 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW1_SetLow()           (_LATA7 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA7 GPIO Pin which has a custom name of SW1
 * @pre      The RA7 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW1_Toggle()           (_LATA7 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA7 GPIO Pin which has a custom name of SW1
 * @param    none
 * @return   none  
 */
#define SW1_GetValue()         _RA7

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA7 GPIO Pin which has a custom name of SW1 as Input
 * @param    none
 * @return   none  
 */
#define SW1_SetDigitalInput()  (_TRISA7 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA7 GPIO Pin which has a custom name of SW1 as Output
 * @param    none
 * @return   none  
 */
#define SW1_SetDigitalOutput() (_TRISA7 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA8 GPIO Pin which has a custom name of SW2 to High
 * @pre      The RA8 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define SW2_SetHigh()          (_LATA8 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA8 GPIO Pin which has a custom name of SW2 to Low
 * @pre      The RA8 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW2_SetLow()           (_LATA8 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA8 GPIO Pin which has a custom name of SW2
 * @pre      The RA8 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW2_Toggle()           (_LATA8 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA8 GPIO Pin which has a custom name of SW2
 * @param    none
 * @return   none  
 */
#define SW2_GetValue()         _RA8

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA8 GPIO Pin which has a custom name of SW2 as Input
 * @param    none
 * @return   none  
 */
#define SW2_SetDigitalInput()  (_TRISA8 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA8 GPIO Pin which has a custom name of SW2 as Output
 * @param    none
 * @return   none  
 */
#define SW2_SetDigitalOutput() (_TRISA8 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA9 GPIO Pin which has a custom name of SW3 to High
 * @pre      The RA9 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define SW3_SetHigh()          (_LATA9 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA9 GPIO Pin which has a custom name of SW3 to Low
 * @pre      The RA9 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW3_SetLow()           (_LATA9 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA9 GPIO Pin which has a custom name of SW3
 * @pre      The RA9 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define SW3_Toggle()           (_LATA9 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA9 GPIO Pin which has a custom name of SW3
 * @param    none
 * @return   none  
 */
#define SW3_GetValue()         _RA9

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA9 GPIO Pin which has a custom name of SW3 as Input
 * @param    none
 * @return   none  
 */
#define SW3_SetDigitalInput()  (_TRISA9 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA9 GPIO Pin which has a custom name of SW3 as Output
 * @param    none
 * @return   none  
 */
#define SW3_SetDigitalOutput() (_TRISA9 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RB5 GPIO Pin which has a custom name of CS_MB to High
 * @pre      The RB5 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define CS_MB_SetHigh()          (_LATB5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RB5 GPIO Pin which has a custom name of CS_MB to Low
 * @pre      The RB5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_MB_SetLow()           (_LATB5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RB5 GPIO Pin which has a custom name of CS_MB
 * @pre      The RB5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_MB_Toggle()           (_LATB5 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RB5 GPIO Pin which has a custom name of CS_MB
 * @param    none
 * @return   none  
 */
#define CS_MB_GetValue()         _RB5

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RB5 GPIO Pin which has a custom name of CS_MB as Input
 * @param    none
 * @return   none  
 */
#define CS_MB_SetDigitalInput()  (_TRISB5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RB5 GPIO Pin which has a custom name of CS_MB as Output
 * @param    none
 * @return   none  
 */
#define CS_MB_SetDigitalOutput() (_TRISB5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC2 GPIO Pin which has a custom name of CS_LCD to High
 * @pre      The RC2 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define CS_LCD_SetHigh()          (_LATC2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC2 GPIO Pin which has a custom name of CS_LCD to Low
 * @pre      The RC2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_LCD_SetLow()           (_LATC2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC2 GPIO Pin which has a custom name of CS_LCD
 * @pre      The RC2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_LCD_Toggle()           (_LATC2 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC2 GPIO Pin which has a custom name of CS_LCD
 * @param    none
 * @return   none  
 */
#define CS_LCD_GetValue()         _RC2

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC2 GPIO Pin which has a custom name of CS_LCD as Input
 * @param    none
 * @return   none  
 */
#define CS_LCD_SetDigitalInput()  (_TRISC2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC2 GPIO Pin which has a custom name of CS_LCD as Output
 * @param    none
 * @return   none  
 */
#define CS_LCD_SetDigitalOutput() (_TRISC2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC3 GPIO Pin which has a custom name of DC to High
 * @pre      The RC3 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define DC_SetHigh()          (_LATC3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC3 GPIO Pin which has a custom name of DC to Low
 * @pre      The RC3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DC_SetLow()           (_LATC3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC3 GPIO Pin which has a custom name of DC
 * @pre      The RC3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define DC_Toggle()           (_LATC3 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC3 GPIO Pin which has a custom name of DC
 * @param    none
 * @return   none  
 */
#define DC_GetValue()         _RC3

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC3 GPIO Pin which has a custom name of DC as Input
 * @param    none
 * @return   none  
 */
#define DC_SetDigitalInput()  (_TRISC3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC3 GPIO Pin which has a custom name of DC as Output
 * @param    none
 * @return   none  
 */
#define DC_SetDigitalOutput() (_TRISC3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC4 GPIO Pin which has a custom name of BLK to High
 * @pre      The RC4 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define BLK_SetHigh()          (_LATC4 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC4 GPIO Pin which has a custom name of BLK to Low
 * @pre      The RC4 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define BLK_SetLow()           (_LATC4 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC4 GPIO Pin which has a custom name of BLK
 * @pre      The RC4 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define BLK_Toggle()           (_LATC4 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC4 GPIO Pin which has a custom name of BLK
 * @param    none
 * @return   none  
 */
#define BLK_GetValue()         _RC4

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC4 GPIO Pin which has a custom name of BLK as Input
 * @param    none
 * @return   none  
 */
#define BLK_SetDigitalInput()  (_TRISC4 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC4 GPIO Pin which has a custom name of BLK as Output
 * @param    none
 * @return   none  
 */
#define BLK_SetDigitalOutput() (_TRISC4 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC5 GPIO Pin which has a custom name of RESET to High
 * @pre      The RC5 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define RESET_SetHigh()          (_LATC5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC5 GPIO Pin which has a custom name of RESET to Low
 * @pre      The RC5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RESET_SetLow()           (_LATC5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC5 GPIO Pin which has a custom name of RESET
 * @pre      The RC5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define RESET_Toggle()           (_LATC5 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC5 GPIO Pin which has a custom name of RESET
 * @param    none
 * @return   none  
 */
#define RESET_GetValue()         _RC5

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC5 GPIO Pin which has a custom name of RESET as Input
 * @param    none
 * @return   none  
 */
#define RESET_SetDigitalInput()  (_TRISC5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC5 GPIO Pin which has a custom name of RESET as Output
 * @param    none
 * @return   none  
 */
#define RESET_SetDigitalOutput() (_TRISC5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC6 GPIO Pin which has a custom name of INT_MB to High
 * @pre      The RC6 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define INT_MB_SetHigh()          (_LATC6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC6 GPIO Pin which has a custom name of INT_MB to Low
 * @pre      The RC6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define INT_MB_SetLow()           (_LATC6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC6 GPIO Pin which has a custom name of INT_MB
 * @pre      The RC6 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define INT_MB_Toggle()           (_LATC6 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC6 GPIO Pin which has a custom name of INT_MB
 * @param    none
 * @return   none  
 */
#define INT_MB_GetValue()         _RC6

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC6 GPIO Pin which has a custom name of INT_MB as Input
 * @param    none
 * @return   none  
 */
#define INT_MB_SetDigitalInput()  (_TRISC6 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC6 GPIO Pin which has a custom name of INT_MB as Output
 * @param    none
 * @return   none  
 */
#define INT_MB_SetDigitalOutput() (_TRISC6 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD0 GPIO Pin which has a custom name of CS_TOUCH to High
 * @pre      The RD0 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define CS_TOUCH_SetHigh()          (_LATD0 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD0 GPIO Pin which has a custom name of CS_TOUCH to Low
 * @pre      The RD0 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_TOUCH_SetLow()           (_LATD0 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD0 GPIO Pin which has a custom name of CS_TOUCH
 * @pre      The RD0 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_TOUCH_Toggle()           (_LATD0 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD0 GPIO Pin which has a custom name of CS_TOUCH
 * @param    none
 * @return   none  
 */
#define CS_TOUCH_GetValue()         _RD0

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD0 GPIO Pin which has a custom name of CS_TOUCH as Input
 * @param    none
 * @return   none  
 */
#define CS_TOUCH_SetDigitalInput()  (_TRISD0 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD0 GPIO Pin which has a custom name of CS_TOUCH as Output
 * @param    none
 * @return   none  
 */
#define CS_TOUCH_SetDigitalOutput() (_TRISD0 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD1 GPIO Pin which has a custom name of IT_TOUCH to High
 * @pre      The RD1 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define IT_TOUCH_SetHigh()          (_LATD1 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD1 GPIO Pin which has a custom name of IT_TOUCH to Low
 * @pre      The RD1 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IT_TOUCH_SetLow()           (_LATD1 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD1 GPIO Pin which has a custom name of IT_TOUCH
 * @pre      The RD1 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IT_TOUCH_Toggle()           (_LATD1 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD1 GPIO Pin which has a custom name of IT_TOUCH
 * @param    none
 * @return   none  
 */
#define IT_TOUCH_GetValue()         _RD1

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD1 GPIO Pin which has a custom name of IT_TOUCH as Input
 * @param    none
 * @return   none  
 */
#define IT_TOUCH_SetDigitalInput()  (_TRISD1 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD1 GPIO Pin which has a custom name of IT_TOUCH as Output
 * @param    none
 * @return   none  
 */
#define IT_TOUCH_SetDigitalOutput() (_TRISD1 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD2 GPIO Pin which has a custom name of CS_SD to High
 * @pre      The RD2 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define CS_SD_SetHigh()          (_LATD2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD2 GPIO Pin which has a custom name of CS_SD to Low
 * @pre      The RD2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_SD_SetLow()           (_LATD2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD2 GPIO Pin which has a custom name of CS_SD
 * @pre      The RD2 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define CS_SD_Toggle()           (_LATD2 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD2 GPIO Pin which has a custom name of CS_SD
 * @param    none
 * @return   none  
 */
#define CS_SD_GetValue()         _RD2

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD2 GPIO Pin which has a custom name of CS_SD as Input
 * @param    none
 * @return   none  
 */
#define CS_SD_SetDigitalInput()  (_TRISD2 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD2 GPIO Pin which has a custom name of CS_SD as Output
 * @param    none
 * @return   none  
 */
#define CS_SD_SetDigitalOutput() (_TRISD2 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of AD_RESET to High
 * @pre      The RD5 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define AD_RESET_SetHigh()          (_LATD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of AD_RESET to Low
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define AD_RESET_SetLow()           (_LATD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD5 GPIO Pin which has a custom name of AD_RESET
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define AD_RESET_Toggle()           (_LATD5 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD5 GPIO Pin which has a custom name of AD_RESET
 * @param    none
 * @return   none  
 */
#define AD_RESET_GetValue()         _RD5

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of AD_RESET as Input
 * @param    none
 * @return   none  
 */
#define AD_RESET_SetDigitalInput()  (_TRISD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of AD_RESET as Output
 * @param    none
 * @return   none  
 */
#define AD_RESET_SetDigitalOutput() (_TRISD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @param    none
 * @return   none  
 */
void PINS_Initialize(void);

/**
 * @ingroup  pinsdriver
 * @brief    This function is callback for SW1 Pin
 * @param    none
 * @return   none   
 */
void SW1_CallBack(void);

/**
 * @ingroup  pinsdriver
 * @brief    This function is callback for SW2 Pin
 * @param    none
 * @return   none   
 */
void SW2_CallBack(void);

/**
 * @ingroup  pinsdriver
 * @brief    This function is callback for SW3 Pin
 * @param    none
 * @return   none   
 */
void SW3_CallBack(void);

/**
 * @ingroup  pinsdriver
 * @brief    This function is callback for IT_TOUCH Pin
 * @param    none
 * @return   none   
 */
void IT_TOUCH_CallBack(void);


/**
 * @ingroup    pinsdriver
 * @brief      This function assigns a function pointer with a callback address
 * @param[in]  InterruptHandler - Address of the callback function 
 * @return     none  
 */
void SW1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup    pinsdriver
 * @brief      This function assigns a function pointer with a callback address
 * @param[in]  InterruptHandler - Address of the callback function 
 * @return     none  
 */
void SW2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup    pinsdriver
 * @brief      This function assigns a function pointer with a callback address
 * @param[in]  InterruptHandler - Address of the callback function 
 * @return     none  
 */
void SW3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup    pinsdriver
 * @brief      This function assigns a function pointer with a callback address
 * @param[in]  InterruptHandler - Address of the callback function 
 * @return     none  
 */
void IT_TOUCH_SetInterruptHandler(void (* InterruptHandler)(void));


#endif
