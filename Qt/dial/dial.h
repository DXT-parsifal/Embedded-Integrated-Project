#ifndef DIAL_H
#define DIAL_H

#include <QWidget>
/*-------- Qt绘图事件和画家类 --------*/
#include <QPaintEvent>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Dial; }
QT_END_NAMESPACE

class Dial : public QWidget
{
    Q_OBJECT

public:
    Dial(QWidget *parent = nullptr);
    ~Dial();

public:
    void paintEvent(QPaintEvent *);
    void drawCrown(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawIndicator(QPainter *painter);
private:
    Ui::Dial *ui;
public:
    QColor m_foreground;    //前景色
    QColor m_background;    //背景色
    QString m_title;        //标题
    int m_startAngle;       //开始角度
    int m_endAngle;         //结束角度
    int m_scaleMajor;       //缩放比例
    int m_minValue;         //最小值
    int m_maxValue;         //最大值
    int m_scaleMinor;       //刻度步长
    int m_value;            //当前显示数值
public: //获取相关属性
    QString title() const;
    int value() const;
    int minValue() const;
    int maxValue() const;
    QColor foreground() const;
    QColor background() const;
    int scaleMinor() const;
public slots://设置相关属性
    void setTitle(const QString &title);            //设置标题
    void setValue(int value);                       //设置当前值
    void setScaleMinor(int scaleMinor);             //设置步长
    void setMinValue(int minValue);                 //设置最小范围
    void setMaxValue(int maxValue);                 //设置最大范围
    void setRange(int minValue,int maxValue);       //设置范围
    void setForeground(const QColor &foreground);   //设置前景色(未开)
    void setBackground(const QColor &background);   //设置背景色(未开)
};
#endif // DIAL_H
