#ifndef REGIST_H
#define REGIST_H

#include <QWidget>
/*---------- TCP相关 -----------*/
#include <QTcpSocket>
/*---------- JSON相关 ----------*/
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace Ui {
class regist;
}

class regist : public QWidget
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();

private slots:
    void slot_TcpSocket_readyRead();

    void on_pushButton_registe_clicked();

private:
    Ui::regist *ui;
    QTcpSocket *TcpSocket;
};

#endif // REGIST_H
