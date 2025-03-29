/********************************************************************************
** Form generated from reading UI file 'extoscpatternask.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTOSCPATTERNASK_H
#define UI_EXTOSCPATTERNASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gui/uihelp.h"

QT_BEGIN_NAMESPACE

class Ui_ExtOscPatternAsk
{
public:
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabs;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *removeButton;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    UiHelp *help;

    void setupUi(QDialog *ExtOscPatternAsk)
    {
        if (ExtOscPatternAsk->objectName().isEmpty())
            ExtOscPatternAsk->setObjectName(QString::fromUtf8("ExtOscPatternAsk"));
        ExtOscPatternAsk->resize(800, 505);
        verticalLayout_2 = new QVBoxLayout(ExtOscPatternAsk);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        splitter = new QSplitter(ExtOscPatternAsk);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 5);
        tabs = new QTabWidget(layoutWidget);
        tabs->setObjectName(QString::fromUtf8("tabs"));
        tabs->setMinimumSize(QSize(775, 20));

        verticalLayout->addWidget(tabs);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addButton = new QPushButton(layoutWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setMinimumSize(QSize(170, 22));
        addButton->setMaximumSize(QSize(170, 27));
        addButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(addButton);

        removeButton = new QPushButton(layoutWidget);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setMinimumSize(QSize(170, 22));
        removeButton->setMaximumSize(QSize(170, 27));
        removeButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(removeButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setFocusPolicy(Qt::NoFocus);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget);
        help = new UiHelp(splitter);
        help->setObjectName(QString::fromUtf8("help"));
        help->setFocusPolicy(Qt::NoFocus);
        splitter->addWidget(help);

        verticalLayout_2->addWidget(splitter);


        retranslateUi(ExtOscPatternAsk);
        QObject::connect(buttonBox, SIGNAL(accepted()), ExtOscPatternAsk, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ExtOscPatternAsk, SLOT(reject()));
        QObject::connect(addButton, SIGNAL(released()), ExtOscPatternAsk, SLOT(actionAddMessage()));
        QObject::connect(removeButton, SIGNAL(released()), ExtOscPatternAsk, SLOT(actionRemoveMessage()));

        tabs->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ExtOscPatternAsk);
    } // setupUi

    void retranslateUi(QDialog *ExtOscPatternAsk)
    {
        ExtOscPatternAsk->setWindowTitle(QCoreApplication::translate("ExtOscPatternAsk", "IanniX \342\200\224 Message editor", nullptr));
#if QT_CONFIG(tooltip)
        addButton->setToolTip(QCoreApplication::translate("ExtOscPatternAsk", "Adds a new message", nullptr));
#endif // QT_CONFIG(tooltip)
        addButton->setText(QCoreApplication::translate("ExtOscPatternAsk", "ADD A NEW MESSAGE", nullptr));
#if QT_CONFIG(tooltip)
        removeButton->setToolTip(QCoreApplication::translate("ExtOscPatternAsk", "Removes current message", nullptr));
#endif // QT_CONFIG(tooltip)
        removeButton->setText(QCoreApplication::translate("ExtOscPatternAsk", "REMOVE CURRENT MESSAGE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExtOscPatternAsk: public Ui_ExtOscPatternAsk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTOSCPATTERNASK_H
