/********************************************************************************
** Form generated from reading UI file 'uihelp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIHELP_H
#define UI_UIHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiHelp
{
public:
    QHBoxLayout *horizontalLayout;
    QTextBrowser *html;

    void setupUi(QWidget *UiHelp)
    {
        if (UiHelp->objectName().isEmpty())
            UiHelp->setObjectName(QString::fromUtf8("UiHelp"));
        UiHelp->resize(530, 305);
        horizontalLayout = new QHBoxLayout(UiHelp);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        html = new QTextBrowser(UiHelp);
        html->setObjectName(QString::fromUtf8("html"));
        html->setFocusPolicy(Qt::NoFocus);
        html->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        html->setOpenLinks(false);

        horizontalLayout->addWidget(html);


        retranslateUi(UiHelp);
        QObject::connect(html, SIGNAL(anchorClicked(QUrl)), UiHelp, SLOT(linkClicked(QUrl)));

        QMetaObject::connectSlotsByName(UiHelp);
    } // setupUi

    void retranslateUi(QWidget *UiHelp)
    {
        UiHelp->setWindowTitle(QCoreApplication::translate("UiHelp", "IanniX Helper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiHelp: public Ui_UiHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIHELP_H
