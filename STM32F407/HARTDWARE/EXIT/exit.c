
#include "exit.h"
#include "key.h"
/*************************************************
函数名:void EXTI_KEY_Init(void)
功能:按键外部中断初始化
参数:无
返回值:无
说明:按键1到4的初始化
**************************************************/
void EXTI_KEY_Init(void)
{
	
	//1.使能外部中断时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//2.使能GPIO外设 和 GPIO初始化
	KEY_Init();
	
	//3.配置中断线
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);	//中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);	//中断线5
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);	//中断线6
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);	//中断线13
	
	//4.配置外部中断
	EXTI_InitTypeDef EXTI_InitStruct;
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line13;//中断线
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;									 //使能
	EXTI_InitStruct.EXTI_Mode =EXTI_Mode_Interrupt;							 //模式:中断
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;					 //下降沿
	
	EXTI_Init(&EXTI_InitStruct);
	
	//5.配置中断
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;	//通道外部中断4
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//响应优先级
	
	NVIC_Init(&NVIC_InitStruct);
	
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;	//通道外部中断5~9
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;	//通道外部中断10~15
	NVIC_Init(&NVIC_InitStruct);
}

/*************************************************************************
中断注意事项:
	1.不能有返回值
	2.不能有参数
	3.不能使用浮点计算
	4.短小精干(尽量不要有延时)
	5.从汇编启动文件.s中的中断向量表初始化找中断服务函数
常用函数: 
	1.获取中断状态 ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
	2.清除中断状态 void EXTI_ClearITPendingBit(uint32_t EXTI_Line); 
**************************************************************************/
#include "led.h"
#include "beep.h"
void EXTI4_IRQHandler()
{
	
	
}


void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET)	//获取中断线5的状态
	{
		LED1 = !LED1;
		EXTI_ClearITPendingBit(EXTI_Line5);	//清除中断状态
	}
	
	if(EXTI_GetITStatus(EXTI_Line6) == SET)	//获取中断线5的状态
	{
		BEEP = !BEEP;
		EXTI_ClearITPendingBit(EXTI_Line6);	//清除中断状态
	}
	
}

void EXTI15_10_IRQHandler()
{
	
	
}



