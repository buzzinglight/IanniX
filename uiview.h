#ifndef UIVIEW_H
#define UIVIEW_H

#include <QMainWindow>
#include "uitransport.h"
#include "uiinspector.h"

namespace Ui {
    class UiView;
}

class UiView : public QMainWindow {
    Q_OBJECT

public:
    explicit UiView(QWidget *parent = 0);
    ~UiView();

private:
    bool wasInspectorVisible, wasTransportVisible;

public:
    UiRender* getRender() const;
    UiTransport* getTransport() const;
    UiInspector* getInspector() const;
public slots:
    void actionFullscreen();
    void escFullscreen();
    void actionGrid();
    void actionToggle_Inspector() { emit(actionRouteToggle_Inspector()); }
    void actionToggle_Transport() { emit(actionRouteToggle_Transport()); }
    void actionToggle_Autosize()  { emit(actionRouteToggle_Autosize()); }
    void actionPlay_pause()       { emit(actionRoutePlay_pause()); }
    void actionFast_rewind()      { emit(actionRouteFast_rewind()); }
    void actionZoom_in();
    void actionZoom_out();
    void actionZoom_initial();
    void actionDrawFreeCurve()    { emit(actionRouteDrawFreeCurve()); }
    void actionDrawPointCurve()   { emit(actionRouteDrawPointCurve()); }
    void actionDrawTriggers()     { emit(actionRouteDrawTriggers()); }
    void actionAddFreeCursor()    { emit(actionRouteAddFreeCursor()); }
    void actionCircleCurve()      { emit(actionRouteCircleCurve()); }
    void actionSnapGrid()         { emit(actionRouteSnapGrid()); }
    void actionLockPos();
    void actionToggleLabel();
    void actionAbout()            { emit(actionRouteAbout()); }

    void unToogleDraw(quint16 id);
    void gridChange();
    void gridOpacityChange();
    void help() {
        QDesktopServices::openUrl(QUrl("file:///" + QFileInfo("Documentation/index.html").absoluteFilePath().replace("\\", "/"), QUrl::TolerantMode));
    }
    void actionPatchesFolder() {
        QDesktopServices::openUrl(QUrl("file:///" + QFileInfo("Patches/").absoluteFilePath().replace("\\", "/"), QUrl::TolerantMode));
    }
    void actionQuit()  {
        close();
    }

signals:
    void actionRouteToggle_Inspector();
    void actionRouteToggle_Transport();
    void actionRouteToggle_Autosize();
    void actionRoutePlay_pause();
    void actionRouteFast_rewind();
    void actionRouteGrid();
    void actionRouteDrawFreeCurve();
    void actionRouteDrawPointCurve();
    void actionRouteDrawTriggers();
    void actionRouteAddFreeCursor();
    void actionRouteCircleCurve();
    void actionRouteGridChange(qreal);
    void actionRouteGridOpacityChange(qreal);
    void actionRouteSnapGrid();
    void actionRouteAbout();
    void actionRouteQuit();
    void actionRouteCloseEvent(QCloseEvent*);

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *);

private:
    Ui::UiView *ui;
};

#endif // UIVIEW_H
