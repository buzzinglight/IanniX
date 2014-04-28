/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

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

#ifndef UIVIEW_H
#define UIVIEW_H

#include <QMainWindow>
#include "uiinspector.h"
#include "transport/uiabout.h"
#include "gui/uihelp.h"

namespace Ui {
    class UiView;
}

class UiView : public QMainWindow {
    Q_OBJECT

public:
    explicit UiView(QWidget *parent = 0);
    ~UiView();

public:
    UiHelp *help;
private:
    UiAbout *about;
    bool wasInspectorVisible, wasTransportVisible, isFullScreen;
    QPoint previousPos;
    QSize previousSize;
    QDesktopWidget *fullscreenDisplays;
    QList<QPushButton*> fullscreenButtons;

public:
    UiRender*        getRender() const;
    Transport*       getTransport() const;
    UiInspector*     getInspector() const;
    UiRenderPreview* getRenderPreview() const;
    bool getPerformancePreview() const;
public slots:
    void fullscreenDisplaysCountChanged();
    void fullscreenDisplaysSelected();
    void showTimer();
    void showHelp();
    void showTransport();
    void showInspector();
    void showEditor();

    void toggleFullscreen(bool);
    void goToFullscreen();
    void goToFullscreen(quint8 screenIndex);
    void escFullscreen();
    void actionPlay_pause();
    void actionFast_rewind();
    void actionPerformance();
    void actionReloadScript()     { emit(actionRouteReloadScript()); }
    void actionImportSVG();
    void actionImportBackground();
    void actionImportText();

    void actionAlign_top()        { emit(arrangeObjects(0)); }
    void actionAlign_left()       { emit(arrangeObjects(1)); }
    void actionAlign_bottom()     { emit(arrangeObjects(2)); }
    void actionAlign_right()      { emit(arrangeObjects(3)); }
    void actionAlign_middle()     { emit(arrangeObjects(4)); }
    void actionAlign_center()     { emit(arrangeObjects(5)); }
    void actionDistributeH()      { emit(arrangeObjects(6)); }
    void actionDistributeV()      { emit(arrangeObjects(7)); }
    void actionAlign_circle()     { emit(arrangeObjects(8)); }
    void actionAlign_ellipse()    { emit(arrangeObjects(9)); }

    void actionSnapshot();
    void actionResize();
    void actionResize(QSize size);
    void gridChange();
    void actionPatchesFolder() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/").absoluteFilePath()));
    }


private:
    quint16 freehandCurveId;
    qint16 freehandCurveIndex;
    bool freehandCurveNeedsCursor;
    NxPoint editingStartPoint;
public slots:
    void unToogleDraw(quint16 id = 0);
    void actionDrawFreeCurveSimple()  { actionDrawFreeCurve (false); }
    void actionDrawPointCurveSimple() { actionDrawPointCurve(false); }
    void actionDrawFreeCurve(bool cursor = true);
    void actionDrawPointCurve(bool cursor = true);
    void actionDrawTriggers();
    void actionAddTimeline();
    void actionAddFreeCursor();
    void actionCircleCurve();
    void actionAddMathCurve();
    void actionAddMathCurveSimple();
    void editingStart(const NxPoint &);
    void editingStop();
    void editingStopWithoutRemoval(bool isLoop = false);
    void editingMove(const NxPoint &, bool add, bool mouseState);


signals:
    void forceGoto(qreal,bool);
    void arrangeObjects(quint16 type);

    void actionRouteReloadScript();
    void actionRouteImportSVG(QString);
    void actionRouteImportBackground(QString);
    void actionRouteImportText(QString,QString);
    void actionRouteCloseEvent(QCloseEvent*);

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *);

private:
    Ui::UiView *ui;
};

#endif // UIVIEW_H
