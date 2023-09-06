#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/****** 位相关宏 *******/
#define KEY1 PEin(4)
#define KEY2 PEin(5)
#define KEY3 PEin(6)
#define KEY4 PCin(13)

/*************************************************
函数名:void KEY_Init(void)
功能:初始化KEY
参数:无
返回值:无
说明:
	KEY1 ---- GPIOE4引脚
	KEY2 ---- GPIOE5引脚
	KEY3 ---- GPIOE6引脚
	KEY4 ---- GPIOC13引脚
	GPIOE,GPIOC 挂载在RCC的AHB1总线
**************************************************/
void KEY_Init(void);
/*************************************************
函数:u8 KEY_Scan()
功能:获取按键状态
参数:无
返回值:
	KEY1 按下 1
	KEY2 按下 2
	KEY3 按下 3
	KEY4 按下 4
	否则返回  0
**************************************************/
u8 KEY_Scan(void);
#endif

