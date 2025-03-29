/********************************************************************************
** Form generated from reading UI file 'transport.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSPORT_H
#define UI_TRANSPORT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Transport
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *globalFrame;
    QHBoxLayout *horizontalLayout_2;
    QFrame *transportFrame;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *ffButton;
    QPushButton *playButton;
    QFrame *timeFrame;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *timeEdit;
    QFrame *speedFrame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *spaceForLog;
    QHBoxLayout *horizontalLayout_5;
    QSlider *speedSlider;
    QDoubleSpinBox *speedSpin;
    QPushButton *speedSpinReset;
    QFrame *perfFrame;
    QVBoxLayout *verticalLayout;
    QLineEdit *perfSchedulerEdit;
    QLineEdit *perfOpenGLEdit;
    QLineEdit *perfCpuEdit;
    QFrame *logoFrame;
    QVBoxLayout *verticalLayout_3;
    QPushButton *logoButton;

    void setupUi(QWidget *Transport)
    {
        if (Transport->objectName().isEmpty())
            Transport->setObjectName(QString::fromUtf8("Transport"));
        Transport->resize(786, 60);
        Transport->setMinimumSize(QSize(0, 60));
        Transport->setMaximumSize(QSize(16777215, 60));
        Transport->setStyleSheet(QString::fromUtf8("QTabWidget, QLabel, QCheckBox, QLineEdit, QPlainTextEdit, QPushButton, QSpinBox, QDoubleSpinBox, QTreeView, QHeaderView, QTabBar, QComboBox, QFrame#globalFrame, QTabBar::tab, QTreeView, QHeaderView, QDockWidget, QStatusBar, QRadioButton, QToolButton {\n"
"	font: 						10px \"Museo Sans\", \"Museo Sans 500\", \"Arial\";\n"
"	padding:					0px;\n"
"	margin:					0px;\n"
"	min-height: 				20px;\n"
"	color: 						white;\n"
"	border: 					0px solid black;\n"
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
"QFrame#globalFrame, QFrame#transportFrame, QFrame#timeFrame, QFrame#optionFrame, QFrame#speedFrame, QFrame#logoFrame, QFrame#perfFrame, "
                        "QDialog {\n"
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
"	margin-left: 			6px;\n"
"	padding-left: 			3px;\n"
""
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
"    image: 						url(:/icons/res_icon_plus.p"
                        "ng);\n"
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
"}\n"
"QHeaderView {\n"
"	background: 							transparent;\n"
"	border: 									0px solid black;\n"
"	color: 										rgb(200, 200, 200);\n"
"	min-height: 								14px;\n"
"}\n"
"QHeaderView::section {\n"
"	background:"
                        " 							rgb(90, 90, 90);\n"
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
"QScrollBar:vertical {						width: 			8px;					}\n"
"QScrollBar:horizo"
                        "ntal {					height: 		8px;				}\n"
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
"	height: 					10px;\n"
"	border-radius: 		5px;\n"
"	margin-top: 			-"
                        "4px;\n"
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
"    background-color:  rgba(0, 0, 0, 20);\n"
"}\n"
"\n"
"\n"
"QStatusBar {\n"
""
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
"	border: 					0px solid black;\n"
"	background-color: 	transparent;\n"
"}\n"
"QPushButton:hov"
                        "er#logoButton {\n"
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
"/* ----- */\n"
"\n"
"\n"
"\n"
"/* MAIN */\n"
"QWidget#centralwidget  {\n"
""
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
        horizontalLayout = new QHBoxLayout(Transport);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        globalFrame = new QFrame(Transport);
        globalFrame->setObjectName(QString::fromUtf8("globalFrame"));
        globalFrame->setFrameShape(QFrame::StyledPanel);
        globalFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(globalFrame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 3);
        transportFrame = new QFrame(globalFrame);
        transportFrame->setObjectName(QString::fromUtf8("transportFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(transportFrame->sizePolicy().hasHeightForWidth());
        transportFrame->setSizePolicy(sizePolicy);
        transportFrame->setFrameShape(QFrame::StyledPanel);
        transportFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(transportFrame);
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(12, 0, -1, 0);
        ffButton = new QPushButton(transportFrame);
        ffButton->setObjectName(QString::fromUtf8("ffButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ffButton->sizePolicy().hasHeightForWidth());
        ffButton->setSizePolicy(sizePolicy1);
        ffButton->setMinimumSize(QSize(48, 42));
        ffButton->setMaximumSize(QSize(40, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/general/res_icon_ff.png"), QSize(), QIcon::Normal, QIcon::Off);
        ffButton->setIcon(icon);
        ffButton->setIconSize(QSize(24, 24));

        horizontalLayout_4->addWidget(ffButton);

        playButton = new QPushButton(transportFrame);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        sizePolicy1.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy1);
        playButton->setMinimumSize(QSize(48, 42));
        playButton->setMaximumSize(QSize(40, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/general/res_icon_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/general/res_icon_pause.png"), QSize(), QIcon::Normal, QIcon::On);
        playButton->setIcon(icon1);
        playButton->setIconSize(QSize(18, 18));
        playButton->setCheckable(true);
        playButton->setChecked(false);

        horizontalLayout_4->addWidget(playButton);


        horizontalLayout_2->addWidget(transportFrame);

        timeFrame = new QFrame(globalFrame);
        timeFrame->setObjectName(QString::fromUtf8("timeFrame"));
        sizePolicy.setHeightForWidth(timeFrame->sizePolicy().hasHeightForWidth());
        timeFrame->setSizePolicy(sizePolicy);
        timeFrame->setFrameShape(QFrame::StyledPanel);
        timeFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(timeFrame);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(6, 0, 6, 0);
        timeEdit = new QLineEdit(timeFrame);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        sizePolicy1.setHeightForWidth(timeEdit->sizePolicy().hasHeightForWidth());
        timeEdit->setSizePolicy(sizePolicy1);
        timeEdit->setMinimumSize(QSize(280, 28));
        timeEdit->setMaximumSize(QSize(280, 55));
        timeEdit->setFocusPolicy(Qt::ClickFocus);
        timeEdit->setInputMask(QString::fromUtf8("99:99:99.999"));
        timeEdit->setText(QString::fromUtf8("00:00:00.000"));

        horizontalLayout_3->addWidget(timeEdit);


        horizontalLayout_2->addWidget(timeFrame);

        speedFrame = new QFrame(globalFrame);
        speedFrame->setObjectName(QString::fromUtf8("speedFrame"));
        speedFrame->setFrameShape(QFrame::StyledPanel);
        speedFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(speedFrame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(12, 0, 12, 0);
        spaceForLog = new QHBoxLayout();
        spaceForLog->setSpacing(0);
        spaceForLog->setObjectName(QString::fromUtf8("spaceForLog"));

        verticalLayout_2->addLayout(spaceForLog);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        speedSlider = new QSlider(speedFrame);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setMinimum(-500);
        speedSlider->setMaximum(500);
        speedSlider->setValue(100);
        speedSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(speedSlider);

        speedSpin = new QDoubleSpinBox(speedFrame);
        speedSpin->setObjectName(QString::fromUtf8("speedSpin"));
        speedSpin->setMinimumSize(QSize(50, 30));
        speedSpin->setMaximumSize(QSize(50, 20));
        speedSpin->setDecimals(3);
        speedSpin->setMinimum(-999.000000000000000);
        speedSpin->setMaximum(999.000000000000000);
        speedSpin->setSingleStep(0.100000000000000);
        speedSpin->setValue(1.000000000000000);

        horizontalLayout_5->addWidget(speedSpin);

        speedSpinReset = new QPushButton(speedFrame);
        speedSpinReset->setObjectName(QString::fromUtf8("speedSpinReset"));
        speedSpinReset->setEnabled(false);
        speedSpinReset->setStyleSheet(QString::fromUtf8("QPushButton  {\n"
"	min-width:  		14px;\n"
"	min-height: 		14px;\n"
"	max-width:  	14px;\n"
"	max-height: 	14px;\n"
"	width:  				14px;\n"
"	height: 			14px;\n"
"	border-radius: 7px;\n"
"	margin: 			0px;\n"
"	margin-top:		7px;\n"
"	padding:			0px;\n"
"}\n"
"QPushButton:disabled {\n"
"	border:				0px solid transparent;\n"
"	background: 	transparent;\n"
"	color:				transparent;\n"
"}"));

        horizontalLayout_5->addWidget(speedSpinReset);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_2->addWidget(speedFrame);

        perfFrame = new QFrame(globalFrame);
        perfFrame->setObjectName(QString::fromUtf8("perfFrame"));
        sizePolicy.setHeightForWidth(perfFrame->sizePolicy().hasHeightForWidth());
        perfFrame->setSizePolicy(sizePolicy);
        perfFrame->setFrameShape(QFrame::StyledPanel);
        perfFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(perfFrame);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 0, 6, 3);
        perfSchedulerEdit = new QLineEdit(perfFrame);
        perfSchedulerEdit->setObjectName(QString::fromUtf8("perfSchedulerEdit"));
        perfSchedulerEdit->setMinimumSize(QSize(60, 28));
        perfSchedulerEdit->setMaximumSize(QSize(60, 28));
        perfSchedulerEdit->setInputMask(QString::fromUtf8("009 ms"));
        perfSchedulerEdit->setText(QString::fromUtf8("5 ms"));
        perfSchedulerEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(perfSchedulerEdit);

        perfOpenGLEdit = new QLineEdit(perfFrame);
        perfOpenGLEdit->setObjectName(QString::fromUtf8("perfOpenGLEdit"));
        perfOpenGLEdit->setMinimumSize(QSize(60, 28));
        perfOpenGLEdit->setMaximumSize(QSize(60, 28));
        perfOpenGLEdit->setInputMask(QString::fromUtf8("009 fps"));
        perfOpenGLEdit->setText(QString::fromUtf8("60 fps"));
        perfOpenGLEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(perfOpenGLEdit);

        perfCpuEdit = new QLineEdit(perfFrame);
        perfCpuEdit->setObjectName(QString::fromUtf8("perfCpuEdit"));
        perfCpuEdit->setMinimumSize(QSize(60, 28));
        perfCpuEdit->setMaximumSize(QSize(60, 28));
        perfCpuEdit->setFocusPolicy(Qt::NoFocus);
        perfCpuEdit->setInputMask(QString::fromUtf8("009 %"));
        perfCpuEdit->setText(QString::fromUtf8("0 %"));
        perfCpuEdit->setCursorPosition(5);
        perfCpuEdit->setAlignment(Qt::AlignCenter);
        perfCpuEdit->setReadOnly(true);

        verticalLayout->addWidget(perfCpuEdit);


        horizontalLayout_2->addWidget(perfFrame);

        logoFrame = new QFrame(globalFrame);
        logoFrame->setObjectName(QString::fromUtf8("logoFrame"));
        sizePolicy.setHeightForWidth(logoFrame->sizePolicy().hasHeightForWidth());
        logoFrame->setSizePolicy(sizePolicy);
        logoFrame->setFrameShape(QFrame::StyledPanel);
        logoFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(logoFrame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 3, 15, 0);
        logoButton = new QPushButton(logoFrame);
        logoButton->setObjectName(QString::fromUtf8("logoButton"));
        logoButton->setMinimumSize(QSize(55, 16));
        logoButton->setMaximumSize(QSize(55, 50));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/general/res_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        logoButton->setIcon(icon2);
        logoButton->setIconSize(QSize(50, 45));

        verticalLayout_3->addWidget(logoButton);


        horizontalLayout_2->addWidget(logoFrame);


        horizontalLayout->addWidget(globalFrame);


        retranslateUi(Transport);
        QObject::connect(perfSchedulerEdit, SIGNAL(textChanged(QString)), Transport, SLOT(action()));
        QObject::connect(perfOpenGLEdit, SIGNAL(textChanged(QString)), Transport, SLOT(action()));
        QObject::connect(speedSlider, SIGNAL(valueChanged(int)), Transport, SLOT(action()));
        QObject::connect(speedSpin, SIGNAL(valueChanged(double)), Transport, SLOT(action()));
        QObject::connect(timeEdit, SIGNAL(editingFinished()), Transport, SLOT(action()));
        QObject::connect(playButton, SIGNAL(released()), Transport, SLOT(action()));
        QObject::connect(ffButton, SIGNAL(released()), Transport, SLOT(action()));
        QObject::connect(logoButton, SIGNAL(released()), Transport, SLOT(action()));
        QObject::connect(speedSpinReset, SIGNAL(released()), Transport, SLOT(action()));

        QMetaObject::connectSlotsByName(Transport);
    } // setupUi

    void retranslateUi(QWidget *Transport)
    {
        Transport->setWindowTitle(QCoreApplication::translate("Transport", "IanniX \342\200\224 Transport", nullptr));
#if QT_CONFIG(tooltip)
        ffButton->setToolTip(QCoreApplication::translate("Transport", "Rewinds the playback", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        ffButton->setStatusTip(QCoreApplication::translate("Transport", "Playback|By pressing the button, IanniX will play or pause the score playback. If nothing happened, be sure the score speed is positive!", nullptr));
#endif // QT_CONFIG(statustip)
        ffButton->setText(QString());
#if QT_CONFIG(tooltip)
        playButton->setToolTip(QCoreApplication::translate("Transport", "Plays or pauses the playback", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        playButton->setStatusTip(QCoreApplication::translate("Transport", "Playback|Press this button to start or pause the playback", nullptr));
#endif // QT_CONFIG(statustip)
        playButton->setText(QString());
#if QT_CONFIG(tooltip)
        timeEdit->setToolTip(QCoreApplication::translate("Transport", "Goes to a specific playback timecode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        timeEdit->setStatusTip(QCoreApplication::translate("Transport", "Playback|This is the elapsed time since the beginning of the playback of the score.\\n If you need to jump to a specific timecode, feel free to type directly the desired timecode in this box.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        speedSlider->setToolTip(QCoreApplication::translate("Transport", "Changes the global playback speed (1.00 = real time clock)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        speedSlider->setStatusTip(QCoreApplication::translate("Transport", "Playback speed|IanniX will play your score with a classical precise clock. But you can speed up or down the playback... or reverse the time!", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        speedSpin->setToolTip(QCoreApplication::translate("Transport", "Changes the global playback speed (1.00 = real time clock)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        speedSpin->setStatusTip(QCoreApplication::translate("Transport", "Playback speed|IanniX will play your score with a classical precise clock. But you can speed up or down the playback... or reverse the time!", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        speedSpinReset->setToolTip(QCoreApplication::translate("Transport", "Resets score speed to nominal speed (1.00)", nullptr));
#endif // QT_CONFIG(tooltip)
        speedSpinReset->setText(QCoreApplication::translate("Transport", "X", nullptr));
#if QT_CONFIG(tooltip)
        perfSchedulerEdit->setToolTip(QCoreApplication::translate("Transport", "Scheduler period", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        perfSchedulerEdit->setStatusTip(QCoreApplication::translate("Transport", "Scheduler period|IanniX computes your score at the displayed rate.\\n You can also force IanniX to a specific scheduler period by typing a value in this field. 5ms is accurate enough but it can also be CPU intensive so feel free to increase this value if needed.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        perfOpenGLEdit->setToolTip(QCoreApplication::translate("Transport", "Rendering frame rate", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        perfOpenGLEdit->setStatusTip(QCoreApplication::translate("Transport", "Rendering frame rate|IannIX refreshes your score at the displayed frame rate.\\n You can also force IanniX to a specific framerate by typing a value in this field. 50fps is fluid but it can also be CPU intensive so feel free to decrease this value if needed.\\n Finaly, be aware that graphical frame rate doesn't affect messages accuracy or sample rate.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        perfCpuEdit->setToolTip(QCoreApplication::translate("Transport", "CPU usage", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        perfCpuEdit->setStatusTip(QCoreApplication::translate("Transport", "CPU usage|CPU usage can give you information about the complexity of your score.\\n If the value is high, be sure to disable logs by closing the Network tab. Then you can also reduce the accuracy of IanniX by changing the scheduler period and the rendering frame rate (fields above).", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        logoButton->setToolTip(QCoreApplication::translate("Transport", "About IanniX", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        logoButton->setStatusTip(QCoreApplication::translate("Transport", "About IanniX|IanniX is open source and developed by volunteers. Discover who they are!", nullptr));
#endif // QT_CONFIG(statustip)
        logoButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Transport: public Ui_Transport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSPORT_H
