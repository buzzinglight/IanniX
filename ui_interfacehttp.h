/********************************************************************************
** Form generated from reading UI file 'interfacehttp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEHTTP_H
#define UI_INTERFACEHTTP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceHttp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *enable;
    QSpacerItem *horizontalSpacer_28;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *port;
    QSpacerItem *horizontalSpacer;
    QPushButton *examples;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelWebSockets;
    QSpinBox *portWebSockets;
    QLabel *clientsWebSockets;

    void setupUi(QWidget *InterfaceHttp)
    {
        if (InterfaceHttp->objectName().isEmpty())
            InterfaceHttp->setObjectName(QString::fromUtf8("InterfaceHttp"));
        InterfaceHttp->resize(340, 100);
        verticalLayout = new QVBoxLayout(InterfaceHttp);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        enable = new QCheckBox(InterfaceHttp);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(true);

        horizontalLayout_2->addWidget(enable);

        horizontalSpacer_28 = new QSpacerItem(141, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_28);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(InterfaceHttp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(100, 0));
        label->setMaximumSize(QSize(100, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        port = new QSpinBox(InterfaceHttp);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMaximumSize(QSize(60, 16777215));
        port->setMinimum(1024);
        port->setMaximum(65535);

        horizontalLayout->addWidget(port);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        examples = new QPushButton(InterfaceHttp);
        examples->setObjectName(QString::fromUtf8("examples"));
        examples->setMinimumSize(QSize(150, 0));
        examples->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(examples);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelWebSockets = new QLabel(InterfaceHttp);
        labelWebSockets->setObjectName(QString::fromUtf8("labelWebSockets"));
        labelWebSockets->setMinimumSize(QSize(100, 0));
        labelWebSockets->setMaximumSize(QSize(100, 16777215));
        labelWebSockets->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(labelWebSockets);

        portWebSockets = new QSpinBox(InterfaceHttp);
        portWebSockets->setObjectName(QString::fromUtf8("portWebSockets"));
        portWebSockets->setMaximumSize(QSize(60, 16777215));
        portWebSockets->setMinimum(1024);
        portWebSockets->setMaximum(65535);

        horizontalLayout_3->addWidget(portWebSockets);

        clientsWebSockets = new QLabel(InterfaceHttp);
        clientsWebSockets->setObjectName(QString::fromUtf8("clientsWebSockets"));
        clientsWebSockets->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(clientsWebSockets);


        verticalLayout->addLayout(horizontalLayout_3);

#if QT_CONFIG(shortcut)
        label->setBuddy(port);
        labelWebSockets->setBuddy(port);
#endif // QT_CONFIG(shortcut)

        retranslateUi(InterfaceHttp);

        QMetaObject::connectSlotsByName(InterfaceHttp);
    } // setupUi

    void retranslateUi(QWidget *InterfaceHttp)
    {
        InterfaceHttp->setWindowTitle(QCoreApplication::translate("InterfaceHttp", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceHttp->setStatusTip(QCoreApplication::translate("InterfaceHttp", "HTTP Interface|IanniX built in HTTP server allows you to control IanniX from a webpage. Open the specific URL and you'll see a basic example of remote control through your webbrowser.\\nYou can also control IanniX with GET messages, have a look at the example source code!", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("InterfaceHttp", "Enables or disables HTTP messages and control", nullptr));
#endif // QT_CONFIG(tooltip)
        enable->setText(QCoreApplication::translate("InterfaceHttp", "ENABLE WEB", nullptr));
        label->setText(QCoreApplication::translate("InterfaceHttp", "HTTP\n"
"SERVER PORT", nullptr));
#if QT_CONFIG(tooltip)
        port->setToolTip(QCoreApplication::translate("InterfaceHttp", "Changes the port for incoming HTTP messages and web page interface", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        examples->setToolTip(QCoreApplication::translate("InterfaceHttp", "Opens a specific URL in your web browser allowing you to control IanniX remotely", nullptr));
#endif // QT_CONFIG(tooltip)
        examples->setText(QCoreApplication::translate("InterfaceHttp", "OPEN URL", nullptr));
        labelWebSockets->setText(QCoreApplication::translate("InterfaceHttp", "WEBSOCKETS\n"
"SERVER PORT", nullptr));
#if QT_CONFIG(tooltip)
        portWebSockets->setToolTip(QCoreApplication::translate("InterfaceHttp", "Changes the port for incoming websockets connections", nullptr));
#endif // QT_CONFIG(tooltip)
        clientsWebSockets->setText(QCoreApplication::translate("InterfaceHttp", "No websocket connected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceHttp: public Ui_InterfaceHttp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEHTTP_H
