#ifndef __UART_H__
#define __UART_H__
#include "sys.h"

/******* ��غ������� ******/
extern char UART2_BUFF[200];
extern u8 UART2_INDEX;	//��ǰ�����±�
extern u8 UART2_FLAG;	//���ݽ�����־
/*************************************
������:void UART1_Init(u32 bound);
����:UART1���ڳ�ʼ��
����:
	@bound��������
����ֵ:��
˵��:(ԭ��ͼ)
	TXD ��Ӧ�����ű�� PA9
	RXD ��Ӧ�����ű�� PA10
**************************************/
void UART1_Init(u32 bound);

/*******************************************************
������:u8 USART1_Send_Data(u8 *data,u32 len)
����:����1����ָ����������
����:
	@data:�����׵�ַ
	@len:���ݳ���
����ֵ:
	�ɹ����͵��ֽ���
*******************************************************/
u8 USART1_Send_Data(u8 *data,u32 len);

/*------------------------------------------ ����2��ع��� ----------------------------------------------------------*/


/*************************************
������:void UART2_Init(u32 bound);
����:UART2���ڳ�ʼ��
����:
	@bound��������
����ֵ:��
˵��:(ԭ��ͼ)
	TXD ��Ӧ�����ű�� PD5
	RXD ��Ӧ�����ű�� PD6
**************************************/
void UART2_Init(u32 bound);
/****************************************************
void WIFI_Connect(char *SSID,char *PASS)
����:����WIFI 
����:
	@SSID��WIFI����
	@PASS��WIFI����
***************************************************/
void WIFI_Connect(char *SSID,char *PASS);

void MQTT_Connect(char *ip,char *port);					//����MQTT������
void MQTT_Subscribe(char *tipname);						//����MQTT����
int MQTT_Get_Message(char *message);					//��ȡMQTT������Ϣ
u32 MQTT_Put_Message(char *topicName,char *message);	//����MQTT������Ϣ
int Wait_OK(void);

extern char ChipID[50];	//ȫ������


#endif

