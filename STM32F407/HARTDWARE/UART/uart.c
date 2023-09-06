/**************************************************************
�ļ���:uart.c
����:��͢��
����:1299030893@qq.com
˵��:��Ҫ����UART|USART������ز���
����ʱ��:2023��7��27��  10:00
�޸�ʱ��:
	1.2023��7��27��  10:35		��͢��{�Ż���ʼ��}
***************************************************************/
#include "uart.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void UART1_Init(u32 bound)
{
	//1.ʱ��ʹ�� GPIOA��AHB1���� �� USART1��APB2����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//GPIOAʹ����AHB1���� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//USART1ʹ��APB2����
	
	//2.GPIO��ʼ��Ϊ���ù���
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10;	//����9,10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			//AF���ù���
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//3.���ø��ù���ѡ��
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//4.���ô��ڳ�ʼ��
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_BaudRate = bound;										//������:�û���������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ����:��
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;						//ģʽ:�շ�
	USART_InitStruct.USART_Parity = USART_Parity_No;								//У��λ:��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;								//ֹͣλ:1λ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;						//����λ:8λ
	
	USART_Init(USART1, &USART_InitStruct);
	
	//5.ʹ�ܴ���
	USART_Cmd(USART1, ENABLE);
	
	//6.���������ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//7.�����ж�
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel	 = USART1_IRQn;	//ͨ��:USART1_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//ʹ��:
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�:2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			//��Ӧ���ȼ�:2
	
	
	NVIC_Init(&NVIC_InitStruct);
}

/******************************************************
�����жϷ�����:USART1
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
	//1.��ȡ�ж�״̬:�����ж�,�����ݿɶ�
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)	//�ж��Ƿ������ݿɶ�
	{
		ret = USART_ReceiveData(USART1);
		USART_SendData(USART2,ret);			//�����ݷ�������2�����ڴ��� WIFI ģ��
		/*------ ������ȥ ------*/
		buff[ind] = ret;	//�����ַ�������
		
		if(buff[ind] == '\n' && buff[ind-1] == '\r')	//hello world\0\n
		{
			buff[ind-1] = '\0';	//�ַ���ĩβ���� '\0' ��β
			/*----------- ���д��� ----------------*/
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
			/*----------- ������� ---------------*/
			ind = -1;
		}
		ind++;
	}
	
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//��մ���1�����ж�λ
}

/*******************************************************
������:u8 USART1_Send_Data(u8 *data,u32 len)
����:����1����ָ����������
����:
	@data:�����׵�ַ
	@len:���ݳ���
����ֵ:
	�ɹ����͵��ֽ���
*******************************************************/
u8 USART1_Send_Data(u8 *data,u32 len)
{
	for(int i = 0; i < len;i++)
	{
		//��ȡ���Ϳ���״̬ 
		while((USART1->SR & 0x40) == 0)
		{
			;	//����ѭ���ȴ�
		}
		USART1->DR = data[i];
	}
	
	return len;
}

/******************************************************
������:int fputc(int ch,FILE *fp)
����:��д �ض��� printf ���õ� fputc ���ֽ����
����:
	@ch:���͵��ַ�
	@fp:�ļ�������ָ��
����ֵ:
	�ɹ�д����ַ�
ʹ�� stdio.h ����Ҫ��΢��
********************************************************/
#include "stdio.h"
int fputc(int ch,FILE *fp)
{
	while((USART1->SR & 0x40) == 0)
	{
		;	//����ѭ���ȴ�
	}
	USART1->DR = ch;
	return ch;
}

/*---------------------------------------------------- ������ع��� ----------------------------------------------------------*/
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
void UART2_Init(u32 bound)
{
	//1.ʱ��ʹ�� GPIOD��AHB1���� �� USART1��APB1����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//GPIODʹ����AHB1���� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//USART2ʹ��APB1����
	
	//2.GPIO��ʼ��Ϊ���ù���
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6;	//����5,6
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;			//AF���ù���
	
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//3.���ø��ù���ѡ��
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	
	//4.���ô��ڳ�ʼ��
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_BaudRate = bound;										//������:�û���������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ����:��
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;						//ģʽ:�շ�
	USART_InitStruct.USART_Parity = USART_Parity_No;								//У��λ:��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;								//ֹͣλ:1λ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;						//����λ:8λ
	
	USART_Init(USART2, &USART_InitStruct);
	
	//5.ʹ�ܴ���
	USART_Cmd(USART2, ENABLE);
	
	//6.���������ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	//7.�����ж�
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel	 = USART2_IRQn;	//ͨ��:USART2_IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//ʹ��:
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�:2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;			//��Ӧ���ȼ�:2
	
	NVIC_Init(&NVIC_InitStruct);
}
/******************************************************
�����жϷ�����:USART2
*******************************************************/
char UART2_BUFF[200];
u8 UART2_INDEX = 0;	//��ǰ�����±�
u8 UART2_FLAG = 0;	//���ݽ�����־
void USART2_IRQHandler()
{
	u8 ret;
	//1.��ȡ�ж�״̬:�����ж�,�����ݿɶ�
	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) == SET)	//�ж��Ƿ������ݿɶ�
	{
		ret = USART_ReceiveData(USART2);
		UART2_BUFF[UART2_INDEX] = ret;
		/*----------- ���ܲ�����:WIFI���ص����ݶ��� \r\n ---------------*/
		if(UART2_BUFF[UART2_INDEX-1] == '\r' && UART2_BUFF[UART2_INDEX] == '\n')	//��ʾ1�����ݽ���
		{
			UART2_FLAG = 1;	//��־ ��1
			UART2_BUFF[UART2_INDEX-1] = '\0';
			//printf("β��:%c\r\n",UART2_BUFF[UART2_INDEX-2]);
		}
		UART2_INDEX++;
		USART_SendData(USART1,ret);				//ת��������1,�����ǵĵ�����ʾ
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);	//��մ���2�����ж�λ
}

/****************************************************
����:u32 UART2_Send_String(char *data)
����:����2�����ַ���
����:
	@data��Ҫ���͵��ַ���
����:�ɹ����͵��ֽ�
*****************************************************/
u32 UART2_Send_String(char *data)
{
	
	int len = 0;
	while(data[len] != '\0')
	{
		while((USART2->SR & 0x40) == 0)
		{
			;	//����ѭ���ȴ�
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
			;	//����ѭ���ȴ�
		}
		USART2->DR = data[i];
	}

	return len;
}

#define USART2_Send_String UART2_Send_String
/****************************************************
void WIFI_Connect(char *SSID,char *PASS)
����:����WIFI 
����:
	@SSID��WIFI����
	@PASS��WIFI����
***************************************************/
void WIFI_Connect(char *SSID,char *PASS)
{
	char buf[100];
	sprintf(buf,"AT+RST\r\n");
	UART2_Send_String(buf);
	delay_ms(1000);		//��ʱ1000�ȴ����
	/*---------- 1.����ģʽΪ STA ģʽ -----------*/
	sprintf(buf,"AT+CWMODE=1\r\n");
	UART2_Send_String(buf);
	delay_ms(500);		//��ʱ500�ȴ����
	UART2_FLAG = 0;UART2_INDEX = 0;	//���㴮���´ν�������
	
	/*---------- 2.����WIFIģ�� ------------------*/
	sprintf(buf,"AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,PASS);
	UART2_Send_String(buf);
	while(1)
	{
		if(UART2_FLAG == 1)
		{
			UART2_FLAG = 0;UART2_INDEX = 0;	//���㴮���´ν�������
			if(strcmp(UART2_BUFF,"OK") == 0) break;
		}
	}
	printf("����WIFI�ɹ�\r\n");
}

/***************************************************
����:void TCP_Connect(char *ip,int port)
����:����TCP������
����:
	@ip��IP��ַ
	@port���˿ں�
***************************************************/
void TCP_Connect(char *ip,int port)
{
	char buf[100];
	/*---------- 1.����TCP������ ------------------*/
	sprintf(buf,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",ip,port);
	UART2_Send_String(buf);
	if(Wait_OK() == 0)
		printf("����TCP�������ɹ�\r\n");
}

/**************************************************
����:int TCP_Get_Message(char *message)
����:��ȡWIFIģ������:
����:
	@message:������ݵĵ�ַ
����:
	�ɹ�:0
	ʧ��:-1
***************************************************/
int TCP_Get_Message(char *message)
{
	if(UART2_FLAG == 0) return -1;
	char *buff = UART2_BUFF;	//��ȡ��������ַ
	/*----------------- �ָ����������ܹ��� -----------------*/
	UART2_FLAG = 0;UART2_INDEX = 0;	
	/*----------------- �������ݿ��� -----------------------*/
	if(strstr(buff,"+IPD") == NULL) return -1;
	
	/*----------------- �������ݿ��� -----------------------*/
	buff = strstr(buff,":")+1;
	strcpy(message,buff);
	
	return 0;
}


/**************************************************
����:void TCP_Put_Message(char *data,int size)
����:����WIFIģ������:
����:
	@data:Ҫ���͵�����
	@message:������ݵĵ�ַ
***************************************************/
void TCP_Put_Message(char *data,int size)
{
	char buf[100];
	/*---------- 1.����ָ����ͷ��С ------------------*/
	sprintf(buf,"AT+CIPSEND=%d\r\n",size);
	UART2_Send_String(buf);
	while(1)
	{
		if(UART2_FLAG == 1)
		{
			UART2_FLAG = 0;UART2_INDEX = 0;	//���㴮���´ν�������
			if(strcmp(UART2_BUFF,"OK") == 0) break;
		}
	}
	/*---------- 2.����ָ������-----------------------*/
	UART2_Send_Data(data,size);
	while(1)
	{
		if(UART2_FLAG == 1)
		{
			UART2_FLAG = 0;UART2_INDEX = 0;	//���㴮���´ν�������
			if(strcmp(UART2_BUFF,"SEND OK") == 0) break;
		}
	}
}

/*------------------------------------------- MQTT ��غ��� -----------------------------------------*/
/*******************************************************
������:void MQTT_Connect(char *ip,char *port)
����:����MQTT��
����:
	@ip:��ַ
	@port:�˿�
����ֵ:
	�ɹ�:0
	ʧ��:-1
*******************************************************/
void MQTT_Connect(char *ip,char *port)
{
	char buf[100] = "";
	/*---------------------- 2.��������client ID -------------------------------------*/
	sprintf(buf,"AT+MQTTUSERCFG=0,1,\"%s\",\"\",\"\",0,0,\"\"\r\n",ChipID);	
	USART2_Send_String(buf);
	if(Wait_OK() == 0)
	printf("����MQTT��client�ɹ�\r\n");
	/*---------------------- 3.����MQTT������ ----------------------------------------*/
	UART2_FLAG  = 0;UART2_INDEX = 0;
	sprintf(buf,"AT+MQTTCONN=0,\"%s\",%s,0\r\n",ip,port);
	USART2_Send_String(buf);
	if(Wait_OK() == 0)
	printf("����MQTT�ɹ�\r\n");
}

/*******************************************************
������:void MQTT_Subscribe(char *tipname)
����:����MQTT����
����:
	@tipname:������
*******************************************************/
void MQTT_Subscribe(char *tipname)
{
	char buf[100] = "";
	//AT+MQTTSUB=0,"004B00553431510D33393332",1
	sprintf(buf,"AT+MQTTSUB=0,\"%s\",1\r\n",tipname);
	printf("���ڶ���MQTT����:%s\r\n",tipname);
	USART2_Send_String(buf);
	delay_ms(200);
	UART2_FLAG  = 0;UART2_INDEX = 0;
	printf("\r\n����MQTT����ɹ�\r\n");
}


/*******************************************************
������:int MQTT_Get_Message(char *message)
����:����MQTT����
����:
	@message:����
����ֵ:
	�ɹ�:0
	ʧ��:-1
*******************************************************/
int MQTT_Get_Message(char *message)
{
	if(UART2_FLAG == 0) return -1;
	/*----------- �ָ����ջ����� ---------*/
	UART2_FLAG  = 0;UART2_INDEX = 0;
	char *buff = UART2_BUFF;
	/*----------- �������� ---------------*/
	if(strstr(buff,"+MQTTSUBRECV") == NULL) return -1;
	buff = strstr(buff,"\",")+2;
	buff = strstr(buff,",")+1;
	strcpy(message,buff);
	return 0;
}

/*********************************************************************************
����:�ַ��� " �� , ����ǰ�� \ ��б����Ϊesp8266ʹ�ö����ж����ݼ��
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
������:u32 MQTT_Put_Message(char *topicName,char *message)
����:����MQTT����
����:
	@topicName:����
	@message:����
����ֵ:
	�ɹ����͵��ֽ���
*********************************************************************************/
#include "delay.h"
u32 MQTT_Put_Message(char *topicName,char *message)
{
	char buf[300];
	u32 len = 0;
	char* escaped = escape_quotes(message);	//��Ҫ����Ϣ����Ķ���ת�������
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

