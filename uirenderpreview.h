#ifndef UIRENDERPREVIEW_H
#define UIRENDERPREVIEW_H

#include <QGLWidget>

class NxEventsPropagation {
public:
    virtual void wheelEvent(QWheelEvent *)             {}
    virtual void mousePressEvent(QMouseEvent *)        {}
    virtual void mouseReleaseEvent(QMouseEvent *)      {}
    virtual void mouseMoveEvent(QMouseEvent *)         {}
    virtual void mouseDoubleClickEvent(QMouseEvent *)  {}
    virtual void keyPressEvent(QKeyEvent *)            {}
};

class UiRenderPreview : public QGLWidget {
    Q_OBJECT

private:
    GLuint renderPreviewTexture;
    NxEventsPropagation *render;
    QSizeF renderSize;

public:
    explicit UiRenderPreview(QWidget *parent = 0);
    explicit UiRenderPreview(QWidget *parent, QGLWidget *shared);
    void paintPreview(NxEventsPropagation *_render, GLuint _renderPreviewTexture, QSizeF _renderSize);

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

signals:
    
public slots:
    
};

#endif // UIRENDERPREVIEW_H
