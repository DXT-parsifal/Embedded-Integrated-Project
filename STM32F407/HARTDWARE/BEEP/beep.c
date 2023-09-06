/**************************************************************
�ļ���:beep.c
����:��͢��
����:1299030893@qq.com
˵��:��Ҫ����BEEP������ ������ز���
����ʱ��:2023��7��27��  10:00
�޸�ʱ��:
	1.2023��7��27��  10:35		��͢��{�Ż���ʼ��}
***************************************************************/
#include "beep.h"
/*************************************************
������:void BEEP_Init(void)
����:��ʼ��BEEP ������
����:��
����ֵ:��
˵��:
	BEEP ---- GPIOB 10����
	GPIOB������RCC��AHB1����
**************************************************/
void BEEP_Init(void)
{
	//1.ʹ��GPIOB����ʱ�� RCC��AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//2.����GPIOB 10����(ע������:ʲôʱ������û򷽷� , �����Ƕ���ͬһ��32λ�Ĵ�������)
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;						//ģʽ:���ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//����:����
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;						//����:10
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//״̬:����
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;					//�ٶ�:����
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	//GPIO��ʼ��
	//3.����GPIO��� �ߵ�ƽ����
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}
