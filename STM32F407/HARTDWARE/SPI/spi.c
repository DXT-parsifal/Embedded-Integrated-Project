
#include "spi.h"
/*************************************************
函数名:void SPI1_Init(void)
功能:初始化SPI总线
参数:无
返回值:无
说明:
	SCLK时钟线 ---- GPIOB 3引脚
	MISO接收线 ---- GPIOB 4引脚
	MOSI发送线 ---- GPIOB 5引脚
	
	GPIOB挂载在RCC的AHB1总线
**************************************************/
void SPI1_Init(void)
{
	//1.使能外部时钟 SPI1 和 GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//2.初始化GPIOB 3|4|5 进行复用
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//引脚:3,4,5
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;						//功能:复用
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//3.复用GPIOB 3|4|5 到 SPI 功能
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	//4.配置SPI相关参数初始化
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	//波特率,分频系数：32分频
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;							//极性:0  第一个时钟边沿采集
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low; 							//相位:0  低电平采集
	SPI_InitStruct.SPI_CRCPolynomial = 0x2; 							//CRC校验:多项式校验法
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;						//数据位:8位
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//方向:全双工
	SPI_InitStruct.SPI_FirstBit =SPI_FirstBit_MSB;						//先发:高位先发
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;							//模式:主机
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;								//NSS管理:软件
	
	SPI_Init(SPI1, &SPI_InitStruct);
	
	//5.使能SPI功能
	SPI_Cmd(SPI1, ENABLE);
}

/*************************************************
函数:u8 SPI1_Write_Read(u8 data)
功能:发送 | 接收 1字节数据
参数:
	@data：要发送的数据,如果是接收可以填写0x00 | 0xFF

返回值:
	@读取的数据 , 如果是写入则忽略该返回值

说明: 发送和接收都是同步操作的
	1.发送数据时,可以忽略收到的消息
	2.接收数据时,发送一个空字节
**************************************************/
u8 SPI1_Write_Read(u8 data)
{
	//1.发送消息前先看看,发送移位寄存器是否空闲 , 如果空闲  标志位 1       
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET)
	{
		;	//死等,移位寄存器将数据发送完成
	}
	
	//2.将数据发送
	SPI_I2S_SendData(SPI1,data);
	
	//3.接收前,判断 SPI 接收移位寄存器缓冲区中是否有数据
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET)
	{
		;	//死等,移位寄存器将数据发送完成
	}
	
	//4.将数据读取
	return SPI_I2S_ReceiveData(SPI1);
}



