#ifndef __AT24C02_H__
#define __AT24C02_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"

/******************************
����:IICд��
	@wr_addr:�豸���׵�ַ
	@data:�����׵�ַ
	@len:���ݳ���
*******************************/
void AT24C02_Write(u8 wr_addr,u8 *data,u8 len);
/******************************
����:IIC��ȡ
	@wr_addr:�豸���׵�ַ
	@data:�����׵�ַ
	@len:���ݳ���
*******************************/
void AT24C02_Read(u8 wr_addr,u8 *data,u8 len);

#endif

