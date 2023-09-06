/**************************************************************
�ļ���:dht11.c
����:��͢��
����:1299030893@qq.com
˵��:��Ҫ���ڵ�����Э���dht11������ز���
����ʱ��:2023��7��27��  10:00
�޸�ʱ��:
***************************************************************/
#include "dht11.h"
#include "delay.h"
/*************************************************
������:void DHT11_Init(void)
����:��ʼ��DHT11��ʪ��ģ��
����:��
����ֵ:��
˵��:
	DHT11_DATA ---- GPIOA 3����
	GPIOA������RCC��AHB1����
**************************************************/
void DHT11_Init(void)
{
	//1.ʹ��GPIOA����ʱ�� RCC��AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//2.����GPIOA3 ����(ע������:ʲôʱ������û򷽷� , �����Ƕ���ͬһ��32λ�Ĵ�������)
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;						//ģʽ:���ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//����:����
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3;						//����:3
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//״̬:����
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;					//�ٶ�:����
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	//GPIO��ʼ��
}


/************************************************
������:void DHT11_Reset(void)
����:�������� ��λ�źŸ� DHT11
����:��
����ֵ:��
˵��:
	����_�ӽ�
**************************************************/
void DHT11_Reset(void)
{
	//1.��������Ϊ���ģʽ
	DHT11_Init_OUT();
	
	//2.�������������ٱ���18ms
	DHT11_OUT = 0;	//����0,����20ms
	delay_ms(20);
	
	//3.���������߱���20 - 40us
	DHT11_OUT = 1;	//����0,����30us
	delay_us(30);
}


/************************************************
������:int DHT11_Check(void)
����:�ȴ�DHT11 ��Ӧ,�ж��Ƿ����
����:��
����ֵ:
	����:0   
	������:!0
˵��:
	����_�ӷ�
**************************************************/
int DHT11_Check(void)
{
	int timer = 0;	//���ڼ�ʱ
	//1.��������Ϊ����ģʽ
	DHT11_Init_IN();
	
	//2.�ȴ�����������
	timer = 0;
	while(DHT11_IN == 1)	//��������
	{
		delay_us(1);
		timer++;
		if(timer > 100) return -1;	//������
	}
	
	//3.�ȴ�����������
	timer = 0;
	while(DHT11_IN == 0)	//��������
	{
		delay_us(1);
		timer++;
		if(timer > 100) return -1;	//������
	}
	
	//4.��ʱ40us
	delay_us(40);
	
	return 0;	//����
}


/************************************************
������:u8 DHT11_Read_Bit(void)
����:��ȡDHT11���͹�����1 bit����
����:��
����ֵ:����ֵ
˵��:
	����_�ӷ�
**************************************************/
u8 DHT11_Read_Bit(void)
{
	int timer = 0;	//���ڼ�ʱ
	//1.��������Ϊ����ģʽ
	DHT11_Init_IN();
	
	//2.�ȴ�DHT11���͵�ƽ
	timer = 0;
	while(DHT11_IN == 1)	//��������
	{
		delay_us(1);
		timer++;
		if(timer > 100) return 0;
	}
	
	//3.�ȴ�DHT11���ߵ�ƽ
	timer = 0;
	while(DHT11_IN == 0)	//��������
	{
		delay_us(1);
		timer++;
		if(timer > 100) return 0;
	}
	
	//4.�жϱ��ֵ�ʱ��
	delay_us(30);      //�ȴ�0���� 26 - 28 us,�ͻᱻ����,���û�б�����,˵������ 1
	
	return DHT11_IN;
}

/***************************************
������:u8 DHT11_Read_Byte(void)
����:DHT11 ��ȡ1�ֽ�����
����:��
����ֵ: ��ֵ
˵��:��λ�ȳ�,�ȴ洢����λ
����:10101000
����:
	ÿ�ζ�ȡ������
***************************************/
u8 DHT11_Read_Byte(void)
{
	u8 data = 0;
	for(int i = 0; i < 8;i++)
	{
		data <<= 1;	//������
		data |= DHT11_Read_Bit();
	}
	
	return data;
}

/*******************************************************************************************
������:int DHT11_Read_Data(u8 *HumiH,u8 *HumiL,u8 *TempH,u8 *TempL)
����:DHT11 ��ȡ�¶Ⱥ�ʪ��
����:
	@HumiH:ʪ�ȸ�λ
	@HumiL:ʪ�ȵ�λ
	@TempH:�¶ȸ�λ
	@TempL:�¶ȵ�λ
����ֵ: 
	�ɹ�:0
	ʧ��:-1	
*******************************************************************************************/
int DHT11_Read_Data(u8 *HumiH,u8 *HumiL,u8 *TempH,u8 *TempL)
{
	DHT11_Init();	//��ʼ��
	//1.���͸�λ�ź�
	DHT11_Reset();
	
	//2.�ȴ���Ӧ
	if(DHT11_Check() != 0) return -1;
	
	//3.��������
	u8 Data[5] = {0}; 
	for(int i = 0; i < 5;i++)
	{
		Data[i] = DHT11_Read_Byte();	//��ȡ1�ֽ�
	}
	
	//4.�ж�У��
	if(Data[0] + Data[1] + Data[2] + Data[3] == Data[4])
	{
		*HumiH = Data[0];	//ʪ�ȸ�λ
		*HumiL = Data[1];	//ʪ�ȵ�λ
		*TempH = Data[2];	//�¶ȸ�λ
		*TempL = Data[3];	//�¶ȵ�λ
		return 0; //�ɹ�
	}
	
	return -1;	//ʧ��
}



