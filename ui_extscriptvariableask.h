/********************************************************************************
** Form generated from reading UI file 'extscriptvariableask.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTSCRIPTVARIABLEASK_H
#define UI_EXTSCRIPTVARIABLEASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExtScriptVariableAsk
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *scriptTitle;
    QTreeWidget *variablesList;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExtScriptVariableAsk)
    {
        if (ExtScriptVariableAsk->objectName().isEmpty())
            ExtScriptVariableAsk->setObjectName(QString::fromUtf8("ExtScriptVariableAsk"));
        ExtScriptVariableAsk->resize(300, 340);
        verticalLayout = new QVBoxLayout(ExtScriptVariableAsk);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scriptTitle = new QLabel(ExtScriptVariableAsk);
        scriptTitle->setObjectName(QString::fromUtf8("scriptTitle"));

        verticalLayout->addWidget(scriptTitle);

        variablesList = new QTreeWidget(ExtScriptVariableAsk);
        variablesList->setObjectName(QString::fromUtf8("variablesList"));
        variablesList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        variablesList->setAlternatingRowColors(true);

        verticalLayout->addWidget(variablesList);

        buttonBox = new QDialogButtonBox(ExtScriptVariableAsk);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#if QT_CONFIG(shortcut)
        scriptTitle->setBuddy(variablesList);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(variablesList, buttonBox);

        retranslateUi(ExtScriptVariableAsk);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExtScriptVariableAsk, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExtScriptVariableAsk, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExtScriptVariableAsk);
    } // setupUi

    void retranslateUi(QDialog *ExtScriptVariableAsk)
    {
        ExtScriptVariableAsk->setWindowTitle(QCoreApplication::translate("ExtScriptVariableAsk", "IanniX", nullptr));
        scriptTitle->setText(QCoreApplication::translate("ExtScriptVariableAsk", "PLEASE ENTER VALUES TO LAUNCH SCRIPT:", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = variablesList->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ExtScriptVariableAsk", "VALUE", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ExtScriptVariableAsk", "VARIABLE", nullptr));
#if QT_CONFIG(tooltip)
        variablesList->setToolTip(QCoreApplication::translate("ExtScriptVariableAsk", "Lists all the editable variables of the script", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class ExtScriptVariableAsk: public Ui_ExtScriptVariableAsk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTSCRIPTVARIABLEASK_H
