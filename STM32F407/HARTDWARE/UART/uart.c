/**************************************************************
文件名:uart.c
作者:王廷胡
邮箱:1299030893@qq.com
说明:主要用于UART|USART串口相关操作
创建时间:2023年7月27日  10:00
修改时间:
	1.2023年7月27日  10:35		王廷胡{优化初始化}
***************************************************************/
#include "uart.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*************************************
函数名:void UART1_Init(u32 bound);
功能:UART1串口初始化
参数:
	@bound：波特率
返回值:无
说明:(原理图)
	TXD 对应的引脚编号 PA9
	RXD 对应的引脚编号 PA10
**************************************/
void UART1_Init(u32 bound)
{
	//1.时钟使能 GPIOA在AHB1总线 和 USART1在APB2总线
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//GPIOA使能在AHB1总线 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//USART1使能APB2总线
	
	//2.GPIO初始化为复用功能
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10;	//引脚9,10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			//AF复用功能
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//3.设置复用功能选择
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//4.配置串口初始化
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_BaudRate = bound;										//波特率:用户参数传入
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流:无
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;						//模式:收发
	USART_InitStruct.USART_Parity = USART_Parity_No;								//校验位:无校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;								//停止位:1位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;						//数据位:8位
	
	USART_Init(USART1, &USART_InitStruct);
	
	//5.使能串口
	USART_Cmd(USART1, ENABLE);
	
	//6.开启接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//7.配置中断
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel	 = USART1_IRQn;	//通道:USART1_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//使能:
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级:2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//响应优先级:2
	
	
	NVIC_Init(&NVIC_InitStruct);
}

/******************************************************
串口中断服务函数:USART1
*******************************************************/
#include "stdio.h"
#include "string.h"
#include "beep.h"
#include "led.h"
char buff[100];
int ind = 0;
void USART1_IRQHandler()
{
	u8 ret;
	//1.获取中断状态:接收中断,有数据可读
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)	//判断是否有数据可读
	{
		ret = USART_ReceiveData(USART1);
		USART_SendData(USART2,ret);			//将数据发给串口2，用于传给 WIFI 模块
		/*------ 反发回去 ------*/
		buff[ind] = ret;	//存入字符数组中
		
		if(buff[ind] == '\n' && buff[ind-1] == '\r')	//hello world\0\n
		{
			buff[ind-1] = '\0';	//字符串末尾处理 '\0' 结尾
			/*----------- 自行处理 ----------------*/
			if(strcmp(buff,"LED1:ON") == 0)
			{
				LED1 = 0;
			}
			else if(strcmp(buff,"LED1:OFF") == 0)
			{
				LED1 = 1;
			}
			else if(strcmp(buff,"BEEP") == 0)
			{
				BEEP = !BEEP;
			}
			/*----------- 处理完成 ---------------*/
			ind = -1;
		}
		ind++;
	}
	
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//清空串口1接收中断位
}

/*******************************************************
函数名:u8 USART1_Send_Data(u8 *data,u32 len)
功能:串口1发送指定长度内容
参数:
	@data:数据首地址
	@len:数据长度
返回值:
	成功发送的字节数
*******************************************************/
u8 USART1_Send_Data(u8 *data,u32 len)
{
	for(int i = 0; i < len;i++)
	{
		//获取发送空闲状态 
		while((USART1->SR & 0x40) == 0)
		{
			;	//进入循环等待
		}
		USART1->DR = data[i];
	}
	
	return len;
}

/******************************************************
函数名:int fputc(int ch,FILE *fp)
功能:重写 重定向 printf 调用的 fputc 单字节输出
参数:
	@ch:发送的字符
	@fp:文件流对象指针
返回值:
	成功写入的字符
使用 stdio.h 是需要打开微库
********************************************************/
#include "stdio.h"
int fputc(int ch,FILE *fp)
{
	while((USART1->SR & 0x40) == 0)
	{
		;	//进入循环等待
	}
	USART1->DR = ch;
	return ch;
}

/*---------------------------------------------------- 串口相关功能 ----------------------------------------------------------*/
/*************************************
函数名:void UART2_Init(u32 bound);
功能:UART2串口初始化
参数:
	@bound：波特率
返回值:无
说明:(原理图)
	TXD 对应的引脚编号 PD5
	RXD 对应的引脚编号 PD6
**************************************/
void UART2_Init(u32 bound)
{
	//1.时钟使能 GPIOD在AHB1总线 和 USART1在APB1总线
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//GPIOD使能在AHB1总线 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//USART2使能APB1总线
	
	//2.GPIO初始化为复用功能
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6;	//引脚5,6
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			//AF复用功能
	
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//3.设置复用功能选择
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	
	//4.配置串口初始化
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_BaudRate = bound;										//波特率:用户参数传入
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流:无
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;						//模式:收发
	USART_InitStruct.USART_Parity = USART_Parity_No;								//校验位:无校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;								//停止位:1位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;						//数据位:8位
	
	USART_Init(USART2, &USART_InitStruct);
	
	//5.使能串口
	USART_Cmd(USART2, ENABLE);
	
	//6.开启接收中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	//7.配置中断
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel	 = USART2_IRQn;	//通道:USART2_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//使能:
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级:2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;			//响应优先级:2
	
	NVIC_Init(&NVIC_InitStruct);
}
/******************************************************
串口中断服务函数:USART2
*******************************************************/
char UART2_BUFF[200];
u8 UART2_INDEX = 0;	//当前数组下标
u8 UART2_FLAG = 0;	//数据结束标志
void USART2_IRQHandler()
{
	u8 ret;
	//1.获取中断状态:接收中断,有数据可读
	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) == SET)	//判断是否有数据可读
	{
		ret = USART_ReceiveData(USART2);
		UART2_BUFF[UART2_INDEX] = ret;
		/*----------- 接受并处理:WIFI发回的数据都带 \r\n ---------------*/
		if(UART2_BUFF[UART2_INDEX-1] == '\r' && UART2_BUFF[UART2_INDEX] == '\n')	//表示1次数据结束
		{
			UART2_FLAG = 1;	//标志 置1
			UART2_BUFF[UART2_INDEX-1] = '\0';
			//printf("尾部:%c\r\n",UART2_BUFF[UART2_INDEX-2]);
		}
		UART2_INDEX++;
		USART_SendData(USART1,ret);				//转发给串口1,到我们的电脑显示
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);	//清空串口2接收中断位
}

/****************************************************
函数:u32 UART2_Send_String(char *data)
功能:串口2发送字符串
参数:
	@data：要发送的字符串
返回:成功发送的字节
*****************************************************/
u32 UART2_Send_String(char *data)
{
	
	int len = 0;
	while(data[len] != '\0')
	{
		while((USART2->SR & 0x40) == 0)
		{
			;	//进入循环等待
		}
		USART2->DR = data[len];
		len++;
	}

	return len;
}

u32 UART2_Send_Data(char *data,int len)
{
	for(int i = 0; i < len;i++)
	{
		while((USART2->SR & 0x40) == 0)
		{
			;	//进入循环等待
		}
		USART2->DR = data[i];
	}

	return len;
}

#define USART2_Send_String UART2_Send_String
/****************************************************
void WIFI_Connect(char *SSID,char *PASS)
功能:连接WIFI 
参数:
	@SSID：WIFI名称
	@PASS：WIFI密码
***************************************************/
void WIFI_Connect(char *SSID,char *PASS)
{
	char buf[100];
	sprintf(buf,"AT+RST\r\n");
	UART2_Send_String(buf);
	delay_ms(1000);		//延时1000等待结果
	/*---------- 1.配置模式为 STA 模式 -----------*/
	sprintf(buf,"AT+CWMODE=1\r\n");
	UART2_Send_String(buf);
	delay_ms(500);		//延时500等待结果
	UART2_FLAG = 0;UART2_INDEX = 0;	//方便串口下次接收数据
	
	/*---------- 2.连接WIFI模块 ------------------*/
	sprintf(buf,"AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,PASS);
	UART2_Send_String(buf);
	while(1)
	{
		if(UART2_FLAG == 1)
		{
			UART2_FLAG = 0;UART2_INDEX = 0;	//方便串口下次接收数据
			if(strcmp(UART2_BUFF,"OK") == 0) break;
		}
	}
	printf("连接WIFI成功\r\n");
}

/***************************************************
函数:void TCP_Connect(char *ip,int port)
功能:连接TCP服务器
参数:
	@ip：IP地址
	@port：端口号
***************************************************/
void TCP_Connect(char *ip,int port)
{
	char buf[100];
	/*---------- 1.连接TCP服务器 ------------------*/
	sprintf(buf,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",ip,port);
	UART2_Send_String(buf);
	if(Wait_OK() == 0)
		printf("连接TCP服务器成功\r\n");
}

/**************************************************
函数:int TCP_Get_Message(char *message)
功能:获取WIFI模块数据:
参数:
	@message:存放数据的地址
返回:
	成功:0
	失败:-1
***************************************************/
int TCP_Get_Message(char *message)
{
	if(UART2_FLAG == 0) return -1;
	char *buff = UART2_BUFF;	//获取缓存区地址
	/*----------------- 恢复缓存区接受功能 -----------------*/
	UART2_FLAG = 0;UART2_INDEX = 0;	
	/*----------------- 处理数据拷贝 -----------------------*/
	if(strstr(buff,"+IPD") == NULL) return -1;
	
	/*----------------- 进行数据拷贝 -----------------------*/
	buff = strstr(buff,":")+1;
	strcpy(message,buff);
	
	return 0;
}


/**************************************************
函数:void TCP_Put_Message(char *data,int size)
功能:发送WIFI模块数据:
参数:
	@data:要发送的数据
	@message:存放数据的地址
***************************************************/
void TCP_Put_Message(char *data,int size)
{
	char buf[100];
	/*---------- 1.发送指定包头大小 ------------------*/
	sprintf(buf,"AT+CIPSEND=%d\r\n",size);
	UART2_Send_String(buf);
	while(1)
	{
		if(UART2_FLAG == 1)
		{
			UART2_FLAG = 0;UART2_INDEX = 0;	//方便串口下次接收数据
			if(strcmp(UART2_BUFF,"OK") == 0) break;
		}
	}
	/*---------- 2.发送指定数据-----------------------*/
	UART2_Send_Data(data,size);
	while(1)
	{
		if(UART2_FLAG == 1)
		{
			UART2_FLAG = 0;UART2_INDEX = 0;	//方便串口下次接收数据
			if(strcmp(UART2_BUFF,"SEND OK") == 0) break;
		}
	}
}

/*------------------------------------------- MQTT 相关函数 -----------------------------------------*/
/*******************************************************
函数名:void MQTT_Connect(char *ip,char *port)
功能:连接MQTT云
参数:
	@ip:地址
	@port:端口
返回值:
	成功:0
	失败:-1
*******************************************************/
void MQTT_Connect(char *ip,char *port)
{
	char buf[100] = "";
	/*---------------------- 2.设置自身client ID -------------------------------------*/
	sprintf(buf,"AT+MQTTUSERCFG=0,1,\"%s\",\"\",\"\",0,0,\"\"\r\n",ChipID);	
	USART2_Send_String(buf);
	if(Wait_OK() == 0)
	printf("设置MQTT的client成功\r\n");
	/*---------------------- 3.连接MQTT服务器 ----------------------------------------*/
	UART2_FLAG  = 0;UART2_INDEX = 0;
	sprintf(buf,"AT+MQTTCONN=0,\"%s\",%s,0\r\n",ip,port);
	USART2_Send_String(buf);
	if(Wait_OK() == 0)
	printf("连接MQTT成功\r\n");
}

/*******************************************************
函数名:void MQTT_Subscribe(char *tipname)
功能:订阅MQTT主题
参数:
	@tipname:主题字
*******************************************************/
void MQTT_Subscribe(char *tipname)
{
	char buf[100] = "";
	//AT+MQTTSUB=0,"004B00553431510D33393332",1
	sprintf(buf,"AT+MQTTSUB=0,\"%s\",1\r\n",tipname);
	printf("正在订阅MQTT主题:%s\r\n",tipname);
	USART2_Send_String(buf);
	delay_ms(200);
	UART2_FLAG  = 0;UART2_INDEX = 0;
	printf("\r\n订阅MQTT主题成功\r\n");
}


/*******************************************************
函数名:int MQTT_Get_Message(char *message)
功能:接收MQTT数据
参数:
	@message:数据
返回值:
	成功:0
	失败:-1
*******************************************************/
int MQTT_Get_Message(char *message)
{
	if(UART2_FLAG == 0) return -1;
	/*----------- 恢复接收缓存区 ---------*/
	UART2_FLAG  = 0;UART2_INDEX = 0;
	char *buff = UART2_BUFF;
	/*----------- 处理数据 ---------------*/
	if(strstr(buff,"+MQTTSUBRECV") == NULL) return -1;
	buff = strstr(buff,"\",")+2;
	buff = strstr(buff,",")+1;
	strcpy(message,buff);
	return 0;
}

/*********************************************************************************
功能:字符串 " 和 , 符号前加 \ 反斜杠因为esp8266使用逗号判断数据间隔
*********************************************************************************/
char* remove_tabs_newlines(const char* str) {
    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < len; i++) {
        if (str[i] != '\t' && str[i] != '\n') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

char* escape_quotes(const char* str) {
    size_t len = strlen(str);
    char* result = malloc(len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < len; i++) {
        if (str[i] == '\"' || str[i] == ',') {
            result[j++] = '\\';
        }
        result[j++] = str[i];
    }
    result[j] = '\0';

    char* sanitized_result = remove_tabs_newlines(result);
    free(result);

    return sanitized_result;
}



/*********************************************************************************
函数名:u32 MQTT_Put_Message(char *topicName,char *message)
功能:发送MQTT数据
参数:
	@topicName:主题
	@message:数据
返回值:
	成功发送的字节数
*********************************************************************************/
#include "delay.h"
u32 MQTT_Put_Message(char *topicName,char *message)
{
	char buf[300];
	u32 len = 0;
	char* escaped = escape_quotes(message);	//需要将消息里面的逗号转义和引号
	sprintf(buf,"AT+MQTTPUB=0,\"%s\",\"%s\",1,0\r\n",topicName,escaped);
	len = USART2_Send_String(buf);
	free(escaped);
	Wait_OK();
	return len;
}

int Wait_OK()
{
	u32 timer = 0;
	while(1){
		delay_us(1);timer++;
		if(timer > 500000L) return -1;
		if(UART2_FLAG == 1)
		{	
			UART2_FLAG  = 0;UART2_INDEX = 0;
			if(strcmp(UART2_BUFF,"OK") == 0) break;
		}
	}
	return 0;
}

