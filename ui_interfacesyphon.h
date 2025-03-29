/********************************************************************************
** Form generated from reading UI file 'interfacesyphon.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACESYPHON_H
#define UI_INTERFACESYPHON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceSyphon
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *serverEnable;
    QCheckBox *clientEnable;

    void setupUi(QWidget *InterfaceSyphon)
    {
        if (InterfaceSyphon->objectName().isEmpty())
            InterfaceSyphon->setObjectName(QString::fromUtf8("InterfaceSyphon"));
        InterfaceSyphon->resize(173, 37);
        verticalLayout = new QVBoxLayout(InterfaceSyphon);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        serverEnable = new QCheckBox(InterfaceSyphon);
        serverEnable->setObjectName(QString::fromUtf8("serverEnable"));

        verticalLayout->addWidget(serverEnable);

        clientEnable = new QCheckBox(InterfaceSyphon);
        clientEnable->setObjectName(QString::fromUtf8("clientEnable"));

        verticalLayout->addWidget(clientEnable);


        retranslateUi(InterfaceSyphon);

        QMetaObject::connectSlotsByName(InterfaceSyphon);
    } // setupUi

    void retranslateUi(QWidget *InterfaceSyphon)
    {
        InterfaceSyphon->setWindowTitle(QCoreApplication::translate("InterfaceSyphon", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceSyphon->setStatusTip(QCoreApplication::translate("InterfaceSyphon", "Syphon Interface|IanniX can output its score video flow through Syphon. With this functionnality, you can for example use the score as an element of your video installation or performance (video mapping, VJ-ing...).", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        serverEnable->setToolTip(QCoreApplication::translate("InterfaceSyphon", "Enables or disables score rendering output through Syphon", nullptr));
#endif // QT_CONFIG(tooltip)
        serverEnable->setText(QCoreApplication::translate("InterfaceSyphon", "ENABLE SYPHON OUT", nullptr));
#if QT_CONFIG(tooltip)
        clientEnable->setToolTip(QCoreApplication::translate("InterfaceSyphon", "Enables or disables score rendering output through Syphon", nullptr));
#endif // QT_CONFIG(tooltip)
        clientEnable->setText(QCoreApplication::translate("InterfaceSyphon", "ENABLE SYPHON IN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceSyphon: public Ui_InterfaceSyphon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACESYPHON_H
