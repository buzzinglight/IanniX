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

#include "uirenderpreview.h"

#ifdef USE_GLWIDGET
UiRenderPreview::UiRenderPreview(QWidget *parent, void *shared) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DirectRendering), parent, (QGLWidget*)shared) {
#else
UiRenderPreview::UiRenderPreview(QWidget *parent, void *shared) :
    QOpenGLWidget(parent) {
    Q_UNUSED(shared);
    QSurfaceFormat sf;
    //sf.setProfile(QSurfaceFormat::CompatibilityProfile);
    //sf.setRenderableType(QSurfaceFormat::OpenGL);
    //sf.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    //sf.setOption(QSurfaceFormat::DeprecatedFunctions);
    sf.setSamples(4./devicePixelRatioFScale());
    setFormat(sf);
#endif
    setFocusPolicy(Qt::StrongFocus);
    render = 0;
}

void UiRenderPreview::initializeGL() {
    //OpenGL options
}

void UiRenderPreview::resizeGL(int width, int height) {
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void UiRenderPreview::paintPreview(NxEventsPropagation *_render, GLuint _renderPreviewTexture, QSizeF _renderSize) {
    makeCurrent();
    render               = _render;
    renderSize           = _renderSize;
    renderPreviewTexture = _renderPreviewTexture;
    updateGL();
}

void UiRenderPreview::paintGL() {
    // Skip if we have no valid texture or render
    if (renderPreviewTexture == 0 || !render) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        qDebug("UiRenderPreview::paintGL - No valid texture or render (texture: %u)", renderPreviewTexture);
        return;
    }

    // Clear the screen with black
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Calculate scale to maintain aspect ratio
    qreal scaleX = 1, scaleY = 1;
    qreal ratioRender  = (qreal)width()            / (qreal)height();
    qreal ratioTexture = (qreal)renderSize.width() / (qreal)renderSize.height();

    if(ratioRender >= ratioTexture) scaleX = ratioTexture / ratioRender;
    else                            scaleY = ratioRender  / ratioTexture;

    qDebug("UiRenderPreview::paintGL - Drawing texture %u with size %.0fx%.0f in viewport %dx%d", 
           renderPreviewTexture, renderSize.width(), renderSize.height(), width(), height());

    // Prepare the drawing
    glLoadIdentity();
    glTranslatef((1-scaleX)/2, (1-scaleY)/2, 0);
    
    // Draw texture using modern OpenGL 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, renderPreviewTexture);
    
    // Explicitly set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // Draw quad with texture
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set color to white for proper texture rendering
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);    glVertex3f(0,      0,      0);
    glTexCoord2f(1, 0);    glVertex3f(scaleX, 0,      0);
    glTexCoord2f(1, 1);    glVertex3f(scaleX, scaleY, 0);
    glTexCoord2f(0, 1);    glVertex3f(0,      scaleY, 0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}
