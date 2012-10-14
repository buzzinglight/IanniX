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

#ifndef IANNIX_H
#define IANNIX_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QFileDialog>
#include <QInputDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileSystemWatcher>
#include <QApplication>
#include <QHostInfo>
#include <QDomDocument>
#include <QFileOpenEvent>
#include "uimessagebox.h"
#include "nxcpu.h"
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
#include "uitimer.h"
#include "uitransport.h"
#include "uiview.h"
#include "uiinspector.h"
#include "uieditor.h"
#include "uihelp.h"
#ifdef WACOM_INSTALLED
#include "extwacommanager.h"
#endif

enum SchedulerActivity { SchedulerOff, SchedulerOn, SchedulerOneShot };

class IanniX : public NxObjectFactoryInterface, public NxObjectDispatchProperty {
    Q_OBJECT

private:
    QDir scriptDir;
    QString baseDocumentDir;
    bool hasStarted;
public:
    explicit IanniX(QObject *parent, bool forceSettings);
    void readyToStart();
    inline void dispatchProperty(const QString & property, const QVariant & value) {
        //Browse documents
        foreach(NxDocument *document, documents)
            document->dispatchProperty(property, value);
    }
    inline const QVariant getProperty(const QString &_property) const {
        //Browse documents
        foreach(NxDocument *document, documents)
            return document->getProperty(_property);
        return QVariant();
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
    ExtScriptManager *currentScript;
    QList<ExtScriptManager*> activeScripts;
public:
    NxGroup* addGroup(const QString & documentId, const QString & groupId);
    void setObjectActivity(void *_object, quint8 activeOld);
    void setObjectGroupId(void *_object, const QString & groupIdOld);
    void removeObject(NxObject *object);
public:
    inline NxObjectDispatchProperty* getObject(const QString & objectIdStr, bool saveObject = true) const {
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
    bool acceptMidiSyncClock, acceptMidiSyncSong;
private slots:
    void fileWatcherChanged(const QString &);
private:
    void fileWatcherFolder(QStringList extension, QDir dir, QTreeWidgetItem *parentList, bool isDocument);
public slots:
    const QVariant execute(const QString & command, bool createNewObjectIfExists = false, bool dump = false);
    inline QString argvFullString(const QString &command, const QStringList &argv, quint16 index) const {
        if(index >= 1)   return command.mid(command.indexOf(argv.at(index), command.indexOf(argv.at(index-1))+argv.at(index-1).length())).trimmed();
        else            return command;
    }
    inline qreal argvDouble(const QStringList &argv, quint16 index) const {
        if(index < argv.count())    return argv.at(index).toDouble();
        else                        return 0;
    }

    QString onOscReceive(const QString & protocol, const QString & host, const QString & port, const QString & destination, const QStringList & arguments);
    QString onDraw();
    void askNxObject(void *_object, bool shift);
    void send(const ExtMessage & message);
    void sendMessage(void *_object, void *_trigger, void *_cursor, void *_collisionCurve, const NxPoint & collisionPoint, const NxPoint & collisionValue, const QString & status);
    QImage takeScreenshot();
    QMainWindow* getMainWindow() { return view; }
    UiRenderPreview* getRenderPreview() { return view->getRenderPreview(); }
    bool getPerformancePreview() { return view->getPerformancePreview(); }
    void syncStop() {
        if((acceptMidiSyncSong) && (schedulerActivity != SchedulerOff)) {
            setScheduler(SchedulerOff);
            sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "stop");
        }
    }
    void syncStart() {
        if((acceptMidiSyncSong) && (schedulerActivity != SchedulerOn)) {
            setScheduler(SchedulerOn);
            sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "play");
        }
    }
    void syncGoto(qreal time) {
        if(acceptMidiSyncSong)
            actionGoto(time, false);
    }
    void syncTimer(qreal delta) {
        if(acceptMidiSyncClock) {
            timerOk = false;
            timerTick(delta);
        }
    }

    void scriptError(const QStringList &error, qint16 line) const {
        editor->scriptError(error, line);
    }
public:
    qreal getTimeLocal() const { return timeLocal; }


    //EXTERNAL INTERFACES
private:
    ExtOscManager    *osc;
    ExtTcpManager    *tcp;
    ExtUdpManager    *udp;
    ExtHttpManager   *http;
    ExtSerialManager *serial;
    ExtMidiManager   *midi;
#ifdef WACOM_INSTALLED
    ExtWacomManager  *wacom;
#endif
    bool oscConsoleActive;
    QHostAddress oscBundleHost;
    quint16 oscBundlePort;
    QString defaultMessageTrigger, defaultMessageCursor;
    NxTrigger *transportObject, *syncObject;
    QString ipOut, midiOut;
    int ipOutId;
public:
    void loadProject(const QString & projectFile);
public slots:
    void setIpOut(const QString &);
    void setMidiOut(const QString &);
    void ipOutStatusFound(const QHostInfo &);
    void setMidiSyncSong(bool);
    void setMidiSyncClock(bool);
    void setMidiOutNewDevice(const QString &midi);
signals:
    void ipOutStatus(bool);
    void midiOutStatus(bool);


    //TIME MANAGEMENT
private:
    UiRender *render;
    qreal renderMeasureAbsoluteValOld;
    QTime renderMeasureAbsolute;
    NxCpu *cpu;
private:
    qreal timeLocal, timeTransportRefresh, timePerfRefresh, timePerfCounter;
    QString timeLocalStr;
    QTimer *timer;
    bool timerOk;
    bool forceTimeLocal;
protected:
    void timerEvent(QTimerEvent *);
private slots:
    void timerTick();
    void timerTick(bool force);
    void timerTick(qreal delta);
    void timerTrig(void *object, bool force = false);
    void closeSplash();
signals:
    void updateTransport(QString, QString);
private:
    SchedulerActivity schedulerActivity;
public:
    void setScheduler(SchedulerActivity _schedulerActivity);
    inline bool getScheduler() const {
        return timerOk;
    }


    //USER INTERFACE
private:
    UiTransport *transport;
    UiInspector *inspector;
    UiView *view;
    UiTimer *uitimer;
    UiSplash *splash;
    UiAbout *about;
    UiEditor *editor;
    quint16 freehandCurveId, freehandCurveIndex;
    QNetworkAccessManager *updateManager;
    void checkForUpdates();
    QTreeWidgetItem *projectScore, *projectScript, *exampleScript, *libScript;
    NxPoint editingStartPoint;
    bool lastMessageAllow, lastMessageReceivedAllow;
    QString lastMessage, lastMessageReceived;
    QIcon iconAppPlay, iconAppPause;
private slots:
    void checkForUpdatesFinished(QNetworkReply*);
public:
    void show();
    QString serialize();
public slots:
    void actionToggle_Inspector();
    void actionToggle_Transport();
    void actionToggle_Autosize();
    void actionPlay_pause();
    void actionFast_rewind();
    void actionLogo();
    void actionGoto();
    void actionGoto(qreal, bool midiSync = true);
    void actionSetScheduler();
    void actionSetOpenGL();
    void actionSpeed();
    void actionTabChange(int);
    void actionViewChange();
    void actionCC();
    void actionCC2();
    void actionChangeID(quint16, quint16); ////CG////
    void actionNew();
    void actionNewScript();
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
    void actionProjectScript();
    void actionProjectScriptsContext(const QPoint & point);
    void actionProjectFilesContext(const QPoint & point);
    void actionDrawFreeCurve();
    void actionDrawPointCurve();
    void actionDrawTriggers();
    void actionAddFreeCursor();
    void actionCircleCurve();
    void actionImportSVG(const QString &filename);
    void actionImportImage(const QString &filename);
    void actionImportBackground(const QString &filename);
    void actionSelectionModeChange(bool,bool,bool);
    void actionImportText(const QString &font, const QString &text);
    void actionImportOldIanniXScore(const QString & filename);
    void editingStart(const NxPoint &);
    void editingStop();
    void editingMove(const NxPoint &, bool add);
    void actionGridChange(qreal val);
    void actionGridOpacityChange(qreal val);
    void actionShowEditor();
    void actionShowTimer();
    void actionReloadScript();
    void actionCloseEvent(QCloseEvent *event);
    void transportMessageChange(const QString & );
    void syncMessageChange(const QString & );
    void bundleMessageChange(const QString &, quint16);
    void actionUnmuteGroups();
    void actionUnmuteObjects();
    void actionUnsoloGroups();
    void actionUnsoloObjects();
    void allowSyphonServer(bool);
public slots:
    void logOscSend(const QString & message);
    void logOscReceive(const QString & message);
    QString waitForMessage();
    void pushSnapshot();
    void actionPasteScript();
signals:
    void newMessageArrived();


    //FAST IMPORT
public:
    void actionImportSVG(const QDomElement &xmlElement, qreal scale);
};

#endif // IANNIX_H
