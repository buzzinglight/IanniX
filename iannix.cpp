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

#include "iannix.h"

IanniX::IanniX(const QString &_projectToLoad, QObject *parent) :
    ApplicationCurrent(parent) {
    projectToLoad = _projectToLoad;
    projectIsLoaded = false;
    iconAppPlay  = QIcon(":icons/res_appicon_pause.png");
    iconAppPause = QIcon(":icons/res_appicon_play.png");
    NxObject::widgetIconActiveOff = QIcon(":gui/res_icon_check_active_off.png");
    NxObject::widgetIconActiveOn  = QIcon(":gui/res_icon_check_active_on.png");
    NxObject::widgetIconSoloOff   = QIcon(":gui/res_icon_check_solo_off.png");
    NxObject::widgetIconSoloOn    = QIcon(":gui/res_icon_check_solo_on.png");

    Global::textures = new UiTextureItems();
    Global::colors   = new UiColorItems();

    Global::messageTemplates << tr("osc://ip_out:port_out/trigger trigger_id trigger_group_id trigger_value_x trigger_value_y trigger_value_z trigger_xPos trigger_yPos trigger_zPos cursor_id cursor_group_id - Default OSC message for triggers");
    Global::messageTemplates << tr("osc://ip_out:port_out/cursor cursor_id cursor_group_id cursor_value_x cursor_value_y cursor_value_z cursor_xPos cursor_yPos cursor_zPos - Default OSC message for cursors");
    Global::messageTemplates << tr("osc://ip_out:port_out/curve collision_curve_id collision_curve_group_id collision_value_x collision_value_y 0 collision_xPos collision_yPos 0 - Default OSC message for classical playhead");
    Global::messageTemplates << tr("midi://midi_out/notef 1 trigger_value_y trigger_value_x 3 - Default MIDI message for triggers");
    Global::messageTemplates << tr("midi://midi_out/note 1 69 127 5 - Play a MIDI note #69 (A - 440Hz) during 5 seconds on channel #1 with maximum velocity");
    Global::messageTemplates << tr("midi://midi_out/ccf 1 0 cursor_value_y - Send a MIDI control change on controler #0 on channel #1 depending on cursor position (as float value between 0 and 1)");
    Global::messageTemplates << tr("direct:// goto 2 - Make score go back to timecode 000:02.000");
    Global::messageTemplates << tr("direct:// setSpeedF 10 1 - Make the cursor #10 start (please set its Master Speed to 0 before)");

    //Updates
    forceUpdate = false;

    //Default values
    currentDocument = 0;
    iniSettings  = 0;
    updateManager   = 0;
    isGroupSoloActive  = false;
    isObjectSoloActive = false;
    waitingForMessageValue = false;
    scriptDir = QDir::current();

    //Create basic workspace
    QDir().mkpath(Global::pathDocuments.absoluteFilePath() + "/");

    //View
    view      = new UiView(0);
    render    = view->getRender();
    inspector = view->getInspector();
    inspector->setRender(render);
    transport = view->getTransport();
    connect(view,   SIGNAL(forceGoto(qreal,bool)),                  SLOT(forceGoto(qreal,bool)));
    connect(view,   SIGNAL(actionRouteReloadScript()),              SLOT(actionReloadScript()));
    connect(view,   SIGNAL(actionRouteCloseEvent(QCloseEvent*)),    SLOT(actionCloseEvent(QCloseEvent*)));
    connect(render, SIGNAL(actionRoutePaste()),                     SLOT(actionPaste()));
    connect(render, SIGNAL(actionRouteCopy()),                      SLOT(actionCopy()));
    //Imports
    connect(view,   SIGNAL(actionRouteImportSVG(QString)),          SLOT(actionImportSVG(QString)));
    connect(render, SIGNAL(actionRouteImportSVG(QString)),          SLOT(actionImportSVG(QString)));
    connect(render, SIGNAL(actionRouteImportBackground(QString)),   SLOT(actionImportBackground(QString)));
    connect(view,   SIGNAL(actionRouteImportBackground(QString)),   SLOT(actionImportBackground(QString)));
    connect(render, SIGNAL(actionRouteImportText(QString,QString)), SLOT(actionImportText(QString,QString)));
    connect(view,   SIGNAL(actionRouteImportText(QString,QString)), SLOT(actionImportText(QString,QString)));

    //Transport
    connect(transport, SIGNAL(forceOpenGLtimer(qreal)),             SLOT(forceOpenGLTimer(qreal)));
    connect(transport, SIGNAL(forceSchedulerTimer(qreal)),          SLOT(forceSchedulerTimer(qreal)));
    connect(Transport::editor, SIGNAL(askSave()),    SLOT(actionSave()));
    connect(Transport::editor, SIGNAL(askSave()),    SLOT(actionReloadScript()));
    connect(Transport::editor, SIGNAL(askRefresh()), SLOT(actionRefresh()));

    //Inspector
    connect(inspector, SIGNAL(actionRouteCC(QTreeWidgetItem*,int)), SLOT(actionCC(QTreeWidgetItem*,int)));
    connect(inspector, SIGNAL(actionUnmuteGroups()),                SLOT(actionUnmuteGroups()));
    connect(inspector, SIGNAL(actionUnmuteObjects()),               SLOT(actionUnmuteObjects()));
    connect(inspector, SIGNAL(actionUnsoloGroups()),                SLOT(actionUnsoloGroups()));
    connect(inspector, SIGNAL(actionUnsoloObjects()),               SLOT(actionUnsoloObjects()));
    connect(inspector->getFileWidget(), SIGNAL(currentDocumentChanged(UiSyncItem*)), SLOT(currentDocumentChanged(UiSyncItem*)));

    //Render
    connect(render, SIGNAL(mousePosChanged(NxPoint)), inspector,    SLOT(setMousePos(NxPoint)));
    connect(render, SIGNAL(mouseZoomChanged(qreal)),  inspector,    SLOT(setMouseZoom(qreal)));
    connect(render, SIGNAL(mouseRotationChanged(NxPoint)),inspector,SLOT(setRotationAngles(NxPoint)));
    connect(render, SIGNAL(selectionChanged()),       inspector,    SLOT(askRefresh()));
    connect(render, SIGNAL(escFullscreen()),          view,         SLOT(escFullscreen()));
    connect(render, SIGNAL(actionRouteNew()),                       SLOT(actionNew()));
    connect(render, SIGNAL(actionRouteOpen()),                      SLOT(actionOpen()));
    connect(render, SIGNAL(actionRouteSave()),                      SLOT(actionSave()));
    connect(render, SIGNAL(actionRouteSave_as()),                   SLOT(actionSave_as()));
    connect(render, SIGNAL(actionRouteUndo()),                      SLOT(actionUndo()));
    connect(render, SIGNAL(actionRouteRedo()),                      SLOT(actionRedo()));
    connect(view,   SIGNAL(arrangeObjects(quint16)),  render,       SLOT(arrangeObjects(quint16)));
    render->setZoom();
    render->rotateTo(NxPoint(0, 0, 0));
    inspector->setMousePos(NxPoint(0, 0));

    //Interfaces
    MessageManager::addNetworkInterface(MessagesTypeDirect, new InterfaceDirect());
    MessageManager::addNetworkInterface(MessagesTypeOsc,    new InterfaceOsc   ());
    MessageManager::addNetworkInterface(MessagesTypeUdp,    new InterfaceUdp   ());
    MessageManager::addNetworkInterface(MessagesTypeTcp,    new InterfaceTcp   ());
    MessageManager::addNetworkInterface(MessagesTypeHttp,   new InterfaceHttp  ());
    MessageManager::addNetworkInterface(MessagesTypeSerial, new InterfaceSerial());
    MessageManager::addNetworkInterface(MessagesTypeMidi,   new InterfaceMidi  ());
#ifdef SYPHON_INSTALLED
    MessageManager::addNetworkInterface(MessagesTypeSyphon, render->interfaceSyphon);
#endif
    inspector->addInterfaces();

    //Message script engine
    QScriptValue messageScript = messageScriptEngine.globalObject();
    messageScript = messageScriptEngine.evaluate(NxDocument::loadLibrary());

    //Special objects
    Application   ::setInterfaces(this, render);
    MessageManager::setInterfaces(this, &messageScriptEngine, 0, transport->getLogMini());
    MessageManager::transportObject = new NxTrigger(this, 0);
    MessageManager::syncObject      = new NxTrigger(this, 0);

    //Other experimental components
#ifdef WACOM_INSTALLED
    wacom = new ExtWacomManager();
#endif
#ifdef KINECT_INSTALLED
    kinect = new ExtKinectManager();
#endif

    //Special settings
    UiOptions::add(&Global::defaultMessage,          "defaultMessage");
    UiOptions::add(&Global::defaultMessageCursor,    "defaultMessageCursor");
    UiOptions::add(&Global::defaultMessageCurve,     "defaultMessageCurve");
    UiOptions::add(&Global::defaultMessageSync,      "defaultMessageSync");
    UiOptions::add(&Global::defaultMessageTransport, "defaultMessageTransport");
    UiOptions::add(&Global::defaultMessageTrigger,   "defaultMessageTrigger");
    NxDocument::restoreDefaults();


    //Global settings creation if needed
    globalSettings = new QSettings();
    if((globalSettings) && (!globalSettings->childKeys().contains("id"))) {
        qsrand(QDateTime::currentDateTime().toTime_t());
        updateAnonymousId = QString::number(qrand());
        globalSettings->setValue("id", updateAnonymousId);
        globalSettings->setValue("updatePeriod", 1);
        globalSettings->setValue("lastUpdate",   QDateTime(QDate(2000, 01, 01)));
    }
    //Local settings creation if needed
    QString settingsFilename = Global::pathDocuments.absoluteFilePath() + "/Settings.ini";
    if(!QFile(settingsFilename).exists()) {
        iniSettings = new QSettings(settingsFilename, QSettings::IniFormat);

        //UiOptions
        foreach(UiOption *option, UiOptions::options)
            iniSettings->setValue(option->settingName, option->variant());

        //Messages
        int messageTemplatesCount = iniSettings->beginReadArray("Messages Templates");
        if(messageTemplatesCount > 0) {
            Global::messageTemplates.clear();
            for(quint16 i = 0 ; i < messageTemplatesCount ; i++) {
                iniSettings->setArrayIndex(i);
                Global::messageTemplates << iniSettings->value("messageTemplates").toString();
            }
        }
        iniSettings->endArray();

        //Colors
        iniSettings->beginGroup("Colors");
        QMapIterator<QString, QColor> colorIterator(*Global::colors);
        while (colorIterator.hasNext()) {
            colorIterator.next();
            iniSettings->setValue(colorIterator.key(), colorIterator.value());
        }
        iniSettings->endGroup();

        delete iniSettings;
    }


    //Read settings
    if(QFile(settingsFilename).exists()) {
        iniSettings = new QSettings(settingsFilename, QSettings::IniFormat);

        QString iniAppVersion = iniSettings->value("appVersion").toString();
        if(iniAppVersion == QApplication::applicationVersion()) {
            //UiOptions
            foreach(UiOption *option, UiOptions::options)
                if(iniSettings->childKeys().contains(option->settingName))
                    option->setVariant(iniSettings->value(option->settingName));
        }

        //Messages
        Global::messageTemplates.clear();
        int count = iniSettings->beginReadArray("Messages Templates");
        for(quint16 i = 0 ; i < count ; i++) {
            iniSettings->setArrayIndex(i);
            Global::messageTemplates.append(iniSettings->value("messageTemplates").toString());
        }
        iniSettings->endArray();

        //Colors
        iniSettings->beginGroup("Colors");
        QStringList settingsKeys = iniSettings->childKeys();
        foreach(const QString &settingsKey, settingsKeys)
            Global::colors->insert(settingsKey, iniSettings->value(settingsKey).value<QColor>());
        iniSettings->endGroup();
    }
    Global::colors->update();

    //Update management
    if((globalSettings) && (globalSettings->childKeys().contains("id"))) {
        QDateTime updateLastDate  = globalSettings->value("lastUpdate")  .toDateTime();
        quint16   updatePeriod    = globalSettings->value("updatePeriod").toUInt();
        updateAnonymousId         = globalSettings->value("id")          .toString();
        qDebug("Last update : %s (should update each %d day(s))", qPrintable(updateLastDate.toString("dd/MM/yyyy hh:mm:ss")), updatePeriod);
        if((updateLastDate.daysTo(QDateTime::currentDateTime()) >= updatePeriod) || (forceUpdate))
            checkForUpdates();
    }

    //Apply specials settings
    ((NxTrigger*)MessageManager::transportObject)->setMessagePatterns("1," + Global::defaultMessageTransport);
    ((NxTrigger*)MessageManager::syncObject)     ->setMessagePatterns("1," + Global::defaultMessageSync);

    //Scheduler
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    timer->setInterval(5);
    timer->start();
    forceGoto(0);

    //Show
    view->show();
}

void IanniX::readyToStart() {
    if(!hasStarted) {
        hasStarted = true;
        qDebug("Ready to start!");

        //Projet par défault
        loadProject(projectToLoad);
        forceGoto(0);

        timerTime = startTimer(50);
        timerPerf = startTimer(500);
        render->startRenderTimer();

        Application::splash->close();
    }
}




void IanniX::actionImportSVG(const QString &filename) {
    qreal scale = 0.01;
    QDomDocument xmlDoc;
    QFile svgFile(filename);
    if(svgFile.open(QFile::ReadOnly)) {
        Application::render->selectionClear(true);
        xmlDoc.setContent(svgFile.readAll());
        actionImportSVG(xmlDoc.documentElement(), scale);
        svgFile.close();
        inspector->showSpaceTab();
    }
}
void IanniX::actionImportSVG(const QDomElement &xmlElement, qreal scale) {
    QDomNode xmlNode = xmlElement.firstChild();
    while(!xmlNode.isNull()) {
        QDomElement xmlData = xmlNode.toElement();
        if((!xmlData.isNull()) && (xmlData.tagName() == "path")) {
            quint16 id = execute(QString(COMMAND_ADD) + " curve auto", ExecuteSourceGui).toUInt();
            execute(QString(COMMAND_CURVE_PATH) + " " + QString::number(id) + " " + QString::number(scale) + " " + xmlData.attribute("d"), ExecuteSourceGui);
            render->selectionAdd(currentDocument->getObject(id));
        }
        else if((!xmlData.isNull()) && (xmlData.tagName() == "polyline")) {
            quint16 id = execute(QString(COMMAND_ADD) + " curve auto", ExecuteSourceGui).toUInt();;
            execute(QString(COMMAND_CURVE_LINES) + " " + QString::number(id) + " " + QString::number(scale) + " " + xmlData.attribute("points"), ExecuteSourceGui);
            render->selectionAdd(currentDocument->getObject(id));
        }
        actionImportSVG(xmlData, scale);
        xmlNode = xmlNode.nextSibling();
    }
}
void IanniX::actionImportBackground(const QString &filename) {
    QPixmap pixmap(filename);
    if(!pixmap.isNull()) {
        qreal scale = qMin(8 / (qreal)pixmap.width(), 8 / (qreal)pixmap.height());
        execute(QString(COMMAND_TEXTURE) + " background " + QString("%1 %2 %3 %4").arg(-scale * pixmap.width() / 2).arg(scale * pixmap.height() / 2).arg(scale * pixmap.width() / 2).arg(-scale * pixmap.height() / 2) + " " + filename, ExecuteSourceGui);
        inspector->showRessourcesTab("background");
    }
}

void IanniX::actionImportText(const QString &font, const QString &text) {
    qreal scale = 0.1;
    bool ok = false;

    QString fontReal = font;
    if(fontReal.isEmpty()) {
        ok = false;
        QFont fontFont = QFontDialog::getFont(&ok);
        if(ok)
            fontReal = fontFont.family();
        else
            return;
    }

    fontReal = fontReal.replace(" ", "_");
    Application::render->selectionClear(true);
    quint16 id = execute(QString(COMMAND_ADD) + " curve auto", ExecuteSourceGui).toUInt();
    execute(QString(COMMAND_CURVE_TXT) + " " + QString::number(id) + " " + QString::number(scale) + " " + fontReal + " " + text, ExecuteSourceGui);
    render->selectionAdd(currentDocument->getObject(id));
    inspector->showSpaceTab();
}




void IanniX::setScheduler(SchedulerActivity _schedulerActivity) {
    MessageManager::messagesCache.clear();
    schedulerActivity = _schedulerActivity;
    if(schedulerActivity != SchedulerOff) {
        Transport::timerOk = true;
        Transport::renderMeasureAbsoluteValOld = 0;
        Transport::renderMeasureAbsolute.start();
    }
    else
        Transport::timerOk = false;
    if(view->isVisible()) {
        if(Transport::timerOk)  QApplication::setWindowIcon(iconAppPause);
        else                    QApplication::setWindowIcon(iconAppPlay);
    }
}

const QString IanniX::serialize() const {
    return transport->serialize() + currentDocument->serialize();
}

void IanniX::timerEvent(QTimerEvent *event) {
    if(transport) {
        if(event->timerId() == timerTime)
            transport->refreshTime();
        else if(event->timerId() == timerPerf)
            transport->refreshPerformances();
    }
}


void IanniX::timerTick() {
    timerTick(false);
}
void IanniX::timerTick(bool force) {
    qreal renderMeasureAbsoluteVal = Transport::renderMeasureAbsolute.elapsed() / 1000.0F;
    qreal delta = renderMeasureAbsoluteVal - Transport::renderMeasureAbsoluteValOld;
    Transport::renderMeasureAbsoluteValOld = renderMeasureAbsoluteVal;

    //Parse MIDI
    if(!force)
        MessageManager::networkManualParsing();

    //Tick !
    if((force) || (Transport::timerOk))
        timerTick(delta);
}

void IanniX::timerTick(qreal delta) {
    if(Transport::forceTimeLocal) {
        delta = 0;
        if(schedulerActivity == SchedulerOneShot)
            setScheduler(SchedulerOff);
    }
    Transport::timeLocal += delta * Transport::scoreSpeed;
    if(Transport::timeLocal < 0) {
        Transport::forceTimeLocal = true;
        Transport::timeLocal = 0;
        return;
    }
    Transport::perfSchedulerRefreshTime += delta;
    Transport::perfSchedulerCounterTime++;

    //Open a bundle if necessary
    MessageManager::networkBundle(true);

    //Browse documents
    //QHashIterator<QString, NxDocument*> documentIterator(documents);
    /*while (documentIterator.hasNext())*/ {
        //documentIterator.next();
        NxDocument *document = currentDocument; //documentIterator.value();

        //Browse groups
        if(document) {
            foreach(const NxGroup *group, document->groups) {
                //Browse active/inactive objects
                for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {

                    //Browse cursors
                    foreach(const NxObject *objectCursor, group->objects[activityIterator][ObjectsTypeCursor]) {
                        NxCursor *cursor = (NxCursor*)objectCursor;

                        //Cursor reset
                        if(Transport::forceTimeLocal) {
                            cursor->setTimeLocal(Transport::timeLocal);
                            cursor->setMessageId(0);
                        }

                        //Set time for a cursor
                        cursor->setTime(delta * Transport::scoreSpeed);

                        //Is cursor active ?
                        if((!Transport::forceTimeLocal) && (cursor->getActive()) && (((!isGroupSoloActive) && (group->isNotMuted())) || ((isGroupSoloActive) && (group->isSolo()))) && (((!isObjectSoloActive) && (cursor->isNotMuted())) || ((isObjectSoloActive) && (cursor->isSolo())))) {
                            timerTrig(cursor);
                        }
                    }
                }
            }
        }
    }

    //Close the bundle if necessary
    MessageManager::networkBundle(false);

    if(Transport::forceTimeLocal)
        Transport::forceTimeLocal = false;
}

void IanniX::timerTrig(void *object, bool force) {
    NxCursor *cursor = (NxCursor*)object;

    //Messages
    if((!Global::allowPlaySelected) || (!render->isSelection()) || ((Global::allowPlaySelected) && (cursor->getSelected())))
        cursor->trig(force);

    //Browse groups
    foreach(const NxGroup *group, currentDocument->groups) {
        //Browse active triggers
        foreach(const NxObject *objectTrigger, group->objects[ObjectsActivityActive][ObjectsTypeTrigger]) {
            NxTrigger *trigger = (NxTrigger*)objectTrigger;

            //Check the collision
            if((cursor->contains(trigger)) && (((!isObjectSoloActive) && (trigger->isNotMuted())) || ((isObjectSoloActive) && (trigger->isSolo()))) && ((!Global::allowPlaySelected) || (!render->isSelection()) || ((Global::allowPlaySelected) && (trigger->getSelected()))))
                trigger->trig(cursor);
        }

        //Browse active curbes
        if(cursor->getPerformCollision()) {
            foreach(const NxObject *objectCurve, group->objects[ObjectsActivityActive][ObjectsTypeCurve]) {
                //Check the collision
                if((!Global::allowPlaySelected) || (!render->isSelection()) || ((Global::allowPlaySelected) && (objectCurve->getSelected())))
                    cursor->trig((NxCurve*)objectCurve);
            }
        }
    }
}



void IanniX::checkForUpdates() {
    updateManager = new QNetworkAccessManager(this);
    connect(updateManager, SIGNAL(finished(QNetworkReply*)), SLOT(checkForUpdatesFinished(QNetworkReply*)));
    QString url = "http://www.iannix.org/download/updates.php?id=" + updateAnonymousId + "&package=" + (QCoreApplication::applicationName() + "__" + QCoreApplication::applicationVersion()).toLower().replace(" ", "_").replace(".", "_");
    qDebug("Checking for updates %s", qPrintable(url));
    updateManager->get(QNetworkRequest(QUrl(url, QUrl::TolerantMode)));
}
void IanniX::checkForUpdatesFinished(QNetworkReply *reply) {
    if(reply->error() != QNetworkReply::NoError)
        qDebug("Network error. %s", qPrintable(reply->errorString()));
    else {
        if(globalSettings)
            globalSettings->setValue("lastUpdate", QDateTime::currentDateTime());
        QString info = reply->readAll().trimmed();
        if((info.length() > 0) || (forceUpdate)) {
            int rep = (new UiMessageBox())->display(tr("IanniX Update Center"), tr("A new version of IanniX is available"), info, tr("Would you like to update IanniX with the new version ?"), QPixmap(":/infos/res_info_update.png"), QDialogButtonBox::Yes | QDialogButtonBox::No);
            if(rep)
                QDesktopServices::openUrl(QUrl("http://www.iannix.org/", QUrl::TolerantMode));
        }
    }
}



void IanniX::actionPlayPause() {
    if(Transport::timerOk) {
        setScheduler(SchedulerOff);
        MessageManager::networkSynchro(false);
    }
    else {
        setScheduler(SchedulerOn);
        MessageManager::networkSynchro(true);
    }
}


void IanniX::forceGoto(qreal gotoTime, bool) {
    if(gotoTime == 0) {
        Transport::forceTimeLocal = true;
        Transport::timeLocal = 0;
        setScheduler(SchedulerOneShot);
    }
    else {
        Transport::timeLocal      = gotoTime;
        Transport::forceTimeLocal = true;
        if(schedulerActivity == SchedulerOff)
            setScheduler(SchedulerOneShot);
    }
    MessageManager::networkSynchro(false);
}
void IanniX::forceSchedulerTimer(qreal val) {
    timer->setInterval(val);
}
void IanniX::forceOpenGLTimer(qreal val) {
    render->setInterval(1000.0F/(qreal)val);
}



void IanniX::actionCC(QTreeWidgetItem *item, int col) {
    if((item) && (col)) {
        if(item->text(0) == tr("GROUP")) ((NxGroup*)item) ->widgetClick(col);
        else                             ((NxObject*)item)->widgetClick(col);
    }
    if(col == 0) {
        QPair< QList<NxGroup*>, UiRenderSelection > elements = inspector->getSelectedCCObject();
        NxPoint center;
        quint16 centerCounter = 0;

        Application::render->selectionClear(true);
        foreach(NxObject* object, elements.second) {
            render->selectionAdd(object);
            center += object->getPos();
            centerCounter++;
        }
        foreach(const NxGroup* group, elements.first) {
            //Browse active/inactive objects
            for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
                //Browse all types of objects
                for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                    //Browse objects
                    foreach(NxObject *object, group->objects[activityIterator][typeIterator]) {
                        render->selectionAdd(object);
                        center += object->getPos();
                        centerCounter++;
                    }
                }
            }
        }
        center /= centerCounter;
        //render->centerOn(center);
    }

    //Is solo active ?
    isGroupSoloActive  = false;
    isObjectSoloActive = false;
    if(currentDocument) {
        //Is solo active ?
        foreach(const NxGroup *group, currentDocument->groups)
            if(group->isSolo()) {
                isGroupSoloActive = true;
                break;
            }
        foreach(const NxGroup* group, currentDocument->groups) {
            //Browse active/inactive objects
            for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
                //Browse all types of objects
                for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                    //Browse objects
                    foreach(const NxObject *object, group->objects[activityIterator][typeIterator]) {
                        if(object->isSolo()) {
                            isObjectSoloActive = true;
                            return;
                        }
                    }
                }
            }
        }
    }
}

void IanniX::actionNew() {

}

void IanniX::currentDocumentChanged(UiSyncItem *item) {
    if(currentDocument)
        delete currentDocument;
    currentDocument = new NxDocument(this, (UiFileItem*)item);
    render->setDocument(currentDocument);
    currentDocument->askFileOpen();
}
void IanniX::actionOpen() {
    QString filename = QFileDialog::getOpenFileName(0, tr("Open IanniX Score"), Global::pathDocuments.absoluteFilePath() + "/");
    if(!filename.isEmpty())
        loadProject(filename);
}
void IanniX::actionSave() {
    inspector->getFileWidget()->askSave();
}
void IanniX::actionSave_as() {
    inspector->getFileWidget()->askSave(true);
}
void IanniX::actionRefresh() {
    currentDocument->updateCode(false);
}
void IanniX::loadProject(const QString & _projectFile) {
    QFileInfo projectFile(_projectFile);
    if(projectFile.isDir())
        UiFileItem::syncWith(QFileInfoList() << QFileInfo(projectFile.absoluteFilePath() + "/"), inspector->getFileWidget()->getTree());
    else if(projectFile.isFile()) {
        UiFileItem::syncWith(QFileInfoList() << QFileInfo(projectFile.absolutePath() + "/"), inspector->getFileWidget()->getTree());
        inspector->getFileWidget()->askImport(QStringList() << projectFile.absoluteFilePath());
        inspector->getFileWidget()->askOpen();
    }
    else
        inspector->getFileWidget()->askNew();
    projectIsLoaded = true;
}






NxGroup* IanniX::addGroup(const QString & groupId) {
    if(currentDocument->groups.contains(groupId))
        return currentDocument->groups.value(groupId);
    else {
        NxGroup *group = new NxGroup(this, inspector->getObjectRootItem());
        group->setId(groupId);
        currentDocument->groups.insert(groupId, group);
        currentDocument->setCurrentGroup(group);
        return group;
    }
}

void IanniX::setObjectActivity(void *_object, quint8 activeOld) {
    if(!currentDocument)
        return;

    //Extract object
    NxObject *object = (NxObject*)_object;
    NxGroup *group = addGroup(object->getGroupId());

    //Move object
    group->objects[activeOld]          [object->getType()].remove(object->getId());
    group->objects[object->getActive()][object->getType()].insert(object->getId(), object);
}
void IanniX::setObjectGroupId(void *_object, const QString & groupIdOld) {
    if(!currentDocument)
        return;

    //Extract object
    NxObject *object = (NxObject*)_object;
    NxGroup *group = addGroup(object->getGroupId());

    //Move object
    group->objects[object->getActive()][object->getType()].insert(object->getId(), object);
    if(currentDocument->groups.contains(groupIdOld))
        currentDocument->groups[groupIdOld]->objects[object->getActive()][object->getType()].remove(object->getId());

    //Remove a group if empty
    /*
    if(currentDocument->groups.value(groupIdOld)->getCount() == 0) {
        NxGroup *group = currentDocument->groups[object->getGroupId()];
        currentDocument->groups.remove(groupIdOld);
        delete group;
    }
    */
}
void IanniX::setObjectId(void *_object, quint16 idOld) {
    //Extract object
    NxObject *object = (NxObject*)_object;
    NxGroup *group = addGroup(object->getGroupId());

    //Move object
    group->objects[object->getActive()][object->getType()].insert(object->getId(), object);
    group->objects[object->getActive()][object->getType()].remove(idOld);
    currentDocument->objects.insert(object->getId(), object);
    currentDocument->objects.remove(idOld);
}




quint16 IanniX::getCount(qint8 objectType) {
    quint16 count = 0;
    if(currentDocument) {
        if(objectType == -2)
            return currentDocument->groups.count();
        else
            foreach(NxGroup *group, currentDocument->groups)
                count += group->getCount(objectType);
    }
    return count;
}
void IanniX::removeObject(NxObject *object) {
    if(object) {
        if(render)
            render->flagIsRemoving();

        //Remove the object
        currentDocument->groups[object->getGroupId()]->objects[object->getActive()][object->getType()].remove(object->getId());
        currentDocument->objects.remove(object->getId());

        //Clear selection
        inspector->clearCCselections();
        if(currentDocument->getCurrentObject() == object)
            currentDocument->setCurrentObject(0);
        Application::render->selectionClear(true);

        if(object->getType() == ObjectsTypeCurve) {
            NxCurve *curve = (NxCurve*)object;
            QStringList commands;
            foreach(const NxObject *object, curve->getCursors())
                commands << QString(COMMAND_REMOVE) + " " + QString::number(object->getId()) + COMMAND_END;
            foreach(const QString & command, commands)
                execute(command, ExecuteSourceSystem);
        }
        else if(object->getType() == ObjectsTypeCursor) {
            NxCurve *curve = ((NxCursor*)object)->getCurve();
            if(curve)
                curve->removeCursor(object);
        }

        //Remove groups
        if((currentDocument->groups.contains(object->getGroupId())) && (currentDocument->groups.value(object->getGroupId())->getCount() == 0)) {
            NxGroup *group = currentDocument->groups[object->getGroupId()];
            currentDocument->groups.remove(object->getGroupId());
            delete group;
        }
        delete object;

        if(render)
            render->flagIsRemoving(false);
    }
}


const QVariant IanniX::execute(const MessageIncomming &command, bool createNewObjectIfExists, bool needOutput) {
    if(waitingForMessageValue) {
        waitingForMessageValue = false;
        waitForMessageValue = command.getVerboseMessage(true);
        emit(waitForMessageArrived());
    }
    return execute(command.command, ExecuteSourceNetwork, createNewObjectIfExists, needOutput);
}
const QVariant IanniX::execute(const QString &command, ExecuteSource source, bool createNewObjectIfExists, bool needOutput) {
    //qDebug(">> %s", qPrintable(command));
    if(((source == ExecuteSourceGui) || (source == ExecuteSourceInformative)) && (view->help))
        view->help->messageHelp(command);
    if(source == ExecuteSourceInformative)
        return QVariant();

    NxObjectDispatchProperty::source = source;

    QStringList argv = command.split(" ", QString::SkipEmptyParts);
    quint16 argc = argv.count();
    if(argc > 0) {
        QString commande = argv.at(0).toLower();
        if((argc > 2) && (commande == COMMAND_ADD)) {
            bool ok = false;
            qint16 id = argv.at(2).toUInt(&ok);
            NxObject *parentObject = 0;
            if(ok) {
                parentObject = currentDocument->getObject(id);
                if(parentObject) {
                    if(createNewObjectIfExists) {
                        id = currentDocument->nextAvailableId();
                    }
                    else {
                        id = parentObject->getId();
                        removeObject(parentObject);
                        parentObject = 0;
                    }
                }
            }
            else
                id = currentDocument->nextAvailableId();

            NxObject *object = 0;
            QString type = argv.at(1).toLower();
            if(type == "curve")         object = new NxCurve(this,   inspector->getObjectRootItem());
            else if(type == "cursor")   object = new NxCursor(this,  inspector->getObjectRootItem());
            else                        object = new NxTrigger(this, inspector->getObjectRootItem());

            if(object) {
                object->setInitialId(id);
                setObjectGroupId(object, "");
                object->dispatchProperty(COMMAND_ID, id);
                setObjectActivity(object, ObjectsActivityInactive);
                object->dispatchProperty(COMMAND_POS, "0 0");
                object->setParentObject(parentObject);

                if(parentObject) {
                    NxPoint posOffset(0.5, -0.5, 0);
                    object->setPosOffset(posOffset);
                }
                currentDocument->objects[id] = object;
                currentDocument->setCurrentObject(object);
                return object->getId();
            }
            return 0;
        }
        else {
            // ---- GLOBAL COMMANDS ----
            //String parameter
            if((commande == COMMAND_ROTATE) || (commande == COMMAND_CENTER)) {
                if(argc > 1)    transport->dispatchProperty(qPrintable(commande), argvFullString(command, argv, 1));
                if(needOutput)  return transport->getProperty(qPrintable(commande));
            }
            //Single parameter
            else if((commande == COMMAND_ZOOM) || (commande == COMMAND_SPEED)) {
                if(argc > 1)    transport->dispatchProperty(qPrintable(commande), argvDouble(argv, 1));
                if(needOutput)  return transport->getProperty(qPrintable(commande));
            }

            //Solo & mute
            else if((commande == COMMAND_SOLO) || (commande == COMMAND_MUTE)) {
                if(argc > 1) {
                    QString key = argv.at(1);
                    bool isObject = false;
                    quint16 objectId = key.toUInt(&isObject);
                    if(isObject) {
                        NxObject *object = currentDocument->getObject(objectId);
                        if(object) {
                            if(argc > 2) {
                                object->dispatchProperty(qPrintable(commande), argvDouble(argv, 2));
                                actionCC(object, 3);
                            }
                            else if(needOutput)
                                return object->getProperty(qPrintable(commande)).toInt();
                        }
                    }
                    else {
                        NxGroup *group = currentDocument->getGroup(key);
                        if(group) {
                            if(argc > 2) {
                                group->dispatchPropertyToGroup(qPrintable(commande), argvDouble(argv, 2));
                                actionCC(group, 3);
                            }
                            else if(needOutput)
                                return group->getPropertyFromGroup(qPrintable(commande)).toInt();
                        }
                    }
                }
            }


            //Other type
            else if((commande == COMMAND_TEXTURE) && (argc > 1)) {
                if(argc > 6) {
                    QString filename = argvFullString(command, argv, 6);
                    if(!QFile().exists(filename))
                        filename = scriptDir.absoluteFilePath(currentDocument->fileItem->filename.file.absolutePath() + "/" + filename);
                    return render->loadTexture(new UiRenderTexture(argv.at(1).trimmed(), QFileInfo(filename), NxRect(NxPoint(argvDouble(argv, 2), argvDouble(argv, 3)), NxPoint(argvDouble(argv, 4), argvDouble(argv, 5)))));
                }
                else
                    return render->removeTexture(argv.at(1).trimmed());
            }
            else if((commande == COMMAND_GLOBAL_COLOR) && (argc > 5)) {
                Global::colors->insert(argv.at(1), QColor(argvDouble(argv, 2), argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5)));
                return Global::colors->update();
            }
            else if((commande == COMMAND_GLOBAL_COLOR_HUE) && (argc > 5)) {
                QColor color;
                color.setHsv(argvDouble(argv, 2), argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5));
                Global::colors->insert(argv.at(1), color);
                return Global::colors->update();
            }



            //No undo or specific commands
            else if(commande == COMMAND_LOAD) {
                if(argc > 1) {
                    //TODO
                    /*
                    QString filename = argvFullString(command, argv, 1);
                    bool ok = false;
                    ok = inspector->setProjectFiles(filename);
                    if(inspector->setProjectFiles(filename))
                        actionProjectFiles();
                    else if(inspector->setProjectScripts(filename))
                        actionProjectScripts();
                    */
                    return true;
                }
                return view->windowTitle();
            }
            else if((commande == COMMAND_SNAPSHOT) && (argc > 1)) {
                if(argc > 2)        return render->captureFrame(argvDouble(argv, 1), argvFullString(command, argv, 2));
                else                return render->captureFrame(argvDouble(argv, 1));
            }
            else if(commande == COMMAND_VIEWPORT) {
                if(argc > 2)        view->actionResize(QSize(argvDouble(argv, 1), argvDouble(argv, 2)));
                if(needOutput)      return QString("%1 %2").arg(render->size().width()).arg(render->size().height());
            }
            else if(commande == COMMAND_PLAY) {
                if(argc > 1) {
                    qreal speed = argvDouble(argv, 1);
                    if(speed != 0) {
                        transport->setSpeed(speed);
                        if(schedulerActivity != SchedulerOn) {
                            setScheduler(SchedulerOn);
                            MessageManager::networkSynchro(true);
                        }
                    }
                    else {
                        if(schedulerActivity != SchedulerOff) {
                            setScheduler(SchedulerOff);
                            MessageManager::networkSynchro(false);
                        }
                    }
                }
                else if(schedulerActivity != SchedulerOn) {
                    setScheduler(SchedulerOn);
                    MessageManager::networkSynchro(true);
                }
            }
            else if(commande == COMMAND_TITLE) {
                return view->windowTitle();
            }
            else if(commande == COMMAND_FF) {
                forceGoto(0);
            }
            else if((commande == COMMAND_LOG) && (argc > 1)) {
                MessageManager::logReceive(MessageLog(tr("Script: ") + argvFullString(command, argv, 1)));
            }
            else if(commande == COMMAND_STOP) {
                if(schedulerActivity != SchedulerOff) {
                    setScheduler(SchedulerOff);
                    MessageManager::networkSynchro(false);
                }
            }
            else if(commande == COMMAND_GOTO) {
                if(argc > 1) {
                    forceGoto(argvDouble(argv, 1));
                    timerTick(true);
                }
                return Transport::timeLocal;
            }
            else if((commande == COMMAND_SLEEP) && (argc > 1)) {
                QMutex mutex;
                QWaitCondition sleep;
                sleep.wait(&mutex, argvDouble(argv, 1));
            }
            else if(commande == COMMAND_CLEAR) {
                currentDocument->pushSnapshot();
                currentDocument->clear();
            }
            else if(commande == COMMAND_MOUSE) {
                if(argc > 1)    QCursor::setPos(argvDouble(argv, 1), argvDouble(argv, 2));
                if(needOutput)  return QString("%1 %2").arg(QCursor::pos().x()).arg(QCursor::pos().y());
            }
            else if(commande == COMMAND_MESSAGE_SEND) {
                if(argc > 1) {
                    QString mess = "1," + argvFullString(command, argv, 1);
                    NxTrigger *obj = new NxTrigger(this, 0);
                    obj->setMessagePatterns(mess);
                    obj->trig(0);
                    delete obj;
                    return true;
                }
            }



            // ---- OBJECT ORIENTED COMMANDS ----
            else if(argc > 1) {
                NxObjectDispatchProperty *object = getObject(argv.at(1));

                if(object) {
                    //String parameter
                    if((commande == COMMAND_GROUP) || (commande == COMMAND_RESIZE) || (commande == COMMAND_POS) || (commande == COMMAND_POS_TRANSLATE) || (commande == COMMAND_LABEL) || (commande == COMMAND_CURSOR_BOUNDS_SOURCE) || (commande == COMMAND_CURSOR_BOUNDS_TARGET) || (commande == COMMAND_CURVE_EQUATION_PARAM) || (commande == COMMAND_COLOR_ACTIVE) || (commande == COMMAND_COLOR_INACTIVE) || (commande == COMMAND_COLOR_ACTIVE_HUE) || (commande == COMMAND_COLOR_INACTIVE_HUE) || (commande == COMMAND_MESSAGE) || (commande == COMMAND_CURVE_ELL) || (commande == COMMAND_CURVE_POINT_SHIFT) || (commande == COMMAND_CURVE_POINT_TRANSLATE) || (commande == COMMAND_CURVE_POINT_TRANSLATE2) || (commande == COMMAND_CURVE_EQUATION) || (commande == COMMAND_TEXTURE_ACTIVE) || (commande == COMMAND_TEXTURE_INACTIVE) || (commande == COMMAND_LINE) || (commande == COMMAND_CURSOR_OFFSET) || (commande == COMMAND_CURSOR_START) || (commande == COMMAND_CURSOR_SPEED)) {
                        if(argc > 2)    object->dispatchProperty(qPrintable(commande), argvFullString(command, argv, 2));
                        if(needOutput)  return object->getProperty(qPrintable(commande));
                    }
                    //Val + string
                    else if((commande == COMMAND_CURVE_PATH) || (commande == COMMAND_CURVE_LINES) || (commande == COMMAND_CURVE_TXT)) {
                        if(argc > 3)  {
                            object->dispatchProperty(qPrintable(commande), argvFullString(command, argv, 3));
                            object->dispatchProperty(COMMAND_RESIZEF, argvDouble(argv, 2));
                        }
                        if(needOutput)  return object->getProperty(qPrintable(commande));
                    }

                    //Single parameter
                    else if((commande == COMMAND_RESIZEF) || (commande == COMMAND_CURSOR_WIDTH) || (commande == COMMAND_CURSOR_DEPTH) || (commande == COMMAND_SIZE) || (commande == COMMAND_CURSOR_SPEEDF) || (commande == COMMAND_CURSOR_BOUNDS_SOURCE_MODE) || (commande == COMMAND_CURSOR_TIME) || (commande == COMMAND_CURSOR_TIME_PERCENT) || (commande == COMMAND_CURVE_INERTIE) || (commande == COMMAND_CURVE_LENGTH) || (commande == COMMAND_POS_X) || (commande == COMMAND_POS_Y) || (commande == COMMAND_POS_Z) || (commande == COMMAND_ACTIVE) || (commande == COMMAND_MESSAGE_INTERVAL) || (commande == COMMAND_TRIGGER_OFF) || (commande == COMMAND_CURVE_EQUATION_POINTS) || (commande == COMMAND_CURVE_POINT_RMV) || (commande == COMMAND_ID)) {
                        if(argc > 2)    object->dispatchProperty(qPrintable(commande), argvDouble(argv, 2));
                        if(needOutput)  return object->getProperty(qPrintable(commande));
                    }

                    //Activation
                    else if((commande == COMMAND_TRIG) || (commande == COMMAND_CURVE_EDITOR)) {
                        object->dispatchProperty(qPrintable(commande), true);
                    }

                    //Specific syntax
                    else if((commande == COMMAND_REMOVE) && (argc > 1) && ((object->getType() == ObjectsTypeCursor) || (object->getType() == ObjectsTypeCurve) || (object->getType() == ObjectsTypeTrigger))) {
                        NxObject *object = (NxObject*)getObject(argv.at(1), false);
                        removeObject(object);
                        return false;
                    }
                    else if((commande == COMMAND_CURVE_POINT) || (commande == COMMAND_CURVE_POINT_SMOOTH) || (commande == COMMAND_CURVE_POINT_X) || (commande == COMMAND_CURVE_POINT_Y) || (commande == COMMAND_CURVE_POINT_Z)) {
                        QList<qreal> points;
                        for(quint16 i = 2 ; i < argc ; i++)
                            points.append(argv.at(i).toDouble());
                        object->dispatchProperty(qPrintable(commande), QVariant::fromValue(points));
                    }


                    //Dual actions
                    else if(commande == COMMAND_COLOR_GLOBAL) {
                        if(argc > 2) {
                            object->dispatchProperty(COMMAND_COLOR_ACTIVE,   argvFullString(command, argv, 2));
                            object->dispatchProperty(COMMAND_COLOR_INACTIVE, argvFullString(command, argv, 2));
                        }
                        if(needOutput)  return object->getProperty(COMMAND_COLOR_ACTIVE);
                    }
                    else if(commande == COMMAND_COLOR_GLOBAL_HUE) {
                        if(argc > 2) {
                            object->dispatchProperty(COMMAND_COLOR_ACTIVE_HUE,   argvFullString(command, argv, 2));
                            object->dispatchProperty(COMMAND_COLOR_INACTIVE_HUE, argvFullString(command, argv, 2));
                        }
                        if(needOutput)  return object->getProperty(COMMAND_COLOR_ACTIVE_HUE);
                    }
                    else if(commande == COMMAND_TEXTURE_GLOBAL) {
                        if(argc > 2) {
                            object->dispatchProperty(COMMAND_TEXTURE_ACTIVE,          argv.at(2));
                            object->dispatchProperty(COMMAND_TEXTURE_INACTIVE,        argv.at(2));
                        }
                        if(needOutput)  return object->getProperty(COMMAND_TEXTURE_ACTIVE);
                    }


                    //No undo or specific commands
                    if(object->getType() == ObjectsTypeCursor) {
                        NxCursor *cursor = (NxCursor*)object;
                        if(commande == COMMAND_CURSOR_CURVE) {
                            if(argc > 2) {
                                NxObject *object2 = (NxObject*)getObject(argv.at(2), false);
                                if((object2) && (object2->getType() == ObjectsTypeCurve)) {
                                    NxCurve *curve = (NxCurve*)object2;
                                    cursor->setCurve(curve);
                                    cursor->calculate();
                                }
                            }
                            NxCurve *curve = cursor->getCurve();
                            if((curve) && (needOutput))
                                return curve->getId();
                        }
                    }
                }
            }
        }
    }
    return false;
}
void IanniX::executeAsScript(const QString &script) {
    currentDocument->scriptEvaluate(script, false);
}

void IanniX::send(const Message &message, QStringList *sentMessage) {
    //Launch
    execute(message.getAsciiMessage(), ExecuteSourceNetwork);

    //Log in console
    MessageManager::logReceive(message, sentMessage);
}

QString IanniX::incomingMessage(const MessageIncomming &source, bool needOutput) {
    if(needOutput) {
        QString retour;
        retour += execute(source, false, true).toString();
        QString retourScript = currentDocument->incomingMessage(source, true);
        if(retourScript != "undefined")
            retourScript += retourScript;
        return retour;
    }
    else {
        execute(source, ExecuteSourceNetwork);
        currentDocument->incomingMessage(source);
    }
    return QString();
}

void IanniX::openMessageEditor() {
    inspector->actionMessages();
}

void IanniX::actionReloadScript() {
    currentDocument->open(false);
}

void IanniX::actionUnmuteGroups() {
    foreach(NxGroup *group, currentDocument->groups)
        if(group->isMuted())
            group->setMute(0);
}
void IanniX::actionUnmuteObjects() {
    //Browse documents
    foreach(NxGroup *group, currentDocument->groups)
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++)
            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++)
                //Browse objects
                foreach(NxObject *object, group->objects[activityIterator][typeIterator])
                    if(object->isMuted())
                        object->setMute(0);
}
void IanniX::actionUnsoloGroups() {
    foreach(NxGroup *group, currentDocument->groups)
        if(group->isSolo())
            group->setSolo(0);
}
void IanniX::actionUnsoloObjects() {
    //Browse documents
    foreach(NxGroup *group, currentDocument->groups)
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++)
            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++)
                //Browse objects
                foreach(NxObject *object, group->objects[activityIterator][typeIterator])
                    if(object->isSolo())
                        object->setSolo(0);
}

void IanniX::actionCloseEvent(QCloseEvent *event) {
    quint16 nbFileNoSave = 0;
    /*
    if(currentDocument->getHasChanged())
        nbFileNoSave++;
        */

    if(nbFileNoSave > 0) {
        int rep = QMessageBox::question(0, tr("Score save"), tr("Score been changed without saving.\n\nDo you want to save modifications?"), QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Cancel);
        if(rep == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
        else if(rep == QMessageBox::Save)
            actionSave();
    }

    //Save settings
    if(iniSettings) {
        foreach(UiOption *option, UiOptions::options)
            iniSettings->setValue(option->settingName, option->variant());
        iniSettings->setValue("appVersion", QApplication::applicationVersion());
    }

    if(render)
        render->close();
    if(transport)
        transport->close();

    MessageManager::deleteNetworkInterface();

    event->accept();
}


void IanniX::actionUndo() {
    currentDocument->popSnapshot();
}
void IanniX::actionRedo() {
    currentDocument->popSnapshot(true);
}


QString IanniX::waitForMessage() {
    waitingForMessageValue = true;
    QEventLoop loop;
    connect(this, SIGNAL(waitForMessageArrived()), &loop, SLOT(quit()));
    loop.exec();
    return waitForMessageValue;
}

void IanniX::pushSnapshot() {
    currentDocument->pushSnapshot();
}

void IanniX::actionPaste() {
    currentDocument->pushSnapshot();
    QString paste = QApplication::clipboard()->text();
    currentDocument->source = ExecuteSourceGui;
    currentDocument->scriptEvaluate(paste, true);
}
void IanniX::actionCopy() {
    QString copy = "";
    NxObjectDispatchProperty::source = ExecuteSourceCopyPaste;
    foreach(NxObject *object, *render->getSelection())
        if(object->getType() != ObjectsTypeCursor)
            copy += object->serialize();

    QApplication::clipboard()->setText(copy);
}
