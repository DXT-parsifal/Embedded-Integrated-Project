#include "light.h"
#include "adc.h"
/*************************************************
������:void Light_Init(void)
����:��ʼ��������������Ϊģ��
����:��
����ֵ:��
˵��:
	GPIOA 0
**************************************************/
void Light_Init(void)
{
	//1.ʹ��GPIOA����ʱ�� RCC��AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//2.����GPIOA0����
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;	//ģʽ:ģ��ģʽ
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;	//����:8
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	//GPIO��ʼ��
}

/****************************************************
����:u16 Light_Get(void)
����:��ȡ����ֵ��дת�����㷨
����ֵ:��ֵ��Χ
��Χ:0-100
��ֵ:0   = �
��ֵ:100 = ����
�����ӽ�:40 - 76��Χ
****************************************************/
u16 Light_Get(void)
{
	u32 temp_value = 0;
	for(int i = 0; i < 10; i++)
	{
		temp_value += Get_ADC(ADC1,0);	//ADC1��ͨ��0�ɼ�
	}
	
	temp_value = temp_value/10;	//��ƽ��ֵ 
	return 100-(temp_value/40);
}
