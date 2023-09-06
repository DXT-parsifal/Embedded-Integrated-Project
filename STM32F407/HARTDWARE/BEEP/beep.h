#ifndef __BEEP_H__
#define __BEEP_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/****** 相关位段操作宏 ******/
#define BEEP PBout(10)

/*************************************************
函数名:void BEEP_Init(void)
功能:初始化BEEP 蜂鸣器
参数:无
返回值:无
说明:
	BEEP ---- GPIOB 10引脚
	GPIOB挂载在RCC的AHB1总线
**************************************************/
void BEEP_Init(void);

#endif

