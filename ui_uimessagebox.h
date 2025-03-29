/********************************************************************************
** Form generated from reading UI file 'uimessagebox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIMESSAGEBOX_H
#define UI_UIMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiMessageBox
{
public:
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *choices;
    QWidget *page;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *spinLabel;
    QDoubleSpinBox *spinSpin;
    QSpacerItem *horizontalSpacer_6;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *spinpPicture;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *spinpLabel;
    QDoubleSpinBox *spinpSpin;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *checkSmooth;
    QCheckBox *checkTrigger;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *messageLabel;
    QWidget *page_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QLabel *textLabel;
    QLineEdit *textEdit;
    QSpacerItem *horizontalSpacer_10;
    QWidget *page_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *updatePicture;
    QSpacerItem *horizontalSpacer_4;
    QLabel *updateLabel;
    QPlainTextEdit *updatePlain;
    QLabel *updateLabel2;
    QDialogButtonBox *messageButtons;

    void setupUi(QDialog *UiMessageBox)
    {
        if (UiMessageBox->objectName().isEmpty())
            UiMessageBox->setObjectName(QString::fromUtf8("UiMessageBox"));
        UiMessageBox->resize(339, 204);
        UiMessageBox->setModal(true);
        verticalLayout_4 = new QVBoxLayout(UiMessageBox);
        verticalLayout_4->setSpacing(12);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(12, 12, 12, 12);
        choices = new QStackedWidget(UiMessageBox);
        choices->setObjectName(QString::fromUtf8("choices"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout_2 = new QHBoxLayout(page);
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        spinLabel = new QLabel(page);
        spinLabel->setObjectName(QString::fromUtf8("spinLabel"));
        spinLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(spinLabel);

        spinSpin = new QDoubleSpinBox(page);
        spinSpin->setObjectName(QString::fromUtf8("spinSpin"));
        spinSpin->setMinimumSize(QSize(0, 30));
        spinSpin->setMaximumSize(QSize(16777215, 24));
        spinSpin->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(spinSpin);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        choices->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_3 = new QVBoxLayout(page_3);
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        spinpPicture = new QLabel(page_3);
        spinpPicture->setObjectName(QString::fromUtf8("spinpPicture"));
        spinpPicture->setScaledContents(true);
        spinpPicture->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(spinpPicture);

        horizontalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(15);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        spinpLabel = new QLabel(page_3);
        spinpLabel->setObjectName(QString::fromUtf8("spinpLabel"));

        horizontalLayout_4->addWidget(spinpLabel);

        spinpSpin = new QDoubleSpinBox(page_3);
        spinpSpin->setObjectName(QString::fromUtf8("spinpSpin"));
        spinpSpin->setMinimumSize(QSize(0, 30));
        spinpSpin->setMaximumSize(QSize(16777215, 24));
        spinpSpin->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(spinpSpin);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_4);

        checkSmooth = new QCheckBox(page_3);
        checkSmooth->setObjectName(QString::fromUtf8("checkSmooth"));
        checkSmooth->setChecked(true);

        verticalLayout_3->addWidget(checkSmooth);

        checkTrigger = new QCheckBox(page_3);
        checkTrigger->setObjectName(QString::fromUtf8("checkTrigger"));

        verticalLayout_3->addWidget(checkTrigger);

        choices->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        messageLabel = new QLabel(page_2);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(messageLabel);

        choices->addWidget(page_2);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        horizontalLayout_3 = new QHBoxLayout(page_4);
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        textLabel = new QLabel(page_4);
        textLabel->setObjectName(QString::fromUtf8("textLabel"));
        textLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(textLabel);

        textEdit = new QLineEdit(page_4);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMinimumSize(QSize(100, 30));
        textEdit->setMaximumSize(QSize(16777215, 24));
        textEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(textEdit);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);

        choices->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        verticalLayout = new QVBoxLayout(page_5);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        updatePicture = new QLabel(page_5);
        updatePicture->setObjectName(QString::fromUtf8("updatePicture"));

        horizontalLayout_6->addWidget(updatePicture);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        updateLabel = new QLabel(page_5);
        updateLabel->setObjectName(QString::fromUtf8("updateLabel"));

        verticalLayout->addWidget(updateLabel);

        updatePlain = new QPlainTextEdit(page_5);
        updatePlain->setObjectName(QString::fromUtf8("updatePlain"));
        updatePlain->setFocusPolicy(Qt::NoFocus);
        updatePlain->setReadOnly(true);

        verticalLayout->addWidget(updatePlain);

        updateLabel2 = new QLabel(page_5);
        updateLabel2->setObjectName(QString::fromUtf8("updateLabel2"));

        verticalLayout->addWidget(updateLabel2);

        choices->addWidget(page_5);

        verticalLayout_4->addWidget(choices);

        messageButtons = new QDialogButtonBox(UiMessageBox);
        messageButtons->setObjectName(QString::fromUtf8("messageButtons"));
        messageButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(messageButtons);

#if QT_CONFIG(shortcut)
        spinpLabel->setBuddy(spinpSpin);
        textLabel->setBuddy(textEdit);
        updateLabel->setBuddy(updatePlain);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(spinSpin, spinpSpin);
        QWidget::setTabOrder(spinpSpin, textEdit);
        QWidget::setTabOrder(textEdit, updatePlain);
        QWidget::setTabOrder(updatePlain, messageButtons);

        retranslateUi(UiMessageBox);
        QObject::connect(messageButtons, SIGNAL(accepted()), UiMessageBox, SLOT(accept()));
        QObject::connect(messageButtons, SIGNAL(rejected()), UiMessageBox, SLOT(reject()));

        choices->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(UiMessageBox);
    } // setupUi

    void retranslateUi(QDialog *UiMessageBox)
    {
        UiMessageBox->setWindowTitle(QCoreApplication::translate("UiMessageBox", "IanniX", nullptr));
        spinLabel->setText(QCoreApplication::translate("UiMessageBox", "ENTER A VALUE FOR", nullptr));
        spinpPicture->setText(QCoreApplication::translate("UiMessageBox", "PICTURE", nullptr));
        spinpLabel->setText(QCoreApplication::translate("UiMessageBox", "ENTER A VALUE FOR", nullptr));
        checkSmooth->setText(QCoreApplication::translate("UiMessageBox", "Make a smooth curve", nullptr));
        checkTrigger->setText(QCoreApplication::translate("UiMessageBox", "Generate triggers instead of resampling curve", nullptr));
        messageLabel->setText(QCoreApplication::translate("UiMessageBox", "ENTER A VALUE FOR", nullptr));
        textLabel->setText(QCoreApplication::translate("UiMessageBox", "ENTER A VALUE FOR", nullptr));
        updatePicture->setText(QCoreApplication::translate("UiMessageBox", "PICTURE", nullptr));
        updateLabel->setText(QCoreApplication::translate("UiMessageBox", "Title of popup", nullptr));
        updateLabel2->setText(QCoreApplication::translate("UiMessageBox", "Question", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiMessageBox: public Ui_UiMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIMESSAGEBOX_H
