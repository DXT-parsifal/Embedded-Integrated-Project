#ifndef __IWDOG_H__
#define __IWDOG_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/*************************************************
函数名:void IWODG_Init(u8 Pere,u16 rlr)
功能:独立看门狗初始化
参数:
	@Pere：预分配系数
		#define IWDG_Prescaler_4            ((uint8_t)0x00)
		#define IWDG_Prescaler_8            ((uint8_t)0x01)
		#define IWDG_Prescaler_16           ((uint8_t)0x02)
		#define IWDG_Prescaler_32           ((uint8_t)0x03)
		#define IWDG_Prescaler_64           ((uint8_t)0x04)
		#define IWDG_Prescaler_128          ((uint8_t)0x05)
		#define IWDG_Prescaler_256          ((uint8_t)0x06)
	@rlr：计数值也叫重装载值
返回值:无
说明:
查看他的分频资料
预分频器 PR[2:0]位   最短超时ms   最长超时ms
	/4		 0		   0.125		512	  (0.512秒)							
	/8		 1		   0.25	 		1024  (1.240秒)
	/16		 2		   0.5	 		2048  (2.048秒)
	/32		 3		   1	 		4096  (4.096秒)
	/64		 4		   2	 		8192  (8.192秒)
	/128	 5		   4	 		16384 (16.384秒)
	/256	 6		   5	 		32768 (32.768秒)
计算公式:
	溢出时间计算：Tout=((4x2^prer)xrlr)/时钟
		Tout = 超时时间
		prer = 分频系数
		xrlr = 计数值(重装载值)
案例: 计算出4秒的喂狗超时时间？
	1.通过最大时间理论看出，我们可以选择
		./32 分频 ---- 4000 = (4 * 2^(3+1) * xrlr)/32    推出结果 xrlr = 2000 次计数
		./64 分频 ---- 4000 = (4 * 2^(4+1) * xrlr)/32    推出结果 xrlr = 1000 次计数
		./128分频 ---- 4000 = (4 * 2^(5+1) * xrlr)/32    推出结果 xrlr = 500 次计数
		./256分频 ---- 4000 = (4 * 2^(6+1) * xrlr)/32    推出结果 xrlr = 250 次计数
**************************************************/
void IWODG_Init(u8 Pere,u16 rlr);

#endif

