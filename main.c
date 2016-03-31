#include "msp430x54x.h"
#include "lcd12864.h"
#include "delay.h"
#include "keyboard.h"

void main(){
    double sum = 0 , weight = 0 ;
    WDTCTL = WDTPW + WDTHOLD ;
    lcm_init();
    keyb_init();
    qp_init();
    weight_init();
    lcm_write_str( RowStart[ 0 ] + 1 , "���ܵ��ӳ�" , 10 ) ;
    lcm_write_str( RowStart[ 1 ] , "����:" , 6 ) ;
    lcm_write_str( RowStart[ 2 ] , "����:" , 6 ) ;
    lcm_write_str( RowStart[ 3 ] , "�ܼ�:" , 6 ) ;
    __bis_SR_register(GIE);                 // enable interrupts
    _EINT();
    while( 1 ){
      weight = 40 * fabs( ave_weight() -qp );
      guozai(weight + 40*qp);
      sum = Price_F * weight ;
      lcm_write_double( RowStart[ 2 ] + 3 , weight ) ;
      delay_ms(50);
      Clean( RowStart[3] + 3 );
      lcm_write_double( RowStart[ 3 ] + 3 , sum ) ;
      delay_ms(50);
    }
}
