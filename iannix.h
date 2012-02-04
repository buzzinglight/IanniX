#ifndef IANNIX_H
#define IANNIX_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileSystemWatcher>
#include <QApplication>
#include <QFileOpenEvent>
#include <time.h>
#include "nxobjectfactoryinterface.h"
#include "extoscmanager.h"
#include "exttcpmanager.h"
#include "extudpmanager.h"
#include "exthttpmanager.h"
#include "extserialmanager.h"
#include "extscriptmanager.h"
#include "extmidimanager.h"
#include "uiabout.h"
#include "uisplash.h"
#include "uitransport.h"
#include "uiview.h"
#include "uiinspector.h"
#include "uieditor.h"

class IanniX : public NxObjectFactoryInterface, public NxObjectDispatchProperty {
    Q_OBJECT

private:
    QDir scriptDir;
public:
    explicit IanniX(QObject *parent, bool forceSettings);
    inline void dispatchProperty(const QString & property, const QVariant & value) {
        //Browse documents
        QHashIterator<QString, NxDocument*> documentIterator(documents);
        while (documentIterator.hasNext()) {
            documentIterator.next();
            NxDocument *document = documentIterator.value();
            document->dispatchProperty(property, value);
        }
    }
    inline const QVariant getProperty(const QString &) const {
        return 0;
    }
    inline quint8 getType() const {
        return ObjectsTypeScheduler;
    }
    inline const QString getTypeStr() const {
        return "scheduler";
    }


    //OBJECT MANAGEMENT
private:
    NxDocument *currentDocument;
    QList<ExtScriptManager*> activeScripts;
public:
    NxGroup* addGroup(const QString & documentId, const QString & groupId);
    void setObjectActivity(void *_object, quint8 activeOld);
    void setObjectLocal(void *_object, QRect localOld);
    void setObjectGroupId(void *_object, const QString & groupIdOld);
    void removeObject(NxObject *object);
public:
    inline NxObjectDispatchProperty* getObject(const QString & objectIdStr, bool saveObject = true) {
        if(currentDocument) {
            bool ok = false;
            quint16 objectId = objectIdStr.toUInt(&ok);
            if(ok) {
                NxObject *object = currentDocument->getObject(objectId);
                if(saveObject)
                    currentDocument->setCurrentObject(object);
                return object;
            }
            else if(objectIdStr.toLower() == "all")
                return currentDocument;
            else if(objectIdStr.toLower() == "current")
                return currentDocument->getCurrentObject();
            else if(objectIdStr.toLower() == "lastcurve")
                return currentDocument->getCurrentCurve();
            else {
                if(currentDocument->groups.contains(objectIdStr))
                    return currentDocument->groups.value(objectIdStr);
                else
                    return 0;
            }
        }
        return 0;
    }


    //FACTORY INTERFACE
private:
    QHash<QString, NxDocument*> documents;
    QFileSystemWatcher fileWatcher;
    ExtMessage message;
    QHash<QByteArray, ExtMessage> messagesCache;
    QScriptEngine messageScriptEngine;
private slots:
    void fileWatcherChanged(const QString &);
private:
    void fileWatcherFolder(QStringList extension, QDir dir, QTreeWidgetItem *parentList, bool isDocument);
public slots:
    const QVariant execute(const QString & command, bool createNewObjectIfExists = false, bool dump = false);
    void onOscReceive(const QString & message);
    void onDraw();
    void askNxObject();
    void send(const ExtMessage & message);
    void sendMessage(void *_object, void *_trigger, void *_cursor, void *_collisionCurve, const NxPoint & collisionPoint, const NxPoint & collisionValue, const QString & status);


    //EXTERNAL INTERFACES
private:
    ExtOscManager *osc;
    ExtTcpManager *tcp;
    ExtUdpManager *udp;
    ExtHttpManager *http;
    ExtSerialManager *serial;
    ExtMidiManager *midi;
    bool oscConsoleActive;
    QString defaultMessageTrigger, defaultMessageCursor;
    NxTrigger *transportObject, *syncObject;
public:
    void loadProject(const QString & projectFile);


    //TIME MANAGEMENT
private:
    UiRender *render;
    QTime renderMeasure;
private:
    qreal timeLocal, timeTransportRefresh, timePerfRefresh, timePerfCounter;
    QTimer *timer;
    bool forceTimeLocal;
private slots:
    void timerEvent();
    void closeSplash();
signals:
    void updateTransport(QString, QString);
public:
    qreal getCpuUsage();

    void setScheduler(bool start);
    inline bool getScheduler() const {
        if(timer)
            return timer->isActive();
        else
            return false;
    }


    //USER INTERFACE
private:
    UiTransport *transport;
    UiInspector *inspector;
    UiView *view;
    UiSplash *splash;
    UiAbout *about;
    UiEditor *editor;
    quint16 freehandCurveId, freehandCurveIndex;
    QNetworkAccessManager *updateManager;
    void checkForUpdates();
    QTreeWidgetItem *projectScore, *projectScript, *exampleScript, *libScript;
    NxPoint editingStartPoint;
    bool lastMessageAllow;
    QString lastMessage;
private slots:
    void checkForUpdatesFinished(QNetworkReply*);
public:
    void show();
public slots:
    void actionToggle_Inspector();
    void actionToggle_Transport();
    void actionToggle_Autosize();
    void actionPlay_pause();
    void actionFast_rewind();
    void actionLogo();
    void actionGoto();
    void actionSetScheduler();
    void actionSetOpenGL();
    void actionSpeed();
    void actionTabChange(int);
    void actionViewChange();
    void actionCC();
    void actionCC2();
    void actionChangeID(quint16, quint16); ////CG////
    void actionNew();
    void actionOpen();
    void actionSave();
    void actionSave_as();
    void actionSave_all();
    void actionRename();
    void actionRemove();
    void actionDuplicateScore();
    void actionUndo();
    void actionRedo();
    void actionSync();
    void actionProjectFiles();
    void actionProjectScripts();
    void actionProjectScriptsContext(const QPoint & point);
    void actionProjectFilesContext(const QPoint & point);
    void actionDrawFreeCurve();
    void actionDrawPointCurve();
    void actionDrawTriggers();
    void actionAddFreeCursor();
    void actionCircleCurve();
    void editingStart(const NxPoint &);
    void editingStop();
    void editingMove(const NxPoint &, bool add);
    void actionGridChange(qreal val);
    void actionGridOpacityChange(qreal val);
    void actionSnapGrid();
    void actionCloseEvent(QCloseEvent *event);
    void transportMessageChange(const QString & );
    void syncMessageChange(const QString & );
public slots:
    void logOscSend(const QString & message);
    void logOscReceive(const QString & message);
    void pushSnapshot();
};

#endif // IANNIX_H
