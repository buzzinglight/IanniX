/********************************************************************************
** Form generated from reading UI file 'uitreeview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UITREEVIEW_H
#define UI_UITREEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "items/uitreeviewwidget.h"

QT_BEGIN_NAMESPACE

class Ui_UiTreeView
{
public:
    QVBoxLayout *verticalLayout;
    UiTreeViewWidget *view;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *actionSave;
    QPushButton *actionDuplicate;
    QPushButton *actionAddRoot;
    QPushButton *actionAdd;
    QPushButton *actionImport;
    QPushButton *actionRemove;

    void setupUi(QWidget *UiTreeView)
    {
        if (UiTreeView->objectName().isEmpty())
            UiTreeView->setObjectName(QString::fromUtf8("UiTreeView"));
        UiTreeView->resize(533, 542);
        UiTreeView->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	min-width:  		20px;\n"
"	min-height: 		20px;\n"
"	max-width:  	20px;\n"
"	max-height: 	20px;\n"
"	width:  				20px;\n"
"	height: 			20px;\n"
"	border-radius: 10px;\n"
"	padding:			0px;\n"
"}\n"
"QPushButton#actionDuplicate, QPushButton#actionAddRoot, QPushButton#actionSave {\n"
"	min-width:  		70px;\n"
"	max-width:  	70px;\n"
"	width:  				70px;\n"
"}"));
        verticalLayout = new QVBoxLayout(UiTreeView);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        view = new UiTreeViewWidget(UiTreeView);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        view->setHeaderItem(__qtreewidgetitem);
        view->setObjectName(QString::fromUtf8("view"));
        view->setEditTriggers(QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        view->setTabKeyNavigation(true);
        view->setDragEnabled(true);
        view->setAlternatingRowColors(true);
        view->setIndentation(0);
        view->setSortingEnabled(true);
        view->setAllColumnsShowFocus(true);
        view->header()->setVisible(false);
        view->header()->setProperty("showSortIndicator", QVariant(true));
        view->header()->setStretchLastSection(false);

        verticalLayout->addWidget(view);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 3, 10, 3);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        actionSave = new QPushButton(UiTreeView);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));

        horizontalLayout->addWidget(actionSave);

        actionDuplicate = new QPushButton(UiTreeView);
        actionDuplicate->setObjectName(QString::fromUtf8("actionDuplicate"));

        horizontalLayout->addWidget(actionDuplicate);

        actionAddRoot = new QPushButton(UiTreeView);
        actionAddRoot->setObjectName(QString::fromUtf8("actionAddRoot"));

        horizontalLayout->addWidget(actionAddRoot);

        actionAdd = new QPushButton(UiTreeView);
        actionAdd->setObjectName(QString::fromUtf8("actionAdd"));

        horizontalLayout->addWidget(actionAdd);

        actionImport = new QPushButton(UiTreeView);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));

        horizontalLayout->addWidget(actionImport);

        actionRemove = new QPushButton(UiTreeView);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));

        horizontalLayout->addWidget(actionRemove);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(UiTreeView);
        QObject::connect(actionAdd, SIGNAL(released()), UiTreeView, SLOT(action()));
        QObject::connect(actionRemove, SIGNAL(released()), UiTreeView, SLOT(action()));
        QObject::connect(actionImport, SIGNAL(released()), UiTreeView, SLOT(action()));
        QObject::connect(actionAddRoot, SIGNAL(released()), UiTreeView, SLOT(action()));
        QObject::connect(view, SIGNAL(doubleClicked(QModelIndex)), UiTreeView, SLOT(action()));
        QObject::connect(actionSave, SIGNAL(released()), UiTreeView, SLOT(action()));
        QObject::connect(actionDuplicate, SIGNAL(released()), UiTreeView, SLOT(action()));

        QMetaObject::connectSlotsByName(UiTreeView);
    } // setupUi

    void retranslateUi(QWidget *UiTreeView)
    {
        UiTreeView->setWindowTitle(QCoreApplication::translate("UiTreeView", "Form", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("UiTreeView", "Save", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave->setText(QCoreApplication::translate("UiTreeView", "SAVE", nullptr));
#if QT_CONFIG(tooltip)
        actionDuplicate->setToolTip(QCoreApplication::translate("UiTreeView", "Duplicate", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDuplicate->setText(QCoreApplication::translate("UiTreeView", "BACKUP", nullptr));
#if QT_CONFIG(tooltip)
        actionAddRoot->setToolTip(QCoreApplication::translate("UiTreeView", "Add a folder", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAddRoot->setText(QCoreApplication::translate("UiTreeView", "NEW FOLDER", nullptr));
#if QT_CONFIG(tooltip)
        actionAdd->setToolTip(QCoreApplication::translate("UiTreeView", "New", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAdd->setText(QCoreApplication::translate("UiTreeView", "+", nullptr));
#if QT_CONFIG(tooltip)
        actionImport->setToolTip(QCoreApplication::translate("UiTreeView", "Import a file", nullptr));
#endif // QT_CONFIG(tooltip)
        actionImport->setText(QCoreApplication::translate("UiTreeView", "+", nullptr));
#if QT_CONFIG(tooltip)
        actionRemove->setToolTip(QCoreApplication::translate("UiTreeView", "Delete", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRemove->setText(QCoreApplication::translate("UiTreeView", "\342\200\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiTreeView: public Ui_UiTreeView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UITREEVIEW_H
