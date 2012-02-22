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
    connect(ui->actionImoprt_Text, SIGNAL(triggered()), SLOT(actionImportText()));

    connect(ui->actionRedo, SIGNAL(triggered()), ui->render, SLOT(actionRedo()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->render, SLOT(actionUndo()));
    connect(ui->actionCopy, SIGNAL(triggered()), ui->render, SLOT(actionCopy()));
    connect(ui->actionPaste, SIGNAL(triggered()), ui->render, SLOT(actionPaste()));
    connect(ui->actionDuplicate, SIGNAL(triggered()), ui->render, SLOT(actionDuplicate()));
    connect(ui->actionCut, SIGNAL(triggered()), ui->render, SLOT(actionCut()));
    connect(ui->actionSelect_all, SIGNAL(triggered()), ui->render, SLOT(actionSelect_all()));
    connect(ui->actionDelete, SIGNAL(triggered()), ui->render, SLOT(actionDelete()));
    connect(ui->actionSync, SIGNAL(triggered()), ui->render, SLOT(actionSync()));

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
    connect(ui->actionSnapGrid, SIGNAL(triggered()), SLOT(actionSnapGrid()));
    connect(ui->actionShowEditor, SIGNAL(triggered()), SLOT(actionShowEditor()));
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

void UiView::actionFullscreen() {
    if(isFullScreen()) {
        setWindowState(windowState() & ~Qt::WindowFullScreen);
        ui->render->setCursor(Qt::ArrowCursor);
        ui->toolBar->setVisible(true);
        ui->inspector->parentWidget()->setVisible(wasInspectorVisible);
        ui->transport->parentWidget()->setVisible(wasTransportVisible);
        ui->menubar->setVisible(true);
    }
    else {
        setWindowState(windowState() | Qt::WindowFullScreen);
        ui->render->setCursor(Qt::BlankCursor);
        ui->toolBar->setVisible(false);
        wasInspectorVisible = ui->inspecteurDock->isVisible();
        wasTransportVisible = ui->transportDock->isVisible();
        ui->menubar->setVisible(false);
        ui->inspector->parentWidget()->hide();
        ui->transport->parentWidget()->hide();
    }
    ui->render->selectionClear(true);
}
void UiView::escFullscreen() {
    if(isFullScreen())
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
void UiView::actionImportSVG() {
    QString fileName = QFileDialog::getOpenFileName(0, tr("Select a SVG file…"), QDir::currentPath(), tr("SVG Files (*.svg)"));
    if(fileName != "")
        emit(actionRouteImportSVG(fileName));
}
void UiView::actionImportImage() {
    QString fileName = QFileDialog::getOpenFileName(0, tr("Select an image…"), QDir::currentPath(), tr("Images (*.png *.jpg *.jpeg)"));
    if(fileName != "")
        emit(actionRouteImportImage(fileName));
}
void UiView::actionImportText() {
    QString font = "";
    QString text = QInputDialog::getText(0, tr("Type a glyph or text…"), tr("Type a glyphe or a text to import in IanniX"), QLineEdit::Normal, tr(""));
    if(text != "")
        emit(actionRouteImportText(font, text));
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
            ui->actionCustomValue->setText(tr("Custom value : %1 sec").arg(val));
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
        actionRouteGridOpacityChange(0.5);
    else if(action == ui->action75_opaque)
        actionRouteGridOpacityChange(0.33);
    else if(action == ui->action50_opaque)
        actionRouteGridOpacityChange(0.25);
    else if(action == ui->action25_opaque)
        actionRouteGridOpacityChange(0.20);
    else if(action == ui->action10_opaque)
        actionRouteGridOpacityChange(0.15);
    if(ok) {
        ui->actionOpaque->setChecked(false);
        ui->action75_opaque->setChecked(false);
        ui->action50_opaque->setChecked(false);
        ui->action25_opaque->setChecked(false);
        ui->action10_opaque->setChecked(false);
        action->setChecked(true);
    }
}
