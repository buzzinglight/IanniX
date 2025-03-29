/********************************************************************************
** Form generated from reading UI file 'messagemanagerlogmini.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEMANAGERLOGMINI_H
#define UI_MESSAGEMANAGERLOGMINI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageManagerLogMini
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *enable;
    QLabel *log;

    void setupUi(QWidget *MessageManagerLogMini)
    {
        if (MessageManagerLogMini->objectName().isEmpty())
            MessageManagerLogMini->setObjectName(QString::fromUtf8("MessageManagerLogMini"));
        MessageManagerLogMini->resize(540, 25);
        MessageManagerLogMini->setStyleSheet(QString::fromUtf8("QWidget#log {\n"
"	font: 	10px \"Lucida Console\", \"Monaco\", \"Monospace\";\n"
"	color: 	rgb(160, 160, 160);\n"
"}\n"
""));
        horizontalLayout = new QHBoxLayout(MessageManagerLogMini);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        enable = new QCheckBox(MessageManagerLogMini);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(true);

        horizontalLayout->addWidget(enable);

        log = new QLabel(MessageManagerLogMini);
        log->setObjectName(QString::fromUtf8("log"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(log->sizePolicy().hasHeightForWidth());
        log->setSizePolicy(sizePolicy);
        log->setMinimumSize(QSize(550, 18));
        log->setMaximumSize(QSize(520, 18));

        horizontalLayout->addWidget(log);


        retranslateUi(MessageManagerLogMini);

        QMetaObject::connectSlotsByName(MessageManagerLogMini);
    } // setupUi

    void retranslateUi(QWidget *MessageManagerLogMini)
    {
        MessageManagerLogMini->setWindowTitle(QCoreApplication::translate("MessageManagerLogMini", "Form", nullptr));
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("MessageManagerLogMini", "Instantaneous messages log activation", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        enable->setStatusTip(QCoreApplication::translate("MessageManagerLogMini", "Instantaneous messages log activation|Disable the instantaneous log if you need to save some CPU resources... and enable it if you need log trace!", nullptr));
#endif // QT_CONFIG(statustip)
        enable->setText(QString());
#if QT_CONFIG(tooltip)
        log->setToolTip(QCoreApplication::translate("MessageManagerLogMini", "Instantaneous messages log", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        log->setStatusTip(QCoreApplication::translate("MessageManagerLogMini", "Instantaneous messages log|The instantaneous log displays each 200ms the last sent or received messages. Useful to see quickly if your score is emitting messages!", nullptr));
#endif // QT_CONFIG(statustip)
        log->setText(QCoreApplication::translate("MessageManagerLogMini", "LOG OF SENT/RECEIVED MESSAGES", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageManagerLogMini: public Ui_MessageManagerLogMini {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEMANAGERLOGMINI_H
