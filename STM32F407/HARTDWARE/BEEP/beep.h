#ifndef __BEEP_H__
#define __BEEP_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/****** ���λ�β����� ******/
#define BEEP PBout(10)

/*************************************************
������:void BEEP_Init(void)
����:��ʼ��BEEP ������
����:��
����ֵ:��
˵��:
	BEEP ---- GPIOB 10����
	GPIOB������RCC��AHB1����
**************************************************/
void BEEP_Init(void);

#endif

