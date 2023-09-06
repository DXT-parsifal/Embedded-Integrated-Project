#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/****** ���λ�β����� ******/
#define LED1 PEout(8)
#define LED2 PEout(9)
#define LED3 PEout(10)

/*************************************************
������:void LED_Init(void)
����:��ʼ��LED
����:��
����ֵ:��
˵��:
	LED1 ---- GPIOE 8����
	LED2 ---- GPIOE 9����
	LED3 ---- GPIOE 10����
	GPIOE������RCC��AHB1����
**************************************************/
void LED_Init(void);

#endif

