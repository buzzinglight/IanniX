/********************************************************************************
** Form generated from reading UI file 'uieditor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIEDITOR_H
#define UI_UIEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "gui/qjsedit/jsedit.h"
#include "gui/uihelp.h"

QT_BEGIN_NAMESPACE

class Ui_UiEditor
{
public:
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionRefreshCode;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter_2;
    JSEdit *jsEditor;
    UiHelp *help;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UiEditor)
    {
        if (UiEditor->objectName().isEmpty())
            UiEditor->setObjectName(QString::fromUtf8("UiEditor"));
        UiEditor->resize(650, 580);
        UiEditor->setStyleSheet(QString::fromUtf8("QStatusBar {\n"
"	background-color: 	rgb(226, 0, 0);\n"
"	color	: 						white;\n"
"}"));
        actionSave = new QAction(UiEditor);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionClose = new QAction(UiEditor);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionRefreshCode = new QAction(UiEditor);
        actionRefreshCode->setObjectName(QString::fromUtf8("actionRefreshCode"));
        centralwidget = new QWidget(UiEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        jsEditor = new JSEdit(splitter_2);
        jsEditor->setObjectName(QString::fromUtf8("jsEditor"));
        splitter_2->addWidget(jsEditor);
        help = new UiHelp(splitter_2);
        help->setObjectName(QString::fromUtf8("help"));
        splitter_2->addWidget(help);

        horizontalLayout->addWidget(splitter_2);

        UiEditor->setCentralWidget(centralwidget);
        toolBar = new QToolBar(UiEditor);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        UiEditor->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(UiEditor);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        UiEditor->setStatusBar(statusBar);

        toolBar->addAction(actionSave);
        toolBar->addAction(actionRefreshCode);
        toolBar->addAction(actionClose);

        retranslateUi(UiEditor);
        QObject::connect(jsEditor, SIGNAL(cursorPositionChanged()), UiEditor, SLOT(cursorChanged()));

        QMetaObject::connectSlotsByName(UiEditor);
    } // setupUi

    void retranslateUi(QMainWindow *UiEditor)
    {
        UiEditor->setWindowTitle(QCoreApplication::translate("UiEditor", "IanniX \342\200\224 Script Editor", nullptr));
        actionSave->setText(QCoreApplication::translate("UiEditor", "Save and refresh score", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("UiEditor", "Save and update score", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("UiEditor", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose->setText(QCoreApplication::translate("UiEditor", "Close window", nullptr));
#if QT_CONFIG(shortcut)
        actionClose->setShortcut(QCoreApplication::translate("UiEditor", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRefreshCode->setText(QCoreApplication::translate("UiEditor", "Refresh code", nullptr));
#if QT_CONFIG(tooltip)
        actionRefreshCode->setToolTip(QCoreApplication::translate("UiEditor", "Refresh code according to actions made through GUI", nullptr));
#endif // QT_CONFIG(tooltip)
        jsEditor->setPlainText(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("UiEditor", "IanniX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiEditor: public Ui_UiEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIEDITOR_H
