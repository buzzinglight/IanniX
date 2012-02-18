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

#ifndef RENDER_H
#define RENDER_H

#include <QObject>
#include <QColor>
#include <QFile>
#include <QTime>
#include <QWheelEvent>
#include <QtCore/qmath.h>
#include <QClipboard>
#include "nxdocument.h"
#include "nxobjectfactoryinterface.h"
#include "uirenderoptions.h"

enum EditingMode { EditingModeFree, EditingModePoint, EditingModeTriggers, EditingModeCircle };

namespace Ui {
    class UiRender;
}

class UiRender : public QGLWidget {
    Q_OBJECT
public:
    explicit UiRender(QWidget *parent = 0);
    ~UiRender();

private:
    NxObjectFactoryInterface *factory;
    NxDocument *document;
    QTime renderMeasure;
    qreal timePerfRefresh, timePerfCounter;
    bool triggerAutosize, editing, editingFirstPoint;
    EditingMode editingMode;
    QList<NxObject*> selectionRect;
    NxObject *selectedHover;
    QList<NxObject*> selection;
    NxPoint rotation, translation;
    NxPoint rotationDrag, translationDrag;
    qreal scale;
public:
    inline QList<NxObject*> *getSelection() {
        return &selection;
    }
    inline NxObject* getSelectedHover() const {
        return selectedHover;
    }
    inline void setEditingMode(EditingMode _editingMode) {
        editingMode = _editingMode;
        editing = true;
        editingFirstPoint = true;
        if(editing)
            setCursor(Qt::CrossCursor);
    }
    inline EditingMode getEditingMode() const {
        return editingMode;
    }
    inline bool getEditing() const {
        return editing;
    }
    inline void unsetEditing() {
        editing = false;
    }


    void setDocument(NxDocument *_document);
    inline void setFactory(NxObjectFactoryInterface *_factory) {
        factory = _factory;
    }
    inline void setTriggerAutosize(bool _triggerAutosize) {
        triggerAutosize = _triggerAutosize;
        zoom();
    }
    inline bool getTriggerAutosize() const {
        return triggerAutosize;
    }

    inline void setRotation(NxPoint _rotation) {  ///CG///
        rotation = _rotation;
    }

signals:
    void setPerfOpenGL(const QString & val);
    void editingStart(const NxPoint &);
    void editingStop();
    void editingMove(const NxPoint &, bool add);
    void escFullscreen();

private:
    QTimer *timer;
protected:
    void initializeGL();
    inline void resizeGL() { resizeGL(width(), height()); }
    void resizeGL(int width, int height);
    void paintGL();
private slots:
    void timerTick();
public:
    inline void refresh() { resizeGL(); updateGL(); }
    inline void simpleRefresh() { updateGL(); }
    void loadTexture(const QString & name, const QString & filename, const NxRect & mapping);
    inline void setInterval(quint16 ms) {
        timer->setInterval(ms);
    }

private:
    UiRenderOptions *renderOptions;
private:
    void paintBackground();
    void paintAxisGrid();
    void paintSelection();
public:
    inline UiRenderOptions* getRenderOptions() {
        return renderOptions;
    }
    void centerOn(const NxPoint & center);
    void rotateTo(const NxPoint & rotation);

private:
    NxPoint mousePressedRawPos, mousePressedAreaPos, mousePressedAreaPosNoCenter, mousePressedAxisCenter;
    bool mousePressed, mouseCommand, mouseShift, mouseObjectDrag, mouseSnap;
    bool canObjectDrag;
    qreal pinchValue;
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool event(QEvent *event);
public:
    void zoom();
    void zoom(qreal axisZoom);
    void zoomIn();
    void zoomOut();
    void zoomInitial();
    void keyPressEvent(QKeyEvent *event);
    void selectionAdd(NxObject *object);
    void selectionClear(bool hoverAussi = false);
    inline void setCanObjectDrag(bool _canObjectDrag) {
        canObjectDrag = _canObjectDrag;
    }
    inline bool isCanObjectDrag() {
        return canObjectDrag;
    }

signals:
    void objectSelected(QList<NxObject*>);
    void mousePosChanged(const NxPoint &);
    void mouseZoomChanged(qreal);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UiRender *ui;

signals:

public slots:
    void actionNew()        { emit(actionRouteNew()); }
    void actionOpen()       { emit(actionRouteOpen()); }
    void actionSave()       { emit(actionRouteSave()); }
    void actionSave_as()    { emit(actionRouteSave_as()); }
    void actionSave_all()   { emit(actionRouteSave_all()); }
    void actionDuplicateScore() { emit(actionRouteDuplicateScore()); }
    void actionRename()     { emit(actionRouteRename()); }
    void actionRemove()     { emit(actionRouteRemove()); }
    void actionUndo()       { emit(actionRouteUndo()); }
    void actionRedo()       { emit(actionRouteRedo()); }
    void actionSync()       { emit(actionRouteSync()); }
    void actionCopy();
    void actionPaste();
    void actionDuplicate();
    void actionCut();
    void actionSelect_all();
    void actionDelete();

    void actionSnapGrid();

signals:
    void actionRouteNew();
    void actionRouteNew_script();
    void actionRouteOpen();
    void actionRouteSave();
    void actionRouteSave_as();
    void actionRouteSave_all();
    void actionRouteDuplicateScore();
    void actionRouteRename();
    void actionRouteRemove();
    void actionRouteQuit();
    void actionRouteSync();

    void actionRouteUndo();
    void actionRouteRedo();
    void selectionChanged();

};

#endif //RENDER_H
