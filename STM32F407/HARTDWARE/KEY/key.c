/**************************************************************
文件名:KEY.c
作者:王廷胡
邮箱:1299030893@qq.com
说明:主要用于KEY驱动相关操作
创建时间:2023年7月27日  10:00
修改时间:
	1.2023年7月27日  10:35		王廷胡{优化初始化}
***************************************************************/

#include "key.h"
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
void KEY_Init(void)
{
	//1.使能GPIOE 和 GPIOC 时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	//使能GPIOE
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);	//使能GPIOC
	//2.1初始化GPIOE 4,5,6
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	//引脚:4|5|6
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;						//模式:输入模式
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//状态:上拉
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);	//GPIO初始化
	//2.2初始化GPIOC13
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct);	//GPIO初始化
}

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
让其不支持连续按
**************************************************/
#include "delay.h"
u8 KEY_Scan(void)
{
	static u8 flag = 0;	//存取上次状态
	if((KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0) && flag == 0)
	{
		flag = 1;
		delay_ms(5);	//消抖
		if(KEY1 == 0) return 1;
		if(KEY2 == 0) return 2;
		if(KEY3 == 0) return 3;
		if(KEY4 == 0) return 4;
	}
	
	if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1){
		flag = 0;
	}
	//没有任何按键按下
	return 0;
}
