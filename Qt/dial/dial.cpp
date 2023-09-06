#include "dial.h"
#include "ui_dial.h"

Dial::Dial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dial)
{
    ui->setupUi(this);
    m_foreground = Qt::magenta;
    m_background = Qt::red;
    m_title = "标题";
    m_startAngle = 45;
    m_endAngle = 45;
    m_scaleMajor = 10;
    m_minValue = 0;
    m_maxValue = 50;
    m_scaleMinor = 5;
    m_value = 0;
}

void Dial::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font("宋体", 14);
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    //坐标变换为窗体中心
    int side = qMin(width(), height());
    painter.scale(side / 400.0, side / 400.0);
    //比例缩放
    drawCrown(&painter);
    //画表盘边框
    drawScaleNum(&painter);
    //画刻度数值
    drawScale(&painter);
    //画刻度线
    drawTitle(&painter);
    //画单位
//    drawNumericValue(&painter);
    //画数字显示
    drawIndicator(&painter);
}


void Dial::drawCrown(QPainter *painter)
{
    painter->save();
    int radius = 200;
    painter->setBrush(m_background = QColor(20,20,20));
    QLinearGradient lg1(0, -220, 0, 220);
    lg1.setColorAt(0, Qt::darkCyan);
    lg1.setColorAt(1, QColor(20, 20, 20));
    painter->setBrush(lg1);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-radius, -radius, radius << 1, radius <<1);
    painter->setBrush(m_background = QColor(20, 20, 20));
    painter->drawEllipse(-180, -180, 360, 360);
    painter->restore();
}

void Dial::drawTitle(QPainter *painter)
{
    painter->save();
    painter->setPen(QColor(220,200,200,200));
    QString str(m_title);
    QFontMetricsF fm(this->font());
    painter->drawText(-30, -50, str);
    painter->restore();
}

void Dial::drawScaleNum(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(QColor(255,255,255)));
    QFontMetricsF fm(this->font());
    int radius = 200;
    int r=(int)(radius*0.8);
    int Angle=45;
    int gap = (360-Angle*2) / 10;
    for(int i=0; i<=10; i+=1)
    {
        int angle = 90+Angle+gap*i;                                 //角度,每隔10格子画一个刻度值
        float angleArc =( angle % 360) * 3.14159 / 180;                //转换为弧度
        int x = (r)*cos(angleArc);
        int y = (r)*sin(angleArc);
        QString value =QString( "%1" ).arg(i*m_maxValue/10);
        //字体大小及位置要微调
        int h = fm.size(Qt::TextSingleLine,value).height();
        x = x -10;
        y = y + h/2;
        painter->drawText(QPointF(x, y),value);
    }
    painter->restore();
}

void Dial::drawScale(QPainter *painter)
{
    painter->save();
    painter->rotate(m_startAngle);
    int steps = (m_scaleMajor * m_scaleMinor);                          //总刻度数量
    double angleStep = (360.0 - m_startAngle - m_endAngle) / steps;     //每一个份数的角度
    for (int i = 0; i <= steps; i++)
    {
        if (i % m_scaleMinor == 0)                                      //大刻度
        {
            QPen pen ;
            pen.setColor(Qt::lightGray);
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawLine(0, 125, 0, 145);
        }
        else                                                            //小刻度
        {
            QPen pen ;
            pen.setColor(Qt::darkGray);
            pen.setWidth(1);
            painter->setPen(pen);
            painter->drawLine(0, 125, 0, 135);
        }
        painter->rotate(angleStep);
    }
    painter->restore();
}


void Dial::drawIndicator(QPainter *painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(5, -2,0, -4,30, 0,120, 4,30, 2,0);
    //第一个参数是坐标的个数，记下来是坐标
    painter->rotate(m_startAngle);
    double degRotate =  (360.0 - m_startAngle - m_endAngle)/(m_maxValue - m_minValue)*(m_value - m_minValue);

    //画指针
    painter->rotate(degRotate);

    //顺时针旋转坐标系统
    QRadialGradient haloGradient(0, 0, 60, 0, 0);
    //辐射渐变
    haloGradient.setColorAt(0, QColor(60,60,60));
    haloGradient.setColorAt(1, QColor(160,160,160));
    painter->setPen(Qt::yellow);
    //定义线条文本颜色  设置线条的颜色
    painter->setBrush(haloGradient);
    //刷子定义形状如何填满 填充后的颜色
    painter->drawConvexPolygon(pts);
    painter->restore();
    //画中心点
    QColor niceBlue(150, 150, 200);
    QConicalGradient coneGradient(0, 0, -90.0);
    //角度渐变
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::yellow);
    coneGradient.setColorAt(1.0, Qt::darkGray);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-8, -8, 16, 16);
}

int Dial::scaleMinor() const
{
    return m_scaleMinor;
}

void Dial::setScaleMinor(int scaleMinor)
{
    m_scaleMinor = scaleMinor;
    this->update(); //更新事件
}

QColor Dial::background() const
{
    return m_background;
}

void Dial::setBackground(const QColor &background)
{
    m_background = background;
    this->update(); //更新事件
}

QColor Dial::foreground() const
{
    return m_foreground;
}

void Dial::setForeground(const QColor &foreground)
{
    m_foreground = foreground;
    this->update(); //更新事件
}

int Dial::maxValue() const
{
    return m_maxValue;
}

void Dial::setMaxValue(int maxValue)
{
    m_maxValue = maxValue;
    this->update(); //更新事件
}

void Dial::setRange(int minValue, int maxValue)
{
    m_minValue = minValue;
    m_maxValue = maxValue;
    this->update(); //更新事件
}

int Dial::minValue() const
{
    return m_minValue;
}

void Dial::setMinValue(int minValue)
{
    m_minValue = minValue;
    this->update(); //更新事件
}

int Dial::value() const
{
    return m_value;
}

void Dial::setValue(int value)
{
    m_value = value;
    this->update(); //更新事件
}

QString Dial::title() const
{
    return m_title;
}

void Dial::setTitle(const QString &title)
{
    m_title = title;
    this->update(); //更新事件
}



Dial::~Dial()
{
    delete ui;
}

