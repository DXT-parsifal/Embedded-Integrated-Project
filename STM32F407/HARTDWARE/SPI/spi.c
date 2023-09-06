
#include "spi.h"
/*************************************************
������:void SPI1_Init(void)
����:��ʼ��SPI����
����:��
����ֵ:��
˵��:
	SCLKʱ���� ---- GPIOB 3����
	MISO������ ---- GPIOB 4����
	MOSI������ ---- GPIOB 5����
	
	GPIOB������RCC��AHB1����
**************************************************/
void SPI1_Init(void)
{
	//1.ʹ���ⲿʱ�� SPI1 �� GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//2.��ʼ��GPIOB 3|4|5 ���и���
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//����:3,4,5
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;						//����:����
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//3.����GPIOB 3|4|5 �� SPI ����
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	//4.����SPI��ز�����ʼ��
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	//������,��Ƶϵ����32��Ƶ
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;							//����:0  ��һ��ʱ�ӱ��زɼ�
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low; 							//��λ:0  �͵�ƽ�ɼ�
	SPI_InitStruct.SPI_CRCPolynomial = 0x2; 							//CRCУ��:����ʽУ�鷨
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;						//����λ:8λ
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//����:ȫ˫��
	SPI_InitStruct.SPI_FirstBit =SPI_FirstBit_MSB;						//�ȷ�:��λ�ȷ�
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;							//ģʽ:����
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;								//NSS����:���
	
	SPI_Init(SPI1, &SPI_InitStruct);
	
	//5.ʹ��SPI����
	SPI_Cmd(SPI1, ENABLE);
}

/*************************************************
����:u8 SPI1_Write_Read(u8 data)
����:���� | ���� 1�ֽ�����
����:
	@data��Ҫ���͵�����,����ǽ��տ�����д0x00 | 0xFF

����ֵ:
	@��ȡ������ , �����д������Ը÷���ֵ

˵��: ���ͺͽ��ն���ͬ��������
	1.��������ʱ,���Ժ����յ�����Ϣ
	2.��������ʱ,����һ�����ֽ�
**************************************************/
u8 SPI1_Write_Read(u8 data)
{
	//1.������Ϣǰ�ȿ���,������λ�Ĵ����Ƿ���� , �������  ��־λ 1       
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET)
	{
		;	//����,��λ�Ĵ��������ݷ������
	}
	
	//2.�����ݷ���
	SPI_I2S_SendData(SPI1,data);
	
	//3.����ǰ,�ж� SPI ������λ�Ĵ������������Ƿ�������
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET)
	{
		;	//����,��λ�Ĵ��������ݷ������
	}
	
	//4.�����ݶ�ȡ
	return SPI_I2S_ReceiveData(SPI1);
}



