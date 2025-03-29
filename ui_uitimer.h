/********************************************************************************
** Form generated from reading UI file 'uitimer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UITIMER_H
#define UI_UITIMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiTimer
{
public:
    QLabel *time;

    void setupUi(QWidget *UiTimer)
    {
        if (UiTimer->objectName().isEmpty())
            UiTimer->setObjectName(QString::fromUtf8("UiTimer"));
        UiTimer->resize(582, 112);
        UiTimer->setStyleSheet(QString::fromUtf8("QWidget#UiTimer {\n"
"	background-color: 	black;\n"
"}\n"
"QLabel#time {\n"
"	font: 						12px \"Lucida Sans\", \"Lucida Grande\", \"Lucida Sans Unicode\", \"Lucida\";\n"
"	color: 						rgb(0, 187, 255);\n"
"}"));
        time = new QLabel(UiTimer);
        time->setObjectName(QString::fromUtf8("time"));
        time->setGeometry(QRect(0, 0, 570, 118));
        time->setStyleSheet(QString::fromUtf8("font-size: 100px;"));
        time->setAlignment(Qt::AlignCenter);

        retranslateUi(UiTimer);

        QMetaObject::connectSlotsByName(UiTimer);
    } // setupUi

    void retranslateUi(QWidget *UiTimer)
    {
        UiTimer->setWindowTitle(QCoreApplication::translate("UiTimer", "IanniX - Timer", nullptr));
        time->setText(QCoreApplication::translate("UiTimer", "00:00:00.000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiTimer: public Ui_UiTimer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UITIMER_H
