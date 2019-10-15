#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define DELAY_TIME 6
#define SHOW_LOOP	150

sbit DAT = P3^0;				// 74HC164 ��������˿�
sbit CLK = P3^1;				// 74HC164 ʱ������˿�

// ��������ܶ�ѡ(0~9��NULL)
uchar code duan[]={0x81,0xD7,0xC8,0xC2,0x96,0xA2,0xA0,0xC7,0x80,0x82,0xff};

// ����ѧ��
// uchar STUNUM[12]=201723010237;

// ������ʾѧ�ŵĶ�ά����
uchar code student[][4]={{10,10,10, 2}, 
												 {10,10, 2, 0},
												 {10, 2, 0, 1},
												 { 2, 0, 1, 7},
												 { 0, 1, 7, 2},
												 { 1, 7, 2, 3},
												 { 7, 2, 3, 0},
												 { 2, 3, 0, 1},
												 { 3, 0, 1, 0},
												 { 0, 1, 0, 2},
												 { 1, 0, 2, 3},
												 { 0, 2, 3, 7},
												 { 2, 3, 7,10},
												 { 3, 7,10,10},
												 { 7,10,10,10},
												 {10,10,10,10}};
//uchar code student[][4]={
//	{duan[10],duan[10],duan[10], STUNUM[0]}, 
//	{duan[10],duan[10], STUNUM[0], STUNUM[1]},
//	{duan[10], STUNUM[0], STUNUM[1], STUNUM[2]},
//	{STUNUM[0], STUNUM[1], STUNUM[2], STUNUM[3]},
//	{STUNUM[1], STUNUM[2], STUNUM[3], STUNUM[4]},
//	{STUNUM[2], STUNUM[3], STUNUM[4], STUNUM[5]},
//	{STUNUM[3], STUNUM[4], STUNUM[5], STUNUM[6]},
//	{STUNUM[4], STUNUM[5], STUNUM[6], STUNUM[7]},
//	{STUNUM[5], STUNUM[6], STUNUM[7], STUNUM[8]},
//	{STUNUM[6], STUNUM[7], STUNUM[8], STUNUM[9]},
//	{STUNUM[7], STUNUM[8], STUNUM[9], STUNUM[10]},
//	{STUNUM[8], STUNUM[9], STUNUM[10], STUNUM[11]},
//	{STUNUM[9], STUNUM[10], STUNUM[11],duan[10]},
//	{STUNUM[10], STUNUM[11],duan[10],duan[10]},
//	{STUNUM[11],duan[10],duan[10],duan[10]},
//	{duan[10],duan[10],duan[10],duan[10]}
//};
										 


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
*  �������ƣ�74HC164����Byte���ݺ���
*  ���ڣ�2019-9-29
*  ������ZhangHJ
*  ˵����74HC164��λ�Ĵ�������һ�ֽ����ݷ����Ĵ���
***********************************************************/
void SendByte_74HC164(uchar byte)
{
	uchar num,c;
	num=duan[byte];
	for(c=0; c<8; c++)
	{
		DAT=num&0x01;		// P3^0 --> 0000 000x
		CLK=0;					// ����һ��������
		CLK=1;
		num>>=1;				// �����ݷ��͵��Ĵ���
	}
}




/**********************************************************
*  �������ƣ�����֡��ʾ����
*  ���ڣ�2019-10-15
*  ������ZhangHJ
*  ˵����ʵ��4������ܹ�����ʾѧ�ŵ�Ч��
* 			 ��������ŵ͵�ƽ��Ч,���ȹر�λѡ�ź�,Ȼ����Ĵ�����������(������ѡ),
*				 ����λѡ���Ʋ���ʱһ��ʱ������ʾ����,���ر�λѡ�ź�����.
***********************************************************/
//void test_light_byte1()											// 2
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte2()											// 20
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte3()											// 201
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte4()											// 2017
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte5()											// 0172
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte6()											// 1723
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte7()											// 7230
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte8()											// 2301
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte9()												// 3010
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte10()												// 0102
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte11()												// 1023
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(1);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte12()												// 0237
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(0);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xfe;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte13()													// 237
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(2);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xfd;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte14()													// 37
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(3);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//	
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xfb;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}
//void test_light_byte15()													// 7
//{
//	P1 |= 0x0f;							// �ص�λѡ
//	SendByte_74HC164(7);		// ������ѡ
//	P1 &= 0xf7;							// ����λѡ
//	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
//	P1 |= 0x0f;							// �ص�λѡ
//}

// ������ʾѧ��
//void main()
//{
//	uint i;
//	while(1)
//	{
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte1();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte2();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte3();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte4();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte5();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte6();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte7();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte8();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte9();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte10();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte11();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte12();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte13();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte14();
//		//delay_ms(5);
//		for(i=0;i<SHOW_LOOP;i++)
//		test_light_byte15();
//		delay_ms(100);
//	}
//}



/**********************************************************
*  �������ƣ��������ʾ����
*  ���ڣ�2019-10-15
*  ������ZhangHJ
*  ˵���������������ʾ����
* 			 ��������ŵ͵�ƽ��Ч,���ȹر�λѡ�ź�,Ȼ����Ĵ�����������(������ѡ),
*				 ����λѡ���Ʋ���ʱһ��ʱ������ʾ����,���ر�λѡ�ź�����.
***********************************************************/
void test_light(uchar num[])
{
	P1 |= 0x0f;							// �ص�λѡ
	SendByte_74HC164(num[0]);		// ������ѡ
	P1 &= 0xf7;							// ����λѡ
	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
	P1 |= 0x0f;							// �ص�λѡ
	
	SendByte_74HC164(num[1]);		// ������ѡ
	P1 &= 0xfb;							// ����λѡ
	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
	P1 |= 0x0f;							// �ص�λѡ
	
	SendByte_74HC164(num[2]);		// ������ѡ
	P1 &= 0xfd;							// ����λѡ
	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
	P1 |= 0x0f;							// �ص�λѡ
	
	SendByte_74HC164(num[3]);		// ������ѡ
	P1 &= 0xfe;							// ����λѡ
	delay_ms(DELAY_TIME);		// ��ʱ��ʾ
	P1 |= 0x0f;							// �ص�λѡ
}



// ͨ����ά������ʾ��������
void main()
{
	uint i,delay;
	while(1)
	{
		for(i=0;i<16;i++)
		{
			for(delay=120;delay>0;delay--)
				test_light(student[i]);
		}
	}
}






