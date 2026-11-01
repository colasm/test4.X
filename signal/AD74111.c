
#include "AD74111.h"
#include <xc.h>
#include "../spi/client/spi2.h"
#include "../mcc_generated_files/system/pins.h"
#include <stdbool.h>
#include <libpic30.h>


#define PUTCMD(ad,val) (spi->WordWrite(((ad<<11)+val)|0x8000))
#define PUTDATA(val) (spi->WordWrite(val))

static const struct SPI_CLIENT_INTERFACE *spi;

void RX_Callback(void);

void AD74111Init(const struct SPI_CLIENT_INTERFACE *host){

    spi = host;
    volatile uint16_t dummy;
    // Reset IC (at this stage, SPI is down so act as I/O pins)
    TRISDbits.TRISD8 = 0;
    AD_RESET_SetLow();  
    _LATD8 = 0;             // place AD in Master
   
    // Fill the spi FIFO with AD74111 initialization (enhanced mode is already on)
    PUTCMD(0,0x0000);   //First write preparation : 
    PUTDATA(0);
    
    
    // SPI is ready for first frame
    __delay_us(1);          // Should be down for 10ns    
    AD_RESET_SetHigh();
   
    // should be finish within 3072 MCLKs after Reset start) : 250�s (50k �C cycles)
    // Default configuration is Normal sync, Mixed mode, 16 bits, 128 DCLK/Ts, Master 
    spi->Open(AD74111);

    // wait for 2 words to be sent
    while(!spi->IsTxOk());

    PUTCMD(1,0x0005);  //First write preparation : 00 0000 0101 : MCLK divided by 4
    PUTDATA(0);
    // wait for 2 words to be sent
    while(!spi->IsTxOk());

    PUTCMD(0,0x07C);        //00 0011 1110 : ADC off, DAC on, REF on
    PUTDATA(0);

    //SPI2_SetInterruptMode(true);
    spi->SetRXInterruptHandler(RX_Callback);
    // From now, commands are undertaken on TX empty interrupt 
    
}



int16_t tabSin[]={0x0000,0x0EDC,0x1D84,0x2BC6,0x3971,0x4655,0x5246,0x5D19,0x66AB,0x6ED9,
                  0x7587,0x7A9E,0x7E0D,0x7FC7,0x7FC7,0x7E0D,0x7A9E,0x7587,0x6ED9,0x66AB,
                  0x5D19,0x5246,0x4655,0x3971,0x2BC6,0x1D84,0x0EDC,0x0000,0xF124,0xE27C,
                  0xD43A,0xC68F,0xB9AB,0xADBA,0xA2E7,0x9955,0x9127,0x8A79,0x8562,0x81F3,
                  0x8039,0x8039,0x81F3,0x8562,0x8A79,0x9127,0x9955,0xA2E7,0xADBA,0xB9AB,
                  0xC68F,0xD43A,0xE27C,0xF124};

const uint16_t TABLENGTH=sizeof(tabSin)/sizeof(int16_t);
extern uint16_t state;


/*void RX_Callback(){
    int16_t data = 0;
    static int16_t index = 0;
    uint16_t dummyControl;
    dummyControl = SPI2_Client.WordRead();
    data = SPI2_Client.WordRead();
    SPI2_Client.WordWrite(0); // ask for a read if no command to send 
    SPI2_Client.WordWrite(data);   //tabSin[index]
}*/



