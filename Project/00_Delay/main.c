#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
sbit DP = P3^7;							// 波形测试引脚
/**********************************************************
*  函数名称：1ms高精度延时函数(1.004ms)(11.0592MHz)
*  日期：2019-10-4
*  姓名：ZhangHJ
*  说明：嵌套循环延时,延时1.004ms已用示波器测量
***********************************************************/
void delay_ms()
{
	int i,j;
	for(i=1; i>=0; i--)
		for(j=123; j>=0; j--);
}


/**********************************************************
*  函数名称：12us高精度延时函数(12.04us)(11.0592MHz)
*  日期：2019-10-4
*  姓名：ZhangHJ
*  说明：嵌套循环延时,延时12.04us已用示波器测量
***********************************************************/
void delay_12us()
{
	int i;
	i++;i++;
}

/**********************************************************
*  函数名称：6us高精度延时函数(6.280us)(11.0592MHz)
*  日期：2019-10-4
*  姓名：ZhangHJ
*  说明：嵌套循环延时,延时6.280us已用示波器测量
***********************************************************/
void delay_6us()
{
	_nop_();
	_nop_();
}

//_nop_();			//2.340us



// 使用示波器测量DP引脚即可得到延时时间
void main()
{
	uint i;
	while(1)
	{
		i=10;while(i>0)i--;
		DP = 1;
		i=10;while(i>0)i--;
		DP = 0;
	}
}