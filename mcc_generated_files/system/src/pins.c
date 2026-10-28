/**
 * PINS Generated Driver Source File 
 * 
 * @file      pins.c
 *            
 * @ingroup   pinsdriver
 *            
 * @brief     This is the generated driver source file for PINS driver.
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

// Section: Includes
#include <xc.h>
#include <stddef.h>
#include "../pins.h"

// Section: File specific functions
static void (*SW1_InterruptHandler)(void) = NULL;
static void (*SW2_InterruptHandler)(void) = NULL;
static void (*SW3_InterruptHandler)(void) = NULL;
static void (*IT_TOUCH_InterruptHandler)(void) = NULL;

// Section: Driver Interface Function Definitions
void PINS_Initialize(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000UL;
    LATB = 0x0000UL;
    LATC = 0x0000UL;
    LATD = 0x0000UL;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x03A3UL;
    TRISB = 0x03DFUL;
    TRISC = 0x00C2UL;
    TRISD = 0x00DAUL;


    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPUA = 0x0380UL;
    CNPUB = 0x0000UL;
    CNPUC = 0x0000UL;
    CNPUD = 0x0000UL;
    CNPDA = 0x0000UL;
    CNPDB = 0x0000UL;
    CNPDC = 0x0000UL;
    CNPDD = 0x0000UL;


    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000UL;
    ODCB = 0x0000UL;
    ODCC = 0x0000UL;
    ODCD = 0x0000UL;


    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x0023UL;
    ANSELB = 0x03DFUL;

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
      PINS_PPSUnlock(); // unlock PPS

        RPINR11bits.SCK2R = 0x0035UL; //RD4->SPI2:SCK2IN;
        RPINR11bits.SDI2R = 0x0037UL; //RD6->SPI2:SDI2;
        RPINR11bits.SS2R = 0x0038UL; //RD7->SPI2:SS2;
        RPINR10bits.SDI1R = 0x0022UL; //RC1->SPI1:SDI1;
        RPOR14bits.RP57R = 0x0010UL;  //RD8->SPI2:SDO2;
        RPOR8bits.RP33R = 0x000DUL;  //RC0->SPI1:SDO1;
        RPINR10bits.SCK1R = 0x0028UL;  //RC7->SPI1:SCK1IN;
        RPOR9bits.RP40R = 0x000EUL;  //RC7->SPI1:SCK1OUT;

      PINS_PPSLock(); // lock PPS

    /*******************************************************************************
    * Interrupt On Change: negative
    *******************************************************************************/
    CNEN1Abits.CNEN1A7 = 1; //Pin : RA7; 
    /*******************************************************************************
    * Interrupt On Change: negative
    *******************************************************************************/
    CNEN1Abits.CNEN1A8 = 1; //Pin : RA8; 
    /*******************************************************************************
    * Interrupt On Change: negative
    *******************************************************************************/
    CNEN1Abits.CNEN1A9 = 1; //Pin : RA9; 
    /*******************************************************************************
    * Interrupt On Change: any
    *******************************************************************************/
    CNEN0Dbits.CNEN0D1 = 1; //Pin : RD1; 
    CNEN1Dbits.CNEN1D1 = 1; //Pin : RD1; 

    /****************************************************************************
     * Interrupt On Change: flag
     ***************************************************************************/
    CNFAbits.CNFA7 = 0;    //Pin : SW1
    CNFAbits.CNFA8 = 0;    //Pin : SW2
    CNFAbits.CNFA9 = 0;    //Pin : SW3
    CNFDbits.CNFD1 = 0;    //Pin : IT_TOUCH

    /****************************************************************************
     * Interrupt On Change: config
     ***************************************************************************/
    CNCONAbits.CNSTYLE = 1; //Config for PORTA
    CNCONAbits.ON = 1; //Config for PORTA
    CNCONDbits.CNSTYLE = 1; //Config for PORTD
    CNCONDbits.ON = 1; //Config for PORTD

    /* Initialize IOC Interrupt Handler*/
    SW1_SetInterruptHandler(&SW1_CallBack);
    SW2_SetInterruptHandler(&SW2_CallBack);
    SW3_SetInterruptHandler(&SW3_CallBack);
    IT_TOUCH_SetInterruptHandler(&IT_TOUCH_CallBack);

    /****************************************************************************
     * Interrupt On Change: Interrupt Enable
     ***************************************************************************/
    IFS3bits.CNAIF = 0; //Clear CNAI interrupt flag
    IEC3bits.CNAIE = 1; //Enable CNAI interrupt
    IFS3bits.CNDIF = 0; //Clear CNDI interrupt flag
    IEC3bits.CNDIE = 1; //Enable CNDI interrupt
}

void __attribute__ ((weak)) SW1_CallBack(void)
{

}

void __attribute__ ((weak)) SW2_CallBack(void)
{

}

void __attribute__ ((weak)) SW3_CallBack(void)
{

}

void __attribute__ ((weak)) IT_TOUCH_CallBack(void)
{

}

void SW1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC3bits.CNAIE = 0; //Disable CNAI interrupt
    SW1_InterruptHandler = InterruptHandler; 
    IEC3bits.CNAIE = 1; //Enable CNAI interrupt
}

void SW2_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC3bits.CNAIE = 0; //Disable CNAI interrupt
    SW2_InterruptHandler = InterruptHandler; 
    IEC3bits.CNAIE = 1; //Enable CNAI interrupt
}

void SW3_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC3bits.CNAIE = 0; //Disable CNAI interrupt
    SW3_InterruptHandler = InterruptHandler; 
    IEC3bits.CNAIE = 1; //Enable CNAI interrupt
}

void IT_TOUCH_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC3bits.CNDIE = 0; //Disable CNDI interrupt
    IT_TOUCH_InterruptHandler = InterruptHandler; 
    IEC3bits.CNDIE = 1; //Enable CNDI interrupt
}

/* Interrupt service function for the CNAI interrupt. */
/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ( ( interrupt ) ) _CNAInterrupt (void)
{
    if(CNFAbits.CNFA7 == 1)
    {
        if(SW1_InterruptHandler != NULL) 
        { 
            SW1_InterruptHandler(); 
        }
        
        CNFAbits.CNFA7 = 0;  //Clear flag for Pin - SW1
    }
    
    if(CNFAbits.CNFA8 == 1)
    {
        if(SW2_InterruptHandler != NULL) 
        { 
            SW2_InterruptHandler(); 
        }
        
        CNFAbits.CNFA8 = 0;  //Clear flag for Pin - SW2
    }
    
    if(CNFAbits.CNFA9 == 1)
    {
        if(SW3_InterruptHandler != NULL) 
        { 
            SW3_InterruptHandler(); 
        }
        
        CNFAbits.CNFA9 = 0;  //Clear flag for Pin - SW3
    }
    
    // Clear the flag
    IFS3bits.CNAIF = 0;
}

/* Interrupt service function for the CNDI interrupt. */
/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ( ( interrupt ) ) _CNDInterrupt (void)
{
    if(CNFDbits.CNFD1 == 1)
    {
        if(IT_TOUCH_InterruptHandler != NULL) 
        { 
            IT_TOUCH_InterruptHandler(); 
        }
        
        CNFDbits.CNFD1 = 0;  //Clear flag for Pin - IT_TOUCH
    }
    
    // Clear the flag
    IFS3bits.CNDIF = 0;
}

