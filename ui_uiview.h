/********************************************************************************
** Form generated from reading UI file 'uiview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIVIEW_H
#define UI_UIVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gui/uiinspector.h"
#include "render/uirender.h"
#include "render/uirenderpreview.h"
#include "transport/transport.h"

QT_BEGIN_NAMESPACE

class Ui_UiView
{
public:
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionSelect_all;
    QAction *actionDelete;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionFullscreen;
    QAction *actionToggle_Inspector;
    QAction *actionToggle_Transport;
    QAction *actionPlay_pause;
    QAction *actionFast_rewind;
    QAction *actionGrid;
    QAction *actionDuplicate;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionZoom_initial;
    QAction *actionDrawFreeCurve;
    QAction *actionDrawPointCurve;
    QAction *actionDrawTriggers;
    QAction *actionAddFreeCursor;
    QAction *action10Seconds;
    QAction *action1second;
    QAction *action500Milliseconds;
    QAction *action100Milliseconds;
    QAction *action10Milliseconds;
    QAction *actionCustomValue;
    QAction *actionAddCircleCurve;
    QAction *actionSnapXGrid;
    QAction *actionLockPos;
    QAction *actionToggleLabel;
    QAction *actionPatchesFolder;
    QAction *actionAbout;
    QAction *actionImport_SVG;
    QAction *actionImport_Text;
    QAction *actionShowEditor;
    QAction *actionReloadScript;
    QAction *actionLight;
    QAction *actionImport_Background;
    QAction *actionAllow_triggers_selection;
    QAction *actionAllow_curves_selection;
    QAction *actionAllow_cursors_selection;
    QAction *actionSnapYGrid;
    QAction *actionDistributeH;
    QAction *actionDistributeV;
    QAction *actionAlign_left;
    QAction *actionAlign_center;
    QAction *actionAlign_right;
    QAction *actionAlign_top;
    QAction *actionAlign_middle;
    QAction *actionAlign_bottom;
    QAction *actionAlign_circle;
    QAction *actionAlign_ellipse;
    QAction *actionSnapshot;
    QAction *actionResize;
    QAction *actionShowTimer;
    QAction *actionPerformance;
    QAction *actionAddTimeline;
    QAction *actionPlaySelected;
    QAction *actionDrawFreeCurveSimple;
    QAction *actionDrawPointCurveSimple;
    QAction *actionAddMathCurveSimple;
    QAction *actionAddMathCurve;
    QAction *actionShowHelp;
    QAction *actionPreferences;
    QAction *actionSave_score_as;
    QAction *actionClose_score;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *pageRender;
    QHBoxLayout *horizontalLayout_2;
    UiRender *render;
    QWidget *pagePerf;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *performanceLayout;
    QCheckBox *performancePreview;
    QSpacerItem *horizontalSpacer;
    UiRenderPreview *renderPreview;
    QMenuBar *menubar;
    QMenu *menuEdit;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuGrid_size;
    QMenu *menuPlayback;
    QMenu *menuAlignment;
    QMenu *menuAlignH;
    QMenu *menuAlignV;
    QDockWidget *transportDock;
    Transport *transport;
    QDockWidget *inspecteurDock;
    UiInspector *inspector;
    QToolBar *toolBarAdd;
    QStatusBar *statusBar;
    QToolBar *toolBarView;
    QToolBar *toolBarWindow;

    void setupUi(QMainWindow *UiView)
    {
        if (UiView->objectName().isEmpty())
            UiView->setObjectName(QString::fromUtf8("UiView"));
        UiView->resize(1094, 740);
        UiView->setStyleSheet(QString::fromUtf8("QTabWidget, QLabel, QCheckBox, QLineEdit, QPlainTextEdit, QPushButton, QSpinBox, QDoubleSpinBox, QTreeView, QHeaderView, QTabBar, QComboBox, QFrame#globalFrame, QTabBar::tab, QTreeView, QHeaderView, QDockWidget, QStatusBar, QRadioButton, QToolButton {\n"
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
"	width:		22px;\n"
"	height:		22px;\n"
"}\n"
"QToolButton:pressed, QToolButton:checked {\n"
"    background-color:  rgba(0, 0, 0, "
                        "20);\n"
"}\n"
"QToolButton#actionPlaySelected:pressed, QToolButton#actionPlaySelected:checked {\n"
"    background-color:  red;\n"
"}\n"
"QToolButton#actionLockPos:pressed, QToolButton#actionLockPos:checked {\n"
"    background-color:  red;\n"
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
"QLineE"
                        "dit#timeEdit {\n"
"	font: 						40px \"Lucida Sans\", \"Lucida Grande\", \"Lucida Sans Unicode\", \"Lucida\";\n"
"	color: 						rgb(0, 187, 255);\n"
"}\n"
"QPushButton#logoButton {\n"
"	border: 					0px solid black;\n"
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
"QWidget#tabProject, QWidget#tabView, QWidget#tab"
                        "Info, QWidget#tabControlCenter, QWidget#tabConfig {\n"
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
        actionUndo = new QAction(UiView);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionUndo->setShortcutContext(Qt::ApplicationShortcut);
        actionRedo = new QAction(UiView);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionRedo->setShortcutContext(Qt::ApplicationShortcut);
        actionCopy = new QAction(UiView);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionCopy->setShortcutContext(Qt::ApplicationShortcut);
        actionPaste = new QAction(UiView);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionPaste->setShortcutContext(Qt::ApplicationShortcut);
        actionCut = new QAction(UiView);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCut->setShortcutContext(Qt::ApplicationShortcut);
        actionSelect_all = new QAction(UiView);
        actionSelect_all->setObjectName(QString::fromUtf8("actionSelect_all"));
        actionSelect_all->setShortcutContext(Qt::ApplicationShortcut);
        actionDelete = new QAction(UiView);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionDelete->setShortcutContext(Qt::ApplicationShortcut);
        actionNew = new QAction(UiView);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionNew->setShortcutContext(Qt::ApplicationShortcut);
        actionOpen = new QAction(UiView);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setShortcutContext(Qt::ApplicationShortcut);
        actionSave = new QAction(UiView);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionQuit = new QAction(UiView);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setShortcutContext(Qt::ApplicationShortcut);
        actionFullscreen = new QAction(UiView);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionFullscreen->setCheckable(true);
        actionFullscreen->setChecked(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/actions/res_icon_fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFullscreen->setIcon(icon);
        actionFullscreen->setShortcutContext(Qt::ApplicationShortcut);
        actionToggle_Inspector = new QAction(UiView);
        actionToggle_Inspector->setObjectName(QString::fromUtf8("actionToggle_Inspector"));
        actionToggle_Inspector->setCheckable(true);
        actionToggle_Inspector->setChecked(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/actions/res_icon_inspector.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggle_Inspector->setIcon(icon1);
        actionToggle_Inspector->setShortcutContext(Qt::ApplicationShortcut);
        actionToggle_Transport = new QAction(UiView);
        actionToggle_Transport->setObjectName(QString::fromUtf8("actionToggle_Transport"));
        actionToggle_Transport->setCheckable(true);
        actionToggle_Transport->setChecked(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/actions/res_icon_transport.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggle_Transport->setIcon(icon2);
        actionToggle_Transport->setShortcutContext(Qt::ApplicationShortcut);
        actionPlay_pause = new QAction(UiView);
        actionPlay_pause->setObjectName(QString::fromUtf8("actionPlay_pause"));
        actionPlay_pause->setShortcutContext(Qt::ApplicationShortcut);
        actionFast_rewind = new QAction(UiView);
        actionFast_rewind->setObjectName(QString::fromUtf8("actionFast_rewind"));
        actionFast_rewind->setShortcutContext(Qt::ApplicationShortcut);
        actionGrid = new QAction(UiView);
        actionGrid->setObjectName(QString::fromUtf8("actionGrid"));
        actionGrid->setCheckable(true);
        actionGrid->setChecked(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/actions/res_icon_grid.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrid->setIcon(icon3);
        actionGrid->setShortcutContext(Qt::ApplicationShortcut);
        actionDuplicate = new QAction(UiView);
        actionDuplicate->setObjectName(QString::fromUtf8("actionDuplicate"));
        actionDuplicate->setShortcutContext(Qt::ApplicationShortcut);
        actionZoom_in = new QAction(UiView);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        actionZoom_in->setShortcutContext(Qt::ApplicationShortcut);
        actionZoom_out = new QAction(UiView);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        actionZoom_out->setShortcutContext(Qt::ApplicationShortcut);
        actionZoom_initial = new QAction(UiView);
        actionZoom_initial->setObjectName(QString::fromUtf8("actionZoom_initial"));
        actionZoom_initial->setShortcutContext(Qt::ApplicationShortcut);
        actionDrawFreeCurve = new QAction(UiView);
        actionDrawFreeCurve->setObjectName(QString::fromUtf8("actionDrawFreeCurve"));
        actionDrawFreeCurve->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/actions/res_icon_curveFree.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawFreeCurve->setIcon(icon4);
        actionDrawFreeCurve->setShortcutContext(Qt::ApplicationShortcut);
        actionDrawPointCurve = new QAction(UiView);
        actionDrawPointCurve->setObjectName(QString::fromUtf8("actionDrawPointCurve"));
        actionDrawPointCurve->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/actions/res_icon_curvePoint.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawPointCurve->setIcon(icon5);
        actionDrawPointCurve->setShortcutContext(Qt::ApplicationShortcut);
        actionDrawTriggers = new QAction(UiView);
        actionDrawTriggers->setObjectName(QString::fromUtf8("actionDrawTriggers"));
        actionDrawTriggers->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/actions/res_icon_trigger.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawTriggers->setIcon(icon6);
        actionDrawTriggers->setShortcutContext(Qt::ApplicationShortcut);
        actionAddFreeCursor = new QAction(UiView);
        actionAddFreeCursor->setObjectName(QString::fromUtf8("actionAddFreeCursor"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/actions/res_icon_cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddFreeCursor->setIcon(icon7);
        actionAddFreeCursor->setShortcutContext(Qt::ApplicationShortcut);
        action10Seconds = new QAction(UiView);
        action10Seconds->setObjectName(QString::fromUtf8("action10Seconds"));
        action10Seconds->setCheckable(true);
        action10Seconds->setShortcutContext(Qt::ApplicationShortcut);
        action1second = new QAction(UiView);
        action1second->setObjectName(QString::fromUtf8("action1second"));
        action1second->setCheckable(true);
        action1second->setChecked(true);
        action1second->setShortcutContext(Qt::ApplicationShortcut);
        action500Milliseconds = new QAction(UiView);
        action500Milliseconds->setObjectName(QString::fromUtf8("action500Milliseconds"));
        action500Milliseconds->setCheckable(true);
        action500Milliseconds->setShortcutContext(Qt::ApplicationShortcut);
        action100Milliseconds = new QAction(UiView);
        action100Milliseconds->setObjectName(QString::fromUtf8("action100Milliseconds"));
        action100Milliseconds->setCheckable(true);
        action100Milliseconds->setShortcutContext(Qt::ApplicationShortcut);
        action10Milliseconds = new QAction(UiView);
        action10Milliseconds->setObjectName(QString::fromUtf8("action10Milliseconds"));
        action10Milliseconds->setCheckable(true);
        action10Milliseconds->setShortcutContext(Qt::ApplicationShortcut);
        actionCustomValue = new QAction(UiView);
        actionCustomValue->setObjectName(QString::fromUtf8("actionCustomValue"));
        actionCustomValue->setCheckable(true);
        actionCustomValue->setShortcutContext(Qt::ApplicationShortcut);
        actionAddCircleCurve = new QAction(UiView);
        actionAddCircleCurve->setObjectName(QString::fromUtf8("actionAddCircleCurve"));
        actionAddCircleCurve->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/actions/res_icon_curveCircle.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddCircleCurve->setIcon(icon8);
        actionAddCircleCurve->setShortcutContext(Qt::ApplicationShortcut);
        actionSnapXGrid = new QAction(UiView);
        actionSnapXGrid->setObjectName(QString::fromUtf8("actionSnapXGrid"));
        actionSnapXGrid->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/actions/res_icon_grid_snapX.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSnapXGrid->setIcon(icon9);
        actionSnapXGrid->setShortcutContext(Qt::ApplicationShortcut);
        actionLockPos = new QAction(UiView);
        actionLockPos->setObjectName(QString::fromUtf8("actionLockPos"));
        actionLockPos->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/actions/res_icon_lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLockPos->setIcon(icon10);
        actionLockPos->setShortcutContext(Qt::ApplicationShortcut);
        actionToggleLabel = new QAction(UiView);
        actionToggleLabel->setObjectName(QString::fromUtf8("actionToggleLabel"));
        actionToggleLabel->setCheckable(true);
        actionToggleLabel->setChecked(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/actions/res_icon_label.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionToggleLabel->setIcon(icon11);
        actionToggleLabel->setShortcutContext(Qt::ApplicationShortcut);
        actionPatchesFolder = new QAction(UiView);
        actionPatchesFolder->setObjectName(QString::fromUtf8("actionPatchesFolder"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/actions/res_icon_patches_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPatchesFolder->setIcon(icon12);
        actionPatchesFolder->setShortcutContext(Qt::ApplicationShortcut);
        actionAbout = new QAction(UiView);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setShortcutContext(Qt::ApplicationShortcut);
        actionAbout->setMenuRole(QAction::AboutRole);
        actionImport_SVG = new QAction(UiView);
        actionImport_SVG->setObjectName(QString::fromUtf8("actionImport_SVG"));
        actionImport_SVG->setShortcutContext(Qt::ApplicationShortcut);
        actionImport_Text = new QAction(UiView);
        actionImport_Text->setObjectName(QString::fromUtf8("actionImport_Text"));
        actionImport_Text->setShortcutContext(Qt::ApplicationShortcut);
        actionShowEditor = new QAction(UiView);
        actionShowEditor->setObjectName(QString::fromUtf8("actionShowEditor"));
        actionShowEditor->setCheckable(true);
        actionShowEditor->setChecked(false);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/actions/res_icon_editor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowEditor->setIcon(icon13);
        actionShowEditor->setShortcutContext(Qt::ApplicationShortcut);
        actionReloadScript = new QAction(UiView);
        actionReloadScript->setObjectName(QString::fromUtf8("actionReloadScript"));
        actionReloadScript->setShortcutContext(Qt::ApplicationShortcut);
        actionLight = new QAction(UiView);
        actionLight->setObjectName(QString::fromUtf8("actionLight"));
        actionLight->setCheckable(true);
        actionLight->setChecked(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/actions/res_icon_light.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLight->setIcon(icon14);
        actionLight->setShortcutContext(Qt::ApplicationShortcut);
        actionImport_Background = new QAction(UiView);
        actionImport_Background->setObjectName(QString::fromUtf8("actionImport_Background"));
        actionImport_Background->setShortcutContext(Qt::ApplicationShortcut);
        actionAllow_triggers_selection = new QAction(UiView);
        actionAllow_triggers_selection->setObjectName(QString::fromUtf8("actionAllow_triggers_selection"));
        actionAllow_triggers_selection->setCheckable(true);
        actionAllow_triggers_selection->setChecked(true);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/general/res_icon_trigger_select.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAllow_triggers_selection->setIcon(icon15);
        actionAllow_triggers_selection->setShortcutContext(Qt::ApplicationShortcut);
        actionAllow_curves_selection = new QAction(UiView);
        actionAllow_curves_selection->setObjectName(QString::fromUtf8("actionAllow_curves_selection"));
        actionAllow_curves_selection->setCheckable(true);
        actionAllow_curves_selection->setChecked(true);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/general/res_icon_curve_select.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAllow_curves_selection->setIcon(icon16);
        actionAllow_curves_selection->setShortcutContext(Qt::ApplicationShortcut);
        actionAllow_cursors_selection = new QAction(UiView);
        actionAllow_cursors_selection->setObjectName(QString::fromUtf8("actionAllow_cursors_selection"));
        actionAllow_cursors_selection->setCheckable(true);
        actionAllow_cursors_selection->setChecked(true);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/general/res_icon_cursor_select.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAllow_cursors_selection->setIcon(icon17);
        actionAllow_cursors_selection->setShortcutContext(Qt::ApplicationShortcut);
        actionSnapYGrid = new QAction(UiView);
        actionSnapYGrid->setObjectName(QString::fromUtf8("actionSnapYGrid"));
        actionSnapYGrid->setCheckable(true);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/actions/res_icon_grid_snapY.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSnapYGrid->setIcon(icon18);
        actionSnapYGrid->setShortcutContext(Qt::ApplicationShortcut);
        actionDistributeH = new QAction(UiView);
        actionDistributeH->setObjectName(QString::fromUtf8("actionDistributeH"));
        actionDistributeH->setShortcutContext(Qt::ApplicationShortcut);
        actionDistributeV = new QAction(UiView);
        actionDistributeV->setObjectName(QString::fromUtf8("actionDistributeV"));
        actionDistributeV->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_left = new QAction(UiView);
        actionAlign_left->setObjectName(QString::fromUtf8("actionAlign_left"));
        actionAlign_left->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_center = new QAction(UiView);
        actionAlign_center->setObjectName(QString::fromUtf8("actionAlign_center"));
        actionAlign_center->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_right = new QAction(UiView);
        actionAlign_right->setObjectName(QString::fromUtf8("actionAlign_right"));
        actionAlign_right->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_top = new QAction(UiView);
        actionAlign_top->setObjectName(QString::fromUtf8("actionAlign_top"));
        actionAlign_top->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_middle = new QAction(UiView);
        actionAlign_middle->setObjectName(QString::fromUtf8("actionAlign_middle"));
        actionAlign_middle->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_bottom = new QAction(UiView);
        actionAlign_bottom->setObjectName(QString::fromUtf8("actionAlign_bottom"));
        actionAlign_bottom->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_circle = new QAction(UiView);
        actionAlign_circle->setObjectName(QString::fromUtf8("actionAlign_circle"));
        actionAlign_circle->setShortcutContext(Qt::ApplicationShortcut);
        actionAlign_ellipse = new QAction(UiView);
        actionAlign_ellipse->setObjectName(QString::fromUtf8("actionAlign_ellipse"));
        actionAlign_ellipse->setShortcutContext(Qt::ApplicationShortcut);
        actionSnapshot = new QAction(UiView);
        actionSnapshot->setObjectName(QString::fromUtf8("actionSnapshot"));
        actionSnapshot->setShortcutContext(Qt::ApplicationShortcut);
        actionResize = new QAction(UiView);
        actionResize->setObjectName(QString::fromUtf8("actionResize"));
        actionResize->setShortcutContext(Qt::ApplicationShortcut);
        actionShowTimer = new QAction(UiView);
        actionShowTimer->setObjectName(QString::fromUtf8("actionShowTimer"));
        actionShowTimer->setCheckable(true);
        actionShowTimer->setChecked(false);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/actions/res_icon_timer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowTimer->setIcon(icon19);
        actionShowTimer->setShortcutContext(Qt::ApplicationShortcut);
        actionPerformance = new QAction(UiView);
        actionPerformance->setObjectName(QString::fromUtf8("actionPerformance"));
        actionPerformance->setCheckable(true);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/actions/res_icon_performance.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPerformance->setIcon(icon20);
        actionPerformance->setShortcutContext(Qt::ApplicationShortcut);
        actionAddTimeline = new QAction(UiView);
        actionAddTimeline->setObjectName(QString::fromUtf8("actionAddTimeline"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/actions/res_icon_timeline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddTimeline->setIcon(icon21);
        actionPlaySelected = new QAction(UiView);
        actionPlaySelected->setObjectName(QString::fromUtf8("actionPlaySelected"));
        actionPlaySelected->setCheckable(true);
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/actions/res_icon_play_selected.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlaySelected->setIcon(icon22);
        actionDrawFreeCurveSimple = new QAction(UiView);
        actionDrawFreeCurveSimple->setObjectName(QString::fromUtf8("actionDrawFreeCurveSimple"));
        actionDrawFreeCurveSimple->setCheckable(true);
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/actions/res_icon_curveFree_simple.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawFreeCurveSimple->setIcon(icon23);
        actionDrawFreeCurveSimple->setShortcutContext(Qt::ApplicationShortcut);
        actionDrawPointCurveSimple = new QAction(UiView);
        actionDrawPointCurveSimple->setObjectName(QString::fromUtf8("actionDrawPointCurveSimple"));
        actionDrawPointCurveSimple->setCheckable(true);
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/actions/res_icon_curvePoint_simple.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawPointCurveSimple->setIcon(icon24);
        actionDrawPointCurveSimple->setShortcutContext(Qt::ApplicationShortcut);
        actionAddMathCurveSimple = new QAction(UiView);
        actionAddMathCurveSimple->setObjectName(QString::fromUtf8("actionAddMathCurveSimple"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/actions/res_icon_curveEq_simple.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddMathCurveSimple->setIcon(icon25);
        actionAddMathCurveSimple->setShortcutContext(Qt::ApplicationShortcut);
        actionAddMathCurve = new QAction(UiView);
        actionAddMathCurve->setObjectName(QString::fromUtf8("actionAddMathCurve"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/actions/res_icon_curveEq.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddMathCurve->setIcon(icon26);
        actionAddMathCurve->setShortcutContext(Qt::ApplicationShortcut);
        actionShowHelp = new QAction(UiView);
        actionShowHelp->setObjectName(QString::fromUtf8("actionShowHelp"));
        actionShowHelp->setCheckable(true);
        actionShowHelp->setChecked(true);
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/actions/res_icon_help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowHelp->setIcon(icon27);
        actionShowHelp->setShortcutContext(Qt::ApplicationShortcut);
        actionPreferences = new QAction(UiView);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        actionSave_score_as = new QAction(UiView);
        actionSave_score_as->setObjectName(QString::fromUtf8("actionSave_score_as"));
        actionClose_score = new QAction(UiView);
        actionClose_score->setObjectName(QString::fromUtf8("actionClose_score"));
        centralwidget = new QWidget(UiView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageRender = new QWidget();
        pageRender->setObjectName(QString::fromUtf8("pageRender"));
        horizontalLayout_2 = new QHBoxLayout(pageRender);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        render = new UiRender(pageRender);
        render->setObjectName(QString::fromUtf8("render"));

        horizontalLayout_2->addWidget(render);

        stackedWidget->addWidget(pageRender);
        pagePerf = new QWidget();
        pagePerf->setObjectName(QString::fromUtf8("pagePerf"));
        verticalLayout = new QVBoxLayout(pagePerf);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        performanceLayout = new QHBoxLayout();
        performanceLayout->setSpacing(15);
        performanceLayout->setObjectName(QString::fromUtf8("performanceLayout"));
        performancePreview = new QCheckBox(pagePerf);
        performancePreview->setObjectName(QString::fromUtf8("performancePreview"));
        performancePreview->setChecked(true);

        performanceLayout->addWidget(performancePreview);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        performanceLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(performanceLayout);

        renderPreview = new UiRenderPreview(pagePerf);
        renderPreview->setObjectName(QString::fromUtf8("renderPreview"));

        verticalLayout->addWidget(renderPreview);

        verticalLayout->setStretch(1, 300);
        stackedWidget->addWidget(pagePerf);

        horizontalLayout->addWidget(stackedWidget);

        UiView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UiView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1094, 22));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuGrid_size = new QMenu(menuView);
        menuGrid_size->setObjectName(QString::fromUtf8("menuGrid_size"));
        menuPlayback = new QMenu(menubar);
        menuPlayback->setObjectName(QString::fromUtf8("menuPlayback"));
        menuAlignment = new QMenu(menubar);
        menuAlignment->setObjectName(QString::fromUtf8("menuAlignment"));
        menuAlignH = new QMenu(menuAlignment);
        menuAlignH->setObjectName(QString::fromUtf8("menuAlignH"));
        menuAlignV = new QMenu(menuAlignment);
        menuAlignV->setObjectName(QString::fromUtf8("menuAlignV"));
        UiView->setMenuBar(menubar);
        transportDock = new QDockWidget(UiView);
        transportDock->setObjectName(QString::fromUtf8("transportDock"));
        transportDock->setMinimumSize(QSize(54, 38));
        transportDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        transportDock->setAllowedAreas(Qt::BottomDockWidgetArea);
        transport = new Transport();
        transport->setObjectName(QString::fromUtf8("transport"));
        transportDock->setWidget(transport);
        UiView->addDockWidget(Qt::BottomDockWidgetArea, transportDock);
        inspecteurDock = new QDockWidget(UiView);
        inspecteurDock->setObjectName(QString::fromUtf8("inspecteurDock"));
        inspecteurDock->setMinimumSize(QSize(370, 38));
        inspecteurDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        inspecteurDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        inspector = new UiInspector();
        inspector->setObjectName(QString::fromUtf8("inspector"));
        inspecteurDock->setWidget(inspector);
        UiView->addDockWidget(Qt::RightDockWidgetArea, inspecteurDock);
        toolBarAdd = new QToolBar(UiView);
        toolBarAdd->setObjectName(QString::fromUtf8("toolBarAdd"));
        toolBarAdd->setIconSize(QSize(32, 32));
        UiView->addToolBar(Qt::TopToolBarArea, toolBarAdd);
        statusBar = new QStatusBar(UiView);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        UiView->setStatusBar(statusBar);
        toolBarView = new QToolBar(UiView);
        toolBarView->setObjectName(QString::fromUtf8("toolBarView"));
        toolBarView->setIconSize(QSize(32, 32));
        UiView->addToolBar(Qt::TopToolBarArea, toolBarView);
        toolBarWindow = new QToolBar(UiView);
        toolBarWindow->setObjectName(QString::fromUtf8("toolBarWindow"));
        toolBarWindow->setIconSize(QSize(32, 32));
        UiView->addToolBar(Qt::TopToolBarArea, toolBarWindow);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuPlayback->menuAction());
        menubar->addAction(menuAlignment->menuAction());
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionDuplicate);
        menuEdit->addAction(actionCut);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelect_all);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionDrawTriggers);
        menuEdit->addAction(actionAddFreeCursor);
        menuEdit->addAction(actionAddCircleCurve);
        menuEdit->addAction(actionDrawFreeCurve);
        menuEdit->addAction(actionDrawPointCurve);
        menuEdit->addAction(actionAddMathCurve);
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_score_as);
        menuFile->addAction(actionReloadScript);
        menuFile->addAction(actionClose_score);
        menuFile->addSeparator();
        menuFile->addAction(actionImport_Text);
        menuFile->addAction(actionImport_SVG);
        menuFile->addAction(actionImport_Background);
        menuFile->addSeparator();
        menuFile->addAction(actionPreferences);
        menuFile->addAction(actionAbout);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuView->addAction(actionFullscreen);
        menuView->addAction(actionPerformance);
        menuView->addSeparator();
        menuView->addAction(actionToggle_Inspector);
        menuView->addAction(actionToggle_Transport);
        menuView->addAction(actionShowEditor);
        menuView->addAction(actionShowTimer);
        menuView->addSeparator();
        menuView->addAction(actionGrid);
        menuView->addAction(actionSnapXGrid);
        menuView->addAction(actionSnapYGrid);
        menuView->addAction(menuGrid_size->menuAction());
        menuView->addSeparator();
        menuView->addAction(actionZoom_in);
        menuView->addAction(actionZoom_initial);
        menuView->addAction(actionZoom_out);
        menuView->addSeparator();
        menuView->addAction(actionResize);
        menuView->addAction(actionSnapshot);
        menuView->addSeparator();
        menuView->addAction(actionLight);
        menuGrid_size->addAction(action10Seconds);
        menuGrid_size->addAction(action1second);
        menuGrid_size->addAction(action500Milliseconds);
        menuGrid_size->addAction(action100Milliseconds);
        menuGrid_size->addAction(action10Milliseconds);
        menuGrid_size->addAction(actionCustomValue);
        menuPlayback->addAction(actionPlay_pause);
        menuPlayback->addAction(actionFast_rewind);
        menuAlignment->addAction(menuAlignH->menuAction());
        menuAlignment->addAction(menuAlignV->menuAction());
        menuAlignment->addSeparator();
        menuAlignment->addAction(actionDistributeH);
        menuAlignment->addAction(actionDistributeV);
        menuAlignment->addAction(actionAlign_circle);
        menuAlignment->addAction(actionAlign_ellipse);
        menuAlignH->addAction(actionAlign_left);
        menuAlignH->addAction(actionAlign_center);
        menuAlignH->addAction(actionAlign_right);
        menuAlignV->addAction(actionAlign_top);
        menuAlignV->addAction(actionAlign_middle);
        menuAlignV->addAction(actionAlign_bottom);
        toolBarAdd->addAction(actionDrawTriggers);
        toolBarAdd->addSeparator();
        toolBarAdd->addAction(actionAddCircleCurve);
        toolBarAdd->addAction(actionDrawFreeCurve);
        toolBarAdd->addAction(actionDrawPointCurve);
        toolBarAdd->addAction(actionAddMathCurve);
        toolBarAdd->addSeparator();
        toolBarAdd->addAction(actionAddFreeCursor);
        toolBarAdd->addAction(actionAddTimeline);
        toolBarAdd->addSeparator();
        toolBarAdd->addAction(actionDrawFreeCurveSimple);
        toolBarAdd->addAction(actionDrawPointCurveSimple);
        toolBarAdd->addAction(actionAddMathCurveSimple);
        toolBarView->addAction(actionPlaySelected);
        toolBarView->addAction(actionAllow_triggers_selection);
        toolBarView->addAction(actionAllow_curves_selection);
        toolBarView->addAction(actionAllow_cursors_selection);
        toolBarView->addSeparator();
        toolBarView->addAction(actionLockPos);
        toolBarView->addAction(actionToggleLabel);
        toolBarView->addAction(actionSnapXGrid);
        toolBarView->addAction(actionSnapYGrid);
        toolBarWindow->addAction(actionFullscreen);
        toolBarWindow->addAction(actionPerformance);
        toolBarWindow->addAction(actionShowEditor);
        toolBarWindow->addAction(actionShowTimer);
        toolBarWindow->addAction(actionShowHelp);
        toolBarWindow->addSeparator();
        toolBarWindow->addAction(actionLight);
        toolBarWindow->addSeparator();
        toolBarWindow->addAction(actionPatchesFolder);

        retranslateUi(UiView);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UiView);
    } // setupUi

    void retranslateUi(QMainWindow *UiView)
    {
        UiView->setWindowTitle(QCoreApplication::translate("UiView", "IanniX \342\200\224 View", nullptr));
        actionUndo->setText(QCoreApplication::translate("UiView", "Undo", nullptr));
#if QT_CONFIG(tooltip)
        actionUndo->setToolTip(QCoreApplication::translate("UiView", "Undo last action", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRedo->setText(QCoreApplication::translate("UiView", "Redo", nullptr));
#if QT_CONFIG(tooltip)
        actionRedo->setToolTip(QCoreApplication::translate("UiView", "Redo last action", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRedo->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("UiView", "Copy", nullptr));
#if QT_CONFIG(tooltip)
        actionCopy->setToolTip(QCoreApplication::translate("UiView", "Copies selected objects to clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("UiView", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("UiView", "Paste", nullptr));
#if QT_CONFIG(tooltip)
        actionPaste->setToolTip(QCoreApplication::translate("UiView", "Pastes copied objects from clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("UiView", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("UiView", "Cut", nullptr));
#if QT_CONFIG(tooltip)
        actionCut->setToolTip(QCoreApplication::translate("UiView", "Copies to clipboard and deletes selected objects", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("UiView", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelect_all->setText(QCoreApplication::translate("UiView", "Select all", nullptr));
#if QT_CONFIG(tooltip)
        actionSelect_all->setToolTip(QCoreApplication::translate("UiView", "Selects all the selectable objects in the score", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSelect_all->setShortcut(QCoreApplication::translate("UiView", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete->setText(QCoreApplication::translate("UiView", "Delete", nullptr));
#if QT_CONFIG(tooltip)
        actionDelete->setToolTip(QCoreApplication::translate("UiView", "Deletes selected objects", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDelete->setShortcut(QCoreApplication::translate("UiView", "Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew->setText(QCoreApplication::translate("UiView", "New score", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("UiView", "Creates a new empty score", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("UiView", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("UiView", "Open a score\342\200\246", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("UiView", "Opens a IanniX project", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("UiView", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("UiView", "Save score", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("UiView", "Saves the current score", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("UiView", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("UiView", "Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("UiView", "Quits IanniX", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFullscreen->setText(QCoreApplication::translate("UiView", "Fullscreen", nullptr));
        actionFullscreen->setIconText(QCoreApplication::translate("UiView", "Fullscreen", nullptr));
#if QT_CONFIG(tooltip)
        actionFullscreen->setToolTip(QCoreApplication::translate("UiView", "Switches score to fullscreen", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionFullscreen->setShortcut(QCoreApplication::translate("UiView", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionToggle_Inspector->setText(QCoreApplication::translate("UiView", "Inspector panel", nullptr));
#if QT_CONFIG(tooltip)
        actionToggle_Inspector->setToolTip(QCoreApplication::translate("UiView", "Shows/hides the inspector panel", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionToggle_Inspector->setStatusTip(QCoreApplication::translate("UiView", "Inspector panel|The inspector panel allows you to configure your objects, scores and settings. All the actions and options are in this very important area.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionToggle_Inspector->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Alt+I", nullptr));
#endif // QT_CONFIG(shortcut)
        actionToggle_Transport->setText(QCoreApplication::translate("UiView", "Transport panel", nullptr));
#if QT_CONFIG(tooltip)
        actionToggle_Transport->setToolTip(QCoreApplication::translate("UiView", "Shows/hides the transport panel", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionToggle_Transport->setStatusTip(QCoreApplication::translate("UiView", "Transport panel|The transport panel allows you to start, stop or set up the playback of your score.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionToggle_Transport->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Alt+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPlay_pause->setText(QCoreApplication::translate("UiView", "Play/pause", nullptr));
#if QT_CONFIG(tooltip)
        actionPlay_pause->setToolTip(QCoreApplication::translate("UiView", "Plays or pauses the playback", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionPlay_pause->setStatusTip(QCoreApplication::translate("UiView", "Play/pause|Press this button to start or pause the playback", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionPlay_pause->setShortcut(QCoreApplication::translate("UiView", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFast_rewind->setText(QCoreApplication::translate("UiView", "Rewind score", nullptr));
        actionFast_rewind->setIconText(QCoreApplication::translate("UiView", "Rewind score", nullptr));
#if QT_CONFIG(tooltip)
        actionFast_rewind->setToolTip(QCoreApplication::translate("UiView", "Rewinds the playback", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionFast_rewind->setStatusTip(QCoreApplication::translate("UiView", "Fast rewind|By pressing the button, IanniX will play or pause the score playback. If nothing happened, be sure the score speed is positive!", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionFast_rewind->setShortcut(QCoreApplication::translate("UiView", "F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionGrid->setText(QCoreApplication::translate("UiView", "Grid && axis", nullptr));
        actionGrid->setIconText(QCoreApplication::translate("UiView", "Grid & axis", nullptr));
#if QT_CONFIG(tooltip)
        actionGrid->setToolTip(QCoreApplication::translate("UiView", "Shows/hides score grid and axis", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionGrid->setShortcut(QCoreApplication::translate("UiView", "Ctrl+G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDuplicate->setText(QCoreApplication::translate("UiView", "Duplicate", nullptr));
#if QT_CONFIG(tooltip)
        actionDuplicate->setToolTip(QCoreApplication::translate("UiView", "Duplicates selected objects", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDuplicate->setShortcut(QCoreApplication::translate("UiView", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoom_in->setText(QCoreApplication::translate("UiView", "Zoom in", nullptr));
#if QT_CONFIG(tooltip)
        actionZoom_in->setToolTip(QCoreApplication::translate("UiView", "Zooms in", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoom_in->setShortcut(QCoreApplication::translate("UiView", "Ctrl++", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoom_out->setText(QCoreApplication::translate("UiView", "Zoom out", nullptr));
#if QT_CONFIG(tooltip)
        actionZoom_out->setToolTip(QCoreApplication::translate("UiView", "Zooms out", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoom_out->setShortcut(QCoreApplication::translate("UiView", "Ctrl+-", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoom_initial->setText(QCoreApplication::translate("UiView", "Reset zoom (100%)", nullptr));
#if QT_CONFIG(tooltip)
        actionZoom_initial->setToolTip(QCoreApplication::translate("UiView", "Restores initial zoom", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionZoom_initial->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+0", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDrawFreeCurve->setText(QCoreApplication::translate("UiView", "Draw a smooth curve with a cursor", nullptr));
        actionDrawFreeCurve->setIconText(QCoreApplication::translate("UiView", "Draw a smooth curve with a cursor", nullptr));
#if QT_CONFIG(tooltip)
        actionDrawFreeCurve->setToolTip(QCoreApplication::translate("UiView", "Draws a smooth curve with a cursor", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDrawFreeCurve->setStatusTip(QCoreApplication::translate("UiView", "Curves|In IanniX vocabulary, a curve is a spatial trajectory. A curve can have two functions: first, it is a support for cursors, defining where they are going on; secondly, it can be a variation of values read by cursors (intersection of cursor with the curve). Curves can be circular, segments of lines, B\303\251zier curves or math equations.\\n\\nAfter creating a curve, you can edit it:\\n- Double click on the path to add a point\\n- Control+double click on a point of the curve to remove it (Command key for Mac users)\\n- Double-click on a point to enable or disable smoothing\\n\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionDrawFreeCurve->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDrawPointCurve->setText(QCoreApplication::translate("UiView", "Draw straight curve with a cursor", nullptr));
        actionDrawPointCurve->setIconText(QCoreApplication::translate("UiView", "Draw straight curve with a cursor", nullptr));
#if QT_CONFIG(tooltip)
        actionDrawPointCurve->setToolTip(QCoreApplication::translate("UiView", "Draws straight curve with a cursor", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDrawPointCurve->setStatusTip(QCoreApplication::translate("UiView", "Curves|In IanniX vocabulary, a curve is a spatial trajectory. A curve can have two functions: first, it is a support for cursors, defining where they are going on; secondly, it can be a variation of values read by cursors (intersection of cursor with the curve). Curves can be circular, segments of lines, B\303\251zier curves or math equations.\\n\\nAfter creating a curve, you can edit it:\\n- Double click on the path to add a point\\n- Control+click on a point of the curve to remove it (Command key for Mac users)\\n- Double-click on a point to enable or disable smoothing\\n- Shift+double-click to resample curve (it means you transform the curve into many segments)\\n\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionDrawPointCurve->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDrawTriggers->setText(QCoreApplication::translate("UiView", "Add triggers", nullptr));
        actionDrawTriggers->setIconText(QCoreApplication::translate("UiView", "Add triggers", nullptr));
#if QT_CONFIG(tooltip)
        actionDrawTriggers->setToolTip(QCoreApplication::translate("UiView", "Adds triggers", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDrawTriggers->setStatusTip(QCoreApplication::translate("UiView", "Triggers|In IanniX vocabulary, a trigger is an event that is fired by cursors. It is very similar to a note in music, but of course IanniX allows you to fire any kind of event, depending on the software linked with your score.\\n\\nDouble click on a trigger to change the sent messages when fired.\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionDrawTriggers->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddFreeCursor->setText(QCoreApplication::translate("UiView", "Add a cursor", nullptr));
        actionAddFreeCursor->setIconText(QCoreApplication::translate("UiView", "Add a cursor", nullptr));
#if QT_CONFIG(tooltip)
        actionAddFreeCursor->setToolTip(QCoreApplication::translate("UiView", "Adds a cursor on the selected curves", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAddFreeCursor->setStatusTip(QCoreApplication::translate("UiView", "Cursors|In IanniX vocabulary, a cursor is a playhead. While running on a curve, it can fire triggers, sends its position or reads curve values. If the cursor is not linked to a curve, it will not move automatically, but you can control it from another software or hardware (sensors\342\200\246).\\n\\nDouble click on a cursor to change the sent messages.", nullptr));
#endif // QT_CONFIG(statustip)
        action10Seconds->setText(QCoreApplication::translate("UiView", "10 seconds", nullptr));
#if QT_CONFIG(tooltip)
        action10Seconds->setToolTip(QCoreApplication::translate("UiView", "Changes the grid base unit to 10 seconds", nullptr));
#endif // QT_CONFIG(tooltip)
        action1second->setText(QCoreApplication::translate("UiView", "1 second", nullptr));
#if QT_CONFIG(tooltip)
        action1second->setToolTip(QCoreApplication::translate("UiView", "Changes the grid base unit to 1 second", nullptr));
#endif // QT_CONFIG(tooltip)
        action500Milliseconds->setText(QCoreApplication::translate("UiView", "500 milliseconds", nullptr));
#if QT_CONFIG(tooltip)
        action500Milliseconds->setToolTip(QCoreApplication::translate("UiView", "Changes the grid base unit to 500 milliseconds", nullptr));
#endif // QT_CONFIG(tooltip)
        action100Milliseconds->setText(QCoreApplication::translate("UiView", "100 milliseconds", nullptr));
#if QT_CONFIG(tooltip)
        action100Milliseconds->setToolTip(QCoreApplication::translate("UiView", "Changes the grid base unit to 100 milliseconds", nullptr));
#endif // QT_CONFIG(tooltip)
        action10Milliseconds->setText(QCoreApplication::translate("UiView", "10 milliseconds", nullptr));
#if QT_CONFIG(tooltip)
        action10Milliseconds->setToolTip(QCoreApplication::translate("UiView", "Changes the grid base unit to 10 milliseconds", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCustomValue->setText(QCoreApplication::translate("UiView", "Custom value", nullptr));
#if QT_CONFIG(tooltip)
        actionCustomValue->setToolTip(QCoreApplication::translate("UiView", "Changes the grid base unit to a custom value", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAddCircleCurve->setText(QCoreApplication::translate("UiView", "Add circular curves with cursors", nullptr));
        actionAddCircleCurve->setIconText(QCoreApplication::translate("UiView", "Add circular curves with cursors", nullptr));
#if QT_CONFIG(tooltip)
        actionAddCircleCurve->setToolTip(QCoreApplication::translate("UiView", "Adds circular curves with cursors", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAddCircleCurve->setStatusTip(QCoreApplication::translate("UiView", "Curves|In IanniX vocabulary, a curve is a spatial trajectory. A curve can have two functions: first, it is a support for cursors, defining where they are going on; secondly, it can be a variation of values read by cursors (intersection of cursor with the curve). Curves can be circular, segments of lines, B\303\251zier curves or math equations.\\n\\nAfter creating a curve, you can edit it:\\n- Double click on the path to add a point\\n- Control+double click on a point of the curve to remove it (Command key for Mac users)\\n- Double-click on a point to enable or disable smoothing\\n\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionAddCircleCurve->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSnapXGrid->setText(QCoreApplication::translate("UiView", "Snap to X-grid", nullptr));
        actionSnapXGrid->setIconText(QCoreApplication::translate("UiView", "Snap to X-grid", nullptr));
#if QT_CONFIG(tooltip)
        actionSnapXGrid->setToolTip(QCoreApplication::translate("UiView", "Snaps mouse actions on vertical grid", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLockPos->setText(QCoreApplication::translate("UiView", "Lock objects position", nullptr));
        actionLockPos->setIconText(QCoreApplication::translate("UiView", "Lock objects position", nullptr));
#if QT_CONFIG(tooltip)
        actionLockPos->setToolTip(QCoreApplication::translate("UiView", "Locks objects position", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionLockPos->setStatusTip(QCoreApplication::translate("UiView", "Locking objects|Activate this option if you only want to navigate safely (without moving objects accidentally) in the score.", nullptr));
#endif // QT_CONFIG(statustip)
        actionToggleLabel->setText(QCoreApplication::translate("UiView", "Objects labels", nullptr));
        actionToggleLabel->setIconText(QCoreApplication::translate("UiView", "Objects labels", nullptr));
#if QT_CONFIG(tooltip)
        actionToggleLabel->setToolTip(QCoreApplication::translate("UiView", "Show/hides objects labels", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionToggleLabel->setStatusTip(QCoreApplication::translate("UiView", "Objects labels|Disable this option if you don't want to display object labels (if you've set labels in inspector) on the score. Displaying label may be CPU intensive so disabling them may increase video frame rate.", nullptr));
#endif // QT_CONFIG(statustip)
        actionPatchesFolder->setText(QCoreApplication::translate("UiView", "Third party software examples", nullptr));
        actionPatchesFolder->setIconText(QCoreApplication::translate("UiView", "Third party software examples", nullptr));
#if QT_CONFIG(tooltip)
        actionPatchesFolder->setToolTip(QCoreApplication::translate("UiView", "Opens a folder where you can find third party software examples", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionPatchesFolder->setStatusTip(QCoreApplication::translate("UiView", "Third party software examples|IanniX only sequences events and values to other software or hardware. Click on this button to open examples using third party software that are compatible with IanniX.\\nBe aware that these represent just samples, many other software tools are compatible with IanniX! Have a look at the configuration tab in inspector panel to see all the available interfaces.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAbout->setText(QCoreApplication::translate("UiView", "About IanniX", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("UiView", "Opens About IanniX window", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAbout->setStatusTip(QCoreApplication::translate("UiView", "About IanniX|IanniX is open source and developed by volunteers. Discover who they are!", nullptr));
#endif // QT_CONFIG(statustip)
        actionImport_SVG->setText(QCoreApplication::translate("UiView", "Import SVG file\342\200\246", nullptr));
#if QT_CONFIG(tooltip)
        actionImport_SVG->setToolTip(QCoreApplication::translate("UiView", "Imports SVG file to score", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionImport_SVG->setStatusTip(QCoreApplication::translate("UiView", "SVG files|IanniX can import SVG files (open vectorial format). Be aware that IanniX tries to make the best it can to import data from SVG, but some of SVG features are not compatible with IanniX philosophy.\\nFinaly, SVG is based on print or display units whereas IanniX is based on seconds; you may need to rescale the imported data.", nullptr));
#endif // QT_CONFIG(statustip)
        actionImport_Text->setText(QCoreApplication::translate("UiView", "Import text\342\200\246", nullptr));
#if QT_CONFIG(tooltip)
        actionImport_Text->setToolTip(QCoreApplication::translate("UiView", "Imports glyphs (characters) to score", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionImport_Text->setStatusTip(QCoreApplication::translate("UiView", "Text import|IanniX can import glyphs (characters) from fonts. Note that font sizes are based on print or display units whereas IanniX is based on seconds; you may need to rescale the imported data.", nullptr));
#endif // QT_CONFIG(statustip)
        actionShowEditor->setText(QCoreApplication::translate("UiView", "Script editor window", nullptr));
        actionShowEditor->setIconText(QCoreApplication::translate("UiView", "Script editor window", nullptr));
#if QT_CONFIG(tooltip)
        actionShowEditor->setToolTip(QCoreApplication::translate("UiView", "Shows/hides script editor window", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionShowEditor->setStatusTip(QCoreApplication::translate("UiView", "Script editor window|The script editor window allows you to add code to your score. Scripts are based on the Javascript language and some special methods allows you to control IanniX. Have a look at examples to start working with scripts!", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionShowEditor->setShortcut(QCoreApplication::translate("UiView", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReloadScript->setText(QCoreApplication::translate("UiView", "Reload score", nullptr));
#if QT_CONFIG(tooltip)
        actionReloadScript->setToolTip(QCoreApplication::translate("UiView", "Reloads the current script if you made changes with an external editor", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionReloadScript->setShortcut(QCoreApplication::translate("UiView", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLight->setText(QCoreApplication::translate("UiView", "Lighter color theme", nullptr));
        actionLight->setIconText(QCoreApplication::translate("UiView", "Lighter color theme", nullptr));
#if QT_CONFIG(tooltip)
        actionLight->setToolTip(QCoreApplication::translate("UiView", "Changes the color theme", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionLight->setStatusTip(QCoreApplication::translate("UiView", "Color themes|IanniX comes with two color themes: one is bright (for editing, with colors inspired by paper and pencil), the other is dark (for performance, not dazzling on stage, in lighting desk or sound controls)", nullptr));
#endif // QT_CONFIG(statustip)
        actionImport_Background->setText(QCoreApplication::translate("UiView", "Import a background image\342\200\246", nullptr));
#if QT_CONFIG(tooltip)
        actionImport_Background->setToolTip(QCoreApplication::translate("UiView", "Imports a background image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionImport_Background->setStatusTip(QCoreApplication::translate("UiView", "Background picture|Background picture is not only an esthetical feature, it also allows you to trace curves manually from the image.\\nNote that pictures are based on pixels whereas IanniX is based on seconds; you may need to rescale the picture in inspector panel.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAllow_triggers_selection->setText(QCoreApplication::translate("UiView", "Allow triggers selection", nullptr));
        actionAllow_triggers_selection->setIconText(QCoreApplication::translate("UiView", "Allow triggers selection", nullptr));
#if QT_CONFIG(tooltip)
        actionAllow_triggers_selection->setToolTip(QCoreApplication::translate("UiView", "Allows triggers selection", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAllow_triggers_selection->setStatusTip(QCoreApplication::translate("UiView", "Objects selection|Use these options to enable or disable selection of objects regarding their nature. It can be very useful if you need to change for example all the messages of the triggers.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAllow_curves_selection->setText(QCoreApplication::translate("UiView", "Allow curves selection", nullptr));
        actionAllow_curves_selection->setIconText(QCoreApplication::translate("UiView", "Allow curves selection", nullptr));
#if QT_CONFIG(tooltip)
        actionAllow_curves_selection->setToolTip(QCoreApplication::translate("UiView", "Allows curves selection", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAllow_curves_selection->setStatusTip(QCoreApplication::translate("UiView", "Objects selection|Use these options to enable or disable selection of objects regarding their nature. It can be very useful if you need to change for example all the messages of the triggers.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAllow_cursors_selection->setText(QCoreApplication::translate("UiView", "Allow cursors selection", nullptr));
        actionAllow_cursors_selection->setIconText(QCoreApplication::translate("UiView", "Allow cursors selection", nullptr));
#if QT_CONFIG(tooltip)
        actionAllow_cursors_selection->setToolTip(QCoreApplication::translate("UiView", "Allows cursors selection", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAllow_cursors_selection->setStatusTip(QCoreApplication::translate("UiView", "Objects selection|Use these options to enable or disable selection of objects regarding their nature. It can be very useful if you need to change for example all the messages of the triggers.", nullptr));
#endif // QT_CONFIG(statustip)
        actionSnapYGrid->setText(QCoreApplication::translate("UiView", "Snap to Y-grid", nullptr));
        actionSnapYGrid->setIconText(QCoreApplication::translate("UiView", "Snap to Y-grid", nullptr));
#if QT_CONFIG(tooltip)
        actionSnapYGrid->setToolTip(QCoreApplication::translate("UiView", "Snaps mouse actions on horizontal grid", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDistributeH->setText(QCoreApplication::translate("UiView", "Distribute horizontally", nullptr));
#if QT_CONFIG(tooltip)
        actionDistributeH->setToolTip(QCoreApplication::translate("UiView", "Distributes objects horizontally from the leftmost object to the rightmost object", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDistributeV->setText(QCoreApplication::translate("UiView", "Distribute vertically", nullptr));
#if QT_CONFIG(tooltip)
        actionDistributeV->setToolTip(QCoreApplication::translate("UiView", "Distributes objects vertically from the topmost object to the bottommost object", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_left->setText(QCoreApplication::translate("UiView", "Align left", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_left->setToolTip(QCoreApplication::translate("UiView", "Aligns objects on the leftmost object", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_center->setText(QCoreApplication::translate("UiView", "Align center", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_center->setToolTip(QCoreApplication::translate("UiView", "Aligns objects on the horizontal center of the selection", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_right->setText(QCoreApplication::translate("UiView", "Align right", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_right->setToolTip(QCoreApplication::translate("UiView", "Aligns objects on the rightmost object", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_top->setText(QCoreApplication::translate("UiView", "Align top", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_top->setToolTip(QCoreApplication::translate("UiView", "Aligns objects on the topmost object", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_middle->setText(QCoreApplication::translate("UiView", "Align middle", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_middle->setToolTip(QCoreApplication::translate("UiView", "Aligns objects on the vertical center of the selection", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_bottom->setText(QCoreApplication::translate("UiView", "Align bottom", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_bottom->setToolTip(QCoreApplication::translate("UiView", "Aligns objects on the bottommost object", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_circle->setText(QCoreApplication::translate("UiView", "Distribute circulary", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_circle->setToolTip(QCoreApplication::translate("UiView", "Aligns objects as a circle", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlign_ellipse->setText(QCoreApplication::translate("UiView", "Distribute on ellipse", nullptr));
#if QT_CONFIG(tooltip)
        actionAlign_ellipse->setToolTip(QCoreApplication::translate("UiView", "Aligns objects as an ellipse", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSnapshot->setText(QCoreApplication::translate("UiView", "Make a high resolution snapshot", nullptr));
#if QT_CONFIG(tooltip)
        actionSnapshot->setToolTip(QCoreApplication::translate("UiView", "Generates a high resolution picture of the score on your desktop", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSnapshot->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionResize->setText(QCoreApplication::translate("UiView", "Resize viewport", nullptr));
#if QT_CONFIG(tooltip)
        actionResize->setToolTip(QCoreApplication::translate("UiView", "Resizes score viewport to specific dimensions", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowTimer->setText(QCoreApplication::translate("UiView", "Timer window", nullptr));
        actionShowTimer->setIconText(QCoreApplication::translate("UiView", "Timer window", nullptr));
#if QT_CONFIG(tooltip)
        actionShowTimer->setToolTip(QCoreApplication::translate("UiView", "Shows/hides the timer window", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionShowTimer->setStatusTip(QCoreApplication::translate("UiView", "Timer window|The timer window is useful if you need a big readable timer on stage for performance.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionShowTimer->setShortcut(QCoreApplication::translate("UiView", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPerformance->setText(QCoreApplication::translate("UiView", "Performance mode", nullptr));
        actionPerformance->setIconText(QCoreApplication::translate("UiView", "Performance mode", nullptr));
#if QT_CONFIG(tooltip)
        actionPerformance->setToolTip(QCoreApplication::translate("UiView", "Switches to performance mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionPerformance->setStatusTip(QCoreApplication::translate("UiView", "Performance mode|While in performance mode, you can take benefits of the multiple display outputs. For example, you can make a video projection of the score on the second video output while keeping a preview and a control of your score on your laptop main display.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionPerformance->setShortcut(QCoreApplication::translate("UiView", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAddTimeline->setText(QCoreApplication::translate("UiView", "Add a timeline", nullptr));
        actionAddTimeline->setIconText(QCoreApplication::translate("UiView", "Add a timeline", nullptr));
#if QT_CONFIG(tooltip)
        actionAddTimeline->setToolTip(QCoreApplication::translate("UiView", "Adds a timeline", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAddTimeline->setStatusTip(QCoreApplication::translate("UiView", "Timeline|A timeline is just a classical horizontal curve with a cursor reading curves values. This feature only adds a curve with a cursor that has a pre-configured message for curve value reading (intersection of cursor with the curves)", nullptr));
#endif // QT_CONFIG(statustip)
        actionPlaySelected->setText(QCoreApplication::translate("UiView", "Only play selected objects", nullptr));
        actionPlaySelected->setIconText(QCoreApplication::translate("UiView", "Only play selected objects", nullptr));
#if QT_CONFIG(tooltip)
        actionPlaySelected->setToolTip(QCoreApplication::translate("UiView", "If checked, only selected objects will output messages", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDrawFreeCurveSimple->setText(QCoreApplication::translate("UiView", "Draw a smooth curve", nullptr));
        actionDrawFreeCurveSimple->setIconText(QCoreApplication::translate("UiView", "Draw a smooth curve", nullptr));
#if QT_CONFIG(tooltip)
        actionDrawFreeCurveSimple->setToolTip(QCoreApplication::translate("UiView", "Draws a smooth curve", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDrawFreeCurveSimple->setStatusTip(QCoreApplication::translate("UiView", "Curves|In IanniX vocabulary, a curve is a spatial trajectory. A curve can have two functions: first, it is a support for cursors, defining where they are going on; secondly, it can be a variation of values read by cursors (intersection of cursor with the curve). Curves can be circular, segments of lines, B\303\251zier curves or math equations.\\n\\nAfter creating a curve, you can edit it:\\n- Double click on the path to add a point\\n- Control+double click on a point of the curve to remove it (Command key for Mac users)\\n- Double-click on a point to enable or disable smoothing\\n\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
        actionDrawPointCurveSimple->setText(QCoreApplication::translate("UiView", "Draw straight curve", nullptr));
        actionDrawPointCurveSimple->setIconText(QCoreApplication::translate("UiView", "Draw straight curve", nullptr));
#if QT_CONFIG(tooltip)
        actionDrawPointCurveSimple->setToolTip(QCoreApplication::translate("UiView", "Draws straight curve", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionDrawPointCurveSimple->setStatusTip(QCoreApplication::translate("UiView", "Curves|In IanniX vocabulary, a curve is a spatial trajectory. A curve can have two functions: first, it is a support for cursors, defining where they are going on; secondly, it can be a variation of values read by cursors (intersection of cursor with the curve). Curves can be circular, segments of lines, B\303\251zier curves or math equations.\\n\\nAfter creating a curve, you can edit it:\\n- Double click on the path to add a point\\n- Control+double click on a point of the curve to remove it (Command key for Mac users)\\n- Double-click on a point to enable or disable smoothing\\n\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAddMathCurveSimple->setText(QCoreApplication::translate("UiView", "Add a math curve", nullptr));
        actionAddMathCurveSimple->setIconText(QCoreApplication::translate("UiView", "Add a math curve", nullptr));
#if QT_CONFIG(tooltip)
        actionAddMathCurveSimple->setToolTip(QCoreApplication::translate("UiView", "Adds a math curve", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAddMathCurveSimple->setStatusTip(QCoreApplication::translate("UiView", "Curves|In IanniX vocabulary, a curve is a spatial trajectory. A curve can have two functions: first, it is a support for cursors, defining where they are going on; secondly, it can be a variation of values read by cursors (intersection of cursor with the curve). Curves can be circular, segments of lines, B\303\251zier curves or math equations.\\n\\nAfter creating a curve, you can edit it:\\n- Double click on the path to add a point\\n- Control+double click on a point of the curve to remove it (Command key for Mac users)\\n- Double-click on a point to enable or disable smoothing\\n\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
        actionAddMathCurve->setText(QCoreApplication::translate("UiView", "Add a math curve with a cursor", nullptr));
        actionAddMathCurve->setIconText(QCoreApplication::translate("UiView", "Add a math curve with a cursor", nullptr));
#if QT_CONFIG(tooltip)
        actionAddMathCurve->setToolTip(QCoreApplication::translate("UiView", "Adds a math curve with a cursor", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionAddMathCurve->setStatusTip(QCoreApplication::translate("UiView", "Curves|In IanniX vocabulary, a curve is a spatial trajectory. A curve can have two functions: first, it is a support for cursors, defining where they are going on; secondly, it can be a variation of values read by cursors (intersection of cursor with the curve). Curves can be circular, segments of lines, B\303\251zier curves or math equations.\\n\\nAfter creating a curve, you can edit it:\\n- Double click on the path to add a point\\n- Control+double click on a point of the curve to remove it (Command key for Mac users)\\n- Double-click on a point to enable or disable smoothing\\n\\nPress ESC or click again on the toolbar button to stop edition.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionAddMathCurve->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+M", nullptr));
#endif // QT_CONFIG(shortcut)
        actionShowHelp->setText(QCoreApplication::translate("UiView", "Help window", nullptr));
        actionShowHelp->setIconText(QCoreApplication::translate("UiView", "Help window", nullptr));
#if QT_CONFIG(tooltip)
        actionShowHelp->setToolTip(QCoreApplication::translate("UiView", "Shows/hides the help window", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionShowHelp->setShortcut(QCoreApplication::translate("UiView", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPreferences->setText(QCoreApplication::translate("UiView", "Preferences", nullptr));
#if QT_CONFIG(tooltip)
        actionPreferences->setToolTip(QCoreApplication::translate("UiView", "Opens the Config tab in Inspector", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave_score_as->setText(QCoreApplication::translate("UiView", "Save score as\342\200\246", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_score_as->setShortcut(QCoreApplication::translate("UiView", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose_score->setText(QCoreApplication::translate("UiView", "Close score", nullptr));
#if QT_CONFIG(shortcut)
        actionClose_score->setShortcut(QCoreApplication::translate("UiView", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(statustip)
        pagePerf->setStatusTip(QCoreApplication::translate("UiView", "Performance preview|While in performance mode, you can take benefits of the multiple display outputs. For example, you can make a video projection of the score on the second video output while keeping a preview and a control of your score on your laptop main display.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(statustip)
        performancePreview->setStatusTip(QCoreApplication::translate("UiView", "Allows you to keep a video thumbnail in the IanniX main window", nullptr));
#endif // QT_CONFIG(statustip)
        performancePreview->setText(QCoreApplication::translate("UiView", "REFRESH THIS PREVIEW", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("UiView", "Edit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("UiView", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("UiView", "Display", nullptr));
        menuGrid_size->setTitle(QCoreApplication::translate("UiView", "Grid resolution", nullptr));
        menuPlayback->setTitle(QCoreApplication::translate("UiView", "Playback", nullptr));
        menuAlignment->setTitle(QCoreApplication::translate("UiView", "Arrange objects", nullptr));
        menuAlignH->setTitle(QCoreApplication::translate("UiView", "Align horizontally", nullptr));
        menuAlignV->setTitle(QCoreApplication::translate("UiView", "Align vertically", nullptr));
        transportDock->setWindowTitle(QCoreApplication::translate("UiView", "Transport", nullptr));
        inspecteurDock->setWindowTitle(QCoreApplication::translate("UiView", "Inspector", nullptr));
        toolBarAdd->setWindowTitle(QCoreApplication::translate("UiView", "Objects creation", nullptr));
        toolBarView->setWindowTitle(QCoreApplication::translate("UiView", "View options", nullptr));
        toolBarWindow->setWindowTitle(QCoreApplication::translate("UiView", "Window options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UiView: public Ui_UiView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIVIEW_H
