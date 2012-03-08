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

#include "extscriptmanager.h"

ExtScriptManager::ExtScriptManager(NxObjectFactoryInterface *_factory, QFileInfo _scriptFile, QTreeWidgetItem *parentList, QDir) :
        QObject(_factory), QTreeWidgetItem(parentList, 1024) {
    factory = _factory;
    scriptFile = _scriptFile;
    //scriptDir = _scriptDir;
    objectId = -1;
    connect(&fileWatcher, SIGNAL(fileChanged(QString)), SLOT(fileWatcherChanged(QString)));
    setFlags(Qt::ItemIsSelectable | /*Qt::ItemIsEditable |*/ Qt::ItemIsEnabled);
    setText(0, scriptFile.baseName());
}



bool ExtScriptManager::parseScript(bool configure) {
    //Open the script file (if its a file)
    QFile scriptFileContent(scriptFile.absoluteFilePath());
    if(scriptFileContent.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //Read file
        scriptContent = scriptFileContent.readAll();
        scriptFileContent.close();

        if(scriptFile.absoluteFilePath().endsWith(".nxscore")) {
            if(factory) {
                QStringList paste = scriptContent.split(COMMAND_END, QString::SkipEmptyParts);
                foreach(const QString & command, paste)
                    factory->execute(command);
            }
        }
        else {
            //GUI to ask the user variables
            variable = new ExtScriptVariableAsk(0);

            //Open the script
            QScriptValue scriptFunctions = scriptEngine.newQObject(this);
            script = scriptEngine.globalObject();

            //Map specials features/keywords/functions
            script.setProperty("mouseX", mousePos.x());
            script.setProperty("mouseY", mousePos.y());
            script.setProperty("objectId", objectId);
            script.setProperty("iannix", scriptFunctions);
            script.setProperty("nx", scriptFunctions);

            //Prepend with prepackaged functions
            QString scriptPreContent = loadLibrary(scriptDir);

            //Launch the script
            QScriptValue scriptReturn = scriptEngine.evaluate(scriptContent + scriptPreContent);

            //Extract function
            scriptOnOSC = script.property("onMessage");
            scriptOnDraw = script.property("onTick");
            scriptOnLoad = script.property("onLoad");
            scriptCreate = script.property("onCreate");
            scriptConfigure  = script.property("onConfigure");

            //Extract errors
            QStringList errors = scriptEngine.uncaughtExceptionBacktrace();
            QString errorsMessage = "";
            if(scriptReturn.isError())
                errors << scriptReturn.property("message").toString();
            foreach(const QString & error, errors)
                errorsMessage += error + "\r\n";
            if(errors.count()) {
                QMessageBox message;
                message.setText(tr("Error found"));
                message.setInformativeText(errorsMessage);
                message.setWindowTitle(tr("IanniX") + QString(" - ") + tr("Script Error"));
                message.setStandardButtons(QMessageBox::Ok);
                message.exec();
            }

            //Call the "configure()" function
            QString scriptId = scriptFile.baseName().replace(" ", "");
            if(configure) {
                fileWatcher.addPath(scriptFile.absoluteFilePath());
                scriptConfigure.call(QScriptValue(), QScriptValueList());
                factory->execute("pushSnapshot " + scriptId);
            }
            factory->execute("popSnapshot " + scriptId);

            //Ask variables to user and sets the variable in the script
            QList<ExtScriptVariable*> variables = variable->ask();
            if(variable->result()) {
                foreach(ExtScriptVariable *variable, variables) {
                    if(variable->isDefFloat())
                        script.setProperty(variable->getValue(), variable->getDefFloat());
                    else
                        script.setProperty(variable->getValue(), variable->getDefStr());
                }

                //Call the "create()" function
                scriptCreate.call(QScriptValue(), QScriptValueList());

                return true;
            }
        }
    }
    return false;
}

void ExtScriptManager::fileWatcherChanged(const QString &) {
    if(isSelected()) {
        parseScript(false);
        factory->execute("fastrewind");
    }
}

const QString ExtScriptManager::loadLibrary(const QDir & libScriptDir) {
    QString scriptContent = "";

    QFileInfoList scriptDirs = QDir(libScriptDir.absoluteFilePath("Tools/")).entryInfoList(QStringList() << "*.js", QDir::Files | QDir::NoDotAndDotDot);
    foreach(const QFileInfo & scriptFile, scriptDirs) {
        QFile scriptFileContent(scriptFile.absoluteFilePath());
        if(scriptFileContent.open(QIODevice::ReadOnly | QIODevice::Text)) {
            //Read file
            scriptContent += scriptFileContent.readAll();
            scriptFileContent.close();
        }
    }
    return scriptContent;
}

