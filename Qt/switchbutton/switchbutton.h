#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

/**
 * 开关按钮控件
 * 1:可设置开关按钮的样式 圆角矩形/内圆形/外圆形
 * 2:可设置选中和未选中时的背景颜色
 * 3:可设置选中和未选中时的滑块颜色
 * 4:可设置显示的文本
 * 5:可设置滑块离背景的间隔
 * 6:可设置圆角角度
 * 7:可设置是否显示动画过渡效果
 */

#include <QWidget>

class SwitchButton : public QWidget
{
    Q_OBJECT
    Q_ENUMS(ButtonStyle)

public:
    enum ButtonStyle {
        ButtonStyle_Rect = 0,       //圆角矩形
        ButtonStyle_CircleIn = 1,   //内圆形
        ButtonStyle_CircleOut = 2   //外圆形
    };

    SwitchButton(QWidget *parent = 0);
    ~SwitchButton();

protected:
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawSlider(QPainter *painter);

private:
    int space;                      //滑块离背景间隔
    int rectRadius;                 //圆角角度
    bool checked;                   //是否选中
    bool showText;                  //显示文字
    bool animation;                 //动画过渡

    ButtonStyle buttonStyle;        //开关按钮样式

    QColor bgColorOff;              //关闭时背景颜色
    QColor bgColorOn;               //打开时背景颜色
    QColor sliderColorOff;          //关闭时滑块颜色
    QColor sliderColorOn;           //打开时滑块颜色
    QColor textColorOff;            //关闭时文字颜色
    QColor textColorOn;             //打开时文字颜色

    QString textOff;                //关闭时显示的文字
    QString textOn;                 //打开时显示的文字

    int step;                       //每次移动的步长
    int startX;                     //滑块开始X轴坐标
    int endX;                       //滑块结束X轴坐标
    QTimer *timer;                  //定时器绘制

private slots:
    void change();
    void updateValue();

public:
    int getSpace()                  const;
    int getRectRadius()             const;
    bool getChecked()               const;
    bool getShowText()              const;
    bool getAnimation()             const;

    ButtonStyle getButtonStyle()    const;

    QColor getBgColorOff()          const;
    QColor getBgColorOn()           const;
    QColor getSliderColorOff()      const;
    QColor getSliderColorOn()       const;
    QColor getTextColorOff()        const;
    QColor getTextColorOn()         const;

    QString getTextOff()            const;
    QString getTextOn()             const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置间隔
    void setSpace(int space);
    //设置圆角角度
    void setRectRadius(int rectRadius);
    //设置是否选中
    void setChecked(bool checked);
    //设置是否显示文字
    void setShowText(bool showText);
    //设置是否动画过渡
    void setAnimation(bool animation);

    //设置风格样式
    void setButtonStyle(const ButtonStyle &buttonStyle);

    //设置背景颜色
    void setBgColorOff(const QColor &bgColorOff);
    void setBgColorOn(const QColor &bgColorOn);

    //设置滑块颜色
    void setSliderColorOff(const QColor &sliderColorOff);
    void setSliderColorOn(const QColor &sliderColorOn);

    //设置文字颜色
    void setTextColorOff(const QColor &textColorOff);
    void setTextColorOn(const QColor &textColorOn);

    //设置文字
    void setTextOff(const QString &textOff);
    void setTextOn(const QString &textOn);

Q_SIGNALS:
    void checkedChanged(bool checked);
};

#endif // SWITCHBUTTON_H
