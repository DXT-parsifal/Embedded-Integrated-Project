#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/****** 相关位段操作宏 ******/
#define LED1 PEout(8)
#define LED2 PEout(9)
#define LED3 PEout(10)

/*************************************************
函数名:void LED_Init(void)
功能:初始化LED
参数:无
返回值:无
说明:
	LED1 ---- GPIOE 8引脚
	LED2 ---- GPIOE 9引脚
	LED3 ---- GPIOE 10引脚
	GPIOE挂载在RCC的AHB1总线
**************************************************/
void LED_Init(void);

#endif

