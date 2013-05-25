#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QImage>
#include <QGLWidget>
#include <QVariant>
#include <QMainWindow>
#include <QPixmap>
#include "gui/uihelp.h"
#include "render/uirenderpreview.h"
#ifdef KINECT_INSTALLED
#include "interfaces/extkinectmanager.h"
#endif
#include "iannix_spec.h"

class ApplicationCurrent : public QObject {
    Q_OBJECT

public:
    explicit ApplicationCurrent(QObject *parent) : QObject(parent) {
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
    virtual const QVariant execute(const QString & command, ExecuteSource source, bool createNewObjectIfExists = false, bool needOutput = false) = 0;
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

class Render : public QGLWidget {
public:
    explicit Render(QWidget *parent) : QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DirectRendering), parent) {}
public:
    virtual void selectionClear(bool) = 0;
    virtual void setZoom(qreal axisZoom) = 0;
    virtual void centerOn(const NxPoint & center, bool force = false) = 0;
    virtual void rotateTo(const NxPoint & rotation, bool force = false) = 0;
    virtual bool loadTexture(UiRenderTexture*, bool = false) = 0;
};


class Application : public QObject {
    Q_OBJECT

public:
    static Render *render;
    static ApplicationCurrent *current;
    static void* synchroLoopGuard;

public:
    static void setInterfaces(ApplicationCurrent *_current = 0, Render *_render = 0);
    static QImage takeScreenshot();
    
signals:
    
public slots:
    
};

#endif // APPLICATION_H
