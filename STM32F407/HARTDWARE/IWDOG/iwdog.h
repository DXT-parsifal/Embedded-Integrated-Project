#ifndef __IWDOG_H__
#define __IWDOG_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"
/*************************************************
������:void IWODG_Init(u8 Pere,u16 rlr)
����:�������Ź���ʼ��
����:
	@Pere��Ԥ����ϵ��
		#define IWDG_Prescaler_4            ((uint8_t)0x00)
		#define IWDG_Prescaler_8            ((uint8_t)0x01)
		#define IWDG_Prescaler_16           ((uint8_t)0x02)
		#define IWDG_Prescaler_32           ((uint8_t)0x03)
		#define IWDG_Prescaler_64           ((uint8_t)0x04)
		#define IWDG_Prescaler_128          ((uint8_t)0x05)
		#define IWDG_Prescaler_256          ((uint8_t)0x06)
	@rlr������ֵҲ����װ��ֵ
����ֵ:��
˵��:
�鿴���ķ�Ƶ����
Ԥ��Ƶ�� PR[2:0]λ   ��̳�ʱms   ���ʱms
	/4		 0		   0.125		512	  (0.512��)							
	/8		 1		   0.25	 		1024  (1.240��)
	/16		 2		   0.5	 		2048  (2.048��)
	/32		 3		   1	 		4096  (4.096��)
	/64		 4		   2	 		8192  (8.192��)
	/128	 5		   4	 		16384 (16.384��)
	/256	 6		   5	 		32768 (32.768��)
���㹫ʽ:
	���ʱ����㣺Tout=((4x2^prer)xrlr)/ʱ��
		Tout = ��ʱʱ��
		prer = ��Ƶϵ��
		xrlr = ����ֵ(��װ��ֵ)
����: �����4���ι����ʱʱ�䣿
	1.ͨ�����ʱ�����ۿ��������ǿ���ѡ��
		./32 ��Ƶ ---- 4000 = (4 * 2^(3+1) * xrlr)/32    �Ƴ���� xrlr = 2000 �μ���
		./64 ��Ƶ ---- 4000 = (4 * 2^(4+1) * xrlr)/32    �Ƴ���� xrlr = 1000 �μ���
		./128��Ƶ ---- 4000 = (4 * 2^(5+1) * xrlr)/32    �Ƴ���� xrlr = 500 �μ���
		./256��Ƶ ---- 4000 = (4 * 2^(6+1) * xrlr)/32    �Ƴ���� xrlr = 250 �μ���
**************************************************/
void IWODG_Init(u8 Pere,u16 rlr);

#endif

