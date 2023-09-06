/**************************************************************
�ļ���:led.c
����:��͢��
����:1299030893@qq.com
˵��:��Ҫ����LED��������ز���
����ʱ��:2023��7��27��  10:00
�޸�ʱ��:
	1.2023��7��27��  10:35		��͢��{�Ż���ʼ��}
	2.2023��7��28��  10:00		����ʦ{����LED8����ش���}
***************************************************************/
#include "led.h"
/*************************************************
������:void LED_Init(void)
����:��ʼ��LED
����:��
����ֵ:��
˵��:
	LED1 ---- GPIOE 8����
	LED2 ---- GPIOE 9����
	LED3 ---- GPIOE 10����
	GPIOE������RCC��AHB1����
**************************************************/
void LED_Init(void)
{
	//1.ʹ��GPIOE����ʱ�� RCC��AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	//2.����GPIOE8,9,10����(ע������:ʲôʱ������û򷽷� , �����Ƕ���ͬһ��32λ�Ĵ�������)
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;						//ģʽ:���ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//����:����
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;	//����:8|9|10
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//״̬:����
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;					//�ٶ�:����
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);	//GPIO��ʼ��
	//3.����GPIO��� �ߵ�ƽ����
	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
}





