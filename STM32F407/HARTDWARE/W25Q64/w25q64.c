
#include "w25q64.h"
#include "spi.h"
#include "delay.h"
/*************************************************
函数名:void W25Q64_Init(void)
功能:初始化LED
参数:无
返回值:无
说明:
	W25Q64_CS ---- GPIOB 2片选引脚
	GPIOB挂载在RCC的AHB1总线
**************************************************/
void W25Q64_Init(void)
{
	//1.使能外设时钟总线 GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//2.配置GPIOB 2
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;						//模式:输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//类型:推挽
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;						//引脚:2
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//状态:上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;					//速度:高速
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	//GPIO初始化
	//3.将其设置为空闲状态
	W25Q64 = 1;
}

/************************************************
功能:写使能  = 06h
*************************************************/
void W25Q64_Write_Ebale(void)
{
	//1.将片选设置为0 
	W25Q64 = 0;
	
	//2.写入数据
	SPI1_Write_Read(0x06);
	
	//3.将片选设置为1 
	W25Q64 = 1;
}

/************************************************
功能:读取状态 判断是否忙碌 = 05h 
*************************************************/
void W25Q64_Check_Busy(void)
{
	u8 flag = 0;
	do
	{
		//1.将片选设置为0 
		W25Q64 = 0;
		
		//2.发送读取状态指令 05h
		flag = SPI1_Write_Read(0x05);
		
		//3.将片选设置为1 
		W25Q64 = 1;
	}while(flag &0x01 != 0);	//死等
}

/************************************************
功能:扇区擦除(4k)  == 20h
*************************************************/
void W25Q64_Erasr(u32 addr)
{
	//1.使能
	W25Q64_Write_Ebale();
	
	//2.片选拉低
	W25Q64 = 0;
	
	//3.片选擦除指令
	SPI1_Write_Read(0x20);
	
	//4.发送要擦除的地址 A23~A16
	SPI1_Write_Read(addr >> 16);
	//5.发送要擦除的地址 A15~A8 
	SPI1_Write_Read(addr >> 8);
	//6.发送要擦除的地址 A7~A0
	SPI1_Write_Read(addr >> 0);
	
	//7.将片选设置为1
	W25Q64 = 1;
	
	//8.等待擦除完成才能离开
	W25Q64_Check_Busy();	//忙碌检测
	delay_ms(50);
}

/************************************************
函数:int W25Q64_Write_Data(u32 addr,u8 *data,u8 len)
功能:页编程 发送数据 = 02h 
参数:
	@addr：地址
	@data：要写入的数据
	@len：要写入的长度
返回:成功写入的数据长度
*************************************************/
int W25Q64_Write_Data(u32 addr,u8 *data,u8 len)
{
	//1.使能
	W25Q64_Write_Ebale();
	W25Q64_Check_Busy();	//忙碌检测
	//2.片选拉低
	W25Q64 = 0;
	
	//3.片选擦除指令
	SPI1_Write_Read(0x02);
	
	//4.发送要写入的地址 A23~A16
	SPI1_Write_Read(addr >> 16);
	//5.发送要写入的地址 A15~A8 
	SPI1_Write_Read(addr >> 8);
	//6.发送要写入的地址 A7~A0
	SPI1_Write_Read(addr >> 0);
	
	//7.循环写入数据 (D7~D0) ... 下一个字节 ...
	for(int i = 0; i < len;i++)
	{
		SPI1_Write_Read(data[i]);
	}
	
	//8.片选拉高
	W25Q64 = 1;
	//9.等待写完成
	W25Q64_Check_Busy();	//忙碌检测
	
	return len;
}

/******************************************************
函数:int W25Q64_Read_Data(u32 addr,u8 *data,u8 len)
功能:读数据 = 03h
参数:
	@addr：地址
	@data：读取后数据存放的地址
	@len：要读的长度
返回:成功读取的数据长度
*******************************************************/
int W25Q64_Read_Data(u32 addr,u8 *data,u8 len)
{
	//1.使能
	W25Q64_Write_Ebale();
	//2.片选拉低
	W25Q64 = 0;
	
	//3.片选擦除指令
	SPI1_Write_Read(0x03);
	
	//4.发送要读取的地址 A23~A16
	SPI1_Write_Read(addr >> 16);
	//5.发送要读取的地址 A15~A8 
	SPI1_Write_Read(addr >> 8);
	//6.发送要读取的地址 A7~A0
	SPI1_Write_Read(addr >> 0);
	
	//7.循环读取数据 (D7~D0)  ... 继续
	for(int i = 0; i < len;i++)
	{
		data[i] = SPI1_Write_Read(0xff);	//空指令
	}
	//8.片选拉高
	W25Q64 = 1;
	
	return len;
}


