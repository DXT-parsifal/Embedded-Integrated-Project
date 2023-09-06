#ifndef FUNC_H
#define FUNC_H

#include <QWidget>
/*---------- TCP相关 -----------*/
#include <QTcpSocket>
/*---------- JSON相关 ----------*/
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
/*---------- MQTT相关 ----------*/
#include <QtMqtt/qmqttclient.h>
/*-----------http相关-----------*/
#include <QFile>
#include <QAudioInput>
#include <QNetworkAccessManager>
#include <QNetworkReply>
/*-----------Chart-------------*/
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QSplineSeries>

QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;

namespace Ui {
class Func;
}
using namespace QtCharts;

class Func : public QWidget
{
    Q_OBJECT

public:
    explicit Func(QString ID,QWidget *parent = nullptr);
    ~Func();

public:
    QPixmap PixmapToRound(const QPixmap &src, int radius);//QLabel圆形图片，动态边框
public slots:
    void slot_TcpSocket_readyRead();
    void getDevice();
    void Mqtt_put(QByteArray data);

    void mqtt_readyread(const QByteArray &message);

private slots:
    void on_pushButton_bind_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_ON_clicked();

    void on_pushButton_OFF_clicked();

    void on_pushButton_LED_ON_clicked();

    void on_pushButton_LED_OFF_clicked();

    void on_pushButton_clicked();

    void on_pushButton_FAN1_clicked();

    void on_pushButton_FAN2_clicked();

    void on_pushButton_FAN3_clicked();

    void on_pushButton_FAN_Close_clicked();

    void on_pushButton_LED2_close_clicked();

    void on_pushButton_LED2_1_clicked();

    void on_pushButton_LED2_2_clicked();

    void on_pushButton_LDE2_3_clicked();

    void on_horizontalSlider_LED3_PWM_sliderMoved(int position);

    /******************Robot*******************/
    void on_pushButton_robot_pressed();

    void on_pushButton_robot_released();

public:
    //网络管理对象
    QNetworkAccessManager *http_online;
    //语音识别
    void RecorderStart(QString fileName);//开始录音
    void RecorderEnd();//结束录音并转换格式
    QFile *outFile;//录音时的变量
    QAudioInput *my_audio;//录音时的变量
    QAudioFormat audioFormat;//录音时的变量

    //语音识别API的url组装
    bool post_sync(QString url,QMap<QString,QString>header,QByteArray requestData,QByteArray &replyData);
    //发送请求，识别结果返回
    QString speechIdentify(QString fileName);
    //解析JSON
    QString getJsonValue(QByteArray ba,QString key);

    void audioCtrl(QString);//语音识别转文字处理
    /*****************天气****************************/
    //网络管理对象
    QNetworkAccessManager *http;
    //服务响应
    QNetworkReply *replay;//一个抽象类
    //城市id map
    QMap<QString,QString> m_city;
public slots:
    void slot_btn_request();
    void slots_http_finshed(QNetworkReply *reply);
public:
    /****************光照折线图***********************************/
    /******************QChart*******************/
    /**
     * 接收到数据源发送来的数据，数据源可以下位机，采集卡，传感器等。
     */
    int timerId;
    int maxSize;  // data 最多存储 maxSize 个元素
    int maxX;
    int maxY;


    QChart *chart;
    QChartView *chartView;
    //湿度
    QSplineSeries *splineSeries1;
    QScatterSeries *scatterSeries1;
    QList<double> data1; // 存储业务数据的 list
    //温度
    QSplineSeries *splineSeries2;
    QScatterSeries *scatterSeries2;
    QList<double> data2; // 存储业务数据的 list
    //光照
    QSplineSeries *splineSeries3;
    QScatterSeries *scatterSeries3;
    QList<double> data3; // 存储业务数据的 list

    void dataReceived1(int value);
    void dataReceived2(int value);
    void dataReceived3(int value);


private:
    Ui::Func *ui;
    QTcpSocket *TcpSocket;//TCP通信对象

    QList<QString> m_ChipID;//用户绑定的芯片ID的列表
    bool flag;//设备列表更新标志，防止操作时更新冲突

    QMqttClient *Mqtt;//MQTT通信对象
};

//    获取Access Token
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "X0m0YWonD0KX8CIpuHKX14Fv";
const QString client_secret = "gFQP3f8SGKbEdxt38cbKmtp7AIGxx9hS";
//    语音识别url
const QString baiduSpeechUrl = "https://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";

#endif // FUNC_H
