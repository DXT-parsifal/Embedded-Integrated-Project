#include "login.h"
#include "regist.h"
#include "ui_regist.h"

#include <QMessageBox>

regist::regist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);

    TcpSocket = new QTcpSocket(this);
    TcpSocket->connectToHost("139.199.212.89",10000);

    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(slot_TcpSocket_readyRead()));
}

regist::~regist()
{
    delete ui;
}

void regist::slot_TcpSocket_readyRead(){
    /**** 接收TCP服务器数据 ****/
    QByteArray data = TcpSocket->readAll();
    /**** 解析JSON格式 *********/
    QJsonDocument JsonDocument = QJsonDocument::fromJson(data);
    if(JsonDocument.isObject() != true) return;
    /**** 转为JSON对象 *********/
    QJsonObject json =JsonDocument.object();
    /**** 处理 *****************/
    if(json["CMD"].toString() == "注册结果")
    {
        if(json["State"].toBool() == true)
        {
            Login *log=new Login();

            this->close();//注册界面关闭
            log->show();//登录界面打开
            TcpSocket->close();
        }
        else
        {
            QMessageBox::warning(this,"注册提示","注册失败,账号密码重复");
        }
    }
}

void regist::on_pushButton_registe_clicked()
{
    QJsonObject json;
    json["CMD"] = "注册";
    json["ID"] = ui->lineEdit_ID->text();
    json["name"]=ui->lineEdit_name->text();
    json["pass"] = ui->lineEdit_pass->text();
    json["email"]=ui->lineEdit_email->text();

    if(json["ID"].isNull()||json["name"].isNull()||json["pass"].isNull()||json["email"].isNull()) return;

    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();

    TcpSocket->write(data);
}
