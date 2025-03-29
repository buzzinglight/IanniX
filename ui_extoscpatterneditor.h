/********************************************************************************
** Form generated from reading UI file 'extoscpatterneditor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTOSCPATTERNEDITOR_H
#define UI_EXTOSCPATTERNEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "interfaces/extoscpatterneditor.h"

QT_BEGIN_NAMESPACE

class Ui_ExtOscPatternEditor
{
public:
    QHBoxLayout *horizontalLayout_2;
    QFrame *global;
    QVBoxLayout *verticalLayout_3;
    QComboBox *templates;
    QHBoxLayout *horizontalLayout_7;
    QPlainTextEditWithFocus *patternEdit;
    QVBoxLayout *verticalLayout_2;
    QPushButton *patternClear;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *patternLearn;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *protocolLabel;
    QComboBox *protocolCombo;
    QHBoxLayout *horizontalLayout;
    QLabel *hostOSCLabel;
    QComboBox *hostIpCombo;
    QSpacerItem *horizontalSpacer;
    QLabel *portLabel;
    QComboBox *portCombo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *addressOSCLabel;
    QComboBox *addressOscCombo;
    QHBoxLayout *horizontalLayout_4;
    QLabel *hostMIDILabel;
    QComboBox *hostMidiCombo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *addressMIDILabel;
    QComboBox *addressMidiCombo;
    QHBoxLayout *horizontalLayout_8;
    QLabel *argument1Label;
    QComboBoxWithFocus *argument1Combo;
    QPushButton *argument1Clear;
    QHBoxLayout *horizontalLayout_12;
    QLabel *argument2Label;
    QComboBoxWithFocus *argument2Combo;
    QPushButton *argument2Clear;
    QHBoxLayout *horizontalLayout_11;
    QLabel *argument3Label;
    QComboBoxWithFocus *argument3Combo;
    QPushButton *argument3Clear;
    QHBoxLayout *horizontalLayout_10;
    QLabel *argument4Label;
    QComboBoxWithFocus *argument4Combo;
    QPushButton *argument4Clear;
    QHBoxLayout *horizontalLayout_9;
    QLabel *argument5Label;
    QComboBoxWithFocus *argument5Combo;
    QPushButton *argument5Clear;
    QHBoxLayout *horizontalLayout_5;
    QLabel *argument6Label;
    QComboBoxWithFocus *argument6Combo;
    QPushButton *argument6Clear;
    QHBoxLayout *horizontalLayout_14;
    QLabel *argument7Label;
    QComboBoxWithFocus *argument7Combo;
    QPushButton *argument7Clear;
    QHBoxLayout *horizontalLayout_15;
    QLabel *argument8Label;
    QComboBoxWithFocus *argument8Combo;
    QPushButton *argument8Clear;
    QHBoxLayout *horizontalLayout_16;
    QLabel *argument9Label;
    QComboBoxWithFocus *argument9Combo;
    QPushButton *argument9Clear;
    QHBoxLayout *horizontalLayout_17;
    QLabel *argument10Label;
    QComboBoxWithFocus *argument10Combo;
    QPushButton *argument10Clear;

    void setupUi(QWidget *ExtOscPatternEditor)
    {
        if (ExtOscPatternEditor->objectName().isEmpty())
            ExtOscPatternEditor->setObjectName(QString::fromUtf8("ExtOscPatternEditor"));
        ExtOscPatternEditor->resize(775, 430);
        ExtOscPatternEditor->setMinimumSize(QSize(775, 430));
        ExtOscPatternEditor->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	font: 						10px \"Museo Sans\", \"Museo Sans 500\", \"Arial\";\n"
"	margin: 					0px;\n"
"	padding: 					0px;\n"
"}\n"
"QLabel {\n"
"	font: 						9px \"Museo Sans\", \"Museo Sans 500\", \"Arial\";\n"
"	color: 						rgb(20, 20, 20);\n"
"}\n"
"QLineEdit {\n"
"	background: 			transparent;\n"
"	border: 					0px solid black;\n"
"}\n"
"\n"
"QFrame#global {\n"
"	background-color:	rgb(242, 241, 237);\n"
"}\n"
"QPlainTextEdit#patternEdit {\n"
"	font: 11px \"Lucida Console\", \"Monaco\", \"Monospace\";\n"
"}\n"
"\n"
"\n"
"QPlainTextEdit, QComboBox {\n"
"	min-height: 				20px;\n"
"	color: 						black;\n"
"	border: 					0px solid black;\n"
"	border-radius: 		2px;\n"
"	background-color: 	rgb(252, 251, 251);\n"
"}\n"
"\n"
"QComboBox {\n"
"	margin-left: 		3px;\n"
"	border-radius: 	3px;\n"
"	selection-color: 	black;\n"
"	padding-left: 		5px;\n"
"	selection-color: 	black;\n"
"}\n"
"QComboBox::drop-down {\n"
"	width: 						10px;\n"
"	padding: 					2px;\n"
"	border: 					0px solid black;\n"
"	background: 			rgb(0"
                        ", 187, 255);\n"
"    image: 						url(:/icons/res_icon_down.png);\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"	min-height: 				50px;\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"QPushButton {\n"
"	border: 					1px solid rgb(204, 203, 200);\n"
"	border-radius: 		10px;\n"
"	background-color: 	rgb(213, 212, 209);\n"
"	color: 						white;\n"
"}\n"
"QPushButton:hover {\n"
"	border: 					1px solid rgb(0, 187, 255);\n"
"	background-color: 	rgb(0, 137, 241, 128);\n"
"}\n"
"QPushButton::checked, QPushButton:pressed {\n"
"	background-color: 	rgb(0, 187, 255);\n"
"}\n"
"QPushButton#patternLearn {\n"
"	border-radius: 		2px;\n"
"}\n"
"\n"
"QTextEdit#help {\n"
"	color: 						white;\n"
"	background-color:	transparent;\n"
"}\n"
"\n"
"\n"
"QScrollBar:vertical, QScrollBar:horizontal {\n"
"	border: 				0px solid black;\n"
"	background: 		rgba(255, 255, 255, 32);\n"
"}\n"
"QScrollBar::handle:vertical, QScrollBar::handle:horizontal {\n"
"	border: 				0px solid black;\n"
"	background: 		rgb(161, 161, 161);\n"
"	border-radius: 	3px;\n"
"}\n"
""
                        "QScrollBar:vertical {						width: 			8px;					}\n"
"QScrollBar:horizontal {					height: 		8px;				}\n"
"QScrollBar::handle:vertical {			min-height: 8px;		}\n"
"QScrollBar::handle:horizontal {	min-width: 	8px;			}\n"
"QScrollBar::add-line:vertical, QScrollBar::add-line:hozirontal, QScrollBar::sub-line:vertical, QScrollBar::sub-line:horizontal, QScrollBar::up-arrow:vertical, QScrollBar::up-arrow:horizontal, QScrollBar::down-arrow:vertical, QScrollBar::down-arrow:horizontal {\n"
"	border: 			0px solid black;\n"
"	background: 	transparent;\n"
"	width: 				1px;\n"
"	height: 			1px;\n"
"}\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical, QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\n"
"	background: 	none;\n"
"}\n"
"\n"
"QSplitter::handle {\n"
"	background: 							rgb(255, 255, 255, 30);\n"
"}\n"
"QSplitter::handle:pressed {\n"
"	background: 							rgb(0, 187, 255);\n"
" }\n"
"QSplitter::handle:horizontal	 	{	width: 	4px; }\n"
"QSplitter::handle:vertical     		{	height:	4px; }\n"
""
                        "\n"
"QSplitter::handle:horizontal	 	{	width: 4px; }\n"
"QSplitter::handle:vertical     		{	height: 4px; }\n"
""));
        horizontalLayout_2 = new QHBoxLayout(ExtOscPatternEditor);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        global = new QFrame(ExtOscPatternEditor);
        global->setObjectName(QString::fromUtf8("global"));
        global->setFrameShape(QFrame::StyledPanel);
        global->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(global);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        templates = new QComboBox(global);
        templates->addItem(QString());
        templates->setObjectName(QString::fromUtf8("templates"));
        templates->setMinimumSize(QSize(0, 20));
        templates->setMaximumSize(QSize(16777215, 20));
        templates->setEditable(false);
        templates->setDuplicatesEnabled(true);

        verticalLayout_3->addWidget(templates);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(15);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        patternEdit = new QPlainTextEditWithFocus(global);
        patternEdit->setObjectName(QString::fromUtf8("patternEdit"));

        horizontalLayout_7->addWidget(patternEdit);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        patternClear = new QPushButton(global);
        patternClear->setObjectName(QString::fromUtf8("patternClear"));
        patternClear->setMinimumSize(QSize(20, 20));
        patternClear->setMaximumSize(QSize(20, 20));
        patternClear->setFocusPolicy(Qt::NoFocus);

        verticalLayout_2->addWidget(patternClear);

        verticalSpacer_2 = new QSpacerItem(10, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        patternLearn = new QPushButton(global);
        patternLearn->setObjectName(QString::fromUtf8("patternLearn"));
        patternLearn->setMinimumSize(QSize(30, 20));
        patternLearn->setMaximumSize(QSize(30, 16777215));
        patternLearn->setFocusPolicy(Qt::NoFocus);

        verticalLayout_2->addWidget(patternLearn);


        horizontalLayout_7->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(15);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        protocolLabel = new QLabel(global);
        protocolLabel->setObjectName(QString::fromUtf8("protocolLabel"));
        protocolLabel->setMinimumSize(QSize(100, 0));
        protocolLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(protocolLabel);

        protocolCombo = new QComboBox(global);
        protocolCombo->setObjectName(QString::fromUtf8("protocolCombo"));
        protocolCombo->setMinimumSize(QSize(0, 20));
        protocolCombo->setMaximumSize(QSize(16777215, 20));
        protocolCombo->setEditable(false);
        protocolCombo->setDuplicatesEnabled(true);

        horizontalLayout_6->addWidget(protocolCombo);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        hostOSCLabel = new QLabel(global);
        hostOSCLabel->setObjectName(QString::fromUtf8("hostOSCLabel"));
        hostOSCLabel->setMinimumSize(QSize(100, 0));
        hostOSCLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(hostOSCLabel);

        hostIpCombo = new QComboBox(global);
        hostIpCombo->setObjectName(QString::fromUtf8("hostIpCombo"));
        hostIpCombo->setMinimumSize(QSize(340, 20));
        hostIpCombo->setMaximumSize(QSize(340, 20));
        hostIpCombo->setEditable(true);
        hostIpCombo->setDuplicatesEnabled(true);

        horizontalLayout->addWidget(hostIpCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        portLabel = new QLabel(global);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setMinimumSize(QSize(65, 0));
        portLabel->setMaximumSize(QSize(65, 16777215));
        portLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(portLabel);

        portCombo = new QComboBox(global);
        portCombo->setObjectName(QString::fromUtf8("portCombo"));
        portCombo->setMinimumSize(QSize(190, 20));
        portCombo->setMaximumSize(QSize(190, 20));
        portCombo->setEditable(true);
        portCombo->setDuplicatesEnabled(true);

        horizontalLayout->addWidget(portCombo);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        addressOSCLabel = new QLabel(global);
        addressOSCLabel->setObjectName(QString::fromUtf8("addressOSCLabel"));
        addressOSCLabel->setMinimumSize(QSize(100, 0));
        addressOSCLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(addressOSCLabel);

        addressOscCombo = new QComboBox(global);
        addressOscCombo->setObjectName(QString::fromUtf8("addressOscCombo"));
        addressOscCombo->setMinimumSize(QSize(0, 20));
        addressOscCombo->setMaximumSize(QSize(16777215, 20));
        addressOscCombo->setEditable(true);
        addressOscCombo->setDuplicatesEnabled(true);

        horizontalLayout_3->addWidget(addressOscCombo);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(15);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        hostMIDILabel = new QLabel(global);
        hostMIDILabel->setObjectName(QString::fromUtf8("hostMIDILabel"));
        hostMIDILabel->setMinimumSize(QSize(100, 0));
        hostMIDILabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(hostMIDILabel);

        hostMidiCombo = new QComboBox(global);
        hostMidiCombo->setObjectName(QString::fromUtf8("hostMidiCombo"));
        hostMidiCombo->setMinimumSize(QSize(340, 20));
        hostMidiCombo->setMaximumSize(QSize(340, 20));
        hostMidiCombo->setEditable(true);
        hostMidiCombo->setDuplicatesEnabled(true);

        horizontalLayout_4->addWidget(hostMidiCombo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        addressMIDILabel = new QLabel(global);
        addressMIDILabel->setObjectName(QString::fromUtf8("addressMIDILabel"));
        addressMIDILabel->setMinimumSize(QSize(65, 0));
        addressMIDILabel->setMaximumSize(QSize(65, 16777215));
        addressMIDILabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(addressMIDILabel);

        addressMidiCombo = new QComboBox(global);
        addressMidiCombo->setObjectName(QString::fromUtf8("addressMidiCombo"));
        addressMidiCombo->setMinimumSize(QSize(190, 20));
        addressMidiCombo->setMaximumSize(QSize(190, 20));
        addressMidiCombo->setEditable(false);
        addressMidiCombo->setDuplicatesEnabled(true);

        horizontalLayout_4->addWidget(addressMidiCombo);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(15);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        argument1Label = new QLabel(global);
        argument1Label->setObjectName(QString::fromUtf8("argument1Label"));
        argument1Label->setMinimumSize(QSize(100, 0));
        argument1Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_8->addWidget(argument1Label);

        argument1Combo = new QComboBoxWithFocus(global);
        argument1Combo->setObjectName(QString::fromUtf8("argument1Combo"));
        argument1Combo->setMinimumSize(QSize(0, 20));
        argument1Combo->setMaximumSize(QSize(16777215, 20));
        argument1Combo->setEditable(true);
        argument1Combo->setDuplicatesEnabled(true);

        horizontalLayout_8->addWidget(argument1Combo);

        argument1Clear = new QPushButton(global);
        argument1Clear->setObjectName(QString::fromUtf8("argument1Clear"));
        argument1Clear->setMinimumSize(QSize(20, 20));
        argument1Clear->setMaximumSize(QSize(20, 20));
        argument1Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_8->addWidget(argument1Clear);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(15);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        argument2Label = new QLabel(global);
        argument2Label->setObjectName(QString::fromUtf8("argument2Label"));
        argument2Label->setMinimumSize(QSize(100, 0));
        argument2Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(argument2Label);

        argument2Combo = new QComboBoxWithFocus(global);
        argument2Combo->setObjectName(QString::fromUtf8("argument2Combo"));
        argument2Combo->setMinimumSize(QSize(0, 20));
        argument2Combo->setMaximumSize(QSize(16777215, 20));
        argument2Combo->setEditable(true);
        argument2Combo->setDuplicatesEnabled(true);

        horizontalLayout_12->addWidget(argument2Combo);

        argument2Clear = new QPushButton(global);
        argument2Clear->setObjectName(QString::fromUtf8("argument2Clear"));
        argument2Clear->setMinimumSize(QSize(20, 20));
        argument2Clear->setMaximumSize(QSize(20, 20));
        argument2Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_12->addWidget(argument2Clear);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(15);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        argument3Label = new QLabel(global);
        argument3Label->setObjectName(QString::fromUtf8("argument3Label"));
        argument3Label->setMinimumSize(QSize(100, 0));
        argument3Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_11->addWidget(argument3Label);

        argument3Combo = new QComboBoxWithFocus(global);
        argument3Combo->setObjectName(QString::fromUtf8("argument3Combo"));
        argument3Combo->setMinimumSize(QSize(0, 20));
        argument3Combo->setMaximumSize(QSize(16777215, 20));
        argument3Combo->setEditable(true);
        argument3Combo->setDuplicatesEnabled(true);

        horizontalLayout_11->addWidget(argument3Combo);

        argument3Clear = new QPushButton(global);
        argument3Clear->setObjectName(QString::fromUtf8("argument3Clear"));
        argument3Clear->setMinimumSize(QSize(20, 20));
        argument3Clear->setMaximumSize(QSize(20, 20));
        argument3Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_11->addWidget(argument3Clear);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(15);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        argument4Label = new QLabel(global);
        argument4Label->setObjectName(QString::fromUtf8("argument4Label"));
        argument4Label->setMinimumSize(QSize(100, 0));
        argument4Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_10->addWidget(argument4Label);

        argument4Combo = new QComboBoxWithFocus(global);
        argument4Combo->setObjectName(QString::fromUtf8("argument4Combo"));
        argument4Combo->setMinimumSize(QSize(0, 20));
        argument4Combo->setMaximumSize(QSize(16777215, 20));
        argument4Combo->setEditable(true);
        argument4Combo->setDuplicatesEnabled(true);

        horizontalLayout_10->addWidget(argument4Combo);

        argument4Clear = new QPushButton(global);
        argument4Clear->setObjectName(QString::fromUtf8("argument4Clear"));
        argument4Clear->setMinimumSize(QSize(20, 20));
        argument4Clear->setMaximumSize(QSize(20, 20));
        argument4Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_10->addWidget(argument4Clear);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(15);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        argument5Label = new QLabel(global);
        argument5Label->setObjectName(QString::fromUtf8("argument5Label"));
        argument5Label->setMinimumSize(QSize(100, 0));
        argument5Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_9->addWidget(argument5Label);

        argument5Combo = new QComboBoxWithFocus(global);
        argument5Combo->setObjectName(QString::fromUtf8("argument5Combo"));
        argument5Combo->setMinimumSize(QSize(0, 20));
        argument5Combo->setMaximumSize(QSize(16777215, 20));
        argument5Combo->setEditable(true);
        argument5Combo->setDuplicatesEnabled(true);

        horizontalLayout_9->addWidget(argument5Combo);

        argument5Clear = new QPushButton(global);
        argument5Clear->setObjectName(QString::fromUtf8("argument5Clear"));
        argument5Clear->setMinimumSize(QSize(20, 20));
        argument5Clear->setMaximumSize(QSize(20, 20));
        argument5Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_9->addWidget(argument5Clear);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(15);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        argument6Label = new QLabel(global);
        argument6Label->setObjectName(QString::fromUtf8("argument6Label"));
        argument6Label->setMinimumSize(QSize(100, 0));
        argument6Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(argument6Label);

        argument6Combo = new QComboBoxWithFocus(global);
        argument6Combo->setObjectName(QString::fromUtf8("argument6Combo"));
        argument6Combo->setMinimumSize(QSize(0, 20));
        argument6Combo->setMaximumSize(QSize(16777215, 20));
        argument6Combo->setEditable(true);
        argument6Combo->setDuplicatesEnabled(true);

        horizontalLayout_5->addWidget(argument6Combo);

        argument6Clear = new QPushButton(global);
        argument6Clear->setObjectName(QString::fromUtf8("argument6Clear"));
        argument6Clear->setMinimumSize(QSize(20, 20));
        argument6Clear->setMaximumSize(QSize(20, 20));
        argument6Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_5->addWidget(argument6Clear);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(15);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        argument7Label = new QLabel(global);
        argument7Label->setObjectName(QString::fromUtf8("argument7Label"));
        argument7Label->setMinimumSize(QSize(100, 0));
        argument7Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_14->addWidget(argument7Label);

        argument7Combo = new QComboBoxWithFocus(global);
        argument7Combo->setObjectName(QString::fromUtf8("argument7Combo"));
        argument7Combo->setMinimumSize(QSize(0, 20));
        argument7Combo->setMaximumSize(QSize(16777215, 20));
        argument7Combo->setEditable(true);
        argument7Combo->setDuplicatesEnabled(true);

        horizontalLayout_14->addWidget(argument7Combo);

        argument7Clear = new QPushButton(global);
        argument7Clear->setObjectName(QString::fromUtf8("argument7Clear"));
        argument7Clear->setMinimumSize(QSize(20, 20));
        argument7Clear->setMaximumSize(QSize(20, 20));
        argument7Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_14->addWidget(argument7Clear);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(15);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        argument8Label = new QLabel(global);
        argument8Label->setObjectName(QString::fromUtf8("argument8Label"));
        argument8Label->setMinimumSize(QSize(100, 0));
        argument8Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_15->addWidget(argument8Label);

        argument8Combo = new QComboBoxWithFocus(global);
        argument8Combo->setObjectName(QString::fromUtf8("argument8Combo"));
        argument8Combo->setMinimumSize(QSize(0, 20));
        argument8Combo->setMaximumSize(QSize(16777215, 20));
        argument8Combo->setEditable(true);
        argument8Combo->setDuplicatesEnabled(true);

        horizontalLayout_15->addWidget(argument8Combo);

        argument8Clear = new QPushButton(global);
        argument8Clear->setObjectName(QString::fromUtf8("argument8Clear"));
        argument8Clear->setMinimumSize(QSize(20, 20));
        argument8Clear->setMaximumSize(QSize(20, 20));
        argument8Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_15->addWidget(argument8Clear);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(15);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        argument9Label = new QLabel(global);
        argument9Label->setObjectName(QString::fromUtf8("argument9Label"));
        argument9Label->setMinimumSize(QSize(100, 0));
        argument9Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_16->addWidget(argument9Label);

        argument9Combo = new QComboBoxWithFocus(global);
        argument9Combo->setObjectName(QString::fromUtf8("argument9Combo"));
        argument9Combo->setMinimumSize(QSize(0, 20));
        argument9Combo->setMaximumSize(QSize(16777215, 20));
        argument9Combo->setEditable(true);
        argument9Combo->setDuplicatesEnabled(true);

        horizontalLayout_16->addWidget(argument9Combo);

        argument9Clear = new QPushButton(global);
        argument9Clear->setObjectName(QString::fromUtf8("argument9Clear"));
        argument9Clear->setMinimumSize(QSize(20, 20));
        argument9Clear->setMaximumSize(QSize(20, 20));
        argument9Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_16->addWidget(argument9Clear);


        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(15);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        argument10Label = new QLabel(global);
        argument10Label->setObjectName(QString::fromUtf8("argument10Label"));
        argument10Label->setMinimumSize(QSize(100, 0));
        argument10Label->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_17->addWidget(argument10Label);

        argument10Combo = new QComboBoxWithFocus(global);
        argument10Combo->setObjectName(QString::fromUtf8("argument10Combo"));
        argument10Combo->setMinimumSize(QSize(0, 20));
        argument10Combo->setMaximumSize(QSize(16777215, 20));
        argument10Combo->setEditable(true);
        argument10Combo->setDuplicatesEnabled(true);

        horizontalLayout_17->addWidget(argument10Combo);

        argument10Clear = new QPushButton(global);
        argument10Clear->setObjectName(QString::fromUtf8("argument10Clear"));
        argument10Clear->setMinimumSize(QSize(20, 20));
        argument10Clear->setMaximumSize(QSize(20, 20));
        argument10Clear->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_17->addWidget(argument10Clear);


        verticalLayout->addLayout(horizontalLayout_17);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout_2->addWidget(global);

#if QT_CONFIG(shortcut)
        protocolLabel->setBuddy(protocolCombo);
        hostOSCLabel->setBuddy(hostIpCombo);
        portLabel->setBuddy(portCombo);
        addressOSCLabel->setBuddy(addressOscCombo);
        hostMIDILabel->setBuddy(hostMidiCombo);
        addressMIDILabel->setBuddy(addressMidiCombo);
        argument1Label->setBuddy(argument1Combo);
        argument2Label->setBuddy(argument2Combo);
        argument3Label->setBuddy(argument3Combo);
        argument4Label->setBuddy(argument4Combo);
        argument5Label->setBuddy(argument5Combo);
        argument6Label->setBuddy(argument6Combo);
        argument7Label->setBuddy(argument6Combo);
        argument8Label->setBuddy(argument6Combo);
        argument9Label->setBuddy(argument6Combo);
        argument10Label->setBuddy(argument6Combo);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(patternEdit, protocolCombo);
        QWidget::setTabOrder(protocolCombo, hostIpCombo);
        QWidget::setTabOrder(hostIpCombo, portCombo);
        QWidget::setTabOrder(portCombo, addressOscCombo);
        QWidget::setTabOrder(addressOscCombo, hostMidiCombo);
        QWidget::setTabOrder(hostMidiCombo, addressMidiCombo);
        QWidget::setTabOrder(addressMidiCombo, argument1Combo);
        QWidget::setTabOrder(argument1Combo, argument2Combo);
        QWidget::setTabOrder(argument2Combo, argument3Combo);
        QWidget::setTabOrder(argument3Combo, argument4Combo);
        QWidget::setTabOrder(argument4Combo, argument5Combo);
        QWidget::setTabOrder(argument5Combo, argument6Combo);
        QWidget::setTabOrder(argument6Combo, patternClear);
        QWidget::setTabOrder(patternClear, argument1Clear);
        QWidget::setTabOrder(argument1Clear, argument2Clear);
        QWidget::setTabOrder(argument2Clear, argument3Clear);
        QWidget::setTabOrder(argument3Clear, argument4Clear);
        QWidget::setTabOrder(argument4Clear, argument5Clear);
        QWidget::setTabOrder(argument5Clear, argument6Clear);

        retranslateUi(ExtOscPatternEditor);
        QObject::connect(protocolCombo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(hostIpCombo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(portCombo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(addressOscCombo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(addressMidiCombo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(hostMidiCombo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument1Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument2Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument3Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument4Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument5Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument6Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(hostIpCombo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(portCombo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(addressOscCombo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(hostMidiCombo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument1Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument2Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument3Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument4Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument5Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument6Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(patternEdit, SIGNAL(textChanged()), ExtOscPatternEditor, SLOT(textPatternChanged()));
        QObject::connect(argument1Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument2Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument3Clear, SIGNAL(pressed()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument4Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument5Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument6Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(patternClear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(patternEdit, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument1Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument2Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument3Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument4Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument5Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument6Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(patternLearn, SIGNAL(released()), ExtOscPatternEditor, SLOT(learn()));
        QObject::connect(templates, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(applyTemplate()));
        QObject::connect(argument9Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument8Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument7Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument6Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument6Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument7Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument8Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument9Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument7Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument8Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument9Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument7Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument8Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument9Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));
        QObject::connect(argument10Clear, SIGNAL(released()), ExtOscPatternEditor, SLOT(clearApattern()));
        QObject::connect(argument10Combo, SIGNAL(editTextChanged(QString)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument10Combo, SIGNAL(currentIndexChanged(int)), ExtOscPatternEditor, SLOT(currentItemChanged()));
        QObject::connect(argument10Combo, SIGNAL(focusIn()), ExtOscPatternEditor, SLOT(fieldFocusIn()));

        QMetaObject::connectSlotsByName(ExtOscPatternEditor);
    } // setupUi

    void retranslateUi(QWidget *ExtOscPatternEditor)
    {
        ExtOscPatternEditor->setWindowTitle(QCoreApplication::translate("ExtOscPatternEditor", "IanniX", nullptr));
        templates->setItemText(0, QCoreApplication::translate("ExtOscPatternEditor", "Templates", nullptr));

#if QT_CONFIG(tooltip)
        templates->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Select here the protocol used to transmit message", nullptr));
#endif // QT_CONFIG(tooltip)
        patternEdit->setPlainText(QString());
#if QT_CONFIG(tooltip)
        patternClear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the message", nullptr));
#endif // QT_CONFIG(tooltip)
        patternClear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
#if QT_CONFIG(tooltip)
        patternLearn->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Learns a message by copying next received message", nullptr));
#endif // QT_CONFIG(tooltip)
        patternLearn->setText(QCoreApplication::translate("ExtOscPatternEditor", "learn", nullptr));
        protocolLabel->setText(QCoreApplication::translate("ExtOscPatternEditor", "SEND THROUGH", nullptr));
#if QT_CONFIG(tooltip)
        protocolCombo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Select here the protocol used to transmit message", nullptr));
#endif // QT_CONFIG(tooltip)
        hostOSCLabel->setText(QCoreApplication::translate("ExtOscPatternEditor", "TO HOST", nullptr));
#if QT_CONFIG(tooltip)
        hostIpCombo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Select or type the destination application/host IP", nullptr));
#endif // QT_CONFIG(tooltip)
        portLabel->setText(QCoreApplication::translate("ExtOscPatternEditor", "ON PORT", nullptr));
#if QT_CONFIG(tooltip)
        portCombo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Select or type the destination application/host port number", nullptr));
#endif // QT_CONFIG(tooltip)
        addressOSCLabel->setText(QCoreApplication::translate("ExtOscPatternEditor", "TO ADDRESS", nullptr));
#if QT_CONFIG(tooltip)
        addressOscCombo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Select or type an OSC address to reach", nullptr));
#endif // QT_CONFIG(tooltip)
        hostMIDILabel->setText(QCoreApplication::translate("ExtOscPatternEditor", "TO MIDI DEVICE", nullptr));
#if QT_CONFIG(tooltip)
        hostMidiCombo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Select or type a MIDI device to reach", nullptr));
#endif // QT_CONFIG(tooltip)
        addressMIDILabel->setText(QCoreApplication::translate("ExtOscPatternEditor", "TO CONTROL", nullptr));
#if QT_CONFIG(tooltip)
        addressMidiCombo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Select here a MIDI control", nullptr));
#endif // QT_CONFIG(tooltip)
        argument1Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 1", nullptr));
#if QT_CONFIG(tooltip)
        argument1Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument1Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument1Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument2Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 2", nullptr));
#if QT_CONFIG(tooltip)
        argument2Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument2Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument2Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument3Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 3", nullptr));
#if QT_CONFIG(tooltip)
        argument3Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument3Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument3Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument4Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 4", nullptr));
#if QT_CONFIG(tooltip)
        argument4Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument4Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument4Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument5Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 5", nullptr));
#if QT_CONFIG(tooltip)
        argument5Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument5Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument5Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument6Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 6", nullptr));
#if QT_CONFIG(tooltip)
        argument6Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument6Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument6Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument7Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 7", nullptr));
#if QT_CONFIG(tooltip)
        argument7Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument7Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument7Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument8Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 8", nullptr));
#if QT_CONFIG(tooltip)
        argument8Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument8Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument8Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument9Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 9", nullptr));
#if QT_CONFIG(tooltip)
        argument9Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument9Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument9Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
        argument10Label->setText(QCoreApplication::translate("ExtOscPatternEditor", "VALUE 10", nullptr));
#if QT_CONFIG(tooltip)
        argument10Combo->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Type here a IanniX variable or your custom value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        argument10Clear->setToolTip(QCoreApplication::translate("ExtOscPatternEditor", "Clears the value", nullptr));
#endif // QT_CONFIG(tooltip)
        argument10Clear->setText(QCoreApplication::translate("ExtOscPatternEditor", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExtOscPatternEditor: public Ui_ExtOscPatternEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTOSCPATTERNEDITOR_H
