#include "extscriptmanager.h"

ExtScriptManager::ExtScriptManager(NxObjectFactoryInterface *_factory, QFileInfo _scriptFile, QTreeWidgetItem *parentList) :
        QObject(_factory), QTreeWidgetItem(parentList, 1024) {
    factory = _factory;
    scriptFile = _scriptFile;
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

            //Launch the script
            QScriptValue scriptReturn = scriptEngine.evaluate(scriptContent);

            //Extract function
            scriptOnOSC = script.property("onMessage");
            scriptOnDraw = script.property("onDraw");
            scriptOnLoad = script.property("onLoad");
            scriptCreate = script.property("onCreate");
            scriptConfigure  = script.property("onConfigure");

            //Extract errors
            QStringList errors = scriptEngine.uncaughtExceptionBacktrace();
            QString errorsMessage = "";
            if(scriptReturn.isError())
                errors << scriptReturn.property("message").toString(); ;
            foreach(const QString & error, errors)
                errorsMessage += error + "\r\n";
            if(errors.count()) {
                QMessageBox message;
                message.setText(tr("Error found"));
                message.setInformativeText(errorsMessage);
                message.setWindowTitle(tr("IanniX Script Error"));
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
                foreach(ExtScriptVariable *variable, variables)
                    script.setProperty(variable->getValue(), variable->getDef());

                //Call the "create()" function
                scriptCreate.call(QScriptValue(), QScriptValueList());

                return true;
            }
        }
    }
    return false;
}

void ExtScriptManager::fileWatcherChanged(const QString &path) {
    if(isSelected()) {
        parseScript(false);
        factory->execute("fastrewind");
    }
}
