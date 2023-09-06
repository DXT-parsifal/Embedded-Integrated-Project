#ifndef __OLED_H
#define __OLED_H

#include "sys.h"
#include "stdlib.h"
#include "iic.h"

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define I2C_Start 		IIC_Start
#define I2C_Stop		IIC_Stop
#define I2C_WaitAck		IIC_Ack
#define Send_Byte		IIC_Send_Byte
/*--------------- ��Ҫ���ܰ���: ---------------------------------------------------------------------------------
1.���ص����
2.����ͼ�λ���(������Բ��)
3.�ַ�(���֡��ַ���������)��ʾ
4.ͼƬ��ʾ
5.�������
6.��Ļˢ����ر�
˵��:����Ը����Լ�������ѡ��ʹ�����в��ֻ����к���,�����OLED��Ļ�������������ʼ��ʹ�á�
----------------------------------------------------------------------------------------------------------------*/
void OLED_ColorTurn(u8 i);								//���Ժ���   ----------   ����������Ļ����ɫ��� 
void OLED_DisplayTurn(u8 i);							//��Ļ��ת180�� -------   ��ת������Ļ����ʾ����
void OLED_WR_Byte(u8 dat,u8 mode);						//д��һ���ֽڵ�OLED
void OLED_DisPlay_On(void);								//������ʾ
void OLED_DisPlay_Off(void);							//�ر���Ļ��ʾ
void OLED_Refresh(void);								//ˢ��������Ļ
void OLED_Clear(void);									//���������Ļ
void OLED_DrawPoint(u8 x,u8 y,u8 t);					//����һ�����ص�
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);	//����һ����
void OLED_DrawCircle(u8 x,u8 y,u8 r);					//����һ��Բ
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);	//��ʾһ���ַ�
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);		//��ʾһ��6x8�ַ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);				//��ʾһ���ַ���
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);			//��ʾһ������
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);				//��ʾһ������
void OLED_ShowChineseString(u8 x,u8 y,u8 *data,u8 size1,u8 mode);		//��ʾ�����ַ���	    ------- ����ʦ���ӵ���ʾ�����㷨,������Ҫ�����ģ
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);						//���ҹ�����Ļ��ʾ	------- ��ָ������������ʾ�ַ��������ֵ����ݣ�ʵ�ּ򵥵���Ļ����Ч��
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);	//��ʾһ������	    ------- ��OLED��Ļ����ʾָ����BMPλͼ����
void OLED_Init(void);													//��ʼ��OLED��Ļ

#endif

