#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/****** λ��غ� *******/
#define KEY1 PEin(4)
#define KEY2 PEin(5)
#define KEY3 PEin(6)
#define KEY4 PCin(13)

/*************************************************
������:void KEY_Init(void)
����:��ʼ��KEY
����:��
����ֵ:��
˵��:
	KEY1 ---- GPIOE4����
	KEY2 ---- GPIOE5����
	KEY3 ---- GPIOE6����
	KEY4 ---- GPIOC13����
	GPIOE,GPIOC ������RCC��AHB1����
**************************************************/
void KEY_Init(void);
/*************************************************
����:u8 KEY_Scan()
����:��ȡ����״̬
����:��
����ֵ:
	KEY1 ���� 1
	KEY2 ���� 2
	KEY3 ���� 3
	KEY4 ���� 4
	���򷵻�  0
**************************************************/
u8 KEY_Scan(void);
#endif

