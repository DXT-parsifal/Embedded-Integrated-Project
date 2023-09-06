/********************************************************************************
** Form generated from reading UI file 'dial.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAL_H
#define UI_DIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dial
{
public:

    void setupUi(QWidget *Dial)
    {
        if (Dial->objectName().isEmpty())
            Dial->setObjectName(QStringLiteral("Dial"));
        Dial->resize(800, 600);

        retranslateUi(Dial);

        QMetaObject::connectSlotsByName(Dial);
    } // setupUi

    void retranslateUi(QWidget *Dial)
    {
        Dial->setWindowTitle(QApplication::translate("Dial", "Dial", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dial: public Ui_Dial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAL_H
