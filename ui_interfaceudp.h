/********************************************************************************
** Form generated from reading UI file 'interfaceudp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEUDP_H
#define UI_INTERFACEUDP_H

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

class Ui_InterfaceUdp
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *enable;
    QSpacerItem *horizontalSpacer;
    QPushButton *examples;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *port;
    QSpacerItem *horizontalSpacer_26;

    void setupUi(QWidget *InterfaceUdp)
    {
        if (InterfaceUdp->objectName().isEmpty())
            InterfaceUdp->setObjectName(QString::fromUtf8("InterfaceUdp"));
        InterfaceUdp->resize(332, 66);
        verticalLayout = new QVBoxLayout(InterfaceUdp);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        enable = new QCheckBox(InterfaceUdp);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(true);

        horizontalLayout_2->addWidget(enable);

        horizontalSpacer = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        examples = new QPushButton(InterfaceUdp);
        examples->setObjectName(QString::fromUtf8("examples"));
        examples->setMinimumSize(QSize(150, 0));
        examples->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(examples);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(InterfaceUdp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(100, 0));
        label->setMaximumSize(QSize(100, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        port = new QSpinBox(InterfaceUdp);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMaximumSize(QSize(60, 16777215));
        port->setMinimum(1024);
        port->setMaximum(65535);

        horizontalLayout->addWidget(port);

        horizontalSpacer_26 = new QSpacerItem(37, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_26);


        verticalLayout->addLayout(horizontalLayout);

#if QT_CONFIG(shortcut)
        label->setBuddy(port);
#endif // QT_CONFIG(shortcut)

        retranslateUi(InterfaceUdp);

        QMetaObject::connectSlotsByName(InterfaceUdp);
    } // setupUi

    void retranslateUi(QWidget *InterfaceUdp)
    {
        InterfaceUdp->setWindowTitle(QCoreApplication::translate("InterfaceUdp", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceUdp->setStatusTip(QCoreApplication::translate("InterfaceUdp", "Raw UDP interface|Raw UDP (or FUDI) is a very simple protocol based on UDP. Values are written in ASCII, separated by spaces and ended by a semicolon, in a UDP packet.\\nPureData is compatible with this protocol, but you can also implement it very quickly in your own applications if you don't want to use OpenSoundControl.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("InterfaceUdp", "Enables or disables raw UDP messages and control", nullptr));
#endif // QT_CONFIG(tooltip)
        enable->setText(QCoreApplication::translate("InterfaceUdp", "ENABLE RAW UDP (FUDI)", nullptr));
#if QT_CONFIG(tooltip)
        examples->setToolTip(QCoreApplication::translate("InterfaceUdp", "Opens the folder where you can find examples of IanniX interfacing with software using raw UDP", nullptr));
#endif // QT_CONFIG(tooltip)
        examples->setText(QCoreApplication::translate("InterfaceUdp", "OPEN EXAMPLES", nullptr));
        label->setText(QCoreApplication::translate("InterfaceUdp", "RAW UDP IN PORT\n"
"(FUDI protocol)", nullptr));
#if QT_CONFIG(tooltip)
        port->setToolTip(QCoreApplication::translate("InterfaceUdp", "Changes the port for incoming raw UDP messages", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class InterfaceUdp: public Ui_InterfaceUdp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEUDP_H
