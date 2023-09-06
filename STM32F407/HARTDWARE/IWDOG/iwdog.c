/**************************************************************
文件名:iwdog.c
作者:王廷胡
邮箱:1299030893@qq.com
说明:主要用于独立看门狗驱动相关操作
创建时间:2023年7月27日  10:00
修改时间:
***************************************************************/
#include "iwdog.h"
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
参考:stm32f4xx_iwdg.c 和 stm32f4xx_iwdg.g 头文件编写程序
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);		//写入值到关键字寄存器 IWDG_KR 寄存器
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);				//设置预分配系数:IWDG_PR
void IWDG_SetReload(uint16_t Reload);						//设置重装载值:IWDG_RLR
void IWDG_ReloadCounter(void);								//喂狗：0xAAAA写入关键字寄存器 IWDG_KR 寄存器
void IWDG_Enable(void);										//使能：0xCCCC写入关键字寄存器 IWDG_KR 寄存器
**************************************************/
void IWODG_Init(u8 Pere,u16 rlr)
{
	//1.取消写保护
	IWDG_WriteAccessCmd(0x5555);
	//2.设置预分配系数
	IWDG_SetPrescaler(Pere);
	//3.设置自动重装载值 并 喂狗
	IWDG_SetReload(rlr);
	IWDG_ReloadCounter();
	//4.使能独立看门狗
	IWDG_Enable();
}
