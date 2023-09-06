#ifndef __VOLTAGE_H__
#define __VOLTAGE_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"

/*************************************************
������:void Voltage_Init(void)
����:��ʼ��������������Ϊģ��
����:��
����ֵ:��
˵��:
	GPIOC 0
**************************************************/
void Voltage_Init(void);

/****************************************************
����:double Voltage_Get(void)
����:��ȡ��ѹֵ
����ֵ:��ֵ
****************************************************/
double Voltage_Get(void);
#endif

