#include "dsp.h"
#include <xc.h>

int32_t __attribute__((section("taps"),aligned(256),space(ymemory))) taps[FILTER_LENGTH];

void initCyclicBuffers(void){
    // todo : disable interrupt nesting to avoid probs with modcon...
    MODCONbits.XWM = 8;
    MODCONbits.YWM = 10;
    YMODSRT = (int32_t) taps;
    YMODEND = ((int32_t) taps)+ 4*FILTER_LENGTH-1;
    XMODSRT = (int32_t) coeffs;
    XMODEND = ((int32_t) coeffs)+ 4*FILTER_LENGTH-1;
}
