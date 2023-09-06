#ifndef __OLED_H
#define __OLED_H

#include "sys.h"
#include "stdlib.h"
#include "iic.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define I2C_Start 		IIC_Start
#define I2C_Stop		IIC_Stop
#define I2C_WaitAck		IIC_Ack
#define Send_Byte		IIC_Send_Byte
/*--------------- 主要功能包括: ---------------------------------------------------------------------------------
1.像素点操作
2.各种图形绘制(线条、圆形)
3.字符(数字、字符串、汉字)显示
4.图片显示
5.画面滚动
6.屏幕刷新与关闭
说明:你可以根据自己的需求选择使用其中部分或所有函数,并结合OLED屏幕的物理连接与初始化使用。
----------------------------------------------------------------------------------------------------------------*/
void OLED_ColorTurn(u8 i);								//反显函数   ----------   调整整个屏幕的颜色层次 
void OLED_DisplayTurn(u8 i);							//屏幕旋转180度 -------   旋转整个屏幕的显示方向
void OLED_WR_Byte(u8 dat,u8 mode);						//写入一个字节到OLED
void OLED_DisPlay_On(void);								//开屏显示
void OLED_DisPlay_Off(void);							//关闭屏幕显示
void OLED_Refresh(void);								//刷新整个屏幕
void OLED_Clear(void);									//清除整个屏幕
void OLED_DrawPoint(u8 x,u8 y,u8 t);					//绘制一个像素点
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);	//绘制一条线
void OLED_DrawCircle(u8 x,u8 y,u8 r);					//绘制一个圆
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);	//显示一个字符
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);		//显示一个6x8字符
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);				//显示一个字符串
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);			//显示一个数字
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);				//显示一个汉字
void OLED_ShowChineseString(u8 x,u8 y,u8 *data,u8 size1,u8 mode);		//显示汉字字符串	    ------- 王老师增加的显示中文算法,依旧需要添加字模
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);						//左右滚动屏幕显示	------- 按指定参数滚动显示字符串、汉字等内容，实现简单的屏幕动画效果
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);	//显示一副画面	    ------- 在OLED屏幕上显示指定的BMP位图数据
void OLED_Init(void);													//初始化OLED屏幕

#endif

