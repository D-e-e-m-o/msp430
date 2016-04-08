#ifndef MSP430_LCD12864_H_
#define MSP430_LCD12864_H_

#define uint  unsigned int
#define uchar unsigned char
#define SET_LCM_RW P1OUT|=0x40
#define CLR_LCM_RW P1OUT&=(~0x40)
#define SET_LCM_E P1OUT|=0x80
#define CLR_LCM_E P1OUT&=(~0x80)
//LCM---DAT P1.6
//LCM---CLK P1.7

void lcm_init(void);
void lcm_write_str(uchar _StartPosition,uchar* _String,uchar _Len);
void lcm_write_chr(uchar _StartPosition,uchar _String);
void lcm_write_double(uchar _StartPosition,double _Num);
void lcm_write_long(uchar _StartPosition,long _Num);
void ClearScreen(void);
void Clean(uchar _StartPosition);
void lcm_write_data(uchar lcddata);
void lcm_write_command(uchar lcdcmd);

void delay_ms(uint);

#endif
