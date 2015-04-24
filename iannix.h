/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

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
#include <QSettings>
#include <QFontDialog>
#include <QWaitCondition>
#include <QDomDocument>
#include <QFileOpenEvent>
#include <QDesktopServices>
#include <time.h>
#include "misc/application.h"
#include "gui/uimessagebox.h"
#include "gui/uiview.h"
#include "gui/uiinspector.h"
#include "gui/uihelp.h"
#include "messages/messagemanager.h"
#include "interfaces/interfacesyphon.h"
#include "interfaces/interfacedirect.h"
#include "interfaces/interfacehttp.h"
#include "interfaces/interfacemidi.h"
#include "interfaces/interfaceosc.h"
#include "interfaces/interfaceserial.h"
#include "interfaces/interfacetcp.h"
#include "interfaces/interfaceudp.h"
#ifdef WACOM_INSTALLED
#include "interfaces/extwacommanager.h"
#endif

class IanniX : public ApplicationCurrent, public NxObjectDispatchProperty, public MessageDispatcher {
    Q_OBJECT

private:
    QDir scriptDir;
    QSettings *iniSettings, *globalSettings;
public:
    explicit IanniX(const QString &_projectToLoad = "", QObject *parent = 0);
    void readyToStart();
    inline void dispatchProperty(const QString &_property, const QVariant &value)  {    dispatchProperty(qPrintable(_property), value); }
    inline const QVariant getProperty(const QString &_property) const              {    return getProperty(qPrintable(_property));      }
    inline void dispatchProperty(const char *_property, const QVariant &value) {
        QHashIterator<QString, NxDocument*> documentIterator(documents);
        while (documentIterator.hasNext()) {
            documentIterator.next();
            documentIterator.value()->dispatchProperty(_property, value);
        }
    }
    inline const QVariant getProperty(const char *_property) const {
        NxDocument *document = getWorkingDocument();
        return document->getProperty(_property);
    }
    inline quint8 getType() const {
        return ObjectsTypeScheduler;
    }
    inline const QString getTypeStr() const {
        return "scheduler";
    }


    //OBJECT MANAGEMENT
private:
    NxDocument *currentDocument, *workingDocument;
    QHash<QString, NxDocument*> documents;
    inline NxDocument* getCurrentDocument() const { return currentDocument; }
    inline NxDocument* getWorkingDocument() const { return workingDocument; }
    void setCurrentDocument(NxDocument *_currentDocument);
public:
    NxGroup* addGroup(const QString & groupId);
    void setObjectActivity(void *_object, quint8 activeOld);
    void setObjectGroupId(void *_object, const QString & groupIdOld);
    void setObjectId(void *_object, quint16 idOld);
    void removeObject(NxObject *object);
    quint16 getCount(qint8 objectType = -1);
    void* getObjectById(quint16 id) {
        return getWorkingDocument()->getObject(id);
    }

public:
    inline NxObjectDispatchProperty* getObject(const QString & objectIdStr, bool saveObject = true) const {
        NxDocument *document = getWorkingDocument();
        bool ok = false;
        quint16 objectId = objectIdStr.toUInt(&ok);
        if(ok) {
            NxObject *object = document->getObject(objectId);
            if(saveObject)
                document->setCurrentObject(object);
            return object;
        }
        else if(objectIdStr.toLower() == "all")
            return document;
        else if(objectIdStr.toLower() == "current")
            return document->getCurrentObject();
        else if(objectIdStr.toLower() == "selection")
            return render->getSelection();
        else if(objectIdStr.toLower() == "lastcurve")
            return document->getCurrentCurve();
        else {
            if(document->groups.contains(objectIdStr))
                return document->groups.value(objectIdStr);
        }
        return 0;
    }


    //FACTORY INTERFACE
private:
    Message message;
    QHash<QByteArray, Message> messagesCache;
    QScriptEngine messageScriptEngine;
public slots:
    const QVariant execute(const MessageIncomming & command, bool createNewObjectIfExists = false, bool needOutput = false);
    const QVariant execute(const QString & command, ExecuteSource source, bool createNewObjectIfExists = false, bool needOutput = false);
    void executeAsScript(const QString &script);
    inline QString argvFullString(const QString &command, const QStringList &argv, quint16 index) const {
        if(index >= 1)   return command.mid(command.indexOf(argv.at(index), command.indexOf(argv.at(index-1))+argv.at(index-1).length())).trimmed();
        else             return command;
    }
    inline qreal argvDouble(const QStringList &argv, quint16 index) const {
        if(index < argv.count())    return argv.at(index).toDouble();
        else                        return 0;
    }
    QString incomingMessage(const MessageIncomming &source, bool needOutput = false, bool needToScript = true);
    void openMessageEditor();
    void send(const Message &message, QStringList *sentMessage = 0);
    QMainWindow* getMainWindow()        { return view; }
    UiRenderPreview* getRenderPreview() { return view->getRenderPreview(); }
    bool getPerformancePreview()        { return view->getPerformancePreview(); }


    //EXTERNAL INTERFACES
private:
#ifdef WACOM_INSTALLED
    ExtWacomManager  *wacom;
#endif
public:
    bool projectIsLoaded;
    QString projectToLoad;
    void loadProject(const QString & projectFile = "");

    //TIME MANAGEMENT
private:
    UiRender *render;
    QTimer *timer;
    int timerTime, timerPerf;
private:
    SchedulerActivity schedulerActivity;
public:
    void setScheduler(SchedulerActivity _schedulerActivity);
protected:
    void timerEvent(QTimerEvent *);
private slots:
    void timerTick();
    void timerTick(bool force);
    void timerTick(qreal delta);
    void timerTrig(void *object, bool force = false);


    //USER INTERFACE
private:
    Transport *transport;
    UiInspector *inspector;
    UiView *view;
    QString waitForMessageValue;
    bool waitingForMessageValue;
    QIcon iconAppPlay, iconAppPause;
private:
    QString updateAnonymousId;
    QNetworkAccessManager *updateManager;
private slots:
    void checkForUpdatesFinished(QNetworkReply*);
public:
    bool forceUpdate, forbidUpdate;
    void checkForUpdates();
    const QString serialize() const;
public slots:
    void forceGoto(qreal, bool midiSync = true);
    void forceSchedulerTimer(qreal);
    void forceOpenGLTimer(qreal);

    void actionPlayPause();
    void actionCC(QTreeWidgetItem*,int);
    void actionNew();
    void actionOpen();
    void actionSave();
    void actionSaveAndReload();
    void actionSave_as();
    void actionRefresh();
    void currentDocumentChanged(UiSyncItem*);
    void actionUndo();
    void actionRedo();
    void actionImportSVG(const QString &filename);
    void actionImportBackground(const QString &filename);
    void actionImportText(const QString &font, const QString &text);
    void actionReloadScript();
    void actionCloseEvent(QCloseEvent *event);
    void actionUnmuteGroups();
    void actionUnmuteObjects();
    void actionUnsoloGroups();
    void actionUnsoloObjects();
public slots:
    QString waitForMessage();
    void pushSnapshot();
    void actionPaste();
    void actionCopy();
signals:
    void waitForMessageArrived();


    //FAST IMPORT
public:
    void actionImportSVG(const QDomElement &xmlElement, qreal scale);
};

#endif // IANNIX_H
