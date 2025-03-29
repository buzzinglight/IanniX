/********************************************************************************
** Form generated from reading UI file 'messagemanagerlog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEMANAGERLOG_H
#define UI_MESSAGEMANAGERLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageManagerLog
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QWidget *layoutWidget23;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *logSendCopy;
    QPushButton *logSendClear;
    QPlainTextEdit *logSend;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *logReceiveCopy;
    QPushButton *logReceiveClear;
    QPlainTextEdit *logReceive;

    void setupUi(QWidget *MessageManagerLog)
    {
        if (MessageManagerLog->objectName().isEmpty())
            MessageManagerLog->setObjectName(QString::fromUtf8("MessageManagerLog"));
        MessageManagerLog->resize(433, 354);
        MessageManagerLog->setStyleSheet(QString::fromUtf8("QWidget#logSend, QWidget#logReceive {\n"
"	font: 						10px \"Lucida Console\", \"Monaco\", \"Monospace\";\n"
"	background-color: 	rgb(242, 241, 237);\n"
"	color:						black;\n"
"}\n"
"QPushButton  {\n"
"	min-width:  		14px;\n"
"	min-height: 		14px;\n"
"	max-width:  	14px;\n"
"	max-height: 	14px;\n"
"	width:  				14px;\n"
"	height: 			14px;\n"
"	padding:			0px;\n"
"	border-radius: 7px;\n"
"}\n"
"QPushButton#logSendCopy, QPushButton#logReceiveCopy {\n"
"	min-width:  		40px;\n"
"	max-width:  	40px;\n"
"	width:  				40px;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(MessageManagerLog);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(MessageManagerLog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget23 = new QWidget(splitter);
        layoutWidget23->setObjectName(QString::fromUtf8("layoutWidget23"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget23);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(layoutWidget23);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        logSendCopy = new QPushButton(layoutWidget23);
        logSendCopy->setObjectName(QString::fromUtf8("logSendCopy"));

        horizontalLayout->addWidget(logSendCopy);

        logSendClear = new QPushButton(layoutWidget23);
        logSendClear->setObjectName(QString::fromUtf8("logSendClear"));

        horizontalLayout->addWidget(logSendClear);


        verticalLayout_2->addLayout(horizontalLayout);

        logSend = new QPlainTextEdit(layoutWidget23);
        logSend->setObjectName(QString::fromUtf8("logSend"));
        logSend->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        logSend->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        logSend->setUndoRedoEnabled(false);
        logSend->setLineWrapMode(QPlainTextEdit::NoWrap);
        logSend->setReadOnly(true);
        logSend->setTabStopWidth(30);

        verticalLayout_2->addWidget(logSend);

        splitter->addWidget(layoutWidget23);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        logReceiveCopy = new QPushButton(layoutWidget);
        logReceiveCopy->setObjectName(QString::fromUtf8("logReceiveCopy"));

        horizontalLayout_2->addWidget(logReceiveCopy);

        logReceiveClear = new QPushButton(layoutWidget);
        logReceiveClear->setObjectName(QString::fromUtf8("logReceiveClear"));

        horizontalLayout_2->addWidget(logReceiveClear);


        verticalLayout->addLayout(horizontalLayout_2);

        logReceive = new QPlainTextEdit(layoutWidget);
        logReceive->setObjectName(QString::fromUtf8("logReceive"));
        logReceive->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        logReceive->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        logReceive->setUndoRedoEnabled(false);
        logReceive->setLineWrapMode(QPlainTextEdit::NoWrap);
        logReceive->setReadOnly(true);
        logReceive->setTabStopWidth(30);

        verticalLayout->addWidget(logReceive);

        splitter->addWidget(layoutWidget);

        verticalLayout_3->addWidget(splitter);


        retranslateUi(MessageManagerLog);
        QObject::connect(logSendClear, SIGNAL(released()), logSend, SLOT(clear()));
        QObject::connect(logReceiveClear, SIGNAL(released()), logReceive, SLOT(clear()));
        QObject::connect(logSendCopy, SIGNAL(released()), MessageManagerLog, SLOT(action()));
        QObject::connect(logReceiveCopy, SIGNAL(released()), MessageManagerLog, SLOT(action()));

        QMetaObject::connectSlotsByName(MessageManagerLog);
    } // setupUi

    void retranslateUi(QWidget *MessageManagerLog)
    {
        MessageManagerLog->setWindowTitle(QCoreApplication::translate("MessageManagerLog", "Form", nullptr));
#if QT_CONFIG(statustip)
        MessageManagerLog->setStatusTip(QCoreApplication::translate("MessageManagerLog", "Full messages log|This tab allows you to see all the sent and received messages. Useful to see exactly what's happening and to understand IanniX inputs/outputs.\\n Be careful, this log is *very* CPU intensive and the score accuracy may decrease if this tab is displayed during playback.", nullptr));
#endif // QT_CONFIG(statustip)
        label_3->setText(QCoreApplication::translate("MessageManagerLog", "SENT MESSAGES (only when this tab is visible)", nullptr));
#if QT_CONFIG(tooltip)
        logSendCopy->setToolTip(QCoreApplication::translate("MessageManagerLog", "Copies sent messages log to clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        logSendCopy->setText(QCoreApplication::translate("MessageManagerLog", "Copy", nullptr));
#if QT_CONFIG(tooltip)
        logSendClear->setToolTip(QCoreApplication::translate("MessageManagerLog", "Clears sent messages log", nullptr));
#endif // QT_CONFIG(tooltip)
        logSendClear->setText(QCoreApplication::translate("MessageManagerLog", "X", nullptr));
        logSend->setPlainText(QString());
        label->setText(QCoreApplication::translate("MessageManagerLog", "RECEIVED MESSAGES (only when this tab is visible)", nullptr));
#if QT_CONFIG(tooltip)
        logReceiveCopy->setToolTip(QCoreApplication::translate("MessageManagerLog", "Copies received messages log to clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        logReceiveCopy->setText(QCoreApplication::translate("MessageManagerLog", "Copy", nullptr));
#if QT_CONFIG(tooltip)
        logReceiveClear->setToolTip(QCoreApplication::translate("MessageManagerLog", "Clears received messages log", nullptr));
#endif // QT_CONFIG(tooltip)
        logReceiveClear->setText(QCoreApplication::translate("MessageManagerLog", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageManagerLog: public Ui_MessageManagerLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEMANAGERLOG_H
