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
    explicit ExtScriptManager(NxObjectFactoryInterface *_factory, QFileInfo _scriptFile = QFileInfo(), QTreeWidgetItem *parentList = 0);

protected:
    NxObjectFactoryInterface *factory;
    ExtScriptVariableAsk *variable;
    QFileSystemWatcher fileWatcher;
    QScriptValue script, scriptOnOSC, scriptOnDraw, scriptOnLoad, scriptCreate, scriptConfigure;
    QScriptEngine scriptEngine;
    QFileInfo scriptFile;
    QPointF mousePos;
    QString scriptContent;
    qint16 objectId;
    bool hasChanged;

public:
    bool parseScript(bool configure = true);
    inline void setMousePos(const QPointF & _pos) {
        mousePos = _pos;
    }
    inline void setObjectId(qint16 _objectId) {
        objectId = _objectId;
    }
    inline void onOSCCall(const QString & message) {
        if(scriptOnOSC.isValid())
            scriptOnOSC.call(QScriptValue(), QScriptValueList() << message);
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

private slots:
    void fileWatcherChanged(const QString &);
};

#endif // EXTSCRIPTMANAGER_H
