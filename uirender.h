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
#include <QDir>
#include <QClipboard>
#include "nxdocument.h"
#include "nxobjectfactoryinterface.h"
#include "uirenderoptions.h"
#ifdef FFMPEG_INSTALLED
#include "qffmpeg/QVideoEncoder.h"
#endif
#ifdef SYPHON_INSTALLED
#include "uirendersyphon.h"
#endif

enum EditingMode { EditingModeFree, EditingModePoint, EditingModeTriggers, EditingModeCircle };

namespace Ui {
    class UiRender;
}

class UiRenderTexture {
public:
    UiRenderTexture() { }
    UiRenderTexture(const QString & _name, const QString & _filename, const NxRect & _mapping) {
        name     = _name;
        filename = _filename;
        mapping  = _mapping;
    }
    QString name, filename;
    NxRect mapping;
};

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
    bool editing, editingFirstPoint;
    EditingMode editingMode;
    QList<NxObject*> selectionRect;
    NxObject *selectedHover;
    QList<NxObject*> selection;
    NxPoint translation;
    NxPoint translationDest;
    NxPoint rotationDrag, translationDrag;
    qreal scale, scaleDest;
    bool colorTheme;
    qint16 followId;
    bool firstLaunch;
    QString defaultStatusTip;
    QList<UiRenderTexture> textures;
    bool texturesLoaded;
    QList<QImage> capturedFrames;
    bool capturedFramesStart;

public:
    inline void startRenderTimer() { timer->start(20); }
    inline void setFollowId(qint16 _followId) { followId = _followId; }
    inline qint16 getFollowId() const { return followId; }

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
#ifdef Q_OS_MAC
        setStatusTip(tr("Click on score to add points. Double-click or press ESC to end your curve. After, Double-click on a curve to add a point, Command+click to remove it, Double-click on a point to enable/disable smoothing. Shift+double-click to resample curve."));
#else
        setStatusTip(tr("Click on score to add points. Double-click or press ESC to end your curve. After, Double-click on a curve to add a point, Control+click to remove it, Double-click on a point to enable/disable smoothing. Shift+double-click to resample curve."));
#endif
    }
    inline EditingMode getEditingMode() const {
        return editingMode;
    }
    inline bool getEditing() const {
        return editing;
    }
    inline void unsetEditing() {
        editing = false;
        setStatusTip(defaultStatusTip);
    }

    bool getColorTheme() const { return colorTheme; }


    void setDocument(NxDocument *_document);
    inline void setFactory(NxObjectFactoryInterface *_factory) {
        factory = _factory;
    }
    inline void setTriggerAutosize(bool _triggerAutosize) {
        renderOptions->triggerAutosize = _triggerAutosize;
        zoom();
    }
    inline bool getTriggerAutosize() const {
        return renderOptions->triggerAutosize;
    }

signals:
    void setPerfOpenGL(const QString & val);
    void editingStart(const NxPoint &);
    void editingStop();
    void editingMove(const NxPoint &, bool add);
    void escFullscreen();

private:
    QTimer *timer;
    QSize renderSize;
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void setFrustum();
public:
    inline void resizeGL() { resizeGL(width(), height()); }
    void loadTexture(const UiRenderTexture &texture);
    void loadTexture(const QString & name, const QString & filename, const NxRect & mapping);
    inline void setInterval(quint16 ms) {
        timer->setInterval(ms);
    }

private:
    UiRenderOptions *renderOptions;
    bool isRemoving;
private:
    void paintBackground();
    void paintAxisGrid();
    void paintSelection();
public:
    inline UiRenderOptions* getRenderOptions() const {
        return renderOptions;
    }
    void flagIsRemoving() { isRemoving = true; }
    void centerOn(const NxPoint & center, bool force = false);
    void rotateTo(const NxPoint & rotation, bool force = false);

private:
    NxPoint mousePressedRawPos, mousePressedAreaPos, mousePressedAreaPosNoCenter, mousePressedAxisCenter;
    bool mousePressed, mouseCommand, mouseShift, mouseObjectDrag, mouseSnapX, mouseSnapY, mouseSnapZ;
    bool canObjectDrag;
    qreal pinchValue;
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool event(QEvent *event);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
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
    void setColorTheme(bool);
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
    void actionImportSVG(QString val)                   { emit(actionRouteImportSVG(val)); }
    void actionImportImage(QString val)                 { emit(actionRouteImportImage(val)); }
    void actionImportBackground(QString val)            { emit(actionRouteImportBackground(val)); }
    void actionImportText(QString val, QString val2)    { emit(actionRouteImportText(val, val2)); }
    void actionCopy();
    void actionCopyScript();
    void actionPaste();
    void actionDuplicate();
    void actionCut();
    void actionSelect_all();
    void actionDelete();
    void actionSnapXGrid();
    void actionSnapYGrid();
    void actionSnapZGrid();
    void actionFollowID(qint16);
    void actionArrange(quint16 type);
    void capture(qreal scaleFactor);
    void captureFrame(qreal scaleFactor, const QString &filename = "");

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
    void actionRouteImportSVG(QString);
    void actionRouteImportImage(QString);
    void actionRouteImportBackground(QString);
    void actionRouteImportText(QString,QString);

    void actionRouteUndo();
    void actionRouteRedo();
    void selectionChanged();

public:
#ifdef FFMPEG_INSTALLED
    QVideoEncoder videoEncoder;
#endif


#ifdef SYPHON_INSTALLED
private:
    bool renderSyphonTextureInit, renderSyphonInit;
    GLuint renderSyphonTexture;
    UiRenderSyphon renderSyphon;
#endif
public:
    bool allowSyphon;
public slots:
    void allowSyphonServer(bool val);


};

#endif //RENDER_H
