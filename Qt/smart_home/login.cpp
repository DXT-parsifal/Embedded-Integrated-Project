#include "login.h"
#include "ui_login.h"
#include "regist.h"
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/res/智能家居3.png"));
    this->setWindowTitle("Smart Campus");
    TcpSocket = new QTcpSocket(this);
    TcpSocket->connectToHost("139.199.212.89",10000);

    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(slot_TcpSocket_readyRead()));
}

#include <QMessageBox>
#include "func.h"
void Login::slot_TcpSocket_readyRead()
{
    /**** 接收TCP服务器数据 ****/
    QByteArray data = TcpSocket->readAll();
    /**** 解析JSON格式 *********/
    QJsonDocument JsonDocument = QJsonDocument::fromJson(data);
    if(JsonDocument.isObject() != true) return;
    /**** 转为JSON对象 *********/
    QJsonObject json =JsonDocument.object();
    /**** 处理 *****************/
    if(json["CMD"].toString() == "登录结果")
    {
        if(json["State"].toBool() == true)
        {
            QString ID = ui->lineEdit_ID->text();
            Func *func = new Func(ID);

            func->show();   //显示功能界面
            this->close();  //关闭登录界面
            TcpSocket->close();
        }
        else
        {
            QMessageBox::warning(this,"登录提示","登录失败,账号密码错误");
        }
    }
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_login_clicked()
{
    QString ID = ui->lineEdit_ID->text();
    QString pass = ui->lineEdit_Pass->text();
    if(ID.isEmpty() || pass.isEmpty() ) return ;    //不能让其为空

    QJsonObject json;
    json["CMD"] = "登录";
    json["ID"] = ID;
    json["pass"] = pass;

    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();

    TcpSocket->write(data);
}

void Login::on_pushButton_regiset_clicked()
{
    regist *reg=new regist;
    this->close();//登录界面关闭
    reg->show();//打开注册界面
    TcpSocket->close();//关闭TCP通信
}
