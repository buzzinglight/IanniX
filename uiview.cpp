/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

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
    ui->render->setFocus();
    isFullScreen = false;

    QRect screen = QApplication::desktop()->geometry();
    move(screen.center() - rect().center());

    connect(ui->actionNew, SIGNAL(triggered()), ui->render, SLOT(actionNew()));
    connect(ui->actionOpen, SIGNAL(triggered()), ui->render, SLOT(actionOpen()));
    connect(ui->actionSave, SIGNAL(triggered()), ui->render, SLOT(actionSave()));
    connect(ui->actionSave_all, SIGNAL(triggered()), ui->render, SLOT(actionSave_all()));
    connect(ui->actionDuplicateScore, SIGNAL(triggered()), ui->render, SLOT(actionDuplicateScore()));
    connect(ui->actionRename, SIGNAL(triggered()), ui->render, SLOT(actionRename()));
    connect(ui->actionRemove, SIGNAL(triggered()), ui->render, SLOT(actionRemove()));
    connect(ui->actionImoprt_SVG, SIGNAL(triggered()), SLOT(actionImportSVG()));
    connect(ui->actionImoprt_Image, SIGNAL(triggered()), SLOT(actionImportImage()));
    connect(ui->actionImoprt_Background, SIGNAL(triggered()), SLOT(actionImportBackground()));
    connect(ui->actionImoprt_Text, SIGNAL(triggered()), SLOT(actionImportText()));

    connect(ui->actionRedo, SIGNAL(triggered()), ui->render, SLOT(actionRedo()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->render, SLOT(actionUndo()));
    connect(ui->actionCopy, SIGNAL(triggered()), ui->render, SLOT(actionCopy()));
    connect(ui->actionPasteScript, SIGNAL(triggered()), SLOT(actionPasteScript()));
    connect(ui->actionCopyScript, SIGNAL(triggered()), ui->render, SLOT(actionCopyScript()));
    connect(ui->actionPaste, SIGNAL(triggered()), ui->render, SLOT(actionPaste()));
    connect(ui->actionDuplicate, SIGNAL(triggered()), ui->render, SLOT(actionDuplicate()));
    connect(ui->actionCut, SIGNAL(triggered()), ui->render, SLOT(actionCut()));
    connect(ui->actionSelect_all, SIGNAL(triggered()), ui->render, SLOT(actionSelect_all()));
    connect(ui->actionDelete, SIGNAL(triggered()), ui->render, SLOT(actionDelete()));
    connect(ui->actionSync, SIGNAL(triggered()), ui->render, SLOT(actionSync()));
    connect(ui->actionSnapshot, SIGNAL(triggered()), SLOT(actionSnapshot()));
    connect(ui->actionResize, SIGNAL(triggered()), SLOT(actionResize()));

    connect(ui->actionFullscreen, SIGNAL(triggered()), SLOT(actionFullscreen()));
    connect(ui->actionToggle_Inspector, SIGNAL(triggered()), SLOT(actionToggle_Inspector()));
    connect(ui->actionToggle_Transport, SIGNAL(triggered()), SLOT(actionToggle_Transport()));
    connect(ui->actionToggle_Autosize, SIGNAL(triggered()), SLOT(actionToggle_Autosize()));
    connect(ui->actionGrid, SIGNAL(triggered()), SLOT(actionGrid()));
    connect(ui->actionZoom_in, SIGNAL(triggered()), SLOT(actionZoom_in()));
    connect(ui->actionZoom_out, SIGNAL(triggered()), SLOT(actionZoom_out()));
    connect(ui->actionZoom_initial, SIGNAL(triggered()), SLOT(actionZoom_initial()));
    connect(ui->actionLight, SIGNAL(triggered(bool)), ui->render, SLOT(setColorTheme(bool)));

    connect(ui->actionToggleLabel, SIGNAL(triggered()), SLOT(actionToggleLabel()));
    connect(ui->actionLockPos, SIGNAL(triggered()), SLOT(actionLockPos()));
    connect(ui->actionPatchesFolder, SIGNAL(triggered()), SLOT(actionPatchesFolder()));
    connect(ui->actionQuit, SIGNAL(triggered()), SLOT(actionQuit()));
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(actionAbout()));

    connect(ui->actionPlay_pause, SIGNAL(triggered()), SLOT(actionPlay_pause()));
    connect(ui->actionFast_rewind, SIGNAL(triggered()), SLOT(actionFast_rewind()));

    connect(ui->actionDrawFreeCurve, SIGNAL(triggered()), SLOT(actionDrawFreeCurve()));
    connect(ui->actionDrawPointCurve, SIGNAL(triggered()), SLOT(actionDrawPointCurve()));
    connect(ui->actionDrawTriggers, SIGNAL(triggered()), SLOT(actionDrawTriggers()));
    connect(ui->actionAddFreeCursor, SIGNAL(triggered()), SLOT(actionAddFreeCursor()));
    connect(ui->actionAddCircleCurve, SIGNAL(triggered()), SLOT(actionCircleCurve()));
    connect(ui->actionSnapXGrid, SIGNAL(triggered()), SLOT(actionSnapXGrid()));
    connect(ui->actionSnapYGrid, SIGNAL(triggered()), SLOT(actionSnapYGrid()));
    connect(ui->actionSnapZGrid, SIGNAL(triggered()), SLOT(actionSnapZGrid()));
    connect(ui->actionShowEditor, SIGNAL(triggered()), SLOT(actionShowEditor()));
    connect(ui->actionShowTimer, SIGNAL(triggered()), SLOT(actionShowTimer()));
    connect(ui->actionReloadScript, SIGNAL(triggered()), SLOT(actionReloadScript()));

    connect(ui->action10Seconds, SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action1second, SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action500Milliseconds, SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action100Milliseconds, SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->action10Milliseconds, SIGNAL(triggered()), SLOT(gridChange()));
    connect(ui->actionCustomValue, SIGNAL(triggered()), SLOT(gridChange()));

    connect(ui->actionOpaque, SIGNAL(triggered()), SLOT(gridOpacityChange()));
    connect(ui->action75_opaque, SIGNAL(triggered()), SLOT(gridOpacityChange()));
    connect(ui->action50_opaque, SIGNAL(triggered()), SLOT(gridOpacityChange()));
    connect(ui->action25_opaque, SIGNAL(triggered()), SLOT(gridOpacityChange()));
    connect(ui->action10_opaque, SIGNAL(triggered()), SLOT(gridOpacityChange()));

    connect(ui->actionAllow_cursors_selection,  SIGNAL(changed()), SLOT(actionSelectionModeChange()));
    connect(ui->actionAllow_curves_selection,   SIGNAL(changed()), SLOT(actionSelectionModeChange()));
    connect(ui->actionAllow_triggers_selection, SIGNAL(changed()), SLOT(actionSelectionModeChange()));

    connect(ui->actionAlign_bottom, SIGNAL(triggered()), SLOT(actionAlign_bottom()));
    connect(ui->actionAlign_center, SIGNAL(triggered()), SLOT(actionAlign_center()));
    connect(ui->actionAlign_left, SIGNAL(triggered()),   SLOT(actionAlign_left()));
    connect(ui->actionAlign_middle, SIGNAL(triggered()), SLOT(actionAlign_middle()));
    connect(ui->actionAlign_right, SIGNAL(triggered()),  SLOT(actionAlign_right()));
    connect(ui->actionAlign_top, SIGNAL(triggered()),    SLOT(actionAlign_top()));
    connect(ui->actionDistributeH, SIGNAL(triggered()),  SLOT(actionDistributeH()));
    connect(ui->actionDistributeV, SIGNAL(triggered()),  SLOT(actionDistributeV()));
    connect(ui->actionAlign_circle, SIGNAL(triggered()), SLOT(actionAlign_circle()));
    connect(ui->actionAlign_ellipse, SIGNAL(triggered()), SLOT(actionAlign_ellipse()));

    connect(ui->actionHelp, SIGNAL(triggered()), SLOT(help()));
}

UiView::~UiView() {
    delete ui;
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
UiTransport* UiView::getTransport() const {
    return ui->transport;
}
UiInspector* UiView::getInspector() const {
    return ui->inspector;
}

void UiView::keyPressEvent(QKeyEvent *event) {
    ui->render->keyPressEvent(event);
}
void UiView::closeEvent(QCloseEvent *event) {
    emit(actionRouteCloseEvent(event));
}

void UiView::tabletEvent(QTabletEvent *) {
    //qDebug("%d : (%f, %f, %f) p=%f angle=%f tp=%f dx=%f dy=%f", event->uniqueId(), event->hiResGlobalPos().x(), event->hiResGlobalPos().y(), event->z(), event->pressure(), event->rotation(), event->tangentialPressure(), event->xTilt(), event->yTilt());
}

void UiView::actionFullscreen() {
    if(isFullScreen) {
        setWindowState(windowState() & ~Qt::WindowFullScreen);
        //setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
        //resize(previousSize);
        //move(previousPos);
        ui->render->setCursor(Qt::ArrowCursor);
        ui->toolBar->setVisible(true);
        ui->inspector->parentWidget()->setVisible(wasInspectorVisible);
        ui->transport->parentWidget()->setVisible(wasTransportVisible);
        ui->statusBar->setVisible(true);
        ui->menubar->setVisible(true);
        isFullScreen = false;
    }
    else {
        previousPos = pos();
        previousSize = size();
        setWindowState(windowState() | Qt::WindowFullScreen);
        //setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        //move(QApplication::desktop()->screenGeometry(pos()).topLeft());
        //resize(QApplication::desktop()->screenGeometry(pos()).size());
        ui->render->setCursor(Qt::BlankCursor);
        ui->toolBar->setVisible(false);
        wasInspectorVisible = ui->inspecteurDock->isVisible();
        wasTransportVisible = ui->transportDock->isVisible();
        ui->statusBar->setVisible(false);
        ui->menubar->setVisible(false);
        ui->inspector->parentWidget()->hide();
        ui->transport->parentWidget()->hide();
        isFullScreen = true;
    }
    activateWindow();
    ui->render->selectionClear(true);
}
void UiView::escFullscreen() {
    if(isFullScreen)
        actionFullscreen();
}

void UiView::actionGrid() {
    if(ui->render->getRenderOptions()->paintAxisGrid) {
        ui->render->getRenderOptions()->paintAxisGrid = false;
        ui->render->getRenderOptions()->paintAxisMain = false;
    }
    else {
        ui->render->getRenderOptions()->paintAxisGrid = true;
        ui->render->getRenderOptions()->paintAxisMain = true;
    }
}

void UiView::actionZoom_in() {
    ui->render->zoomIn();
}
void UiView::actionZoom_out() {
    ui->render->zoomOut();
}
void UiView::actionZoom_initial() {
    ui->render->zoomInitial();
}
void UiView::actionToggleLabel() {
    ui->render->getRenderOptions()->paintLabel = ui->actionToggleLabel->isChecked();
}
void UiView::actionSelectionModeChange() {
    emit(actionRouteSelectionModeChange(ui->actionAllow_cursors_selection->isChecked(), ui->actionAllow_curves_selection->isChecked(), ui->actionAllow_triggers_selection->isChecked()));
}

void UiView::actionImportSVG() {
    QString fileName = QFileDialog::getOpenFileName(0, tr("Select a SVG file…"), QDir::currentPath(), tr("SVG Files") + " (*.svg)");
    if(!fileName.isEmpty())
        emit(actionRouteImportSVG(fileName));
}
void UiView::actionImportImage() {
    QString fileName = QFileDialog::getOpenFileName(0, tr("Select an image…"), QDir::currentPath(), tr("Images") + " (*.png *.jpg *.jpeg)");
    if(!fileName.isEmpty())
        emit(actionRouteImportImage(fileName));
}
void UiView::actionImportBackground() {
    QString fileName = QFileDialog::getOpenFileName(0, tr("Select an image…"), QDir::currentPath(), tr("Images") + " (*.png *.jpg *.jpeg)");
    if(!fileName.isEmpty())
        emit(actionRouteImportBackground(fileName));
}
void UiView::actionImportText() {
    QString font = "";
    QString text = QInputDialog::getText(0, tr("Type a glyph or text…"), tr("Type a glyphe or a text to import in IanniX"), QLineEdit::Normal, "");
    if(!text.isEmpty())
        emit(actionRouteImportText(font, text));
}

void UiView::actionSnapshot() {
    bool ok = false;
    qreal scaleFactor = QInputDialog::getDouble(0, tr("Snaptshot"), tr("Snapshot will be saved on your desktop.\nEntrer a scale factor (1=current size, 2=double size...)"), 5, 0.1, 100, 1, &ok);
    if(ok)
        emit(actionRouteSnaphot(scaleFactor));
}

void UiView::actionLockPos() {
    if(ui->actionDrawTriggers->isChecked()) {
        ui->actionDrawTriggers->setChecked(false);
        emit(actionRouteDrawTriggers());
    }
    else if(ui->actionDrawPointCurve->isChecked()) {
        ui->actionDrawPointCurve->setChecked(false);
        emit(actionRouteDrawPointCurve());
    }
    else if(ui->actionDrawFreeCurve->isChecked()) {
        ui->actionDrawFreeCurve->setChecked(false);
        emit(actionRouteDrawFreeCurve());
    }
    ui->render->setCanObjectDrag(!ui->actionLockPos->isChecked());
}

void UiView::setColorTheme(bool val) {
    ui->actionLight->setChecked(val);
}

void UiView::unToogleDraw(quint16 id) {
    if(id == 1)
        ui->actionDrawFreeCurve->setChecked(false);
    else if(id == 2)
        ui->actionDrawPointCurve->setChecked(false);
    else if(id == 3)
        ui->actionDrawTriggers->setChecked(false);
    else if(id == 4)
        ui->actionAddCircleCurve->setChecked(false);
    else {
        ui->actionDrawTriggers->setChecked(false);
        ui->actionDrawFreeCurve->setChecked(false);
        ui->actionDrawPointCurve->setChecked(false);
        ui->actionAddCircleCurve->setChecked(false);
    }
}

void UiView::gridChange() {
    QAction *action = (QAction*)sender();
    bool ok = true;
    if(action == ui->action10Seconds)
        actionRouteGridChange(10);
    else if(action == ui->action1second)
        actionRouteGridChange(1);
    else if(action == ui->action500Milliseconds)
        actionRouteGridChange(0.5);
    else if(action == ui->action100Milliseconds)
        actionRouteGridChange(0.1);
    else if(action == ui->action10Milliseconds)
        actionRouteGridChange(0.01);
    else if(action == ui->actionCustomValue) {
        qreal val = QInputDialog::getDouble(0, tr("Custom grid value"), tr("Enter the desired grid time value in seconds:"), 0.500, 0.00001, 9999999, 3, &ok);
        if(ok) {
            ui->actionCustomValue->setText(tr("Custom value:") + QString(" %1 ").arg(val) + tr("sec"));
            actionRouteGridChange(val);
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
void UiView::gridOpacityChange() {
    QAction *action = (QAction*)sender();
    bool ok = true;
    if(action == ui->actionOpaque)
        actionRouteGridOpacityChange(2);
    else if(action == ui->action75_opaque)
        actionRouteGridOpacityChange(1.5);
    else if(action == ui->action50_opaque)
        actionRouteGridOpacityChange(1);
    else if(action == ui->action25_opaque)
        actionRouteGridOpacityChange(0.5);
    else if(action == ui->action10_opaque)
        actionRouteGridOpacityChange(0.3);
    if(ok) {
        ui->actionOpaque->setChecked(false);
        ui->action75_opaque->setChecked(false);
        ui->action50_opaque->setChecked(false);
        ui->action25_opaque->setChecked(false);
        ui->action10_opaque->setChecked(false);
        action->setChecked(true);
    }
}

void UiView::setAutosize(bool val) {
    ui->actionToggle_Autosize->setChecked(val);
}

void UiView::actionResize() {
    QSize currentSize = ui->render->size();
    QStringList newSizes = QInputDialog::getText(0, tr("Resize viewport"), tr("New viewport size"), QLineEdit::Normal, tr("%1 x %2").arg(currentSize.width()).arg(currentSize.height())).split("x", QString::SkipEmptyParts);
    if(newSizes.count() == 2) {
        QSize newSize(newSizes.at(0).toUInt(), newSizes.at(1).toUInt());
        if((newSize.width() > 0) && (newSize.height() > 0))
            resize(size() + newSize - ui->render->size());
    }
}
