/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/epoll.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
/* Network form */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
/* std */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
/*-------- Mysql ------------*/
#include <mysql/mysql.h>
/*-------- JSON -------------*/
#include <jsoncpp/json/json.h>
using namespace Json;
/************* 网络编程服务器作为案例 *********************************************************************
 * 发现网络编程服务器,处理客户端消息，检测客户端套接字是否有数据可读?
 * 1.监听 sid 服务器有用户连接
 * 2.监听 cid 客户端有数据可读
 * 
 * 创建epoll描述符 int epoll_create(int size);
 * 操作epoll描述符 int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
 * 监听epoll描述符 int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
 * ***************************************************************************************************/
#define MAXSIZE 1024
#include "main.h"
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
    //1.创建套接字
    int sid = socket(AF_INET, SOCK_STREAM, 0);

    //2.绑定
    struct sockaddr_in IPv4;
    IPv4.sin_family = AF_INET;
    IPv4.sin_port = htons(10000);        //端口号:10000
    IPv4.sin_addr.s_addr = 0;            //IP地址:双栈协议,任意网卡绑定

    /*--- 因为我要做测试,可能重复开启服务器,导致绑定失败,实现端口复用 ---*/
    int on = 1;
    setsockopt(sid, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

    if(bind(sid,(struct sockaddr *)&IPv4,sizeof(IPv4)) < 0)
    {
        perror("绑定失败:");
        return -1;
    }

    //3.监听
    listen(sid,10);

    //----------- 1.创建epoll描述符 --------------------
    int epfd = epoll_create(MAXSIZE);

    //----------  2.将文件描述符加入 --------------------
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = sid;

    epoll_ctl(epfd,EPOLL_CTL_ADD,sid,&event);
    //总结: 
    //     1.epoll 是select 和 epoll 的升级版
    //     2.epoll 没有数量限制,而且使用的是内核事件表(存在内存中)
    //     3.epoll 不需要清空后重复加载文件描述符
    //     4.epoll 不需要进行全部轮询
    //----------- 3.监听epoll 描述符 -------------------
    struct epoll_event events[MAXSIZE];
    while(1)
    {
        int count = epoll_wait(epfd,events,MAXSIZE,3000);
        for(int i = 0; i < count;i++)
        {
            if(events[i].data.fd == sid)    //服务器
            {
                int cid = accept(sid,NULL,NULL);
                printf("有cid = %d连接\n",cid);
                /*---- 将客户端套接字添加到epoll中 -----*/
                event.data.fd = cid;
                epoll_ctl(epfd,EPOLL_CTL_ADD,cid,&event);
            }
            else    //客户端套接字
            {
                int cid = events[i].data.fd;
                char buf[200] = "";
                int len = recv(cid,buf,sizeof(buf),0);
                if(len <= 0){
                    printf("有内鬼,终止交易\n");
                    /*---- 将监听的套接字从epoll中删除 -----*/
                    epoll_ctl(epfd,EPOLL_CTL_DEL,cid,NULL);

                    close(cid);
                    continue;
                }
                
                /*----------- 处理客户端cid的内容 ---------------*/
                /*--------------- MQTT数据处理:JSON ------------------*/
                Reader json_reader;
                Value json;  //JSON对象

                json_reader.parse(buf,json);    //解析
                if(json.isObject() == false) continue;
                /*--------------------- 客户端发送JSON格式:注册信息 -------------------------*/
                if(json.isMember("CMD") == true)
                {
                    if(json["CMD"].asString() == "注册")
                        tcp_regist(cid,json,mysql);
                    else if(json["CMD"].asString() == "登录")
                        tcp_login(cid,json,mysql);
                    else if(json["CMD"].asString() == "绑定")
                        tcp_bind(cid,json,mysql);
                    else if(json["CMD"].asString() == "获取绑定")
                        tcp_get_bind(cid,json,mysql);
                    else if(json["CMD"].asString() == "状态")
                        tcp_ret_state(cid,json,mysql);
                }
            }
        }
    }
}

void tcp_ret_state(int cid,Value &json,MYSQL &mysql){
    cout<<"更新状态"<<endl;
    char sql[200];
    int ret = -1;
    /*----- 根据sql执行结果返回JSON结果 --------*/
    Value json_ret;
    json_ret["CMD"] = "状态更新";
    MYSQL_ROW row;	// 记录数组
    float temp;
    /*----- 解析内容，并写入到数据库user中 -----*/
    const char *ChipID   = json["ChipID"].asCString();
    /*----- 查询数据库 -----------------------*/
    sprintf(sql,"select _value from device_hum where ChipID='%s' ORDER BY _time DESC LIMIT 2;",ChipID);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    MYSQL_RES *RES = mysql_store_result(&mysql); //获取结果集
    if(RES)
    {
        while((row = mysql_fetch_row(RES)) != NULL)
        {
            temp += stol(row[0]);
        }
        temp = temp/2;
        json_ret["hum"]=temp;   //加入到数组中
        /*---- 记得释放结果集 -----*/
        mysql_free_result(RES);
    }
    temp=0;
    sprintf(sql,"select _value from device_tem where ChipID='%s' ORDER BY _time DESC LIMIT 2;",ChipID);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    RES = mysql_store_result(&mysql); //获取结果集
    if(RES)
    {
        while((row = mysql_fetch_row(RES)) != NULL)
        {
            temp += stol(row[0]);
        }
        temp = temp/2;
        json_ret["tem"]=temp;   //加入到数组中
        /*---- 记得释放结果集 -----*/
        mysql_free_result(RES);
    }

    temp=0;
    sprintf(sql,"select _value from device_light where ChipID='%s' ORDER BY _time DESC LIMIT 2;",ChipID);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    RES = mysql_store_result(&mysql); //获取结果集
    if(RES)
    {
        while((row = mysql_fetch_row(RES)) != NULL)
        {
            temp += stol(row[0]);
        }
        temp = temp/2;
        json_ret["light"]=temp;   //加入到数组中
        /*---- 记得释放结果集 -----*/
        mysql_free_result(RES);
    }

    sprintf(sql,"select _value from device_led3 where ChipID='%s' ORDER BY _time DESC LIMIT 1;",ChipID);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    RES = mysql_store_result(&mysql); //获取结果集
    if(RES)
    {
        while((row = mysql_fetch_row(RES)) != NULL)
        {
            temp = stol(row[0]);
        }
        json_ret["led3"]=temp;   //加入到数组中
        /*---- 记得释放结果集 -----*/
        mysql_free_result(RES);
    }

    sprintf(sql,"select _value from device_beep where ChipID='%s' ORDER BY _time DESC LIMIT 1;",ChipID);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    RES = mysql_store_result(&mysql); //获取结果集
    if(RES)
    {
        while((row = mysql_fetch_row(RES)) != NULL)
        {
            temp = stol(row[0]);
        }
        json_ret["beep"]=temp;   //加入到数组中
        /*---- 记得释放结果集 -----*/
        mysql_free_result(RES);
    }

    sprintf(sql,"select _value from device_fan where ChipID='%s' ORDER BY _time DESC LIMIT 1;",ChipID);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    RES = mysql_store_result(&mysql); //获取结果集
    if(RES)
    {
        while((row = mysql_fetch_row(RES)) != NULL)
        {
            temp = stol(row[0]);
        }
        json_ret["fan"]=temp;   //加入到数组中
        /*---- 记得释放结果集 -----*/
        mysql_free_result(RES);
    }

    /*----- 将其发送 --------------------------*/
    string json_str = json_ret.toStyledString();
    cout<<"状态更新发送客户端数据:"<<json_str<<endl;
    send(cid,json_str.data(),strlen(json_str.data()),0);
}

// {
//     "CMD":"获取绑定",			   				 /*命令字*/
//     "ID":"10000",								/*账号*/
// }
// {
//     "CMD":"绑定列表",		 /*命令字*/
//     "list":[
//         {
//          "芯片ID":"1516DC4611515D6516"
//          "备注":"一号教室"
//         },
//         {
//          "芯片ID":"1516DC461111111111"
//          "备注":"二号教室"
//         },
//     ]
// }
void tcp_get_bind(int cid,Value &json,MYSQL &mysql)    //获取绑定芯片
{
    char sql[200];
    int ret = -1;
    /*----- 解析内容，并写入到数据库user中 -----*/
    const char *ID   = json["ID"].asCString();
    /*----- 查询数据库 -----------------------*/
    sprintf(sql,"select ChipID,name from user_chip where ID='%s';",ID);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    MYSQL_RES *RES = mysql_store_result(&mysql); //获取结果集

    /*----- 根据sql执行结果返回JSON结果 --------*/
    Value json_ret;
    json_ret["CMD"] = "绑定列表";
    MYSQL_ROW row;	// 记录数组
    if(RES)
    {
        Value json_device;
        while((row = mysql_fetch_row(RES)) != NULL)
        {
            json_device["芯片ID"] = row[0];
            json_device["备注"] = row[1];
            json_ret["list"].append(json_device);   //加入到数组中
        }
        /*---- 记得释放结果集 -----*/
        mysql_free_result(RES);
    }

    /*----- 将其发送 --------------------------*/
    string json_str = json_ret.toStyledString();
    send(cid,json_str.data(),strlen(json_str.data()),0);
}


// {
//     "CMD":"绑定",			   					   /*命令字*/
//     "ID":"10000",								/*账号*/
//     "ChipID":"1516DC4611515D6516",			    /*芯片ID*/
//     "name":"备注"								  /*备注*/
// }
void tcp_bind(int cid,Value &json,MYSQL &mysql)
{
    char sql[200];
    int ret = -1;
    /*----- 解析内容，并写入到数据库user中 -----*/
    const char *ID   = json["ID"].asCString();
    const char *ChipID = json["ChipID"].asCString();
    const char *name = json["name"].asCString();
    /*----- 插入数据库 -----------------------*/
    sprintf(sql,"insert into user_chip values('%s','%s','%s');",ID,ChipID,name);
    /*----- 执行sql语句 -----------------------*/
    cout << "执行SQL:" << sql << endl;
    ret = mysql_real_query(&mysql,sql,strlen(sql));
    if(ret != 0)
    {
        cout << "错误原因:" << mysql_error(&mysql) << endl;
        /*--- 出现两种原因: 1.芯片ID不存在   2.重复绑定 ----*/
    }
    /*----- 根据sql执行结果返回JSON结果 --------*/
    Value json_ret;
    json_ret["CMD"] = "绑定结果";
    json_ret["State"] = (ret == 0 ? true : false);
    /*----- 将其发送 --------------------------*/
    string json_str = json_ret.toStyledString();
    send(cid,json_str.data(),strlen(json_str.data()),0);
}


// {
//     "CMD":"登录",		/*命令字*/
//     "ID":"10000",		/*账号*/
//     "pass":"123456",		/*密码*/
// }
void tcp_login(int cid,Value &json,MYSQL &mysql)
{
    char sql[200];
    int ret = -1;
    /*----- 解析内容，并写入到数据库user中 -----*/
    const char *ID   = json["ID"].asCString();
    const char *pass = json["pass"].asCString();
    /*----- 查询数据库 -----------------------*/
    sprintf(sql,"select * from user where ID='%s' and pass='%s';",ID,pass);
    /*----- 执行sql -------------------------*/
    mysql_real_query(&mysql,sql,strlen(sql));   //执行
    MYSQL_RES *RES = mysql_store_result(&mysql); //获取结果集
    int row = mysql_num_rows(RES); //获取结果行数
    /*---- 记得释放结果集 -----*/
    mysql_free_result(RES);

    /*----- 根据sql执行结果返回JSON结果 --------*/
    Value json_ret;
    json_ret["CMD"] = "登录结果";
    json_ret["State"] = (row == 1 ? true : false);
    /*----- 将其发送 --------------------------*/
    string json_str = json_ret.toStyledString();
    send(cid,json_str.data(),strlen(json_str.data()),0);
}


void tcp_regist(int cid,Value &json,MYSQL &mysql)
{
    char sql[200];
    int ret = -1;
    /*----- 解析内容，并写入到数据库user中 -----*/
    const char *ID   = json["ID"].asCString();
    const char *pass = json["pass"].asCString();
    const char *name = json["name"].asCString();
    const char *email = json["email"].asCString();
    /*----- 写入数据库 ------------------------*/
    sprintf(sql,"insert into user values('%s','%s','%s','%s');",ID,pass,name,email);
    
    /*----- 执行sql语句 -----------------------*/
    cout << "执行SQL:" << sql << endl;

    ret = mysql_real_query(&mysql,sql,strlen(sql));
    if(ret != 0)
    {
        cout << "错误原因:" << mysql_error(&mysql) << endl;
        /*--- 出现两种原因: 1.账号重复   2.邮箱重复 ----*/
    }
    /*----- 根据sql执行结果返回JSON结果 --------*/
    Value json_ret;
    json_ret["CMD"] = "注册结果";
    json_ret["State"] = (ret == 0 ? true : false);
    /*----- 将其发送 --------------------------*/
    string json_str = json_ret.toStyledString();
    send(cid,json_str.data(),strlen(json_str.data()),0);
}



/*****************************************************
 * 1.开启tcp服务器,等待客户端连接
 * 2.JSON格式处理客户端消息
 * 3.与Mysql数据库操作
 * **************************************************/
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