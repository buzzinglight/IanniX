/********************************************************************************
** Form generated from reading UI file 'interfacetcp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACETCP_H
#define UI_INTERFACETCP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceTcp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *enable;
    QSpacerItem *horizontalSpacer;
    QPushButton *examples;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QRadioButton *typeRaw;
    QRadioButton *typeXml;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *port;
    QLabel *clients;

    void setupUi(QWidget *InterfaceTcp)
    {
        if (InterfaceTcp->objectName().isEmpty())
            InterfaceTcp->setObjectName(QString::fromUtf8("InterfaceTcp"));
        InterfaceTcp->resize(381, 88);
        verticalLayout = new QVBoxLayout(InterfaceTcp);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        enable = new QCheckBox(InterfaceTcp);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(true);

        horizontalLayout_2->addWidget(enable);

        horizontalSpacer = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        examples = new QPushButton(InterfaceTcp);
        examples->setObjectName(QString::fromUtf8("examples"));
        examples->setMinimumSize(QSize(150, 0));
        examples->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(examples);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(InterfaceTcp);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setMaximumSize(QSize(100, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        typeRaw = new QRadioButton(InterfaceTcp);
        typeRaw->setObjectName(QString::fromUtf8("typeRaw"));
        typeRaw->setChecked(false);

        horizontalLayout_3->addWidget(typeRaw);

        typeXml = new QRadioButton(InterfaceTcp);
        typeXml->setObjectName(QString::fromUtf8("typeXml"));
        typeXml->setChecked(true);

        horizontalLayout_3->addWidget(typeXml);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(InterfaceTcp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(100, 0));
        label->setMaximumSize(QSize(100, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        port = new QSpinBox(InterfaceTcp);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMaximumSize(QSize(60, 16777215));
        port->setMinimum(1024);
        port->setMaximum(65535);

        horizontalLayout->addWidget(port);

        clients = new QLabel(InterfaceTcp);
        clients->setObjectName(QString::fromUtf8("clients"));
        clients->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(clients);


        verticalLayout->addLayout(horizontalLayout);

#if QT_CONFIG(shortcut)
        label_2->setBuddy(port);
        label->setBuddy(port);
        clients->setBuddy(port);
#endif // QT_CONFIG(shortcut)

        retranslateUi(InterfaceTcp);

        QMetaObject::connectSlotsByName(InterfaceTcp);
    } // setupUi

    void retranslateUi(QWidget *InterfaceTcp)
    {
        InterfaceTcp->setWindowTitle(QCoreApplication::translate("InterfaceTcp", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceTcp->setStatusTip(QCoreApplication::translate("InterfaceTcp", "TCP/XML interface|The built in TCP server of IanniX allows you to exchange messages with a reliable network protocol. You may use TCP if you want to receive messages from IanniX over an Internet connexion.\\nMessages are sent in an XML format, fully compatible with software like Adobe Flash. However, unlike the OpenSoundControl protocol, be aware that a TCP connexion will add latency and jitter to your messages.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("InterfaceTcp", "Enables or disables TCP/XML messages and control", nullptr));
#endif // QT_CONFIG(tooltip)
        enable->setText(QCoreApplication::translate("InterfaceTcp", "ENABLE TCP (Flash, hardware\342\200\246)", nullptr));
#if QT_CONFIG(tooltip)
        examples->setToolTip(QCoreApplication::translate("InterfaceTcp", "Opens the folder where you can find examples of IanniX interfacing with software using TCP/XML", nullptr));
#endif // QT_CONFIG(tooltip)
        examples->setText(QCoreApplication::translate("InterfaceTcp", "OPEN EXAMPLES", nullptr));
        label_2->setText(QCoreApplication::translate("InterfaceTcp", "DATA FORMAT", nullptr));
        typeRaw->setText(QCoreApplication::translate("InterfaceTcp", "Raw format", nullptr));
        typeXml->setText(QCoreApplication::translate("InterfaceTcp", "XML format", nullptr));
        label->setText(QCoreApplication::translate("InterfaceTcp", "TCP\n"
"SERVER PORT", nullptr));
#if QT_CONFIG(tooltip)
        port->setToolTip(QCoreApplication::translate("InterfaceTcp", "Changes the port for incoming TCP clients and XML messages", nullptr));
#endif // QT_CONFIG(tooltip)
        clients->setText(QCoreApplication::translate("InterfaceTcp", "No client connected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceTcp: public Ui_InterfaceTcp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACETCP_H
