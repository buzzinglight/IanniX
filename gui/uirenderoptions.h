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
    qreal objectSize;
    NxRect selectionArea;
    QMap<QString, Texture> textures;
    QMap<QString, QColor> colors;
    bool paintBackground, paintAxisGrid, paintAxisMain, paintTriggers, paintCursors, paintCurves, paintCurvesOpacity, paintThisGroup, paintLabel;
    qreal paintZStart, paintZEnd;
    NxRect axisArea;
    qreal zoomValue, zoomLinear, zoomLinearDest, axisGrid;
    NxPoint axisCenter, axisCenterDest;
    NxPoint rotation, rotationDest;
    QGLWidget *render;
    QFont renderFont;
    qreal timeFactor;
    bool allowSelection, allowSelectionCursors, allowSelectionCurves, allowSelectionTriggers, triggerAutosize;
    bool forceLists, forceTexture, forceFrustumInInit;

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
        triggerAutosize = false;
        paintZStart = 0;
        paintZEnd = 0;
        objectSize = 1;
        forceLists = false;
        forceTexture = false;
        forceFrustumInInit = false;
    }
};

#endif // RENDEROPTIONS_H
