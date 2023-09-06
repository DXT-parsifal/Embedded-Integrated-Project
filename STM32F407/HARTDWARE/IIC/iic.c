
#include "iic.h"
#include "delay.h"
/*************************************************
函数名:void IIC_Init(void)
功能:初始化IIC
参数:无
返回值:无
说明:
	数据线SCL -----> PB6
	数据线SDA -----> PB7
	GPIOB挂载在RCC的AHB1总线
**************************************************/
void IIC_Init(void)
{
	//1.使能GPIOB外设时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//2.初始化GPIO引脚
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	//输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD; //类型:开漏模式
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	//状态:上拉
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//引脚:6和7
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	//3.设置电平为空闲
	I2C_SCL = 1;
	I2C_SDA = 1;
}

/***************************************************
函数名:void IIC_Start(void)
功能:IIC起始信号
参数:
返回值:
说明:
	时钟线高电平期间,数据线由高变低
****************************************************/
void IIC_Start(void)
{
	//1.将数据线设置为输出模式
	I2C_OUT();
	
	//2.设置时钟线和数据线都为高电平,保持 >4.7 um
	I2C_SCL = 1;
	I2C_SDA = 1;
	/*--------- 维持 4.7 us 时间 ---------------*/
	delay_us(IIC_DELAY);
	
	//3.设置数据线拉低,保持 > 4.7 us
	I2C_SDA = 0;
	/*--------- 维持 4.7 us 时间 ---------------*/
	delay_us(IIC_DELAY);
	
	//4.好像看到时钟线往下拉了
	I2C_SCL = 0;
}

/***************************************************
函数名:void IIC_Stop(void)
功能:IIC终止信号
参数:
返回值:
说明:
	时钟线高电平期间,数据线由低变高
****************************************************/
void IIC_Stop(void)
{
	//1.将数据线设置为输出模式
	I2C_OUT();
	
	//2.看到数据线和时钟线一开始都为低电平
	I2C_SCL = 0;
	I2C_SDA = 0;
	
	//3.看到时钟线拉高,保持4us
	I2C_SCL = 1;
	/*--------- 维持 4.7 us 时间 ---------------*/
	delay_us(IIC_DELAY);
	
	//4.看到随后数据线也拉高4us时间
	I2C_SDA = 1;
	/*--------- 维持 4.7 us 时间 ---------------*/
	delay_us(IIC_DELAY);
	/*----- 进入总线空闲,反正 数据线和时钟线都是处于高电平 ----*/
}

/***************************************************
函数名:void IIC_Ack(void)
功能:IIC主机产生应答信号
参数:
返回值:
说明:
****************************************************/
void IIC_Ack(void)
{
	
	//1.将数据线设置为输出模式
	I2C_OUT();
	//2.看到数据线拉低,时钟线拉高保持 4us
	I2C_SCL = 0;	//时钟线低电平
	I2C_SDA = 0;	//数据线
	/*--------- 维持 4.7 us 时间 ---------------*/
	delay_us(IIC_DELAY);
	/*------- 准备好数据,将时钟线电平拉高发送 ------*/
	I2C_SCL = 1;
	/*--------- 维持 4.7 us 时间 ---------------*/
	delay_us(IIC_DELAY);
    
    I2C_SCL = 0;	//时钟线低电平
}


/***************************************************
函数名:void IIC_NAck(void)
功能:IIC主机产生非应答信号
参数:
返回值:
说明:
****************************************************/
void IIC_NAck(void)
{
	I2C_OUT();	//将数据线变为输出模式
	
	I2C_SCL = 0;	//时钟线低电平
	delay_us(IIC_DELAY);
	/*------- 输出 高电平 1 -------- */
	I2C_SDA = 1;	//数据线
	delay_us(IIC_DELAY);
	/*------- 准备好数据,将时钟线电平拉高发送 ------*/
	I2C_SCL = 1;
	/*--------- 高电平延时------------*/
	delay_us(IIC_DELAY);
	/*-------- 数据已经发完,将时钟线拉低 ---------*/
	I2C_SCL = 0;
}

/***************************************************
函数名:int IIC_Wait_Ack(void)
功能:IIC主机等待从机应答
参数:
返回值:
	应答:0
	非应答:-1
****************************************************/
int IIC_Wait_Ack(void)
{
	int timer = 0;
	//1.将数据线设置为输出模式
	I2C_OUT();
	
	//2.将数据线和时钟线拉高,等待从机拉低产生应答
	I2C_SDA = 1;
	I2C_SCL = 1;
	delay_us(IIC_DELAY);
	//3.设置数据线为输入模式
	I2C_IN();
	
	//4.循环等待从机应答
	timer = 0;
	while(READ_SDA == 1)
	{
		timer++;
		delay_us(1);
		if(timer > 20) //说明没有响应
		{
			IIC_Stop();	//发送停止信号,我不干了
			return -1;
		}
	}
	
	//5.将时钟线拉低
	I2C_SCL = 0;
	delay_us(IIC_DELAY);		//一定要去等延时
	
	return 0;	//应答了
}

/*********************************************
函数名:void IIC_Send_Byte(u8 data)
功能:发送1字节数据
参数:
	@data：数据
*********************************************/
void IIC_Send_Byte(u8 data)
{
	//1.将数据线设置为输出模式
	I2C_OUT();
	
	//2.将时钟线拉低,准备开始写数据
	I2C_SCL = 0;
	
	//3.循环写bit数据  1000 0000  == 0x80   & data   在 >> 7位
	for(int i = 0; i < 8; i++)
	{
		I2C_SDA = (data&0x80) >> 7;	//发送数据
		data <<= 1;
		/**** 等待将数据写入到引脚 ****/
		delay_us(IIC_DELAY);
		
		I2C_SCL = 1;	//拉高发送数据
		//等待时间保持状态
		delay_us(IIC_DELAY);
		
		//拉低写入数据
		I2C_SCL = 0;
		delay_us(IIC_DELAY);
	}
}

/*********************************************
函数名:u8 IIC_Read_Byte(void)
功能:读取1字节数据
参数:
返回值:数据
*********************************************/
u8 IIC_Read_Byte(void)
{
	u8 data = 0;
	//1.设置数据线为输入模式
	I2C_IN();	
	
	//2.循环读取8个比特
	for(int i = 0; i < 8;i++)
	{
		I2C_SCL = 0;
		delay_us(IIC_DELAY);
		
		I2C_SCL = 1;	//等待接收数据,可以被从机拉低 
		delay_us(IIC_DELAY);
		
		data <<= 1;
		data |= READ_SDA;	//读取数据线电平
	}
	
	return data;
}





