/********************************************************************************
** Form generated from reading UI file 'regist.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGIST_H
#define UI_REGIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_regist
{
public:
    QLabel *label;
    QPushButton *pushButton_registe;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_ID;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_name;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_pass;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_email;

    void setupUi(QWidget *regist)
    {
        if (regist->objectName().isEmpty())
            regist->setObjectName(QStringLiteral("regist"));
        regist->resize(472, 498);
        regist->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 127);"));
        label = new QLabel(regist);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 20, 301, 171));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        pushButton_registe = new QPushButton(regist);
        pushButton_registe->setObjectName(QStringLiteral("pushButton_registe"));
        pushButton_registe->setGeometry(QRect(170, 400, 121, 41));
        QFont font1;
        font1.setPointSize(15);
        pushButton_registe->setFont(font1);
        pushButton_registe->setStyleSheet(QLatin1String("	background-color: rgb(85, 255, 127);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));
        widget = new QWidget(regist);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(100, 200, 261, 151));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font2;
        font2.setPointSize(12);
        label_2->setFont(font2);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        lineEdit_ID = new QLineEdit(widget);
        lineEdit_ID->setObjectName(QStringLiteral("lineEdit_ID"));
        lineEdit_ID->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout->addWidget(lineEdit_ID);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout_2->addWidget(lineEdit_name);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font2);

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        lineEdit_pass = new QLineEdit(widget);
        lineEdit_pass->setObjectName(QStringLiteral("lineEdit_pass"));
        lineEdit_pass->setMinimumSize(QSize(0, 0));
        lineEdit_pass->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout_3->addWidget(lineEdit_pass);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);
        label_5->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        lineEdit_email = new QLineEdit(widget);
        lineEdit_email->setObjectName(QStringLiteral("lineEdit_email"));
        lineEdit_email->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout_4->addWidget(lineEdit_email);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(regist);

        QMetaObject::connectSlotsByName(regist);
    } // setupUi

    void retranslateUi(QWidget *regist)
    {
        regist->setWindowTitle(QApplication::translate("regist", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("regist", "\346\263\250\345\206\214\347\225\214\351\235\242", Q_NULLPTR));
        pushButton_registe->setText(QApplication::translate("regist", "\346\263\250\345\206\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("regist", "\350\264\246\346\210\267ID", Q_NULLPTR));
        label_3->setText(QApplication::translate("regist", "\350\264\246\346\210\267\345\220\215", Q_NULLPTR));
        label_4->setText(QApplication::translate("regist", "\345\257\206\347\240\201", Q_NULLPTR));
        label_5->setText(QApplication::translate("regist", "\351\202\256\347\256\261", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class regist: public Ui_regist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGIST_H
