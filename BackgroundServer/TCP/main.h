#ifndef __MAIN_H__
#define __MAIN_H__
bool connectDB(MYSQL &mysql);
void tcp_regist(int cid,Value &json,MYSQL &mysql);  //注册
void tcp_login(int cid,Value &json,MYSQL &mysql);   //登录
void tcp_bind(int cid,Value &json,MYSQL &mysql);    //绑定芯片
void tcp_get_bind(int cid,Value &json,MYSQL &mysql);    //获取绑定芯片
void tcp_ret_state(int cid,Value &json,MYSQL &mysql);  //更新状态
#endif 
