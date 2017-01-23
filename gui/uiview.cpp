/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (https://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "uiview.h"
#include "ui_uiview.h"

UiView::UiView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiView) {
    ui->setupUi(this);
    isFullScreen = false;
    freehandCurveId = freehandCurveIndex = 0;

    Help::syncHelpWith(ui->actionImport_Text, COMMAND_CURVE_TXT);
    Help::syncHelpWith(ui->actionImport_SVG,  COMMAND_CURVE_PATH);

#ifndef Q_OS_MAC
    ui->actionDelete->setShortcut(QApplication::trUtf8("UiView", "Delete"));
#endif

    //About
    about = new UiAbout();

    //Helper
    help  = new UiHelp();
    connect(&help->visibility, SIGNAL(triggered(bool)), SLOT(showHelp()));
    connect(ui->statusBar, SIGNAL(messageChanged(QString)), help, SLOT(statusHelp(QString)));
    ui->statusBar->setVisible(false);
    help->visibility.setAction(ui->actionShowHelp, "showHelp");

    ui->render->defaultStatusTip = ui->render->statusTip();
    ui->render->curveStatusTip   = ui->actionDrawFreeCurve->statusTip().remove(tr("\nPress ESC or click again on the toolbar button to stop edition."));
    ui->render->cursorStatusTip  = ui->actionAddFreeCursor->statusTip().remove(tr("\nPress ESC or click again on the toolbar button to stop edition."));
    ui->render->triggerStatusTip = ui->actionDrawTriggers ->statusTip().remove(tr("\nPress ESC or click again on the toolbar button to stop edition."));

    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - rect().center());

    connect(ui->render, SIGNAL(editingMove(NxPoint,bool,bool)), SLOT(editingMove(NxPoint,bool,bool)));
    connect(ui->render, SIGNAL(editingStart(NxPoint)),     SLOT(editingStart(NxPoint)));
    connect(ui->render, SIGNAL(editingStop()),             SLOT(editingStop()));

    connect(ui->actionNew,               SIGNAL(triggered()), ui->render, SLOT(actionNew()));
    connect(ui->actionClose_score,       SIGNAL(triggered()), ui->render, SLOT(actionNew()));
    connect(ui->actionOpen,              SIGNAL(triggered()), ui->render, SLOT(actionOpen()));
    connect(ui->actionSave,              SIGNAL(triggered()), ui->render, SLOT(actionSave()));
    connect(ui->actionSave_score_as,     SIGNAL(triggered()), ui->render, SLOT(actionSave_as()));
    connect(ui->actionImport_SVG,        SIGNAL(triggered()), SLOT(actionImportSVG()));
    connect(ui->actionImport_Background, SIGNAL(triggered()), SLOT(actionImportBackground()));
    connect(ui->actionImport_Text,       SIGNAL(triggered()), SLOT(actionImportText()));

    connect(ui->actionRedo,              SIGNAL(triggered()), ui->render, SLOT(actionRedo()));
    connect(ui->actionUndo,              SIGNAL(triggered()), ui->render, SLOT(actionUndo()));
    connect(ui->actionCopy,              SIGNAL(triggered()), ui->render, SLOT(actionCopy()));
    connect(ui->actionPaste,             SIGNAL(triggered()), ui->render, SLOT(actionPaste()));
    connect(ui->actionDuplicate,         SIGNAL(triggered()), ui->render, SLOT(actionDuplicate()));
    connect(ui->actionCut,               SIGNAL(triggered()), ui->render, SLOT(actionCut()));
    connect(ui->actionSelect_all,        SIGNAL(triggered()), ui->render, SLOT(actionSelect_all()));
    connect(ui->actionDelete,            SIGNAL(triggered()), ui->render, SLOT(actionDelete()));
    connect(ui->actionResize,            SIGNAL(triggered()), SLOT(actionResize()));
    connect(ui->actionSnapshot,          SIGNAL(triggered()), SLOT(actionSnapshot()));

    connect(ui->actionZoom_in,           SIGNAL(triggered()), ui->render, SLOT(zoomIn()));
    connect(ui->actionZoom_out,          SIGNAL(triggered()), ui->render, SLOT(zoomOut()));
    connect(ui->actionZoom_initial,      SIGNAL(triggered()), ui->render, SLOT(zoomInitial()));
    connect(ui->actionAbout,             SIGNAL(triggered()), about, SLOT(show()));
    connect(ui->actionPreferences,       SIGNAL(triggered()), ui->inspector, SLOT(showConfigTab()));
    connect(ui->actionQuit,              SIGNAL(triggered()), SLOT(close()));
    connect(ui->actionToggle_Inspector,  SIGNAL(triggered()), SLOT(showInspector()));
    connect(ui->actionToggle_Transport,  SIGNAL(triggered()), SLOT(showTransport()));
    connect(ui->actionPatchesFolder,     SIGNAL(triggered()), SLOT(actionPatchesFolder()));
    connect(ui->actionLockPos,           SIGNAL(triggered()), SLOT(editingStop()));
    Application::colorTheme            .setAction(ui->actionLight,                    "guiColorTheme");
    Application::paintAxisGrid         .setAction(ui->actionGrid,                     "guiPaintAxisGrid");
    Application::paintLabel            .setAction(ui->actionToggleLabel,              "guiPaintLabel");
    Application::mouseSnapX            .setAction(ui->actionSnapXGrid,                "guiMouseSnapX");
    Application::mouseSnapY            .setAction(ui->actionSnapYGrid,                "guiMouseSnapY");
    Application::allowLockPos          .setAction(ui->actionLockPos,                  "guiAllowLockPos");
    Application::allowSelectionCursors .setAction(ui->actionAllow_cursors_selection,  "guiAllowSelectionCursors");
    Application::allowSelectionCurves  .setAction(ui->actionAllow_curves_selection,   "guiAllowSelectionCurves");
    Application::allowSelectionTriggers.setAction(ui->actionAllow_triggers_selection, "guiAllowSelectionTriggers");
    Application::allowPlaySelected     .setAction(ui->actionPlaySelected,             "guiAllowPlaySelected");

    connect(ui->actionFullscreen,           SIGNAL(triggered()), SLOT(goToFullscreen()));
    connect(ui->actionPerformance,          SIGNAL(triggered()), SLOT(actionPerformance()));

    connect(ui->actionPlay_pause,           SIGNAL(triggered()), SLOT(actionPlay_pause()));
    connect(ui->actionFast_rewind,          SIGNAL(triggered()), SLOT(actionFast_rewind()));

    connect(ui->actionDrawFreeCurve,        SIGNAL(triggered()), SLOT(actionDrawFreeCurve()));
    connect(ui->actionDrawPointCurve,       SIGNAL(triggered()), SLOT(actionDrawPointCurve()));
    connect(ui->actionDrawFreeCurveSimple,  SIGNAL(triggered()), SLOT(actionDrawFreeCurveSimple()));
    connect(ui->actionDrawPointCurveSimple, SIGNAL(triggered()), SLOT(actionDrawPointCurveSimple()));
    connect(ui->actionDrawTriggers,         SIGNAL(triggered()), SLOT(actionDrawTriggers()));
    connect(ui->actionAddFreeCursor,        SIGNAL(triggered()), SLOT(actionAddFreeCursor()));
    connect(ui->actionAddCircleCurve,       SIGNAL(triggered()), SLOT(actionCircleCurve()));
    connect(ui->actionAddMathCurve,         SIGNAL(triggered()), SLOT(actionAddMathCurve()));
    connect(ui->actionAddMathCurveSimple,   SIGNAL(triggered()), SLOT(actionAddMathCurveSimple()));
    connect(ui->actionAddTimeline,          SIGNAL(triggered()), SLOT(actionAddTimeline()));

    connect(ui->actionShowEditor,           SIGNAL(triggered()), SLOT(showEditor()));
    connect(ui->actionShowTimer,            SIGNAL(triggered()), SLOT(showTimer()));
    connect(ui->actionReloadScript,         SIGNAL(triggered()), SLOT(actionReloadScript()));

    connect(ui->action10Seconds,            SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action1second,              SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action500Milliseconds,      SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action100Milliseconds,      SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action10Milliseconds,       SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->actionCustomValue,          SIGNAL(triggered()), SLOT(gridChange()));

    connect(ui->actionAlign_bottom,         SIGNAL(triggered()), SLOT(actionAlign_bottom()));
    connect(ui->actionAlign_center,         SIGNAL(triggered()), SLOT(actionAlign_center()));
    connect(ui->actionAlign_left,           SIGNAL(triggered()), SLOT(actionAlign_left()));
    connect(ui->actionAlign_middle,         SIGNAL(triggered()), SLOT(actionAlign_middle()));
    connect(ui->actionAlign_right,          SIGNAL(triggered()), SLOT(actionAlign_right()));
    connect(ui->actionAlign_top,            SIGNAL(triggered()), SLOT(actionAlign_top()));
    connect(ui->actionDistributeH,          SIGNAL(triggered()), SLOT(actionDistributeH()));
    connect(ui->actionDistributeV,          SIGNAL(triggered()), SLOT(actionDistributeV()));
    connect(ui->actionAlign_circle,         SIGNAL(triggered()), SLOT(actionAlign_circle()));
    connect(ui->actionAlign_ellipse,        SIGNAL(triggered()), SLOT(actionAlign_ellipse()));

    delete ui->renderPreview;
    ui->renderPreview = new UiRenderPreview(ui->pagePerf, ui->render);
    ui->pagePerf->layout()->addWidget(ui->renderPreview);
    fullscreenDisplays = QApplication::desktop();
    connect(fullscreenDisplays, SIGNAL(screenCountChanged(int)), SLOT(fullscreenDisplaysCountChanged()));
    fullscreenDisplaysCountChanged();
    //delete ui->actionPerformance;
    ui->render->setFocus();
}

UiView::~UiView() {
    delete ui;
}

void UiView::toggleFullscreen(bool val) {
    ui->actionFullscreen->setChecked(val);
}


void UiView::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

UiRender* UiView::getRender() const {
    return ui->render;
}
Transport* UiView::getTransport() const {
    return ui->transport;
}
UiInspector* UiView::getInspector() const {
    return ui->inspector;
}
UiRenderPreview* UiView::getRenderPreview() const {
    return ui->renderPreview;
}
bool UiView::getPerformancePreview() const {
    return ui->performancePreview->isChecked();
}

void UiView::keyPressEvent(QKeyEvent *event) {
    ui->render->keyPressEvent(event);
}
void UiView::closeEvent(QCloseEvent *event) {
    emit(actionRouteCloseEvent(event));
    if(about)
        about->close();
    if(help)
        help->close();
}

void UiView::fullscreenDisplaysCountChanged() {
    foreach(QPushButton *fullscreenButton, fullscreenButtons)
        delete fullscreenButton;
    fullscreenButtons.clear();

    for(quint8 fullscreenDisplayIndex = 0 ; fullscreenDisplayIndex < fullscreenDisplays->screenCount() ; fullscreenDisplayIndex++) {
        QPushButton *fullscreenButton = new QPushButton(tr("DISPLAY %1 (%2 x %3)").arg(fullscreenDisplayIndex+1).arg(fullscreenDisplays->screenGeometry(fullscreenDisplayIndex).width()).arg(fullscreenDisplays->screenGeometry(fullscreenDisplayIndex).height()), ui->pagePerf);
        fullscreenButton->setToolTip(tr("Moves the render window on this video output and switches to fullscreen"));
        ui->performanceLayout->addWidget(fullscreenButton);
        connect(fullscreenButton, SIGNAL(released()), SLOT(fullscreenDisplaysSelected()));
        fullscreenButtons.append(fullscreenButton);
    }
}
void UiView::fullscreenDisplaysSelected() {
    qint8 index = fullscreenButtons.indexOf((QPushButton*)sender());
    if(index >= 0)
        goToFullscreen(index);
}

void UiView::goToFullscreen() {
    if(ui->render->parent())    goToFullscreen(fullscreenDisplays->screenNumber(pos()));
    else                        goToFullscreen(fullscreenDisplays->screenNumber(ui->render->pos()));
}
void UiView::goToFullscreen(quint8 screenIndex) {
    if(ui->render->parent()) {
        if(isFullScreen) {
            setWindowState(windowState() & ~Qt::WindowFullScreen);
            ui->render->setCursor(Qt::ArrowCursor);
            ui->toolBarAdd->setVisible(true);
            ui->toolBarView->setVisible(true);
            ui->toolBarWindow->setVisible(true);
            ui->inspector->parentWidget()->setVisible(wasInspectorVisible);
            ui->transport->parentWidget()->setVisible(wasTransportVisible);
            ui->menubar->setVisible(true);
            isFullScreen = false;
            toggleFullscreen(isFullScreen);
        }
        else {
            setWindowState(windowState() | Qt::WindowFullScreen);
            ui->render->setCursor(Qt::BlankCursor);
            ui->toolBarAdd->setVisible(false);
            ui->toolBarView->setVisible(false);
            ui->toolBarWindow->setVisible(false);
            wasInspectorVisible = ui->inspecteurDock->isVisible();
            wasTransportVisible = ui->transportDock->isVisible();
            ui->menubar->setVisible(false);
            ui->inspector->parentWidget()->hide();
            ui->transport->parentWidget()->hide();
            isFullScreen = true;
            toggleFullscreen(isFullScreen);
        }
        //activateWindow();
    }
    else {
        ui->render->hide();
        if(isFullScreen) {
            ui->render->setWindowState(windowState() & ~Qt::WindowFullScreen);
            ui->render->move(previousPos);
            ui->render->setCursor(Qt::ArrowCursor);
            isFullScreen = false;
            toggleFullscreen(isFullScreen);
        }
        else {
            previousPos  = ui->render->pos();
            //previousSize = ui->render->size();

            ui->render->move(fullscreenDisplays->screenGeometry(screenIndex).topLeft());
            ui->render->setWindowState(windowState() | Qt::WindowFullScreen);
            ui->render->setCursor(Qt::BlankCursor);
            isFullScreen = true;
            toggleFullscreen(isFullScreen);
        }
        ui->render->show();
        //ui->render->activateWindow();
    }
    ui->render->selectionClear(true);
}
void UiView::escFullscreen() {
    if(isFullScreen)
        goToFullscreen();
}

void UiView::actionPlay_pause() {
    if(Transport::timerOk)  Application::current->execute(QString("%1").arg(COMMAND_STOP), ExecuteSourceGui);
    else                    Application::current->execute(QString("%1").arg(COMMAND_PLAY), ExecuteSourceGui);
}
void UiView::actionFast_rewind() {
    Application::current->execute(QString("%1").arg(COMMAND_FF), ExecuteSourceGui);
}


void UiView::actionPerformance() {
    if(ui->actionPerformance->isChecked()) {
        fullscreenDisplaysCountChanged();
        ui->render->setPerformanceMode(true);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        ui->render->setPerformanceMode(false);
        ui->stackedWidget->widget(0)->layout()->addWidget(ui->render);
        ui->stackedWidget->setCurrentIndex(0);
    }
}



void UiView::actionImportSVG() {
    QString fileName = QFileDialog::getOpenFileName(0, tr("Select a SVG file…"), QDir::currentPath(), tr("SVG Files") + " (*.svg)");
    if(!fileName.isEmpty())
        emit(actionRouteImportSVG(fileName));
}
void UiView::actionImportBackground() {
    QString fileName = QFileDialog::getOpenFileName(0, tr("Select an image…"), QDir::currentPath(), tr("Images") + " (*.png *.jpg *.jpeg)");
    if(!fileName.isEmpty())
        emit(actionRouteImportBackground(fileName));
}
void UiView::actionImportText() {
    QString font = "";
    QString text = (new UiMessageBox())->getText(tr("Text Import"), tr("Type a character or some text to import in IanniX:"), "");
    if(!text.isEmpty())
        emit(actionRouteImportText(font, text));
}

void UiView::actionSnapshot() {
    bool ok = false;
    qreal scaleFactor = (new UiMessageBox())->getDouble(tr("Score Snapshot"), tr("Snapshot will be saved on your desktop.\nPlease enter a scale factor:"), QPixmap(":/infos/res_info_export.png"), 4, 0.1, 30, 0.25, 2, "times current screen size", false, &ok);
    if(ok)
        ui->render->capture(scaleFactor);
}

void UiView::showTimer() {
    ui->transport->bigTimer->toolbarButton = ui->actionShowTimer;
    if(ui->transport->bigTimer->isVisible())    ui->transport->bigTimer->close();
    else                                        ui->transport->bigTimer->show();
}
void UiView::showHelp() {
    if(help->visibility) {
        if(help->pos() == QPoint(0, 0))
            help->move(QPoint(qMax(0, geometry().left() - help->width()), geometry().center().y() - help->height()));
        UiHelp::statusHelp(ui->render);
        help->show();
    }
    else
        help->close();
}
void UiView::showEditor() {
    ui->transport->editor->toolbarButton = ui->actionShowEditor;
    if(ui->transport->editor->isVisible())  ui->transport->editor->close();
    else                                    ui->transport->editor->show();
}
void UiView::showTransport() {
    ui->transport->toolbarButton = ui->actionToggle_Transport;
    if(ui->transport->isVisible())   ui->transport->parentWidget()->close();
    else                             ui->transport->parentWidget()->show();
}
void UiView::showInspector() {
    ui->inspector->toolbarButton = ui->actionToggle_Inspector;
    if(ui->inspector->isVisible())    ui->inspector->parentWidget()->close();
    else                              ui->inspector->parentWidget()->show();
}


void UiView::unToogleDraw(quint16 id) {
    if(id == 1) {
        ui->actionDrawFreeCurve->setChecked(false);
        ui->actionDrawFreeCurveSimple->setChecked(false);
    }
    else if(id == 2) {
        ui->actionDrawPointCurve->setChecked(false);
        ui->actionDrawPointCurveSimple->setChecked(false);
    }
    else if(id == 3) {
        ui->actionDrawTriggers->setChecked(false);
    }
    else if(id == 4) {
        ui->actionAddCircleCurve->setChecked(false);
    }
    else {
        ui->actionDrawTriggers->setChecked(false);
        ui->actionDrawFreeCurve->setChecked(false);
        ui->actionDrawFreeCurveSimple->setChecked(false);
        ui->actionDrawPointCurve->setChecked(false);
        ui->actionDrawPointCurveSimple->setChecked(false);
        ui->actionAddCircleCurve->setChecked(false);
    }
}

void UiView::gridChange() {
    QAction *action = (QAction*)sender();
    bool ok = true;
    if(action == ui->action10Seconds)
        Render::axisGrid = 10;
    else if(action == ui->action1second)
        Render::axisGrid = 1;
    else if(action == ui->action500Milliseconds)
        Render::axisGrid = 0.5;
    else if(action == ui->action100Milliseconds)
        Render::axisGrid = 0.1;
    else if(action == ui->action10Milliseconds)
        Render::axisGrid = 0.01;
    else if(action == ui->actionCustomValue) {
        qreal val = (new UiMessageBox())->getDouble(tr("Custom grid value"), tr("Enter the desired grid time value in seconds:"), 0.500, 0.001, 999, 0.1, 3, "seconds", &ok);
        if(ok) {
            ui->actionCustomValue->setText(tr("Custom value:") + QString(" %1 ").arg(val) + tr("sec"));
            Render::axisGrid = val;
        }
    }
    if(ok) {
        ui->action10Seconds->setChecked(false);
        ui->action1second->setChecked(false);
        ui->action500Milliseconds->setChecked(false);
        ui->action100Milliseconds->setChecked(false);
        ui->action10Milliseconds->setChecked(false);
        ui->actionCustomValue->setChecked(false);
        action->setChecked(true);
    }
}


void UiView::actionResize() {
    QSize currentSize = ui->render->size();
    QStringList newSizes = (new UiMessageBox())->getText(tr("Viewport Resize"), tr("New viewport size:"), tr("%1 x %2").arg(currentSize.width()).arg(currentSize.height())).split("x", QString::SkipEmptyParts);
    if(newSizes.count() == 2) {
        QSize newSize(newSizes.at(0).toUInt(), newSizes.at(1).toUInt());
        if((newSize.width() > 0) && (newSize.height() > 0))
            actionResize(newSize);
    }
}
void UiView::actionResize(QSize newSize) {
    resize(size() + newSize - ui->render->size());
}







void UiView::actionDrawFreeCurve(bool cursor) {
    if((Render::editingMode == EditingModeFree) && (Render::editing))
        editingStop();
    else {
        freehandCurveId = freehandCurveIndex = 0;
        freehandCurveNeedsCursor = cursor;
        unToogleDraw(2);
        unToogleDraw(3);
        unToogleDraw(4);
        ui->render->setEditingMode(EditingModeFree);
    }
}
void UiView::actionDrawPointCurve(bool cursor) {
    if((Render::editingMode == EditingModePoint) && (Render::editing))
        editingStop();
    else {
        freehandCurveId = freehandCurveIndex = 0;
        freehandCurveNeedsCursor = cursor;
        unToogleDraw(1);
        unToogleDraw(3);
        unToogleDraw(4);
        ui->render->setEditingMode(EditingModePoint);
    }
}
void UiView::actionDrawTriggers() {
    if((Render::editingMode == EditingModeTriggers) && (Render::editing))
        editingStop();
    else {
        unToogleDraw(1);
        unToogleDraw(2);
        unToogleDraw(4);
        ui->render->setEditingMode(EditingModeTriggers);
    }
}
void UiView::actionAddTimeline() {
    unToogleDraw(1);
    unToogleDraw(2);
    unToogleDraw(3);
    unToogleDraw(4);
    ui->render->selectionClear(true);
    quint16 id1 = Application::current->execute("add curve auto", ExecuteSourceGui).toUInt();
    Application::current->execute("setpointat " + QString::number(id1) + " 0 -5 0", ExecuteSourceGui);
    Application::current->execute("setpointat " + QString::number(id1) + " 1  5 0", ExecuteSourceGui);
    quint16 id2 = Application::current->execute("add cursor auto", ExecuteSourceGui).toUInt();
    Application::current->execute("setwidth " + QString::number(id2) + " 5", ExecuteSourceGui);
    Application::current->execute("setcurve " + QString::number(id2) + " lastCurve", ExecuteSourceGui);
    Application::current->execute("setboundssourcemode " + QString::number(id2) + " 1", ExecuteSourceGui);
    Application::current->execute("setmessage " + QString::number(id2) + " 20, " + Application::defaultMessageCurve, ExecuteSourceGui);
    ui->render->selectionAdd((NxObject*)Application::current->getObjectById(id1));
    ui->render->selectionAdd((NxObject*)Application::current->getObjectById(id2));
}
void UiView::actionAddMathCurve() {
    unToogleDraw(1);
    unToogleDraw(2);
    unToogleDraw(3);
    unToogleDraw(4);
    ui->render->selectionClear(true);
    quint16 id = Application::current->execute("add curve auto", ExecuteSourceGui).toUInt();
    Application::current->execute("setequation " + QString::number(id) + " cartesian 10*param1*t , sin(param2*20*t*PI) * exp(1-4*param3*t) , 2*param5*cos(8*param4*t*PI)", ExecuteSourceGui);
    ui->render->selectionAdd((NxObject*)Application::current->getObjectById(id));
    ui->inspector->showSpaceTab();
    id = Application::current->execute("add cursor auto", ExecuteSourceGui).toUInt();
    Application::current->execute("setcurve " + QString::number(id) + " lastCurve", ExecuteSourceGui);
}
void UiView::actionAddMathCurveSimple() {
    unToogleDraw(1);
    unToogleDraw(2);
    unToogleDraw(3);
    unToogleDraw(4);
    ui->render->selectionClear(true);
    quint16 id = Application::current->execute("add curve auto", ExecuteSourceGui).toUInt();
    Application::current->execute("setequation " + QString::number(id) + " cartesian 10*param1*t , sin(param2*20*t*PI) * exp(1-4*param3*t) , 0", ExecuteSourceGui);
    ui->render->selectionAdd((NxObject*)Application::current->getObjectById(id));
    ui->inspector->showSpaceTab();
}
void UiView::actionAddFreeCursor() {
    bool freeCursor = true;
    unToogleDraw(1);
    unToogleDraw(2);
    unToogleDraw(3);
    unToogleDraw(4);
    freehandCurveNeedsCursor = false;
    editingStop();
    Application::current->pushSnapshot();
    foreach(const NxObject *object, *(ui->render->getSelection())) {
        if(object->getType() == ObjectsTypeCurve) {
            freeCursor = false;
            NxCurve *curve = (NxCurve*)object;
            quint16 cursorId = Application::current->execute(QString("add cursor auto"), ExecuteSourceGui).toUInt();
            Application::current->execute(QString("%1 %2 %3").arg(COMMAND_CURSOR_CURVE).arg(cursorId).arg(curve->getId()), ExecuteSourceGui);
            Application::current->execute(QString("%1 %2 %3 0 end").arg(COMMAND_CURSOR_OFFSET).arg(cursorId).arg(curve->getMaxOffset() / 2), ExecuteSourceGui);
        }
    }
    if(freeCursor)
        Application::current->execute(QString("add cursor auto"), ExecuteSourceGui).toUInt();
}


void UiView::actionCircleCurve() {
    if((Render::editingMode == EditingModeCircle) && (Render::editing))
        editingStop();
    else {
        unToogleDraw(1);
        unToogleDraw(2);
        unToogleDraw(3);
        ui->render->setEditingMode(EditingModeCircle);
    }
}

void UiView::editingStart(const NxPoint & point) {
    if(Render::editing) {
        if((Render::editingMode == EditingModeFree) || (Render::editingMode == EditingModePoint)) {
            editingStartPoint = point;
            freehandCurveIndex = 1;
            Application::current->pushSnapshot();
            freehandCurveId = Application::current->execute("add curve auto", ExecuteSourceGui).toUInt();
            Application::current->execute(QString("%1 %2 %3 %4 0").arg(COMMAND_POS).arg(freehandCurveId).arg(editingStartPoint.x()).arg(editingStartPoint.y()), ExecuteSourceGui);
            if(Render::editingMode == EditingModeFree)
                Application::current->execute(QString("%1 %2 0 0 0 0").arg(COMMAND_CURVE_POINT_SMOOTH).arg(freehandCurveId), ExecuteSourceGui);
            else
                Application::current->execute(QString("%1 %2 0 0 0 0").arg(COMMAND_CURVE_POINT).arg(freehandCurveId), ExecuteSourceGui);

        }
        else if(Render::editingMode == EditingModeTriggers) {
            Application::current->pushSnapshot();
            quint16 triggerId = Application::current->execute("add trigger auto", ExecuteSourceGui).toUInt();
            Application::current->execute(QString("%1 %2 %3 %4 0").arg(COMMAND_POS).arg(triggerId).arg(point.x()).arg(point.y()), ExecuteSourceGui);
        }
        else if(Render::editingMode == EditingModeCircle) {
            Application::current->pushSnapshot();
            quint16 curveId = Application::current->execute(QString("add curve auto"), ExecuteSourceGui).toUInt();
            Application::current->execute(QString("%1 %2 %3 %4 0").arg(COMMAND_POS).arg(curveId).arg(point.x()).arg(point.y()), ExecuteSourceGui);
            Application::current->execute(QString("%1 %2 2 2").arg(COMMAND_CURVE_ELL).arg(curveId), ExecuteSourceGui);
            quint16 cursorId = Application::current->execute(QString("add cursor auto"), ExecuteSourceGui).toUInt();
            Application::current->execute(QString("%1 %2 %3").arg(COMMAND_CURSOR_CURVE).arg(cursorId).arg(curveId), ExecuteSourceGui);
            Application::current->execute(QString("%1 %2 0 0 1").arg(COMMAND_CURSOR_START).arg(cursorId), ExecuteSourceGui);
        }
    }
}
void UiView::editingStop() {
    if((Render::editing) && ((Render::editingMode == EditingModeFree) || (Render::editingMode == EditingModePoint))) {
        if(freehandCurveIndex > 0) {
            Application::current->execute(QString("%1 %2 %3").arg(COMMAND_CURVE_POINT_RMV).arg(freehandCurveId).arg(freehandCurveIndex), ExecuteSourceSystem);
            freehandCurveIndex--;
        }
    }
    editingStopWithoutRemoval();
}
void UiView::editingStopWithoutRemoval(bool isLoop) {
    if(freehandCurveIndex > 0) {
        if(freehandCurveNeedsCursor) {
            quint16 cursorId = Application::current->execute(QString("add cursor auto"), ExecuteSourceGui).toUInt();
            Application::current->execute(QString("%1 %2 %3").arg(COMMAND_CURSOR_CURVE).arg(cursorId).arg(freehandCurveId), ExecuteSourceGui);
            if(isLoop)
                Application::current->execute(QString("%1 %2 0 0 1").arg(COMMAND_CURSOR_START).arg(cursorId), ExecuteSourceGui);
        }
    }
    else
        Application::current->execute(QString("%1 %2").arg(COMMAND_REMOVE).arg(freehandCurveId), ExecuteSourceSystem);
    freehandCurveId = 0;
    freehandCurveIndex = 0;
    freehandCurveNeedsCursor = false;

    unToogleDraw(0);
    ui->render->unsetEditing();
}

void UiView::editingMove(const NxPoint & point, bool add, bool mouseState) {
    bool isLoop = false;
    NxPoint newPoint = point - editingStartPoint;
    if((!mouseState) && (freehandCurveIndex > 1) && ((qAbs(newPoint.x()) < (0.25 * Render::zoomLinear)) && (qAbs(newPoint.y()) < (0.25 * Render::zoomLinear)) && (qAbs(newPoint.z()) < (0.25 * Render::zoomLinear)))) {
        isLoop = true;
        newPoint = NxPoint();
    }

    if((Render::editing) && (Render::editingMode == EditingModeFree)) {
        Application::current->execute(QString("%1 %2 %3 %4 %5").arg(COMMAND_CURVE_POINT_SMOOTH).arg(freehandCurveId).arg(freehandCurveIndex).arg(newPoint.x()).arg(newPoint.y()), ExecuteSourceGui);
        if(add)
            freehandCurveIndex++;
    }
    else if((Render::editing) && (Render::editingMode == EditingModePoint)) {
        Application::current->execute(QString("%1 %2 %3 %4 %5").arg(COMMAND_CURVE_POINT).arg(freehandCurveId).arg(freehandCurveIndex).arg(newPoint.x()).arg(newPoint.y()), ExecuteSourceGui);
        if(add)
            freehandCurveIndex++;
    }
    if((isLoop) && (add)) {
        freehandCurveIndex--;
        editingStopWithoutRemoval(isLoop);
    }
}
