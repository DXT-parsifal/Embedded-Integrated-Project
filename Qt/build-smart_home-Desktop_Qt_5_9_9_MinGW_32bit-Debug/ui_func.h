/********************************************************************************
** Form generated from reading UI file 'func.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNC_H
#define UI_FUNC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dial.h"
#include "switchbutton.h"

QT_BEGIN_NAMESPACE

class Ui_Func
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_19;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_ChipID;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_name;
    QPushButton *pushButton_bind;
    QHBoxLayout *horizontalLayout_18;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *label_ID;
    QSpacerItem *horizontalSpacer;
    QLabel *label_image;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_robot;
    QPushButton *pushButton_robot;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QPushButton *pushButton_ON;
    QPushButton *pushButton_OFF;
    SwitchButton *widget_beep_switch;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QPushButton *pushButton_LED2_close;
    QPushButton *pushButton_LED2_1;
    QPushButton *pushButton_LED2_2;
    QPushButton *pushButton_LDE2_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QPushButton *pushButton_LED_ON;
    QPushButton *pushButton_LED_OFF;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QPushButton *pushButton_FAN_Close;
    QPushButton *pushButton_FAN1;
    QPushButton *pushButton_FAN2;
    QPushButton *pushButton_FAN3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_15;
    QSlider *horizontalSlider_LED3_PWM;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *pushButton_weather;
    QComboBox *comboBox_weather;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_weather_text;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QLabel *label_fan;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QLabel *label_beep;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QLabel *label_led3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLabel *label_hum;
    Dial *widget_temp;
    Dial *widget_hum;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLabel *label_tem;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QLabel *label_light;
    QWidget *widget_chart;

    void setupUi(QWidget *Func)
    {
        if (Func->objectName().isEmpty())
            Func->setObjectName(QStringLiteral("Func"));
        Func->resize(1124, 643);
        Func->setStyleSheet(QLatin1String("background-color: rgb(30, 40, 50);\n"
"color: rgb(255, 255, 255);\n"
""));
        verticalLayout_4 = new QVBoxLayout(Func);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        groupBox = new QGroupBox(Func);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_4 = new QHBoxLayout(groupBox);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_ChipID = new QLineEdit(groupBox);
        lineEdit_ChipID->setObjectName(QStringLiteral("lineEdit_ChipID"));
        lineEdit_ChipID->setFont(font);
        lineEdit_ChipID->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_2->addWidget(lineEdit_ChipID);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        lineEdit_name = new QLineEdit(groupBox);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setFont(font);
        lineEdit_name->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout);

        pushButton_bind = new QPushButton(groupBox);
        pushButton_bind->setObjectName(QStringLiteral("pushButton_bind"));
        pushButton_bind->setMinimumSize(QSize(0, 60));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_bind->setFont(font1);
        pushButton_bind->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_4->addWidget(pushButton_bind);


        horizontalLayout_19->addWidget(groupBox);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        groupBox_2 = new QGroupBox(Func);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 100));
        groupBox_2->setFont(font);
        groupBox_2->setAlignment(Qt::AlignCenter);
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(80, 16777215));
        label_4->setFont(font);

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setFont(font);
        comboBox->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_5->addWidget(comboBox);

        horizontalSpacer_4 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        horizontalLayout_18->addWidget(groupBox_2);


        horizontalLayout_19->addLayout(horizontalLayout_18);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(12, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(Func);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 25));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        label_ID = new QLabel(Func);
        label_ID->setObjectName(QStringLiteral("label_ID"));
        label_ID->setMaximumSize(QSize(16777215, 25));
        label_ID->setFont(font2);
        label_ID->setStyleSheet(QLatin1String("background-color: rgb(170, 255, 127);\n"
"color: rgb(0, 0, 0);"));
        label_ID->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_ID);

        horizontalSpacer = new QSpacerItem(40, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_image = new QLabel(Func);
        label_image->setObjectName(QStringLiteral("label_image"));
        label_image->setStyleSheet(QLatin1String("\n"
"\n"
"    max-width:  100px;\n"
"    min-height: 100px;\n"
"    max-height: 100px;\n"
" \n"
"    border-radius: 50px;\n"
"    border-width: 0 0 0 0;"));

        horizontalLayout->addWidget(label_image);


        horizontalLayout_19->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(horizontalLayout_19);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_3 = new QGroupBox(Func);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setFont(font);
        groupBox_3->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setFont(font);
        groupBox_5->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_robot = new QLabel(groupBox_5);
        label_robot->setObjectName(QStringLiteral("label_robot"));

        verticalLayout_3->addWidget(label_robot);

        pushButton_robot = new QPushButton(groupBox_5);
        pushButton_robot->setObjectName(QStringLiteral("pushButton_robot"));
        pushButton_robot->setFont(font);
        pushButton_robot->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(pushButton_robot);


        gridLayout_3->addLayout(verticalLayout_3, 0, 1, 1, 1);

        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_3->addWidget(label_17, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_5, 5, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_5);

        pushButton_ON = new QPushButton(groupBox_3);
        pushButton_ON->setObjectName(QStringLiteral("pushButton_ON"));
        pushButton_ON->setFont(font);
        pushButton_ON->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_6->addWidget(pushButton_ON);

        pushButton_OFF = new QPushButton(groupBox_3);
        pushButton_OFF->setObjectName(QStringLiteral("pushButton_OFF"));
        pushButton_OFF->setFont(font);
        pushButton_OFF->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_6->addWidget(pushButton_OFF);

        widget_beep_switch = new SwitchButton(groupBox_3);
        widget_beep_switch->setObjectName(QStringLiteral("widget_beep_switch"));

        horizontalLayout_6->addWidget(widget_beep_switch);


        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(label_10);

        pushButton_LED2_close = new QPushButton(groupBox_3);
        pushButton_LED2_close->setObjectName(QStringLiteral("pushButton_LED2_close"));
        pushButton_LED2_close->setFont(font);
        pushButton_LED2_close->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_12->addWidget(pushButton_LED2_close);

        pushButton_LED2_1 = new QPushButton(groupBox_3);
        pushButton_LED2_1->setObjectName(QStringLiteral("pushButton_LED2_1"));
        pushButton_LED2_1->setFont(font);
        pushButton_LED2_1->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_12->addWidget(pushButton_LED2_1);

        pushButton_LED2_2 = new QPushButton(groupBox_3);
        pushButton_LED2_2->setObjectName(QStringLiteral("pushButton_LED2_2"));
        pushButton_LED2_2->setFont(font);
        pushButton_LED2_2->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_12->addWidget(pushButton_LED2_2);

        pushButton_LDE2_3 = new QPushButton(groupBox_3);
        pushButton_LDE2_3->setObjectName(QStringLiteral("pushButton_LDE2_3"));
        pushButton_LDE2_3->setFont(font);
        pushButton_LDE2_3->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_12->addWidget(pushButton_LDE2_3);


        gridLayout->addLayout(horizontalLayout_12, 3, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_6);

        pushButton_LED_ON = new QPushButton(groupBox_3);
        pushButton_LED_ON->setObjectName(QStringLiteral("pushButton_LED_ON"));
        pushButton_LED_ON->setFont(font);
        pushButton_LED_ON->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_7->addWidget(pushButton_LED_ON);

        pushButton_LED_OFF = new QPushButton(groupBox_3);
        pushButton_LED_OFF->setObjectName(QStringLiteral("pushButton_LED_OFF"));
        pushButton_LED_OFF->setFont(font);
        pushButton_LED_OFF->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_7->addWidget(pushButton_LED_OFF);


        gridLayout->addLayout(horizontalLayout_7, 1, 1, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_8);

        pushButton_FAN_Close = new QPushButton(groupBox_3);
        pushButton_FAN_Close->setObjectName(QStringLiteral("pushButton_FAN_Close"));
        pushButton_FAN_Close->setFont(font);
        pushButton_FAN_Close->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_11->addWidget(pushButton_FAN_Close);

        pushButton_FAN1 = new QPushButton(groupBox_3);
        pushButton_FAN1->setObjectName(QStringLiteral("pushButton_FAN1"));
        pushButton_FAN1->setFont(font);
        pushButton_FAN1->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_11->addWidget(pushButton_FAN1);

        pushButton_FAN2 = new QPushButton(groupBox_3);
        pushButton_FAN2->setObjectName(QStringLiteral("pushButton_FAN2"));
        pushButton_FAN2->setFont(font);
        pushButton_FAN2->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_11->addWidget(pushButton_FAN2);

        pushButton_FAN3 = new QPushButton(groupBox_3);
        pushButton_FAN3->setObjectName(QStringLiteral("pushButton_FAN3"));
        pushButton_FAN3->setFont(font);
        pushButton_FAN3->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_11->addWidget(pushButton_FAN3);


        gridLayout->addLayout(horizontalLayout_11, 2, 0, 1, 2);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(82, 25));
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label_15);

        horizontalSlider_LED3_PWM = new QSlider(groupBox_3);
        horizontalSlider_LED3_PWM->setObjectName(QStringLiteral("horizontalSlider_LED3_PWM"));
        horizontalSlider_LED3_PWM->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"border: 0px solid #bbb;\n"
"}\n"
"QSlider::sub-page:horizontal {\n"
"background: rgb(100, 150, 200);\n"
"border-radius: 0px;\n"
"margin-top:8px;\n"
"margin-bottom:8px;\n"
"}\n"
"QSlider::add-page:horizontal {\n"
"background: rgb(255, 255, 255);\n"
"border: 0px solid #777;\n"
"border-radius: 2px;\n"
"margin-top:8px;\n"
"margin-bottom:8px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"background: rgb(100, 150, 200);\n"
"border: 1px solid rgb(0, 66, 199);\n"
"width: 14px;\n"
"height:10px;\n"
"border-radius: 7px;\n"
"margin-top:2px;\n"
"margin-bottom:2px;\n"
"}\n"
"QSlider::handle:horizontal:hover {\n"
"background: rgb(100, 150, 200);\n"
"border: 1px solid rgba(102,102,102,102);\n"
"border-radius: 7px;\n"
"}\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #bbb;\n"
"border-color: #999;\n"
"}\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aa"
                        "a;\n"
"border-radius: 4px;\n"
"}\n"
""));
        horizontalSlider_LED3_PWM->setMaximum(90);
        horizontalSlider_LED3_PWM->setOrientation(Qt::Horizontal);

        horizontalLayout_16->addWidget(horizontalSlider_LED3_PWM);


        gridLayout->addLayout(horizontalLayout_16, 4, 0, 1, 2);


        gridLayout_4->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox_6 = new QGroupBox(Func);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setFont(font);
        groupBox_6->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox_6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        pushButton_weather = new QPushButton(groupBox_6);
        pushButton_weather->setObjectName(QStringLiteral("pushButton_weather"));
        pushButton_weather->setMaximumSize(QSize(108, 16777215));
        pushButton_weather->setFont(font);
        pushButton_weather->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_17->addWidget(pushButton_weather);

        comboBox_weather = new QComboBox(groupBox_6);
        comboBox_weather->setObjectName(QStringLiteral("comboBox_weather"));
        comboBox_weather->setMaximumSize(QSize(108, 16777215));
        comboBox_weather->setFont(font);
        comboBox_weather->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        horizontalLayout_17->addWidget(comboBox_weather);


        verticalLayout_2->addLayout(horizontalLayout_17);

        widget = new QWidget(groupBox_6);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_20 = new QHBoxLayout(widget);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_weather_text = new QLabel(widget);
        label_weather_text->setObjectName(QStringLiteral("label_weather_text"));
        label_weather_text->setFont(font);

        horizontalLayout_20->addWidget(label_weather_text);


        verticalLayout_2->addWidget(widget);


        gridLayout_4->addWidget(groupBox_6, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(Func);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFont(font);
        groupBox_4->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(pushButton, 0, 1, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMaximumSize(QSize(16777215, 20));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_12);

        label_fan = new QLabel(groupBox_4);
        label_fan->setObjectName(QStringLiteral("label_fan"));
        label_fan->setMaximumSize(QSize(16777215, 20));
        label_fan->setFont(font);

        horizontalLayout_13->addWidget(label_fan);


        gridLayout_2->addLayout(horizontalLayout_13, 4, 1, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMaximumSize(QSize(16777215, 20));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(label_14);

        label_beep = new QLabel(groupBox_4);
        label_beep->setObjectName(QStringLiteral("label_beep"));
        label_beep->setMaximumSize(QSize(16777215, 20));
        label_beep->setFont(font);

        horizontalLayout_15->addWidget(label_beep);


        gridLayout_2->addLayout(horizontalLayout_15, 5, 1, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMaximumSize(QSize(16777215, 20));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_13);

        label_led3 = new QLabel(groupBox_4);
        label_led3->setObjectName(QStringLiteral("label_led3"));
        label_led3->setMaximumSize(QSize(16777215, 20));
        label_led3->setFont(font);

        horizontalLayout_14->addWidget(label_led3);


        gridLayout_2->addLayout(horizontalLayout_14, 5, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMaximumSize(QSize(16777215, 20));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_9);

        label_hum = new QLabel(groupBox_4);
        label_hum->setObjectName(QStringLiteral("label_hum"));
        label_hum->setMaximumSize(QSize(16777215, 20));
        label_hum->setFont(font);

        horizontalLayout_9->addWidget(label_hum);


        gridLayout_2->addLayout(horizontalLayout_9, 3, 1, 1, 1);

        widget_temp = new Dial(groupBox_4);
        widget_temp->setObjectName(QStringLiteral("widget_temp"));
        widget_temp->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(widget_temp, 1, 0, 1, 1);

        widget_hum = new Dial(groupBox_4);
        widget_hum->setObjectName(QStringLiteral("widget_hum"));
        widget_hum->setMinimumSize(QSize(120, 120));

        gridLayout_2->addWidget(widget_hum, 1, 1, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(16777215, 20));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_7);

        label_tem = new QLabel(groupBox_4);
        label_tem->setObjectName(QStringLiteral("label_tem"));
        label_tem->setMaximumSize(QSize(16777215, 20));
        label_tem->setFont(font);

        horizontalLayout_8->addWidget(label_tem);


        gridLayout_2->addLayout(horizontalLayout_8, 3, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(16777215, 20));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_11);

        label_light = new QLabel(groupBox_4);
        label_light->setObjectName(QStringLiteral("label_light"));
        label_light->setMaximumSize(QSize(16777215, 20));
        label_light->setFont(font);

        horizontalLayout_10->addWidget(label_light);


        gridLayout_2->addLayout(horizontalLayout_10, 4, 0, 1, 1);

        widget_chart = new QWidget(groupBox_4);
        widget_chart->setObjectName(QStringLiteral("widget_chart"));
        widget_chart->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(widget_chart, 2, 0, 1, 2);


        gridLayout_4->addWidget(groupBox_4, 0, 0, 2, 1);


        verticalLayout_4->addLayout(gridLayout_4);


        retranslateUi(Func);

        QMetaObject::connectSlotsByName(Func);
    } // setupUi

    void retranslateUi(QWidget *Func)
    {
        Func->setWindowTitle(QApplication::translate("Func", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Func", "\346\225\231\345\256\244\350\256\276\345\244\207\347\273\221\345\256\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("Func", "\350\212\257\347\211\207ID", Q_NULLPTR));
        lineEdit_ChipID->setText(QString());
        label_3->setText(QApplication::translate("Func", "\345\244\207  \346\263\250", Q_NULLPTR));
        lineEdit_name->setText(QString());
        pushButton_bind->setText(QApplication::translate("Func", "\347\273\221\345\256\232", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Func", "\351\200\211\346\213\251\346\216\247\345\210\266\347\232\204\346\225\231\345\256\244", Q_NULLPTR));
        label_4->setText(QApplication::translate("Func", "\350\256\276\345\244\207\345\220\215\347\247\260", Q_NULLPTR));
        label->setText(QApplication::translate("Func", "\350\264\246\345\217\267:", Q_NULLPTR));
        label_ID->setText(QApplication::translate("Func", "xxx", Q_NULLPTR));
        label_image->setText(QString());
        groupBox_3->setTitle(QApplication::translate("Func", "\350\256\276\345\244\207\346\223\215\344\275\234", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("Func", "\346\234\272\345\231\250\344\272\272", Q_NULLPTR));
        label_robot->setText(QString());
        pushButton_robot->setText(QApplication::translate("Func", "\346\214\211\344\270\213\350\257\264\350\257\235", Q_NULLPTR));
        label_17->setText(QApplication::translate("Func", "<html><head/><body><p>\346\210\221\346\230\257\344\275\240\347\232\204\346\231\272\350\203\275\347\256\241\345\256\266\357\274\214\344\275\240\345\217\257\344\273\245\345\257\271\346\210\221\350\257\264<img src=\"file:///C:\\WINDOWS\\TEMP\\SGPicFaceTpBq\\18612\\30BF5F8B.png\"/> \357\274\232</p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Noto Sans','Helvetica','Arial','sans-serif','Apple Color Emoji','Segoe UI Emoji'; font-size:14px; color:#c9d1d9; background-color:#1e1e20;\">\342\230\200\357\270\2171\343\200\201&quot;\345\274\200\347\201\257&quot;\357\274\214&quot;\345\205\263\347\201\257&quot;\357\274\214&quot;\347\201\257\344\272\256\344\270\200\347\202\271&quot;\357\274\214&quot;\347\201\257\346\232\227\344\270\200\347\202\271&quot;</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Noto Sans','Helvetica','Arial','sans-serif','Apple Color Emoji','Segoe UI Emoji'; font-size:14px; color:#c9d1d9; background-color:#1e1e20;\">\360\237\203\217"
                        "2\343\200\201&quot;\347\203\255\346\255\273\344\272\206&quot;\357\274\214&quot;\345\205\263\351\243\216\346\211\207&quot;\357\274\214&quot;\345\274\200\351\243\216\346\211\207&quot;</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Noto Sans','Helvetica','Arial','sans-serif','Apple Color Emoji','Segoe UI Emoji'; font-size:14px; color:#c9d1d9; background-color:#1e1e20;\">\360\237\230\2043\343\200\201&quot;\346\212\245\350\255\246&quot;\357\274\214&quot;\345\210\253\345\217\253\344\272\206&quot;</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Noto Sans','Helvetica','Arial','sans-serif','Apple Color Emoji','Segoe UI Emoji'; font-size:14px; color:#c9d1d9; background-color:#1e1e20;\">\360\237\220\2744\343\200\201&quot;\346\237\245\347\234\213\345\244\251\346\260\224&quot;\357\274\214&quot;\345\271\277\345\267\236\345\244\251\346\260\224&quot;\357\274\214&quot;\345\214\227\344\272\254\345\244\251\346\260\224&quot;</span></p></body></html"
                        ">", Q_NULLPTR));
        label_5->setText(QApplication::translate("Func", "\350\255\246\346\212\245\345\231\250", Q_NULLPTR));
        pushButton_ON->setText(QApplication::translate("Func", "\345\274\200", Q_NULLPTR));
        pushButton_OFF->setText(QApplication::translate("Func", "\345\205\263", Q_NULLPTR));
        widget_beep_switch->setStyleSheet(QApplication::translate("Func", "	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;\n"
"	color: rgb(0, 0, 0);", Q_NULLPTR));
        label_10->setText(QApplication::translate("Func", "\346\225\231\345\256\244\345\211\215\347\201\257", Q_NULLPTR));
        pushButton_LED2_close->setText(QApplication::translate("Func", "\345\205\263", Q_NULLPTR));
        pushButton_LED2_1->setText(QApplication::translate("Func", "1\346\214\241", Q_NULLPTR));
        pushButton_LED2_2->setText(QApplication::translate("Func", "2\346\214\241", Q_NULLPTR));
        pushButton_LDE2_3->setText(QApplication::translate("Func", "3\346\214\241", Q_NULLPTR));
        label_6->setText(QApplication::translate("Func", "\351\273\221\346\235\277\347\201\257", Q_NULLPTR));
        pushButton_LED_ON->setText(QApplication::translate("Func", "\345\274\200", Q_NULLPTR));
        pushButton_LED_OFF->setText(QApplication::translate("Func", "\345\205\263", Q_NULLPTR));
        label_8->setText(QApplication::translate("Func", "\351\243\216\346\211\207", Q_NULLPTR));
        pushButton_FAN_Close->setText(QApplication::translate("Func", "\345\205\263", Q_NULLPTR));
        pushButton_FAN1->setText(QApplication::translate("Func", "1\346\241\243", Q_NULLPTR));
        pushButton_FAN2->setText(QApplication::translate("Func", "2\346\241\243", Q_NULLPTR));
        pushButton_FAN3->setText(QApplication::translate("Func", "3\346\241\243", Q_NULLPTR));
        label_15->setText(QApplication::translate("Func", "\346\225\231\345\256\244\345\220\216\347\201\257", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("Func", "\344\273\212\346\227\245\345\244\251\346\260\224", Q_NULLPTR));
        pushButton_weather->setText(QApplication::translate("Func", "\346\233\264\346\226\260\345\244\251\346\260\224", Q_NULLPTR));
        comboBox_weather->clear();
        comboBox_weather->insertItems(0, QStringList()
         << QApplication::translate("Func", "\351\225\277\346\262\231", Q_NULLPTR)
         << QApplication::translate("Func", "\346\267\261\345\234\263", Q_NULLPTR)
         << QApplication::translate("Func", "\345\214\227\344\272\254", Q_NULLPTR)
         << QApplication::translate("Func", "\345\271\277\345\267\236", Q_NULLPTR)
         << QApplication::translate("Func", "\344\270\212\346\265\267", Q_NULLPTR)
        );
        label_weather_text->setText(QApplication::translate("Func", "\345\237\216\345\270\202:\351\225\277\346\262\231  \346\227\245\346\234\237:2023-08-10  \346\230\237\346\234\237:\346\230\237\346\234\237\345\233\233\n"
"\347\231\275\345\244\251\346\270\251\345\272\246:34\346\221\204\346\260\217\345\272\246  \346\231\232\344\270\212\346\270\251\345\272\246:26\346\221\204\346\260\217\345\272\246  \345\244\251\346\260\224:\345\244\232\344\272\221", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("Func", "\345\256\244\345\206\205\347\216\257\345\242\203", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Func", "\346\233\264\346\226\260", Q_NULLPTR));
        label_12->setText(QApplication::translate("Func", "\351\243\216\346\211\207:", Q_NULLPTR));
        label_fan->setText(QString());
        label_14->setText(QApplication::translate("Func", "\346\212\245\350\255\246\345\231\250:", Q_NULLPTR));
        label_beep->setText(QString());
        label_13->setText(QApplication::translate("Func", "LED3:", Q_NULLPTR));
        label_led3->setText(QString());
        label_9->setText(QApplication::translate("Func", "\346\271\277\345\272\246:", Q_NULLPTR));
        label_hum->setText(QString());
        label_7->setText(QApplication::translate("Func", "\346\270\251\345\272\246:", Q_NULLPTR));
        label_tem->setText(QString());
        label_11->setText(QApplication::translate("Func", "\345\205\211\347\205\247:", Q_NULLPTR));
        label_light->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Func: public Ui_Func {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNC_H
