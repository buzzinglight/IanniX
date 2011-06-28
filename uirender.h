#ifndef RENDER_H
#define RENDER_H

#include <QObject>
#include <QColor>
#include <QFile>
#include <QTime>
#include <QWheelEvent>
#include <math.h>
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
    QPointF rotation, translation;
    QPointF rotationDrag, translationDrag;
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


signals:
    void setPerfOpenGL(const QString & val);
    void editingStart(const QPointF &);
    void editingStop();
    void editingMove(const QPointF &);
    void escFullscreen();

private:
    QTimer *timer;
protected:
    void initializeGL();
    inline void resizeGL() { resizeGL(width(), height()); }
    void resizeGL(int width, int height);
    void paintGL();
private slots:
    void timerEvent();
public:
    inline void refresh() { resizeGL(); updateGL(); }
    inline void simpleRefresh() { updateGL(); }
    void loadTexture(const QString & name, const QString & filename, const QRectF & mapping);
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
    void centerOn(const QPointF & center);

private:
    QPointF mousePressedRawPos, mousePressedAreaPos, mousePressedAreaPosNoCenter, mousePressedAxisCenter;
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
    void mousePosChanged(const QPointF &);
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
    void actionCopy();
    void actionPaste();
    void actionDuplicate();
    void actionCut();
    void actionSelect_all();
    void actionDelete();

    void actionSnapGrid();

signals:
    void actionRouteNew();
    void actionRouteOpen();
    void actionRouteSave();
    void actionRouteSave_as();
    void actionRouteSave_all();
    void actionRouteDuplicateScore();
    void actionRouteRename();
    void actionRouteRemove();
    void actionRouteQuit();
    void actionRouteUndo();
    void actionRouteRedo();
    void selectionChanged();

};

#endif //RENDER_H
