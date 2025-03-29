/********************************************************************************
** Form generated from reading UI file 'interfacemidi.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEMIDI_H
#define UI_INTERFACEMIDI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceMidi
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *enable;
    QSpacerItem *horizontalSpacer;
    QPushButton *examples;
    QHBoxLayout *horizontalLayout_34;
    QLabel *aliasLabel;
    QComboBox *aliasPort;
    QSpacerItem *horizontalSpacer_22;
    QHBoxLayout *horizontalLayout_33;
    QLabel *syncLabel;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *syncTransportIn;
    QCheckBox *syncTransportOut;
    QSpinBox *bpm;
    QSpacerItem *horizontalSpacer_21;
    QWidget *midiJack;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QPushButton *download;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *InterfaceMidi)
    {
        if (InterfaceMidi->objectName().isEmpty())
            InterfaceMidi->setObjectName(QString::fromUtf8("InterfaceMidi"));
        InterfaceMidi->resize(375, 196);
        verticalLayout = new QVBoxLayout(InterfaceMidi);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        enable = new QCheckBox(InterfaceMidi);
        enable->setObjectName(QString::fromUtf8("enable"));
        enable->setChecked(true);

        horizontalLayout->addWidget(enable);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        examples = new QPushButton(InterfaceMidi);
        examples->setObjectName(QString::fromUtf8("examples"));
        examples->setMinimumSize(QSize(150, 0));
        examples->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(examples);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(10);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        aliasLabel = new QLabel(InterfaceMidi);
        aliasLabel->setObjectName(QString::fromUtf8("aliasLabel"));
        aliasLabel->setMinimumSize(QSize(100, 0));
        aliasLabel->setMaximumSize(QSize(100, 16777215));
        aliasLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_34->addWidget(aliasLabel);

        aliasPort = new QComboBox(InterfaceMidi);
        aliasPort->setObjectName(QString::fromUtf8("aliasPort"));
        aliasPort->setMinimumSize(QSize(200, 20));
        aliasPort->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_34->addWidget(aliasPort);

        horizontalSpacer_22 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_22);


        verticalLayout->addLayout(horizontalLayout_34);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(10);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        syncLabel = new QLabel(InterfaceMidi);
        syncLabel->setObjectName(QString::fromUtf8("syncLabel"));
        syncLabel->setMinimumSize(QSize(100, 0));
        syncLabel->setMaximumSize(QSize(100, 16777215));
        syncLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_33->addWidget(syncLabel);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(5);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        syncTransportIn = new QCheckBox(InterfaceMidi);
        syncTransportIn->setObjectName(QString::fromUtf8("syncTransportIn"));
        syncTransportIn->setChecked(true);

        verticalLayout_12->addWidget(syncTransportIn);

        syncTransportOut = new QCheckBox(InterfaceMidi);
        syncTransportOut->setObjectName(QString::fromUtf8("syncTransportOut"));

        verticalLayout_12->addWidget(syncTransportOut);

        bpm = new QSpinBox(InterfaceMidi);
        bpm->setObjectName(QString::fromUtf8("bpm"));
        bpm->setMinimumSize(QSize(100, 0));
        bpm->setMaximumSize(QSize(100, 16777215));
        bpm->setMinimum(1);
        bpm->setMaximum(65535);

        verticalLayout_12->addWidget(bpm);


        horizontalLayout_33->addLayout(verticalLayout_12);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_21);


        verticalLayout->addLayout(horizontalLayout_33);

        midiJack = new QWidget(InterfaceMidi);
        midiJack->setObjectName(QString::fromUtf8("midiJack"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(midiJack->sizePolicy().hasHeightForWidth());
        midiJack->setSizePolicy(sizePolicy);
        midiJack->setMinimumSize(QSize(0, 50));
        horizontalLayout_2 = new QHBoxLayout(midiJack);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(midiJack);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        download = new QPushButton(midiJack);
        download->setObjectName(QString::fromUtf8("download"));
        download->setMinimumSize(QSize(150, 0));
        download->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(download);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(midiJack);

#if QT_CONFIG(shortcut)
        aliasLabel->setBuddy(aliasPort);
        syncLabel->setBuddy(bpm);
#endif // QT_CONFIG(shortcut)

        retranslateUi(InterfaceMidi);

        QMetaObject::connectSlotsByName(InterfaceMidi);
    } // setupUi

    void retranslateUi(QWidget *InterfaceMidi)
    {
        InterfaceMidi->setWindowTitle(QCoreApplication::translate("InterfaceMidi", "Form", nullptr));
#if QT_CONFIG(statustip)
        InterfaceMidi->setStatusTip(QCoreApplication::translate("InterfaceMidi", "MIDI Interface|If you cannot use OpenSoundControl in your creative application, you can use the built in MIDI support of IanniX.\\nOn Mac OS X, a new virtual MIDI device will be available; you just have to enable it in the settings of your software.\\nIanniX is able to send notes-on/off, control changes, pitchbend... but it is not as simple to control IanniX with a MIDI surface control, we strongly recommend to use OpenSoundControl for that.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        enable->setToolTip(QCoreApplication::translate("InterfaceMidi", "Enables or disables MIDI messages", nullptr));
#endif // QT_CONFIG(tooltip)
        enable->setText(QCoreApplication::translate("InterfaceMidi", "ENABLE MIDI", nullptr));
#if QT_CONFIG(tooltip)
        examples->setToolTip(QCoreApplication::translate("InterfaceMidi", "Opens the folder where you can find examples of IanniX interfacing with software using a MIDI connection", nullptr));
#endif // QT_CONFIG(tooltip)
        examples->setText(QCoreApplication::translate("InterfaceMidi", "OPEN EXAMPLES", nullptr));
        aliasLabel->setText(QCoreApplication::translate("InterfaceMidi", "DEFAULT MIDI OUT\n"
"(ALIAS MIDI_OUT)", nullptr));
#if QT_CONFIG(tooltip)
        aliasPort->setToolTip(QCoreApplication::translate("InterfaceMidi", "Changes the default MIDI device for all outgoing MIDI messages", nullptr));
#endif // QT_CONFIG(tooltip)
        syncLabel->setText(QCoreApplication::translate("InterfaceMidi", "SEQUENCER\n"
"SYNCHRONIZATION", nullptr));
#if QT_CONFIG(tooltip)
        syncTransportIn->setToolTip(QCoreApplication::translate("InterfaceMidi", "Check this option if you want to sync transport (play, pause, stop, rewind, song position) from another sequencer", nullptr));
#endif // QT_CONFIG(tooltip)
        syncTransportIn->setText(QCoreApplication::translate("InterfaceMidi", "SYNC TRANSPORT IN", nullptr));
#if QT_CONFIG(tooltip)
        syncTransportOut->setToolTip(QCoreApplication::translate("InterfaceMidi", "Check this option if you want to sync transport (play, pause, stop, rewind, song position) to another sequencer", nullptr));
#endif // QT_CONFIG(tooltip)
        syncTransportOut->setText(QCoreApplication::translate("InterfaceMidi", "SYNC TRANSPORT OUT", nullptr));
#if QT_CONFIG(tooltip)
        bpm->setToolTip(QCoreApplication::translate("InterfaceMidi", "Changes the BPM of the score (used by clock synchronization)", nullptr));
#endif // QT_CONFIG(tooltip)
        bpm->setSuffix(QString());
        bpm->setPrefix(QCoreApplication::translate("InterfaceMidi", "BPM @ ", nullptr));
        label->setText(QCoreApplication::translate("InterfaceMidi", "You may need a virtual\n"
"MIDI jack to connect IanniX\n"
"with other MIDI software", nullptr));
#if QT_CONFIG(tooltip)
        download->setToolTip(QCoreApplication::translate("InterfaceMidi", "Downloads LoopBe1", nullptr));
#endif // QT_CONFIG(tooltip)
        download->setText(QCoreApplication::translate("InterfaceMidi", "DOWNLOAD LOOPBE1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceMidi: public Ui_InterfaceMidi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEMIDI_H
