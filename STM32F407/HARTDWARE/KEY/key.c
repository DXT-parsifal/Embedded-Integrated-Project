/**************************************************************
�ļ���:KEY.c
����:��͢��
����:1299030893@qq.com
˵��:��Ҫ����KEY������ز���
����ʱ��:2023��7��27��  10:00
�޸�ʱ��:
	1.2023��7��27��  10:35		��͢��{�Ż���ʼ��}
***************************************************************/

#include "key.h"
/*************************************************
������:void KEY_Init(void)
����:��ʼ��KEY
����:��
����ֵ:��
˵��:
	KEY1 ---- GPIOE4����
	KEY2 ---- GPIOE5����
	KEY3 ---- GPIOE6����
	KEY4 ---- GPIOC13����
	GPIOE,GPIOC ������RCC��AHB1����
**************************************************/
void KEY_Init(void)
{
	//1.ʹ��GPIOE �� GPIOC ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	//ʹ��GPIOE
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);	//ʹ��GPIOC
	//2.1��ʼ��GPIOE 4,5,6
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	//����:4|5|6
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;						//ģʽ:����ģʽ
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//״̬:����
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);	//GPIO��ʼ��
	//2.2��ʼ��GPIOC13
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);	//GPIO��ʼ��
}

/*************************************************
����:u8 KEY_Scan()
����:��ȡ����״̬
����:��
����ֵ:
	KEY1 ���� 1
	KEY2 ���� 2
	KEY3 ���� 3
	KEY4 ���� 4
	���򷵻�  0
���䲻֧��������
**************************************************/
#include "delay.h"
u8 KEY_Scan(void)
{
	static u8 flag = 0;	//��ȡ�ϴ�״̬
	if((KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0) && flag == 0)
	{
		flag = 1;
		delay_ms(5);	//����
		if(KEY1 == 0) return 1;
		if(KEY2 == 0) return 2;
		if(KEY3 == 0) return 3;
		if(KEY4 == 0) return 4;
	}
	
	if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1){
		flag = 0;
	}
	//û���κΰ�������
	return 0;
}
