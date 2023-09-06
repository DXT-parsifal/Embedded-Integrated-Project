
#include "at24c02.h"
#include "iic.h"
/******************************
����:IICд��
	@wr_addr:�豸���׵�ַ
	@data:�����׵�ַ
	@len:���ݳ���
*******************************/
void AT24C02_Write(u8 wr_addr,u8 *data,u8 len)
{
	//1.������ʼ�ź�
	IIC_Start();
	
	//2.���ʹӻ�������ַ 0 д��
	IIC_Send_Byte(0xA0);
	IIC_Wait_Ack();		//�ȴ�Ӧ��
	
	//3.����Ҫ�����ĵ�ַ
	IIC_Send_Byte(wr_addr);
	IIC_Wait_Ack();		//�ȴ�Ӧ��
	
	//4.ѭ��д������
	for(int i = 0; i < len;i++)
	{
		IIC_Send_Byte(data[i]);
		IIC_Wait_Ack();		//�ȴ�Ӧ��
	}
	//5.д����,����ֹͣ�ź�
	IIC_Stop();
}
/******************************
����:IIC��ȡ
	@wr_addr:�豸���׵�ַ
	@data:�����׵�ַ
	@len:���ݳ���
*******************************/
void AT24C02_Read(u8 wr_addr,u8 *data,u8 len)
{
	//1.������ʼ�ź�
	IIC_Start();
	
	//2.���ʹӻ�������ַ 0 д��
	IIC_Send_Byte(0xA0);
	IIC_Wait_Ack();		//�ȴ�Ӧ��
	
	//3.����Ҫ�����ĵ�ַ,������ת���ƶ���ַ
	IIC_Send_Byte(wr_addr);
	IIC_Wait_Ack();		//�ȴ�Ӧ��
		
	//4.���·�����ʼ�ź�
	IIC_Start();
	
	//5.����Ҫ�����Ĵӻ��豸 1 ��ȡ
	IIC_Send_Byte(0xA0+0x1);
	IIC_Wait_Ack();		//�ȴ�Ӧ��
	
	//6.ѭ����ȡ����
	for(int i = 0; i < len;i++)
	{
		data[i] = IIC_Read_Byte();
		if(i != len-1)IIC_Ack();	//Ӧ��
	}
	
	//7.������,������Ӧ���ֹͣ�ź�
	IIC_NAck();
	IIC_Stop();
}



