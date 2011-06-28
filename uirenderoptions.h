#ifndef RENDEROPTIONS_H
#define RENDEROPTIONS_H

#include <QObject>
#include <QRect>
#include <QPointF>
#include <QColor>
#include <QMap>
#include <QtOpenGL>

typedef struct _Texture {
public:
    GLuint texture;
    QRectF mapping;
} Texture;
Q_DECLARE_TYPEINFO(Texture, Q_PRIMITIVE_TYPE);


class UiRenderOptions : public QObject {
    Q_OBJECT
public:
    explicit UiRenderOptions(QObject *parent):QObject(parent) { }

public:
    QRectF axisArea;
    QRect axisAreaSearch;
    qreal zoomValue, zoomLinear, axisGrid;
    QPointF axisCenter;
    QGLWidget *render;
    QFont renderFont;

public:
    QMap<QString, Texture> textures;
    QMap<QString, QColor> colors;

public:
    bool paintBackground, paintAxisGrid, paintAxisMain;
    bool paintTriggers, paintCursors, paintCurves;
    bool paintThisGroup;
    bool paintLabel;
    qreal paintZStart, paintZEnd;

public:
    /*
    inline qreal transformX(qreal x) {
        return x*x*((x>0)?(1):(-1));
    }
    inline qreal transformY(qreal y) {
        return y;
    }
    inline QPointF transform(const QPointF & pt) {
        return QPointF(transformX(pt.x()), transformY(pt.y()));
    }
    */

public:
    qreal objectSize;
public:
    QRectF selectionArea;

signals:

public slots:

};

#endif // RENDEROPTIONS_H
