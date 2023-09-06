
#include "w25q64.h"
#include "spi.h"
#include "delay.h"
/*************************************************
������:void W25Q64_Init(void)
����:��ʼ��LED
����:��
����ֵ:��
˵��:
	W25Q64_CS ---- GPIOB 2Ƭѡ����
	GPIOB������RCC��AHB1����
**************************************************/
void W25Q64_Init(void)
{
	//1.ʹ������ʱ������ GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//2.����GPIOB 2
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;						//ģʽ:���ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;						//����:����
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2;						//����:2
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;						//״̬:����
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;					//�ٶ�:����
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	//GPIO��ʼ��
	//3.��������Ϊ����״̬
	W25Q64 = 1;
}

/************************************************
����:дʹ��  = 06h
*************************************************/
void W25Q64_Write_Ebale(void)
{
	//1.��Ƭѡ����Ϊ0 
	W25Q64 = 0;
	
	//2.д������
	SPI1_Write_Read(0x06);
	
	//3.��Ƭѡ����Ϊ1 
	W25Q64 = 1;
}

/************************************************
����:��ȡ״̬ �ж��Ƿ�æµ = 05h 
*************************************************/
void W25Q64_Check_Busy(void)
{
	u8 flag = 0;
	do
	{
		//1.��Ƭѡ����Ϊ0 
		W25Q64 = 0;
		
		//2.���Ͷ�ȡ״ָ̬�� 05h
		flag = SPI1_Write_Read(0x05);
		
		//3.��Ƭѡ����Ϊ1 
		W25Q64 = 1;
	}while(flag &0x01 != 0);	//����
}

/************************************************
����:��������(4k)  == 20h
*************************************************/
void W25Q64_Erasr(u32 addr)
{
	//1.ʹ��
	W25Q64_Write_Ebale();
	
	//2.Ƭѡ����
	W25Q64 = 0;
	
	//3.Ƭѡ����ָ��
	SPI1_Write_Read(0x20);
	
	//4.����Ҫ�����ĵ�ַ A23~A16
	SPI1_Write_Read(addr >> 16);
	//5.����Ҫ�����ĵ�ַ A15~A8 
	SPI1_Write_Read(addr >> 8);
	//6.����Ҫ�����ĵ�ַ A7~A0
	SPI1_Write_Read(addr >> 0);
	
	//7.��Ƭѡ����Ϊ1
	W25Q64 = 1;
	
	//8.�ȴ�������ɲ����뿪
	W25Q64_Check_Busy();	//æµ���
	delay_ms(50);
}

/************************************************
����:int W25Q64_Write_Data(u32 addr,u8 *data,u8 len)
����:ҳ��� �������� = 02h 
����:
	@addr����ַ
	@data��Ҫд�������
	@len��Ҫд��ĳ���
����:�ɹ�д������ݳ���
*************************************************/
int W25Q64_Write_Data(u32 addr,u8 *data,u8 len)
{
	//1.ʹ��
	W25Q64_Write_Ebale();
	W25Q64_Check_Busy();	//æµ���
	//2.Ƭѡ����
	W25Q64 = 0;
	
	//3.Ƭѡ����ָ��
	SPI1_Write_Read(0x02);
	
	//4.����Ҫд��ĵ�ַ A23~A16
	SPI1_Write_Read(addr >> 16);
	//5.����Ҫд��ĵ�ַ A15~A8 
	SPI1_Write_Read(addr >> 8);
	//6.����Ҫд��ĵ�ַ A7~A0
	SPI1_Write_Read(addr >> 0);
	
	//7.ѭ��д������ (D7~D0) ... ��һ���ֽ� ...
	for(int i = 0; i < len;i++)
	{
		SPI1_Write_Read(data[i]);
	}
	
	//8.Ƭѡ����
	W25Q64 = 1;
	//9.�ȴ�д���
	W25Q64_Check_Busy();	//æµ���
	
	return len;
}

/******************************************************
����:int W25Q64_Read_Data(u32 addr,u8 *data,u8 len)
����:������ = 03h
����:
	@addr����ַ
	@data����ȡ�����ݴ�ŵĵ�ַ
	@len��Ҫ���ĳ���
����:�ɹ���ȡ�����ݳ���
*******************************************************/
int W25Q64_Read_Data(u32 addr,u8 *data,u8 len)
{
	//1.ʹ��
	W25Q64_Write_Ebale();
	//2.Ƭѡ����
	W25Q64 = 0;
	
	//3.Ƭѡ����ָ��
	SPI1_Write_Read(0x03);
	
	//4.����Ҫ��ȡ�ĵ�ַ A23~A16
	SPI1_Write_Read(addr >> 16);
	//5.����Ҫ��ȡ�ĵ�ַ A15~A8 
	SPI1_Write_Read(addr >> 8);
	//6.����Ҫ��ȡ�ĵ�ַ A7~A0
	SPI1_Write_Read(addr >> 0);
	
	//7.ѭ����ȡ���� (D7~D0)  ... ����
	for(int i = 0; i < len;i++)
	{
		data[i] = SPI1_Write_Read(0xff);	//��ָ��
	}
	//8.Ƭѡ����
	W25Q64 = 1;
	
	return len;
}


