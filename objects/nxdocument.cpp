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

#include "nxdocument.h"

NxDocument::NxDocument(ApplicationCurrent *parent, UiFileItem *_fileItem) :
    QObject(parent) {
    fileItem = _fileItem;
    connect(fileItem, SIGNAL(askFileClose()),  SLOT(askFileClose()));
    connect(fileItem, SIGNAL(askFileOpen()),   SLOT(askFileOpen()));
    connect(fileItem, SIGNAL(askFileReload()), SLOT(askFileReload()));
    connect(fileItem, SIGNAL(askFileSave()),   SLOT(askFileSave()));
    setCurrentObject(0);
    setCurrentGroup(0);
    currentCurve = 0;
    snapshotsIndex = 0;
    isLoaded = false;
}


const QString NxDocument::serialize() const {
    QString retour;
    QString prefix = "\trun(\"", postfix = "\");\n";

    if(NxObjectDispatchProperty::source == ExecuteSourceGui) {
        //Textures
        QMapIterator<QString, UiRenderTexture*> textureIterator(*Global::textures);
        while (textureIterator.hasNext()) {
            textureIterator.next();
            UiRenderTexture *texture = textureIterator.value();
            if(texture->filename.exists()) {
                QString filename = getScriptFile().absoluteDir().relativeFilePath(texture->filename.absoluteFilePath());
                retour += prefix + QString("%1 %2 %3  %4 %5 %6 %7").arg(COMMAND_TEXTURE).arg(textureIterator.key()).arg(texture->mapping.topLeft().x()).arg(texture->mapping.topLeft().y()).arg(texture->mapping.bottomRight().x()).arg(texture->mapping.bottomRight().y()).arg(filename) + postfix;
            }
        }

        //Colors
        QMapIterator<QString, QColor> colorIterator(*Global::colors);
        while (colorIterator.hasNext()) {
            colorIterator.next();
            if(!((Global::defaultColors.contains(colorIterator.key())) && (Global::defaultColors.value(colorIterator.key()) == colorIterator.value()))) {
                QColor color = colorIterator.value();
                retour += prefix + QString("%1 %2  %3 %4 %5 %6").arg(COMMAND_GLOBAL_COLOR).arg(colorIterator.key()).arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()) + postfix;
            }
        }

        retour += COMMAND_END;
    }

    //Browse groups
    foreach(NxGroup *group, groups)
        retour += group->serialize();

    return retour;
}

void NxDocument::pushSnapshot() {
    NxObjectDispatchProperty::source = ExecuteSourceCopyPaste;
    if(snapshotsIndex < snapshots.count())
        snapshots.replace(snapshotsIndex, Application::current->serialize());
    else
        snapshots.append(Application::current->serialize());
    snapshotsIndex++;
}
void NxDocument::popSnapshot(bool revert) {
    bool canDo = false;
    if((revert) && (snapshotsIndex < snapshots.count()-1)) {
        snapshotsIndex++;
        canDo = true;
    }
    else if ((!revert) && (snapshotsIndex > 0) && (snapshotsIndex == snapshots.count())) {
        pushSnapshot();
        snapshotsIndex--;
        snapshotsIndex--;
        canDo = true;
    }
    else if ((!revert) && (snapshotsIndex > 0)) {
        snapshotsIndex--;
        canDo = true;
    }
    if(canDo) {
        clear();
        NxObjectDispatchProperty::source = ExecuteSourceGui;
        Application::current->executeAsScript(snapshots.at(snapshotsIndex));
    }
}


void NxDocument::open() {
    if(!isLoaded) {
        clear();
        open(true);
        isLoaded = true;
    }
}
bool NxDocument::open(bool configure) {
    //Open the script
    QScriptValue scriptFunctions = scriptEngine.newQObject(this);
    script = scriptEngine.globalObject();

    //Map specials features/keywords/functions
    script.setProperty("mouseX",   mousePos.x());
    script.setProperty("mouseY",   mousePos.y());
    script.setProperty("iannix",   scriptFunctions);
    script.setProperty("nx",       scriptFunctions);

    //GUI to ask the user variables
    variable = new ExtScriptVariableAsk(Application::current->getMainWindow());

    //Open the script file (if its a file)
    if(getScriptFile().exists()) {
        QFile scriptFileContent(getScriptFile().absoluteFilePath());
        if(scriptFileContent.open(QIODevice::ReadOnly | QIODevice::Text)) {
            //Read file
            scriptContent = scriptFileContent.readAll();
            scriptFileContent.close();

            //Load
            if(getScriptFile().suffix().toLower() == "nxscore") {
                QStringList paste = scriptContent.split(COMMAND_END, QString::SkipEmptyParts);
                foreach(const QString & command, paste)
                    Application::current->execute(command, ExecuteSourceGui);
            }
            else {
                QScriptValue scriptReturn = scriptEvaluate(scriptContent, false);

                //Extract function
                if(getScriptFile().suffix().toLower() == "iannix") {
                    scriptMakeWithScript       = script.property("makeWithScript");
                    scriptOnIncomingMessage    = script.property("onIncomingMessage");
                    scriptAskUserForParameters = script.property("askUserForParameters");
                }
                else {
                    scriptOnIncomingMessage    = script.property("onMessage");
                    scriptMakeWithScript       = script.property("onCreate");
                    scriptAskUserForParameters = script.property("onConfigure");
                }
                scriptMadeThroughGUI           = script.property("madeThroughGUI");
                scriptAlterateWithScript       = script.property("alterateWithScript");
                scriptMadeThroughInterfaces    = script.property("madeThroughInterfaces");


                //Extract errors
                QStringList errors = scriptEngine.uncaughtExceptionBacktrace();
                if(scriptReturn.isError())
                    errors << scriptReturn.property("message").toString();
                if(errors.count())  Transport::editor->scriptError(errors, scriptEngine.uncaughtExceptionLineNumber());
                else                Transport::editor->scriptError(QStringList(), -1);


                //Call the "askUserForParameters()" function
                if(configure) {
                    scriptAskUserForParameters.call(QScriptValue(), QScriptValueList());
                    Application::current->pushSnapshot();
                }

                //Ask variables to user and sets the variable in the script
                QList<ExtScriptVariable*> variables = variable->ask();
                if(variable->result()) {
                    foreach(const ExtScriptVariable *variable, variables) {
                        if(variable->isDefFloat())  script.setProperty(variable->getValue(), variable->getDefFloat());
                        else                        script.setProperty(variable->getValue(), variable->getDefStr());
                    }

                    //Call the functions
                    source = ExecuteSourceScript;
                    scriptMakeWithScript       .call(QScriptValue(), QScriptValueList());
                    source = ExecuteSourceGui;
                    scriptMadeThroughGUI       .call(QScriptValue(), QScriptValueList());
                    source = ExecuteSourceNetwork;
                    scriptMadeThroughInterfaces.call(QScriptValue(), QScriptValueList());
                    source = ExecuteSourceScript;
                    scriptAlterateWithScript   .call(QScriptValue(), QScriptValueList());

                    return true;
                }
            }
        }
    }
    return false;
}

bool NxDocument::save() {
    QString scoreContent = "";
    if((!getScriptFile().exists()) || (getScriptFile().suffix().toLower() != "iannix")) {
        //Load IanniX Score template
        QFile scoreTemplateFile(Global::pathApplication.absoluteFilePath() + "/Tools/Score template.iannix");
        if(scoreTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            scoreContent = scoreTemplateFile.readAll();
            scoreTemplateFile.close();
        }
    }
    else {
        //Load IanniX Score
        QFile scoreTemplateFile(getScriptFile().absoluteFilePath());
        if(scoreTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            scoreContent = scoreTemplateFile.readAll();
            scoreTemplateFile.close();
        }
    }

    //Locate functions
    NxObjectDispatchProperty::source = ExecuteSourceGui;
    remplaceInFunction(&scoreContent, "//GUI: NEVER EVER REMOVE THIS LINE\n", Application::current->serialize());
    NxObjectDispatchProperty::source = ExecuteSourceNetwork;
    remplaceInFunction(&scoreContent, "//INTERFACES: NEVER EVER REMOVE THIS LINE\n", Application::current->serialize());
    remplaceInFunction(&scoreContent, " *\t//APP VERSION: NEVER EVER REMOVE THIS LINE\n", QString(" *\tMade with IanniX %1").arg(QCoreApplication::applicationVersion()));

    qDebug("%s", qPrintable(scoreContent));
    qDebug("SAVED TO %s", qPrintable(getScriptFile().absoluteFilePath()));

    QFile scriptFileContent(getScriptFile().absoluteFilePath());
    if(!scriptFileContent.exists()) {
        if(scriptFileContent.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug("%s", qPrintable(scoreContent));
            scriptFileContent.write(scoreContent.toLatin1());
            scriptFileContent.close();
            return true;
        }
    }
    return false;
}

void NxDocument::remplaceInFunction(QString *content, const QString &delimiter, const QString &data) {
    qint32 startReplace = content->indexOf(delimiter, 0) + delimiter.length();
    qint32 endReplace   = content->indexOf(delimiter, startReplace);
    if((startReplace < endReplace) && (startReplace >= 0) && (endReplace >= 0))
        *content = content->left(startReplace) + data + "\n" + content->mid(endReplace);
}




const QString NxDocument::loadLibrary() {
    QString scriptContent = "";

    QFileInfoList scriptDirs = QDir(Global::pathApplication.absoluteFilePath() + "/Tools/").entryInfoList(QStringList() << "*.js", QDir::Files | QDir::NoDotAndDotDot);
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

QScriptValue NxDocument::scriptEvaluate(const QString &scriptContent, bool _createNewObjectIfExists) {
    createNewObjectIfExists = _createNewObjectIfExists;
    return scriptEngine.evaluate(scriptContent + loadLibrary());
}

void NxDocument::askFileOpen() {
    qDebug("==> OPEN %s", qPrintable(getScriptFile().absoluteFilePath()));
    restoreDefaults();
    open();
}
void NxDocument::askFileSave() {
    qDebug("==> SAVE %s", qPrintable(getScriptFile().absoluteFilePath()));
    save();
}
void NxDocument::askFileReload() {
    qDebug("==> RELOAD %s", qPrintable(getScriptFile().absoluteFilePath()));
    open();
}
void NxDocument::askFileClose() {
    clear();
    qDebug("==> CLOSE %s", qPrintable(getScriptFile().absoluteFilePath()));
}

void NxDocument::restoreDefaults() {
    Global::defaultColors.insert("darktheme_empty"                  , QColor(  0,   0,   0, 255));
    Global::defaultColors.insert("darktheme_background"             , QColor(255, 255, 255, 255));
    Global::defaultColors.insert("darktheme_grid"                   , QColor(255, 255, 255,  43));
    Global::defaultColors.insert("darktheme_axis"                   , QColor(255, 255, 255,  28));
    Global::defaultColors.insert("darktheme_gridSnap"               , QColor( 90,  25,  15, 255));
    Global::defaultColors.insert("darktheme_axisSnap"               , QColor( 90,  25,  15, 255));
    Global::defaultColors.insert("darktheme_selection"              , QColor(255, 255, 255,  40));
    Global::defaultColors.insert("darktheme_object_selection"       , QColor(255, 240,  35, 255));
    Global::defaultColors.insert("darktheme_object_hover"           , QColor( 35, 255, 165, 255));
    Global::defaultColors.insert("darktheme_cursor_active"          , QColor(255,  80,  30, 255));
    Global::defaultColors.insert("darktheme_cursor_inactive"        , QColor(255, 255, 255,  92));
    Global::defaultColors.insert("darktheme_trigger_active"         , QColor(  0, 185, 255, 255));
    Global::defaultColors.insert("darktheme_trigger_inactive"       , QColor(255, 255, 255, 92));
    Global::defaultColors.insert("darktheme_curve_active"           , QColor(255, 255, 255, 175));
    Global::defaultColors.insert("darktheme_curve_inactive"         , QColor(255, 255, 255,  92));
    Global::defaultColors.insert("darktheme_simple_curve_active"    , QColor(115, 159,  89, 255));
    Global::defaultColors.insert("darktheme_simple_curve_inactive"  , QColor(115, 159,  89, 255));
    Global::defaultColors.insert("lighttheme_empty"                 , QColor(242, 241, 237, 255));
    Global::defaultColors.insert("lighttheme_background"            , QColor(255, 255, 255, 255));
    Global::defaultColors.insert("lighttheme_grid"                  , QColor(  0,   0,   0,  20));
    Global::defaultColors.insert("lighttheme_axis"                  , QColor(  0,   0,   0,  13));
    Global::defaultColors.insert("lighttheme_gridSnap"              , QColor(255, 190, 190, 255));
    Global::defaultColors.insert("lighttheme_axisSnap"              , QColor(255, 190, 190, 255));
    Global::defaultColors.insert("lighttheme_selection"             , QColor(  0,   0,   0,  40));
    Global::defaultColors.insert("lighttheme_object_selection"      , QColor(  0,  15, 220, 255));
    Global::defaultColors.insert("lighttheme_object_hover"          , QColor(220,   0,  90, 255));
    Global::defaultColors.insert("lighttheme_cursor_active"         , QColor(255,  80,  30, 255));
    Global::defaultColors.insert("lighttheme_cursor_inactive"       , QColor(  0,   0,   0,  92));
    Global::defaultColors.insert("lighttheme_trigger_active"        , QColor(  0, 185, 255, 255));
    Global::defaultColors.insert("lighttheme_trigger_inactive"      , QColor(  0,   0,   0,  92));
    Global::defaultColors.insert("lighttheme_curve_active"          , QColor(  0,   0,   0, 175));
    Global::defaultColors.insert("lighttheme_curve_inactive"        , QColor(  0,   0,   0,  92));
    Global::defaultColors.insert("lighttheme_simple_curve_active"   , QColor(115, 159,  89, 255));
    Global::defaultColors.insert("lighttheme_simple_curve_inactive" , QColor(115, 159,  89, 255));
    Global::colors->clear();
    QMapIterator<QString, QColor> colorIterator(Global::defaultColors);
    while (colorIterator.hasNext()) {
        colorIterator.next();
        Global::colors->insert(colorIterator.key(), colorIterator.value());
    }

    Application::render->loadTexture(new UiRenderTexture("background",       QFileInfo("filename"), NxRect(-4, 4, 8, -8)));
    Application::render->loadTexture(new UiRenderTexture("trigger_active",   QFileInfo("filename"), NxRect(-1, 1, 2, -2)));
    Application::render->loadTexture(new UiRenderTexture("trigger_inactive", QFileInfo("filename"), NxRect(-1, 1, 2, -2)));
}
