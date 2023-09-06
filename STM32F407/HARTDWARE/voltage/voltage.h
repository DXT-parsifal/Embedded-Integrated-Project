#ifndef __VOLTAGE_H__
#define __VOLTAGE_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"

/*************************************************
函数名:void Voltage_Init(void)
功能:初始化光敏电阻引脚为模拟
参数:无
返回值:无
说明:
	GPIOC 0
**************************************************/
void Voltage_Init(void);

/****************************************************
函数:double Voltage_Get(void)
功能:获取电压值
返回值:数值
****************************************************/
double Voltage_Get(void);
#endif

