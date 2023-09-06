/**************************************************************
文件名:dht11.c
作者:王廷胡
邮箱:1299030893@qq.com
说明:主要用于单总线协议的dht11驱动相关操作
创建时间:2023年7月27日  10:00
修改时间:
***************************************************************/
#include "dht11.h"
#include "delay.h"
/*************************************************
函数名:void DHT11_Init(void)
功能:初始化DHT11温湿度模块
参数:无
返回值:无
说明:
	DHT11_DATA ---- GPIOA 3引脚
	GPIOA挂载在RCC的AHB1总线
**************************************************/
void DHT11_Init(void)
{
	//1.使能GPIOA外设时钟 RCC的AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//2.配置GPIOA3 引脚(注意事项:什么时候才能用或方法 , 当他们都在同一个32位寄存器组中)
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;						//模式:输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//类型:推挽
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3;						//引脚:3
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//状态:上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;					//速度:高速
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	//GPIO初始化
}


/************************************************
函数名:void DHT11_Reset(void)
功能:主机发送 复位信号给 DHT11
参数:无
返回值:无
说明:
	主发_从接
**************************************************/
void DHT11_Reset(void)
{
	//1.设置引脚为输出模式
	DHT11_Init_OUT();
	
	//2.拉低数据线至少保持18ms
	DHT11_OUT = 0;	//拉低0,保持20ms
	delay_ms(20);
	
	//3.拉高数据线保持20 - 40us
	DHT11_OUT = 1;	//拉低0,保持30us
	delay_us(30);
}


/************************************************
函数名:int DHT11_Check(void)
功能:等待DHT11 响应,判断是否存在
参数:无
返回值:
	存在:0   
	不存在:!0
说明:
	主收_从发
**************************************************/
int DHT11_Check(void)
{
	int timer = 0;	//用于计时
	//1.设置主机为输入模式
	DHT11_Init_IN();
	
	//2.等待数据线拉低
	timer = 0;
	while(DHT11_IN == 1)	//死等拉低
	{
		delay_us(1);
		timer++;
		if(timer > 100) return -1;	//不存在
	}
	
	//3.等待数据线拉高
	timer = 0;
	while(DHT11_IN == 0)	//死等拉高
	{
		delay_us(1);
		timer++;
		if(timer > 100) return -1;	//不存在
	}
	
	//4.延时40us
	delay_us(40);
	
	return 0;	//存在
}


/************************************************
函数名:u8 DHT11_Read_Bit(void)
功能:读取DHT11发送过来的1 bit数据
参数:无
返回值:比特值
说明:
	主收_从发
**************************************************/
u8 DHT11_Read_Bit(void)
{
	int timer = 0;	//用于计时
	//1.设置主机为输入模式
	DHT11_Init_IN();
	
	//2.等待DHT11拉低电平
	timer = 0;
	while(DHT11_IN == 1)	//死等拉低
	{
		delay_us(1);
		timer++;
		if(timer > 100) return 0;
	}
	
	//3.等待DHT11拉高电平
	timer = 0;
	while(DHT11_IN == 0)	//死等拉高
	{
		delay_us(1);
		timer++;
		if(timer > 100) return 0;
	}
	
	//4.判断保持的时间
	delay_us(30);      //等待0极限 26 - 28 us,就会被拉低,如果没有被拉低,说明就是 1
	
	return DHT11_IN;
}

/***************************************
函数名:u8 DHT11_Read_Byte(void)
功能:DHT11 读取1字节数据
参数:无
返回值: 数值
说明:高位先出,先存储到高位
例如:10101000
接收:
	每次读取则左移
***************************************/
u8 DHT11_Read_Byte(void)
{
	u8 data = 0;
	for(int i = 0; i < 8;i++)
	{
		data <<= 1;	//先左移
		data |= DHT11_Read_Bit();
	}
	
	return data;
}

/*******************************************************************************************
函数名:int DHT11_Read_Data(u8 *HumiH,u8 *HumiL,u8 *TempH,u8 *TempL)
功能:DHT11 读取温度和湿度
参数:
	@HumiH:湿度高位
	@HumiL:湿度低位
	@TempH:温度高位
	@TempL:温度低位
返回值: 
	成功:0
	失败:-1	
*******************************************************************************************/
int DHT11_Read_Data(u8 *HumiH,u8 *HumiL,u8 *TempH,u8 *TempL)
{
	DHT11_Init();	//初始化
	//1.发送复位信号
	DHT11_Reset();
	
	//2.等待响应
	if(DHT11_Check() != 0) return -1;
	
	//3.接收数据
	u8 Data[5] = {0}; 
	for(int i = 0; i < 5;i++)
	{
		Data[i] = DHT11_Read_Byte();	//读取1字节
	}
	
	//4.判断校验
	if(Data[0] + Data[1] + Data[2] + Data[3] == Data[4])
	{
		*HumiH = Data[0];	//湿度高位
		*HumiL = Data[1];	//湿度低位
		*TempH = Data[2];	//温度高位
		*TempL = Data[3];	//温度低位
		return 0; //成功
	}
	
	return -1;	//失败
}



