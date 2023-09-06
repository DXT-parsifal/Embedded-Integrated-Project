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

char ChipID[50];	//оƬID
int flag_put = 1;	//�ϴ���־λ
int RetFlag=1;      //����˵������������־
int main()
{
	/*------ ��ȡоƬID ----------*/
	uint32_t id1, id2, id3;	//��ȡоƬID
	
	id1 = *(uint32_t*)(0x1FFF7A10);
    id2 = *(uint32_t*)(0x1FFF7A14);
    id3 = *(uint32_t*)(0x1FFF7A18);
	sprintf(ChipID,"%08X%08X%08X",id1,id2,id3);
	/*------ оƬID��ȡ���� ------*/
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//���ж����ȼ����飺2����
    delay_Init(168);								//�δ�ʱ����ʼ����168Mhz
    UART1_Init(115200);								//����1��ʼ��,������Ϊ115200
	UART2_Init(115200);								//����2��ʼ��,������Ϊ115200
    KEY_Init();										//KEY������ʼ��
	
	LED_Init();			//LED��ʼ��
	BEEP_Init();		//BEEP��������ʼ��
	ADC1_Init();		//��ʼ��ADC1
	Light_Init();		//���������ʼ��
	Voltage_Init();		//�ɱ��ѹ��ʼ�� 
    IIC_Init();         //IIC��ʼ��
    OLED_Init();        //OLED��ʾ����ʼ��
	MenuShow();         //���˵���ʾ
    
    printf("�����豸\r\n");
	
    WIFI_Connect("LAPTOP-FQASV313","12345678");		//����WIFI·����
	MQTT_Connect("mqtt.yyzlab.com.cn","1883");	//����MQTT������
	delay_ms(1000);
	MQTT_Subscribe(ChipID);						//�����Լ�Ϊ����
    
    TIM1_Init(90-1,16800-1);//���ȣ�LED1��LED3
    TIM_SetCompare3(TIM1,0);//����,��ʼֵ���ȹ�
    TIM_SetCompare1(TIM1,90);//LED2,��ʼֵLED2��
    value_led3=0;
    TIM_SetCompare2(TIM1,0);//LED3
    //�������õ��籣��
    int value_r;
    AT24C02_Read(0x00,(u8*)&value_r,sizeof(value_r));//��ȡEEPRAM����
	printf("EEPRAM��ȡ���� = %d\r\n",value_r);
    
    value_fan=value_r;
    TIM_SetCompare3(TIM1,value_r);//����
	
    TIM7_Init(10000-1,8400-1);//��ʱ�ϴ����ݣ�1�����һ�Σ�30������״̬��־λ
    
    char message[200];
	int key;
	u8 HumiH,HumiL,TempH,TempL;
    while(1)	//��ֹ�����ܷ�
    {        
		/****** ��ʱ������Ϣ ********/
		if(flag_put == 1)
		{
			MQTT_Subscribe(ChipID);						//�����Լ�Ϊ����
            flag_put = 0;
			DHT11_Read_Data(&HumiH,&HumiL,&TempH,&TempL);
			/**---- �ϴ��¶�״̬ ----**/
			//1.JSON��װ
			cJSON *json = cJSON_CreateObject();		//����JSON����
			
			cJSON_AddStringToObject(json,"ChipID",ChipID);			//оƬID
			cJSON_AddNumberToObject(json,"tem",TempH);				//�¶�
			cJSON_AddNumberToObject(json,"hum",HumiH);				//ʪ��
			cJSON_AddNumberToObject(json,"light",Light_Get());		//����
			cJSON_AddNumberToObject(json,"beep",BEEP);              //������
            cJSON_AddNumberToObject(json,"fan",gear_judgment(value_fan));      //����
            cJSON_AddNumberToObject(json,"led3",gear_judgment(value_led3));     //LED3
            
			//2.תΪJSON�ַ���
			char *json_str = cJSON_Print(json);
			
			//3.�������ݵ�MQTT
			MQTT_Put_Message("Deng_511757085",json_str);
			
			//4.�ͷ�JSON�����JSON�ַ���
			cJSON_Delete(json);		//�ͷ�JSON����
			cJSON_free(json_str);	//�ͷ�JSON�ַ���
		}

		/******** ���մ�����Ϣ *********/
		if(MQTT_Get_Message(message) == 0)
		{
			Mqtt_Control(message);
		}
        
        if(RetFlag==0){
            MenuShow();
            RetFlag=1;
        }
        
        /*******************�����水ť����******************/
        key = KEY_Scan();
        switch(key)
        {
            case 1:
                RetFlag=1;//��ֹ������ˢ��
                EnvShow();//������ʾ
                break;
            case 2:
                RetFlag=1;
                DeviceControl();//���ƽ���
                break;
            case 3:
                RetFlag=1;
                ad_show();      //�����ʾ
                break;
            case 4:
                LED1 = !LED1;//LED1���״̬
                flag_put = 1;//�ϴ���־
                RetFlag=0;
                break;
        }
    }
}

//��ʪ�ȷ��ȵ�λ��ʾ
void EnvShow(void){
    u8 HumiH,HumiL,TempH,TempL;
    char BuffHumi[20]={0};
    char BuffTemp[20]={0};
    char BuffLight[20]={0};
    if(DHT11_Read_Data(&HumiH,&HumiL,&TempH,&TempL)==0) {
        OLED_Clear();
        OLED_ShowChineseString(0,0,"ʪ��",16,1);
        sprintf(BuffHumi,": %d.%d %%",HumiH,HumiL);      
        OLED_ShowString(32,0,(u8 *)BuffHumi,16,1);
        
        OLED_ShowChineseString(0,16,"�¶�",16,1);
        sprintf(BuffTemp,": %d.%d C",TempH,TempL);    
        OLED_ShowString(32,16,(u8 *)BuffTemp,16,1);
        
        OLED_ShowChineseString(0,32,"����",16,1);
        sprintf(BuffLight,": %d   Lux",Light_Get());
        OLED_ShowString(32,32,(u8 *)BuffLight,16,1);
    }
    OLED_ShowString(0,48,"key1:Reflash",8,1);   
    OLED_ShowString(72,48,"key4:Back",8,1);
    
    OLED_Refresh();  
    int key=0;
    //�ȴ�����
    while(key!=4)	//��ֹ�����ܷ�
    {
        switch(key=KEY_Scan())
        {
            case 1:
                if(DHT11_Read_Data(&HumiH,&HumiL,&TempH,&TempL)==0) {
                    OLED_Clear();
                    OLED_ShowChineseString(0,0,"ʪ��",16,1);
                    sprintf(BuffHumi,": %d.%d %%",HumiH,HumiL);      
                    OLED_ShowString(32,0,(u8 *)BuffHumi,16,1);
                    
                    OLED_ShowChineseString(0,16,"�¶�",16,1);
                    sprintf(BuffTemp,": %d.%d C",TempH,TempL);    
                    OLED_ShowString(32,16,(u8 *)BuffTemp,16,1);
                    
                    OLED_ShowChineseString(0,32,"����",16,1);
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

//LED�Ƶ�λ���ƣ����ȿ��ƣ�����������
void DeviceControl(void){
    OLED_Clear();
    OLED_ShowString(0,0,"key1:LED3",16,1);
    OLED_ShowString(0,16,"key2:",16,1);
    OLED_ShowChineseString(40,16,"����",16,1);
    OLED_ShowString(0,32,"key3:",16,1);
    OLED_ShowChineseString(40,32,"������",16,1);
    OLED_ShowString(56,48,"key4:Back",16,1);
    OLED_Refresh();    
    int key=0;
    //*****���ƽ���*******ѡ����Ƶ��豸
    while(key!=4)	//��ֹ�����ܷ�
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
            case 2://����
                RetFlag=1;
                value_fan+=30;
                if(value_fan>90) value_fan=0;
                
                AT24C02_Write(0x00,(u8*)&value_fan,sizeof(value_fan));//д��EEPRAM����
                printf("EEPRAMд������:%d\r\n",value_fan);
                
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
//OLED��ʾ��λ
void show_gear(int value,u8 position){
    switch(value){
    case 0:
        OLED_ShowChineseString(96,position,"�� ",16,1);
        OLED_Refresh(); 
        break;
    case 30:
        OLED_ShowString(96,position,"1",16,1);
        OLED_ShowChineseString(108,position,"��",16,1);
        OLED_Refresh(); 
        break;
    case 60:
        OLED_ShowString(96,position,"2",16,1);
        OLED_ShowChineseString(108,position,"��",16,1);
        OLED_Refresh(); 
        break;
    case 90:
        OLED_ShowString(96,position,"3",16,1);
        OLED_ShowChineseString(108,position,"��",16,1);
        OLED_Refresh(); 
        break;
    }
}
//�����ϴ���λ�ж�
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

void ad_show(void){//�����ʾ
    OLED_Clear();
    OLED_ShowChineseString(0,0,"�����԰��ɫ����",16,1);
    OLED_ShowChineseString(32,16,"�������",16,1);
    OLED_ShowString(10,32,"500",24,1);
    OLED_ShowChinese(46,32,1,24,1);
    OLED_ShowChinese(70,32,2,24,1);
    OLED_ShowChinese(94,32,3,24,1);
    OLED_Refresh();
    delay_ms(5000);
    RetFlag=0;
}      

//���˵���ʾ
void MenuShow(void){
    OLED_Clear();
    OLED_ShowString(0,0,"key1:",16,1);
    OLED_ShowChineseString(40,0,"�������",16,1);
    OLED_ShowString(0,16,"key2:",16,1);
    OLED_ShowChineseString(40,16,"�豸����",16,1);
    OLED_ShowString(0,32,"key3:",16,1);
    OLED_ShowChineseString(40,32,"�����ʾ",16,1);
    OLED_ShowString(0,48,"key4:",16,1);
    OLED_ShowChineseString(40,48,"����",16,1);
    OLED_Refresh();
}


void Mqtt_Control(char * message){
    /*------ ����JSON�ַ��� --------*/
    cJSON *json = cJSON_Parse(message);//�����Ż�
    cJSON *device =  NULL;
    if(json != NULL)
    {
        //������
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
        //���ȵ�λ����
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
        //LED2��λ����
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
            //ȡ��cjson��LED3��ֵ
            cJSON *json_led3;
            json_led3 = cJSON_GetObjectItem(json, "LED3");
            TIM_SetCompare2(TIM1,json_led3->valueint);
            printf("LED3\r\n");
        }
        /*----- �ͷ�JSON���� -----*/
        cJSON_Delete(json);
    }
}

