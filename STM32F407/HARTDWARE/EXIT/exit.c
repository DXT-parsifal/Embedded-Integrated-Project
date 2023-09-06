
#include "exit.h"
#include "key.h"
/*************************************************
������:void EXTI_KEY_Init(void)
����:�����ⲿ�жϳ�ʼ��
����:��
����ֵ:��
˵��:����1��4�ĳ�ʼ��
**************************************************/
void EXTI_KEY_Init(void)
{
	
	//1.ʹ���ⲿ�ж�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//2.ʹ��GPIO���� �� GPIO��ʼ��
	KEY_Init();
	
	//3.�����ж���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);	//�ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);	//�ж���5
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);	//�ж���6
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);	//�ж���13
	
	//4.�����ⲿ�ж�
	EXTI_InitTypeDef EXTI_InitStruct;
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line13;//�ж���
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;									 //ʹ��
	EXTI_InitStruct.EXTI_Mode =EXTI_Mode_Interrupt;							 //ģʽ:�ж�
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;					 //�½���
	
	EXTI_Init(&EXTI_InitStruct);
	
	//5.�����ж�
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;	//ͨ���ⲿ�ж�4
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStruct);
	
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;	//ͨ���ⲿ�ж�5~9
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;	//ͨ���ⲿ�ж�10~15
	NVIC_Init(&NVIC_InitStruct);
}

/*************************************************************************
�ж�ע������:
	1.�����з���ֵ
	2.�����в���
	3.����ʹ�ø������
	4.��С����(������Ҫ����ʱ)
	5.�ӻ�������ļ�.s�е��ж��������ʼ�����жϷ�����
���ú���: 
	1.��ȡ�ж�״̬ ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
	2.����ж�״̬ void EXTI_ClearITPendingBit(uint32_t EXTI_Line); 
**************************************************************************/
#include "led.h"
#include "beep.h"
void EXTI4_IRQHandler()
{
	
	
}


void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET)	//��ȡ�ж���5��״̬
	{
		LED1 = !LED1;
		EXTI_ClearITPendingBit(EXTI_Line5);	//����ж�״̬
	}
	
	if(EXTI_GetITStatus(EXTI_Line6) == SET)	//��ȡ�ж���5��״̬
	{
		BEEP = !BEEP;
		EXTI_ClearITPendingBit(EXTI_Line6);	//����ж�״̬
	}
	
}

void EXTI15_10_IRQHandler()
{
	
	
}



