#include "func.h"
#include "ui_func.h"
#include <QTimer>
#include <QMessageBox>
#include "func.h"

Func::Func(QString ID,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Func)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/res/智能家居3.png"));
    this->setWindowTitle("Smart Campus");
    //动态曲线图
//    ui->widget_chart->resize(400,400);
    ui->comboBox->setCurrentIndex(2);
    QPixmap img1;
    img1.load(":/new/prefix1/res/头像.jpg");
    //100,100为QLabel的宽高
    QPixmap pixMap= img1.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //50为圆形的半径
    pixMap =  PixmapToRound(pixMap, 50);
    ui->label_image->setPixmap(pixMap);

    ui->label_ID->setText(ID);//登录界面回去用户ID
    ui->widget_hum->setTitle("湿度%");
    ui->widget_hum->setRange(0,100);
    ui->widget_hum->setValue(30);
    ui->widget_temp->setTitle("温度℃");
    ui->widget_temp->setRange(0,100);
    ui->widget_temp->setValue(20);
    ui->label_fan->setText("关");
    ui->label_light->setText("70Lux");
    ui->label_led3->setText("关");
    ui->label_beep->setText("关");
    ui->label_tem->setText("20℃");
    ui->label_hum->setText("30%");
    ui->label_robot->setPixmap(QPixmap(":/new/prefix1/res/机器人.png"));
    TcpSocket = new QTcpSocket(this);
    TcpSocket->connectToHost("139.199.212.89",10000);//连接服务器访问数据库
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(slot_TcpSocket_readyRead()));//有服务器返回数据读取

    connect(TcpSocket,&QTcpSocket::connected,[=](){
        getDevice();    //获取绑定
    });

    /*----- Mqtt -----*/
    Mqtt = new QMqttClient(this);

    Mqtt->setHostname("mqtt.yyzlab.com.cn");        //网址
    Mqtt->setClientId(QString("Deng_")+ID);         //ID
    Mqtt->setPort(1883);                            //端口号
    Mqtt->connectToHost();//配置完MQTT后连接服务器MQTT
    /*---- 心跳包 -----*/
    QTimer *timer= new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        Mqtt->publish(QMqttTopicName("x"),"x"); //发布消息 心跳
        on_pushButton_clicked();
//        qDebug() << "心跳包" << endl;
    });

    connect(Mqtt,&QMqttClient::connected,[=](){
        timer->start(10000);
        qDebug()<<"MQTT服务器连接成功"<<endl;
        //订阅下位机的状态信息
        Mqtt->subscribe(QMqttTopicFilter("Deng_511757085"));
    });

    //mqtt有数据可读信号
    connect(Mqtt,&QMqttClient::messageReceived,this,&Func::mqtt_readyread);

    //switchbutton信号改变
    connect(ui->widget_beep_switch,&SwitchButton::checkedChanged,ui->widget_beep_switch,[=](bool checked){
        if(checked==true){
            emit ui->pushButton_ON->clicked();
        }else if(checked==false){
            emit ui->pushButton_OFF->clicked();
        }
    });

    /******************Robot*******************/
    this->http_online=new QNetworkAccessManager(this);//网络管理对象

    /*****************天气*********************/
    //API天气JSON解析，
    //城市map
    m_city["长沙"]="101250101";
    m_city["北京"]="101010100";
    m_city["上海"]="101020100";
    m_city["深圳"]="101280601";
    m_city["广州"]="101280101";
    this->http=new QNetworkAccessManager(this);//网络管理对象
    //replay由get请求返回
    //初始请求、得到回应、主界面显示
    slot_btn_request();
    if(this->replay->isFinished()){
        slots_http_finshed(replay);
    }
    //发送请求
    connect(ui->pushButton_weather,&QPushButton::clicked,this,&Func::slot_btn_request);
    //收到回应后读取JSON数据
    connect(http,&QNetworkAccessManager::finished,this,&Func::slots_http_finshed);

    // *****************************折线图数据改变**********************
    maxSize = 31; // 只存储最新的 31 个数据
    maxX = 360;
    maxY = 100;

    splineSeries1 = new QSplineSeries();
    splineSeries1->setName("湿度");
    scatterSeries1 = new QScatterSeries();
    scatterSeries1->setMarkerSize(8);
//    splineSeries->setColor(QColor());

    splineSeries2 = new QSplineSeries();
    splineSeries2->setName("光照");
    scatterSeries2 = new QScatterSeries();
    scatterSeries2->setMarkerSize(8);

    splineSeries3 = new QSplineSeries();
    splineSeries3->setName("温度");
    scatterSeries3 = new QScatterSeries();
    scatterSeries3->setMarkerSize(8);

    chart = new QChart();
    chart->addSeries(splineSeries1);
    chart->addSeries(scatterSeries1);

    chart->addSeries(splineSeries2);
    chart->addSeries(scatterSeries2);

    chart->addSeries(splineSeries3);
    chart->addSeries(scatterSeries3);

    chart->setTitle("实时动态曲线");
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 360);
    chart->axisX()->setTitleText("时间/10s");
    chart->axisY()->setRange(0, maxY);
    chart->axisY()->setTitleText("数值%");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
    ui->widget_chart->setLayout(layout);//将QChart对象加入到widget_chart中

    timerId = startTimer(200);
//    qsrand(QDateTime::currentDateTime().toTime_t());

}




/***************************************代码TEST测试功能*******************************************************************/
void Func::mqtt_readyread(const QByteArray &message)
{
    // QByteArray转换成QJsonObject
    QJsonDocument document=QJsonDocument::fromJson(message);
    QJsonObject json = document.object();

    qDebug()<<"主题Deng_511757085:"<<json<<endl;
}

/***************************TCP接收服务器通信结果，***************************************************/
//根据用户ID通过TCP通信访问数据库该用户下的设备
void Func::getDevice()
{
    QString ID = ui->label_ID->text();//用户ID

    QJsonObject json;
    json["CMD"] = "获取绑定";
    json["ID"] = ID;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();

    TcpSocket->write(data);
}

//TCP访问数据库服务器返回结果
void Func::slot_TcpSocket_readyRead()
{
    /**** 接收TCP服务器数据 ****/
    QByteArray data = TcpSocket->readAll();
    /**** 解析JSON格式 *********/
    QJsonDocument JsonDocument = QJsonDocument::fromJson(data);
    if(JsonDocument.isObject() != true) return;
    /**** 转为JSON对象 *********/
    QJsonObject json =JsonDocument.object();
    /**** 处理 *****************/
    //接收到绑定结构进行后续处理
    if(json["CMD"].toString() == "绑定结果")
    {
        if(json["State"].toBool() == true)
        {
            QMessageBox::warning(this,"绑定提示","绑定成功");
            getDevice();    //获取设备绑定表
        }
        else
        {
            QMessageBox::warning(this,"绑定提示","绑定失败,重复绑定");
        }
    }
    //返回用户绑定设备列表
    if(json["CMD"].toString() == "绑定列表")
    {
        flag = false;
        ui->comboBox->clear();  //清空
        m_ChipID.clear();       //清空
        /*----- 解析 --------*/
        QJsonArray Array = json["list"].toArray();
        for(int i = 0; i < Array.size();i++)
        {
            QJsonObject object = Array[i].toObject();
            ui->comboBox->addItem(object["备注"].toString());
            //芯片ID
            m_ChipID.push_back(object["芯片ID"].toString());
        }
        flag = true;
    }
    //返回设备状态信息，具有按不同设备查询的状态信息
    if(json["CMD"].toString()=="状态更新"){
        QString hum;
        QString light;
        QString tem;
        QString beep;
        QString fan;
        QString led3;
        hum += QString::number(json.value("hum").toDouble());
        ui->widget_hum->setValue(hum.toDouble());
        hum += "%";
        light += QString::number(json.value("light").toDouble());
        light += "Lux";
        tem += QString::number(json.value("tem").toDouble());
        ui->widget_temp->setValue(tem.toDouble());
        tem +="℃";

        int newdata1=json.value("hum").toDouble();
        int newdata2=json.value("light").toDouble();
        int newdata3=json.value("tem").toDouble();
        qDebug()<<"newdata1"<<newdata1<<"newdata2"<<newdata2<<"newdata3"<<newdata3<<endl;
        dataReceived1(newdata1);
        dataReceived2(newdata2);
        dataReceived3(newdata3);

        beep += QString::number(json.value("beep").toDouble());
        fan += QString::number(json.value("fan").toDouble());
        led3 += QString::number(json.value("led3").toDouble());

        ui->label_hum->setText(hum);
        ui->label_tem->setText(tem);
        ui->label_light->setText(light);
        hum.clear();
        light.clear();
        tem.clear();

        if(beep=="1"){
            ui->label_beep->setText("开");//弹出警告
        }else{
            ui->label_beep->setText("关");
        }
        if(fan=="0"){
            ui->label_fan->setText("关");
        }else if(fan=="1"){
            ui->label_fan->setText("1档");
        }else if(fan=="2"){
            ui->label_fan->setText("2档");
        }else if(fan=="3"){
            ui->label_fan->setText("3档");
        }
        if(led3=="0"){
            ui->label_led3->setText("关");
        }else if(led3=="1"){
            ui->label_led3->setText("1档");
        }else if(led3=="2"){
            ui->label_led3->setText("2档");
        }else if(led3=="3"){
            ui->label_led3->setText("3档");
        }
        qDebug()<<"状态更新"<<endl;
    }
}

/************************TCP上位机write访问数据库JSON格式通信**************************/
//设备绑定
void Func::on_pushButton_bind_clicked()
{
    QString ID = ui->label_ID->text();
    QString ChipID = ui->lineEdit_ChipID->text();
    QString name = ui->lineEdit_name->text();
    if(ChipID.isEmpty() || name.isEmpty() ) return ;    //不能让其为空

    QJsonObject json;
    json["CMD"] = "绑定";
    json["ID"] = ID;
    json["ChipID"] = ChipID;
    json["name"] = name;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    TcpSocket->write(data);//发送信息
}
//更新温湿度光照控制类数据
void Func::on_pushButton_clicked()//
{
    int index = ui->comboBox->currentIndex();
    if(index < 0) return ;
    QString ChipID = m_ChipID[index];

    QJsonObject json;
    json["CMD"] = "状态";
    json["ID"]=ui->label_ID->text();
    json["ChipID"]=ChipID;

    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    TcpSocket->write(data);//发送信息
}

//测试打印芯片ID
#include <QBitmap>
#include <QDebug>
#include <QHostInfo>
void Func::on_comboBox_currentIndexChanged(int index)
{
    if(index < 0 || flag == false) return ;
    qDebug() << "芯片ID:" << m_ChipID[index] << endl;
}

/*************************MQTT通信设备控制部分********************************************************/
//发送主题为芯片ID，信息为控制指令
void Func::Mqtt_put(QByteArray data)
{
    /**************** 获取芯片ID ************/
    int index = ui->comboBox->currentIndex();
//    qDebug()<<"index="<<index<<endl;
    if(index < 0) return ;

    QString ChipID = m_ChipID[index];

    Mqtt->publish(QMqttTopicName(ChipID),data); //发布到指定下位机芯片ID的消息，下位机自己订阅自己的主题信息
}
//指令判断
//蜂鸣器开
void Func::on_pushButton_ON_clicked()
{
    ui->widget_beep_switch->setChecked(1);
    QJsonObject json;
    json["alarm"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//蜂鸣器关
void Func::on_pushButton_OFF_clicked()
{
    ui->widget_beep_switch->setChecked(0);
    QJsonObject json;
    json["alarm"] = false;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//LDE1开
void Func::on_pushButton_LED_ON_clicked()
{
    QJsonObject json;
    json["LED1"] = false;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//LED1关
void Func::on_pushButton_LED_OFF_clicked()
{
    QJsonObject json;
    json["LED1"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//风扇1挡FAn1
void Func::on_pushButton_FAN1_clicked()
{
    QJsonObject json;
    json["FAN1"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}

//风扇2挡FAN2
void Func::on_pushButton_FAN2_clicked()
{
    QJsonObject json;
    json["FAN2"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//风扇3挡FAN3
void Func::on_pushButton_FAN3_clicked()
{
    QJsonObject json;
    json["FAN3"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//风扇关FAN0
void Func::on_pushButton_FAN_Close_clicked()
{
    QJsonObject json;
    json["FAN0"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//LED2_0挡
void Func::on_pushButton_LED2_close_clicked()
{
    QJsonObject json;
    json["LED2_0"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//LED2_1挡
void Func::on_pushButton_LED2_1_clicked()
{
    QJsonObject json;
    json["LED2_1"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//LED2_2挡
void Func::on_pushButton_LED2_2_clicked()
{
    QJsonObject json;
    json["LED2_2"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//LED2_3挡
void Func::on_pushButton_LDE2_3_clicked()
{
    QJsonObject json;
    json["LED2_3"] = true;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}
//LED3 PWM改变
void Func::on_horizontalSlider_LED3_PWM_sliderMoved(int position)
{
    QJsonObject json;
    json["LED3"] = position;
    /*---- 发送 ----*/
    QByteArray data = QJsonDocument(json).toJson();
    Mqtt_put(data);
}

//**********************************录音开始
void Func::RecorderStart(QString fileName)
{
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    if(device.isNull())
    {
        QMessageBox::warning(NULL,"QAudioDeviceInfo","录音设备不存在");
        return;
    }
//    设置通道数
    audioFormat.setChannelCount(1);
//    设置编码
    audioFormat.setCodec("audio/pcm");
//    设置采样频率
    audioFormat.setSampleRate(16000);
//    设置位深
    audioFormat.setSampleSize(16);
//    判断设备是否支持该格式
    if(!device.isFormatSupported(audioFormat)){ //当前使用设备是否支持
        audioFormat = device.nearestFormat(audioFormat); //转换为最接近格式
    }
//    创建录音对象
    my_audio = new QAudioInput(audioFormat,this);
    outFile = new QFile(this);
    outFile->setFileName(fileName); //语音原始文件
    outFile->open(QIODevice::WriteOnly);
//     开始录音
    my_audio->start(outFile);
}

/**********************
 * 结束录音并转换格式
**********************/
void Func::RecorderEnd()
{
//    结束录音
    my_audio->stop();

    outFile->close();
    delete outFile;
    outFile =NULL;

    delete my_audio;
    my_audio = NULL;
}

//按钮按下开始识别
void Func::on_pushButton_robot_pressed()
{
    RecorderStart("./1.pcm");
    ui->pushButton_robot->setText("松开识别");
    ui->label_robot->setPixmap(QPixmap(":/new/prefix1/res/机器人_speak.png"));
}

//按钮松开开始语音识别，并返回文字搜索音乐
void Func::on_pushButton_robot_released()
{
    ui->pushButton_robot->setText("按下说话");
    ui->label_robot->setPixmap(QPixmap(":/new/prefix1/res/机器人.png"));
    RecorderEnd();
    QString text =speechIdentify("./1.pcm");
    audioCtrl(text);
}


//识别结果处理，填入lineEdit，触发搜索按键
void Func::audioCtrl(QString text)
{
    QString strTmp = text.left(text.size()-1);
    qDebug()<<"语音识别结果:"<<strTmp<<endl;
    if(strTmp=="开灯"){
        emit ui->pushButton_LED_ON->clicked();
    }else if(strTmp=="关灯"){
        emit ui->pushButton_LED_OFF->clicked();
    }else if(strTmp=="开风扇"){
        emit ui->pushButton_FAN1->clicked();
    }else if(strTmp=="关风扇"){
        emit ui->pushButton_FAN_Close->clicked();
    }else if(strTmp=="热死了"){
        emit ui->pushButton_FAN3->clicked();
    }else if(strTmp=="灯亮一点"){
        emit ui->pushButton_LDE2_3->clicked();
    }else if(strTmp=="灯暗一点"){
        emit ui->pushButton_LED2_1->clicked();
    }else if(strTmp=="报警"){
        emit ui->pushButton_ON->clicked();
    }else if(strTmp=="别叫了"){
        emit ui->pushButton_OFF->clicked();
    }else if(strTmp=="查看天气"){
        slot_btn_request();
    }else if(strTmp=="广州天气"){
        ui->comboBox_weather->setCurrentIndex(3);
        slot_btn_request();
    }else if(strTmp=="北京天气"){
        ui->comboBox_weather->setCurrentIndex(2);
        slot_btn_request();
    }
}

//求url组装
bool Func::post_sync(QString url,QMap<QString,QString>header,QByteArray requestData,QByteArray &replyData)
{
//    发送请求的对象
    QNetworkAccessManager manager;
//    请求 对象
    QNetworkRequest request;
    request.setUrl(url);
    QMapIterator<QString,QString> it(header);
    while (it.hasNext()) {
        it.next();
        request.setRawHeader(it.key().toLatin1() ,it.value().toLatin1());
    }
//设置openssl签名配置,否则在ARM上会报错
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    conf.setProtocol(QSsl::TlsV1_0);
#else
    conf.setProtocol(QSsl::TlsV1);
#endif
    request.setSslConfiguration(conf);

    QNetworkReply *reply = manager.post(request,requestData);
    QEventLoop l;
    //一旦服务器返回，reply会发出信号
    connect(reply,&QNetworkReply::finished,&l,&QEventLoop::quit);
    l.exec();
    if(reply != nullptr && reply->error() == QNetworkReply::NoError)
    {

        replyData = reply->readAll();
        return true;
    }
    else
    {
        qDebug()<<"request error!";
        return false;
    }
}
//发送请求，百度识别返回结果，送给getJsonValue处理
QString Func::speechIdentify(QString fileName)
{
//    获取Access Token
    QString tokenUrl =QString(baiduTokenUrl).arg(client_id).arg(client_secret);
    QMap<QString,QString>header;
    header.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));
    QByteArray requestData;//请求内容
    QByteArray replyData;//url返回内容

   qDebug()<<tokenUrl;
    bool result = post_sync(tokenUrl,header,requestData,replyData);
    if(result) {
        QString key = "access_token";
        QString accessToken =getJsonValue(replyData,key);
        qDebug()<<accessToken;
        //    语音识别
        QString speechUrl = QString(baiduSpeechUrl).arg(QHostInfo::localHostName()).arg(accessToken);
        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);
        requestData = file.readAll();
        file.close();
        replyData.clear();
//        再次发起请求
        result = post_sync(speechUrl,header,requestData,replyData);
         if(result) {
             QString key = "result";
             QString retText =getJsonValue(replyData,key);
             qDebug()<<retText;
             return retText;
         }
         else{
             return NULL;
         }
    }
    else {
        return  "error";
    }
}
//解析返回的语音JOSN格式，得到语音识别的结果
QString Func::getJsonValue(QByteArray ba,QString key)
{
    QJsonParseError parseError;
    QJsonDocument jsondocument = QJsonDocument::fromJson(ba,&parseError);
    if(parseError.error ==QJsonParseError::NoError)
    {
        if(jsondocument.isObject())
        {
            QJsonObject jsonObject = jsondocument.object();
            if(jsonObject.contains(key)){
                QJsonValue jsonvalue = jsonObject.value(key);
                if(jsonvalue.isString())
                    return jsonvalue.toString();
                else if(jsonvalue.isArray()){
                    QJsonArray arr = jsonvalue.toArray();
                    QJsonValue val =arr.at(0);
                    return val.toString();
                }
            }
        }
    }
    return "";
}

//**************************天气显示****************************
//天气请求URL get
void Func::slot_btn_request()
{
    //获取comboBox栏的信息
    QString city=ui->comboBox_weather->currentText();

    //组装url信息
    QString url= "http://aider.meizu.com/app/weather/listWeather?cityIds=";
    url += m_city[city];
    //请求连接方式：get/post
    this->replay=this->http->get(QNetworkRequest(QUrl(url)));//请求链接
}
//请求回复读取JSON
void Func::slots_http_finshed(QNetworkReply *reply)
{
    int stat=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    //读取全部接受到的信息
    QByteArray data=reply->readAll();
    if(stat!=200){//成功获取
        QMessageBox::warning(this,"http警告","请求失败，错误数据:"+data);
        return;
    }

    //解析成JSON格式文本
    QJsonDocument document=QJsonDocument::fromJson(data);
    QJsonObject jsonObject=document.object();
    QJsonArray json_value=jsonObject.value("value").toArray();

    QJsonArray json_alarms=json_value.at(0).toObject().value("alarms").toArray();
    QJsonObject object_alarms=json_alarms.at(0).toObject();

    QJsonArray json_weather = json_value.at(0).toObject().value("weathers").toArray();
    QJsonObject object_weather =json_weather.at(0).toObject();
    qDebug()<<object_weather["weather"].toString();
    QString mes = "城市:" ;
    mes += ui->comboBox_weather->currentText();
    mes += "         日期:";
    mes += object_weather["date"].toString();
    mes += "   星期:";
    mes += object_weather["week"].toString();
    mes += "\n白天温度:";
    mes += object_weather["temp_day_c"].toString();
    mes += "摄氏度  晚上温度:";
    mes += object_weather["temp_night_c"].toString();
    mes += "摄氏度  天气:";
    mes += object_weather["weather"].toString();
    mes +="\n天气预警:";
    mes += object_alarms["alarmContent"].toString().insert(25, QString("\n")).insert(50, QString("\n")).
            insert(75, QString("\n")).insert(100, QString("\n")).insert(125, QString("\n")).insert(150, QString("\n"));
    //将读取的信息直接set到label_weather_text中
    ui->label_weather_text->setText(mes);
}

//***************************QChart光照折线图***********************
void Func::dataReceived1(int value) {
    data1<<value;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (data1.size() > maxSize) {
        data1.removeFirst();
    }

    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        splineSeries1->clear();
        scatterSeries1->clear();
        int dx = maxX / (maxSize-1);

        for (int i = 0; i < data1.size(); ++i) {
            splineSeries1->append((i+1)*dx, data1.at(i));
            scatterSeries1->append((i+1)*dx, data1.at(i));
        }
    }
    chartView->update();
}

void Func::dataReceived2(int value) {
    data2<<value;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (data2.size() > maxSize) {
        data2.removeFirst();
    }

    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        splineSeries2->clear();
        scatterSeries2->clear();
        int dx = maxX / (maxSize-1);

        for (int i = 0; i < data2.size(); ++i) {
            splineSeries2->append((i+1)*dx, data2.at(i));
            scatterSeries2->append((i+1)*dx, data2.at(i));
        }
    }
    chartView->update();
}

void Func::dataReceived3(int value) {
    data3<<value;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (data3.size() > maxSize) {
        data3.removeFirst();
    }

    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        splineSeries3->clear();
        scatterSeries3->clear();
        int dx = maxX / (maxSize-1);

        for (int i = 0; i < data3.size(); ++i) {
            splineSeries3->append((i+1)*dx, data3.at(i));
            scatterSeries3->append((i+1)*dx, data3.at(i));
        }
    }
}


//**************************QLabel圆形图片，动态边框***************************
QPixmap Func::PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
    QPixmap image = src.scaled(size);
    image.setMask(mask);

    return image;
}


//添加上位机控制指令
Func::~Func()
{

    delete chart;

    delete ui;
}











