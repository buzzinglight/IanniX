/********************************************************************************
** Form generated from reading UI file 'interfaceserial.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACESERIAL_H
#define UI_INTERFACESERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceSerial
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *enable;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *examples;
    QFormLayout *formLayout;
    QLabel *portLabel;
    QComboBox *portCombo;
    QLabel *baudLabel;
    QComboBox *baudCombo;
    QLabel *bitsLabel;
    QComboBox *bitsCombo;
    QLabel *parityLabel;
    QComboBox *parityCombo;
    QLabel *stopLabel;
    QComboBox *stopCombo;
    QLabel *flowLabel;
    QComboBox *flowCombo;

    void setupUi(QWidget *InterfaceSerial)
    {
        if (InterfaceSerial->objectName().isEmpty())
            InterfaceSerial->setObjectName(QString::fromUtf8("InterfaceSerial"));
        InterfaceSerial->resize(311, 172);
        verticalLayout = new QVBoxLayout(InterfaceSerial);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        enable = new QCheckBox(InterfaceSerial);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(false);

        horizontalLayout_2->addWidget(enable);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        examples = new QPushButton(InterfaceSerial);
        examples->setObjectName(QString::fromUtf8("examples"));
        examples->setMinimumSize(QSize(150, 0));
        examples->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(examples);


        verticalLayout->addLayout(horizontalLayout_2);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(10);
        formLayout->setVerticalSpacing(3);
        portLabel = new QLabel(InterfaceSerial);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setMinimumSize(QSize(100, 0));
        portLabel->setMaximumSize(QSize(100, 16777215));
        portLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, portLabel);

        portCombo = new QComboBox(InterfaceSerial);
        portCombo->setObjectName(QString::fromUtf8("portCombo"));
        portCombo->setMinimumSize(QSize(200, 0));

        formLayout->setWidget(0, QFormLayout::FieldRole, portCombo);

        baudLabel = new QLabel(InterfaceSerial);
        baudLabel->setObjectName(QString::fromUtf8("baudLabel"));
        baudLabel->setMinimumSize(QSize(100, 0));
        baudLabel->setMaximumSize(QSize(100, 16777215));
        baudLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, baudLabel);

        baudCombo = new QComboBox(InterfaceSerial);
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->addItem(QString());
        baudCombo->setObjectName(QString::fromUtf8("baudCombo"));
        baudCombo->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(1, QFormLayout::FieldRole, baudCombo);

        bitsLabel = new QLabel(InterfaceSerial);
        bitsLabel->setObjectName(QString::fromUtf8("bitsLabel"));
        bitsLabel->setMinimumSize(QSize(100, 0));
        bitsLabel->setMaximumSize(QSize(100, 16777215));
        bitsLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, bitsLabel);

        bitsCombo = new QComboBox(InterfaceSerial);
        bitsCombo->addItem(QString());
        bitsCombo->addItem(QString());
        bitsCombo->addItem(QString());
        bitsCombo->addItem(QString());
        bitsCombo->setObjectName(QString::fromUtf8("bitsCombo"));
        bitsCombo->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(2, QFormLayout::FieldRole, bitsCombo);

        parityLabel = new QLabel(InterfaceSerial);
        parityLabel->setObjectName(QString::fromUtf8("parityLabel"));
        parityLabel->setMinimumSize(QSize(100, 0));
        parityLabel->setMaximumSize(QSize(100, 16777215));
        parityLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, parityLabel);

        parityCombo = new QComboBox(InterfaceSerial);
        parityCombo->addItem(QString());
        parityCombo->addItem(QString());
        parityCombo->addItem(QString());
        parityCombo->addItem(QString());
        parityCombo->setObjectName(QString::fromUtf8("parityCombo"));
        parityCombo->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(3, QFormLayout::FieldRole, parityCombo);

        stopLabel = new QLabel(InterfaceSerial);
        stopLabel->setObjectName(QString::fromUtf8("stopLabel"));
        stopLabel->setMinimumSize(QSize(100, 0));
        stopLabel->setMaximumSize(QSize(100, 16777215));
        stopLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, stopLabel);

        stopCombo = new QComboBox(InterfaceSerial);
        stopCombo->addItem(QString());
        stopCombo->addItem(QString());
        stopCombo->setObjectName(QString::fromUtf8("stopCombo"));
        stopCombo->setMinimumSize(QSize(120, 0));

        formLayout->setWidget(4, QFormLayout::FieldRole, stopCombo);

        flowLabel = new QLabel(InterfaceSerial);
        flowLabel->setObjectName(QString::fromUtf8("flowLabel"));
        flowLabel->setMinimumSize(QSize(100, 0));
        flowLabel->setMaximumSize(QSize(100, 16777215));
        flowLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, flowLabel);

        flowCombo = new QComboBox(InterfaceSerial);
        flowCombo->addItem(QString());
        flowCombo->addItem(QString());
        flowCombo->addItem(QString());
        flowCombo->setObjectName(QString::fromUtf8("flowCombo"));
        flowCombo->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(5, QFormLayout::FieldRole, flowCombo);


        verticalLayout->addLayout(formLayout);


        retranslateUi(InterfaceSerial);

        QMetaObject::connectSlotsByName(InterfaceSerial);
    } // setupUi

    void retranslateUi(QWidget *InterfaceSerial)
    {
        InterfaceSerial->setWindowTitle(QCoreApplication::translate("InterfaceSerial", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceSerial->setStatusTip(QCoreApplication::translate("InterfaceSerial", "Serial port interface|IanniX can send and receive messages through a serial port connectivity (UART / RS232). Values are sent in ASCII format, separated by spaces and ended by CR character.\\nThis is totaly compatible with Arduino shields for example.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("InterfaceSerial", "Enables or disables serial port messages and control", nullptr));
#endif // QT_CONFIG(tooltip)
        enable->setText(QCoreApplication::translate("InterfaceSerial", "ENABLE SERIAL PORT", nullptr));
#if QT_CONFIG(tooltip)
        examples->setToolTip(QCoreApplication::translate("InterfaceSerial", "Opens the folder where you can find examples of IanniX interfacing with software using serial port", nullptr));
#endif // QT_CONFIG(tooltip)
        examples->setText(QCoreApplication::translate("InterfaceSerial", "OPEN EXAMPLES", nullptr));
        portLabel->setText(QCoreApplication::translate("InterfaceSerial", "PORT NAME", nullptr));
        baudLabel->setText(QCoreApplication::translate("InterfaceSerial", "BAUD RATE", nullptr));
        baudCombo->setItemText(0, QCoreApplication::translate("InterfaceSerial", "110 bps", nullptr));
        baudCombo->setItemText(1, QCoreApplication::translate("InterfaceSerial", "300 bps", nullptr));
        baudCombo->setItemText(2, QCoreApplication::translate("InterfaceSerial", "600 bps", nullptr));
        baudCombo->setItemText(3, QCoreApplication::translate("InterfaceSerial", "1200 bps", nullptr));
        baudCombo->setItemText(4, QCoreApplication::translate("InterfaceSerial", "2400 bps", nullptr));
        baudCombo->setItemText(5, QCoreApplication::translate("InterfaceSerial", "4800 bps", nullptr));
        baudCombo->setItemText(6, QCoreApplication::translate("InterfaceSerial", "9600 bps", nullptr));
        baudCombo->setItemText(7, QCoreApplication::translate("InterfaceSerial", "19200 bps", nullptr));
        baudCombo->setItemText(8, QCoreApplication::translate("InterfaceSerial", "38400 bps", nullptr));
        baudCombo->setItemText(9, QCoreApplication::translate("InterfaceSerial", "57600 bps", nullptr));
        baudCombo->setItemText(10, QCoreApplication::translate("InterfaceSerial", "115200 bps", nullptr));

        bitsLabel->setText(QCoreApplication::translate("InterfaceSerial", "DATA BITS", nullptr));
        bitsCombo->setItemText(0, QCoreApplication::translate("InterfaceSerial", "5 bits", nullptr));
        bitsCombo->setItemText(1, QCoreApplication::translate("InterfaceSerial", "6 bits", nullptr));
        bitsCombo->setItemText(2, QCoreApplication::translate("InterfaceSerial", "7 bits", nullptr));
        bitsCombo->setItemText(3, QCoreApplication::translate("InterfaceSerial", "8 bits", nullptr));

        parityLabel->setText(QCoreApplication::translate("InterfaceSerial", "PARITY", nullptr));
        parityCombo->setItemText(0, QCoreApplication::translate("InterfaceSerial", "No parity", nullptr));
        parityCombo->setItemText(1, QCoreApplication::translate("InterfaceSerial", "Odd parity", nullptr));
        parityCombo->setItemText(2, QCoreApplication::translate("InterfaceSerial", "Even parity", nullptr));
        parityCombo->setItemText(3, QCoreApplication::translate("InterfaceSerial", "Space parity", nullptr));

        stopLabel->setText(QCoreApplication::translate("InterfaceSerial", "STOP BITS", nullptr));
        stopCombo->setItemText(0, QCoreApplication::translate("InterfaceSerial", "1 bit", nullptr));
        stopCombo->setItemText(1, QCoreApplication::translate("InterfaceSerial", "2 bits", nullptr));

        flowLabel->setText(QCoreApplication::translate("InterfaceSerial", "FLOW CONTROL", nullptr));
        flowCombo->setItemText(0, QCoreApplication::translate("InterfaceSerial", "No flow control", nullptr));
        flowCombo->setItemText(1, QCoreApplication::translate("InterfaceSerial", "Hardware flow control", nullptr));
        flowCombo->setItemText(2, QCoreApplication::translate("InterfaceSerial", "XON/XOFF flow control", nullptr));

    } // retranslateUi

};

namespace Ui {
    class InterfaceSerial: public Ui_InterfaceSerial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACESERIAL_H
