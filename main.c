#include "msp430f5438.h"
#include "lcd12864.h"
#include "delay.h"
#include "keyboard.h"
#include "rc522.h"


extern uchar RowStart[];

void main(){
    WDTCTL = WDTPW + WDTHOLD ;
    lcm_init();
    keyb_init();
    lcm_write_str( RowStart[ 0 ] , "welcome!" , 8 );
    /*
    uchar rcStatus = 0;
    uchar passWd[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uchar tagType[2], rcSnr[4], rcStr[4];
    init_rc522();
    while( ( rcStatus = PcdRequest(PICC_REQALL, tagType) ) != MI_OK );
    while( ( rcStatus = PcdAnticoll(rcSnr) ) != MI_OK );
    while( ( rcStatus = PcdSelect(rcSnr) ) != MI_OK );
    while( ( rcStatus = PcdAuthState(PICC_AUTHENT1A, 1, passWd, rcSnr) ) != MI_OK );
    while( ( rcStatus = PcdRead(1, rcStr) ) != MI_OK );
    */
    __bis_SR_register(GIE);                 // enable interrupts
    _EINT();
    while( 1 );
}
