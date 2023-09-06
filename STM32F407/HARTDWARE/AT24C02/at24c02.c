
#include "at24c02.h"
#include "iic.h"
/******************************
功能:IIC写入
	@wr_addr:设备的首地址
	@data:数据首地址
	@len:数据长度
*******************************/
void AT24C02_Write(u8 wr_addr,u8 *data,u8 len)
{
	//1.发送起始信号
	IIC_Start();
	
	//2.发送从机器件地址 0 写入
	IIC_Send_Byte(0xA0);
	IIC_Wait_Ack();		//等待应答
	
	//3.发送要操作的地址
	IIC_Send_Byte(wr_addr);
	IIC_Wait_Ack();		//等待应答
	
	//4.循环写入数据
	for(int i = 0; i < len;i++)
	{
		IIC_Send_Byte(data[i]);
		IIC_Wait_Ack();		//等待应答
	}
	//5.写完了,产生停止信号
	IIC_Stop();
}
/******************************
功能:IIC读取
	@wr_addr:设备的首地址
	@data:数据首地址
	@len:数据长度
*******************************/
void AT24C02_Read(u8 wr_addr,u8 *data,u8 len)
{
	//1.发送起始信号
	IIC_Start();
	
	//2.发送从机器件地址 0 写入
	IIC_Send_Byte(0xA0);
	IIC_Wait_Ack();		//等待应答
	
	//3.发送要操作的地址,让其跳转到制定地址
	IIC_Send_Byte(wr_addr);
	IIC_Wait_Ack();		//等待应答
		
	//4.重新发送起始信号
	IIC_Start();
	
	//5.发送要操作的从机设备 1 读取
	IIC_Send_Byte(0xA0+0x1);
	IIC_Wait_Ack();		//等待应答
	
	//6.循环读取数据
	for(int i = 0; i < len;i++)
	{
		data[i] = IIC_Read_Byte();
		if(i != len-1)IIC_Ack();	//应答
	}
	
	//7.接完了,产生非应答和停止信号
	IIC_NAck();
	IIC_Stop();
}



