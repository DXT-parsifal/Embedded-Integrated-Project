#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx.h"

int value_led3;//PWM LED3数值 
int value_fan;//PWM 风扇数值

void Mqtt_Control(char * message);//上位机下传操作指令

void MenuShow(void);            //菜单显示
void EnvShow(void);             //环境监测
void DeviceControl(void);       //设备控制
void ad_show(void);             //广告显示

void show_gear(int value,u8 position);      //OLED显示档位
u8 gear_judgment(int value);                //数据上传档位判断

#endif  

