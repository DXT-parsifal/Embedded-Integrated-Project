/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *label_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_ID;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_Pass;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_login;
    QPushButton *pushButton_regiset;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(482, 594);
        Login->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        label_3 = new QLabel(Login);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 70, 341, 131));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(30);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 290, 341, 201));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("Consolas"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(label);

        lineEdit_ID = new QLineEdit(layoutWidget);
        lineEdit_ID->setObjectName(QStringLiteral("lineEdit_ID"));
        QFont font2;
        font2.setPointSize(20);
        lineEdit_ID->setFont(font2);
        lineEdit_ID->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout_2->addWidget(lineEdit_ID);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font3;
        font3.setFamily(QStringLiteral("Consolas"));
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        label_2->setFont(font3);

        horizontalLayout->addWidget(label_2);

        lineEdit_Pass = new QLineEdit(layoutWidget);
        lineEdit_Pass->setObjectName(QStringLiteral("lineEdit_Pass"));
        lineEdit_Pass->setFont(font2);
        lineEdit_Pass->setStyleSheet(QLatin1String("	background-color: rgb(255, 255, 255);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout->addWidget(lineEdit_Pass);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_login = new QPushButton(layoutWidget);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setFont(font2);
        pushButton_login->setStyleSheet(QLatin1String("	background-color: rgb(225, 225, 225);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout_3->addWidget(pushButton_login);

        pushButton_regiset = new QPushButton(layoutWidget);
        pushButton_regiset->setObjectName(QStringLiteral("pushButton_regiset"));
        pushButton_regiset->setFont(font2);
        pushButton_regiset->setStyleSheet(QLatin1String("	background-color: rgb(225, 225, 225);\n"
"	border:2px groove gray;\n"
"	border-radius:10px;\n"
"	padding:2px 4px;\n"
"	border-style: outset;"));

        horizontalLayout_3->addWidget(pushButton_regiset);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", Q_NULLPTR));
        label_3->setText(QApplication::translate("Login", "\347\231\273\345\275\225\347\225\214\351\235\242", Q_NULLPTR));
        label->setText(QApplication::translate("Login", "\350\264\246\345\217\267", Q_NULLPTR));
        lineEdit_ID->setText(QApplication::translate("Login", "511757085", Q_NULLPTR));
        label_2->setText(QApplication::translate("Login", "\345\257\206\347\240\201", Q_NULLPTR));
        lineEdit_Pass->setText(QApplication::translate("Login", "123456", Q_NULLPTR));
        pushButton_login->setText(QApplication::translate("Login", "\347\231\273\345\275\225", Q_NULLPTR));
        pushButton_regiset->setText(QApplication::translate("Login", "\346\263\250\345\206\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
