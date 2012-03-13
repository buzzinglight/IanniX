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

#ifndef RENDEROPTIONS_H
#define RENDEROPTIONS_H

#include <QObject>
#include <QRect>
#include <QColor>
#include <QMap>
#include <QtOpenGL>
#include "iannix_spec.h"

typedef struct _Texture {
public:
    GLuint texture;
    NxRect mapping;
} Texture;
Q_DECLARE_TYPEINFO(Texture, Q_PRIMITIVE_TYPE);


class UiRenderOptions : public QObject {
    Q_OBJECT
public:
    explicit UiRenderOptions(QObject *parent):QObject(parent) {
        zoomValue = 1;
        zoomLinear = 1;
        zoomLinearDest = 1;
        axisGrid = 1;
        timeFactor = 0;
        allowSelection = false;
        allowSelectionCursors = true;
        allowSelectionCurves = true;
        allowSelectionTriggers = true;
        paintZStart = 0;
        paintZEnd = 0;
        objectSize = 1;
    }

public:
    NxRect axisArea;
    QRect axisAreaSearch;
    qreal zoomValue, zoomLinear, zoomLinearDest, axisGrid;
    NxPoint axisCenter, axisCenterDest;
    QGLWidget *render;
    QFont renderFont;
    qreal timeFactor;
    bool allowSelection;
    bool allowSelectionCursors, allowSelectionCurves, allowSelectionTriggers;

public:
    QMap<QString, Texture> textures;
    QMap<QString, QColor> colors;

public:
    bool paintBackground, paintAxisGrid, paintAxisMain;
    bool paintTriggers, paintCursors, paintCurves, paintCurvesOpacity;
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
    inline NxPoint transform(const NxPoint & pt) {
        return NxPoint(transformX(pt.x()), transformY(pt.y()));
    }
    */

public:
    qreal objectSize;
public:
    NxRect selectionArea;

signals:

public slots:

};

#endif // RENDEROPTIONS_H
