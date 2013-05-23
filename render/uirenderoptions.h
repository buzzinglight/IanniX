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
#include "items/uitextureitem.h"
#include "items/uicoloritem.h"
#include "items/uifileitem.h"
#include "items/uipathpointsitem.h"
#include "misc/options.h"
#include "iannix_spec.h"

enum EditingMode { EditingModeFree, EditingModePoint, EditingModeTriggers, EditingModeCircle };

class Global {
public:
    static QFileInfo pathApplication, pathDocuments, pathCurrent;
    static qreal objectSize;
    static NxRect selectionArea;
    static UiTextureItems* textures;
    static UiColorItems*   colors;
    static QMap<QString, QColor> defaultColors;
    static UiFileItem      files;
    static UiBool paintAxisGrid, paintCurvesOpacity, paintThisGroup, paintLabel;
    static UiBool allowSelection, allowSelectionCursors, allowSelectionCurves, allowSelectionTriggers, triggerAutosize, colorTheme, allowLockPos, allowPlaySelected;
    static UiBool forceLists, forceTexture, forceFrustumInInit;
    static UiBool mouseSnapX, mouseSnapY, mouseSnapZ;
    static UiReal followId;
    static NxRect axisArea;
    static qreal zoomValue, zoomLinear, zoomLinearDest, axisGrid;
    static NxPoint axisCenter, axisCenterDest;
    static NxPoint rotation, rotationDest;
    static QFont renderFont;
    static EditingMode editingMode;
    static bool editing, editingFirstPoint;
    static UiString defaultMessageTrigger, defaultMessageCursor, defaultMessageCurve, defaultMessageTransport, defaultMessageSync, defaultMessage;
    static const QString colorsPrefix(qint16 i = -1) {
        if(i < 0) {
            if(colorTheme)   return "lighttheme";
            else             return "darktheme";
        }
        else if(i == 0)      return "darktheme";
        else                 return "lighttheme";

        return "";
    }
};

#endif // RENDEROPTIONS_H
