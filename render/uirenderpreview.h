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

#ifndef UIRENDERPREVIEW_H
#define UIRENDERPREVIEW_H

#ifdef USE_GLWIDGET
#include <QGLWidget>
#include <QGLFormat>
#else
#include <QOpenGLWidget>
#include <QGLWidget>
#include <QOpenGLFunctions>
#endif

class NxEventsPropagation {
public:
    virtual void wheelEvent(QWheelEvent *)             {}
    virtual void mousePressEvent(QMouseEvent *)        {}
    virtual void mouseReleaseEvent(QMouseEvent *)      {}
    virtual void mouseMoveEvent(QMouseEvent *)         {}
    virtual void mouseDoubleClickEvent(QMouseEvent *)  {}
    virtual void keyPressEvent(QKeyEvent *)            {}
};

#ifdef QT4
class UiRenderPreview : public QGLWidget {
#else
class UiRenderPreview : public QOpenGLWidget {
#endif
    Q_OBJECT

public:
    explicit UiRenderPreview(QWidget *parent, void *shared = 0);
    void paintPreview(NxEventsPropagation *_render, GLuint _renderPreviewTexture, QSizeF _renderSize);

private:
    GLuint renderPreviewTexture;
    NxEventsPropagation *render;
    QSizeF renderSize;

protected:
    void wheelEvent(QWheelEvent *event)             { if(render) render->wheelEvent(event); }
    void mousePressEvent(QMouseEvent *event)        { if(render) render->mousePressEvent(event); }
    void mouseReleaseEvent(QMouseEvent *event)      { if(render) render->mouseReleaseEvent(event); }
    void mouseMoveEvent(QMouseEvent *event)         { if(render) render->mouseMoveEvent(event); }
    void mouseDoubleClickEvent(QMouseEvent *event)  { if(render) render->mouseDoubleClickEvent(event); }
    void keyPressEvent(QKeyEvent *event)            { if(render) render->keyPressEvent(event); }
    
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

#ifdef QT5
public slots:
    void updateGL() {
        update();
    }
#endif

signals:
    
public slots:
    
};

#endif // UIRENDERPREVIEW_H
