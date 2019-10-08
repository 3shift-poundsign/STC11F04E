/****************************************************
*
* ESP8266 ATָ�����
*
*****************************************************/

#include<reg52.h>
#define uchar unsigned char		//�궨��һ���޷��ŵ�char����
#define uint unsigned int			//�궨��һ���޷��ŵ�int����

//����һ�ֽ�
void sendByte(uchar b)
{
  SBUF = b;
  while(!TI);
  TI=0;
}

//�����ַ���
void sendString(uchar *s)
{
  while(*s != '\0')	//�ַ���Ĭ�Ͻ�β'\0'���Դ����ж��ַ����Ľ���
  {
    sendByte(*s);
    s++;
  }
}

//��ʼ��ESP8266WiFiģ��
void initEsp()
{
  uint a;
  SCON = 0x50;    //8λ���ݣ��ɱ䲨����
  TMOD = 0x20;    //���ö�ʱ��1λ16λ�Զ���װģʽ
  TL1 = 0xfd;     //���ö�ʱ����ֵ��������Ϊ9600
  TH1 = 0xfd;
  ET1 = 0;        //��ֹ��ʱ��1�ж�
  TR1 = 1;        //������ʱ��1
  EA = 1;

  for (a=0; a<50000; a++);		//��ʱ���룬��ģ����ʱ������
  sendString("AT+CWMODE=2\n");	//����ΪsoftAP��station����ģʽ

  //WiFi�ȵ㲻��ͨ���������ã���ʹ�ô������ֽ������ã������öϵ粻��ʧ
  for (a=0; a<20000; a++);
  sendString("AT+CWSAP='1A308','tensorflow',1,3\n"); //����WiFi�ȵ�

  for (a=0; a<50000; a++);    
  sendString("AT+CIPMUX=1\n"); //����������

  for (a=0; a<20000; a++);
  sendString("AT+CIPSERVER=1,333\n");//����server���˿�Ϊ333

  for (a=0; a<20000; a++);
  sendString("AT+CIPSTO=50\n");     //��������ʱʱ������

  RI=0;
  ES=1;   //��ʼ����ɣ����п��жϴ�
}

//������  
void  main()  
{  
  initEsp();
}      
