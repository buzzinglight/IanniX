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

#ifndef NXDOCUMENT_H
#define NXDOCUMENT_H

#include <QObject>
#include <QScriptEngine>
#include <QFile>
#include <QFileInfo>
#include <QInputDialog>
#include <QFileSystemWatcher>
#include "misc/application.h"
#include "objects/nxgroup.h"
#include "interfaces/extscriptvariableask.h"

#include "gui/uimessagebox.h"
#include "messages/messagemanagerloginterface.h"

class NxDocument : public QObject, public QTreeWidgetItem, public MessageDispatcher, public NxObjectDispatchProperty {
    Q_OBJECT

public:
    ExecuteSource source;
    UiFileItem *fileItem;
    QString initialContent;
    bool skipClose;
public slots:
    void askFileOpen();
    void askFileOpen(bool mode);
    void askFileSave();
    void askFileReload();
    void askFileClose();
    void open();
    void save();
private:
    bool isLoaded;
    QList<QString> snapshots;
    quint16 snapshotsIndex;
    QFileInfo hiddenFilename;
public:
    explicit NxDocument(ApplicationCurrent *parent, UiFileItem *_fileItem = 0);

    inline void clear() {
        QStringList commands;
        foreach(const NxObject *object, objects)
            commands << QString(COMMAND_REMOVE) + " " + QString::number(object->getId());
        foreach(const QString & command, commands)
            Application::current->execute(command, ExecuteSourceCopyPaste);
    }

    void setHiddenFilename(const QFileInfo &_hiddenFilename) { hiddenFilename = _hiddenFilename; }

    const QString serialize() const;
    void pushSnapshot();
    void popSnapshot(bool revert=false);
    void updateCode(bool fromFile);
    const QString getContent(bool fromFile);
    void remplaceInFunction(QString *content, const QString &delimiter, const QString &data);
    QScriptValue scriptEvaluate(const QString &script, bool _createNewObjectIfExists);

public:
    QMap<QString, NxGroup*> groups;
    QHash<quint16, NxObject*> objects;

private:
    NxObject *currentObject;
    NxGroup *currentGroup;
    NxCurve *currentCurve;
public slots:
    inline void setCurrentObject(NxObject *_currentObject) {
        currentObject = _currentObject;
        if((currentObject) && (currentObject->getType() == ObjectsTypeCurve))
            currentCurve = (NxCurve*)currentObject;
    }
    inline void setCurrentGroup(NxGroup *_currentGroup) {  currentGroup = _currentGroup;  }
    inline NxObject* getCurrentObject() const { return currentObject; }
    inline NxCurve* getCurrentCurve()   const { return currentCurve;  }
    inline NxGroup* getCurrentGroup()   const { return currentGroup;  }

public:
    inline NxObject* getObject(quint16 id) const {
        if(objects.contains(id))
            return objects.value(id);
        else
            return 0;
    }
    inline NxGroup* getGroup(QString id) const {
        if(groups.contains(id))
            return groups.value(id);
        else
            return 0;
    }
    inline quint16 nextAvailableId() const {
        //return objects.count();
        quint16 nextId = 0;
        for(quint16 index = 0 ; index < objects.count() ; index++)
            if(objects.keys().at(index) > nextId)
                nextId = objects.keys().at(index);
        return nextId+1;
    }



    //SCRIPT
public:
    QScriptEngine scriptEngine;
protected:
    ExtScriptVariableAsk *variable;
    QScriptValue script;
    QScriptValue scriptOnIncomingMessage, scriptMakeWithScript, scriptAlterateWithScript, scriptMadeThroughGUI, scriptMadeThroughInterfaces, scriptAskUserForParameters;
    NxPoint mousePos;
    QString scriptContent;

public:
    void open(bool configure);
    inline void setMousePos(const NxPoint & _pos) {
        mousePos = _pos;
    }

    inline QString incomingMessage(const MessageIncomming &source, bool needOutput = false, bool needToScript = true) {
        if(scriptOnIncomingMessage.isValid()) {
            QString argumentsStr;
            foreach(const QString &argument, source.arguments)
                argumentsStr += "\"" + argument + "\",";
            argumentsStr.chop(1);
            if(needOutput)  return scriptOnIncomingMessage.call(QScriptValue(), QScriptValueList() << source.protocol << source.host << source.port.toString() << source.destination << scriptEngine.evaluate(QString("[%5]").arg(argumentsStr))).toString();
            else            scriptOnIncomingMessage.call(QScriptValue(), QScriptValueList() << source.protocol << source.host << source.port.toString() << source.destination << scriptEngine.evaluate(QString("[%5]").arg(argumentsStr)));
        }
        return QString();
    }

    inline const QFileInfo getScriptFile() const {
        if(fileItem)    return fileItem->filename.file;
        else            return hiddenFilename;
    }

public:
    bool createNewObjectIfExists;
public slots:
    void ask(const QString & group, const QString & prompt, const QString & value, const QString & def)     {   return variable->ask(group, prompt, value, def);    }
    void meta(const QString & meta)                                                                         {   return variable->meta(meta);    }
    const QVariant execute(const QString & command) const                                                   {   return Application::current->execute(command, source, createNewObjectIfExists, true);   }

public:
    static const QString loadLibrary();

public:
    inline void dispatchProperty(const char *_property, const QVariant & value) {
        //Browse groups
        foreach(NxGroup *group, groups)
            group->dispatchProperty(_property, value);
    }
    inline const QVariant getProperty(const char *_property) const {
        foreach(NxGroup *group, groups)
            return group->getProperty(_property);
        return QVariant();
    }
    inline quint8 getType() const {
        return ObjectsTypeDocument;
    }
    inline const QString getTypeStr() const {
        return "document";
    }
    inline const NxRect getBoundingRect() const {
        NxRect boundingRect;

        //Browse groups
        foreach(const NxGroup *group, groups)
            boundingRect = boundingRect.united(group->getBoundingRect());

        return boundingRect;
    }


    //DEFAULT
public:
    static void restoreDefaults();

signals:


};

#endif // NXDOCUMENT_H
