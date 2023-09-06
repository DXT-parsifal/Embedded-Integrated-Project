#ifndef __UART_H__
#define __UART_H__
#include "sys.h"

/******* 相关函数声明 ******/
extern char UART2_BUFF[200];
extern u8 UART2_INDEX;	//当前数组下标
extern u8 UART2_FLAG;	//数据结束标志
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
void UART1_Init(u32 bound);

/*******************************************************
函数名:u8 USART1_Send_Data(u8 *data,u32 len)
功能:串口1发送指定长度内容
参数:
	@data:数据首地址
	@len:数据长度
返回值:
	成功发送的字节数
*******************************************************/
u8 USART1_Send_Data(u8 *data,u32 len);

/*------------------------------------------ 串口2相关功能 ----------------------------------------------------------*/


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
void UART2_Init(u32 bound);
/****************************************************
void WIFI_Connect(char *SSID,char *PASS)
功能:连接WIFI 
参数:
	@SSID：WIFI名称
	@PASS：WIFI密码
***************************************************/
void WIFI_Connect(char *SSID,char *PASS);

void MQTT_Connect(char *ip,char *port);					//连接MQTT服务器
void MQTT_Subscribe(char *tipname);						//订阅MQTT主题
int MQTT_Get_Message(char *message);					//获取MQTT主题消息
u32 MQTT_Put_Message(char *topicName,char *message);	//发布MQTT主题消息
int Wait_OK(void);

extern char ChipID[50];	//全局声明


#endif

