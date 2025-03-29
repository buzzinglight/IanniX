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

#ifndef RENDER_H
#define RENDER_H

#include <QObject>
#include <QColor>
#include <QFile>
#include <QMimeData>
#include <QTime>
#include <QWheelEvent>
#include <QGesture>
#include <QtCore/qmath.h>
#include <QDir>
#include <QClipboard>
#include "interfaces/interfacesyphon.h"
#include "objects/nxdocument.h"
#include "misc/application.h"
#include "abstractionsgl.h"

#include "render/uirenderpreview.h"
#ifdef FFMPEG_INSTALLED
#include "interfaces/qffmpeg/QVideoEncoder.h"
#endif

namespace Ui {
    class UiRender;
}

class UiRenderSelection : public QList<NxObject*>, public NxObjectDispatchProperty {
public:
    inline void dispatchProperty(const char *_property, const QVariant & value) {
        for(quint16 i = 0 ; i < count() ; i++)
            (*this)[i]->dispatchProperty(_property, value);
    }
    inline const QVariant getProperty(const char *_property) const {
        for(quint16 i = 0 ; i < count() ; i++)
            (*this)[i]->getProperty(_property);
        return QVariant();
    }
    inline quint8 getType() const {
        return ObjectsTypeSelection;
    }
    inline const QString getTypeStr() const {
        return "selection";
    }
};

class UiRender : public Render, public NxEventsPropagation {
    Q_OBJECT

public:
    explicit UiRender(QWidget *parent = 0, void *share = 0);
    ~UiRender();

public:
    QString defaultStatusTip, cursorStatusTip, curveStatusTip, triggerStatusTip;
private:
    NxDocument *documentToRender;
    QTime renderMeasure;
    UiRenderSelection selectionRect;
    NxObject *selectedHover;
    UiRenderSelection selection;
    NxPoint translation, translationDest, rotationDrag, translationDrag;
    qreal scale, scaleDest;
    QList<QImage> capturedFrames;
    bool capturedFramesStart;
public:
    QString legend;
    QColor legendColor;
    qreal legendSize;

public:
    inline void startRenderTimer() { timer->start(16); }


    inline UiRenderSelection *getSelection() {
        return &selection;
    }
    inline NxObject* getSelectedHover() const {
        return selectedHover;
    }
    inline bool isSelection() const {
        return (selection.count() > 0);
    }

    inline qreal getAutoScale(qreal factor) {
        return 0.15 * ((1. - factor) + (Render::zoomLinear/1.3) * factor);
    }


    inline void setEditingMode(EditingMode _editingMode) {
        Render::editingMode = _editingMode;
        Render::editing = true;
        Render::editingFirstPoint = true;
        if(Render::editing)
            setCursor(Qt::CrossCursor);
    }
    inline void unsetEditing() {
        Render::editing = false;
        setStatusTip(defaultStatusTip);
    }

    void setDocument(NxDocument *_documentToRender) { documentToRender = _documentToRender; }

signals:
    void escFullscreen();
    void editingStart(const NxPoint &);
    void editingStop();
    void editingMove(const NxPoint &, bool add, bool mouseState);

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
    bool loadTexture(UiRenderTexture *texture, bool gl = false);
    bool removeTexture(const QString &name);
    inline void setInterval(quint16 ms) {
        timer->setInterval(ms);
    }

private:
    bool isRemoving;
private:
    void paintBackground();
    void paintAxisGrid();
    void paintSelection();
public:
    void flagIsRemoving(bool _val = true) { isRemoving = _val; }
    void centerOn(const NxPoint & center, bool force = false);
    void rotateTo(const NxPoint & rotation, const NxPoint &rotationCenter = NxPoint(0, 0), bool force = false);

private:
    NxPoint mousePressedRawPos, mousePressedAreaPos, mousePressedAreaPosNoCenter, mousePressedAxisCenter;
    bool mousePressed, mouseControl, mouseShift, mouseObjectDrag;
    qreal pinchValue;
    bool snapBeforeKeyX, snapBeforeKeyY;
public:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void changeStatus(const QString &_status);
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool event(QEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public:
    void setZoom(qreal axisZoom);
    void selectionAdd(NxObject *object);
    void selectionClear(bool hoverAlso = false);
public slots:
    void setZoom();
    void zoomIn();
    void zoomOut();
    void zoomInitial();

signals:
    void objectSelected(UiRenderSelection);
    void mousePosChanged(const NxPoint &);
    void mouseZoomChanged(qreal);
    void mouseRotationChanged(const NxPoint &);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UiRender *ui;

signals:

public slots:
    void cameraPerspectiveChanged() { scaleDest = (cameraPerspective)?(3):(1); }
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
    void actionImportSVG(QString val)                   { emit(actionRouteImportSVG(val)); }
    void actionImportBackground(QString val)            { emit(actionRouteImportBackground(val)); }
    void actionImportText(QString val, QString val2)    { emit(actionRouteImportText(val, val2)); }
    void actionPaste()                                  { emit(actionRoutePaste()); }
    void actionCopy()                                   { emit(actionRouteCopy()); }
    void actionDuplicate();
    void actionCut();
    void actionSelect_all();
    void actionDelete();
    void arrangeObjects(quint16 type);
    void arrangeObjects(NxObject *objet, const NxPoint &pt);
    void capture(qreal scaleFactor);
    bool captureFrame(qreal scaleFactor, const QString &filename = "");

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
    void actionRouteImportSVG(QString);
    void actionRouteImportBackground(QString);
    void actionRouteImportText(QString,QString);
    void actionRouteCopy();
    void actionRoutePaste();

    void actionRouteUndo();
    void actionRouteRedo();
    void selectionChanged();

public:
#ifdef FFMPEG_INSTALLED
    QVideoEncoder videoEncoder;
#endif
#ifdef USE_OPENGLWIDGET
    inline void qglColor(const QColor &color) {
        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    }
    inline void qglClearColor(const QColor &color) {
        glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    }
    quint16 renderTextTextureIndex;
    OpenGlFont renderTextFont;
    void renderText(qreal x, qreal y, qreal z, const QString &text, const QFont &font, bool billboarded);
#else
    // Add renderText method with 6 parameters for consistency
    void renderText(qreal x, qreal y, qreal z, const QString &text, const QFont &font, bool billboarded);
#endif

public slots:
    void updateGL() {
        update();
    }

public:
    InterfaceSyphon *interfaceSyphon;
public:
    void setPerformanceMode(bool _performanceMode);
    void toggleBorderlessMode();
    bool isBorderlessMode() const { return borderlessMode; }
private:
    bool renderPreviewTextureInit, performanceMode, borderlessMode;
    GLuint renderPreviewTexture;
private:
    GLuint destinationTexture, workingTexture;
public:
    void adjustOpacity(bool increase);  // Adjust window opacity by 0.1 increments
};

#endif //RENDER_H
