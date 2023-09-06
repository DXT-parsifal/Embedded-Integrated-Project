/**************************************************************
文件名:timer.c
作者:王廷胡
邮箱:1299030893@qq.com
说明:主要用于定时器驱动相关操作
创建时间:2023年7月27日  10:00
修改时间:
***************************************************************/
#include "timer.h"
/*************************************************
函数名:void TIM7_Init(u32 arr,u32 psc);
功能:定时器初始化
参数:
	@arr:自动重装载值
	@psc:分频系数值
返回值:无
	说明,这只是通用初始化,如其他高级配置请自行查看详细说明。
**************************************************/
void TIM7_Init(u32 arr,u32 psc)
{
	//1.TIM7定时器外部时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	//2.初始化TIM7时钟配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//分频因子:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//计数模式:向上
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//预分配系数
	
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);
	
	//3.使能更新中断
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	//4.配置定时器中断优先级
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;			//通道 TIM7_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//使能:ENABLE
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//响应优先级
	
	NVIC_Init(&NVIC_InitStruct);
	
	//5.使能TIM7 定时器功能
	TIM_Cmd(TIM7,ENABLE);
}

/*------------------- TIM7 的中断服务函数 ------------------------*/
extern int flag_put;//数据状态上传标志
int timer=0;
#include "beep.h"
void TIM7_IRQHandler()
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update) == SET)	//说明产生了溢出更新中断
	{
        timer++;
        if(timer==30){
            flag_put=1;//数据状态上传标志
            timer=0;//清零
        }
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);	//清除TIM7 的更新中断
	}
}

/*************************************************
函数名:void TIM3_Init(u32 arr,u32 psc);
功能:定时器初始化
参数:
	@arr:自动重装载值
	@psc:分频系数值
返回值:无
	说明,这只是通用初始化,如其他高级配置请自行查看详细说明。
**************************************************/
void TIM3_Init(u32 arr,u32 psc)
{
	//1.TIM3定时器外部时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//2.初始化TIM7时钟配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//分频因子:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//计数模式:向上
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//预分配系数
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	//3.使能更新中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	//4.配置定时器中断优先级
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;			//通道 TIM3_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//使能:ENABLE
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//响应优先级
	
	NVIC_Init(&NVIC_InitStruct);
	
	//5.使能TIM3 定时器功能
	TIM_Cmd(TIM3,ENABLE);
}

/*------------------- TIM3 的中断服务函数 ------------------------*/
#include "beep.h"
void TIM3_IRQHandler()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)	//说明产生了溢出更新中断
	{
		BEEP = !BEEP;	//蜂鸣器反转
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	//清除TIM3 的更新中断
	}
}



/*************************************************
函数名:void TIM8_Init(u32 arr,u32 psc);
功能:定时器初始化
参数:
	@arr:自动重装载值
	@psc:分频系数值
返回值:无
	说明,这只是通用初始化,如其他高级配置请自行查看详细说明。
**************************************************/
void TIM8_Init(u32 arr,u32 psc)
{
	//1.TIM3定时器外部时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	//2.初始化TIM7时钟配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//分频因子:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//计数模式:向上
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//预分配系数
	
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);
	
	//3.使能更新中断
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
	
	//4.配置定时器中断优先级
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;	//通道 TIM8_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//使能:ENABLE
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//响应优先级
	
	NVIC_Init(&NVIC_InitStruct);
	
	//5.使能TIM8 定时器功能
	TIM_Cmd(TIM8,ENABLE);
}

/*------------------- TIM8 的中断服务函数 ------------------------*/
#include "beep.h"
#include "led.h"
void TIM8_UP_TIM13_IRQHandler()
{
	if(TIM_GetITStatus(TIM8,TIM_IT_Update) == SET)	//说明产生了溢出更新中断
	{
		BEEP = !BEEP;	//蜂鸣器反转
		
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);	//清除TIM3 的更新中断
	}
}





/*****************************************************************************************************
函数名:void TIM2_Init(u32 arr,u32 psc);
功能:定时器PWM初始化
参数:
	@arr:自动重装载值
	@psc:分频系数值
返回值:无
	说明,这只是通用初始化,如其他高级配置请自行查看详细说明。
	本函数对 BEEP 蜂鸣器进行 PWM 脉冲宽度调制
	使用引脚: PB10	,对其 CH2 通道进行PWM
	可以使用 void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);设置通道的比较值 
******************************************************************************************************/
void TIM2_Init(u32 arr,u32 psc)
{
	//1.TIM2定时器外部时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//2.GPIO初始化为复用功能 定时器2
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	//模式:复用功能
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;	//引脚:10号
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//3.将其引脚复用成定时器2功能
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
	
	//4.初始化TIM2时钟配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//分频因子:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//计数模式:向上
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//预分配系数
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//5.设置TIM2的CH3为PWM1模式等配置
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//模式:PWM1，当计数值小于比较值时输出高电平
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	//输出状态:使能
	TIM_OCInitStruct.TIM_Pulse = 0;								//脉冲宽度比较值:0
	
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	
	//6.使能TIM2 定时器功能
	TIM_Cmd(TIM2,ENABLE);
	
	//7.如果是TIM1和TIM8高级定时器,需要开启外设使能
	//TIM_CtrlPWMOutputs(TIM1,ENABLE);
}







/*****************************************************************************************************
函数名:void TIM1_Init(u32 arr,u32 psc);
功能:定时器PWM初始化
参数:
	@arr:自动重装载值
	@psc:分频系数值
返回值:无
	说明,这只是通用初始化,如其他高级配置请自行查看详细说明。
	本函数对 FAN 风扇进行 PWM 脉冲宽度调制
	本函数对 LED1小灯进行 PWM 脉冲宽度调制
	本函数对 LED2小灯进行 PWM 脉冲宽度调制
    本函数对 LED3小灯进行 PWM 脉冲宽度调制
	使用引脚: PB15	,对其 CH3N 通道进行PWM  风扇
	使用引脚: PE8	,对其 CH1N 通道进行PWM  LED1
	使用引脚: PE9	,对其 CH1  通道进行PWM  LED2
    使用引脚: PE10	,对其 CH2N  通道进行PWM  LED2
	可以使用 void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare2);设置通道的比较值 
	可以使用 void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare2);设置通道的比较值 
******************************************************************************************************/
void TIM1_Init(u32 arr,u32 psc)		//TIM1初始化
{
	//1.TIM1定时器外部时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//2.1 GPIOB初始化为复用功能 定时器1
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	//模式:复用功能
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_15;	//引脚:15号
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//2.2 GPIOE初始化为复用功能 定时器1
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10;	//引脚:8号LED1带N和9号LED2不带N和10号LED3带N
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	//3.将其引脚复用成定时器1功能
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM1);
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM1);
	//4.初始化TIM1时钟配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//分频因子:1
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//计数模式:向上
	TIM_TimeBaseInitStruct.TIM_Period = arr;					//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;					//预分配系数
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	
	//5.1 设置TIM1的CH3N为PWM1模式等配置 , 注意:现在操作的是带N的操作 
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//模式:PWM1，当计数值小于比较值时输出高电平
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;//互补输出状态:使能
	TIM_OCInitStruct.TIM_Pulse = 0;								//脉冲宽度比较值:0
	
	TIM_OC3Init(TIM1, &TIM_OCInitStruct);						//通道3
	
	//5.2 设置TIM1的CH1N和CH1为PWM1模式等配置 , 注意:现在操作的是带N的操作 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;				//模式:PWM1，当计数值小于比较值时输出高电平
	TIM_OCInitStruct.TIM_Pulse = 0;								//脉冲宽度比较值:0
	
	TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Enable;	//输出状态:使能
//	TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;	//互补极性:高电平
//	TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Set;	//空闲状态:
	
	
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;//互补输出状态:使能
//	TIM_OCInitStruct.TIM_OCNPolarity  = TIM_OCNPolarity_Low;	//互补极性:低电平
//	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;	//空闲状态:
	
	TIM_OC1Init(TIM1, &TIM_OCInitStruct);						//通道1
    TIM_OC2Init(TIM1, &TIM_OCInitStruct);						//通道2
	//6.使能TIM1 定时器功能
	TIM_Cmd(TIM1,ENABLE);
	
	//7.如果是TIM1和TIM8高级定时器,需要开启外设使能
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
