#include "msp430f5438.h"
#include "keyboard.h"
#include "lcd12864.h"
#include "string.h"
#include "rc522.h"
/*
unsigned char mKeyValueIndex[] = {0xFF, 0x31, 0x32, 0x33, 'e', // 1 2 3 4
                                     0x34,0x35, 0x36, 'e', // 5 6 7 8
                                     0x37, 0x38, 0x49, 'e',// 9 0 A B
                                     '.', 0x30, 'B', 0x46,// C D E F
                                    };
*/
int mKeyValueIndex[] = {11,1,2,3,17,4,5,6,16,7,8,9,15,12,0,13,14};
int KeyValue = 11;
uchar KeyIndex = 0x00;
long passwdE=0;
long password = 888888;
int D=0;
uchar m_nTestStatus = 0xFF;
uchar* xxx="¡ñ¡ñ¡ñ¡ñ¡ñ¡ñ";

// ï¿½ï¿½ï¿½Ì¶Ë¿Ú³ï¿½Ê¼ï¿½ï¿½

void keyb_init()
{
    P1IFG = 0;
    P2IFG = 0;
    P2DIR = 0x0F;            // ï¿½ï¿½ï¿½Ì¶Ë¿ï¿½ï¿½ï¿½ï¿½Ã£ï¿½P2.0-3 ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½P2.4-7 ï¿½ï¿½ï¿½ï¿½
    P2REN = 0xF0;
    P2OUT = 0xF0;                               //
    P2IES = 0xf0;                          // ï¿½ï¿½ï¿½ï¿½ï¿½Â½ï¿½ï¿½ï¿½ï¿½Ð¶ï¿½
    P2IE  = 0x00;                         // ï¿½ï¿½ï¿½ï¿½ï¿½Â½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½P2 ï¿½Ð¶ï¿½
    P1IE |= BIT0 + BIT2 + BIT4;
}

// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 4*4
// ï¿½ï¿½ï¿½ß£ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½  ï¿½ï¿½ï¿½ï¿½1-4,  ï¿½ï¿½ï¿½ï¿½1---P2.0  ï¿½ï¿½2---P2.1  ï¿½ï¿½3---P2.2ï¿½ï¿½4----P2.3
// ï¿½ï¿½ï¿½ß£ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½1-4,  ï¿½ï¿½ï¿½ï¿½1---P2.7 ï¿½ï¿½2---P2.6 ï¿½ï¿½3---P2.5 ï¿½ï¿½4---P2.4

unsigned char keyb_scan(void)
{
  unsigned char x = 0x00;
  unsigned char mP2IN[4];

  // É¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÐµÄ¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð·ï¿½Ê½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½//É¨ï¿½ï¿½ï¿½ï¿½ 1ï¿½ï¿½

  P2OUT  = 0xFF;
  P2OUT &= (~0x01);
  mP2IN[0] = P2IN;
  P2OUT = 0xFF;
  P2OUT &= (~0x02);
  mP2IN[1] = P2IN;

  P2OUT = 0xFF;
  P2OUT &= (~0x04);
  mP2IN[2] = P2IN;

  P2OUT = 0xFF;
  P2OUT &= (~0x08);
  mP2IN[3] = P2IN;

  if(((~(mP2IN[0] >> 4)) & 0x0F) != 0x00)
  {
    x = x + ((~(mP2IN[0] >> 4)) & 0x01) * 0x04;
    x = x + ((~(mP2IN[0] >> 5)) & 0x01) * 0x03;
    x = x + ((~(mP2IN[0] >> 6)) & 0x01) * 0x02;
    x = x + ((~(mP2IN[0] >> 7)) & 0x01) * 0x01;
    x = x + 0x00;
  }
  else if(((~(mP2IN[1] >> 4)) & 0x0F) != 0x00)
  {
    x = x + ((~(mP2IN[1] >> 4)) & 0x01) * 0x04;
    x = x + ((~(mP2IN[1] >> 5)) & 0x01) * 0x03;
    x = x + ((~(mP2IN[1] >> 6)) & 0x01) * 0x02;
    x = x + ((~(mP2IN[1] >> 7)) & 0x01) * 0x01;
    x = x + 0x04;
  }
  else if(((~(mP2IN[2] >> 4)) & 0x0F) != 0x00)
  {
    x = x + ((~(mP2IN[2] >> 4)) & 0x01) * 0x04;
    x = x + ((~(mP2IN[2] >> 5)) & 0x01) * 0x03;
    x = x + ((~(mP2IN[2] >> 6)) & 0x01) * 0x02;
    x = x + ((~(mP2IN[2] >> 7)) & 0x01) * 0x01;
    x = x + 0x08;
  }
  else if(((~(mP2IN[3] >> 4)) & 0x0F) != 0x00)
  {
    x = x + ((~(mP2IN[3] >> 4)) & 0x01) * 0x04;
    x = x + ((~(mP2IN[3] >> 5)) & 0x01) * 0x03;
    x = x + ((~(mP2IN[3] >> 6)) & 0x01) * 0x02;
    x = x + ((~(mP2IN[3] >> 7)) & 0x01) * 0x01;
    x = x + 0x0C;
  }
    return x;
}
 #pragma vector=PORT1_VECTOR

__interrupt void Port_1(void)
{
    if( P1IFG&BIT0 ){
      Clean(RowStart[1]);
      Clean(RowStart[2]);
      Clean(RowStart[3]);
      lcm_write_str(RowStart[0],"Ë¢¿¨°´Ò»ÃÜÂë°´¶þ",16);
    }
    if( P1IFG&BIT2 ){
      Clean(RowStart[1]);
      Clean(RowStart[2]);
      Clean(RowStart[3]);
      lcm_write_str(RowStart[1],"Ôª¼þËð»µÔÝ²»ÄÜÓÃ",16);
      //test();
      keyb_init();
    }
    if( P1IFG&BIT4 ){
          P1IE = 0;
          Clean(RowStart[1]);
          lcm_write_str(RowStart[1],"ÇëÊäÈëÃÜÂë",10);
          Clean(RowStart[2]);
          Clean(RowStart[3]);
          P2IE  = 0xF0;
          //P1OUT &= ~BIT2;
          //P1IFG &= ~BIT2;
          //P1IE |= BIT2;
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
  unsigned char mTmp;
  P2IE = 0x00;                          //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ø½ï¿½Ö¹ P2 ï¿½Ð¶ï¿½

  mTmp = P2IN & 0xF0;

  if(mTmp != 0xF0)
  {
    delay_ms(20); //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

    if((P2IN&0xF0) == mTmp)
    {
      KeyIndex = keyb_scan();
      KeyValue = mKeyValueIndex[KeyIndex];
      if( KeyValue == 16 ){             //È·¶¨
        D = 0;
        Clean(RowStart[2]);
        Clean(RowStart[3]);
        KeyValue = 0;
        if(passwdE == password)
        {
          Clean(RowStart[1]);
          lcm_write_str(RowStart[3],"ÃÜÂëÕýÈ·welcome",16);
          keyb_init();
          return;
        }
        else
        {
          lcm_write_str(RowStart[3],"ÃÜÂë´íÎóÖØÐÂÊäÈë",16);
        }
        passwdE = 0;
      }
      else
      if( KeyValue == 15 )
      {
          Clean(RowStart[1]);
          Clean(RowStart[2]);
          Clean(RowStart[3]);
          lcm_write_str(RowStart[3],"ÄúÒÑÍË³öÃÜÂëÄ£Ê½",16);
          keyb_init();
          return;
      }
      else
      {
        if( KeyValue == 17 ){                   //Çå³ýÊäÈë
          D = -1;
          Clean(RowStart[2]);
          Clean(RowStart[3]);
          passwdE = 0;
          KeyValue = 0;
        }
        if( D < 6 )
        {
          D++ ;
          lcm_write_str(RowStart[2],xxx,2*D);
          passwdE=passwdE*10+KeyValue;
          //lcm_write_long(RowStart[3],passwdE);
        }
      }
    }
  }
  KeyValue = 0 ;

  P2DIR = 0x0F;
  P2REN = 0xF0;
  P2OUT = 0xF0;
  P2IFG = 0x00;
  P2IE  = 0xF0;            //ï¿½ï¿½ï¿½ï¿½ï¿½Ð¶Ï±ï¿½Ö¾  ï¿½ï¿½ï¿½ï¿½ï¿½Ð¶ï¿½

}
