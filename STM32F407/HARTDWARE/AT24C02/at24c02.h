#ifndef __AT24C02_H__
#define __AT24C02_H__

#include "stm32f4xx.h"                  // Device header
#include "sys.h"

/******************************
功能:IIC写入
	@wr_addr:设备的首地址
	@data:数据首地址
	@len:数据长度
*******************************/
void AT24C02_Write(u8 wr_addr,u8 *data,u8 len);
/******************************
功能:IIC读取
	@wr_addr:设备的首地址
	@data:数据首地址
	@len:数据长度
*******************************/
void AT24C02_Read(u8 wr_addr,u8 *data,u8 len);

#endif

