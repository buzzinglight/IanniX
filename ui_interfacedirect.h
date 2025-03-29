/********************************************************************************
** Form generated from reading UI file 'interfacedirect.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEDIRECT_H
#define UI_INTERFACEDIRECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceDirect
{
public:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *enable;
    QSpacerItem *horizontalSpacer_28;

    void setupUi(QWidget *InterfaceDirect)
    {
        if (InterfaceDirect->objectName().isEmpty())
            InterfaceDirect->setObjectName(QString::fromUtf8("InterfaceDirect"));
        InterfaceDirect->resize(226, 32);
        horizontalLayout = new QHBoxLayout(InterfaceDirect);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        enable = new QCheckBox(InterfaceDirect);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(true);

        horizontalLayout_2->addWidget(enable);

        horizontalSpacer_28 = new QSpacerItem(141, 11, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_28);


        horizontalLayout->addLayout(horizontalLayout_2);


        retranslateUi(InterfaceDirect);

        QMetaObject::connectSlotsByName(InterfaceDirect);
    } // setupUi

    void retranslateUi(QWidget *InterfaceDirect)
    {
        InterfaceDirect->setWindowTitle(QCoreApplication::translate("InterfaceDirect", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceDirect->setStatusTip(QCoreApplication::translate("InterfaceDirect", "Recursive Interface|You've understood that IanniX can send messages to other software in order to control parameters. But imagine if you loop the output of IanniX on its input... Messages will be directly re-interpreted by IanniX, creating a recursive score.\\nBut you can also use recursivity for very simple use cases: for example, a trigger that rewind the score, a cursor that moves the camera point of view...", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("InterfaceDirect", "Enables or disables recursive messages and control", nullptr));
#endif // QT_CONFIG(tooltip)
        enable->setText(QCoreApplication::translate("InterfaceDirect", "ENABLE RECURSIVITY (direct://)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceDirect: public Ui_InterfaceDirect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEDIRECT_H
