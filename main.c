#include "msp430f5438.h"
#include "lcd12864.h"
#include "delay.h"
//#include "keyboard.h"

void main(){
    WDTCTL = WDTPW + WDTHOLD ;
    lcm_init();
    //keyb_init();
    lcm_write_str( RowStart[ 0 ] , "welcome" , 8 ) ;
    lcm_write_str( RowStart[ 0 ] + 4, "MSP430" , 6 ) ;
    lcm_write_double(RowStart[1],13.875);
   // __bis_SR_register(GIE);                 // enable interrupts
    //_EINT();
    while( 1 );
}
