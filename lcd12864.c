//LCM显示处理程序
#include "msp430f5438.h"
#include "lcd12864.h"
uchar RowStart[]={0x80,0x90,0x88,0x98};
// 液晶屏初始化
extern void lcm_init(void)
{
    delay_ms(6);
    P1DIR |= 0xC0;
    lcm_write_command(0x30); // 功能设定
    delay_ms(3);
    lcm_write_command(0x30); // 功能设定
    delay_ms(3);
    lcm_write_command(0x0c); // 显示开关
    delay_ms(3);
    lcm_write_command(0x01); // 清除屏幕
    delay_ms(3);
    lcm_write_command(0x06); // 进入设定点
    delay_ms(3);
}
void lcm_write_command(uchar lcdcmd){
    uchar tmp,i;

    SET_LCM_RW;

    for( i = 0 ; i < 5 ; i ++ ){
        CLR_LCM_E;
        SET_LCM_E;
    }

    CLR_LCM_RW;
    CLR_LCM_E;
    SET_LCM_E;
    CLR_LCM_E;
    SET_LCM_E;
    CLR_LCM_E;
    SET_LCM_E;

    tmp = lcdcmd & 0xf0 ;
    i = 128 ;

    do{
        CLR_LCM_E;
        if ( tmp & i ) SET_LCM_RW;
            else CLR_LCM_RW;
        SET_LCM_E;
        i >>= 1;
    }while ( i );

    CLR_LCM_E;
    delay_ms(3);

    tmp = ( lcdcmd & 0x0f ) << 4 ;
    i = 128 ;
    do{
        CLR_LCM_E;
        if ( tmp & i ) SET_LCM_RW;
            else CLR_LCM_RW;
        SET_LCM_E;
        i >>= 1;
    }while ( i );

    CLR_LCM_E;
    delay_ms(3);

}
void lcm_write_data(uchar lcdcmd){
    uchar tmp,i;

    SET_LCM_RW;

    for( i = 0 ; i < 5 ; i ++ ){
        CLR_LCM_E;
        SET_LCM_E;
    }

    CLR_LCM_RW;
    CLR_LCM_E;
    SET_LCM_E;
    SET_LCM_RW;
    CLR_LCM_E;
    SET_LCM_E;
    CLR_LCM_RW;
    CLR_LCM_E;
    SET_LCM_E;

    tmp = lcdcmd & 0xf0 ;
    i = 128 ;

    do{
        CLR_LCM_E;
        if ( tmp & i ) SET_LCM_RW;
            else CLR_LCM_RW;
        SET_LCM_E;
        i >>= 1;
    }while ( i );

    CLR_LCM_E;
    //delay_ms(3);

    tmp = ( lcdcmd & 0x0f ) << 4 ;
    i = 128 ;
    do{
        CLR_LCM_E;
        if ( tmp & i ) SET_LCM_RW;
            else CLR_LCM_RW;
        SET_LCM_E;
        i >>= 1;
    }while ( i );

    CLR_LCM_E;
    //delay_ms(3);

}

extern void ClearScreen(){
    lcm_write_command( 0x01 );
    delay_ms(3);
}

extern void Clean( uchar _Start ){
    uchar* blank = "                " ;
    lcm_write_str( _Start , blank , 16 );
}

extern void lcm_write_str(uchar _StartPosition,uchar* _String,uchar _len){
    uchar tmp ;
    if( ( _StartPosition == 0x90 ) && ( _String[0] == 0x20 ) )
        tmp = 0x00 ;
    for( tmp = 0; tmp < _len / 2 ; tmp++ ){
        if( _String[tmp*2] == 0x00 ) _String[tmp*2] = 0x20 ;
        if( _String[tmp*2+1] == 0x00 ) _String[tmp*2+1] = 0x20 ;
        lcm_write_command( _StartPosition + tmp ) ;
        lcm_write_data( _String[tmp*2] );
        lcm_write_data( _String[tmp*2+1] );
    }
}

extern void lcm_write_chr(uchar _StartPosition,uchar _String){
//        if( _String[tmp*2] == 0x00 ) _String[tmp*2] = 0x20 ;
//        if( _String[tmp*2+1] == 0x00 ) _String[tmp*2+1] = 0x20 ;
        lcm_write_command( _StartPosition ) ;
        lcm_write_data( _String );
//        lcm_write_data( _String[tmp*2+1] );
}

extern void lcm_write_double(uchar row,double num){
    uchar k[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39} ;
    long tmp = (long)(num * 1000) ;
    uchar queue_tmp[2][10] ;
    int i = 0 ;
    uchar len = 0 ;
    while( tmp | i <= 4 ){
        if( 3 == i ) queue_tmp[0][ i++ ] = '.' ;
          else{
            queue_tmp[0][i++] = k[ (uchar)( tmp % 10 ) ] ;
            tmp /= 10 ;
          }
    }
   for( --i; i >= 0 ; i-- )
     queue_tmp[1][ len++ ] = queue_tmp[0][ i ] ;
   queue_tmp[1][ len ] = '\0' ;
   lcm_write_str( row , queue_tmp[1] , len+1 );
}

extern void lcm_write_long(uchar row,long num){
    uchar k[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39} ;
    long tmp = num ;
    uchar queue_tmp[2][16] ;
    int i = 0 ;
    uchar len = 0 ;
    while( tmp ){
        queue_tmp[0][i++] = k[ (uchar)( tmp % 10 ) ] ;
        tmp /= 10 ;
    }
   for( --i; i >= 0 ; i-- )
     queue_tmp[1][ len++ ] = queue_tmp[0][ i ] ;
   queue_tmp[1][ len ] = '\0' ;
   if ( len % 2 ) len++ ;
   lcm_write_str( row , queue_tmp[1] , len );
}
