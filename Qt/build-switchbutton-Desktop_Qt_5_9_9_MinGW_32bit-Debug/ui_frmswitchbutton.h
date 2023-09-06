/********************************************************************************
** Form generated from reading UI file 'frmswitchbutton.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSWITCHBUTTON_H
#define UI_FRMSWITCHBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "switchbutton.h"

QT_BEGIN_NAMESPACE

class Ui_frmSwitchButton
{
public:
    SwitchButton *switchButton11;
    SwitchButton *switchButton12;
    SwitchButton *switchButton13;
    SwitchButton *switchButton14;
    SwitchButton *switchButton23;
    SwitchButton *switchButton22;
    SwitchButton *switchButton21;
    SwitchButton *switchButton24;
    SwitchButton *switchButton31;
    SwitchButton *switchButton33;
    SwitchButton *switchButton34;
    SwitchButton *switchButton32;

    void setupUi(QWidget *frmSwitchButton)
    {
        if (frmSwitchButton->objectName().isEmpty())
            frmSwitchButton->setObjectName(QStringLiteral("frmSwitchButton"));
        frmSwitchButton->resize(500, 300);
        switchButton11 = new SwitchButton(frmSwitchButton);
        switchButton11->setObjectName(QStringLiteral("switchButton11"));
        switchButton11->setGeometry(QRect(30, 20, 71, 31));
        switchButton12 = new SwitchButton(frmSwitchButton);
        switchButton12->setObjectName(QStringLiteral("switchButton12"));
        switchButton12->setGeometry(QRect(30, 70, 71, 31));
        switchButton13 = new SwitchButton(frmSwitchButton);
        switchButton13->setObjectName(QStringLiteral("switchButton13"));
        switchButton13->setGeometry(QRect(30, 120, 71, 31));
        switchButton14 = new SwitchButton(frmSwitchButton);
        switchButton14->setObjectName(QStringLiteral("switchButton14"));
        switchButton14->setGeometry(QRect(30, 170, 71, 31));
        switchButton23 = new SwitchButton(frmSwitchButton);
        switchButton23->setObjectName(QStringLiteral("switchButton23"));
        switchButton23->setGeometry(QRect(120, 120, 71, 31));
        switchButton22 = new SwitchButton(frmSwitchButton);
        switchButton22->setObjectName(QStringLiteral("switchButton22"));
        switchButton22->setGeometry(QRect(120, 70, 71, 31));
        switchButton21 = new SwitchButton(frmSwitchButton);
        switchButton21->setObjectName(QStringLiteral("switchButton21"));
        switchButton21->setGeometry(QRect(120, 20, 71, 31));
        switchButton24 = new SwitchButton(frmSwitchButton);
        switchButton24->setObjectName(QStringLiteral("switchButton24"));
        switchButton24->setGeometry(QRect(120, 170, 71, 31));
        switchButton31 = new SwitchButton(frmSwitchButton);
        switchButton31->setObjectName(QStringLiteral("switchButton31"));
        switchButton31->setGeometry(QRect(210, 20, 81, 31));
        switchButton33 = new SwitchButton(frmSwitchButton);
        switchButton33->setObjectName(QStringLiteral("switchButton33"));
        switchButton33->setGeometry(QRect(210, 120, 81, 31));
        switchButton34 = new SwitchButton(frmSwitchButton);
        switchButton34->setObjectName(QStringLiteral("switchButton34"));
        switchButton34->setGeometry(QRect(210, 170, 81, 31));
        switchButton32 = new SwitchButton(frmSwitchButton);
        switchButton32->setObjectName(QStringLiteral("switchButton32"));
        switchButton32->setGeometry(QRect(210, 70, 81, 31));

        retranslateUi(frmSwitchButton);

        QMetaObject::connectSlotsByName(frmSwitchButton);
    } // setupUi

    void retranslateUi(QWidget *frmSwitchButton)
    {
        frmSwitchButton->setWindowTitle(QApplication::translate("frmSwitchButton", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmSwitchButton: public Ui_frmSwitchButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSWITCHBUTTON_H
