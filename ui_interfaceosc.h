/********************************************************************************
** Form generated from reading UI file 'interfaceosc.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEOSC_H
#define UI_INTERFACEOSC_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceOsc
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *enable;
    QSpacerItem *horizontalSpacer_27;
    QPushButton *examples;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *port;
    QPushButton *bonjourPortIn;
    QSpacerItem *horizontalSpacer_25;
    QHBoxLayout *horizontalLayout_2;
    QLabel *aliasLabel;
    QLineEdit *aliasIp;
    QSpinBox *aliasPort;
    QPushButton *bonjour;
    QSpacerItem *horizontalSpacer_26;
    QHBoxLayout *horizontalLayout_39;
    QLabel *bundleLabel;
    QLineEdit *bundleIp;
    QSpinBox *bundlePort;
    QPushButton *bonjourBundle;
    QSpacerItem *horizontalSpacer_29;

    void setupUi(QWidget *InterfaceOsc)
    {
        if (InterfaceOsc->objectName().isEmpty())
            InterfaceOsc->setObjectName(QString::fromUtf8("InterfaceOsc"));
        InterfaceOsc->resize(320, 157);
        verticalLayout = new QVBoxLayout(InterfaceOsc);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        enable = new QCheckBox(InterfaceOsc);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(true);

        horizontalLayout_3->addWidget(enable);

        horizontalSpacer_27 = new QSpacerItem(146, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_27);

        examples = new QPushButton(InterfaceOsc);
        examples->setObjectName(QString::fromUtf8("examples"));
        examples->setMinimumSize(QSize(150, 0));
        examples->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_3->addWidget(examples);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(InterfaceOsc);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(100, 0));
        label->setMaximumSize(QSize(100, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        port = new QSpinBox(InterfaceOsc);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMaximumSize(QSize(60, 16777215));
        port->setMinimum(1024);
        port->setMaximum(65535);
        port->setValue(1024);

        horizontalLayout->addWidget(port);

        bonjourPortIn = new QPushButton(InterfaceOsc);
        bonjourPortIn->setObjectName(QString::fromUtf8("bonjourPortIn"));
        bonjourPortIn->setMinimumSize(QSize(30, 25));
        bonjourPortIn->setMaximumSize(QSize(30, 25));
        bonjourPortIn->setContextMenuPolicy(Qt::CustomContextMenu);
        bonjourPortIn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/actions/res_icon_bonjour.png"), QSize(), QIcon::Normal, QIcon::Off);
        bonjourPortIn->setIcon(icon);

        horizontalLayout->addWidget(bonjourPortIn);

        horizontalSpacer_25 = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_25);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        aliasLabel = new QLabel(InterfaceOsc);
        aliasLabel->setObjectName(QString::fromUtf8("aliasLabel"));
        aliasLabel->setMinimumSize(QSize(100, 0));
        aliasLabel->setMaximumSize(QSize(100, 16777215));
        aliasLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(aliasLabel);

        aliasIp = new QLineEdit(InterfaceOsc);
        aliasIp->setObjectName(QString::fromUtf8("aliasIp"));
        aliasIp->setMinimumSize(QSize(100, 0));
        aliasIp->setMaximumSize(QSize(100, 16777215));
        aliasIp->setStyleSheet(QString::fromUtf8(""));
        aliasIp->setText(QString::fromUtf8(""));
        aliasIp->setMaxLength(15);

        horizontalLayout_2->addWidget(aliasIp);

        aliasPort = new QSpinBox(InterfaceOsc);
        aliasPort->setObjectName(QString::fromUtf8("aliasPort"));
        aliasPort->setMaximumSize(QSize(60, 16777215));
        aliasPort->setMinimum(1024);
        aliasPort->setMaximum(65535);

        horizontalLayout_2->addWidget(aliasPort);

        bonjour = new QPushButton(InterfaceOsc);
        bonjour->setObjectName(QString::fromUtf8("bonjour"));
        bonjour->setMinimumSize(QSize(30, 25));
        bonjour->setMaximumSize(QSize(30, 25));
        bonjour->setContextMenuPolicy(Qt::CustomContextMenu);
        bonjour->setStyleSheet(QString::fromUtf8(""));
        bonjour->setIcon(icon);

        horizontalLayout_2->addWidget(bonjour);

        horizontalSpacer_26 = new QSpacerItem(37, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_26);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(10);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        bundleLabel = new QLabel(InterfaceOsc);
        bundleLabel->setObjectName(QString::fromUtf8("bundleLabel"));
        bundleLabel->setMinimumSize(QSize(100, 0));
        bundleLabel->setMaximumSize(QSize(100, 16777215));
        bundleLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_39->addWidget(bundleLabel);

        bundleIp = new QLineEdit(InterfaceOsc);
        bundleIp->setObjectName(QString::fromUtf8("bundleIp"));
        bundleIp->setMinimumSize(QSize(100, 0));
        bundleIp->setMaximumSize(QSize(100, 20));
        bundleIp->setStyleSheet(QString::fromUtf8("margin-top: 0px;"));
        bundleIp->setText(QString::fromUtf8(""));
        bundleIp->setMaxLength(15);

        horizontalLayout_39->addWidget(bundleIp);

        bundlePort = new QSpinBox(InterfaceOsc);
        bundlePort->setObjectName(QString::fromUtf8("bundlePort"));
        bundlePort->setMaximumSize(QSize(60, 16777215));
        bundlePort->setMinimum(1024);
        bundlePort->setMaximum(65535);

        horizontalLayout_39->addWidget(bundlePort);

        bonjourBundle = new QPushButton(InterfaceOsc);
        bonjourBundle->setObjectName(QString::fromUtf8("bonjourBundle"));
        bonjourBundle->setMinimumSize(QSize(30, 25));
        bonjourBundle->setMaximumSize(QSize(30, 25));
        bonjourBundle->setContextMenuPolicy(Qt::CustomContextMenu);
        bonjourBundle->setStyleSheet(QString::fromUtf8(""));
        bonjourBundle->setIcon(icon);

        horizontalLayout_39->addWidget(bonjourBundle);

        horizontalSpacer_29 = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_29);


        verticalLayout->addLayout(horizontalLayout_39);

#if QT_CONFIG(shortcut)
        label->setBuddy(port);
        aliasLabel->setBuddy(aliasIp);
        bundleLabel->setBuddy(bundleIp);
#endif // QT_CONFIG(shortcut)

        retranslateUi(InterfaceOsc);

        QMetaObject::connectSlotsByName(InterfaceOsc);
    } // setupUi

    void retranslateUi(QWidget *InterfaceOsc)
    {
        InterfaceOsc->setWindowTitle(QCoreApplication::translate("InterfaceOsc", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceOsc->setStatusTip(QCoreApplication::translate("InterfaceOsc", "Open Sound Control Interface|OpenSoundControl is a very versatile protocol allowing IanniX to exchange messages with other software. We strongly recommend you to use this protocol instead of MIDI (MIDI resolution is 7bits, OpenSoundControl is 32bits).\\nA lot of creative software implement this protocol, like PureData, SuperCollider, MaxMSP...", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("InterfaceOsc", "Enables or disables OpenSoundControl messages and control", nullptr));
#endif // QT_CONFIG(tooltip)
        enable->setText(QCoreApplication::translate("InterfaceOsc", "ENABLE OSC", nullptr));
#if QT_CONFIG(tooltip)
        examples->setToolTip(QCoreApplication::translate("InterfaceOsc", "Opens the folder where you can find examples of IanniX interfacing with software using OpenSoundControl", nullptr));
#endif // QT_CONFIG(tooltip)
        examples->setText(QCoreApplication::translate("InterfaceOsc", "OPEN EXAMPLES", nullptr));
        label->setText(QCoreApplication::translate("InterfaceOsc", "OSC IN PORT", nullptr));
#if QT_CONFIG(tooltip)
        port->setToolTip(QCoreApplication::translate("InterfaceOsc", "Changes the port for incoming OpenSoundControl messages", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bonjourPortIn->setToolTip(QCoreApplication::translate("InterfaceOsc", "Displays a list of applications with their OSC port", nullptr));
#endif // QT_CONFIG(tooltip)
        bonjourPortIn->setText(QString());
        aliasLabel->setText(QCoreApplication::translate("InterfaceOsc", "DEFAULT IP\n"
"(ALIAS IP_OUT)", nullptr));
#if QT_CONFIG(tooltip)
        aliasIp->setToolTip(QCoreApplication::translate("InterfaceOsc", "Changes the default IP address for all outgoing IP messages", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        aliasPort->setToolTip(QCoreApplication::translate("InterfaceOsc", "All the messages matching this IP + port will be packed in an OpenSoundControl bundle", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bonjour->setToolTip(QCoreApplication::translate("InterfaceOsc", "Displays a list of applications with their OSC port", nullptr));
#endif // QT_CONFIG(tooltip)
        bonjour->setText(QString());
        bundleLabel->setText(QCoreApplication::translate("InterfaceOsc", "MAKE OSC\n"
"BUNDLE ON", nullptr));
#if QT_CONFIG(tooltip)
        bundleIp->setToolTip(QCoreApplication::translate("InterfaceOsc", "All the messages matching this IP + port will be packed in an OpenSoundControl bundle", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bundlePort->setToolTip(QCoreApplication::translate("InterfaceOsc", "All the messages matching this IP + port will be packed in an OpenSoundControl bundle", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bonjourBundle->setToolTip(QCoreApplication::translate("InterfaceOsc", "Displays a list of applications with their OSC port", nullptr));
#endif // QT_CONFIG(tooltip)
        bonjourBundle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceOsc: public Ui_InterfaceOsc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEOSC_H
