#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
/*---------- TCP相关 -----------*/
#include <QTcpSocket>
/*---------- JSON相关 ----------*/
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

public slots:
    void slot_TcpSocket_readyRead();
private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_regiset_clicked();

private:
    Ui::Login *ui;
    QTcpSocket *TcpSocket;
};
#endif // LOGIN_H
