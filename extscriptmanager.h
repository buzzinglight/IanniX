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

#ifndef EXTSCRIPTMANAGER_H
#define EXTSCRIPTMANAGER_H

#include <QObject>
#include <QScriptEngine>
#include <QFile>
#include <QFileInfo>
#include <QInputDialog>
#include <QFileSystemWatcher>
#include "nxobjectfactoryinterface.h"
#include "extscriptvariableask.h"
#include "nxobject.h"
#include "uirenderoptions.h"

class ExtScriptManager : public QObject, public QTreeWidgetItem {
    Q_OBJECT

public:
    explicit ExtScriptManager(NxObjectFactoryInterface *_factory, QFileInfo _scriptFile = QFileInfo(), QTreeWidgetItem *parentList = 0, QDir _scriptDir = QDir::current());

protected:
    NxObjectFactoryInterface *factory;
    ExtScriptVariableAsk *variable;
    QFileSystemWatcher fileWatcher;
    QScriptValue script, scriptOnOSC, scriptOnDraw, scriptOnLoad, scriptCreate, scriptConfigure;
    QScriptEngine scriptEngine;
    QFileInfo scriptFile;
    NxPoint mousePos;
    QString scriptContent;
    QDir scriptDir;
    qint16 objectId;
    bool hasChanged;

public:
    bool parseScript(bool configure = true);
    inline void setMousePos(const NxPoint & _pos) {
        mousePos = _pos;
    }
    inline void setObjectId(qint16 _objectId) {
        objectId = _objectId;
    }
    inline void onOSCCall(const QString & protocol, const QString & host, const QString & port, const QString & destination, const QStringList & arguments) {
        if(scriptOnOSC.isValid()) {
            QString argumentsStr = "";
            foreach(const QString & argument, arguments)
                argumentsStr += "\"" + argument + "\",";
            argumentsStr.chop(1);
            scriptOnOSC.call(QScriptValue(), QScriptValueList() << protocol << host << port << destination << scriptEngine.evaluate(tr("[%5]").arg(argumentsStr)));
        }
    }
    inline void onDrawCall(qreal time) {
        if(scriptOnDraw.isValid())
            scriptOnDraw.call(QScriptValue(), QScriptValueList() << time);
    }
    inline const QFileInfo & getScriptFile() const {
        return scriptFile;
    }
    inline void rename(const QString & newFileName) {
        if(!QFile::exists(newFileName)) {
            QString oldFileName = scriptFile.absoluteFilePath();
            setNewFilename(newFileName);
            QFile::rename(oldFileName, newFileName);
        }
        else {
            QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be renamed! A file with this name exists in your project."), QMessageBox::Ok);
        }
    }
    inline void remove() {
        QFile::remove(scriptFile.absoluteFilePath());
    }
    inline void setNewFilename(const QString & newFileName) {
        scriptFile.setFile(newFileName);
    }
    void load();
    bool save(UiRenderOptions *options);


public slots:
    const QVariant execute(const QString & command) const {
        return factory->execute(command);
    }
    void ask(const QString & group, const QString & prompt, const QString & value, const QString & def) {
        return variable->ask(group, prompt, value, def);
    }
    void meta(const QString & meta) {
        return variable->meta(meta);
    }
    inline void updateTitle() {
        if(hasChanged)
            setText(0, scriptFile.baseName() + "*");
        else
            setText(0, scriptFile.baseName());
    }

protected:
    inline void setHasChanged(bool _hasChanged) {
        hasChanged = _hasChanged;
        updateTitle();
    }

public:
    static const QString loadLibrary(const QDir & libScriptDir);

private slots:
    void fileWatcherChanged(const QString &);
};

#endif // EXTSCRIPTMANAGER_H
