#include <string.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
using namespace std;
/*-------- MQTT ------------*/
#include "MQTTClient.h"
/*-------- JSON -------------*/
#include <jsoncpp/json/json.h>
using namespace Json;
/*-------- Mysql ------------*/
#include <mysql/mysql.h>
/**--------- 1.创建mqtt句柄 -----------**/
MQTTClient clinet;
bool connectDB(MYSQL &mysql)
{
    // 初始化文件句柄
    mysql_init(&mysql);
    // 设置字符编码
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
    // 连接数据库
    MYSQL *ret = mysql_real_connect(&mysql, "139.199.212.89", "admin", "admin123", NULL, 3306, NULL, 0);
    if (ret == NULL){
        cout << "数据库连接失败！原因：" << mysql_error(&mysql) << endl;
        return false;
    }
    else
        cout << "数据库连接成功！" << endl;
    return true;
}


int main()
{
    /*----------- 连接数据库 ---------------------------------------------------------*/
    MYSQL mysql;
    if (connectDB(mysql) == true){
        cout << "连接mysql数据库成功" << endl;
    }
    else{
        cout << "连接mysql数据库失败" << endl;
    }
    mysql_select_db(&mysql,"myproject");//切换数据库

    /**---------- 2.创建MQTT客户端对象 ------------------------------------------------**/
    MQTTClient_create(&clinet,"mqtt.yyzlab.com.cn","1299030893",1,NULL);

    /**---------- 3.创建JSON连接结构体对象 --------------------------------------------**/
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;    //默认  

    /**---------- 4.连接MQTT服务器 ---------------------------------------------------**/
    if(MQTTClient_connect(clinet,&conn_opts) != 0)
    {
        cout << "连接MQTT失败" << endl;
        return -1;
    }
    cout << "连接MQTT成功" << endl;
    /**---------- 5.订阅主题 ---------------------------------------------------------**/
    MQTTClient_subscribe(clinet,"Deng_511757085",1);

    /**---------- 6.循环接收并处理消息 ------------------------------------------------**/
    int ret = -1;
    char *topicName;
    int topicLen;
    MQTTClient_message *message;
    char device_name[][20] = {"tem","hum","light","beep","fan","led3"};

    /**----------- MQTT需要发送心跳包 -------------------------------------------------*/
    if(fork() == 0)//子进程发送心跳
    {
        MQTTClient_message msg = MQTTClient_message_initializer;    //默认值
        msg.payload = NULL; //内容
        msg.payloadlen = 0; //内容长度
        msg.qos = 0;        //QOS 次数:一次发送即可
        msg.retained = 0;   //超时时间
        while(1)
        {
            MQTTClient_publishMessage(clinet,"x",&msg,NULL);
            cout << "10秒发送一次心跳包" << endl;
            sleep(10);  //10秒发送一次心跳包
        }
    }

    while(1)
    {
        ret = MQTTClient_receive(clinet,&topicName,&topicLen,&message,-1);
        if(ret != 0)
        {
            continue;
        }
        cout << "收到消息:" << (char*)message->payload << endl;
        char *str = (char*)message->payload;
        /*--------------- MQTT数据处理:JSON ------------------*/
        Reader json_reader;
        Value json_object;  //JSON对象
        char sql[200];

        json_reader.parse(str,json_object);    //解析
        /*--------------- 打印以下JSON -----------------------*/
        if(json_object.isObject() == false) continue;

        /*--------------- 解析JSON --------------------------*/
        if(json_object.isMember("ChipID") == false) continue; 
        const char *ChipID = json_object["ChipID"].asCString();
        /*--------------- 将芯片ID插入到数据库 ----------------*/
        sprintf(sql,"INSERT INTO chip VALUES('%s');",ChipID);
        mysql_real_query(&mysql,sql,strlen(sql));                   //执行sql命令
        cout << "sql:" << sql << endl;
        /*--------------- 解析 ------------------------------*/
        for(int i = 0; i < sizeof(device_name)/sizeof(device_name[0]);i++)
        {
            if(json_object.isMember(device_name[i]) == true)//温度
            {
                double value = json_object[device_name[i]].asDouble();
                sprintf(sql,"INSERT INTO device_info VALUES('%s','%s');",ChipID,device_name[i]);
                mysql_real_query(&mysql,sql,strlen(sql));                   //执行sql命令

                sprintf(sql,"INSERT INTO device_%s VALUES('%s',%.2f,%ld);",device_name[i],ChipID,value,time(NULL));
                mysql_real_query(&mysql,sql,strlen(sql));                   //执行sql命令
            }
        }
    }
    return 0;
}
