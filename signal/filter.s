.include "xc.inc"

 .equ FILTER_LENGTH,57 
    ; fs=11.025k, fc = [1200 2300], fp =[1500 1800] , Ap = 1, Ac = 30
    .global _coeffs
    .section coeffs,xmemory,align(256)
    _coeffs:
        .long 0x004F9068,0xFF775EA9,0xFEB1E23F,0xFF0992A3,0x008CEFEA,0x01E6FF66
	.long 0x01A204EE,0xFFD7A880,0xFE435CB5,0xFE63F561,0xFFC682BA,0x00A3002D
	.long 0x00310D3C,0xFFC0606E,0x00E3287A,0x02C2A386,0x025C32F8,0xFE3A778B
	.long 0xF9804F1B,0xF9CABFE6,0x00FC7BC1,0x09992CA2,0x0AE1F8A8,0x01C181C6
	.long 0xF55601FB,0xF13FB1B2,0xFA585440,0x09225C10,0x10410410,0x09225C10
	.long 0xFA585440,0xF13FB1B2,0xF55601FB,0x01C181C6,0x0AE1F8A8,0x09992CA2
	.long 0x00FC7BC1,0xF9CABFE6,0xF9804F1B,0xFE3A778B,0x025C32F8,0x02C2A386
	.long 0x00E3287A,0xFFC0606E,0x00310D3C,0x00A3002D,0xFFC682BA,0xFE63F561
	.long 0xFE435CB5,0xFFD7A880,0x01A204EE,0x01E6FF66,0x008CEFEA,0xFF0992A3
	.long 0xFEB1E23F,0xFF775EA9,0x004F9068

	
    
    
.data
    .global ptaps
    ptaps: .long _taps

    .global _RX_Callback
;.text
;    ; w0 to w7 can be used
;    ; without any backup but we are not entering into an interrupt so here, 
;    ; not sure that these register are not used by the context
;    _RX_Callback:
;    push MODCON
;    push w8
;    push w10
;    
;    bset MODCON,#YMODEN
;    bset MODCON,#XMODEN
;    
;    mov.l ptaps,w10
;    mov.l #_coeffs,w8
;    
;    ; state
;    mov SPI2BUF,w0
;    ; data
;    mov SPI2BUF,w1
;    sl w1,#16,w1
;    mov.l w1,[w10]
;    
;    ; application du filtrage
;    clr A
; 
;    repeat #FILTER_LENGTH-2
;    mac [w8]+=4,[w10]+=4,A
;    mac [w8],[w10],A
;    sac.l A,w1
;    
;    ; écriture registre DAC volume
;    mov #0xB000,w2  
;    mov _volume,w3
;    mov #33,w0
;    muluu.w w3,w0,w3
;    mov #0x3FF,w0
;    com w3,w3
;    and w3,w0,w3
;    add w2,w3,w3
;    
;    ;stat
;    mov w3,SPI2BUF
;    ;data
;    mov w1,SPI2BUF
;   
;    mov.l w10,ptaps
;    
;    pop w10
;    pop w8
;    pop MODCON
;    return
    
    
    
    .text
    ; w0 to w7 can be used
    ; without any backup but we are not entering into an interrupt so here, 
    ; not sure that these register are not used by the context
    _RX_Callback:
    push MODCON
    push w8
    push w10
    

    bset MODCON,#YMODEN
    bset MODCON,#XMODEN


    mov.l ptaps,w10
    mov.l #_coeffs,w8

    clr.l w1
    ; state
    mov SPI2BUF,w0
    ; data
    mov SPI2BUF,w1
    
     sl.l w1,#16,w1
     mov.l w1,[w10]     ;corrigé en .l


      ; application du filtrage
    clr A
 
    repeat #FILTER_LENGTH-2
    mac.l [w8]+=4,[w10]+=4,A
    mac.l [w8],[w10],A
    sac.l A,w1

    mov #0,w3
    ;stat
    mov w3,SPI2BUF
    ;data
    ; penser à redécaler le contenu à droite
    mov w1,SPI2BUF

    mov.l w10,ptaps
    pop w10
    pop w8
    pop MODCON   
    return

    