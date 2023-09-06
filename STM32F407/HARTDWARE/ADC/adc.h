#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"

/*************************************************
函数名:void ADC1_Init(void)
功能:初始化ADC1
参数:无
返回值:无
说明:
	ADC1初始化 APB2 总线
**************************************************/
void ADC1_Init(void);
/**************************************
功能:采集ADC通道值
参数:
	@ADCx:使用的是ADC1|2|3
	@ch:采集通道0 - 15
返回值:数值结果
***************************************/
u16 Get_ADC(ADC_TypeDef* ADCx,u8 ch);
#endif

