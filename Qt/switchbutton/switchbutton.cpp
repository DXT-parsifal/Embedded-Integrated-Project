#pragma execution_character_set("utf-8")

#include "switchbutton.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

SwitchButton::SwitchButton(QWidget *parent): QWidget(parent)
{
    space = 2;
    rectRadius = 5;
    checked = false;
    showText = false;
    animation = true;

    buttonStyle	= ButtonStyle_CircleIn;

    bgColorOff = QColor(229, 229, 229);
    bgColorOn = QColor(100, 184, 255);

    sliderColorOff = QColor(255, 255, 255);
    sliderColorOn = QColor(255, 255, 255);

    textColorOff = QColor(32, 32, 32);
    textColorOn = QColor(255, 255, 255);

    textOff = "关闭";
    textOn = "开启";

    step = 0;
    startX = 0;
    endX = 0;

    timer = new QTimer(this);
    timer->setInterval(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
}

SwitchButton::~SwitchButton()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void SwitchButton::mousePressEvent(QMouseEvent *)
{
    checked = !checked;
    emit checkedChanged(checked);

    //每次移动的步长
    step = width() / 7;

    //状态切换改变后自动计算终点坐标
    if (checked) {
        if (buttonStyle == ButtonStyle_Rect) {
            endX = width() - width() / 2;
        } else if (buttonStyle == ButtonStyle_CircleIn) {
            endX = width() - height();
        } else if (buttonStyle == ButtonStyle_CircleOut) {
            endX = width() - height();
        }
    } else {
        endX = 0;
    }

    if (animation) {
        timer->start();
    } else {
        startX = endX;
        update();
    }
}

void SwitchButton::resizeEvent(QResizeEvent *)
{
    //每次移动的步长为宽度的 50分之一
    step = width() / 50;

    //尺寸大小改变后自动设置起点坐标为终点
    if (checked) {
        if (buttonStyle == ButtonStyle_Rect) {
            startX = width() - width() / 2;
        } else if (buttonStyle == ButtonStyle_CircleIn) {
            startX = width() - height();
        } else if (buttonStyle == ButtonStyle_CircleOut) {
            startX = width() - height();
        }
    } else {
        startX = 0;
    }

    update();
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制滑块
    drawSlider(&painter);
}

void SwitchButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked) {
        painter->setBrush(bgColorOff);
    } else {
        painter->setBrush(bgColorOn);
    }

    if (buttonStyle == ButtonStyle_Rect) {
        painter->drawRoundedRect(rect(), rectRadius, rectRadius);
    } else if (buttonStyle == ButtonStyle_CircleIn) {
        QRect rect(0, 0, width(), height());
        //半径为高度的一半
        int side = qMin(rect.width(), rect.height());

        //左侧圆
        QPainterPath path1;
        path1.addEllipse(rect.x(), rect.y(), side, side);
        //右侧圆
        QPainterPath path2;
        path2.addEllipse(rect.width() - side, rect.y(), side, side);
        //中间矩形
        QPainterPath path3;
        path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, rect.height());

        QPainterPath path;
        path = path3 + path1 + path2;
        painter->drawPath(path);
    } else if (buttonStyle == ButtonStyle_CircleOut) {
        QRect rect(height() / 2, space, width() - height(), height() - space * 2);
        painter->drawRoundedRect(rect, rectRadius, rectRadius);
    }

    //绘制文本
    if (buttonStyle == ButtonStyle_Rect || buttonStyle == ButtonStyle_CircleIn) {
        if (showText) {
            int sliderWidth = qMin(width(), height()) - space * 2;

            if (buttonStyle == ButtonStyle_Rect) {
                sliderWidth += 5;
            } else if (buttonStyle == ButtonStyle_CircleIn) {
                sliderWidth -= 5;
            }

            if (checked) {
                QRect textRect(0, 0, width() - sliderWidth, height());
                painter->setPen(textColorOn);
                painter->drawText(textRect, Qt::AlignCenter, textOn);
            } else {
                QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
                painter->setPen(textColorOff);
                painter->drawText(textRect, Qt::AlignCenter, textOff);
            }
        }
    }

    painter->restore();
}

void SwitchButton::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked) {
        painter->setBrush(sliderColorOff);
    } else {
        painter->setBrush(sliderColorOn);
    }

    if (buttonStyle == ButtonStyle_Rect) {
        int sliderWidth = width() / 2 - space * 2;
        int sliderHeight = height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth , sliderHeight);
        painter->drawRoundedRect(sliderRect, rectRadius, rectRadius);
    } else if (buttonStyle == ButtonStyle_CircleIn) {
        QRect rect(0, 0, width(), height());
        int sliderWidth = qMin(rect.width(), rect.height()) - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
    } else if (buttonStyle == ButtonStyle_CircleOut) {
        int sliderWidth = this->height();
        QRect sliderRect(startX, 0, sliderWidth, sliderWidth);

        QColor color1 = (checked ? Qt::white : bgColorOff);
        QColor color2 = (checked ? sliderColorOn : sliderColorOff);

        QRadialGradient radialGradient(sliderRect.center(), sliderWidth / 2);
        radialGradient.setColorAt(0, checked ? color1 : color2);
        radialGradient.setColorAt(0.5, checked ? color1 : color2);
        radialGradient.setColorAt(0.6, checked ? color2 : color1);
        radialGradient.setColorAt(1.0, checked ? color2 : color1);
        painter->setBrush(radialGradient);

        painter->drawEllipse(sliderRect);
    }

    painter->restore();
}

void SwitchButton::change()
{
    mousePressEvent(NULL);
}

void SwitchButton::updateValue()
{
    if (checked) {
        if (startX < endX) {
            startX = startX + step;
        } else {
            startX = endX;
            timer->stop();
        }
    } else {
        if (startX > endX) {
            startX = startX - step;
        } else {
            startX = endX;
            timer->stop();
        }
    }

    update();
}

int SwitchButton::getSpace() const
{
    return this->space;
}

int SwitchButton::getRectRadius() const
{
    return this->rectRadius;
}

bool SwitchButton::getChecked() const
{
    return this->checked;
}

bool SwitchButton::getShowText() const
{
    return this->showText;
}

bool SwitchButton::getAnimation() const
{
    return this->animation;
}

SwitchButton::ButtonStyle SwitchButton::getButtonStyle() const
{
    return this->buttonStyle;
}

QColor SwitchButton::getBgColorOff() const
{
    return bgColorOff;
}

QColor SwitchButton::getBgColorOn() const
{
    return this->bgColorOn;
}

QColor SwitchButton::getSliderColorOff() const
{
    return this->sliderColorOff;
}

QColor SwitchButton::getSliderColorOn() const
{
    return this->sliderColorOn;
}

QColor SwitchButton::getTextColorOff() const
{
    return this->textColorOff;
}

QColor SwitchButton::getTextColorOn() const
{
    return this->textColorOn;
}

QString SwitchButton::getTextOff() const
{
    return this->textOff;
}

QString SwitchButton::getTextOn() const
{
    return this->textOn;
}

QSize SwitchButton::sizeHint() const
{
    return QSize(60, 30);
}

QSize SwitchButton::minimumSizeHint() const
{
    return QSize(10, 5);
}

void SwitchButton::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void SwitchButton::setRectRadius(int rectRadius)
{
    if (this->rectRadius != rectRadius) {
        this->rectRadius = rectRadius;
        update();
    }
}

void SwitchButton::setChecked(bool checked)
{
    //如果刚刚初始化完成的属性改变则延时处理
    if (this->checked != checked) {
        if (step == 0) {
            QTimer::singleShot(10, this, SLOT(change()));
        } else {
            mousePressEvent(NULL);
        }
    }
}

void SwitchButton::setShowText(bool showText)
{
    if (this->showText != showText) {
        this->showText = showText;
        update();
    }
}

void SwitchButton::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void SwitchButton::setButtonStyle(const SwitchButton::ButtonStyle &buttonStyle)
{
    if (this->buttonStyle != buttonStyle) {
        this->buttonStyle = buttonStyle;
        update();
    }
}

void SwitchButton::setBgColorOff(const QColor &bgColorOff)
{
    if (this->bgColorOff != bgColorOff) {
        this->bgColorOff = bgColorOff;
        update();
    }
}

void SwitchButton::setBgColorOn(const QColor &bgColorOn)
{
    if (this->bgColorOn != bgColorOn) {
        this->bgColorOn = bgColorOn;
        update();
    }
}

void SwitchButton::setSliderColorOff(const QColor &sliderColorOff)
{
    if (this->sliderColorOff != sliderColorOff) {
        this->sliderColorOff = sliderColorOff;
        update();
    }
}

void SwitchButton::setSliderColorOn(const QColor &sliderColorOn)
{
    if (this->sliderColorOn != sliderColorOn) {
        this->sliderColorOn = sliderColorOn;
        update();
    }
}

void SwitchButton::setTextColorOff(const QColor &textColorOff)
{
    if (this->textColorOff != textColorOff) {
        this->textColorOff = textColorOff;
        update();
    }
}

void SwitchButton::setTextColorOn(const QColor &textColorOn)
{
    if (this->textColorOn != textColorOn) {
        this->textColorOn = textColorOn;
        update();
    }
}

void SwitchButton::setTextOff(const QString &textOff)
{
    if (this->textOff != textOff) {
        this->textOff = textOff;
        update();
    }
}

void SwitchButton::setTextOn(const QString &textOn)
{
    if (this->textOn != textOn) {
        this->textOn = textOn;
        update();
    }
}
