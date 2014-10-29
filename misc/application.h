/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QImage>
#include <QGLWidget>
#include <QVariant>
#include <QMainWindow>
#include <QPixmap>
#include "applicationexecute.h"
#include "gui/uihelp.h"
#include "render/uirenderpreview.h"
#ifdef KINECT_INSTALLED
#include "interfaces/extkinectmanager.h"
#endif
#include "items/uitextureitem.h"
#include "items/uicoloritem.h"
#include "items/uifileitem.h"
#include "items/uipathpointsitem.h"
#include "misc/options.h"


class ApplicationCurrent : public QObject, public ApplicationExecute {
    Q_OBJECT

public:
    bool hasStarted;
    explicit ApplicationCurrent(QObject *parent) : QObject(parent) {
        hasStarted = false;
    }

//KINECT
#ifdef KINECT_INSTALLED
public:
    ExtKinectManager *kinect;
#endif

public:
    virtual void setObjectActivity(void *_object, quint8 activeOld) = 0;
    virtual void setObjectGroupId(void *_object, const QString & groupIdOld) = 0;
    virtual void setObjectId(void *_object, quint16 idOld) = 0;
    bool isGroupSoloActive, isObjectSoloActive;
public slots:
    virtual void openMessageEditor() = 0;
    virtual void pushSnapshot() = 0;
    virtual quint16 getCount(qint8 objectType = -1) = 0;
    virtual const QString serialize() const = 0;
    virtual void readyToStart() = 0;
    virtual QMainWindow* getMainWindow() = 0;
    virtual UiRenderPreview* getRenderPreview() = 0;
    virtual bool getPerformancePreview() = 0;
    virtual void timerTrig(void *object, bool force = false) = 0;
    virtual QString waitForMessage() = 0;
    virtual void* getObjectById(quint16 id) = 0;
    virtual void executeAsScript(const QString &script) = 0;
};



enum EditingMode { EditingModeFree, EditingModePoint, EditingModeTriggers, EditingModeCircle };

class Render : public QGLWidget {
public:
    explicit Render(QWidget *parent = 0, QGLWidget *share = 0) : QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DirectRendering), parent, share) {}
public:
    virtual void selectionClear(bool) = 0;
    virtual void setZoom(qreal axisZoom) = 0;
    virtual void centerOn(const NxPoint & center, bool force = false) = 0;
    virtual void rotateTo(const NxPoint & rotation, bool force = false) = 0;
    virtual bool loadTexture(UiRenderTexture*, bool = false) = 0;

public:
    static qreal objectSize;
    static NxRect selectionArea;
    static UiTextureItems* textures;
    static UiColorItems*   colors;
    static QMap<QString, QColor> defaultColors;
    static UiFileItem      files;
    static UiBool paintThisGroup;
    static UiBool forceLists, forceTexture, forceFrustumInInit;
    static NxRect axisArea;
    static qreal zoomValue, zoomLinear, zoomLinearDest;
    static UiReal axisGrid;
    static NxPoint axisCenter, axisCenterDest;
    static NxPoint rotation, rotationDest;
    static EditingMode editingMode;
    static bool editing, editingFirstPoint;
};



class Application : public QObject {
    Q_OBJECT

public:
    static QFileInfo pathApplication, pathDocuments, pathCurrent;
    static Render *render;
    static ApplicationCurrent *current;
    static void* synchroLoopGuard;
    static QWidget *splash;
    static UiString defaultMessageTrigger, defaultMessageCursor, defaultMessageCurve, defaultMessageTransport, defaultMessageSync, defaultMessage;
    static QFont renderFont;
    static UiBool allowSelection, allowSelectionCursors, allowSelectionCurves, allowSelectionTriggers, colorTheme, allowLockPos, allowPlaySelected;
    static UiBool paintAxisGrid, paintCurvesOpacity, paintLabel;
    static UiReal objectsAutosize;
    static UiBool mouseSnapX, mouseSnapY, mouseSnapZ;
    static UiReal followId;
    static const QString colorsPrefix(qint16 i = -1) {
        if(i < 0) {
            if(colorTheme)   return "lighttheme";
            else             return "darktheme";
        }
        else if(i == 0)      return "darktheme";
        else                 return "lighttheme";

        return "";
    }

public:
    static void setInterfaces(ApplicationCurrent *_current = 0, Render *_render = 0);
    static QImage takeScreenshot();
};

#endif // APPLICATION_H
