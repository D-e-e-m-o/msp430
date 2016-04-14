#include "msp430f5438.h"
#include "lcd12864.h"
#include "delay.h"
#include "keyboard.h"
#include "rc522.h"

extern uchar RowStart[];
void main(){
    int rcStatus;
    uchar* tagType, rcSnr, rcStr;
    WDTCTL = WDTPW + WDTHOLD ;
    lcm_init();
    keyb_init();
    lcm_write_str( RowStart[ 0 ] , "welcome!" , 8 ) ;
    lcm_write_str( RowStart[ 0 ] + 4, "MSP430" , 6 ) ;
    init_rc522();
    rcStatus = PcdRequest(PICC_REQALL, tagType);
    rcStatus = PcdAnticoll(rcSnr);
    rcStatus = PcdSelect(rcSnr);
    rcStatus = PcdAuthState(PICC_AUTHENT1A, 1, passWd, rcSnr);
    rcStatus = PcdRead(1, rcStr);
    //lcm_write_double(RowStart[1],13.7555);
    //lcm_write_double(RowStart[1],KeyValue);
    __bis_SR_register(GIE);                 // enable interrupts
    _EINT();
    while( 1 );
}
