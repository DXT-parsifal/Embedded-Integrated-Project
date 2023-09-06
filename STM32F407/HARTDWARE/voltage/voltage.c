#include "voltage.h"
#include "adc.h"
/*************************************************
函数名:void Voltage_Init(void)
功能:初始化光敏电阻引脚为模拟
参数:无
返回值:无
说明:
	GPIOC 0
**************************************************/
void Voltage_Init(void)
{
	//1.使能GPIOC外设时钟 RCC的AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	//2.配置GPIOC0引脚
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;	//模式:模拟模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;	//引脚:0
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);	//GPIO初始化
}

/****************************************************
函数:u16 Voltage_Get(void)
功能:获取电压值  通道10
返回值:数值
****************************************************/
double Voltage_Get(void)
{
	double temp_value = 0;
	for(int i = 0; i < 10; i++)
	{
		temp_value += Get_ADC(ADC1,10);	//ADC1的通道10采集
	}
	
	temp_value = temp_value/10;		//求平均值 
	return 3.3 * temp_value/4096;	//
}
