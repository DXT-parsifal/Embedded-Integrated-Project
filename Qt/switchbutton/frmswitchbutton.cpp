#pragma execution_character_set("utf-8")

#include "frmswitchbutton.h"
#include "ui_frmswitchbutton.h"
#include "switchbutton.h"

frmSwitchButton::frmSwitchButton(QWidget *parent) : QWidget(parent), ui(new Ui::frmSwitchButton)
{
    ui->setupUi(this);
    this->initForm();
}

frmSwitchButton::~frmSwitchButton()
{
    delete ui;
}

void frmSwitchButton::initForm()
{
    QColor color1(100, 184, 255);
    QColor color2(24, 189, 155);
    QColor color3(255, 107, 107);
    QColor color4(21, 156, 119);

    ui->switchButton12->setBgColorOn(color2);
    ui->switchButton13->setBgColorOn(color3);
    ui->switchButton14->setBgColorOn(color4);

    ui->switchButton12->setShowText(true);
    ui->switchButton13->setShowText(true);
    ui->switchButton13->setTextOff("停止");
    ui->switchButton13->setTextOn("启动");
    ui->switchButton14->setShowText(true);
    ui->switchButton14->setTextOff("禁用");
    ui->switchButton14->setTextOn("启用");
    ui->switchButton14->setAnimation(false);

    ui->switchButton12->setChecked(true);
    ui->switchButton14->setChecked(true);

    ui->switchButton21->setButtonStyle(SwitchButton::ButtonStyle_Rect);
    ui->switchButton22->setButtonStyle(SwitchButton::ButtonStyle_Rect);
    ui->switchButton23->setButtonStyle(SwitchButton::ButtonStyle_Rect);
    ui->switchButton24->setButtonStyle(SwitchButton::ButtonStyle_Rect);

    ui->switchButton22->setBgColorOn(color2);
    ui->switchButton23->setBgColorOn(color3);
    ui->switchButton24->setBgColorOn(color4);

    ui->switchButton22->setShowText(true);
    ui->switchButton23->setShowText(true);
    ui->switchButton23->setTextOff("停止");
    ui->switchButton23->setTextOn("启动");
    ui->switchButton24->setShowText(true);
    ui->switchButton24->setTextOff("禁用");
    ui->switchButton24->setTextOn("启用");
    ui->switchButton24->setAnimation(false);

    ui->switchButton21->setChecked(true);
    ui->switchButton23->setChecked(true);

    ui->switchButton31->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);
    ui->switchButton32->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);
    ui->switchButton33->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);
    ui->switchButton34->setButtonStyle(SwitchButton::ButtonStyle_CircleOut);

    int space = 8;
    ui->switchButton31->setSpace(space);
    ui->switchButton32->setSpace(space);
    ui->switchButton33->setSpace(space);
    ui->switchButton34->setSpace(space);

    int radius = 8;
    ui->switchButton31->setRectRadius(radius);
    ui->switchButton32->setRectRadius(radius);
    ui->switchButton33->setRectRadius(radius);
    ui->switchButton34->setRectRadius(radius);

    ui->switchButton32->setBgColorOn(color2);
    ui->switchButton33->setBgColorOn(color3);
    ui->switchButton34->setBgColorOn(color4);

    ui->switchButton31->setSliderColorOn(color1);
    ui->switchButton32->setSliderColorOn(color2);
    ui->switchButton33->setSliderColorOn(color3);
    ui->switchButton34->setSliderColorOn(color4);

    ui->switchButton32->setShowText(true);
    ui->switchButton33->setShowText(true);
    ui->switchButton33->setTextOff("停止");
    ui->switchButton33->setTextOn("启动");
    ui->switchButton34->setShowText(true);
    ui->switchButton34->setTextOff("禁用");
    ui->switchButton34->setTextOn("启用");
    ui->switchButton34->setAnimation(false);

    ui->switchButton32->setChecked(true);
    ui->switchButton34->setChecked(true);
}
