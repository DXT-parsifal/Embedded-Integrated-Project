/**************************************************************
文件名:led.c
作者:王廷胡
邮箱:1299030893@qq.com
说明:主要用于LED灯驱动相关操作
创建时间:2023年7月27日  10:00
修改时间:
	1.2023年7月27日  10:35		王廷胡{优化初始化}
	2.2023年7月28日  10:00		蒋老师{增加LED8灯相关代码}
***************************************************************/
#include "led.h"
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
void LED_Init(void)
{
	//1.使能GPIOE外设时钟 RCC的AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	//2.配置GPIOE8,9,10引脚(注意事项:什么时候才能用或方法 , 当他们都在同一个32位寄存器组中)
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;						//模式:输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//类型:推挽
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;	//引脚:8|9|10
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//状态:上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;					//速度:高速
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);	//GPIO初始化
	//3.设置GPIO输出 高电平不亮
	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
}





