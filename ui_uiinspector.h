/********************************************************************************
** Form generated from reading UI file 'uiinspector.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIINSPECTOR_H
#define UI_UIINSPECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "items/uitreeview.h"

QT_BEGIN_NAMESPACE

class Ui_UiInspector
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *globalFrame;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tab;
    QWidget *tabProject;
    QVBoxLayout *verticalLayout_13;
    UiTreeView *files;
    QWidget *tabInfo;
    QVBoxLayout *verticalLayout_3;
    QLabel *typeLabel;
    QTabWidget *ssTabInfo;
    QWidget *ssTabInfoGeneral;
    QVBoxLayout *verticalLayout_17;
    QWidget *widgetID;
    QVBoxLayout *verticalLayout_20;
    QHBoxLayout *horizontalLayout_24;
    QLabel *IDLabel;
    QPushButton *newIdButton;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_25;
    QLabel *groupIdLabel;
    QPushButton *groupIdButton;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_28;
    QLabel *activityLabel;
    QCheckBox *activityCheck;
    QWidget *widgetStyle;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_26;
    QLabel *sizeLabel2;
    QDoubleSpinBox *sizeSpin;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_27;
    QLabel *labelLabel;
    QLineEdit *labelLine;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_32;
    QLabel *colorLabel1;
    QComboBox *colorCombo1;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_31;
    QLabel *colorLabel2;
    QComboBox *colorCombo2;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_33;
    QLabel *colorLabelMultiply;
    QComboBox *colorComboMultiply;
    QSpacerItem *horizontalSpacer_21;
    QHBoxLayout *horizontalLayout_35;
    QLabel *textureLabel1;
    QComboBox *textureCombo1;
    QSpacerItem *horizontalSpacer_28;
    QHBoxLayout *horizontalLayout_34;
    QLabel *textureLabel2;
    QComboBox *textureCombo2;
    QSpacerItem *horizontalSpacer_27;
    QSpacerItem *verticalSpacer_4;
    QWidget *ssTabInfoSpace;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *positionLabel;
    QDoubleSpinBox *positionX;
    QDoubleSpinBox *positionY;
    QDoubleSpinBox *positionZ;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_16;
    QLabel *sizeLabel;
    QDoubleSpinBox *sizeWSpin;
    QDoubleSpinBox *sizeHSpin;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_38;
    QLabel *intertiaLabel;
    QDoubleSpinBox *intertiaSpin;
    QSpacerItem *horizontalSpacer_22;
    QHBoxLayout *horizontalLayout_18;
    QLabel *widthLabel;
    QDoubleSpinBox *widthSpin;
    QDoubleSpinBox *depthSpin;
    QSpacerItem *horizontalSpacer_25;
    QHBoxLayout *horizontalLayout_17;
    QLabel *pointsLabel;
    QPushButton *pointsResample;
    QPushButton *pointsLists;
    QSpacerItem *horizontalSpacer_7;
    QGridLayout *gridLayout;
    QComboBox *equationTemplate;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *horizontalSpacer_24;
    QLabel *equationLabel;
    QPlainTextEdit *equationEdit;
    QWidget *equationType;
    QVBoxLayout *verticalLayout_8;
    QRadioButton *equationType0;
    QRadioButton *equationType1;
    QFrame *frame;
    QVBoxLayout *verticalLayout_24;
    QHBoxLayout *horizontalLayout_8;
    QLabel *equationParam1Label;
    QSlider *equationParam1Slider;
    QDoubleSpinBox *equationParam1Value;
    QHBoxLayout *horizontalLayout_29;
    QLabel *equationParam2Label;
    QSlider *equationParam2Slider;
    QDoubleSpinBox *equationParam2Value;
    QHBoxLayout *horizontalLayout_30;
    QLabel *equationParam3Label;
    QSlider *equationParam3Slider;
    QDoubleSpinBox *equationParam3Value;
    QHBoxLayout *horizontalLayout_36;
    QLabel *equationParam4Label;
    QSlider *equationParam4Slider;
    QDoubleSpinBox *equationParam4Value;
    QHBoxLayout *horizontalLayout_37;
    QLabel *equationParam5Label;
    QSlider *equationParam5Slider;
    QDoubleSpinBox *equationParam5Value;
    QPushButton *equationParamReset;
    QSpinBox *equationPoints;
    QSpacerItem *verticalSpacer;
    QWidget *ssTabInfoTime;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_15;
    QLabel *triggerOffLabel;
    QDoubleSpinBox *triggerOffSpin;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_21;
    QLabel *cursorSpeedLabel;
    QDoubleSpinBox *speedSpin;
    QLabel *cursorSpeedLabel_2;
    QDoubleSpinBox *cursorLengthSpin;
    QCheckBox *cursorSpeedLock;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_23;
    QLabel *speedFLabel;
    QDoubleSpinBox *speedFSpin;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_19;
    QLabel *patternLabel;
    QComboBox *patternLine;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_20;
    QLabel *easingLabel;
    QComboBox *easingCombo;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_39;
    QLabel *fireTriggersLabel;
    QComboBox *fireTriggers;
    QSpacerItem *horizontalSpacer_29;
    QHBoxLayout *horizontalLayout_22;
    QLabel *offsetLabel;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_3;
    QLabel *offsetLabel1;
    QDoubleSpinBox *offsetInitialSpin;
    QLabel *offsetLabel2_2;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *offsetLabel2;
    QDoubleSpinBox *offsetStartSpin;
    QLabel *offsetLabel3;
    QDoubleSpinBox *offsetEndSpin;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QWidget *ssTabInfoMessage;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *messagesButton;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *messagesSpin;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_6;
    QWidget *cursorSourceMode;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *cursorSourceMode0;
    QRadioButton *cursorSourceMode1;
    QRadioButton *cursorSourceMode2;
    QRadioButton *cursorSourceMode3;
    QGridLayout *gridLayout_5;
    QLabel *cursorTargetLabel1;
    QDoubleSpinBox *cursorSourceX1;
    QLabel *cursorTargetLabel2;
    QDoubleSpinBox *cursorSourceX2;
    QLabel *cursorTargetLabel3;
    QDoubleSpinBox *cursorTargetX1;
    QLabel *cursorTargetLabel4;
    QDoubleSpinBox *cursorTargetX2;
    QSpacerItem *horizontalSpacer_19;
    QGridLayout *gridLayout_4;
    QLabel *cursorTargetLabel5;
    QDoubleSpinBox *cursorSourceY2;
    QLabel *cursorTargetLabel6;
    QDoubleSpinBox *cursorSourceY1;
    QLabel *cursorTargetLabel7;
    QDoubleSpinBox *cursorTargetY2;
    QLabel *cursorTargetLabel8;
    QDoubleSpinBox *cursorTargetY1;
    QSpacerItem *horizontalSpacer_20;
    QGridLayout *gridLayout_2;
    QLabel *cursorTargetLabel11;
    QDoubleSpinBox *cursorSourceZ1;
    QLabel *cursorTargetLabel13;
    QDoubleSpinBox *cursorSourceZ2;
    QLabel *cursorTargetLabel12;
    QDoubleSpinBox *cursorTargetZ1;
    QLabel *cursorTargetLabel14;
    QDoubleSpinBox *cursorTargetZ2;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *verticalSpacer_2;
    QWidget *ssTabRessource;
    QVBoxLayout *verticalLayout_14;
    QLabel *ressourcesTexturesLabel;
    UiTreeView *ressourcesTextures;
    QLabel *ressourcesColorsLabel;
    UiTreeView *ressourcesColors;
    QSpacerItem *verticalSpacer_5;
    QWidget *tabView;
    QVBoxLayout *verticalLayout_10;
    QSplitter *splitter_3;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_7;
    QTreeWidget *ccView;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *unmuteObjects;
    QPushButton *unsoloObjects;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *unmuteGroups;
    QPushButton *unsoloGroups;
    QCheckBox *viewCurveOpacityCheck;
    QCheckBox *viewCameraModeCheck;
    QHBoxLayout *horizontalLayout_9;
    QLabel *followIdLabel;
    QSpinBox *followId;
    QPushButton *followIdClear;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_22;
    QLabel *autoresizeLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *autoresizeLabelLeft;
    QSlider *autoresizeSlider;
    QLabel *autoresizeLabelRight;
    QWidget *tabConfig;
    QHBoxLayout *horizontalLayout_11;
    QTabWidget *ssTabConfig;
    QWidget *ssTabConfigLog;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *spaceForMessageLog;
    QWidget *ssTabConfigNetwork;
    QVBoxLayout *verticalLayout_19;
    QLabel *myIPLabel;
    QPlainTextEdit *myIP;
    QVBoxLayout *ssTabConfigNetworkLayout;
    QSpacerItem *verticalSpacer_10;
    QWidget *ssTabConfigMIDI;
    QVBoxLayout *verticalLayout_18;
    QVBoxLayout *ssTabConfigMIDILayout;
    QSpacerItem *verticalSpacer_7;
    QWidget *ssTabConfigArduino;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *ssTabConfigArduinoLayout;
    QSpacerItem *verticalSpacer_8;
    QWidget *ssTabConfigSyphon;
    QVBoxLayout *verticalLayout_21;
    QVBoxLayout *ssTabConfigSyphonLayout;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_4;
    QLabel *mouseLabel;
    QLabel *rotationLabel;
    QLabel *zoomLabel;

    void setupUi(QWidget *UiInspector)
    {
        if (UiInspector->objectName().isEmpty())
            UiInspector->setObjectName(QString::fromUtf8("UiInspector"));
        UiInspector->resize(387, 562);
        UiInspector->setMaximumSize(QSize(390, 16777215));
        UiInspector->setStyleSheet(QString::fromUtf8("QTabWidget, QLabel, QCheckBox, QLineEdit, QPlainTextEdit, QPushButton, QSpinBox, QDoubleSpinBox, QTreeView, QHeaderView, QTabBar, QComboBox, QFrame#globalFrame, QTabBar::tab, QTreeView, QHeaderView, QDockWidget, QStatusBar, QRadioButton, QToolButton {\n"
"	font: 						10px \"Museo Sans\", \"Museo Sans 500\", \"Arial\";\n"
"	padding:					0px;\n"
"	margin:					0px;\n"
"	min-height: 				20px;\n"
"	color: 						white;\n"
"	border: 					0px solid black;\n"
"	icon-size: 									14px;\n"
"}\n"
"QPushButton, QSpinBox, QDoubleSpinBox, QLineEdit, QPlainTextEdit, QCheckBox::indicator, QRadioButton::indicator, QTreeView::indicator, QComboBox, QTreeView, QHeaderView {\n"
"	border: 					1px solid rgb(55, 55, 55);\n"
"	border-radius: 		2px;\n"
"	background-color: 	rgb(70, 70, 70);\n"
"}\n"
"QSpinBox, QDoubleSpinBox, QLineEdit, QPlainTextEdit, QCheckBox {\n"
"	margin-top: 			4px;\n"
"	margin-bottom: 		4px;\n"
"}\n"
"\n"
"QFrame#globalFrame, QFrame#transportFrame, QFrame#timeFrame, QFrame#optionFrame, QFrame#speedFrame, QFram"
                        "e#logoFrame, QFrame#perfFrame, QDialog {\n"
"	background-color: 	rgb(40, 40, 40);\n"
"}\n"
"QLabel, QCheckBox, QRadioButton {\n"
"	color: 						rgb(210, 210, 210);\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"	border: 					1px solid rgb(50, 50, 50);\n"
"}\n"
"QTabWidget::tab-bar {\n"
"	left: 							0px;\n"
"}\n"
"QTabWidget#tab {\n"
"	color: red;\n"
"}\n"
"QTabBar::tab {\n"
"	min-height: 							25px; /* FIX IN SS-TAB */\n"
"	background-color: 				rgb(110, 110, 110);\n"
"    border-top-left-radius: 		4px;\n"
"    border-top-right-radius: 	4px;\n"
"	margin-right:						2px;\n"
"	padding-left: 						5px;\n"
"	padding-right:						5px;\n"
"	color: 									rgb(220, 220, 220);\n"
"}\n"
"QTabBar::tab:selected {\n"
"	background-color: 				rgb(242, 241, 237);\n"
"	color: 									black;\n"
"}\n"
"QTabBar::tab:hover {\n"
"	color: 									black;\n"
"}\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 						2px;\n"
"}\n"
"QTabBar::tab:disabled {\n"
"	color: 									gray;\n"
"}\n"
"\n"
"\n"
"QPushButton {\n"
"	margin-left: 			6px"
                        ";\n"
"	padding-left: 			3px;\n"
"	padding-right: 		3px;\n"
"}\n"
"QPushButton:hover {\n"
"	border: 					1px solid rgb(28, 124, 195);\n"
"	background-color: 	rgb(21, 91, 143);\n"
"}\n"
"QPushButton::checked, QPushButton:pressed, QCheckBox::indicator:checked, QTreeView::indicator:checked, QRadioButton::indicator:checked {\n"
"	background-color: 	rgb(0, 187, 255);\n"
"}\n"
"\n"
"\n"
"QCheckBox, QRadioButton {\n"
"	spacing: 					5px;\n"
"}\n"
"QCheckBox::indicator, QTreeView::indicator, QRadioButton::indicator  {\n"
"	width: 						10px;\n"
"	height: 					10px;\n"
"}\n"
"\n"
"QSpinBox, QDoubleSpinBox, QLineEdit {\n"
"	padding-left	:			5px;\n"
"}\n"
"QSpinBox::up-button, QDoubleSpinBox::up-button, QSpinBox::down-button, QDoubleSpinBox::down-button {\n"
"	width: 						5px;\n"
"	padding: 					2px;\n"
"	padding-left:			3px;\n"
"	background-color: 	rgb(60, 60, 60);\n"
"	border: 					0px solid black;\n"
"	border-left:				1px solid rgb(70, 70, 70);\n"
"}\n"
"QSpinBox::up-button, QDoubleSpinBox::up-button {\n"
"    image: "
                        "						url(:/icons/res_icon_plus.png);\n"
"	border-bottom:		1px solid rgb(70, 70, 70);\n"
"}\n"
"QSpinBox::down-button, QDoubleSpinBox::down-button {\n"
"    image: 						url(:/icons/res_icon_minus.png);\n"
"}\n"
"\n"
"\n"
"QComboBox {\n"
"	background:			rgb(242, 241, 237);\n"
"	color: 					black;\n"
"	margin-left: 		3px;\n"
"	border-radius: 	3px;\n"
"	selection-color: 	black;\n"
"	padding-left: 		5px;\n"
"}\n"
"QComboBox::drop-down {\n"
"	width: 						10px;\n"
"	padding: 					2px;\n"
"	border: 					0px solid black;\n"
"	background-color: 	rgb(70, 70, 70);\n"
"    image: 						url(:/icons/res_icon_down.png);\n"
"}\n"
"\n"
"\n"
"QTreeView {\n"
"	background:								rgb(50, 50, 50);\n"
"	alternate-background-color: 	rgb(55, 55, 55);\n"
"	selection-background-color: 	rgb(0, 187, 255);\n"
"	gridline-color: 							rgb(60, 60, 60);\n"
"	icon-size: 									14px;\n"
"}\n"
"QHeaderView {\n"
"	background: 							transparent;\n"
"	border: 									0px solid black;\n"
"	color: 										rgb(200, 200, 200);\n"
"	min-height:"
                        " 								14px;\n"
"}\n"
"QHeaderView::section {\n"
"	background: 							rgb(90, 90, 90);\n"
"	padding-left: 							5px;\n"
"	border-top-left-radius:  			3px;\n"
"	border-top-right-radius: 		3px;\n"
"	margin-right:							1px;\n"
"	font: 										9px \"Arial\";\n"
"}\n"
"QTreeView::item {\n"
"	min-height: 20px;\n"
"}\n"
"QTreeView::branch:has-children:!has-siblings:closed, QTreeView::branch:closed:has-children:has-siblings {\n"
"	border-image: 	none;\n"
"	image: 					url(:/items/res_tree_close.png);\n"
"}\n"
"QTreeView::branch:open:has-children:!has-siblings, QTreeView::branch:open:has-children:has-siblings  {\n"
"	border-image: 	none;\n"
"	image: 					url(:/items/res_tree_open.png);\n"
"}\n"
"\n"
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
"QScro"
                        "llBar:vertical {						width: 			8px;					}\n"
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
"\n"
"QSlider:horizontal {\n"
"	min-width: 				100px;\n"
"}\n"
"QSlider::groove:horizontal {\n"
"	border: 					0px solid transparent;\n"
"	background-color: 	rgb(70, 70, 70);\n"
"	height: 					3px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	width: 						11px;\n"
"	hei"
                        "ght: 					10px;\n"
"	border-radius: 		5px;\n"
"	margin-top: 			-4px;\n"
"	margin-bottom: 		-4px;\n"
"	border: 					0px solid black;\n"
"	background-color: 	rgb(0, 187, 250);\n"
"}\n"
"\n"
"\n"
"QSplitter::handle {\n"
"	background: 							rgb(255, 255, 255, 30);\n"
"}\n"
"QSplitter::handle:pressed {\n"
"	background: 							rgb(0, 187, 255);\n"
" }\n"
"QSplitter::handle:horizontal	 	{	width: 	4px; }\n"
"QSplitter::handle:vertical     		{	height:	4px; }\n"
"\n"
"QDockWidget {\n"
"}\n"
"QDockWidget::title {\n"
"    text-align:				center;\n"
"	background-color: 	rgb(70, 70, 70);\n"
"}\n"
"\n"
"QToolBar {\n"
"	background:				qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(247, 247, 247, 255), stop:1 rgba(222, 222, 222, 255));\n"
"	border: 					1px solid rgba(202, 202, 202, 255);\n"
"	spacing:					0px; \n"
"}\n"
"QToolButton {\n"
"	border: 					0px solid black;\n"
"	color:						black;\n"
"	border-radius: 		3px;\n"
"	margin:					3px;\n"
"}\n"
"QToolButton:pressed, QToolButton:checked {\n"
"    backgrou"
                        "nd-color:  rgba(0, 0, 0, 20);\n"
"}\n"
"\n"
"\n"
"QStatusBar {\n"
"	color: 						rgb(210, 210, 210);\n"
"	border-top: 				1px solid rgb(50, 50, 50);\n"
"	background-color: 	rgb(30, 30, 30);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"/*TRANSPORT*/\n"
"QFrame#transportFrame, QFrame#timeFrame, QFrame#optionFrame, QFrame#speedFrame, QFrame#logoFrame, QFrame#perfFrame{\n"
"	border: 					0px solid black;\n"
"	border-left: 				1px solid rgb(50, 50, 50);\n"
"}\n"
"QWIdget {\n"
"	margin:					0px;\n"
"	padding:					0px;\n"
"}\n"
"QWidget#speedSlider {\n"
"	margin-top: 			7px;\n"
"}\n"
"QWidget#timeEdit, QWidget#perfCpuEdit, QWidget#perfOpenGLEdit, QWidget#perfSchedulerEdit {\n"
"	background-color: 	transparent;\n"
"	border: 					0px solid black;\n"
"	font:							9px;\n"
"	color: 						rgb(140, 140, 140);\n"
"}\n"
"QLineEdit#timeEdit {\n"
"	font: 						40px \"Lucida Sans\", \"Lucida Grande\", \"Lucida Sans Unicode\", \"Lucida\";\n"
"	color: 						rgb(0, 187, 255);\n"
"}\n"
"QPushButton#logoButton {\n"
"	border: 					0px solid bl"
                        "ack;\n"
"	background-color: 	transparent;\n"
"}\n"
"QPushButton:hover#logoButton {\n"
"	border: 					1px solid rgb(28, 124, 195);\n"
"	background-color: 	rgb(21, 91, 143);\n"
"}\n"
"QPushButton#ffButton, QPushButton#playButton {\n"
"	min-width:  		40px;\n"
"	min-height: 		40px;\n"
"	border-radius: 20px;\n"
"	padding:			0px;\n"
"}\n"
"QPushButton#logoButton {\n"
"	margin: -2px;\n"
"}\n"
"/* ---- */\n"
"\n"
"\n"
"/* INSPECTEUR */\n"
"QWidget#ssTabInfoGeneral, QWidget#ssTabInfoSpace, QWidget#ssTabInfoTime, QWidget#ssTabInfoMessage, QWidget#ssTabConfigLog, QWidget#ssTabConfigNetwork, QWidget#ssTabConfigMIDI, QWidget#ssTabConfigArduino, QWidget#ssTabConfigSyphon, QWidget#ssTabConfigWeb, QWidget#ssTabRessource {\n"
"	background-color: 	rgb(50, 50, 50)\n"
"}\n"
"QWidget#tabProject, QWidget#tabView, QWidget#tabInfo, QWidget#tabControlCenter, QWidget#tabConfig {\n"
"	background-color: 	transparent;\n"
"}\n"
"QWidget#equationEdit {\n"
"	font: 						10px \"Lucida Console\", \"Monaco\", \"Monospace\";\n"
"}\n"
"\n"
"/* --"
                        "--- */\n"
"\n"
"\n"
"\n"
"/* MAIN */\n"
"QWidget#centralwidget  {\n"
"	background-color: black;\n"
"}\n"
"/* ----- */\n"
"\n"
"\n"
"/* DIALOG */\n"
"QDialogButtonBox QPushButton {\n"
"	padding-left: 		10px;\n"
"	padding-right: 	10px;\n"
"	min-height:			25px;\n"
"	margin:				5px;\n"
"}\n"
"/* ------ */\n"
""));
        verticalLayout = new QVBoxLayout(UiInspector);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        globalFrame = new QFrame(UiInspector);
        globalFrame->setObjectName(QString::fromUtf8("globalFrame"));
        globalFrame->setFrameShape(QFrame::StyledPanel);
        globalFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(globalFrame);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(3, 3, 3, 3);
        tab = new QTabWidget(globalFrame);
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setIconSize(QSize(24, 24));
        tabProject = new QWidget();
        tabProject->setObjectName(QString::fromUtf8("tabProject"));
        verticalLayout_13 = new QVBoxLayout(tabProject);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(6, 6, 6, 6);
        files = new UiTreeView(tabProject);
        files->setObjectName(QString::fromUtf8("files"));
        files->setMinimumSize(QSize(0, 150));

        verticalLayout_13->addWidget(files);

        QIcon icon;
        icon.addFile(QString::fromUtf8(":/general/res_icon_inspector_project.png"), QSize(), QIcon::Normal, QIcon::Off);
        tab->addTab(tabProject, icon, QString());
        tabInfo = new QWidget();
        tabInfo->setObjectName(QString::fromUtf8("tabInfo"));
        verticalLayout_3 = new QVBoxLayout(tabInfo);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(6, 6, 6, 6);
        typeLabel = new QLabel(tabInfo);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(typeLabel->sizePolicy().hasHeightForWidth());
        typeLabel->setSizePolicy(sizePolicy);
        typeLabel->setStyleSheet(QString::fromUtf8("color: white; font: 12px;"));

        verticalLayout_3->addWidget(typeLabel);

        ssTabInfo = new QTabWidget(tabInfo);
        ssTabInfo->setObjectName(QString::fromUtf8("ssTabInfo"));
        ssTabInfo->setStyleSheet(QString::fromUtf8("QTabBar::tab { min-height: 20px; }\n"
""));
        ssTabInfoGeneral = new QWidget();
        ssTabInfoGeneral->setObjectName(QString::fromUtf8("ssTabInfoGeneral"));
        verticalLayout_17 = new QVBoxLayout(ssTabInfoGeneral);
        verticalLayout_17->setSpacing(3);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(10, 10, 10, 10);
        widgetID = new QWidget(ssTabInfoGeneral);
        widgetID->setObjectName(QString::fromUtf8("widgetID"));
        verticalLayout_20 = new QVBoxLayout(widgetID);
        verticalLayout_20->setSpacing(3);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(10);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        IDLabel = new QLabel(widgetID);
        IDLabel->setObjectName(QString::fromUtf8("IDLabel"));
        IDLabel->setMinimumSize(QSize(100, 20));
        IDLabel->setMaximumSize(QSize(100, 16777215));
        IDLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        IDLabel->setWordWrap(true);

        horizontalLayout_24->addWidget(IDLabel);

        newIdButton = new QPushButton(widgetID);
        newIdButton->setObjectName(QString::fromUtf8("newIdButton"));
        newIdButton->setMinimumSize(QSize(206, 22));
        newIdButton->setMaximumSize(QSize(206, 16777215));

        horizontalLayout_24->addWidget(newIdButton);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_16);


        verticalLayout_20->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(10);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        groupIdLabel = new QLabel(widgetID);
        groupIdLabel->setObjectName(QString::fromUtf8("groupIdLabel"));
        groupIdLabel->setMinimumSize(QSize(100, 20));
        groupIdLabel->setMaximumSize(QSize(100, 16777215));
        groupIdLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupIdLabel->setWordWrap(true);

        horizontalLayout_25->addWidget(groupIdLabel);

        groupIdButton = new QPushButton(widgetID);
        groupIdButton->setObjectName(QString::fromUtf8("groupIdButton"));
        groupIdButton->setMinimumSize(QSize(206, 22));
        groupIdButton->setMaximumSize(QSize(206, 16777215));

        horizontalLayout_25->addWidget(groupIdButton);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_17);


        verticalLayout_20->addLayout(horizontalLayout_25);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(10);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        activityLabel = new QLabel(widgetID);
        activityLabel->setObjectName(QString::fromUtf8("activityLabel"));
        activityLabel->setMinimumSize(QSize(100, 20));
        activityLabel->setMaximumSize(QSize(100, 16777215));
        activityLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        activityLabel->setWordWrap(true);

        horizontalLayout_28->addWidget(activityLabel);

        activityCheck = new QCheckBox(widgetID);
        activityCheck->setObjectName(QString::fromUtf8("activityCheck"));
        activityCheck->setStyleSheet(QString::fromUtf8("padding-left: 2px;"));

        horizontalLayout_28->addWidget(activityCheck);


        verticalLayout_20->addLayout(horizontalLayout_28);


        verticalLayout_17->addWidget(widgetID);

        widgetStyle = new QWidget(ssTabInfoGeneral);
        widgetStyle->setObjectName(QString::fromUtf8("widgetStyle"));
        verticalLayout_12 = new QVBoxLayout(widgetStyle);
        verticalLayout_12->setSpacing(3);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(10);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        sizeLabel2 = new QLabel(widgetStyle);
        sizeLabel2->setObjectName(QString::fromUtf8("sizeLabel2"));
        sizeLabel2->setMinimumSize(QSize(100, 20));
        sizeLabel2->setMaximumSize(QSize(100, 16777215));
        sizeLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sizeLabel2->setWordWrap(true);

        horizontalLayout_26->addWidget(sizeLabel2);

        sizeSpin = new QDoubleSpinBox(widgetStyle);
        sizeSpin->setObjectName(QString::fromUtf8("sizeSpin"));
        sizeSpin->setMinimumSize(QSize(80, 30));
        sizeSpin->setMaximumSize(QSize(80, 16777215));
        sizeSpin->setSuffix(QString::fromUtf8(""));
        sizeSpin->setDecimals(3);
        sizeSpin->setMinimum(0.000000000000000);
        sizeSpin->setMaximum(999999.000000000000000);
        sizeSpin->setSingleStep(0.100000000000000);

        horizontalLayout_26->addWidget(sizeSpin);

        horizontalSpacer_11 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_11);


        verticalLayout_12->addLayout(horizontalLayout_26);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(10);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        labelLabel = new QLabel(widgetStyle);
        labelLabel->setObjectName(QString::fromUtf8("labelLabel"));
        labelLabel->setMinimumSize(QSize(100, 20));
        labelLabel->setMaximumSize(QSize(100, 16777215));
        labelLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelLabel->setWordWrap(true);

        horizontalLayout_27->addWidget(labelLabel);

        labelLine = new QLineEdit(widgetStyle);
        labelLine->setObjectName(QString::fromUtf8("labelLine"));
        labelLine->setMinimumSize(QSize(200, 30));
        labelLine->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_27->addWidget(labelLine);

        horizontalSpacer_18 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_18);


        verticalLayout_12->addLayout(horizontalLayout_27);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(10);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        colorLabel1 = new QLabel(widgetStyle);
        colorLabel1->setObjectName(QString::fromUtf8("colorLabel1"));
        colorLabel1->setMinimumSize(QSize(100, 20));
        colorLabel1->setMaximumSize(QSize(100, 16777215));
        colorLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        colorLabel1->setWordWrap(true);

        horizontalLayout_32->addWidget(colorLabel1);

        colorCombo1 = new QComboBox(widgetStyle);
        colorCombo1->setObjectName(QString::fromUtf8("colorCombo1"));
        colorCombo1->setMinimumSize(QSize(203, 22));
        colorCombo1->setMaximumSize(QSize(203, 16777215));
        colorCombo1->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView {\n"
"	min-height: 100px;\n"
"}"));
        colorCombo1->setEditable(true);
        colorCombo1->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_32->addWidget(colorCombo1);

        horizontalSpacer_14 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_14);


        verticalLayout_12->addLayout(horizontalLayout_32);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(10);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        colorLabel2 = new QLabel(widgetStyle);
        colorLabel2->setObjectName(QString::fromUtf8("colorLabel2"));
        colorLabel2->setMinimumSize(QSize(100, 20));
        colorLabel2->setMaximumSize(QSize(100, 16777215));
        colorLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        colorLabel2->setWordWrap(true);

        horizontalLayout_31->addWidget(colorLabel2);

        colorCombo2 = new QComboBox(widgetStyle);
        colorCombo2->setObjectName(QString::fromUtf8("colorCombo2"));
        colorCombo2->setMinimumSize(QSize(203, 22));
        colorCombo2->setMaximumSize(QSize(203, 16777215));
        colorCombo2->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView {\n"
"	min-height: 100px;\n"
"}"));
        colorCombo2->setEditable(true);
        colorCombo2->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_31->addWidget(colorCombo2);

        horizontalSpacer_15 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_15);


        verticalLayout_12->addLayout(horizontalLayout_31);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(10);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        colorLabelMultiply = new QLabel(widgetStyle);
        colorLabelMultiply->setObjectName(QString::fromUtf8("colorLabelMultiply"));
        colorLabelMultiply->setMinimumSize(QSize(100, 20));
        colorLabelMultiply->setMaximumSize(QSize(100, 16777215));
        colorLabelMultiply->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        colorLabelMultiply->setWordWrap(true);

        horizontalLayout_33->addWidget(colorLabelMultiply);

        colorComboMultiply = new QComboBox(widgetStyle);
        colorComboMultiply->setObjectName(QString::fromUtf8("colorComboMultiply"));
        colorComboMultiply->setMinimumSize(QSize(203, 22));
        colorComboMultiply->setMaximumSize(QSize(203, 16777215));
        colorComboMultiply->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView {\n"
"	min-height: 100px;\n"
"}"));
        colorComboMultiply->setEditable(true);
        colorComboMultiply->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_33->addWidget(colorComboMultiply);

        horizontalSpacer_21 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_21);


        verticalLayout_12->addLayout(horizontalLayout_33);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(10);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        textureLabel1 = new QLabel(widgetStyle);
        textureLabel1->setObjectName(QString::fromUtf8("textureLabel1"));
        textureLabel1->setMinimumSize(QSize(100, 20));
        textureLabel1->setMaximumSize(QSize(100, 16777215));
        textureLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textureLabel1->setWordWrap(true);

        horizontalLayout_35->addWidget(textureLabel1);

        textureCombo1 = new QComboBox(widgetStyle);
        textureCombo1->setObjectName(QString::fromUtf8("textureCombo1"));
        textureCombo1->setMinimumSize(QSize(203, 22));
        textureCombo1->setMaximumSize(QSize(203, 16777215));
        textureCombo1->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView {\n"
"	min-height: 100px;\n"
"}"));
        textureCombo1->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_35->addWidget(textureCombo1);

        horizontalSpacer_28 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_35->addItem(horizontalSpacer_28);


        verticalLayout_12->addLayout(horizontalLayout_35);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(10);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        textureLabel2 = new QLabel(widgetStyle);
        textureLabel2->setObjectName(QString::fromUtf8("textureLabel2"));
        textureLabel2->setMinimumSize(QSize(100, 20));
        textureLabel2->setMaximumSize(QSize(100, 16777215));
        textureLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textureLabel2->setWordWrap(true);

        horizontalLayout_34->addWidget(textureLabel2);

        textureCombo2 = new QComboBox(widgetStyle);
        textureCombo2->setObjectName(QString::fromUtf8("textureCombo2"));
        textureCombo2->setMinimumSize(QSize(203, 22));
        textureCombo2->setMaximumSize(QSize(203, 16777215));
        textureCombo2->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView {\n"
"	min-height: 100px;\n"
"}"));
        textureCombo2->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_34->addWidget(textureCombo2);

        horizontalSpacer_27 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_27);


        verticalLayout_12->addLayout(horizontalLayout_34);


        verticalLayout_17->addWidget(widgetStyle);

        verticalSpacer_4 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_4);

        ssTabInfo->addTab(ssTabInfoGeneral, QString());
        ssTabInfoSpace = new QWidget();
        ssTabInfoSpace->setObjectName(QString::fromUtf8("ssTabInfoSpace"));
        verticalLayout_9 = new QVBoxLayout(ssTabInfoSpace);
        verticalLayout_9->setSpacing(5);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        positionLabel = new QLabel(ssTabInfoSpace);
        positionLabel->setObjectName(QString::fromUtf8("positionLabel"));
        positionLabel->setMinimumSize(QSize(85, 20));
        positionLabel->setMaximumSize(QSize(85, 16777215));
        positionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        positionLabel->setWordWrap(true);

        horizontalLayout_5->addWidget(positionLabel);

        positionX = new QDoubleSpinBox(ssTabInfoSpace);
        positionX->setObjectName(QString::fromUtf8("positionX"));
        positionX->setMinimumSize(QSize(70, 30));
        positionX->setMaximumSize(QSize(70, 16777215));
        positionX->setSuffix(QString::fromUtf8(" s"));
        positionX->setDecimals(3);
        positionX->setMinimum(-999999.000000000000000);
        positionX->setMaximum(999999.000000000000000);
        positionX->setSingleStep(0.100000000000000);

        horizontalLayout_5->addWidget(positionX);

        positionY = new QDoubleSpinBox(ssTabInfoSpace);
        positionY->setObjectName(QString::fromUtf8("positionY"));
        positionY->setMinimumSize(QSize(70, 30));
        positionY->setMaximumSize(QSize(70, 16777215));
        positionY->setSuffix(QString::fromUtf8(" s"));
        positionY->setDecimals(3);
        positionY->setMinimum(-999999.000000000000000);
        positionY->setMaximum(999999.000000000000000);
        positionY->setSingleStep(0.100000000000000);

        horizontalLayout_5->addWidget(positionY);

        positionZ = new QDoubleSpinBox(ssTabInfoSpace);
        positionZ->setObjectName(QString::fromUtf8("positionZ"));
        positionZ->setMinimumSize(QSize(70, 30));
        positionZ->setMaximumSize(QSize(70, 16777215));
        positionZ->setSuffix(QString::fromUtf8(" s"));
        positionZ->setDecimals(3);
        positionZ->setMinimum(-999999.000000000000000);
        positionZ->setMaximum(999999.000000000000000);
        positionZ->setSingleStep(0.100000000000000);

        horizontalLayout_5->addWidget(positionZ);

        horizontalSpacer_8 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout_9->addLayout(horizontalLayout_5);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(10);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        sizeLabel = new QLabel(ssTabInfoSpace);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));
        sizeLabel->setMinimumSize(QSize(85, 20));
        sizeLabel->setMaximumSize(QSize(85, 16777215));
        sizeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        sizeLabel->setWordWrap(true);

        horizontalLayout_16->addWidget(sizeLabel);

        sizeWSpin = new QDoubleSpinBox(ssTabInfoSpace);
        sizeWSpin->setObjectName(QString::fromUtf8("sizeWSpin"));
        sizeWSpin->setMinimumSize(QSize(70, 30));
        sizeWSpin->setMaximumSize(QSize(70, 16777215));
        sizeWSpin->setSuffix(QString::fromUtf8(" s"));
        sizeWSpin->setDecimals(3);
        sizeWSpin->setMinimum(0.000000000000000);
        sizeWSpin->setMaximum(999999.000000000000000);
        sizeWSpin->setSingleStep(0.100000000000000);

        horizontalLayout_16->addWidget(sizeWSpin);

        sizeHSpin = new QDoubleSpinBox(ssTabInfoSpace);
        sizeHSpin->setObjectName(QString::fromUtf8("sizeHSpin"));
        sizeHSpin->setMinimumSize(QSize(70, 30));
        sizeHSpin->setMaximumSize(QSize(70, 16777215));
        sizeHSpin->setSuffix(QString::fromUtf8(" s"));
        sizeHSpin->setDecimals(3);
        sizeHSpin->setMinimum(0.000000000000000);
        sizeHSpin->setMaximum(999999.000000000000000);
        sizeHSpin->setSingleStep(0.100000000000000);

        horizontalLayout_16->addWidget(sizeHSpin);

        horizontalSpacer_9 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_9);


        verticalLayout_9->addLayout(horizontalLayout_16);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(10);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        intertiaLabel = new QLabel(ssTabInfoSpace);
        intertiaLabel->setObjectName(QString::fromUtf8("intertiaLabel"));
        intertiaLabel->setMinimumSize(QSize(85, 20));
        intertiaLabel->setMaximumSize(QSize(85, 16777215));
        intertiaLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        intertiaLabel->setWordWrap(true);

        horizontalLayout_38->addWidget(intertiaLabel);

        intertiaSpin = new QDoubleSpinBox(ssTabInfoSpace);
        intertiaSpin->setObjectName(QString::fromUtf8("intertiaSpin"));
        intertiaSpin->setMinimumSize(QSize(70, 30));
        intertiaSpin->setMaximumSize(QSize(70, 16777215));
        intertiaSpin->setSuffix(QString::fromUtf8(""));
        intertiaSpin->setDecimals(2);
        intertiaSpin->setMinimum(0.000000000000000);
        intertiaSpin->setMaximum(999999.000000000000000);
        intertiaSpin->setSingleStep(0.100000000000000);

        horizontalLayout_38->addWidget(intertiaSpin);

        horizontalSpacer_22 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_22);


        verticalLayout_9->addLayout(horizontalLayout_38);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(10);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        widthLabel = new QLabel(ssTabInfoSpace);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));
        widthLabel->setMinimumSize(QSize(85, 20));
        widthLabel->setMaximumSize(QSize(85, 16777215));
        widthLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widthLabel->setWordWrap(true);

        horizontalLayout_18->addWidget(widthLabel);

        widthSpin = new QDoubleSpinBox(ssTabInfoSpace);
        widthSpin->setObjectName(QString::fromUtf8("widthSpin"));
        widthSpin->setMinimumSize(QSize(70, 30));
        widthSpin->setMaximumSize(QSize(70, 16777215));
        widthSpin->setSuffix(QString::fromUtf8(" s"));
        widthSpin->setDecimals(3);
        widthSpin->setMaximum(999999.000000000000000);
        widthSpin->setSingleStep(0.100000000000000);

        horizontalLayout_18->addWidget(widthSpin);

        depthSpin = new QDoubleSpinBox(ssTabInfoSpace);
        depthSpin->setObjectName(QString::fromUtf8("depthSpin"));
        depthSpin->setMinimumSize(QSize(70, 30));
        depthSpin->setMaximumSize(QSize(70, 16777215));
        depthSpin->setSuffix(QString::fromUtf8(" s"));
        depthSpin->setDecimals(3);
        depthSpin->setMaximum(999999.000000000000000);
        depthSpin->setSingleStep(0.100000000000000);

        horizontalLayout_18->addWidget(depthSpin);

        horizontalSpacer_25 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_25);


        verticalLayout_9->addLayout(horizontalLayout_18);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(10);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        pointsLabel = new QLabel(ssTabInfoSpace);
        pointsLabel->setObjectName(QString::fromUtf8("pointsLabel"));
        pointsLabel->setMinimumSize(QSize(85, 20));
        pointsLabel->setMaximumSize(QSize(85, 16777215));
        pointsLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pointsLabel->setWordWrap(true);

        horizontalLayout_17->addWidget(pointsLabel);

        pointsResample = new QPushButton(ssTabInfoSpace);
        pointsResample->setObjectName(QString::fromUtf8("pointsResample"));
        pointsResample->setMinimumSize(QSize(103, 22));

        horizontalLayout_17->addWidget(pointsResample);

        pointsLists = new QPushButton(ssTabInfoSpace);
        pointsLists->setObjectName(QString::fromUtf8("pointsLists"));
        pointsLists->setMinimumSize(QSize(103, 22));

        horizontalLayout_17->addWidget(pointsLists);

        horizontalSpacer_7 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_7);


        verticalLayout_9->addLayout(horizontalLayout_17);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(-1, -1, -1, 0);
        equationTemplate = new QComboBox(ssTabInfoSpace);
        equationTemplate->addItem(QString());
        equationTemplate->setObjectName(QString::fromUtf8("equationTemplate"));
        equationTemplate->setMinimumSize(QSize(203, 22));
        equationTemplate->setMaximumSize(QSize(203, 16777215));
        equationTemplate->setStyleSheet(QString::fromUtf8("QComboBox QAbstractItemView {\n"
"	min-height: 100px;\n"
"}"));

        gridLayout->addWidget(equationTemplate, 0, 1, 1, 2);

        verticalSpacer_9 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_9, 1, 1, 1, 1);

        horizontalSpacer_26 = new QSpacerItem(35, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_26, 4, 2, 1, 1);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_24, 2, 2, 1, 1);

        equationLabel = new QLabel(ssTabInfoSpace);
        equationLabel->setObjectName(QString::fromUtf8("equationLabel"));
        equationLabel->setMinimumSize(QSize(85, 20));
        equationLabel->setMaximumSize(QSize(85, 16777215));
        equationLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equationLabel->setWordWrap(true);

        gridLayout->addWidget(equationLabel, 2, 0, 5, 1);

        equationEdit = new QPlainTextEdit(ssTabInfoSpace);
        equationEdit->setObjectName(QString::fromUtf8("equationEdit"));
        equationEdit->setMinimumSize(QSize(0, 30));
        equationEdit->setMaximumSize(QSize(16777215, 120));

        gridLayout->addWidget(equationEdit, 6, 1, 1, 2);

        equationType = new QWidget(ssTabInfoSpace);
        equationType->setObjectName(QString::fromUtf8("equationType"));
        verticalLayout_8 = new QVBoxLayout(equationType);
        verticalLayout_8->setSpacing(5);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        equationType0 = new QRadioButton(equationType);
        equationType0->setObjectName(QString::fromUtf8("equationType0"));
        equationType0->setChecked(true);

        verticalLayout_8->addWidget(equationType0);

        equationType1 = new QRadioButton(equationType);
        equationType1->setObjectName(QString::fromUtf8("equationType1"));

        verticalLayout_8->addWidget(equationType1);


        gridLayout->addWidget(equationType, 2, 1, 1, 1);

        frame = new QFrame(ssTabInfoSpace);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 50));
        frame->setStyleSheet(QString::fromUtf8("QFrame#frame {\n"
"	border: 0px solid black;\n"
"}\n"
"QWidget {\n"
"	padding-top: 0px;\n"
"	padding-bottom: 0px;\n"
"	margin-top: -2px;\n"
"	margin-bottom: -2px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_24 = new QVBoxLayout(frame);
        verticalLayout_24->setSpacing(0);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(10);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        equationParam1Label = new QLabel(frame);
        equationParam1Label->setObjectName(QString::fromUtf8("equationParam1Label"));
        equationParam1Label->setMinimumSize(QSize(45, 16));
        equationParam1Label->setMaximumSize(QSize(54, 16777215));
        equationParam1Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equationParam1Label->setWordWrap(true);

        horizontalLayout_8->addWidget(equationParam1Label);

        equationParam1Slider = new QSlider(frame);
        equationParam1Slider->setObjectName(QString::fromUtf8("equationParam1Slider"));
        equationParam1Slider->setMaximum(1000);
        equationParam1Slider->setPageStep(50);
        equationParam1Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(equationParam1Slider);

        equationParam1Value = new QDoubleSpinBox(frame);
        equationParam1Value->setObjectName(QString::fromUtf8("equationParam1Value"));
        equationParam1Value->setMinimumSize(QSize(50, 18));
        equationParam1Value->setMaximumSize(QSize(50, 16777215));
        equationParam1Value->setStyleSheet(QString::fromUtf8(""));
        equationParam1Value->setDecimals(3);
        equationParam1Value->setMinimum(-999999.000000000000000);
        equationParam1Value->setMaximum(999999.000000000000000);
        equationParam1Value->setSingleStep(0.100000000000000);

        horizontalLayout_8->addWidget(equationParam1Value);


        verticalLayout_24->addLayout(horizontalLayout_8);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(10);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        equationParam2Label = new QLabel(frame);
        equationParam2Label->setObjectName(QString::fromUtf8("equationParam2Label"));
        equationParam2Label->setMinimumSize(QSize(45, 16));
        equationParam2Label->setMaximumSize(QSize(54, 16777215));
        equationParam2Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equationParam2Label->setWordWrap(true);

        horizontalLayout_29->addWidget(equationParam2Label);

        equationParam2Slider = new QSlider(frame);
        equationParam2Slider->setObjectName(QString::fromUtf8("equationParam2Slider"));
        equationParam2Slider->setMaximum(1000);
        equationParam2Slider->setPageStep(50);
        equationParam2Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_29->addWidget(equationParam2Slider);

        equationParam2Value = new QDoubleSpinBox(frame);
        equationParam2Value->setObjectName(QString::fromUtf8("equationParam2Value"));
        equationParam2Value->setMinimumSize(QSize(50, 18));
        equationParam2Value->setMaximumSize(QSize(50, 16777215));
        equationParam2Value->setDecimals(3);
        equationParam2Value->setMinimum(-999999.000000000000000);
        equationParam2Value->setMaximum(999999.000000000000000);
        equationParam2Value->setSingleStep(0.100000000000000);

        horizontalLayout_29->addWidget(equationParam2Value);


        verticalLayout_24->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(10);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        equationParam3Label = new QLabel(frame);
        equationParam3Label->setObjectName(QString::fromUtf8("equationParam3Label"));
        equationParam3Label->setMinimumSize(QSize(45, 16));
        equationParam3Label->setMaximumSize(QSize(54, 16777215));
        equationParam3Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equationParam3Label->setWordWrap(true);

        horizontalLayout_30->addWidget(equationParam3Label);

        equationParam3Slider = new QSlider(frame);
        equationParam3Slider->setObjectName(QString::fromUtf8("equationParam3Slider"));
        equationParam3Slider->setMaximum(1000);
        equationParam3Slider->setPageStep(50);
        equationParam3Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_30->addWidget(equationParam3Slider);

        equationParam3Value = new QDoubleSpinBox(frame);
        equationParam3Value->setObjectName(QString::fromUtf8("equationParam3Value"));
        equationParam3Value->setMinimumSize(QSize(50, 18));
        equationParam3Value->setMaximumSize(QSize(50, 16777215));
        equationParam3Value->setDecimals(3);
        equationParam3Value->setMinimum(-999999.000000000000000);
        equationParam3Value->setMaximum(999999.000000000000000);
        equationParam3Value->setSingleStep(0.100000000000000);

        horizontalLayout_30->addWidget(equationParam3Value);


        verticalLayout_24->addLayout(horizontalLayout_30);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(10);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        equationParam4Label = new QLabel(frame);
        equationParam4Label->setObjectName(QString::fromUtf8("equationParam4Label"));
        equationParam4Label->setMinimumSize(QSize(45, 16));
        equationParam4Label->setMaximumSize(QSize(54, 16777215));
        equationParam4Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equationParam4Label->setWordWrap(true);

        horizontalLayout_36->addWidget(equationParam4Label);

        equationParam4Slider = new QSlider(frame);
        equationParam4Slider->setObjectName(QString::fromUtf8("equationParam4Slider"));
        equationParam4Slider->setMaximum(1000);
        equationParam4Slider->setPageStep(50);
        equationParam4Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_36->addWidget(equationParam4Slider);

        equationParam4Value = new QDoubleSpinBox(frame);
        equationParam4Value->setObjectName(QString::fromUtf8("equationParam4Value"));
        equationParam4Value->setMinimumSize(QSize(50, 18));
        equationParam4Value->setMaximumSize(QSize(50, 16777215));
        equationParam4Value->setDecimals(3);
        equationParam4Value->setMinimum(-999999.000000000000000);
        equationParam4Value->setMaximum(999999.000000000000000);
        equationParam4Value->setSingleStep(0.100000000000000);

        horizontalLayout_36->addWidget(equationParam4Value);


        verticalLayout_24->addLayout(horizontalLayout_36);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(10);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        equationParam5Label = new QLabel(frame);
        equationParam5Label->setObjectName(QString::fromUtf8("equationParam5Label"));
        equationParam5Label->setMinimumSize(QSize(45, 16));
        equationParam5Label->setMaximumSize(QSize(54, 16777215));
        equationParam5Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        equationParam5Label->setWordWrap(true);

        horizontalLayout_37->addWidget(equationParam5Label);

        equationParam5Slider = new QSlider(frame);
        equationParam5Slider->setObjectName(QString::fromUtf8("equationParam5Slider"));
        equationParam5Slider->setMaximum(1000);
        equationParam5Slider->setPageStep(50);
        equationParam5Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_37->addWidget(equationParam5Slider);

        equationParam5Value = new QDoubleSpinBox(frame);
        equationParam5Value->setObjectName(QString::fromUtf8("equationParam5Value"));
        equationParam5Value->setMinimumSize(QSize(50, 18));
        equationParam5Value->setMaximumSize(QSize(50, 16777215));
        equationParam5Value->setDecimals(3);
        equationParam5Value->setMinimum(-999999.000000000000000);
        equationParam5Value->setMaximum(999999.000000000000000);
        equationParam5Value->setSingleStep(0.100000000000000);

        horizontalLayout_37->addWidget(equationParam5Value);


        verticalLayout_24->addLayout(horizontalLayout_37);

        equationParamReset = new QPushButton(frame);
        equationParamReset->setObjectName(QString::fromUtf8("equationParamReset"));
        equationParamReset->setStyleSheet(QString::fromUtf8("margin-top:5px;\n"
"margin-bottom:0px;"));

        verticalLayout_24->addWidget(equationParamReset);


        gridLayout->addWidget(frame, 7, 1, 1, 2);

        equationPoints = new QSpinBox(ssTabInfoSpace);
        equationPoints->setObjectName(QString::fromUtf8("equationPoints"));
        equationPoints->setMinimumSize(QSize(203, 30));
        equationPoints->setMaximumSize(QSize(203, 16777215));
        equationPoints->setMinimum(2);
        equationPoints->setMaximum(9999);

        gridLayout->addWidget(equationPoints, 4, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer);

        ssTabInfo->addTab(ssTabInfoSpace, QString());
        ssTabInfoTime = new QWidget();
        ssTabInfoTime->setObjectName(QString::fromUtf8("ssTabInfoTime"));
        verticalLayout_16 = new QVBoxLayout(ssTabInfoTime);
        verticalLayout_16->setSpacing(3);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(10);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        triggerOffLabel = new QLabel(ssTabInfoTime);
        triggerOffLabel->setObjectName(QString::fromUtf8("triggerOffLabel"));
        triggerOffLabel->setMinimumSize(QSize(85, 20));
        triggerOffLabel->setMaximumSize(QSize(85, 16777215));
        triggerOffLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        triggerOffLabel->setWordWrap(true);

        horizontalLayout_15->addWidget(triggerOffLabel);

        triggerOffSpin = new QDoubleSpinBox(ssTabInfoTime);
        triggerOffSpin->setObjectName(QString::fromUtf8("triggerOffSpin"));
        triggerOffSpin->setMinimumSize(QSize(80, 30));
        triggerOffSpin->setMaximumSize(QSize(80, 16777215));
        triggerOffSpin->setSuffix(QString::fromUtf8(" s"));
        triggerOffSpin->setDecimals(3);
        triggerOffSpin->setMaximum(999999.000000000000000);
        triggerOffSpin->setSingleStep(0.100000000000000);

        horizontalLayout_15->addWidget(triggerOffSpin);

        horizontalSpacer_6 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_6);


        verticalLayout_16->addLayout(horizontalLayout_15);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(10);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        cursorSpeedLabel = new QLabel(ssTabInfoTime);
        cursorSpeedLabel->setObjectName(QString::fromUtf8("cursorSpeedLabel"));
        cursorSpeedLabel->setMinimumSize(QSize(85, 20));
        cursorSpeedLabel->setMaximumSize(QSize(85, 16777215));
        cursorSpeedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cursorSpeedLabel->setWordWrap(true);

        horizontalLayout_21->addWidget(cursorSpeedLabel);

        speedSpin = new QDoubleSpinBox(ssTabInfoTime);
        speedSpin->setObjectName(QString::fromUtf8("speedSpin"));
        speedSpin->setMinimumSize(QSize(60, 30));
        speedSpin->setMaximumSize(QSize(60, 16777215));
        speedSpin->setSuffix(QString::fromUtf8(""));
        speedSpin->setDecimals(3);
        speedSpin->setMinimum(-999999.000000000000000);
        speedSpin->setMaximum(999999.000000000000000);
        speedSpin->setSingleStep(0.100000000000000);

        horizontalLayout_21->addWidget(speedSpin);

        cursorSpeedLabel_2 = new QLabel(ssTabInfoTime);
        cursorSpeedLabel_2->setObjectName(QString::fromUtf8("cursorSpeedLabel_2"));
        cursorSpeedLabel_2->setMinimumSize(QSize(10, 20));
        cursorSpeedLabel_2->setMaximumSize(QSize(10, 16777215));
        cursorSpeedLabel_2->setText(QString::fromUtf8("="));

        horizontalLayout_21->addWidget(cursorSpeedLabel_2);

        cursorLengthSpin = new QDoubleSpinBox(ssTabInfoTime);
        cursorLengthSpin->setObjectName(QString::fromUtf8("cursorLengthSpin"));
        cursorLengthSpin->setMinimumSize(QSize(60, 30));
        cursorLengthSpin->setMaximumSize(QSize(60, 16777215));
        cursorLengthSpin->setSuffix(QString::fromUtf8(" s"));
        cursorLengthSpin->setDecimals(3);
        cursorLengthSpin->setMinimum(-999999.000000000000000);
        cursorLengthSpin->setMaximum(999999.000000000000000);
        cursorLengthSpin->setSingleStep(0.100000000000000);

        horizontalLayout_21->addWidget(cursorLengthSpin);

        cursorSpeedLock = new QCheckBox(ssTabInfoTime);
        cursorSpeedLock->setObjectName(QString::fromUtf8("cursorSpeedLock"));
        cursorSpeedLock->setChecked(false);

        horizontalLayout_21->addWidget(cursorSpeedLock);

        horizontalSpacer_3 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_3);


        verticalLayout_16->addLayout(horizontalLayout_21);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(10);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        speedFLabel = new QLabel(ssTabInfoTime);
        speedFLabel->setObjectName(QString::fromUtf8("speedFLabel"));
        speedFLabel->setMinimumSize(QSize(85, 20));
        speedFLabel->setMaximumSize(QSize(85, 16777215));
        speedFLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        speedFLabel->setWordWrap(true);

        horizontalLayout_23->addWidget(speedFLabel);

        speedFSpin = new QDoubleSpinBox(ssTabInfoTime);
        speedFSpin->setObjectName(QString::fromUtf8("speedFSpin"));
        speedFSpin->setMinimumSize(QSize(80, 30));
        speedFSpin->setMaximumSize(QSize(80, 16777215));
        speedFSpin->setSuffix(QString::fromUtf8(""));
        speedFSpin->setDecimals(3);
        speedFSpin->setMinimum(-999999.000000000000000);
        speedFSpin->setMaximum(999999.000000000000000);
        speedFSpin->setSingleStep(0.100000000000000);

        horizontalLayout_23->addWidget(speedFSpin);

        horizontalSpacer_10 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_10);


        verticalLayout_16->addLayout(horizontalLayout_23);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(10);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        patternLabel = new QLabel(ssTabInfoTime);
        patternLabel->setObjectName(QString::fromUtf8("patternLabel"));
        patternLabel->setMinimumSize(QSize(85, 20));
        patternLabel->setMaximumSize(QSize(85, 16777215));
        patternLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        patternLabel->setWordWrap(true);

        horizontalLayout_19->addWidget(patternLabel);

        patternLine = new QComboBox(ssTabInfoTime);
        patternLine->addItem(QString());
        patternLine->addItem(QString());
        patternLine->addItem(QString());
        patternLine->addItem(QString());
        patternLine->addItem(QString());
        patternLine->setObjectName(QString::fromUtf8("patternLine"));
        patternLine->setMinimumSize(QSize(200, 22));
        patternLine->setMaximumSize(QSize(200, 16777215));
        patternLine->setEditable(true);
        patternLine->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_19->addWidget(patternLine);

        horizontalSpacer_12 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_12);


        verticalLayout_16->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(10);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        easingLabel = new QLabel(ssTabInfoTime);
        easingLabel->setObjectName(QString::fromUtf8("easingLabel"));
        easingLabel->setMinimumSize(QSize(85, 20));
        easingLabel->setMaximumSize(QSize(85, 16777215));
        easingLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        easingLabel->setWordWrap(true);

        horizontalLayout_20->addWidget(easingLabel);

        easingCombo = new QComboBox(ssTabInfoTime);
        easingCombo->setObjectName(QString::fromUtf8("easingCombo"));
        easingCombo->setMinimumSize(QSize(200, 22));
        easingCombo->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_20->addWidget(easingCombo);

        horizontalSpacer_13 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_13);


        verticalLayout_16->addLayout(horizontalLayout_20);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(10);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        fireTriggersLabel = new QLabel(ssTabInfoTime);
        fireTriggersLabel->setObjectName(QString::fromUtf8("fireTriggersLabel"));
        fireTriggersLabel->setMinimumSize(QSize(85, 20));
        fireTriggersLabel->setMaximumSize(QSize(85, 16777215));
        fireTriggersLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        fireTriggersLabel->setWordWrap(true);

        horizontalLayout_39->addWidget(fireTriggersLabel);

        fireTriggers = new QComboBox(ssTabInfoTime);
        fireTriggers->addItem(QString());
        fireTriggers->addItem(QString());
        fireTriggers->addItem(QString());
        fireTriggers->setObjectName(QString::fromUtf8("fireTriggers"));
        fireTriggers->setMinimumSize(QSize(200, 22));
        fireTriggers->setMaximumSize(QSize(200, 16777215));
        fireTriggers->setEditable(true);
        fireTriggers->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_39->addWidget(fireTriggers);

        horizontalSpacer_29 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_29);


        verticalLayout_16->addLayout(horizontalLayout_39);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(10);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        offsetLabel = new QLabel(ssTabInfoTime);
        offsetLabel->setObjectName(QString::fromUtf8("offsetLabel"));
        offsetLabel->setMinimumSize(QSize(85, 20));
        offsetLabel->setMaximumSize(QSize(85, 16777215));
        offsetLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        offsetLabel->setWordWrap(true);

        horizontalLayout_22->addWidget(offsetLabel);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(0);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        offsetLabel1 = new QLabel(ssTabInfoTime);
        offsetLabel1->setObjectName(QString::fromUtf8("offsetLabel1"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(offsetLabel1->sizePolicy().hasHeightForWidth());
        offsetLabel1->setSizePolicy(sizePolicy1);
        offsetLabel1->setMinimumSize(QSize(75, 20));
        offsetLabel1->setMaximumSize(QSize(130, 16777215));

        horizontalLayout_3->addWidget(offsetLabel1);

        offsetInitialSpin = new QDoubleSpinBox(ssTabInfoTime);
        offsetInitialSpin->setObjectName(QString::fromUtf8("offsetInitialSpin"));
        offsetInitialSpin->setMinimumSize(QSize(60, 30));
        offsetInitialSpin->setMaximumSize(QSize(80, 16777215));
        offsetInitialSpin->setSuffix(QString::fromUtf8(" s"));
        offsetInitialSpin->setDecimals(3);
        offsetInitialSpin->setMinimum(-999999.000000000000000);
        offsetInitialSpin->setMaximum(999999.000000000000000);
        offsetInitialSpin->setSingleStep(0.100000000000000);

        horizontalLayout_3->addWidget(offsetInitialSpin);

        offsetLabel2_2 = new QLabel(ssTabInfoTime);
        offsetLabel2_2->setObjectName(QString::fromUtf8("offsetLabel2_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(offsetLabel2_2->sizePolicy().hasHeightForWidth());
        offsetLabel2_2->setSizePolicy(sizePolicy2);
        offsetLabel2_2->setMinimumSize(QSize(35, 20));
        offsetLabel2_2->setMaximumSize(QSize(35, 16777215));
        offsetLabel2_2->setWordWrap(false);

        horizontalLayout_3->addWidget(offsetLabel2_2);

        horizontalSpacer_5 = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_15->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        offsetLabel2 = new QLabel(ssTabInfoTime);
        offsetLabel2->setObjectName(QString::fromUtf8("offsetLabel2"));
        sizePolicy2.setHeightForWidth(offsetLabel2->sizePolicy().hasHeightForWidth());
        offsetLabel2->setSizePolicy(sizePolicy2);
        offsetLabel2->setMinimumSize(QSize(70, 20));
        offsetLabel2->setMaximumSize(QSize(60, 16777215));
        offsetLabel2->setWordWrap(false);

        horizontalLayout_2->addWidget(offsetLabel2);

        offsetStartSpin = new QDoubleSpinBox(ssTabInfoTime);
        offsetStartSpin->setObjectName(QString::fromUtf8("offsetStartSpin"));
        offsetStartSpin->setMinimumSize(QSize(60, 30));
        offsetStartSpin->setMaximumSize(QSize(80, 16777215));
        offsetStartSpin->setSuffix(QString::fromUtf8(" s"));
        offsetStartSpin->setDecimals(3);
        offsetStartSpin->setMinimum(-999999.000000000000000);
        offsetStartSpin->setMaximum(999999.000000000000000);
        offsetStartSpin->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(offsetStartSpin);

        offsetLabel3 = new QLabel(ssTabInfoTime);
        offsetLabel3->setObjectName(QString::fromUtf8("offsetLabel3"));
        offsetLabel3->setMinimumSize(QSize(20, 20));
        offsetLabel3->setMaximumSize(QSize(20, 16777215));
        offsetLabel3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(offsetLabel3);

        offsetEndSpin = new QDoubleSpinBox(ssTabInfoTime);
        offsetEndSpin->setObjectName(QString::fromUtf8("offsetEndSpin"));
        offsetEndSpin->setMinimumSize(QSize(60, 30));
        offsetEndSpin->setMaximumSize(QSize(80, 16777215));
        offsetEndSpin->setSuffix(QString::fromUtf8("s"));
        offsetEndSpin->setDecimals(3);
        offsetEndSpin->setMinimum(0.000000000000000);
        offsetEndSpin->setMaximum(9999999.000000000000000);
        offsetEndSpin->setSingleStep(0.100000000000000);

        horizontalLayout_2->addWidget(offsetEndSpin);

        horizontalSpacer = new QSpacerItem(40, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_15->addLayout(horizontalLayout_2);


        horizontalLayout_22->addLayout(verticalLayout_15);


        verticalLayout_16->addLayout(horizontalLayout_22);

        verticalSpacer_3 = new QSpacerItem(20, 96, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_3);

        ssTabInfo->addTab(ssTabInfoTime, QString());
        ssTabInfoMessage = new QWidget();
        ssTabInfoMessage->setObjectName(QString::fromUtf8("ssTabInfoMessage"));
        verticalLayout_5 = new QVBoxLayout(ssTabInfoMessage);
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(20);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        messagesButton = new QPushButton(ssTabInfoMessage);
        messagesButton->setObjectName(QString::fromUtf8("messagesButton"));
        messagesButton->setMinimumSize(QSize(120, 22));
        messagesButton->setMaximumSize(QSize(120, 16777215));
        messagesButton->setStyleSheet(QString::fromUtf8("margin: 0px;"));

        horizontalLayout_12->addWidget(messagesButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_2);

        messagesSpin = new QDoubleSpinBox(ssTabInfoMessage);
        messagesSpin->setObjectName(QString::fromUtf8("messagesSpin"));
        messagesSpin->setMinimumSize(QSize(160, 30));
        messagesSpin->setMaximumSize(QSize(80, 16777215));
        messagesSpin->setSuffix(QString::fromUtf8(" ms"));
        messagesSpin->setDecimals(0);
        messagesSpin->setMinimum(0.000000000000000);
        messagesSpin->setMaximum(999999.000000000000000);
        messagesSpin->setSingleStep(1.000000000000000);
        messagesSpin->setValue(0.000000000000000);

        horizontalLayout_12->addWidget(messagesSpin);


        verticalLayout_5->addLayout(horizontalLayout_12);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(10);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 0, -1, -1);
        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_6);

        cursorSourceMode = new QWidget(ssTabInfoMessage);
        cursorSourceMode->setObjectName(QString::fromUtf8("cursorSourceMode"));
        verticalLayout_11 = new QVBoxLayout(cursorSourceMode);
        verticalLayout_11->setSpacing(5);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        cursorSourceMode0 = new QRadioButton(cursorSourceMode);
        cursorSourceMode0->setObjectName(QString::fromUtf8("cursorSourceMode0"));

        verticalLayout_11->addWidget(cursorSourceMode0);

        cursorSourceMode1 = new QRadioButton(cursorSourceMode);
        cursorSourceMode1->setObjectName(QString::fromUtf8("cursorSourceMode1"));

        verticalLayout_11->addWidget(cursorSourceMode1);

        cursorSourceMode2 = new QRadioButton(cursorSourceMode);
        cursorSourceMode2->setObjectName(QString::fromUtf8("cursorSourceMode2"));

        verticalLayout_11->addWidget(cursorSourceMode2);

        cursorSourceMode3 = new QRadioButton(cursorSourceMode);
        cursorSourceMode3->setObjectName(QString::fromUtf8("cursorSourceMode3"));

        verticalLayout_11->addWidget(cursorSourceMode3);


        verticalLayout_4->addWidget(cursorSourceMode);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(5);
        gridLayout_5->setVerticalSpacing(0);
        gridLayout_5->setContentsMargins(-1, -1, -1, 5);
        cursorTargetLabel1 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel1->setObjectName(QString::fromUtf8("cursorTargetLabel1"));
        cursorTargetLabel1->setMinimumSize(QSize(100, 20));
        cursorTargetLabel1->setMaximumSize(QSize(100, 16777215));
        cursorTargetLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(cursorTargetLabel1, 0, 0, 1, 1);

        cursorSourceX1 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorSourceX1->setObjectName(QString::fromUtf8("cursorSourceX1"));
        cursorSourceX1->setMinimumSize(QSize(60, 30));
        cursorSourceX1->setMaximumSize(QSize(60, 16777215));
        cursorSourceX1->setSuffix(QString::fromUtf8(" s"));
        cursorSourceX1->setDecimals(3);
        cursorSourceX1->setMinimum(-999999.000000000000000);
        cursorSourceX1->setMaximum(999999.000000000000000);
        cursorSourceX1->setSingleStep(0.100000000000000);

        gridLayout_5->addWidget(cursorSourceX1, 0, 1, 1, 1);

        cursorTargetLabel2 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel2->setObjectName(QString::fromUtf8("cursorTargetLabel2"));
        cursorTargetLabel2->setMinimumSize(QSize(20, 20));
        cursorTargetLabel2->setMaximumSize(QSize(15, 16777215));
        cursorTargetLabel2->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(cursorTargetLabel2, 0, 2, 1, 1);

        cursorSourceX2 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorSourceX2->setObjectName(QString::fromUtf8("cursorSourceX2"));
        cursorSourceX2->setMinimumSize(QSize(60, 30));
        cursorSourceX2->setMaximumSize(QSize(60, 16777215));
        cursorSourceX2->setSuffix(QString::fromUtf8(" s"));
        cursorSourceX2->setDecimals(3);
        cursorSourceX2->setMinimum(-999999.000000000000000);
        cursorSourceX2->setMaximum(999999.000000000000000);
        cursorSourceX2->setSingleStep(0.100000000000000);

        gridLayout_5->addWidget(cursorSourceX2, 0, 3, 1, 1);

        cursorTargetLabel3 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel3->setObjectName(QString::fromUtf8("cursorTargetLabel3"));
        cursorTargetLabel3->setMinimumSize(QSize(100, 20));
        cursorTargetLabel3->setMaximumSize(QSize(100, 16777215));
        cursorTargetLabel3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(cursorTargetLabel3, 1, 0, 1, 1);

        cursorTargetX1 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorTargetX1->setObjectName(QString::fromUtf8("cursorTargetX1"));
        cursorTargetX1->setMinimumSize(QSize(60, 30));
        cursorTargetX1->setMaximumSize(QSize(60, 16777215));
        cursorTargetX1->setSuffix(QString::fromUtf8(""));
        cursorTargetX1->setDecimals(3);
        cursorTargetX1->setMinimum(-999999.000000000000000);
        cursorTargetX1->setMaximum(999999.000000000000000);
        cursorTargetX1->setSingleStep(0.100000000000000);

        gridLayout_5->addWidget(cursorTargetX1, 1, 1, 1, 1);

        cursorTargetLabel4 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel4->setObjectName(QString::fromUtf8("cursorTargetLabel4"));
        cursorTargetLabel4->setMinimumSize(QSize(20, 20));
        cursorTargetLabel4->setMaximumSize(QSize(15, 16777215));
        cursorTargetLabel4->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(cursorTargetLabel4, 1, 2, 1, 1);

        cursorTargetX2 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorTargetX2->setObjectName(QString::fromUtf8("cursorTargetX2"));
        cursorTargetX2->setMinimumSize(QSize(60, 30));
        cursorTargetX2->setMaximumSize(QSize(60, 16777215));
        cursorTargetX2->setSuffix(QString::fromUtf8(""));
        cursorTargetX2->setDecimals(3);
        cursorTargetX2->setMinimum(-999999.000000000000000);
        cursorTargetX2->setMaximum(999999.000000000000000);
        cursorTargetX2->setSingleStep(0.100000000000000);

        gridLayout_5->addWidget(cursorTargetX2, 1, 3, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_19, 1, 4, 1, 1);


        verticalLayout_4->addLayout(gridLayout_5);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(5);
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(-1, -1, -1, 5);
        cursorTargetLabel5 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel5->setObjectName(QString::fromUtf8("cursorTargetLabel5"));
        cursorTargetLabel5->setMinimumSize(QSize(100, 20));
        cursorTargetLabel5->setMaximumSize(QSize(100, 16777215));
        cursorTargetLabel5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(cursorTargetLabel5, 0, 0, 1, 1);

        cursorSourceY2 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorSourceY2->setObjectName(QString::fromUtf8("cursorSourceY2"));
        cursorSourceY2->setMinimumSize(QSize(60, 30));
        cursorSourceY2->setMaximumSize(QSize(60, 16777215));
        cursorSourceY2->setSuffix(QString::fromUtf8(" s"));
        cursorSourceY2->setDecimals(3);
        cursorSourceY2->setMinimum(-999999.000000000000000);
        cursorSourceY2->setMaximum(999999.000000000000000);
        cursorSourceY2->setSingleStep(0.100000000000000);

        gridLayout_4->addWidget(cursorSourceY2, 0, 1, 1, 1);

        cursorTargetLabel6 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel6->setObjectName(QString::fromUtf8("cursorTargetLabel6"));
        cursorTargetLabel6->setMinimumSize(QSize(20, 20));
        cursorTargetLabel6->setMaximumSize(QSize(15, 16777215));
        cursorTargetLabel6->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(cursorTargetLabel6, 0, 2, 1, 1);

        cursorSourceY1 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorSourceY1->setObjectName(QString::fromUtf8("cursorSourceY1"));
        cursorSourceY1->setMinimumSize(QSize(60, 30));
        cursorSourceY1->setMaximumSize(QSize(60, 16777215));
        cursorSourceY1->setSuffix(QString::fromUtf8(" s"));
        cursorSourceY1->setDecimals(3);
        cursorSourceY1->setMinimum(-999999.000000000000000);
        cursorSourceY1->setMaximum(999999.000000000000000);
        cursorSourceY1->setSingleStep(0.100000000000000);

        gridLayout_4->addWidget(cursorSourceY1, 0, 3, 1, 1);

        cursorTargetLabel7 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel7->setObjectName(QString::fromUtf8("cursorTargetLabel7"));
        cursorTargetLabel7->setMinimumSize(QSize(100, 20));
        cursorTargetLabel7->setMaximumSize(QSize(100, 16777215));
        cursorTargetLabel7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(cursorTargetLabel7, 1, 0, 1, 1);

        cursorTargetY2 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorTargetY2->setObjectName(QString::fromUtf8("cursorTargetY2"));
        cursorTargetY2->setMinimumSize(QSize(60, 30));
        cursorTargetY2->setMaximumSize(QSize(60, 16777215));
        cursorTargetY2->setSuffix(QString::fromUtf8(""));
        cursorTargetY2->setDecimals(3);
        cursorTargetY2->setMinimum(-999999.000000000000000);
        cursorTargetY2->setMaximum(999999.000000000000000);
        cursorTargetY2->setSingleStep(0.100000000000000);

        gridLayout_4->addWidget(cursorTargetY2, 1, 1, 1, 1);

        cursorTargetLabel8 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel8->setObjectName(QString::fromUtf8("cursorTargetLabel8"));
        cursorTargetLabel8->setMinimumSize(QSize(20, 20));
        cursorTargetLabel8->setMaximumSize(QSize(15, 16777215));
        cursorTargetLabel8->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(cursorTargetLabel8, 1, 2, 1, 1);

        cursorTargetY1 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorTargetY1->setObjectName(QString::fromUtf8("cursorTargetY1"));
        cursorTargetY1->setMinimumSize(QSize(60, 30));
        cursorTargetY1->setMaximumSize(QSize(60, 16777215));
        cursorTargetY1->setSuffix(QString::fromUtf8(""));
        cursorTargetY1->setDecimals(3);
        cursorTargetY1->setMinimum(-999999.000000000000000);
        cursorTargetY1->setMaximum(999999.000000000000000);
        cursorTargetY1->setSingleStep(0.100000000000000);

        gridLayout_4->addWidget(cursorTargetY1, 1, 3, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_20, 1, 4, 1, 1);


        verticalLayout_4->addLayout(gridLayout_4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(5);
        gridLayout_2->setVerticalSpacing(0);
        cursorTargetLabel11 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel11->setObjectName(QString::fromUtf8("cursorTargetLabel11"));
        cursorTargetLabel11->setMinimumSize(QSize(100, 20));
        cursorTargetLabel11->setMaximumSize(QSize(100, 16777215));
        cursorTargetLabel11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(cursorTargetLabel11, 0, 0, 1, 1);

        cursorSourceZ1 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorSourceZ1->setObjectName(QString::fromUtf8("cursorSourceZ1"));
        cursorSourceZ1->setMinimumSize(QSize(60, 30));
        cursorSourceZ1->setMaximumSize(QSize(60, 16777215));
        cursorSourceZ1->setSuffix(QString::fromUtf8(" s"));
        cursorSourceZ1->setDecimals(3);
        cursorSourceZ1->setMinimum(-999999.000000000000000);
        cursorSourceZ1->setMaximum(999999.000000000000000);
        cursorSourceZ1->setSingleStep(0.100000000000000);

        gridLayout_2->addWidget(cursorSourceZ1, 0, 1, 1, 1);

        cursorTargetLabel13 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel13->setObjectName(QString::fromUtf8("cursorTargetLabel13"));
        cursorTargetLabel13->setMinimumSize(QSize(20, 20));
        cursorTargetLabel13->setMaximumSize(QSize(15, 16777215));
        cursorTargetLabel13->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(cursorTargetLabel13, 0, 2, 1, 1);

        cursorSourceZ2 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorSourceZ2->setObjectName(QString::fromUtf8("cursorSourceZ2"));
        cursorSourceZ2->setMinimumSize(QSize(60, 30));
        cursorSourceZ2->setMaximumSize(QSize(60, 16777215));
        cursorSourceZ2->setSuffix(QString::fromUtf8(" s"));
        cursorSourceZ2->setDecimals(3);
        cursorSourceZ2->setMinimum(-999999.000000000000000);
        cursorSourceZ2->setMaximum(999999.000000000000000);
        cursorSourceZ2->setSingleStep(0.100000000000000);

        gridLayout_2->addWidget(cursorSourceZ2, 0, 3, 1, 1);

        cursorTargetLabel12 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel12->setObjectName(QString::fromUtf8("cursorTargetLabel12"));
        cursorTargetLabel12->setMinimumSize(QSize(100, 20));
        cursorTargetLabel12->setMaximumSize(QSize(100, 16777215));
        cursorTargetLabel12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(cursorTargetLabel12, 1, 0, 1, 1);

        cursorTargetZ1 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorTargetZ1->setObjectName(QString::fromUtf8("cursorTargetZ1"));
        cursorTargetZ1->setMinimumSize(QSize(60, 30));
        cursorTargetZ1->setMaximumSize(QSize(60, 16777215));
        cursorTargetZ1->setSuffix(QString::fromUtf8(""));
        cursorTargetZ1->setDecimals(3);
        cursorTargetZ1->setMinimum(-999999.000000000000000);
        cursorTargetZ1->setMaximum(999999.000000000000000);
        cursorTargetZ1->setSingleStep(0.100000000000000);

        gridLayout_2->addWidget(cursorTargetZ1, 1, 1, 1, 1);

        cursorTargetLabel14 = new QLabel(ssTabInfoMessage);
        cursorTargetLabel14->setObjectName(QString::fromUtf8("cursorTargetLabel14"));
        cursorTargetLabel14->setMinimumSize(QSize(20, 20));
        cursorTargetLabel14->setMaximumSize(QSize(15, 16777215));
        cursorTargetLabel14->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(cursorTargetLabel14, 1, 2, 1, 1);

        cursorTargetZ2 = new QDoubleSpinBox(ssTabInfoMessage);
        cursorTargetZ2->setObjectName(QString::fromUtf8("cursorTargetZ2"));
        cursorTargetZ2->setMinimumSize(QSize(60, 30));
        cursorTargetZ2->setMaximumSize(QSize(60, 16777215));
        cursorTargetZ2->setSuffix(QString::fromUtf8(""));
        cursorTargetZ2->setDecimals(3);
        cursorTargetZ2->setMinimum(-999999.000000000000000);
        cursorTargetZ2->setMaximum(999999.000000000000000);
        cursorTargetZ2->setSingleStep(0.100000000000000);

        gridLayout_2->addWidget(cursorTargetZ2, 1, 3, 1, 1);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_23, 1, 4, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        horizontalLayout_14->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout_14);

        verticalSpacer_2 = new QSpacerItem(20, 93, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        ssTabInfo->addTab(ssTabInfoMessage, QString());
        ssTabRessource = new QWidget();
        ssTabRessource->setObjectName(QString::fromUtf8("ssTabRessource"));
        verticalLayout_14 = new QVBoxLayout(ssTabRessource);
        verticalLayout_14->setSpacing(10);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(10, 10, 10, 10);
        ressourcesTexturesLabel = new QLabel(ssTabRessource);
        ressourcesTexturesLabel->setObjectName(QString::fromUtf8("ressourcesTexturesLabel"));

        verticalLayout_14->addWidget(ressourcesTexturesLabel);

        ressourcesTextures = new UiTreeView(ssTabRessource);
        ressourcesTextures->setObjectName(QString::fromUtf8("ressourcesTextures"));
        ressourcesTextures->setMinimumSize(QSize(0, 150));

        verticalLayout_14->addWidget(ressourcesTextures);

        ressourcesColorsLabel = new QLabel(ssTabRessource);
        ressourcesColorsLabel->setObjectName(QString::fromUtf8("ressourcesColorsLabel"));

        verticalLayout_14->addWidget(ressourcesColorsLabel);

        ressourcesColors = new UiTreeView(ssTabRessource);
        ressourcesColors->setObjectName(QString::fromUtf8("ressourcesColors"));
        ressourcesColors->setMinimumSize(QSize(0, 150));

        verticalLayout_14->addWidget(ressourcesColors);

        verticalSpacer_5 = new QSpacerItem(20, 168, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_5);

        ssTabInfo->addTab(ssTabRessource, QString());

        verticalLayout_3->addWidget(ssTabInfo);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/general/res_icon_inspector_info.png"), QSize(), QIcon::Normal, QIcon::Off);
        tab->addTab(tabInfo, icon1, QString());
        tabView = new QWidget();
        tabView->setObjectName(QString::fromUtf8("tabView"));
        verticalLayout_10 = new QVBoxLayout(tabView);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(6, 6, 6, 6);
        splitter_3 = new QSplitter(tabView);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        layoutWidget4 = new QWidget(splitter_3);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        verticalLayout_7 = new QVBoxLayout(layoutWidget4);
        verticalLayout_7->setSpacing(5);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        ccView = new QTreeWidget(layoutWidget4);
        ccView->setObjectName(QString::fromUtf8("ccView"));
        ccView->setAlternatingRowColors(true);
        ccView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ccView->setSortingEnabled(true);
        ccView->setAnimated(true);
        ccView->header()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout_7->addWidget(ccView);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(15);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        unmuteObjects = new QPushButton(layoutWidget4);
        unmuteObjects->setObjectName(QString::fromUtf8("unmuteObjects"));
        unmuteObjects->setMinimumSize(QSize(0, 22));
        unmuteObjects->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(unmuteObjects);

        unsoloObjects = new QPushButton(layoutWidget4);
        unsoloObjects->setObjectName(QString::fromUtf8("unsoloObjects"));
        unsoloObjects->setMinimumSize(QSize(0, 22));
        unsoloObjects->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(unsoloObjects);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(15);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        unmuteGroups = new QPushButton(layoutWidget4);
        unmuteGroups->setObjectName(QString::fromUtf8("unmuteGroups"));
        unmuteGroups->setMinimumSize(QSize(0, 22));
        unmuteGroups->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(unmuteGroups);

        unsoloGroups = new QPushButton(layoutWidget4);
        unsoloGroups->setObjectName(QString::fromUtf8("unsoloGroups"));
        unsoloGroups->setMinimumSize(QSize(0, 22));
        unsoloGroups->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(unsoloGroups);


        verticalLayout_7->addLayout(horizontalLayout_7);

        splitter_3->addWidget(layoutWidget4);

        verticalLayout_10->addWidget(splitter_3);

        viewCurveOpacityCheck = new QCheckBox(tabView);
        viewCurveOpacityCheck->setObjectName(QString::fromUtf8("viewCurveOpacityCheck"));
        viewCurveOpacityCheck->setChecked(false);

        verticalLayout_10->addWidget(viewCurveOpacityCheck);

        viewCameraModeCheck = new QCheckBox(tabView);
        viewCameraModeCheck->setObjectName(QString::fromUtf8("viewCameraModeCheck"));
        viewCameraModeCheck->setChecked(false);

        verticalLayout_10->addWidget(viewCameraModeCheck);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(10);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        followIdLabel = new QLabel(tabView);
        followIdLabel->setObjectName(QString::fromUtf8("followIdLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(followIdLabel->sizePolicy().hasHeightForWidth());
        followIdLabel->setSizePolicy(sizePolicy3);

        horizontalLayout_9->addWidget(followIdLabel);

        followId = new QSpinBox(tabView);
        followId->setObjectName(QString::fromUtf8("followId"));
        followId->setMinimumSize(QSize(80, 30));
        followId->setMaximumSize(QSize(80, 16777215));
        followId->setMinimum(-1);
        followId->setMaximum(999999);
        followId->setValue(-1);

        horizontalLayout_9->addWidget(followId);

        followIdClear = new QPushButton(tabView);
        followIdClear->setObjectName(QString::fromUtf8("followIdClear"));
        followIdClear->setStyleSheet(QString::fromUtf8("QPushButton  {\n"
"	min-width:  		14px;\n"
"	min-height: 		14px;\n"
"	max-width:  	14px;\n"
"	max-height: 	14px;\n"
"	width:  				14px;\n"
"	height: 			14px;\n"
"	border-radius: 7px;\n"
"	margin: 			0px;\n"
"	padding:			0px;\n"
"}"));

        horizontalLayout_9->addWidget(followIdClear);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_10->addLayout(horizontalLayout_9);

        widget = new QWidget(tabView);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_22 = new QVBoxLayout(widget);
        verticalLayout_22->setSpacing(0);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        autoresizeLabel = new QLabel(widget);
        autoresizeLabel->setObjectName(QString::fromUtf8("autoresizeLabel"));
        autoresizeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_22->addWidget(autoresizeLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        autoresizeLabelLeft = new QLabel(widget);
        autoresizeLabelLeft->setObjectName(QString::fromUtf8("autoresizeLabelLeft"));
        sizePolicy3.setHeightForWidth(autoresizeLabelLeft->sizePolicy().hasHeightForWidth());
        autoresizeLabelLeft->setSizePolicy(sizePolicy3);
        autoresizeLabelLeft->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(autoresizeLabelLeft);

        autoresizeSlider = new QSlider(widget);
        autoresizeSlider->setObjectName(QString::fromUtf8("autoresizeSlider"));
        autoresizeSlider->setMaximum(100);
        autoresizeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(autoresizeSlider);

        autoresizeLabelRight = new QLabel(widget);
        autoresizeLabelRight->setObjectName(QString::fromUtf8("autoresizeLabelRight"));
        sizePolicy3.setHeightForWidth(autoresizeLabelRight->sizePolicy().hasHeightForWidth());
        autoresizeLabelRight->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(autoresizeLabelRight);


        verticalLayout_22->addLayout(horizontalLayout);


        verticalLayout_10->addWidget(widget);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/general/res_icon_inspector_view.png"), QSize(), QIcon::Normal, QIcon::Off);
        tab->addTab(tabView, icon2, QString());
        tabConfig = new QWidget();
        tabConfig->setObjectName(QString::fromUtf8("tabConfig"));
        horizontalLayout_11 = new QHBoxLayout(tabConfig);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(6, 20, 6, 6);
        ssTabConfig = new QTabWidget(tabConfig);
        ssTabConfig->setObjectName(QString::fromUtf8("ssTabConfig"));
        ssTabConfig->setStyleSheet(QString::fromUtf8("QTabBar::tab {\n"
"	min-height: 20px;\n"
"}\n"
""));
        ssTabConfigLog = new QWidget();
        ssTabConfigLog->setObjectName(QString::fromUtf8("ssTabConfigLog"));
        horizontalLayout_10 = new QHBoxLayout(ssTabConfigLog);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(5, 5, 5, 5);
        spaceForMessageLog = new QVBoxLayout();
        spaceForMessageLog->setSpacing(5);
        spaceForMessageLog->setObjectName(QString::fromUtf8("spaceForMessageLog"));

        horizontalLayout_10->addLayout(spaceForMessageLog);

        ssTabConfig->addTab(ssTabConfigLog, QString());
        ssTabConfigNetwork = new QWidget();
        ssTabConfigNetwork->setObjectName(QString::fromUtf8("ssTabConfigNetwork"));
        verticalLayout_19 = new QVBoxLayout(ssTabConfigNetwork);
        verticalLayout_19->setSpacing(0);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(10, 5, 10, 5);
        myIPLabel = new QLabel(ssTabConfigNetwork);
        myIPLabel->setObjectName(QString::fromUtf8("myIPLabel"));

        verticalLayout_19->addWidget(myIPLabel);

        myIP = new QPlainTextEdit(ssTabConfigNetwork);
        myIP->setObjectName(QString::fromUtf8("myIP"));
        myIP->setMinimumSize(QSize(0, 20));
        myIP->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: 0px solid transparent;\n"
"margin: 0px;\n"
"padding: 0px;"));
        myIP->setLineWrapMode(QPlainTextEdit::NoWrap);
        myIP->setReadOnly(true);

        verticalLayout_19->addWidget(myIP);

        ssTabConfigNetworkLayout = new QVBoxLayout();
        ssTabConfigNetworkLayout->setSpacing(5);
        ssTabConfigNetworkLayout->setObjectName(QString::fromUtf8("ssTabConfigNetworkLayout"));

        verticalLayout_19->addLayout(ssTabConfigNetworkLayout);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_19->addItem(verticalSpacer_10);

        ssTabConfig->addTab(ssTabConfigNetwork, QString());
        ssTabConfigMIDI = new QWidget();
        ssTabConfigMIDI->setObjectName(QString::fromUtf8("ssTabConfigMIDI"));
        verticalLayout_18 = new QVBoxLayout(ssTabConfigMIDI);
        verticalLayout_18->setSpacing(10);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(10, 10, 10, 10);
        ssTabConfigMIDILayout = new QVBoxLayout();
        ssTabConfigMIDILayout->setSpacing(20);
        ssTabConfigMIDILayout->setObjectName(QString::fromUtf8("ssTabConfigMIDILayout"));

        verticalLayout_18->addLayout(ssTabConfigMIDILayout);

        verticalSpacer_7 = new QSpacerItem(20, 247, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_7);

        ssTabConfig->addTab(ssTabConfigMIDI, QString());
        ssTabConfigArduino = new QWidget();
        ssTabConfigArduino->setObjectName(QString::fromUtf8("ssTabConfigArduino"));
        verticalLayout_2 = new QVBoxLayout(ssTabConfigArduino);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        ssTabConfigArduinoLayout = new QVBoxLayout();
        ssTabConfigArduinoLayout->setSpacing(20);
        ssTabConfigArduinoLayout->setObjectName(QString::fromUtf8("ssTabConfigArduinoLayout"));

        verticalLayout_2->addLayout(ssTabConfigArduinoLayout);

        verticalSpacer_8 = new QSpacerItem(20, 339, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_8);

        ssTabConfig->addTab(ssTabConfigArduino, QString());
        ssTabConfigSyphon = new QWidget();
        ssTabConfigSyphon->setObjectName(QString::fromUtf8("ssTabConfigSyphon"));
        verticalLayout_21 = new QVBoxLayout(ssTabConfigSyphon);
        verticalLayout_21->setSpacing(10);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(10, 10, 10, 10);
        ssTabConfigSyphonLayout = new QVBoxLayout();
        ssTabConfigSyphonLayout->setSpacing(20);
        ssTabConfigSyphonLayout->setObjectName(QString::fromUtf8("ssTabConfigSyphonLayout"));

        verticalLayout_21->addLayout(ssTabConfigSyphonLayout);

        verticalSpacer_11 = new QSpacerItem(20, 339, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_21->addItem(verticalSpacer_11);

        ssTabConfig->addTab(ssTabConfigSyphon, QString());

        horizontalLayout_11->addWidget(ssTabConfig);

        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/general/res_icon_inspector_osc.png"), QSize(), QIcon::Normal, QIcon::Off);
        tab->addTab(tabConfig, icon3, QString());

        verticalLayout_6->addWidget(tab);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        mouseLabel = new QLabel(globalFrame);
        mouseLabel->setObjectName(QString::fromUtf8("mouseLabel"));
        mouseLabel->setMinimumSize(QSize(150, 20));
        mouseLabel->setMaximumSize(QSize(150, 20));

        horizontalLayout_4->addWidget(mouseLabel);

        rotationLabel = new QLabel(globalFrame);
        rotationLabel->setObjectName(QString::fromUtf8("rotationLabel"));
        rotationLabel->setMinimumSize(QSize(150, 20));
        rotationLabel->setMaximumSize(QSize(150, 20));
        rotationLabel->setStyleSheet(QString::fromUtf8("font: 10px;"));

        horizontalLayout_4->addWidget(rotationLabel);

        zoomLabel = new QLabel(globalFrame);
        zoomLabel->setObjectName(QString::fromUtf8("zoomLabel"));
        zoomLabel->setMaximumSize(QSize(85, 20));

        horizontalLayout_4->addWidget(zoomLabel);

        horizontalLayout_4->setStretch(0, 2);
        horizontalLayout_4->setStretch(1, 2);
        horizontalLayout_4->setStretch(2, 1);

        verticalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(globalFrame);

#if QT_CONFIG(shortcut)
        IDLabel->setBuddy(newIdButton);
        groupIdLabel->setBuddy(newIdButton);
        activityLabel->setBuddy(activityCheck);
        sizeLabel2->setBuddy(sizeSpin);
        labelLabel->setBuddy(labelLine);
        colorLabel1->setBuddy(colorCombo1);
        colorLabel2->setBuddy(colorCombo1);
        colorLabelMultiply->setBuddy(colorCombo1);
        textureLabel1->setBuddy(colorCombo1);
        textureLabel2->setBuddy(colorCombo1);
        positionLabel->setBuddy(positionX);
        sizeLabel->setBuddy(sizeWSpin);
        intertiaLabel->setBuddy(sizeWSpin);
        widthLabel->setBuddy(widthSpin);
        equationParam1Label->setBuddy(positionX);
        equationParam2Label->setBuddy(positionX);
        equationParam3Label->setBuddy(positionX);
        equationParam4Label->setBuddy(positionX);
        equationParam5Label->setBuddy(positionX);
        triggerOffLabel->setBuddy(triggerOffSpin);
        cursorSpeedLabel->setBuddy(speedSpin);
        speedFLabel->setBuddy(speedFSpin);
        patternLabel->setBuddy(patternLine);
        easingLabel->setBuddy(patternLine);
        fireTriggersLabel->setBuddy(patternLine);
        offsetLabel->setBuddy(offsetInitialSpin);
        followIdLabel->setBuddy(followId);
        autoresizeLabelLeft->setBuddy(followId);
        autoresizeLabelRight->setBuddy(followId);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(tab, newIdButton);
        QWidget::setTabOrder(newIdButton, groupIdButton);
        QWidget::setTabOrder(groupIdButton, sizeSpin);
        QWidget::setTabOrder(sizeSpin, labelLine);
        QWidget::setTabOrder(labelLine, activityCheck);
        QWidget::setTabOrder(activityCheck, colorCombo1);
        QWidget::setTabOrder(colorCombo1, colorCombo2);
        QWidget::setTabOrder(colorCombo2, ccView);
        QWidget::setTabOrder(ccView, unmuteObjects);
        QWidget::setTabOrder(unmuteObjects, unsoloObjects);
        QWidget::setTabOrder(unsoloObjects, unmuteGroups);
        QWidget::setTabOrder(unmuteGroups, unsoloGroups);
        QWidget::setTabOrder(unsoloGroups, followId);

        retranslateUi(UiInspector);
        QObject::connect(tab, SIGNAL(currentChanged(int)), UiInspector, SLOT(actionTabChange(int)));
        QObject::connect(groupIdButton, SIGNAL(released()), UiInspector, SLOT(actionInfoGroup()));
        QObject::connect(activityCheck, SIGNAL(stateChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(labelLine, SIGNAL(textChanged(QString)), UiInspector, SLOT(actionInfo()));
        QObject::connect(ccView, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), UiInspector, SLOT(actionCC()));
        QObject::connect(labelLine, SIGNAL(returnPressed()), UiInspector, SLOT(actionInfo()));
        QObject::connect(colorCombo1, SIGNAL(currentIndexChanged(QString)), UiInspector, SLOT(actionColor()));
        QObject::connect(colorCombo2, SIGNAL(currentIndexChanged(QString)), UiInspector, SLOT(actionColor()));
        QObject::connect(sizeSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(ccView, SIGNAL(itemClicked(QTreeWidgetItem*,int)), UiInspector, SLOT(actionCC(QTreeWidgetItem*,int)));
        QObject::connect(newIdButton, SIGNAL(released()), UiInspector, SLOT(actionInfoID()));
        QObject::connect(unmuteObjects, SIGNAL(released()), UiInspector, SLOT(actionCCButton()));
        QObject::connect(unsoloObjects, SIGNAL(released()), UiInspector, SLOT(actionCCButton()));
        QObject::connect(unsoloGroups, SIGNAL(released()), UiInspector, SLOT(actionCCButton()));
        QObject::connect(unmuteGroups, SIGNAL(released()), UiInspector, SLOT(actionCCButton()));
        QObject::connect(followId, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionCCButton()));
        QObject::connect(positionX, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(positionY, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(positionZ, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(sizeWSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(sizeHSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(widthSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(depthSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(triggerOffSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorLengthSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(speedSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(speedFSpin, SIGNAL(valueChanged(QString)), UiInspector, SLOT(actionInfo()));
        QObject::connect(patternLine, SIGNAL(currentIndexChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(patternLine, SIGNAL(editTextChanged(QString)), UiInspector, SLOT(actionInfo()));
        QObject::connect(easingCombo, SIGNAL(currentIndexChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(offsetInitialSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(offsetStartSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(offsetEndSpin, SIGNAL(valueChanged(QString)), UiInspector, SLOT(actionInfo()));
        QObject::connect(messagesButton, SIGNAL(released()), UiInspector, SLOT(actionMessages()));
        QObject::connect(messagesSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceX1, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceX2, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorTargetX1, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorTargetX2, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceY2, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceY1, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorTargetY2, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorTargetY1, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceZ1, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceZ2, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorTargetZ1, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorTargetZ2, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSpeedLock, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationEdit, SIGNAL(textChanged()), UiInspector, SLOT(actionInfo()));
        QObject::connect(pointsLists, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationPoints, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(textureCombo1, SIGNAL(currentIndexChanged(int)), UiInspector, SLOT(actionTexture()));
        QObject::connect(textureCombo2, SIGNAL(currentIndexChanged(int)), UiInspector, SLOT(actionTexture()));
        QObject::connect(equationType0, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationType1, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceMode0, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceMode1, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceMode2, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(cursorSourceMode3, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(ssTabConfig, SIGNAL(currentChanged(int)), UiInspector, SLOT(actionTabChange(int)));
        QObject::connect(followIdClear, SIGNAL(released()), UiInspector, SLOT(actionCCButton()));
        QObject::connect(autoresizeSlider, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionCCButton()));
        QObject::connect(equationTemplate, SIGNAL(currentIndexChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(colorComboMultiply, SIGNAL(currentIndexChanged(QString)), UiInspector, SLOT(actionColor()));
        QObject::connect(colorCombo1, SIGNAL(editTextChanged(QString)), UiInspector, SLOT(actionColor()));
        QObject::connect(colorCombo2, SIGNAL(editTextChanged(QString)), UiInspector, SLOT(actionColor()));
        QObject::connect(colorComboMultiply, SIGNAL(editTextChanged(QString)), UiInspector, SLOT(actionColor()));
        QObject::connect(pointsResample, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam1Slider, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam2Slider, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam3Slider, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam4Slider, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam5Slider, SIGNAL(valueChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam1Value, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam2Value, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam3Value, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam4Value, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParam5Value, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(equationParamReset, SIGNAL(released()), UiInspector, SLOT(actionInfo()));
        QObject::connect(intertiaSpin, SIGNAL(valueChanged(double)), UiInspector, SLOT(actionInfo()));
        QObject::connect(fireTriggers, SIGNAL(currentIndexChanged(int)), UiInspector, SLOT(actionInfo()));
        QObject::connect(fireTriggers, SIGNAL(editTextChanged(QString)), UiInspector, SLOT(actionInfo()));

        tab->setCurrentIndex(0);
        ssTabInfo->setCurrentIndex(0);
        ssTabConfig->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UiInspector);
    } // setupUi

    void retranslateUi(QWidget *UiInspector)
    {
        UiInspector->setWindowTitle(QCoreApplication::translate("UiInspector", "IanniX \342\200\224 Inspector", nullptr));
#if QT_CONFIG(statustip)
        tabProject->setStatusTip(QCoreApplication::translate("UiInspector", "Scores file|Scores are stored in files containing three parts:\\n- objects edited through graphical user interface\\n- script code\\n- received messages from external software", nullptr));
#endif // QT_CONFIG(statustip)
        tab->setTabText(tab->indexOf(tabProject), QCoreApplication::translate("UiInspector", "FILES", nullptr));
        typeLabel->setText(QCoreApplication::translate("UiInspector", "TRIGGER", nullptr));
#if QT_CONFIG(statustip)
        widgetID->setStatusTip(QCoreApplication::translate("UiInspector", "Objects identification|An object in IanniX is defined by two identifiers:\\n- the ID is a unique number in the score (two objects cannot have the same ID). IDs are used in sent messages to know who was the sender; they are used in received messages to control a targer a specific object\\n- the group ID is a string allowing a group control of objects in received messages. In sent messages, it can also be used as a human readable ID.\\n\\nIf an object is disabled (\"active\" checkbox), it will not be used in the score (no sent messages).", nullptr));
#endif // QT_CONFIG(statustip)
        IDLabel->setText(QCoreApplication::translate("UiInspector", "ID", nullptr));
#if QT_CONFIG(tooltip)
        newIdButton->setToolTip(QCoreApplication::translate("UiInspector", "Changes the object ID", nullptr));
#endif // QT_CONFIG(tooltip)
        newIdButton->setText(QCoreApplication::translate("UiInspector", "ID", nullptr));
        groupIdLabel->setText(QCoreApplication::translate("UiInspector", "GROUP ID", nullptr));
#if QT_CONFIG(tooltip)
        groupIdButton->setToolTip(QCoreApplication::translate("UiInspector", "Changes the group ID", nullptr));
#endif // QT_CONFIG(tooltip)
        groupIdButton->setText(QCoreApplication::translate("UiInspector", "GROUP", nullptr));
        activityLabel->setText(QCoreApplication::translate("UiInspector", "ACTIVE", nullptr));
#if QT_CONFIG(tooltip)
        activityCheck->setToolTip(QCoreApplication::translate("UiInspector", "Enables or disables the object in the socre", nullptr));
#endif // QT_CONFIG(tooltip)
        activityCheck->setText(QString());
#if QT_CONFIG(statustip)
        widgetStyle->setStatusTip(QCoreApplication::translate("UiInspector", "Objects style|Objects can have different graphical behaviours:\\n - you can change the colors and texture (images - only for triggers)\\n - size or thickness of the object is customisable\\n - a label can be set to add human readable information to the object", nullptr));
#endif // QT_CONFIG(statustip)
        sizeLabel2->setText(QCoreApplication::translate("UiInspector", "THICKNESS / SIZE", nullptr));
#if QT_CONFIG(tooltip)
        sizeSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes the tickness or size of objects", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLabel->setText(QCoreApplication::translate("UiInspector", "LABEL", nullptr));
#if QT_CONFIG(tooltip)
        labelLine->setToolTip(QCoreApplication::translate("UiInspector", "Changes the label of objects", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLine->setText(QString());
        colorLabel1->setText(QCoreApplication::translate("UiInspector", "COLOR\n"
"if ACTIVE", nullptr));
#if QT_CONFIG(tooltip)
        colorCombo1->setToolTip(QCoreApplication::translate("UiInspector", "Changes the color of active objects by using a color in the palette or a custom color", nullptr));
#endif // QT_CONFIG(tooltip)
        colorLabel2->setText(QCoreApplication::translate("UiInspector", "COLOR\n"
"if INACTIVE", nullptr));
#if QT_CONFIG(tooltip)
        colorCombo2->setToolTip(QCoreApplication::translate("UiInspector", "Changes the color of inactive objects by using a color in the palette or a custom color", nullptr));
#endif // QT_CONFIG(tooltip)
        colorLabelMultiply->setText(QCoreApplication::translate("UiInspector", "COLOR\n"
"MULTIPLICATION", nullptr));
#if QT_CONFIG(tooltip)
        colorComboMultiply->setToolTip(QCoreApplication::translate("UiInspector", "Multiplies the color of objects by another color in the palette or a custom color", nullptr));
#endif // QT_CONFIG(tooltip)
        textureLabel1->setText(QCoreApplication::translate("UiInspector", "TEXTURE\n"
"if ACTIVE", nullptr));
#if QT_CONFIG(tooltip)
        textureCombo1->setToolTip(QCoreApplication::translate("UiInspector", "Changes the texture (image) of active objects", nullptr));
#endif // QT_CONFIG(tooltip)
        textureLabel2->setText(QCoreApplication::translate("UiInspector", "TEXTURE\n"
"if INACTIVE", nullptr));
#if QT_CONFIG(tooltip)
        textureCombo2->setToolTip(QCoreApplication::translate("UiInspector", "Changes the texture (image) of inactive objects", nullptr));
#endif // QT_CONFIG(tooltip)
        ssTabInfo->setTabText(ssTabInfo->indexOf(ssTabInfoGeneral), QCoreApplication::translate("UiInspector", "GENERAL", nullptr));
#if QT_CONFIG(statustip)
        ssTabInfoSpace->setStatusTip(QCoreApplication::translate("UiInspector", "Objects and 3D space|Objects are positioned in a 3D space. These options allows you to control how objects interact with space:\\n - absolute position\\n - size of curves\\n - playhead cursor size\\n - curve trajectory points (manual or mathematical edition)", nullptr));
#endif // QT_CONFIG(statustip)
        positionLabel->setText(QCoreApplication::translate("UiInspector", "3D POSITION\n"
"(X / Y / Z)", nullptr));
#if QT_CONFIG(tooltip)
        positionX->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute X-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        positionY->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute Y-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        positionZ->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute Z-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
        sizeLabel->setText(QCoreApplication::translate("UiInspector", "3D CURVE SIZE\n"
"(W / H)", nullptr));
#if QT_CONFIG(tooltip)
        sizeWSpin->setToolTip(QCoreApplication::translate("UiInspector", "Resizes the object width", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        sizeHSpin->setToolTip(QCoreApplication::translate("UiInspector", "Resizes the object height", nullptr));
#endif // QT_CONFIG(tooltip)
        intertiaLabel->setText(QCoreApplication::translate("UiInspector", "ELASTICITY\n"
"FACTOR", nullptr));
#if QT_CONFIG(tooltip)
        intertiaSpin->setToolTip(QCoreApplication::translate("UiInspector", "Set a factor of elasticity making the curve \"elastic\" while moving points", nullptr));
#endif // QT_CONFIG(tooltip)
        widthLabel->setText(QCoreApplication::translate("UiInspector", "CURSOR\n"
"WIDTH / DEPTH", nullptr));
#if QT_CONFIG(tooltip)
        widthSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes the width of cursor playhead", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        depthSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes the depth of cursor playhead", nullptr));
#endif // QT_CONFIG(tooltip)
        pointsLabel->setText(QCoreApplication::translate("UiInspector", "CURVE\n"
"POINTS", nullptr));
#if QT_CONFIG(tooltip)
        pointsResample->setToolTip(QCoreApplication::translate("UiInspector", "Click here to manually edit curve points", nullptr));
#endif // QT_CONFIG(tooltip)
        pointsResample->setText(QCoreApplication::translate("UiInspector", "RESAMPLE", nullptr));
#if QT_CONFIG(tooltip)
        pointsLists->setToolTip(QCoreApplication::translate("UiInspector", "Click here to manually edit curve points", nullptr));
#endif // QT_CONFIG(tooltip)
        pointsLists->setText(QCoreApplication::translate("UiInspector", "EDIT POINTS", nullptr));
        equationTemplate->setItemText(0, QCoreApplication::translate("UiInspector", "Templates", nullptr));

        equationLabel->setText(QCoreApplication::translate("UiInspector", "CURVE\n"
"EQUATION", nullptr));
#if QT_CONFIG(tooltip)
        equationEdit->setToolTip(QCoreApplication::translate("UiInspector", "Changes the 3D mathematical equation of the curve", nullptr));
#endif // QT_CONFIG(tooltip)
        equationEdit->setPlainText(QCoreApplication::translate("UiInspector", "1\n"
",\n"
"3\n"
",\n"
"5\n"
"", nullptr));
        equationType0->setText(QCoreApplication::translate("UiInspector", "Cartesian coordinates (x, y, z)", nullptr));
        equationType1->setText(QCoreApplication::translate("UiInspector", "Polar coordinates (r, phi, theta)", nullptr));
        equationParam1Label->setText(QCoreApplication::translate("UiInspector", "PARAM1", nullptr));
#if QT_CONFIG(tooltip)
        equationParam1Value->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute Y-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
        equationParam2Label->setText(QCoreApplication::translate("UiInspector", "PARAM2", nullptr));
#if QT_CONFIG(tooltip)
        equationParam2Value->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute Y-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
        equationParam3Label->setText(QCoreApplication::translate("UiInspector", "PARAM3", nullptr));
#if QT_CONFIG(tooltip)
        equationParam3Value->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute Y-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
        equationParam4Label->setText(QCoreApplication::translate("UiInspector", "PARAM4", nullptr));
#if QT_CONFIG(tooltip)
        equationParam4Value->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute Y-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
        equationParam5Label->setText(QCoreApplication::translate("UiInspector", "PARAM5", nullptr));
#if QT_CONFIG(tooltip)
        equationParam5Value->setToolTip(QCoreApplication::translate("UiInspector", "Changes the absolute Y-position of object", nullptr));
#endif // QT_CONFIG(tooltip)
        equationParamReset->setText(QCoreApplication::translate("UiInspector", "RESET PARAMETERS TO DEFAULT", nullptr));
#if QT_CONFIG(tooltip)
        equationPoints->setToolTip(QCoreApplication::translate("UiInspector", "Defines the number of points used to calculate the 3D mathematical equation", nullptr));
#endif // QT_CONFIG(tooltip)
        equationPoints->setSuffix(QCoreApplication::translate("UiInspector", " points", nullptr));
        equationPoints->setPrefix(QCoreApplication::translate("UiInspector", "with a precision of ", nullptr));
        ssTabInfo->setTabText(ssTabInfo->indexOf(ssTabInfoSpace), QCoreApplication::translate("UiInspector", "3D SPACE", nullptr));
#if QT_CONFIG(statustip)
        ssTabInfoTime->setStatusTip(QCoreApplication::translate("UiInspector", "Objects and time|Cursors moves according to time. You can set up:\\n - speed of progression of cursors on curves\\n - how cursors loops on curve (in terms of speed and position/time)\\n - variation of speed (acceleration, multiple speeds according to loops)\\n\\n Last option is for triggers event duration. Typically, this duration is used for MIDI notes off (duration of note).", nullptr));
#endif // QT_CONFIG(statustip)
        triggerOffLabel->setText(QCoreApplication::translate("UiInspector", "TRIGGER\n"
"DURATION", nullptr));
#if QT_CONFIG(tooltip)
        triggerOffSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes the duration of a trigger event", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorSpeedLabel->setText(QCoreApplication::translate("UiInspector", "CURSOR SPEED\n"
"or LENGTH", nullptr));
#if QT_CONFIG(tooltip)
        speedSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes the cursor speed in terms of factor of global playback speed (1.00 = score playback speed)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        cursorLengthSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes the duration of one run of the cursor on its curve", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        cursorSpeedLock->setToolTip(QCoreApplication::translate("UiInspector", "Locks cursor speed to a specific duration on curve (even if curve length changes in the future)", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorSpeedLock->setText(QCoreApplication::translate("UiInspector", "LOCK", nullptr));
        speedFLabel->setText(QCoreApplication::translate("UiInspector", "CURSOR\n"
"MASTER SPEED", nullptr));
#if QT_CONFIG(tooltip)
        speedFSpin->setToolTip(QCoreApplication::translate("UiInspector", "Applies a last factor on cursor speed (1.00 = no changes)", nullptr));
#endif // QT_CONFIG(tooltip)
        patternLabel->setText(QCoreApplication::translate("UiInspector", "CURSOR\n"
"LOOP PATTERN", nullptr));
        patternLine->setItemText(0, QCoreApplication::translate("UiInspector", "1 0 - One run on curve", nullptr));
        patternLine->setItemText(1, QCoreApplication::translate("UiInspector", "1 - Loop on curve", nullptr));
        patternLine->setItemText(2, QCoreApplication::translate("UiInspector", "1 -1 0 - Single roundtrip on curve ", nullptr));
        patternLine->setItemText(3, QCoreApplication::translate("UiInspector", "1 -1 - Loop roundtrip on curve ", nullptr));
        patternLine->setItemText(4, QCoreApplication::translate("UiInspector", "1 2 0 - One normal run, another at double speed", nullptr));

#if QT_CONFIG(tooltip)
        patternLine->setToolTip(QCoreApplication::translate("UiInspector", "Defines the \"speed pattern\" of the cursor. Speeds are applied consecutively on each loop or run of the cursor on the curve.", nullptr));
#endif // QT_CONFIG(tooltip)
        easingLabel->setText(QCoreApplication::translate("UiInspector", "CURSOR\n"
"EASING CURVE", nullptr));
#if QT_CONFIG(tooltip)
        easingCombo->setToolTip(QCoreApplication::translate("UiInspector", "Manages cursor acceleration on the curve (beta)", nullptr));
#endif // QT_CONFIG(tooltip)
        fireTriggersLabel->setText(QCoreApplication::translate("UiInspector", "IMPACT ON TRIGGERS", nullptr));
        fireTriggers->setItemText(0, QCoreApplication::translate("UiInspector", "Doesn't fire triggers", nullptr));
        fireTriggers->setItemText(1, QCoreApplication::translate("UiInspector", "Fires only triggers of the same group", nullptr));
        fireTriggers->setItemText(2, QCoreApplication::translate("UiInspector", "Fires all triggers", nullptr));

#if QT_CONFIG(tooltip)
        fireTriggers->setToolTip(QCoreApplication::translate("UiInspector", "Defines the \"speed pattern\" of the cursor. Speeds are applied consecutively on each loop or run of the cursor on the curve.", nullptr));
#endif // QT_CONFIG(tooltip)
        offsetLabel->setText(QCoreApplication::translate("UiInspector", "CURSOR\n"
"OFFSETS", nullptr));
        offsetLabel1->setText(QCoreApplication::translate("UiInspector", "INITIALLY STARTS FROM", nullptr));
#if QT_CONFIG(tooltip)
        offsetInitialSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes initial position/time of the cursor on the curve for the first run. Negative value is a delay before starting the run.", nullptr));
#endif // QT_CONFIG(tooltip)
        offsetLabel2_2->setText(QCoreApplication::translate("UiInspector", "THEN", nullptr));
        offsetLabel2->setText(QCoreApplication::translate("UiInspector", "LOOPS FROM", nullptr));
#if QT_CONFIG(tooltip)
        offsetStartSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes loop starting position/time of the cursor on the curve for each run", nullptr));
#endif // QT_CONFIG(tooltip)
        offsetLabel3->setText(QCoreApplication::translate("UiInspector", "TO", nullptr));
#if QT_CONFIG(tooltip)
        offsetEndSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes loop ending position/time of the cursor on the curve for each run", nullptr));
#endif // QT_CONFIG(tooltip)
        offsetEndSpin->setSpecialValueText(QCoreApplication::translate("UiInspector", "the end", nullptr));
        ssTabInfo->setTabText(ssTabInfo->indexOf(ssTabInfoTime), QCoreApplication::translate("UiInspector", "TIME", nullptr));
#if QT_CONFIG(statustip)
        ssTabInfoMessage->setStatusTip(QCoreApplication::translate("UiInspector", "Objects and messages|Cursors emit periodically messages containing especially their position on score. This panel allows you to set up some options:\\n - you can edit the messages (protocol, what kind of values are sent...) and the amount of messages sent each second\\n - you can configure the mapping of coordinates. This fundamental option makes a translation between coordinates in score 3D space to the desired value ranges needed by the receiver (for example, you can translate coordinates to frequencies, or coordinates to MIDI velocities)\\n\\n Triggers will also emit messages each time cursor playheads will hit them.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        messagesButton->setToolTip(QCoreApplication::translate("UiInspector", "Changes the object sent messages", nullptr));
#endif // QT_CONFIG(tooltip)
        messagesButton->setText(QCoreApplication::translate("UiInspector", "EDIT MESSAGE(S)", nullptr));
#if QT_CONFIG(tooltip)
        messagesSpin->setToolTip(QCoreApplication::translate("UiInspector", "Changes the amount of messages sent by objects (small values may be CPU and network intensive)", nullptr));
#endif // QT_CONFIG(tooltip)
        messagesSpin->setSpecialValueText(QCoreApplication::translate("UiInspector", "Messages are sent immediately", nullptr));
        messagesSpin->setPrefix(QCoreApplication::translate("UiInspector", "Messages are sent each ", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceMode0->setToolTip(QCoreApplication::translate("UiInspector", "Changes the cursor mapping to match the curve bounding rectangle", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorSourceMode0->setText(QCoreApplication::translate("UiInspector", "Mapped on curves bounding rectangle", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceMode1->setToolTip(QCoreApplication::translate("UiInspector", "Changes the cursor mapping to match the curve+cursor bounding rectangle", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorSourceMode1->setText(QCoreApplication::translate("UiInspector", "Mapped on curves bounding rectangle including cursor size", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceMode2->setToolTip(QCoreApplication::translate("UiInspector", "Changes the cursor mapping to match the score bounding rectangle", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorSourceMode2->setText(QCoreApplication::translate("UiInspector", "Mapped on global score bounding rectangle", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceMode3->setToolTip(QCoreApplication::translate("UiInspector", "Changes the cursor mapping to your own coordinates mapping", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorSourceMode3->setText(QCoreApplication::translate("UiInspector", "Custom mapping", nullptr));
        cursorTargetLabel1->setText(QCoreApplication::translate("UiInspector", "X-COORDINATE\n"
"GOING FROM", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceX1->setToolTip(QCoreApplication::translate("UiInspector", "Sets starting range for X absolute coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel2->setText(QCoreApplication::translate("UiInspector", "TO", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceX2->setToolTip(QCoreApplication::translate("UiInspector", "Sets starting range for X absolute coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel3->setText(QCoreApplication::translate("UiInspector", "X-OUTPUT FROM", nullptr));
#if QT_CONFIG(tooltip)
        cursorTargetX1->setToolTip(QCoreApplication::translate("UiInspector", "Sets mapped range for X coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel4->setText(QCoreApplication::translate("UiInspector", "TO", nullptr));
#if QT_CONFIG(tooltip)
        cursorTargetX2->setToolTip(QCoreApplication::translate("UiInspector", "Sets mapped range for X coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel5->setText(QCoreApplication::translate("UiInspector", "Y-COORDINATE\n"
"GOING FROM", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceY2->setToolTip(QCoreApplication::translate("UiInspector", "Sets starting range for Y absolute coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel6->setText(QCoreApplication::translate("UiInspector", "TO", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceY1->setToolTip(QCoreApplication::translate("UiInspector", "Sets starting range for Y absolute coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel7->setText(QCoreApplication::translate("UiInspector", "Y-OUTPUT FROM", nullptr));
#if QT_CONFIG(tooltip)
        cursorTargetY2->setToolTip(QCoreApplication::translate("UiInspector", "Sets mapped range for Y coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel8->setText(QCoreApplication::translate("UiInspector", "TO", nullptr));
#if QT_CONFIG(tooltip)
        cursorTargetY1->setToolTip(QCoreApplication::translate("UiInspector", "Sets mapped range for Y coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel11->setText(QCoreApplication::translate("UiInspector", "Z-COORDINATE\n"
"GOING FROM", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceZ1->setToolTip(QCoreApplication::translate("UiInspector", "Sets starting range for Z absolute coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel13->setText(QCoreApplication::translate("UiInspector", "TO", nullptr));
#if QT_CONFIG(tooltip)
        cursorSourceZ2->setToolTip(QCoreApplication::translate("UiInspector", "Sets starting range for Z absolute coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel12->setText(QCoreApplication::translate("UiInspector", "Z-OUTPUT FROM", nullptr));
#if QT_CONFIG(tooltip)
        cursorTargetZ1->setToolTip(QCoreApplication::translate("UiInspector", "Sets mapped range for Z coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        cursorTargetLabel14->setText(QCoreApplication::translate("UiInspector", "TO", nullptr));
#if QT_CONFIG(tooltip)
        cursorTargetZ2->setToolTip(QCoreApplication::translate("UiInspector", "Sets mapped range for Z coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        ssTabInfo->setTabText(ssTabInfo->indexOf(ssTabInfoMessage), QCoreApplication::translate("UiInspector", "MESSAGES", nullptr));
#if QT_CONFIG(statustip)
        ssTabRessource->setStatusTip(QCoreApplication::translate("UiInspector", "Score resources|These two lists allow you to add external files (image file for triggers appearance or score background) or to create a color palette for your score. Each resource is identified by a unique string. Once edited, your new resources will be available in the first tab if you want to apply them on objects.", nullptr));
#endif // QT_CONFIG(statustip)
        ressourcesTexturesLabel->setText(QCoreApplication::translate("UiInspector", "TEXTURES", nullptr));
#if QT_CONFIG(tooltip)
        ressourcesTextures->setToolTip(QCoreApplication::translate("UiInspector", "Loads/initializes textures (images) for the current score", nullptr));
#endif // QT_CONFIG(tooltip)
        ressourcesColorsLabel->setText(QCoreApplication::translate("UiInspector", "COLORS", nullptr));
#if QT_CONFIG(tooltip)
        ressourcesColors->setToolTip(QCoreApplication::translate("UiInspector", "Loads/initializes global colors (color palette) for the current score", nullptr));
#endif // QT_CONFIG(tooltip)
        ssTabInfo->setTabText(ssTabInfo->indexOf(ssTabRessource), QCoreApplication::translate("UiInspector", "RESOURCES", nullptr));
        tab->setTabText(tab->indexOf(tabInfo), QCoreApplication::translate("UiInspector", "INFOS", nullptr));
#if QT_CONFIG(statustip)
        tabView->setStatusTip(QCoreApplication::translate("UiInspector", "Objects panel|This panel allows you to control the objects behaviour regarding to the score. You can mute some of them, turn objects in solo mode\342\200\246", nullptr));
#endif // QT_CONFIG(statustip)
        QTreeWidgetItem *___qtreewidgetitem = ccView->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("UiInspector", "GROUP ID", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("UiInspector", "ID", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("UiInspector", "S", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("UiInspector", "M", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("UiInspector", "TYPE", nullptr));
#if QT_CONFIG(tooltip)
        ccView->setToolTip(QCoreApplication::translate("UiInspector", "Lists all objects of the score", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        unmuteObjects->setToolTip(QCoreApplication::translate("UiInspector", "Switch on all objects", nullptr));
#endif // QT_CONFIG(tooltip)
        unmuteObjects->setText(QCoreApplication::translate("UiInspector", "Switch on all objects", nullptr));
#if QT_CONFIG(tooltip)
        unsoloObjects->setToolTip(QCoreApplication::translate("UiInspector", "Disable solo for all objects", nullptr));
#endif // QT_CONFIG(tooltip)
        unsoloObjects->setText(QCoreApplication::translate("UiInspector", "Disable solo for all objects", nullptr));
#if QT_CONFIG(tooltip)
        unmuteGroups->setToolTip(QCoreApplication::translate("UiInspector", "Switch on all groups", nullptr));
#endif // QT_CONFIG(tooltip)
        unmuteGroups->setText(QCoreApplication::translate("UiInspector", "Switch on all groups", nullptr));
#if QT_CONFIG(tooltip)
        unsoloGroups->setToolTip(QCoreApplication::translate("UiInspector", "Disable solo for all groups", nullptr));
#endif // QT_CONFIG(tooltip)
        unsoloGroups->setText(QCoreApplication::translate("UiInspector", "Disable solo for all groups", nullptr));
#if QT_CONFIG(tooltip)
        viewCurveOpacityCheck->setToolTip(QCoreApplication::translate("UiInspector", "Gives a small opacity on curves which has no cursor running on", nullptr));
#endif // QT_CONFIG(tooltip)
        viewCurveOpacityCheck->setText(QCoreApplication::translate("UiInspector", "LIGHT OFF UNUSED CURVES", nullptr));
#if QT_CONFIG(tooltip)
        viewCameraModeCheck->setToolTip(QCoreApplication::translate("UiInspector", "Gives a small opacity on curves which has no cursor running on", nullptr));
#endif // QT_CONFIG(tooltip)
        viewCameraModeCheck->setText(QCoreApplication::translate("UiInspector", "CAMERA IN PERSPECTIVE MODE", nullptr));
        followIdLabel->setText(QCoreApplication::translate("UiInspector", "CAMERA FOLLOWS OBJECT ID", nullptr));
#if QT_CONFIG(tooltip)
        followId->setToolTip(QCoreApplication::translate("UiInspector", "Camera point of view can be controlled by an object. Type here the ID of this object.", nullptr));
#endif // QT_CONFIG(tooltip)
        followId->setSpecialValueText(QCoreApplication::translate("UiInspector", "no objects", nullptr));
#if QT_CONFIG(tooltip)
        followIdClear->setToolTip(QCoreApplication::translate("UiInspector", "Resets camera follow object ID", nullptr));
#endif // QT_CONFIG(tooltip)
        followIdClear->setText(QCoreApplication::translate("UiInspector", "X", nullptr));
#if QT_CONFIG(statustip)
        widget->setStatusTip(QCoreApplication::translate("UiInspector", "Autoresize option|This options will adapt the size of objects according to the current zoom. When you zoom or unzoom very far, objects like triggers may be very big or invisible. This feature allows you to have a clear and homogenous vision of your score by resizing objects to a reasonable size.", nullptr));
#endif // QT_CONFIG(statustip)
        autoresizeLabel->setText(QCoreApplication::translate("UiInspector", "OBJECTS SIZE ACCORDING TO ZOOM", nullptr));
        autoresizeLabelLeft->setText(QCoreApplication::translate("UiInspector", "BASIC\n"
"SIZE", nullptr));
#if QT_CONFIG(tooltip)
        autoresizeSlider->setToolTip(QCoreApplication::translate("UiInspector", "Rescales objects size according to zoom", nullptr));
#endif // QT_CONFIG(tooltip)
        autoresizeLabelRight->setText(QCoreApplication::translate("UiInspector", "FIXED\n"
"SIZE", nullptr));
        tab->setTabText(tab->indexOf(tabView), QCoreApplication::translate("UiInspector", "OBJECTS", nullptr));
        ssTabConfig->setTabText(ssTabConfig->indexOf(ssTabConfigLog), QCoreApplication::translate("UiInspector", "MESSAGE LOG", nullptr));
        myIPLabel->setText(QCoreApplication::translate("UiInspector", "My IP:", nullptr));
        myIP->setPlainText(QString());
        ssTabConfig->setTabText(ssTabConfig->indexOf(ssTabConfigNetwork), QCoreApplication::translate("UiInspector", "NETWORK", nullptr));
        ssTabConfig->setTabText(ssTabConfig->indexOf(ssTabConfigMIDI), QCoreApplication::translate("UiInspector", "MIDI", nullptr));
        ssTabConfig->setTabText(ssTabConfig->indexOf(ssTabConfigArduino), QCoreApplication::translate("UiInspector", "ARDUINO", nullptr));
        ssTabConfig->setTabText(ssTabConfig->indexOf(ssTabConfigSyphon), QCoreApplication::translate("UiInspector", "SOFTWARE", nullptr));
        tab->setTabText(tab->indexOf(tabConfig), QCoreApplication::translate("UiInspector", "CONFIG", nullptr));
#if QT_CONFIG(tooltip)
        mouseLabel->setToolTip(QCoreApplication::translate("UiInspector", "Current mouse position on score", nullptr));
#endif // QT_CONFIG(tooltip)
        mouseLabel->setText(QCoreApplication::translate("UiInspector", "MOUSE: 0.000 s. / 0.000 s.", nullptr));
#if QT_CONFIG(tooltip)
        rotationLabel->setToolTip(QCoreApplication::translate("UiInspector", "Current score zoom", nullptr));
#endif // QT_CONFIG(tooltip)
        rotationLabel->setText(QCoreApplication::translate("UiInspector", "ANGLES: 0.000\302\260 / 0.000\302\260", nullptr));
#if QT_CONFIG(tooltip)
        zoomLabel->setToolTip(QCoreApplication::translate("UiInspector", "Current score zoom", nullptr));
#endif // QT_CONFIG(tooltip)
        zoomLabel->setText(QCoreApplication::translate("UiInspector", "ZOOM: 100%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiInspector: public Ui_UiInspector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIINSPECTOR_H
