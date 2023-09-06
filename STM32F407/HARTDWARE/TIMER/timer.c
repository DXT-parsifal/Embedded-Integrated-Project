/**************************************************************
�ļ���:timer.c
����:��͢��
����:1299030893@qq.com
˵��:��Ҫ���ڶ�ʱ��������ز���
����ʱ��:2023��7��27��  10:00
�޸�ʱ��:
***************************************************************/
#include "timer.h"
/*************************************************
������:void TIM7_Init(u32 arr,u32 psc);
����:��ʱ����ʼ��
����:
	@arr:�Զ���װ��ֵ
	@psc:��Ƶϵ��ֵ
����ֵ:��
	˵��,��ֻ��ͨ�ó�ʼ��,�������߼����������в鿴��ϸ˵����
**************************************************/
void TIM7_Init(u32 arr,u32 psc)
{
	//1.TIM7��ʱ���ⲿʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	//2.��ʼ��TIM7ʱ������
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//��Ƶ����:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ:����
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//Ԥ����ϵ��
	
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);
	
	//3.ʹ�ܸ����ж�
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	//4.���ö�ʱ���ж����ȼ�
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;			//ͨ�� TIM7_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//ʹ��:ENABLE
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStruct);
	
	//5.ʹ��TIM7 ��ʱ������
	TIM_Cmd(TIM7,ENABLE);
}

/*------------------- TIM7 ���жϷ����� ------------------------*/
extern int flag_put;//����״̬�ϴ���־
int timer=0;
#include "beep.h"
void TIM7_IRQHandler()
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update) == SET)	//˵����������������ж�
	{
        timer++;
        if(timer==30){
            flag_put=1;//����״̬�ϴ���־
            timer=0;//����
        }
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);	//���TIM7 �ĸ����ж�
	}
}

/*************************************************
������:void TIM3_Init(u32 arr,u32 psc);
����:��ʱ����ʼ��
����:
	@arr:�Զ���װ��ֵ
	@psc:��Ƶϵ��ֵ
����ֵ:��
	˵��,��ֻ��ͨ�ó�ʼ��,�������߼����������в鿴��ϸ˵����
**************************************************/
void TIM3_Init(u32 arr,u32 psc)
{
	//1.TIM3��ʱ���ⲿʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//2.��ʼ��TIM7ʱ������
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//��Ƶ����:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ:����
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//Ԥ����ϵ��
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	//3.ʹ�ܸ����ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	//4.���ö�ʱ���ж����ȼ�
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;			//ͨ�� TIM3_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//ʹ��:ENABLE
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStruct);
	
	//5.ʹ��TIM3 ��ʱ������
	TIM_Cmd(TIM3,ENABLE);
}

/*------------------- TIM3 ���жϷ����� ------------------------*/
#include "beep.h"
void TIM3_IRQHandler()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)	//˵����������������ж�
	{
		BEEP = !BEEP;	//��������ת
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	//���TIM3 �ĸ����ж�
	}
}



/*************************************************
������:void TIM8_Init(u32 arr,u32 psc);
����:��ʱ����ʼ��
����:
	@arr:�Զ���װ��ֵ
	@psc:��Ƶϵ��ֵ
����ֵ:��
	˵��,��ֻ��ͨ�ó�ʼ��,�������߼����������в鿴��ϸ˵����
**************************************************/
void TIM8_Init(u32 arr,u32 psc)
{
	//1.TIM3��ʱ���ⲿʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	//2.��ʼ��TIM7ʱ������
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//��Ƶ����:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ:����
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//Ԥ����ϵ��
	
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);
	
	//3.ʹ�ܸ����ж�
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
	
	//4.���ö�ʱ���ж����ȼ�
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;	//ͨ�� TIM8_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//ʹ��:ENABLE
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitStruct);
	
	//5.ʹ��TIM8 ��ʱ������
	TIM_Cmd(TIM8,ENABLE);
}

/*------------------- TIM8 ���жϷ����� ------------------------*/
#include "beep.h"
#include "led.h"
void TIM8_UP_TIM13_IRQHandler()
{
	if(TIM_GetITStatus(TIM8,TIM_IT_Update) == SET)	//˵����������������ж�
	{
		BEEP = !BEEP;	//��������ת
		
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);	//���TIM3 �ĸ����ж�
	}
}





/*****************************************************************************************************
������:void TIM2_Init(u32 arr,u32 psc);
����:��ʱ��PWM��ʼ��
����:
	@arr:�Զ���װ��ֵ
	@psc:��Ƶϵ��ֵ
����ֵ:��
	˵��,��ֻ��ͨ�ó�ʼ��,�������߼����������в鿴��ϸ˵����
	�������� BEEP ���������� PWM �����ȵ���
	ʹ������: PB10	,���� CH2 ͨ������PWM
	����ʹ�� void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);����ͨ���ıȽ�ֵ 
******************************************************************************************************/
void TIM2_Init(u32 arr,u32 psc)
{
	//1.TIM2��ʱ���ⲿʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//2.GPIO��ʼ��Ϊ���ù��� ��ʱ��2
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	//ģʽ:���ù���
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;	//����:10��
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//3.�������Ÿ��óɶ�ʱ��2����
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
	
	//4.��ʼ��TIM2ʱ������
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//��Ƶ����:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ:����
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//Ԥ����ϵ��
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//5.����TIM2��CH3ΪPWM1ģʽ������
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//ģʽ:PWM1��������ֵС�ڱȽ�ֵʱ����ߵ�ƽ
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	//���״̬:ʹ��
	TIM_OCInitStruct.TIM_Pulse = 0;								//�����ȱȽ�ֵ:0
	
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	
	//6.ʹ��TIM2 ��ʱ������
	TIM_Cmd(TIM2,ENABLE);
	
	//7.�����TIM1��TIM8�߼���ʱ��,��Ҫ��������ʹ��
	//TIM_CtrlPWMOutputs(TIM1,ENABLE);
}







/*****************************************************************************************************
������:void TIM1_Init(u32 arr,u32 psc);
����:��ʱ��PWM��ʼ��
����:
	@arr:�Զ���װ��ֵ
	@psc:��Ƶϵ��ֵ
����ֵ:��
	˵��,��ֻ��ͨ�ó�ʼ��,�������߼����������в鿴��ϸ˵����
	�������� FAN ���Ƚ��� PWM �����ȵ���
	�������� LED1С�ƽ��� PWM �����ȵ���
	�������� LED2С�ƽ��� PWM �����ȵ���
    �������� LED3С�ƽ��� PWM �����ȵ���
	ʹ������: PB15	,���� CH3N ͨ������PWM  ����
	ʹ������: PE8	,���� CH1N ͨ������PWM  LED1
	ʹ������: PE9	,���� CH1  ͨ������PWM  LED2
    ʹ������: PE10	,���� CH2N  ͨ������PWM  LED2
	����ʹ�� void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare2);����ͨ���ıȽ�ֵ 
	����ʹ�� void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare2);����ͨ���ıȽ�ֵ 
******************************************************************************************************/
void TIM1_Init(u32 arr,u32 psc)		//TIM1��ʼ��
{
	//1.TIM1��ʱ���ⲿʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//2.1 GPIOB��ʼ��Ϊ���ù��� ��ʱ��1
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	//ģʽ:���ù���
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_15;	//����:15��
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//2.2 GPIOE��ʼ��Ϊ���ù��� ��ʱ��1
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10;	//����:8��LED1��N��9��LED2����N��10��LED3��N
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	//3.�������Ÿ��óɶ�ʱ��1����
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM1);
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM1);
	//4.��ʼ��TIM1ʱ������
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//��Ƶ����:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ:����
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//Ԥ����ϵ��
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	
	//5.1 ����TIM1��CH3NΪPWM1ģʽ������ , ע��:���ڲ������Ǵ�N�Ĳ��� 
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//ģʽ:PWM1��������ֵС�ڱȽ�ֵʱ����ߵ�ƽ
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;//�������״̬:ʹ��
	TIM_OCInitStruct.TIM_Pulse = 0;								//�����ȱȽ�ֵ:0
	
	TIM_OC3Init(TIM1, &TIM_OCInitStruct);						//ͨ��3
	
	//5.2 ����TIM1��CH1N��CH1ΪPWM1ģʽ������ , ע��:���ڲ������Ǵ�N�Ĳ��� 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//ģʽ:PWM1��������ֵС�ڱȽ�ֵʱ����ߵ�ƽ
	TIM_OCInitStruct.TIM_Pulse = 0;								//�����ȱȽ�ֵ:0
	
	TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Enable;	//���״̬:ʹ��
//	TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;	//��������:�ߵ�ƽ
//	TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Set;	//����״̬:
	
	
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;//�������״̬:ʹ��
//	TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCNPolarity_Low;	//��������:�͵�ƽ
//	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;	//����״̬:
	
	TIM_OC1Init(TIM1, &TIM_OCInitStruct);						//ͨ��1
    TIM_OC2Init(TIM1, &TIM_OCInitStruct);						//ͨ��2
	//6.ʹ��TIM1 ��ʱ������
	TIM_Cmd(TIM1,ENABLE);
	
	//7.�����TIM1��TIM8�߼���ʱ��,��Ҫ��������ʹ��
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
