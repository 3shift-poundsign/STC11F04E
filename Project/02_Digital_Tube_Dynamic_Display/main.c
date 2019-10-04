/**********************ʵ����Գ���************************
*  ƽ̨��Keil U5 + STC11F04E
*  ���ƣ�����ܶ�̬��ʾʵ��
*  ���ڣ�2019-9-30
*  ������ZhangHJ
*  ˵��������ܾ�̬��ʾ
***********************************************************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
#define DELAY_TIME 10
#define ON 0
#define OFF 1

sbit DAT=P3^0;			// 74HC164 ��������
sbit CLK=P3^1;			// 74HC164 ʱ������
//sbit DP=P3^7;			// С����
//sbit DP1=P3^5;
sbit DPY0 = P1^0;		// ����λѡ
sbit DPY1 = P1^1;
sbit DPY2 = P1^2;
sbit DPY3 = P1^3;
sbit KEY = P3^2;		// INT0 ����,����Ϊ�͵�ƽ

// ����ܶ�ѡ����	����0~9��ȫ��
uchar code tab[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82,0xff};
// �����λѡ����	ȫ��Ͷ���3~0
uchar code wei[]={0xf0,0xf8,0xf4,0xf2,0xf1};



/**********************************************************
*  �������ƣ��;�����ʱ����
*  ���ڣ�2019-9-7
*  ������ZhangHJ
*  ˵����Ƕ��ѭ����ʱ
***********************************************************/
void delay_ms(unsigned int mstime)
{
	int i,j;
	for(i=mstime; i>=0; i--)
		for(j=112; j>=0; j--);
}



/**********************************************************
*  �������ƣ�74HC164����Byte����
*  ���ڣ�2019-9-29
*  ������ZhangHJ
*  ˵����74HC164��λ�Ĵ�������һ�ֽ����ݷ����Ĵ���
***********************************************************/
void SendByte_74HC164(uchar byte)
{
	uchar num,c;
	num=tab[byte];
	for(c=0; c<8; c++)
	{
		DAT=num&0x01;		// P3^0 --> 0000 000x
		CLK=0;					// ����һ��������
		CLK=1;
		num>>=1;				// �����ݷ��͵��Ĵ���
	}
}



/**********************************************************
*  �������ƣ���λ��������ܶ�̬��ʾ����
*  ���ڣ�2019-9-30
*  ������ZhangHJ
*  ˵����ʵ��4���������ʾ 4321 ��Ч��
* 			 ��������Ÿߵ�ƽ��Ч,�������ø�λ��ѡ�ź�,Ȼ����Ĵ�����������
*				 ��ʱһ��ʱ��ʵ��������ʾ,��������ѡ�ź�����.
***********************************************************/
void test_light_bit()
{
		DPY0 = ON;
		DPY1 = OFF;
		DPY2 = OFF;
		DPY3 = OFF;
		SendByte_74HC164(1);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
	
		DPY0 = OFF;
		DPY1 = ON;
		DPY2 = OFF;
		DPY3 = OFF;
		SendByte_74HC164(2);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
	
		DPY0 = OFF;
		DPY1 = OFF;
		DPY2 = ON;
		DPY3 = OFF;
		SendByte_74HC164(3);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
		
		DPY0 = OFF;
		DPY1 = OFF;
		DPY2 = OFF;
		DPY3 = ON;
		SendByte_74HC164(4);
		delay_ms(DELAY_TIME);
		SendByte_74HC164(10);
}



/**********************************************************
*  �������ƣ����ֽڿ�������ܶ�̬��ʾ����
*  ���ڣ�2019-9-30
*  ������ZhangHJ
*  ˵����ʵ��4���������ʾ 1234 ��Ч��
* 			 ��������ŵ͵�ƽ��Ч,���ȹر�λѡ�ź�,Ȼ����Ĵ�����������(������ѡ),
*				 ����λѡ���Ʋ���ʱһ��ʱ������ʾ����,���ر�λѡ�ź�����.
***********************************************************/
void test_light_byte()
{
		P1 |= 0x0f;							// �ص�λѡ
		SendByte_74HC164(1);		// ������ѡ
		P1 &= 0xf7;							// ����λѡ
		delay_ms(DELAY_TIME);		// ��ʱ��ʾ
		P1 |= 0x0f;							// �ص�λѡ
		
		SendByte_74HC164(2);
		P1 &= 0xfB;
		delay_ms(DELAY_TIME);
		P1 |= 0x0f;
		
		SendByte_74HC164(3);
		P1 &= 0xfD;
		delay_ms(DELAY_TIME);
		P1 |= 0x0f;

		SendByte_74HC164(4);
		P1 &= 0xfe;
		delay_ms(DELAY_TIME);
}



//���������ܣ�����״̬��ʾ1234,����INT0����ʱ��ʾ4321
void main()
{
	while(1)
	{
		if(KEY == 0)
		{
			delay_ms(20);
			while(KEY == 0)				// INT0����������
			{
				test_light_bit();		// ��ʾ4321
			}
		}
		test_light_byte();			// ��ʾ1234
	}
}









