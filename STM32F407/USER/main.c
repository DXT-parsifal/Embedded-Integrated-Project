#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "exit.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"
#include "iwdog.h"
#include "timer.h"
#include "dht11.h"
#include "iic.h"
#include "oled.h"
#include "at24c02.h"
#include "adc.h"
#include "light.h"
#include "voltage.h"
#include "string.h"
#include "cJSON.h"

char ChipID[50];	//芯片ID
int flag_put = 1;	//上传标志位
int RetFlag=1;      //界面菜单返回主界面标志
int main()
{
	/*------ 读取芯片ID ----------*/
	uint32_t id1, id2, id3;	//获取芯片ID
	
	id1 = *(uint32_t*)(0x1FFF7A10);
    id2 = *(uint32_t*)(0x1FFF7A14);
    id3 = *(uint32_t*)(0x1FFF7A18);
	sprintf(ChipID,"%08X%08X%08X",id1,id2,id3);
	/*------ 芯片ID读取结束 ------*/
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//先中断优先级分组：2分组
    delay_Init(168);								//滴答定时器初始化：168Mhz
    UART1_Init(115200);								//串口1初始化,波特率为115200
	UART2_Init(115200);								//串口2初始化,波特率为115200
    KEY_Init();										//KEY按键初始化
	
	LED_Init();			//LED初始化
	BEEP_Init();		//BEEP蜂鸣器初始化
	ADC1_Init();		//初始化ADC1
	Light_Init();		//光敏电阻初始化
	Voltage_Init();		//可变电压初始化 
    IIC_Init();         //IIC初始化
    OLED_Init();        //OLED显示屏初始化
	MenuShow();         //主菜单显示
    
    printf("重启设备\r\n");
	
    WIFI_Connect("LAPTOP-FQASV313","12345678");		//连接WIFI路由器
	MQTT_Connect("mqtt.yyzlab.com.cn","1883");	//连接MQTT服务器
	delay_ms(1000);
	MQTT_Subscribe(ChipID);						//订阅自己为主题
    
    TIM1_Init(90-1,16800-1);//风扇，LED1和LED3
    TIM_SetCompare3(TIM1,0);//风扇,初始值风扇关
    TIM_SetCompare1(TIM1,90);//LED2,初始值LED2关
    value_led3=0;
    TIM_SetCompare2(TIM1,0);//LED3
    //风扇设置掉电保护
    int value_r;
    AT24C02_Read(0x00,(u8*)&value_r,sizeof(value_r));//读取EEPRAM数据
	printf("EEPRAM读取数据 = %d\r\n",value_r);
    
    value_fan=value_r;
    TIM_SetCompare3(TIM1,value_r);//风扇
	
    TIM7_Init(10000-1,8400-1);//定时上传数据，1秒更新一次，30秒设置状态标志位
    
    char message[200];
	int key;
	u8 HumiH,HumiL,TempH,TempL;
    while(1)	//防止程序跑飞
    {        
		/****** 定时发送消息 ********/
		if(flag_put == 1)
		{
			MQTT_Subscribe(ChipID);						//订阅自己为主题
            flag_put = 0;
			DHT11_Read_Data(&HumiH,&HumiL,&TempH,&TempL);
			/**---- 上传温度状态 ----**/
			//1.JSON封装
			cJSON *json = cJSON_CreateObject();		//创建JSON对象
			
			cJSON_AddStringToObject(json,"ChipID",ChipID);			//芯片ID
			cJSON_AddNumberToObject(json,"tem",TempH);				//温度
			cJSON_AddNumberToObject(json,"hum",HumiH);				//湿度
			cJSON_AddNumberToObject(json,"light",Light_Get());		//光照
			cJSON_AddNumberToObject(json,"beep",BEEP);              //报警器
            cJSON_AddNumberToObject(json,"fan",gear_judgment(value_fan));      //风扇
            cJSON_AddNumberToObject(json,"led3",gear_judgment(value_led3));     //LED3
            
			//2.转为JSON字符串
			char *json_str = cJSON_Print(json);
			
			//3.发送数据到MQTT
			MQTT_Put_Message("Deng_511757085",json_str);
			
			//4.释放JSON对象和JSON字符串
			cJSON_Delete(json);		//释放JSON对象
			cJSON_free(json_str);	//释放JSON字符串
		}

		/******** 接收处理消息 *********/
		if(MQTT_Get_Message(message) == 0)
		{
			Mqtt_Control(message);
		}
        
        if(RetFlag==0){
            MenuShow();
            RetFlag=1;
        }
        
        /*******************主界面按钮控制******************/
        key = KEY_Scan();
        switch(key)
        {
            case 1:
                RetFlag=1;//防止主界面刷屏
                EnvShow();//环境显示
                break;
            case 2:
                RetFlag=1;
                DeviceControl();//控制界面
                break;
            case 3:
                RetFlag=1;
                ad_show();      //广告显示
                break;
            case 4:
                LED1 = !LED1;//LED1变更状态
                flag_put = 1;//上传标志
                RetFlag=0;
                break;
        }
    }
}

//温湿度风扇档位显示
void EnvShow(void){
    u8 HumiH,HumiL,TempH,TempL;
    char BuffHumi[20]={0};
    char BuffTemp[20]={0};
    char BuffLight[20]={0};
    if(DHT11_Read_Data(&HumiH,&HumiL,&TempH,&TempL)==0) {
        OLED_Clear();
        OLED_ShowChineseString(0,0,"湿度",16,1);
        sprintf(BuffHumi,": %d.%d %%",HumiH,HumiL);      
        OLED_ShowString(32,0,(u8 *)BuffHumi,16,1);
        
        OLED_ShowChineseString(0,16,"温度",16,1);
        sprintf(BuffTemp,": %d.%d C",TempH,TempL);    
        OLED_ShowString(32,16,(u8 *)BuffTemp,16,1);
        
        OLED_ShowChineseString(0,32,"光照",16,1);
        sprintf(BuffLight,": %d   Lux",Light_Get());
        OLED_ShowString(32,32,(u8 *)BuffLight,16,1);
    }
    OLED_ShowString(0,48,"key1:Reflash",8,1);   
    OLED_ShowString(72,48,"key4:Back",8,1);
    
    OLED_Refresh();  
    int key=0;
    //等待返回
    while(key!=4)	//防止程序跑飞
    {
        switch(key=KEY_Scan())
        {
            case 1:
                if(DHT11_Read_Data(&HumiH,&HumiL,&TempH,&TempL)==0) {
                    OLED_Clear();
                    OLED_ShowChineseString(0,0,"湿度",16,1);
                    sprintf(BuffHumi,": %d.%d %%",HumiH,HumiL);      
                    OLED_ShowString(32,0,(u8 *)BuffHumi,16,1);
                    
                    OLED_ShowChineseString(0,16,"温度",16,1);
                    sprintf(BuffTemp,": %d.%d C",TempH,TempL);    
                    OLED_ShowString(32,16,(u8 *)BuffTemp,16,1);
                    
                    OLED_ShowChineseString(0,32,"光照",16,1);
                    sprintf(BuffLight,": %d   Lux",Light_Get());
                    OLED_ShowString(32,32,(u8 *)BuffLight,16,1);
                    OLED_ShowString(0,48,"key1:Reflash",8,1);   
                    OLED_ShowString(72,48,"key4:Back",8,1);
                    OLED_Refresh(); 
                }
            case 4:
                RetFlag=0;
                break;
        }
    }    
}

//LED灯档位控制，风扇控制，蜂鸣器控制
void DeviceControl(void){
    OLED_Clear();
    OLED_ShowString(0,0,"key1:LED3",16,1);
    OLED_ShowString(0,16,"key2:",16,1);
    OLED_ShowChineseString(40,16,"风扇",16,1);
    OLED_ShowString(0,32,"key3:",16,1);
    OLED_ShowChineseString(40,32,"蜂鸣器",16,1);
    OLED_ShowString(56,48,"key4:Back",16,1);
    OLED_Refresh();    
    int key=0;
    //*****控制界面*******选择控制的设备
    while(key!=4)	//防止程序跑飞
    {
        switch(key=KEY_Scan())
        {
            case 1://LED3
                RetFlag=1;
                value_led3+=30;
                if(value_led3>90) value_led3=0;
                printf("value_led3=%d\r\n",value_led3);
                TIM_SetCompare2(TIM1,value_led3);
                show_gear(value_led3,0);
                flag_put=1;
                break;
            case 2://风扇
                RetFlag=1;
                value_fan+=30;
                if(value_fan>90) value_fan=0;
                
                AT24C02_Write(0x00,(u8*)&value_fan,sizeof(value_fan));//写入EEPRAM数据
                printf("EEPRAM写入数据:%d\r\n",value_fan);
                
                TIM_SetCompare3(TIM1,value_fan);
                show_gear(value_fan,16);
                flag_put=1;
                break;
            case 3:
                BEEP=!BEEP;
                flag_put=1;
                break;
            case 4:
                RetFlag=0;
                break;
        }
    }
}
//OLED显示档位
void show_gear(int value,u8 position){
    switch(value){
    case 0:
        OLED_ShowChineseString(96,position,"关 ",16,1);
        OLED_Refresh(); 
        break;
    case 30:
        OLED_ShowString(96,position,"1",16,1);
        OLED_ShowChineseString(108,position,"档",16,1);
        OLED_Refresh(); 
        break;
    case 60:
        OLED_ShowString(96,position,"2",16,1);
        OLED_ShowChineseString(108,position,"档",16,1);
        OLED_Refresh(); 
        break;
    case 90:
        OLED_ShowString(96,position,"3",16,1);
        OLED_ShowChineseString(108,position,"档",16,1);
        OLED_Refresh(); 
        break;
    }
}
//数据上传档位判断
u8 gear_judgment(int value){
    switch(value){
    case 0:
        return 0;
    case 30:
        return 1;
    case 60:
        return 2;
    case 90:
        return 3;
    }
    return 0;
}

void ad_show(void){//广告显示
    OLED_Clear();
    OLED_ShowChineseString(0,0,"理想家园绿色生活",16,1);
    OLED_ShowChineseString(32,16,"劲爆起价",16,1);
    OLED_ShowString(10,32,"500",24,1);
    OLED_ShowChinese(46,32,1,24,1);
    OLED_ShowChinese(70,32,2,24,1);
    OLED_ShowChinese(94,32,3,24,1);
    OLED_Refresh();
    delay_ms(5000);
    RetFlag=0;
}      

//主菜单显示
void MenuShow(void){
    OLED_Clear();
    OLED_ShowString(0,0,"key1:",16,1);
    OLED_ShowChineseString(40,0,"环境监测",16,1);
    OLED_ShowString(0,16,"key2:",16,1);
    OLED_ShowChineseString(40,16,"设备控制",16,1);
    OLED_ShowString(0,32,"key3:",16,1);
    OLED_ShowChineseString(40,32,"广告显示",16,1);
    OLED_ShowString(0,48,"key4:",16,1);
    OLED_ShowChineseString(40,48,"返回",16,1);
    OLED_Refresh();
}


void Mqtt_Control(char * message){
    /*------ 解析JSON字符串 --------*/
    cJSON *json = cJSON_Parse(message);//数组优化
    cJSON *device =  NULL;
    if(json != NULL)
    {
        //警报器
        device = cJSON_GetObjectItem(json,"alarm");
        if(device != NULL)
        {
            BEEP = device->valueint;
            printf("BEEP = %ld\r\n",BEEP);
        }
        //LED1
        device = cJSON_GetObjectItem(json,"LED1");
        if(device != NULL)
        {
            LED1 = device->valueint;
            printf("LED1 = %ld\r\n",LED1);
        }
        //风扇档位控制
        device = cJSON_GetObjectItem(json,"FAN0");
        if(device != NULL)
        {
            TIM_SetCompare3(TIM1,0);
            printf("FAN0\r\n");
        }
        device = cJSON_GetObjectItem(json,"FAN1");
        if(device != NULL)
        {
            TIM_SetCompare3(TIM1,30);
            printf("FAN1\r\n");
        }    
        device = cJSON_GetObjectItem(json,"FAN2");
        if(device != NULL)
        {
            TIM_SetCompare3(TIM1,60);
            printf("FAN2\r\n");
        }
        device = cJSON_GetObjectItem(json,"FAN3");
        if(device != NULL)
        {
            TIM_SetCompare3(TIM1,90);
            printf("FAN3\r\n");
        }
        //LED2档位控制
        device = cJSON_GetObjectItem(json,"LED2_0");
        if(device != NULL)
        {
            TIM_SetCompare1(TIM1,90);
            printf("LED2_0\r\n");
        }
        device = cJSON_GetObjectItem(json,"LED2_1");
        if(device != NULL)
        {
            TIM_SetCompare1(TIM1,60);
            printf("LED2_1\r\n");
        }
        device = cJSON_GetObjectItem(json,"LED2_2");
        if(device != NULL)
        {
            TIM_SetCompare1(TIM1,30);
            printf("LED2_2\r\n");
        }
        device = cJSON_GetObjectItem(json,"LED2_3");
        if(device != NULL)
        {
            TIM_SetCompare1(TIM1,0);
            printf("LED2_3\r\n");
        }
        //LED3 PWM
        device = cJSON_GetObjectItem(json,"LED3");
        if(device != NULL)
        {
            //取出cjson中LED3的值
            cJSON *json_led3;
            json_led3 = cJSON_GetObjectItem(json, "LED3");
            TIM_SetCompare2(TIM1,json_led3->valueint);
            printf("LED3\r\n");
        }
        /*----- 释放JSON对象 -----*/
        cJSON_Delete(json);
    }
}

