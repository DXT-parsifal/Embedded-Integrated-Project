#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"

int value_led3;//PWM LED3��ֵ 
int value_fan;//PWM ������ֵ

void Mqtt_Control(char * message);//��λ���´�����ָ��

void MenuShow(void);            //�˵���ʾ
void EnvShow(void);             //�������
void DeviceControl(void);       //�豸����
void ad_show(void);             //�����ʾ

void show_gear(int value,u8 position);      //OLED��ʾ��λ
u8 gear_judgment(int value);                //�����ϴ���λ�ж�

#endif  

