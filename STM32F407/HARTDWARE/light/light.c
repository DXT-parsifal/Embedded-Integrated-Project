#include "light.h"
#include "adc.h"
/*************************************************
函数名:void Light_Init(void)
功能:初始化光敏电阻引脚为模拟
参数:无
返回值:无
说明:
	GPIOA 0
**************************************************/
void Light_Init(void)
{
	//1.使能GPIOA外设时钟 RCC的AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//2.配置GPIOA0引脚
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;	//模式:模拟模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;	//引脚:8
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	//GPIO初始化
}

/****************************************************
函数:u16 Light_Get(void)
功能:获取光照值并写转换％算法
返回值:数值范围
范围:0-100
数值:0   = 最暗
数值:100 = 最亮
人眼视角:40 - 76范围
****************************************************/
u16 Light_Get(void)
{
	u32 temp_value = 0;
	for(int i = 0; i < 10; i++)
	{
		temp_value += Get_ADC(ADC1,0);	//ADC1的通道0采集
	}
	
	temp_value = temp_value/10;	//求平均值 
	return 100-(temp_value/40);
}
