#include "voltage.h"
#include "adc.h"
/*************************************************
������:void Voltage_Init(void)
����:��ʼ��������������Ϊģ��
����:��
����ֵ:��
˵��:
	GPIOC 0
**************************************************/
void Voltage_Init(void)
{
	//1.ʹ��GPIOC����ʱ�� RCC��AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	//2.����GPIOC0����
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;	//ģʽ:ģ��ģʽ
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;	//����:0
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);	//GPIO��ʼ��
}

/****************************************************
����:u16 Voltage_Get(void)
����:��ȡ��ѹֵ  ͨ��10
����ֵ:��ֵ
****************************************************/
double Voltage_Get(void)
{
	double temp_value = 0;
	for(int i = 0; i < 10; i++)
	{
		temp_value += Get_ADC(ADC1,10);	//ADC1��ͨ��10�ɼ�
	}
	
	temp_value = temp_value/10;		//��ƽ��ֵ 
	return 3.3 * temp_value/4096;	//
}
