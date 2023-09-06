#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/*************************************************************
基本定时器:TIM6 和 TIM7
通用定时器:TIM2 和 TIM5 以及 TIM9 ~ TIME14
高级定时器:TIM1 和 TIM8
他们各自有不同的功能,使用时需自行查阅芯片参考开发手册。
**************************************************************/

/****************************************************************
函数名:void TIMx_Init(u32 arr,u32 psc);
功能:定时器初始化
参数:
	@arr:自动重装载值
	@psc:分频系数值
返回值:无
	说明,这只是通用初始化,如其他高级配置请自行查看详细说明。
*****************************************************************/
/********************* 基本定时器代码 ******************************/
void TIM7_Init(u32 arr,u32 psc);		//TIM7初始化
/********************* 通用定时器代码 ******************************/
void TIM3_Init(u32 arr,u32 psc);		//TIM3初始化
/*-------------------- 通用定时器PWM  -----------------------------*/
void TIM2_Init(u32 arr,u32 psc);		//TIM2初始化

/********************* 高级定时器代码 ******************************/
void TIM8_Init(u32 arr,u32 psc);		//TIM8初始化
/*-------------------- 高级定时器PWM  -----------------------------*/
void TIM1_Init(u32 arr,u32 psc);		//TIM1初始化

#endif

