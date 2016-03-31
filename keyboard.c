#include 'keyboard.h'
/*
unsigned char mKeyValueIndex[] = {0xFF, 0x31, 0x32, 0x33, 'e', // 1 2 3 4
                                     0x34,0x35, 0x36, 'e', // 5 6 7 8
                                     0x37, 0x38, 0x49, 'e',// 9 0 A B
                                     '.', 0x30, 'B', 0x46,// C D E F
                                    };
*/
int mKeyValueIndex[] = {11,1,2,3,11,4,5,6,11,7,8,9,11,12,0,13,14};
int KeyValue = 11;
unsigned char KeyIndex = 0x00;
int w=0;
int x=1;

long Price = 0;
long zhengshu =1;
long xiaoshu = 0;
double Xiaoshu = 0;
double Price_F = 0;
unsigned char m_nTestStatus = 0xFF;

// ���̶˿ڳ�ʼ��
void Set_Price(void);
void keyb_init()
{
    P2DIR = 0x0F;            // ���̶˿����ã�P2.0-3 ������P2.4-7 ����
    P2REN = 0xF0;
    P2OUT = 0xF0;                               //
    P2IES = 0xF0;                          // �����½����ж�
    P2IE  = 0x00;                         // �����½�������P2 �ж�
    P1IE |= BIT2;
}

// �������� 4*4
// ���ߣ� ��������  ����1-4,  ����1---P2.0  ��2---P2.1  ��3---P2.2��4----P2.3
// ���ߣ� �������� ����1-4,  ����1---P2.7 ��2---P2.6 ��3---P2.5 ��4---P2.4

unsigned char keyb_scan(void)
{
  unsigned char x = 0x00;
  unsigned char mP2IN[4];

  // ɨ���������еļ������з�ʽ��������������������//ɨ���� 1��

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
    if( P1IFG&BIT2 ){
          P1IE = 0;
          //lcm_write_str(RowStart[0],"���ۣ�",6);
          Clean( RowStart[1] + 3 );
          //Clean( RowStart[2] + 6 );
          _EINT();
          P2IE  = 0xF0;
          Price = 0;
          Price_F = 0 ;
          Xiaoshu = 0 ;
          Set_Price();
          P1OUT &= ~BIT2;
          P1IFG &= ~BIT2;
          P1IE |= BIT2;
    }
    if( P1IFG&BIT0 ){
          qupi();
    }
}

void Set_Price(void)
{

  for(;KeyValue!=14;)
  {
  }

}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
  unsigned char mTmp;
  P2IE = 0x00;                          //���������ؽ�ֹ P2 �ж�

  mTmp = P2IN & 0xF0;

  if(mTmp != 0xF0)
  {
    delay_ms(20); //������

    if((P2IN&0xF0) == mTmp)
    {
      KeyIndex = keyb_scan();
      KeyValue = mKeyValueIndex[KeyIndex];    //��������ֵ���浽����
      m_nTestStatus = KeyValue;
      if(KeyValue==12)
      {
      zhengshu=0;

      }

      else if(KeyValue==13)
       {
       Clean( RowStart[1] + 3 );
       w=0;
       Price=0;
       x=1;
       zhengshu=1;
         }


        else if(KeyValue==14)
  {
    P2IE  = 0x00;
    P1IE |= BIT0 + BIT1 ;
    Clean( RowStart[2] + 3 );
    Clean( RowStart[3] + 3 );
    return;
  }
       else if(KeyValue==11)
         Price_F=Price_F;

      else if(zhengshu)
      { Price=10*Price+KeyValue;
        Price_F=Price;
        lcm_write_double(RowStart[1] + 3,(double)Price);
      w++;
      }
       else if(zhengshu==0)
      { Xiaoshu=KeyValue;
      {
        for(int j=0;j<x;j++)

         Xiaoshu/=10;}
        Price_F+=Xiaoshu;
      lcm_write_double(RowStart[1] + 3,Price_F);
      x++;
      }

    }
    }

  KeyValue = 11 ;
  P2DIR = 0x0F;
  P2REN = 0xF0;
  P2OUT = 0xF0;
  P2IFG = 0x00;
  P2IE  = 0xF0;            //�����жϱ�־  �����ж�

}
