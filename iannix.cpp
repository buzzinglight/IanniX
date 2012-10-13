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


IanniX::IanniX(QObject *parent, bool forceSettings) :
    NxObjectFactoryInterface(parent) {
    hasStarted = false;
    currentDocument = 0;
    currentScript = 0;
    projectScore = 0;
    isGroupSoloActive = false;
    isObjectSoloActive = false;
    acceptMidiSyncClock = false;
    acceptMidiSyncSong = false;
    timeLocalStr = "000:00.000";
    freehandCurveId = 0;
    lastMessageAllow = true;
    lastMessageReceivedAllow = false;
    oscBundleHost = QHostAddress("127.0.0.1");
    oscBundlePort = 0;
    scriptDir = QDir::current();
    cpu = new NxCpu(this);
    baseDocumentDir = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) + QString(QDir::separator()) + "IanniX" + QString(QDir::separator());

    QFileInfo newScriptDestination = QFileInfo(baseDocumentDir + "New Script.nxscript");
    if(!newScriptDestination.exists()) {
        QDir().mkpath(newScriptDestination.absolutePath());
        QFile::copy(QFileInfo("./Project/New Script Template.nxscript").absoluteFilePath(), newScriptDestination.absoluteFilePath());
    }
    QFileInfo newScoreDestination  = QFileInfo(baseDocumentDir + "New Score.nxscore");
    if(!newScoreDestination.exists()) {
        QFile::copy(QFileInfo("./Project/New Score Template.nxscore").absoluteFilePath(),  newScoreDestination.absoluteFilePath());
        QDir().mkpath(newScoreDestination.absolutePath());
    }

    splash = new UiSplash(0);
    splash->show();
    QTimer::singleShot(1500, this, SLOT(closeSplash()));
    QCoreApplication::processEvents();

    iconAppPlay  = QIcon(":icons/res_appicon_play.png");
    iconAppPause = QIcon(":icons/res_appicon_pause.png");

    //Update management
    updateManager = new QNetworkAccessManager(this);
    connect(updateManager, SIGNAL(finished(QNetworkReply*)), SLOT(checkForUpdatesFinished(QNetworkReply*)));

    //View
    view = new UiView(0);
    connect(view, SIGNAL(actionRouteFast_rewind()), SLOT(actionFast_rewind()));
    connect(view, SIGNAL(actionRoutePlay_pause()), SLOT(actionPlay_pause()));
    connect(view, SIGNAL(actionRouteToggle_Inspector()), SLOT(actionToggle_Inspector()));
    connect(view, SIGNAL(actionRouteToggle_Transport()), SLOT(actionToggle_Transport()));
    connect(view, SIGNAL(actionRouteToggle_Autosize()), SLOT(actionToggle_Autosize()));
    connect(view, SIGNAL(actionRouteDrawFreeCurve()), SLOT(actionDrawFreeCurve()));
    connect(view, SIGNAL(actionRouteDrawPointCurve()), SLOT(actionDrawPointCurve()));
    connect(view, SIGNAL(actionRouteDrawTriggers()), SLOT(actionDrawTriggers()));
    connect(view, SIGNAL(actionRouteAddFreeCursor()), SLOT(actionAddFreeCursor()));
    connect(view, SIGNAL(actionRouteCircleCurve()), SLOT(actionCircleCurve()));
    connect(view, SIGNAL(actionRouteGridChange(qreal)), SLOT(actionGridChange(qreal)));
    connect(view, SIGNAL(actionRouteGridOpacityChange(qreal)), SLOT(actionGridOpacityChange(qreal)));
    connect(view, SIGNAL(actionRouteShowEditor()), SLOT(actionShowEditor()));
    connect(view, SIGNAL(actionRouteShowTimer()), SLOT(actionShowTimer()));
    connect(view, SIGNAL(actionRouteReloadScript()), SLOT(actionReloadScript()));
    connect(view, SIGNAL(actionRouteCloseEvent(QCloseEvent*)), SLOT(actionCloseEvent(QCloseEvent*)));
    connect(view, SIGNAL(actionRouteAbout()), SLOT(actionLogo()));
    connect(view, SIGNAL(actionRouteImportSVG(QString)),            SLOT(actionImportSVG(QString)));
    connect(view, SIGNAL(actionRouteImportImage(QString)),          SLOT(actionImportImage(QString)));
    connect(view, SIGNAL(actionRouteImportBackground(QString)),     SLOT(actionImportBackground(QString)));
    connect(view, SIGNAL(actionRouteImportText(QString,QString)),   SLOT(actionImportText(QString,QString)));
    connect(view, SIGNAL(actionRouteSelectionModeChange(bool,bool,bool)), SLOT(actionSelectionModeChange(bool,bool,bool)));
    connect(view, SIGNAL(actionRoutePasteScript()), SLOT(actionPasteScript()));
    connect(view, SIGNAL(editingStop()), SLOT(editingStop()));
    connect(view, SIGNAL(editingStart(NxPoint)), SLOT(editingStart(NxPoint)));
    connect(view, SIGNAL(editingMove(NxPoint,bool)), SLOT(editingMove(NxPoint,bool)));

    //Transport
    transport = view->getTransport();
    connect(transport, SIGNAL(actionRouteFast_rewind()), SLOT(actionFast_rewind()));
    connect(transport, SIGNAL(actionRoutePlay_pause()), SLOT(actionPlay_pause()));
    connect(transport, SIGNAL(actionRouteLogo()), SLOT(actionLogo()));
    connect(transport, SIGNAL(actionRouteGoto()), SLOT(actionGoto()));
    connect(transport, SIGNAL(actionRouteSetOpenGL()), SLOT(actionSetOpenGL()));
    connect(transport, SIGNAL(actionRouteSetScheduler()), SLOT(actionSetScheduler()));
    connect(transport, SIGNAL(actionRouteSpeed()), SLOT(actionSpeed()));
    connect(transport, SIGNAL(actionRouteSyphon(bool)), SLOT(allowSyphonServer(bool)));
    connect(this, SIGNAL(updateTransport(QString,QString)), transport, SLOT(updateTransport(QString,QString)));
    //Timer
    uitimer = new UiTimer(0);
    connect(this, SIGNAL(updateTransport(QString,QString)), uitimer, SLOT(updateTransport(QString,QString)));
    connect(uitimer, SIGNAL(closed(bool)), view, SLOT(toggleTimer(bool)));

    //Inspector
    inspector = view->getInspector();
    inspector->setFactory(this);
    connect(inspector, SIGNAL(actionRouteTabChange(int)), SLOT(actionTabChange(int)));
    connect(inspector, SIGNAL(actionRouteViewChange()), SLOT(actionViewChange()));
    connect(inspector, SIGNAL(actionRouteCC()), SLOT(actionCC()));
    connect(inspector, SIGNAL(actionRouteCC2()), SLOT(actionCC2()));
    connect(inspector, SIGNAL(actionChangeID(quint16, quint16)), SLOT(actionChangeID(quint16, quint16))); ////CG////
    connect(inspector, SIGNAL(actionRouteProjectFiles()), SLOT(actionProjectFiles()));
    connect(inspector, SIGNAL(actionRouteProjectScripts()), SLOT(actionProjectScripts()));
    connect(inspector, SIGNAL(actionRouteProjectScriptsContext(QPoint)), SLOT(actionProjectScriptsContext(QPoint)));
    connect(inspector, SIGNAL(actionRouteProjectFilesContext(QPoint)), SLOT(actionProjectFilesContext(QPoint)));
    connect(inspector, SIGNAL(transportMessageChange(QString)), SLOT(transportMessageChange(QString)));
    connect(inspector, SIGNAL(syncMessageChange(QString)), SLOT(syncMessageChange(QString)));
    connect(inspector, SIGNAL(bundleMessageChange(QString,quint16)), SLOT(bundleMessageChange(QString,quint16)));
    connect(inspector, SIGNAL(actionUnmuteGroups()), SLOT(actionUnmuteGroups()));
    connect(inspector, SIGNAL(actionUnmuteObjects()), SLOT(actionUnmuteObjects()));
    connect(inspector, SIGNAL(actionUnsoloGroups()), SLOT(actionUnsoloGroups()));
    connect(inspector, SIGNAL(actionUnsoloObjects()), SLOT(actionUnsoloObjects()));
    connect(inspector, SIGNAL(midiSyncClockChanged(bool)), SLOT(setMidiSyncClock(bool)));
    connect(inspector, SIGNAL(midiSyncSongChanged(bool)), SLOT(setMidiSyncSong(bool)));

    //Render
    render = view->getRender();
    render->setFactory(this);
    connect(render, SIGNAL(setPerfOpenGL(QString)), transport, SLOT(setPerfOpenGL(QString)));
    connect(render, SIGNAL(mousePosChanged(NxPoint)), inspector, SLOT(setMousePos(NxPoint)));
    connect(render, SIGNAL(mouseZoomChanged(qreal)), inspector, SLOT(setMouseZoom(qreal)));
    connect(render, SIGNAL(selectionChanged()), inspector, SLOT(askRefresh()));
    connect(render, SIGNAL(actionRouteNew()), SLOT(actionNew()));
    connect(render, SIGNAL(actionRouteOpen()), SLOT(actionOpen()));
    connect(render, SIGNAL(actionRouteSave()), SLOT(actionSave()));
    connect(render, SIGNAL(actionRouteSave_as()), SLOT(actionSave_as()));
    connect(render, SIGNAL(actionRouteSave_all()), SLOT(actionSave_all()));
    connect(render, SIGNAL(actionRouteDuplicateScore()), SLOT(actionDuplicateScore()));
    connect(render, SIGNAL(actionRouteRename()), SLOT(actionRename()));
    connect(render, SIGNAL(actionRouteRemove()), SLOT(actionRemove()));
    connect(render, SIGNAL(actionRouteUndo()), SLOT(actionUndo()));
    connect(render, SIGNAL(actionRouteSync()), SLOT(actionSync()));
    connect(render, SIGNAL(actionRouteRedo()), SLOT(actionRedo()));
    connect(render, SIGNAL(actionRouteImportSVG(QString)),          SLOT(actionImportSVG(QString)));
    connect(render, SIGNAL(actionRouteImportImage(QString)),        SLOT(actionImportImage(QString)));
    connect(render, SIGNAL(actionRouteImportBackground(QString)),   SLOT(actionImportBackground(QString)));
    connect(render, SIGNAL(actionRouteImportText(QString,QString)), SLOT(actionImportText(QString,QString)));
    connect(render, SIGNAL(editingStop()), SLOT(editingStop()));
    connect(render, SIGNAL(editingStart(NxPoint)), SLOT(editingStart(NxPoint)));
    connect(render, SIGNAL(editingMove(NxPoint,bool)), SLOT(editingMove(NxPoint,bool)));
    connect(render, SIGNAL(escFullscreen()), view, SLOT(escFullscreen()));
    connect(view, SIGNAL(actionRouteSnapXGrid()), render, SLOT(actionSnapXGrid()));
    connect(view, SIGNAL(actionRouteSnapYGrid()), render, SLOT(actionSnapYGrid()));
    connect(view, SIGNAL(actionRouteSnapZGrid()), render, SLOT(actionSnapZGrid()));
    connect(inspector, SIGNAL(actionFollowID(qint16)), render, SLOT(actionFollowID(qint16)));
    connect(view, SIGNAL(actionRouteArrange(quint16)), render, SLOT(actionArrange(quint16)));
    connect(view, SIGNAL(actionRouteSnaphot(qreal)), render, SLOT(capture(qreal)));
    render->zoom();

    //Message script engine
    QScriptValue messageScript = messageScriptEngine.globalObject();
    messageScript = messageScriptEngine.evaluate(ExtScriptManager::loadLibrary(scriptDir));

    //Objet transport
    transportObject = new NxTrigger(this, 0, render->getRenderOptions());
    syncObject = new NxTrigger(this, 0, render->getRenderOptions());

    //Editor
    editor = new UiEditor(this, 0);
    connect(editor, SIGNAL(closed(bool)), view, SLOT(toggleEditor(bool)));

    //Other connections
    actionViewChange();
    inspector->setRender(render);

    //Other composents
    osc = new ExtOscManager(this);
    connect(inspector, SIGNAL(oscPortChange(quint16)), osc, SLOT(openPort(quint16)));
    connect(osc, SIGNAL(openPortStatus(bool)), inspector, SLOT(setOSCOk(bool)));

    tcp = new ExtTcpManager(this);
    connect(inspector, SIGNAL(tcpPortChange(quint16)), tcp, SLOT(openPort(quint16)));
    connect(tcp, SIGNAL(openPortStatus(bool)), inspector, SLOT(setTCPOk(bool)));
    connect(tcp, SIGNAL(clientsStatus(quint16)), inspector, SLOT(setTCPClients(quint16)));

    udp = new ExtUdpManager(this);
    connect(inspector, SIGNAL(udpPortChange(quint16)), udp, SLOT(openPort(quint16)));
    connect(udp, SIGNAL(openPortStatus(bool)), inspector, SLOT(setUDPOk(bool)));

    http = new ExtHttpManager(this);
    connect(inspector, SIGNAL(httpPortChange(quint16)), http, SLOT(openPort(quint16)));
    connect(http, SIGNAL(openPortStatus(bool)), inspector, SLOT(setHttpOk(bool)));

    serial = new ExtSerialManager(this);
    connect(inspector, SIGNAL(serialPortChange(QString)), serial, SLOT(openPort(QString)));
    connect(serial, SIGNAL(openPortStatus(bool)), inspector, SLOT(setSerialOk(bool)));

    midi = new ExtMidiManager(this);

#ifdef WACOM_INSTALLED
    wacom = new ExtWacomManager();
#endif

    ipOutId = -1;
    connect(inspector, SIGNAL(ipOutChange(QString)), SLOT(setIpOut(QString)));
    connect(this, SIGNAL(ipOutStatus(bool)), inspector, SLOT(setIpOutOk(bool)));
    connect(inspector, SIGNAL(midiOutChange(QString)), SLOT(setMidiOut(QString)));
    connect(inspector, SIGNAL(midiTempoChange(qreal)), midi, SLOT(setMidiTempo(qreal)));
    //connect(this, SIGNAL(midiOutStatus(bool)), inspector, SLOT(setMidiOutOk(bool)));


#ifdef KINECT_INSTALLED
    kinect = new ExtKinectManager();
#endif


    //File management
    //connect(&fileWatcher, SIGNAL(fileChanged(QString)), SLOT(fileWatcherChanged(QString)));
    connect(&fileWatcher, SIGNAL(directoryChanged(QString)), SLOT(fileWatcherChanged(QString)));

    //About
    about = new UiAbout(0);

    //Scheduler
    actionSpeed();
    timeLocal = 0;
    timeTransportRefresh = 0;
    timePerfRefresh = 0;
    timePerfCounter = 0;
    timer = new QTimer(this);
    timer->setInterval(5);
    timerOk = false;
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    timer->start();
    actionFast_rewind();
    actionTabChange(0);

    //Settings
    QSettings settings;
    //UDP
    if((forceSettings) || (!settings.childKeys().contains("oscPort")))
        settings.setValue("oscPort",  1234);
    if((forceSettings) || (!settings.childKeys().contains("udpPort")))
        settings.setValue("udpPort",  1235);
    if((forceSettings) || (!settings.childKeys().contains("httpPort")))
        settings.setValue("httpPort", 1236);
    if((forceSettings) || (!settings.childKeys().contains("tcpPort")))
        settings.setValue("tcpPort", 3000);
    if((forceSettings) || (!settings.childKeys().contains("ipOut")))
        settings.setValue("ipOut", "127.0.0.1");
    if((forceSettings) || (!settings.childKeys().contains("midiOut")))
        settings.setValue("midiOut", "To_IanniX");
    if((forceSettings) || (!settings.childKeys().contains("midiTempo")))
        settings.setValue("midiTempo", 120);
    if((forceSettings) || (!settings.childKeys().contains("acceptMidiSyncClock")))
        settings.setValue("acceptMidiSyncClock", 0);
    if((forceSettings) || (!settings.childKeys().contains("acceptMidiSyncSong")))
        settings.setValue("acceptMidiSyncSong", 1);

#ifdef Q_OS_MAC
    if((forceSettings) || (!settings.childKeys().contains("serialPort")))
        settings.setValue("serialPort", "/dev/tty.usbserial-A600afc5:BAUD115200:DATA_8:PAR_NONE:STOP_1:FLOW_OFF");
#endif
#ifdef Q_OS_WIN
    if((forceSettings) || (!settings.childKeys().contains("serialPort")))
        settings.setValue("serialPort", "COM1:BAUD115200:DATA_8:PAR_NONE:STOP_1:FLOW_OFF");
#endif
#ifdef Q_OS_LINUX
    if((forceSettings) || (!settings.childKeys().contains("serialPort")))
        settings.setValue("serialPort", "/dev/tty.usbserial-A600afc5:BAUD115200:DATA_8:PAR_NONE:STOP_1:FLOW_OFF");
#endif

    settings.setValue("defaultMessageTrigger", "osc://ip_out:57120/trigger trigger_id trigger_xPos trigger_yPos trigger_zPos cursor_id");
    settings.setValue("defaultMessageCursor", "osc://ip_out:57120/cursor cursor_id cursor_value_x cursor_value_y cursor_xPos cursor_yPos cursor_zPos");
    settings.setValue("defaultMessage", "osc://ip_out:57120/object trigger_id cursor_id");
    settings.setValue("defaultMessageSync", "");

    if((forceSettings) || (!settings.childKeys().contains("defaultMessageTransport")))
        settings.setValue("defaultMessageTransport", "osc://ip_out:57120/transport status nb_triggers nb_cursors nb_curves");

    if((forceSettings) || (!settings.childKeys().contains("defaultMessageSync")))
        settings.setValue("defaultMessageSync", "osc://127.0.0.1:57120/iannix/ status");
    if((forceSettings) || (!settings.childKeys().contains("updatePeriod")))
        settings.setValue("updatePeriod", 1);

    if((forceSettings) || (!settings.childKeys().contains("bundleHost")))
        settings.setValue("bundleHost", "127.000.000.001");
    if((forceSettings) || (!settings.childKeys().contains("bundlePort")))
        settings.setValue("bundlePort", "57121");

    if((forceSettings) || (!settings.childKeys().contains("colorTheme")))
        settings.setValue("colorTheme", false);
    if((forceSettings) || (!settings.childKeys().contains("opacityCurve")))
        settings.setValue("opacityCurve", false);
    if((forceSettings) || (!settings.childKeys().contains("autoresize")))
        settings.setValue("autoresize", false);
    if((forceSettings) || (!settings.childKeys().contains("objectLabel")))
        settings.setValue("objectLabel", true);
    if((forceSettings) || (!settings.childKeys().contains("grid")))
        settings.setValue("grid", true);

    inspector->setOSCPort(settings.value("oscPort").toUInt());
    inspector->setUDPPort(settings.value("udpPort").toUInt());
    inspector->setTCPPort(settings.value("tcpPort").toUInt());
    inspector->setHttpPort(settings.value("httpPort").toUInt());
    inspector->setIpOut(settings.value("ipOut").toString());
    inspector->setMidiOut(settings.value("midiOut").toString());
    inspector->setMidiTempo(settings.value("midiTempo").toDouble());
    inspector->setSerialPort(settings.value("serialPort").toString());
    inspector->setTransportMessage(settings.value("defaultMessageTransport").toString());
    inspector->setSyncMessage(settings.value("defaultMessageSync").toString());
    inspector->setBundleMessage(settings.value("bundleHost").toString(), settings.value("bundlePort").toUInt());
    defaultMessageTrigger = settings.value("defaultMessageTrigger").toString();
    defaultMessageCursor = settings.value("defaultMessageCursor").toString();
    render->setColorTheme(settings.value("colorTheme").toBool());
    view->setColorTheme(render->getColorTheme());
    inspector->setViewCurveOpacityCheck(settings.value("opacityCurve").toBool());
    render->setTriggerAutosize(settings.value("autoresize").toBool());
    view->toggleAutosize(settings.value("autoresize").toBool());
    view->setToggleLabel(settings.value("objectLabel").toBool());
    render->getRenderOptions()->paintAxisGrid = settings.value("grid").toBool();

    acceptMidiSyncClock = settings.value("acceptMidiSyncClock").toBool();
    inspector->setMidiSyncClock(settings.value("acceptMidiSyncClock").toBool());
    acceptMidiSyncSong = settings.value("acceptMidiSyncSong").toBool();
    inspector->setMidiSyncSong(settings.value("acceptMidiSyncSong").toBool());
    //acceptMidiSyncClock = settings.value("acceptMidiSyncClock").toBool();
    //acceptMidiSyncSong = settings.value("acceptMidiSyncSong").toBool();

    bool settingsOk = settings.childKeys().contains("lastUpdate") && settings.childKeys().contains("updatePeriod") && settings.childKeys().contains("id");
    if(settingsOk) {
        QDateTime date = settings.value("lastUpdate").toDateTime();
        quint16 period = settings.value("updatePeriod").toUInt();
        qDebug("Last update : %s (each %d days)", qPrintable(date.toString("dd/MM/yyyy hh:mm:ss")), period);
        if(date.daysTo(QDateTime::currentDateTime()) >= period)
            checkForUpdates();
    }
    else {
        qDebug("First launch. Write settings.");
        qsrand(QDateTime::currentDateTime().toTime_t());
        settings.setValue("id", qrand());
        checkForUpdates();
    }

    //Files
    inspector->getProjectFiles()->clear();
    inspector->getProjectScripts()->clear();
    projectScore = new QTreeWidgetItem(inspector->getProjectFiles());
    projectScore->setFlags(Qt::ItemIsEnabled);
    projectScore->setText(0, tr("CURRENT PROJECT"));
    projectScript = new QTreeWidgetItem(inspector->getProjectScripts());
    projectScript->setFlags(Qt::ItemIsEnabled);
    projectScript->setText(0, tr("CURRENT PROJECT"));
    libScript = new QTreeWidgetItem(inspector->getProjectScripts());
    libScript->setFlags(Qt::ItemIsEnabled);
    libScript->setText(0, tr("TOOLS"));
    exampleScript = new QTreeWidgetItem(inspector->getProjectScripts());
    exampleScript->setFlags(Qt::ItemIsEnabled);
    exampleScript->setText(0, tr("EXAMPLES"));

    //Expand
    inspector->getProjectFiles()->expandAll();
    inspector->getProjectScripts()->expandAll();

    QDir examplesDir("./Examples/");
    QDir libDir("./Tools/");
    fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", libDir, libScript, false);
    fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", examplesDir, exampleScript, false);

    //Conversion d'EDL
    //actionImportOldIanniXScore("tutorials/Tutorial 1.xml");
    /*
    QString tracks;
    for(quint16 i = 0 ; i < 10 ; i++) {
        QString sequence = QString("SEQ%1").arg(i);
        QFile edl(QString("EDL-%1.txt").arg(sequence));
        if(edl.exists() && edl.open(QFile::ReadOnly)) {
            tracks += QString("{\tsequence: \"%1\",\n"
                         "\ttrajectories: [\n").arg(sequence);
            QString edlContent = edl.readAll();
            QStringList edlTracklistsSeparator = edlContent.split("TRACK NAME:\t", QString::SkipEmptyParts);
            for(quint16 i = 1 ; i < edlTracklistsSeparator.count() ; i++) {
                QStringList edlTracklists = edlTracklistsSeparator[i].split("\n", QString::SkipEmptyParts);
                QString name, info, start, end, duration;
                qreal startSec = 0, endSec = 0, durationSec = 0;
                for(quint16 j = 0 ; j < edlTracklists.count() ; j++) {
                    if(j == 4) {
                        QStringList edlTracklistChannel = edlTracklists[j].split("\t");
                        if(edlTracklistChannel.count() > 5) {
                            QStringList edlTracklistChannelName = edlTracklistChannel[2].split(" ");
                            name     = edlTracklistChannelName[0];
                            info     = edlTracklistChannel[2].replace(name + " ", "");

                            start    = edlTracklistChannel[3];
                            QStringList startSeparator = start.split(":");
                            startSec = startSeparator[0].toDouble()*3600 + startSeparator[1].toDouble()*60 + startSeparator[2].toDouble() + startSeparator[3].toDouble()*1./25.;
                            startSec -= 3600;

                            end      = edlTracklistChannel[4];
                            QStringList endSeparator = end.split(":");
                            endSec = endSeparator[0].toDouble()*3600 + endSeparator[1].toDouble()*60 + endSeparator[2].toDouble() + endSeparator[3].toDouble()*1./25.;
                            endSec -= 3600;

                            duration = edlTracklistChannel[5];
                            QStringList durationSeparator = duration.split(":");
                            durationSec = durationSeparator[0].toDouble()*3600 + durationSeparator[1].toDouble()*60 + durationSeparator[2].toDouble() + durationSeparator[3].toDouble()*1./25.;
                        }
                    }
                }
                tracks += QString("\t{\tsequence: \"%1\", calque: \"\",\n"
                             "\t\tname: \"%2\", start: %3, duration: %4, acceleration: 1,\n"
                             "\t\tedlStart: \"%5\", edlEnd: \"%6\",\n"
                             "\t\tinfo: \"%7\", color: colors.green,\n"
                             "\t\tsize: {x: 0, y: 0, z: 0},\n"
                             "\t\tpoints: [	{x: -30, y: -5, z: -5, extra: \"smooth\"},\n"
                             "\t\t          {x:   0, y:  0, z:  5, extra: \"smooth\"},\n"
                             "\t\t          {x:  30, y:  5, z: -5, extra: \"smooth\"},\n"
                             "\t\t        ]},\n").arg(sequence).arg(name).arg(startSec).arg(durationSec).arg(start).arg(end).arg(info);
            }
            tracks += "]}, \n";
        }
        edl.close();
    }
    if(!tracks.isEmpty()) {
        QFile edlOut("EDL-out.js");
        if(edlOut.open(QFile::WriteOnly)) {
            tracks = QString("var data = [\n%1];").arg(tracks);
            edlOut.write(qPrintable(tracks));
            edlOut.close();
        }
    }
    */
}

void IanniX::readyToStart() {
    if(!hasStarted) {
        hasStarted = true;
        qDebug("Ready to start!");
        //allowSyphonServer(false);

        //Projet par défault
        loadProject(baseDocumentDir + "root.root");
        actionFast_rewind();

        startTimer(1000);
        render->startRenderTimer();
    }
}

void IanniX::actionImportSVG(const QString &filename) {
    qreal scale = 0.01;
    bool ok = false;
    scale = (new UiMessageBox())->getDouble(tr("SVG Import"), tr("Coordinates systems are differents.\nPlease enter a scale factor: "), QPixmap(":/infos/res_info_svg.png"), scale, 0.001, 10., 0.1, 3, "hundred of pixels/second", &ok);
    if(ok) {
        QDomDocument xmlDoc;
        QFile svgFile(filename);
        if(svgFile.open(QFile::ReadOnly)) {
            xmlDoc.setContent(svgFile.readAll());
            actionImportSVG(xmlDoc.documentElement(), scale);
            svgFile.close();
        }
    }
}
void IanniX::actionImportSVG(const QDomElement &xmlElement, qreal scale) {
    QDomNode xmlNode = xmlElement.firstChild();
    while(!xmlNode.isNull()) {
        QDomElement xmlData = xmlNode.toElement();
        if((!xmlData.isNull()) && (xmlData.tagName() == "path")) {
            execute(COMMAND_ADD + " curve auto");
            execute(COMMAND_CURVE_PATH + " current " + QString::number(scale) + " " + xmlData.attribute("d"));
        }
        else if((!xmlData.isNull()) && (xmlData.tagName() == "polyline")) {
            execute(COMMAND_ADD + " curve auto");
            execute(COMMAND_CURVE_LINES + " current " + QString::number(scale) + " " + xmlData.attribute("points"));
        }
        actionImportSVG(xmlData, scale);
        xmlNode = xmlNode.nextSibling();
    }
}
void IanniX::actionImportImage(const QString &filename) {
    qreal scale = 0.01;
    bool ok = false;
    scale = (new UiMessageBox())->getDouble(tr("Image import"), tr("Coordinates systems are differents.\nPlease enter a scale factor: "), QPixmap(":/infos/res_info_img.png"), scale, 0.001, 10., 0.1, 3, "hundred of pixels/second", &ok);
    if(ok) {
        execute(COMMAND_ADD + " curve auto");
        execute(COMMAND_CURVE_IMG + " current " + QString::number(scale) + " " + filename);
    }
}
void IanniX::actionImportBackground(const QString &filename) {
    QPixmap pixmap(filename);
    if(!pixmap.isNull()) {
        qreal scale = 100*qMin(8 / (qreal)pixmap.width(), 8 / (qreal)pixmap.height());
        bool ok = false;
        scale = (new UiMessageBox())->getDouble(tr("Image import"), tr("Coordinates systems are differents.\nPlease enter a scale factor: "), QPixmap(":/infos/res_info_img.png"), scale, 0.001, 10., 0.1, 3, "hundred of pixels/second", &ok);
        if(ok) {
            scale /= 100.;
            execute(COMMAND_TEXTURE + " background " + QString("%1 %2 %3 %4").arg(-scale * pixmap.width() / 2).arg(scale * pixmap.height() / 2).arg(scale * pixmap.width() / 2).arg(-scale * pixmap.height() / 2) + " " + filename);
        }
    }
}

void IanniX::actionSelectionModeChange(bool cursors, bool curves, bool triggers) {
    render->getRenderOptions()->allowSelectionCursors  = cursors;
    render->getRenderOptions()->allowSelectionCurves   = curves;
    render->getRenderOptions()->allowSelectionTriggers = triggers;
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
    ok = false;
    scale = (new UiMessageBox())->getDouble(tr("Text import"), tr("Coordinates systems are differents.\nPlease enter a scale factor: "), QPixmap(":/infos/res_info_txt.png"), scale, 0.001, 10., 0.1, 3, "hundred of pixels/second", &ok);
    if(ok) {
        execute(COMMAND_ADD + " curve auto");
        execute(COMMAND_CURVE_TXT + " current " + QString::number(scale) + " " + fontReal + " " + text);
    }
}

void IanniX::actionImportOldIanniXScore(const QString &filename) {
    QDomDocument xmlDoc;
    QFile xmlFile(filename);
    if((xmlFile.exists()) && (xmlFile.open(QFile::ReadOnly))) {
        xmlDoc.setContent(xmlFile.readAll());
        xmlFile.close();

        //Racine
        QDomElement xmlRoot = xmlDoc.documentElement();

        //Parse les menaces
        QDomNode xmlNxScore = xmlRoot.firstChild();
        while(!xmlNxScore.isNull()) {
            QDomElement xmlNxElement = xmlNxScore.toElement();

            if((!xmlNxElement.isNull()) && (xmlNxElement.tagName() == "NxEnv")) {
            }
            else if((!xmlNxElement.isNull()) && (xmlNxElement.tagName() == "NxCurve")) {
                execute("add curve "              + xmlNxElement.attribute("ID"));
                execute("setGroup  current group" + xmlNxElement.attribute("groupID"));
                execute("setLabel  current "      + xmlNxElement.attribute("name"));
                execute("setActive current "      + xmlNxElement.attribute("active"));
                bool isSmooth = (xmlNxElement.attribute("drawType")=="7");
                qreal scale = xmlNxElement.attribute("scale").toDouble();
                bool colorFirst = true;
                QDomNode xmlNxSub = xmlNxElement.firstChild();
                while(!xmlNxSub.isNull()) {
                    QDomElement xmlNxSubElement = xmlNxSub.toElement();
                    if((!xmlNxSubElement.isNull()) && (xmlNxSubElement.tagName() == "Position"))
                        execute("setPos current " + xmlNxSubElement.attribute("x") + " " + xmlNxSubElement.attribute("y") + " " + xmlNxSubElement.attribute("z"));
                    else if((!xmlNxSubElement.isNull()) && (xmlNxSubElement.tagName() == "NxPoint") && (!isSmooth))
                        execute("setPointAt current " + xmlNxSubElement.attribute("ID") + " " + xmlNxSubElement.attribute("x") + " " + QString::number(xmlNxSubElement.attribute("y").toDouble() * scale) + " " + xmlNxSubElement.attribute("z"));
                    else if((!xmlNxSubElement.isNull()) && (xmlNxSubElement.tagName() == "NxPoint") && (isSmooth))
                        execute("setSmoothPointAt current " + xmlNxSubElement.attribute("ID") + " " + xmlNxSubElement.attribute("x") + " " + QString::number(xmlNxSubElement.attribute("y").toDouble() * scale) + " " + xmlNxSubElement.attribute("z"));
                    else if((!xmlNxSubElement.isNull()) && (xmlNxSubElement.tagName() == "color") && (colorFirst)) {
                        execute("setColorActive        current " + xmlNxSubElement.attribute("r") + " " + xmlNxSubElement.attribute("g") + " " + xmlNxSubElement.attribute("b") + " " + xmlNxSubElement.attribute("a"));
                        execute("setColorActiveMessage current " + xmlNxSubElement.attribute("r") + " " + xmlNxSubElement.attribute("g") + " " + xmlNxSubElement.attribute("b") + " " + xmlNxSubElement.attribute("a"));
                        colorFirst = false;
                    }
                    else if((!xmlNxSubElement.isNull()) && (xmlNxSubElement.tagName() == "color")) {
                        execute("setColorInactive        current " + xmlNxSubElement.attribute("r") + " " + xmlNxSubElement.attribute("g") + " " + xmlNxSubElement.attribute("b") + " " + xmlNxSubElement.attribute("a"));
                        execute("setColorInactiveMessage current " + xmlNxSubElement.attribute("r") + " " + xmlNxSubElement.attribute("g") + " " + xmlNxSubElement.attribute("b") + " " + xmlNxSubElement.attribute("a"));
                    }
                    xmlNxSub = xmlNxSub.nextSibling();
                }
            }
            xmlNxScore = xmlNxScore.nextSibling();
        }
    }
}

void IanniX::setScheduler(SchedulerActivity _schedulerActivity) {
    schedulerActivity = _schedulerActivity;
    if(schedulerActivity != SchedulerOff) {
        timerOk = true;
        renderMeasureAbsoluteValOld = 0;
        renderMeasureAbsolute.start();
    }
    else
        timerOk = false;
    transport->setPlay_pause(getScheduler());
    timeTransportRefresh = 9999;
    if(getScheduler())
        QApplication::setWindowIcon(iconAppPause);
    else
        QApplication::setWindowIcon(iconAppPlay);
}

void IanniX::closeSplash() {
    splash->close();
    show();
}

void IanniX::show() {
    view->show();
    view->activateWindow();
}

QString IanniX::serialize() {
    return currentDocument->serialize(render->getRenderOptions(), false);
}

void IanniX::timerEvent(QTimerEvent *) {
    transport->setPerfCpu((quint16)qRound(cpu->cpu));
}
void IanniX::timerTick() {
    timerTick(false);
}
void IanniX::timerTick(bool force) {
    qreal renderMeasureAbsoluteVal = renderMeasureAbsolute.elapsed() / 1000.0F;
    qreal delta = renderMeasureAbsoluteVal - renderMeasureAbsoluteValOld;
    renderMeasureAbsoluteValOld = renderMeasureAbsoluteVal;

    //Parse MIDI
    if((midi) && (!force))
        midi->parseReceivedMessage();

    //Tick !
    if((force) || (timerOk))
        timerTick(delta);
}

void IanniX::timerTick(qreal delta) {
    if(forceTimeLocal) {
        delta = 0;
        timeTransportRefresh = 9999;
        if(schedulerActivity == SchedulerOneShot)
            setScheduler(SchedulerOff);
    }
    timeLocal += delta * render->getRenderOptions()->timeFactor;
    if(timeLocal < 0) {
        forceTimeLocal = true;
        timeLocal = 0;
        return;
    }
    timeTransportRefresh += delta;
    timePerfRefresh += delta;
    timePerfCounter++;

    //Open a bundle if necessary
    if((forceTimeLocal) && (osc))
        osc->setBundleMessageId(0);
    if(osc)
        osc->openBundle(oscBundleHost, oscBundlePort);

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
                        if(forceTimeLocal) {
                            cursor->setTimeLocal(timeLocal);
                            cursor->setMessageId(0);
                        }

                        //Set time for a cursor
                        cursor->setTime(delta * render->getRenderOptions()->timeFactor);

                        //Is cursor active ?
                        if((!forceTimeLocal) && (cursor->getActive()) && (((!isGroupSoloActive) && (group->checkState(0) == Qt::Checked)) || ((isGroupSoloActive) && (group->checkState(1) == Qt::Checked))) && (((!isObjectSoloActive) && (cursor->checkState(1) == Qt::Checked)) || ((isObjectSoloActive) && (cursor->checkState(2) == Qt::Checked))))
                            timerTrig(cursor);
                    }
                }
            }
        }
    }

    onDraw();

    //Close the bundle if necessary
    if(osc)
        osc->closeBundle();

    if(timeTransportRefresh >= 0.03) {
        timeTransportRefresh = 0;
        timeLocalStr = "";

        quint16 min = timeLocal / 60;
        if(min < 10) timeLocalStr += "00";
        else if(min < 100) timeLocalStr += "0";
        timeLocalStr += QString::number(min) + ":";

        quint8 sec = (int)floor(timeLocal) % 60;
        if(sec < 10) timeLocalStr += "0";
        timeLocalStr += QString::number(sec) + ":";

        quint16 milli = (timeLocal - floor(timeLocal)) * 1000;
        if(milli < 10)       timeLocalStr += "00";
        else if(milli < 100) timeLocalStr += "0";
        timeLocalStr += QString::number(milli);

        emit(updateTransport(timeLocalStr, lastMessage));
        lastMessageAllow = true;
    }
    if(timePerfRefresh >= 1) {
        transport->setPerfScheduler(QString::number((quint16)qRound(1000.0F*timePerfRefresh/timePerfCounter)));
        timePerfRefresh = 0;
        timePerfCounter = 0;
    }

    if(forceTimeLocal)
        forceTimeLocal = false;
}

void IanniX::timerTrig(void *object, bool force) {
    NxCursor *cursor = (NxCursor*)object;

    //Messages
    cursor->trig(force);

    //Browse groups
    foreach(const NxGroup *group, currentDocument->groups) {
        //Browse active triggers
        foreach(const NxObject *objectTrigger, group->objects[ObjectsActivityActive][ObjectsTypeTrigger]) {
            NxTrigger *trigger = (NxTrigger*)objectTrigger;

            //Check the collision
            if((cursor->contains(trigger)) && (((!isObjectSoloActive) && (trigger->checkState(1) == Qt::Checked)) || ((isObjectSoloActive) && (trigger->checkState(2) == Qt::Checked))))
                trigger->trig(cursor);
        }

        //Browse active triggers
        if(cursor->getPerformCollision()) {
            foreach(const NxObject *objectCurve, group->objects[ObjectsActivityActive][ObjectsTypeCurve]) {
                //Check the collision
                cursor->trig((NxCurve*)objectCurve);
            }
        }
    }
}

void IanniX::checkForUpdates() {
    QString url = "http://www.iannix.org/download/updates.php?id=" + QSettings().value("id").toString() + "&package=" + (QCoreApplication::applicationName() + "__" + QCoreApplication::applicationVersion()).toLower().replace(" ", "_").replace(".", "_");
    qDebug("Checking for updates %s", qPrintable(url));
    updateManager->get(QNetworkRequest(QUrl(url, QUrl::TolerantMode)));
}
void IanniX::checkForUpdatesFinished(QNetworkReply *reply) {
    if(reply->error() != QNetworkReply::NoError)
        qDebug("Network error. %s", qPrintable(reply->errorString()));
    else {
        QSettings().setValue("lastUpdate", QDateTime::currentDateTime());
        QString info = reply->readAll().trimmed();
        if(info.length() > 0) {
            int rep = (new UiMessageBox())->display(tr("IanniX Update Center"), tr("A new version of IanniX is available"), info, tr("Would you like to update IanniX with the new version ?"), QPixmap(":/infos/res_info_update.png"), QDialogButtonBox::Yes | QDialogButtonBox::No);
            if(rep)
                QDesktopServices::openUrl(QUrl("http://www.iannix.org/en/download.php", QUrl::TolerantMode));
        }
    }
}

void IanniX::actionToggle_Inspector() {
    if(inspector->isVisible()) {
        inspector->parentWidget()->hide();
        view->toggleInspector(false);
    }
    else {
        inspector->parentWidget()->show();
        view->toggleInspector(true);
    }
    view->activateWindow();;
}
void IanniX::actionToggle_Transport() {
    if(transport->isVisible()) {
        transport->parentWidget()->hide();
        view->toggleTransport(false);
    }
    else {
        transport->parentWidget()->show();
        view->toggleTransport(true);
    }
    view->activateWindow();
}
void IanniX::actionToggle_Autosize() {
    if(render->getTriggerAutosize()) {
        render->setTriggerAutosize(false);
        view->toggleAutosize(false);
    }
    else {
        render->setTriggerAutosize(true);
        view->toggleAutosize(true);
    }
}

void IanniX::actionPlay_pause() {
    if(getScheduler()) {
        setScheduler(SchedulerOff);
        sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "stop");
        midi->sendSPPStop();
    }
    else {
        setScheduler(SchedulerOn);
        sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "play");
        midi->sendSPPStart();
    }
    view->activateWindow();
}
void IanniX::actionFast_rewind() {
    if(timeLocal != 0) {
        midi->sendSPPStop();
        midi->sendSPPTime(0);
    }
    forceTimeLocal = true;
    timeLocal = 0;
    setScheduler(SchedulerOneShot);
    sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "fastrewind");
    view->activateWindow();
}

void IanniX::actionLogo() {
    about->show();
}

void IanniX::actionGoto() {
    QStringList transportTime = transport->getTime().split(":", QString::SkipEmptyParts);
    if(transportTime.count() == 2) {
        QStringList transportTime2 = transportTime.at(1).split(".", QString::SkipEmptyParts);
        if(transportTime2.count() == 2) {
            qreal milli = transportTime2.at(1).toUInt();
            qreal sec = transportTime2.at(0).toUInt();
            qreal min = transportTime.at(0).toUInt();
            actionGoto(min * 60 + sec + milli / 1000.F);
        }
    }
}
void IanniX::actionGoto(qreal gotoTime, bool midiSync) {
    timeLocal = gotoTime;
    forceTimeLocal = true;
    if(schedulerActivity == SchedulerOff)
        setScheduler(SchedulerOneShot);
    if(midiSync)
        midi->sendSPPTime(timeLocal);
}

void IanniX::actionSetScheduler() {
    QString valStr = transport->getPerfScheduler();
    quint16 val = valStr.remove("ms").toUInt();
    if(val > 0)
        timer->setInterval(val);
}
void IanniX::actionSetOpenGL() {
    QString valStr = transport->getPerfOpenGL();
    quint16 val = valStr.remove("fps").toUInt();
    if(val > 0)
        render->setInterval(1000.0F/(qreal)val);
}

void IanniX::actionSpeed() {
    render->getRenderOptions()->timeFactor = transport->getSpeed();
}

void IanniX::actionTabChange(int tab) {
    if(tab == 3)
        oscConsoleActive = true;
    else
        oscConsoleActive = false;
}
void IanniX::actionViewChange() {
    if(inspector->getViewTriggerCheck())
        render->getRenderOptions()->paintTriggers = true;
    else
        render->getRenderOptions()->paintTriggers = false;
    if(inspector->getViewCurveCheck())
        render->getRenderOptions()->paintCurves = true;
    else
        render->getRenderOptions()->paintCurves = false;
    if(inspector->getViewCursorCheck())
        render->getRenderOptions()->paintCursors = true;
    else
        render->getRenderOptions()->paintCursors = false;
    if(inspector->getViewCurveOpacityCheck())
        render->getRenderOptions()->paintCurvesOpacity = true;
    else
        render->getRenderOptions()->paintCurvesOpacity = false;
    render->getRenderOptions()->paintZStart = inspector->getViewZStart();
    render->getRenderOptions()->paintZEnd = inspector->getViewZEnd();
}
void IanniX::actionCC() {
    QList<NxObject*> objects = inspector->getSelectedCCObject();
    NxPoint center;
    quint16 centerCounter = 0;

    render->selectionClear(true);
    foreach(NxObject* object, objects) {
        render->selectionAdd(object);
        center += object->getPos();
        centerCounter++;
    }
    center /= centerCounter;
    //render->centerOn(center);

    //Is solo active ?
    isObjectSoloActive = false;
    if(currentDocument) {
        foreach(const NxGroup* group, currentDocument->groups) {
            //Browse active/inactive objects
            for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
                //Browse all types of objects
                for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                    //Browse objects
                    foreach(const NxObject *object, group->objects[activityIterator][typeIterator]) {
                        if(object->checkState(2) == Qt::Checked) {
                            isObjectSoloActive = true;
                            return;
                        }
                    }
                }
            }
        }
    }
}
void IanniX::actionCC2() {
    QList<NxGroup*> groups = inspector->getSelectedCC2Object();
    NxPoint center;
    quint16 centerCounter = 0;

    render->selectionClear(true);
    foreach(const NxGroup* group, groups) {
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

    //Is solo active ?
    isGroupSoloActive = false;
    if(currentDocument) {
        foreach(const NxGroup *group, currentDocument->groups)
            if(group->checkState(1) == Qt::Checked) {
                isGroupSoloActive = true;
                return;
            }
    }
}

void IanniX::actionChangeID(quint16 idOld, quint16 idNew) {   ////CG////
    NxObject *existingObject = 0;
    existingObject = currentDocument->getObject(idNew);
    if(existingObject) {
        inspector->changeID_success(false, 0);
    } else {
        NxObject *thisObject = 0;
        thisObject = currentDocument->getObject(idOld);
        //ADD// replace this line with: create new object and make it equal to thisObject
        currentDocument->objects[idNew] = thisObject;
        currentDocument->objects.remove(idOld);
        inspector->changeID_success(true, idNew);
    }
}

void IanniX::actionNew() {
    if(projectScore) {
        bool ok;
        QString text = (new UiMessageBox())->getText(tr("New score"), tr("Enter the name of your new score:"), "New Document " + QDateTime::currentDateTime().toString("MMddhhmmss"), &ok);
        if((ok) && (!text.isEmpty())) {
            QFileInfo newScoreDestination = QFileInfo(scriptDir.absoluteFilePath(text +  ".nxscore"));
            if(!newScoreDestination.exists()) {
                QFile::copy(QFileInfo("./Project/New Score Template.nxscore").absoluteFilePath(),  newScoreDestination.absoluteFilePath());
                fileWatcherChanged(scriptDir.path());
                inspector->setProjectFiles(text);
                actionProjectFiles();
            }
            else
                (new UiMessageBox())->display(tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QDialogButtonBox::Ok);
        }
    }
}

void IanniX::actionNewScript() {
    if(projectScore) {
        bool ok;
        QString text = (new UiMessageBox())->getText(tr("New script"), tr("Enter the name of your new script:"), "New Script " + QDateTime::currentDateTime().toString("MMddhhmmss"), &ok);
        if((ok) && (!text.isEmpty())) {
            QFileInfo newScriptDestination = QFileInfo(scriptDir.absoluteFilePath(text +  ".nxscript"));
            if(!newScriptDestination.exists()) {
                QFile::copy(QFileInfo("./Project/New Script Template.nxscript").absoluteFilePath(), newScriptDestination.absoluteFilePath());
                fileWatcherChanged(scriptDir.path());
                inspector->setProjectScripts(text);
                actionProjectScripts();
            }
            else
                (new UiMessageBox())->display(tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QDialogButtonBox::Ok);
        }
    }
}


void IanniX::actionOpen() {
    QString fileName = QFileDialog::getExistingDirectory(0, tr("Open IanniX Project Folder"), baseDocumentDir);
    if(!fileName.isEmpty())
        loadProject(fileName + QString(QDir::separator()));
}
void IanniX::actionSave() {
    if(currentDocument) {
        if(!currentDocument->save(render->getRenderOptions()))
            actionSave_as();
    }
}
void IanniX::actionSave_as() {

}
void IanniX::actionRename() {
    if(currentDocument) {
        bool ok;
        ExtScriptManager *fileList = (ExtScriptManager*)inspector->getProjectFiles()->currentItem();
        QString text = (new UiMessageBox())->getText(tr("File rename"), tr("New name of script:"), fileList->getScriptFile().baseName(), &ok);
        QString f = fileList->getScriptFile().absoluteFilePath().replace(fileList->getScriptFile().baseName()+".", text+".");
        if((ok) && (!f.isEmpty())) {
            if(!QFile::exists(f)) {
                QFile::rename(fileList->getScriptFile().absoluteFilePath(), f);
            }
            else {
                (new UiMessageBox())->display(tr("Filename conflict"), tr("The file can't be renamed! A file with this name exists in your project."), QDialogButtonBox::Ok);
            }
        }
    }
}
void IanniX::actionRemove() {
    ExtScriptManager *fileList = (ExtScriptManager*)inspector->getProjectFiles()->currentItem();
    if(currentDocument) {
        int rep = (new UiMessageBox())->display(tr("File remove"), tr("The file will be removed from your disk. Are you sure?"), QDialogButtonBox::Yes | QDialogButtonBox::No);
        if(rep)
            QFile::remove(fileList->getScriptFile().absoluteFilePath());
    }
}
void IanniX::actionDuplicateScore() {
    if(currentDocument) {
        bool ok;
        QString text = (new UiMessageBox())->getText(tr("File duplication"), tr("Enter the desired name of the duplicated score"), currentDocument->getScriptFile().baseName(), &ok);
        if((ok) && (!text.isEmpty())) {
            currentDocument->setNewFilename(currentDocument->getScriptFile().absoluteFilePath().replace(currentDocument->getScriptFile().baseName()+".", text+"."));
            currentDocument->save(render->getRenderOptions());
        }
    }
}

void IanniX::actionSave_all() {
    foreach(NxDocument *document, documents)
        document->save(render->getRenderOptions());
}
void IanniX::actionProjectFiles() {
    if(inspector->getProjectFiles()->currentItem()->type() == 1024) {
        NxDocument *scriptList = (NxDocument*)inspector->getProjectFiles()->currentItem();
        if(scriptList) {
            currentDocument = scriptList;
            render->setDocument(currentDocument);
            currentDocument->load();
            render->selectionClear(true);
            if((currentScript) && (currentDocument))
                view->setWindowTitle(tr("IanniX") + QString(" - %2 / %1").arg(currentDocument->getScriptFile().baseName()).arg(currentScript->getScriptFile().baseName()));
            else if(currentDocument)
                view->setWindowTitle(tr("IanniX") + QString(" / %1").arg(currentDocument->getScriptFile().baseName()));
            else
                view->setWindowTitle(tr("IanniX"));
            actionGoto(timeLocal);
        }
    }
}
void IanniX::actionProjectScripts() {
    if((inspector->getProjectScripts()->currentItem()->type() == 1024) && (currentDocument)) {
        currentScript = (ExtScriptManager*)inspector->getProjectScripts()->currentItem();
        actionProjectScript();
    }
}
void IanniX::actionProjectScript() {
    if(currentScript) {
        pushSnapshot();
        currentScript->parseScript();
        if(!activeScripts.contains(currentScript))
            activeScripts.append(currentScript);
        render->selectionClear(true);
        editor->openFile(currentScript->getScriptFile());
        view->activateWindow();
        if((currentScript) && (currentDocument))
            view->setWindowTitle(tr("IanniX") + QString(" - %2 / %1").arg(currentDocument->getScriptFile().baseName()).arg(currentScript->getScriptFile().baseName()));
        else if(currentDocument)
            view->setWindowTitle(tr("IanniX") + QString(" / %1").arg(currentDocument->getScriptFile().baseName()));
        else
            view->setWindowTitle(tr("IanniX"));
        actionGoto(timeLocal);
    }
}

void IanniX::actionProjectFilesContext(const QPoint & point) {   ///CG///
    if((inspector->getProjectFiles()->currentItem()->type() == 1024) && (currentDocument)) {
        ExtScriptManager *fileList = (ExtScriptManager*)inspector->getProjectFiles()->currentItem();
        if(fileList) {
            QMenu menu(view);
            QAction *openProject   = menu.addAction(tr("Open a project"));
            QAction *newFile       = menu.addAction(tr("New"));
            QAction *duplicateFile = menu.addAction(tr("Duplicate"));
            QAction *renameFile    = menu.addAction(tr("Rename"));
            QAction *removeFile    = menu.addAction(tr("Remove"));
            QAction *ret = menu.exec(inspector->getProjectFiles()->mapToGlobal(point));
            openProject->setStatusTip  (tr("Click here to open a project folder"));
            newFile->setStatusTip      (tr("Click here to create a new score"));
            duplicateFile->setStatusTip(tr("Click here to duplicate the score to a new one"));
            renameFile->setStatusTip   (tr("Click here to rename the score"));
            removeFile->setStatusTip   (tr("Click here to remove the score from project folder"));

            if (ret == openProject)
                actionOpen();
            else {
                if (ret == newFile)
                    actionNew();
                else if (ret == duplicateFile) {
                    if(currentDocument) {
                        bool ok;
                        QString text = (new UiMessageBox())->getText(tr("File duplication"), tr("Name of duplicate script:"), fileList->getScriptFile().baseName(), &ok);
                        QString f = fileList->getScriptFile().absoluteFilePath().replace(fileList->getScriptFile().baseName()+".", text+".");
                        if((ok) && (!f.isEmpty())) {
                            if(!QFile::exists(f))
                                QFile::copy(fileList->getScriptFile().absoluteFilePath(), f);
                            else
                                (new UiMessageBox())->display(tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QDialogButtonBox::Ok);
                        }
                    }
                }
                else if (ret == renameFile)
                    actionRename();
                else if (ret == removeFile)
                    actionRemove();
                QDir examplesDir("./Examples/");
                QDir libDir("./Tools/");
                QDir projectDir(baseDocumentDir);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", libDir, libScript, false);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", examplesDir, exampleScript, false);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", projectDir, projectScript, false);
            }
        }
    }
}


void IanniX::actionProjectScriptsContext(const QPoint & point) {   ///CG///
    if((inspector->getProjectScripts()->currentItem()->type() == 1024) && (currentDocument)) {
        ExtScriptManager *scriptList = (ExtScriptManager*)inspector->getProjectScripts()->currentItem();
        if(view) {
            QMenu menu(view);
            QAction *runFile          = menu.addAction(tr("Run"));
            QAction *openFile         = menu.addAction(tr("Open"));
            QAction *externalOpenFile = menu.addAction(tr("Open with default external editor"));
            QAction *newFile          = menu.addAction(tr("New"));
            QAction *duplicateFile    = menu.addAction(tr("Duplicate"));
            QAction *renameFile       = menu.addAction(tr("Rename"));
            QAction *removeFile       = menu.addAction(tr("Remove"));
            runFile->setStatusTip      (tr("Click here to run this script"));
            runFile->setStatusTip      (tr("Click here to open a project folder"));
            newFile->setStatusTip      (tr("Click here to create a new script"));
            duplicateFile->setStatusTip(tr("Click here to duplicate the script to a new one"));
            renameFile->setStatusTip   (tr("Click here to rename the script"));
            removeFile->setStatusTip   (tr("Click here to remove the script from project folder"));

            QAction *ret = menu.exec(inspector->getProjectScripts()->mapToGlobal(point));

            if(ret == runFile)
                actionProjectScripts();
            else if (ret == openFile)
                editor->openFile(scriptList->getScriptFile());
            else if (ret == externalOpenFile) {
                fileWatcher.addPath(scriptList->getScriptFile().absoluteFilePath());
                QDesktopServices::openUrl(QUrl("file:///" + scriptList->getScriptFile().absoluteFilePath().replace("\\", "/"), QUrl::TolerantMode));
            }
            else {
                if (ret == newFile)
                    actionNewScript();
                else if (ret == duplicateFile) {
                    if(currentDocument) {
                        bool ok;
                        QString text = (new UiMessageBox())->getText(tr("File duplication"), tr("Name of duplicate script:"), scriptList->getScriptFile().baseName(), &ok);
                        QString f = scriptList->getScriptFile().absoluteFilePath().replace(scriptList->getScriptFile().baseName()+".", text+".");
                        if((ok) && (!f.isEmpty())) {
                            if(!QFile::exists(f))
                                QFile::copy(scriptList->getScriptFile().absoluteFilePath(), f);
                            else
                                (new UiMessageBox())->display(tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QDialogButtonBox::Ok);
                        }
                    }
                }
                else if (ret == renameFile) {
                    if(currentDocument) {
                        bool ok;
                        QString text = (new UiMessageBox())->getText(tr("File rename"), tr("New name of script:"), scriptList->getScriptFile().baseName(), &ok);
                        QString f = scriptList->getScriptFile().absoluteFilePath().replace(scriptList->getScriptFile().baseName()+".", text+".");
                        if((ok) && (!f.isEmpty())) {
                            if(!QFile::exists(f))
                                QFile::rename(scriptList->getScriptFile().absoluteFilePath(), f);
                            else
                                (new UiMessageBox())->display(tr("Filename conflict"), tr("The file can't be renamed! A file with this name exists in your project."), QDialogButtonBox::Ok);
                        }
                    }
                }
                else if (ret == removeFile) {
                    if(currentDocument) {
                        int rep = (new UiMessageBox())->display(tr("File remove"), tr("The file will be removed from your disk. Are you sure?"), QDialogButtonBox::Yes | QDialogButtonBox::No);
                        if(rep)
                            QFile::remove(scriptList->getScriptFile().absoluteFilePath());
                    }
                }
                QDir examplesDir("./Examples/");
                QDir libDir("./Tools/");
                QDir projectDir(baseDocumentDir);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", libDir, libScript, false);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", examplesDir, exampleScript, false);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", projectDir, projectScript, false);
            }
        }
    }
}




NxGroup* IanniX::addGroup(const QString & documentId, const QString & groupId) {
    NxGroup *group = new NxGroup(this, inspector->getViewGroup(), Qt::Checked);
    inspector->getViewGroup()->sortItems(0, Qt::AscendingOrder);
    group->setId(groupId);
    documents.value(documentId)->groups[group->getId()] = group;
    documents.value(documentId)->setCurrentGroup(group);
    return group;
}


void IanniX::setObjectActivity(void *_object, quint8 activeOld) {
    //Extract object
    NxObject *object = (NxObject*)_object;

    //Add a group if not allocated
    if(!documents.value(object->getDocumentId())->groups.contains(object->getGroupId()))
        addGroup(object->getDocumentId(), object->getGroupId());

    //Move object
    documents.value(object->getDocumentId())->groups.value(object->getGroupId())->objects[activeOld][object->getType()].remove(object->getId());
    documents.value(object->getDocumentId())->groups.value(object->getGroupId())->objects[object->getActive()][object->getType()].insert(object->getId(), object);
}
void IanniX::setObjectGroupId(void *_object, const QString & groupIdOld) {
    //Extract object
    NxObject *object = (NxObject*)_object;

    //Add a group if not allocated
    if(!documents.value(object->getDocumentId())->groups.contains(object->getGroupId()))
        addGroup(object->getDocumentId(), object->getGroupId());

    //Move object
    documents.value(object->getDocumentId())->groups.value(object->getGroupId())->objects[object->getActive()][object->getType()].insert(object->getId(), object);

    //Remove a group if empty
    if(documents.value(object->getDocumentId())->groups.contains(groupIdOld)) {
        documents.value(object->getDocumentId())->groups.value(groupIdOld)->objects[object->getActive()][object->getType()].remove(object->getId());
        if(documents.value(object->getDocumentId())->groups.value(groupIdOld)->getCount() == 0) {
            NxGroup *group = documents.value(object->getDocumentId())->groups.value(groupIdOld);
            documents.value(object->getDocumentId())->groups.remove(groupIdOld);
            delete group;
        }
    }
}

void IanniX::removeObject(NxObject *object) {
    if(object) {
        if(render)
            render->flagIsRemoving();

        if(object->getType() == ObjectsTypeCurve) {
            NxCurve *curve = (NxCurve*)object;
            QStringList commands;
            foreach(const NxObject *object, curve->getCursors())
                commands << COMMAND_REMOVE + " " + QString::number(object->getId()) + COMMAND_END;
            foreach(const QString & command, commands) {
                execute(command);
            }
        }
        else if(object->getType() == ObjectsTypeCursor) {
            NxCurve *curve = ((NxCursor*)object)->getCurve();
            if(curve)
                curve->removeCursor(object);
        }

        //Remove the object
        documents.value(object->getDocumentId())->groups.value(object->getGroupId())->objects[object->getActive()][object->getType()].remove(object->getId());
        documents.value(object->getDocumentId())->objects.remove(object->getId());


        ////CG////  If the deleted object is selected in CC or CC2 we crash, make sure nothing is selected
        // Note: might be better to only deselect the object in CC and/or the group in CC2 but clearing the entire selection is good enough for now
        inspector->clearCCselections();

        //Remove groups
        if(documents.value(object->getDocumentId())->groups.value(object->getGroupId())->getCount() == 0) {
            NxGroup *group = documents.value(object->getDocumentId())->groups.value(object->getGroupId());
            documents.value(object->getDocumentId())->groups.remove(object->getGroupId());
            delete group;
        }

        render->selectionClear(true);

        delete object;
    }
}


const QVariant IanniX::execute(const QString & command, bool createNewObjectIfExists, bool) {
    QStringList argv = command.split(" ", QString::SkipEmptyParts);
    quint16 argc = argv.count();
    if((argc > 0) && (currentDocument)) {
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

            //Répétiteur de message
            //QString commandReplace = command;
            //sendMessage(syncObject, 0, 0, 0, NxPoint(), NxPoint(), commandReplace.replace("auto", QString::number(id)));

            NxObject *object = 0;
            QString type = argv.at(1).toLower();
            if(type == "curve")         object = new NxCurve(this,   inspector->getCurveItem(),   render->getRenderOptions());
            else if(type == "cursor")   object = new NxCursor(this,  inspector->getCursorItem(),  render->getRenderOptions());
            else                        object = new NxTrigger(this, inspector->getTriggerItem(), render->getRenderOptions());

            if(object) {
                object->dispatchProperty("documentId", currentDocument->getId());
                object->dispatchProperty("groupId", "");
                object->dispatchProperty("id", id);
                object->dispatchProperty("active", ObjectsActivityActive);
                object->dispatchProperty("posStr", "0 0");
                if(object->getType() == ObjectsTypeTrigger)     object->dispatchProperty("messagePatterns",  "1," + defaultMessageTrigger);
                else if(object->getType() == ObjectsTypeCursor) object->dispatchProperty("messagePatterns", "20," + defaultMessageCursor);
                object->setParentObject(parentObject);

                if(parentObject) {
                    NxPoint posOffset(0.5, -0.5);
                    object->setPosOffset(posOffset);
                }
                currentDocument->objects[id] = object;
                currentDocument->setCurrentObject(object);
                return object->getId();
            }
            else
                return 0;
        }
        else {
            if(commande == COMMAND_TEXTURE) {
                if(argc > 6) {
                    QString filename = argvFullString(command, argv, 6);
                    if(!QFile().exists(filename))
                        filename = scriptDir.absoluteFilePath(filename);
                    render->loadTexture(UiRenderTexture(argv.at(1).trimmed(), filename, NxRect(NxPoint(argvDouble(argv, 2), argvDouble(argv, 3)), NxPoint(argvDouble(argv, 4), argvDouble(argv, 5)))));
                    currentDocument->registredTextures[argv.at(1)] = command.trimmed();
                    return true;
                }
                return false;
            }
            else if(commande == COMMAND_GLOBAL_COLOR) {
                if(argc > 5) {
                    render->getRenderOptions()->colors[argv.at(1)] = QColor(argvDouble(argv, 2), argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5));
                    currentDocument->registredColors[argv.at(1)] = command.trimmed();
                    return true;
                }
                return false;
            }
            else if((commande == COMMAND_GLOBAL_COLOR2) || (commande == COMMAND_GLOBAL_COLOR_HUE)) {
                if(argc > 5) {
                    QColor color;
                    color.setHsv(argvDouble(argv, 2), argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5));
                    render->getRenderOptions()->colors[argv.at(1)] = color;
                    currentDocument->registredColors[argv.at(1)] = command.trimmed();
                    return true;
                }
                return false;
            }
            else if(commande == COMMAND_ZOOM) {
                if(argc > 1)
                    render->zoom(argvDouble(argv, 1));
                return render->getRenderOptions()->zoomValue;
            }
            else if(commande == COMMAND_LOAD) {
                if(argc > 1) {
                    QString filename = argvFullString(command, argv, 1);
                    bool ok = false;
                    ok = inspector->setProjectFiles(filename);
                    if(inspector->setProjectFiles(filename))
                        actionProjectFiles();
                    else if(inspector->setProjectScripts(filename))
                        actionProjectScripts();
                }
                return view->windowTitle();
            }
            else if(commande == COMMAND_SNAPSHOT) {
                if(argc > 2) {
                    render->captureFrame(argvDouble(argv, 1), argvFullString(command, argv, 2));
                    return true;
                }
                else if(argc > 1) {
                    render->captureFrame(argvDouble(argv, 1));
                    return true;
                }
                return false;
            }
            else if(commande == COMMAND_VIEWPORT) {
                if(argc > 2)
                    view->actionResize(QSize(argvDouble(argv, 1), argvDouble(argv, 2)));
                return QString("%1 %2").arg(render->size().width()).arg(render->size().height());
            }
            else if(commande == COMMAND_ROTATE){
                if(argc > 4)
                    render->rotateTo(NxPoint(argvDouble(argv, 1),argvDouble(argv, 2),argvDouble(argv, 3)), true);
                else if(argc > 1)
                    render->rotateTo(NxPoint(argvDouble(argv, 1),argvDouble(argv, 2),argvDouble(argv, 3)));
                return QString("%1 %2 %3").arg(render->getRenderOptions()->rotation.x()).arg(render->getRenderOptions()->rotation.y()).arg(render->getRenderOptions()->rotation.z());
            }
            else if(commande == COMMAND_CENTER) {
                if(argc > 3)
                    render->centerOn(NxPoint(argvDouble(argv, 1), argvDouble(argv, 2)), true);
                else if(argc > 1)
                    render->centerOn(NxPoint(argvDouble(argv, 1), argvDouble(argv, 2)));
                return QString("%1 %2").arg(render->getRenderOptions()->axisCenter.x()).arg(render->getRenderOptions()->axisCenter.y());
            }
            else if(commande == COMMAND_PLAY) {
                if(argc > 1) {
                    qreal speed = argvDouble(argv, 1);
                    if(speed != 0) {
                        transport->setSpeed(speed);
                        if(schedulerActivity != SchedulerOn) {
                            setScheduler(SchedulerOn);
                            sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "play");
                            midi->sendSPPStart();
                        }
                    }
                    else {
                        if(schedulerActivity != SchedulerOff) {
                            setScheduler(SchedulerOff);
                            sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "stop");
                            midi->sendSPPStop();
                        }
                    }
                    actionSpeed();
                    return "";
                }
                else if(schedulerActivity != SchedulerOn) {
                    setScheduler(SchedulerOn);
                    sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "play");
                    midi->sendSPPStart();
                    return "";
                }
                return "";
            }
            else if(commande == COMMAND_TITLE) {
                return view->windowTitle();
            }
            else if(commande == COMMAND_STOP) {
                if(schedulerActivity != SchedulerOff) {
                    setScheduler(SchedulerOff);
                    sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "stop");
                    midi->sendSPPStop();
                    return "";
                }
                return "";
            }
            else if(commande == COMMAND_GOTO) {
                if(argc > 1) {
                    actionGoto(argvDouble(argv, 1));
                    timerTick(true);
                }
                return timeLocal;
            }
            else if(commande == COMMAND_SLEEP) {
                if(argc > 1) {
                    QMutex mutex;
                    QWaitCondition sleep;
                    sleep.wait(&mutex, argvDouble(argv, 1));
                    return true;
                }
                return false;
            }
            else if(commande == COMMAND_FF) {
                actionFast_rewind();
                return "";
            }
            else if(commande == COMMAND_LOG) {
                if(argc > 1) {
                    lastMessage = argvFullString(command, argv, 1);
                    logOscReceive(tr("Script:") + QString(" %1").arg(lastMessage));
                }
                return lastMessage;
            }
            else if(commande == COMMAND_CLEAR) {
                pushSnapshot();
                currentDocument->clear();
                return true;
            }
            else if(commande == COMMAND_SNAP_PUSH) {
                if(argc > 1)    currentDocument->pushSnapshot(argvFullString(command, argv, 1));
                else            currentDocument->pushSnapshot();
            }
            else if(commande == COMMAND_SNAP_POP) {
                render->selectionClear(true);
                if(argc > 1)    currentDocument->popSnapshot(argvFullString(command, argv, 1));
                else            currentDocument->popSnapshot();
                return true;
            }
            else if(commande == COMMAND_SPEED) {
                if(argc > 1)
                    transport->setSpeed(argvDouble(argv, 1));
                return transport->getSpeed();
            }
            else if((commande == COMMAND_SOLO) || (commande == COMMAND_MUTE)) {
                if(argc > 1) {
                    QString key = argv.at(1);
                    bool ok = false;
                    quint16 objectId = key.toUInt(&ok);
                    if(ok) {
                        NxObject *object = currentDocument->getObject(objectId);
                        if(object) {
                            if(argc > 2) {
                                object->setCheckState((commande == COMMAND_MUTE)?(1):(2), (argvDouble(argv, 2))?(Qt::Checked):(Qt::Unchecked));
                                actionCC();
                            }
                            else
                                return (object->checkState((commande == COMMAND_MUTE)?(1):(2)) == Qt::Checked)?(1):(0);
                        }
                    }
                    else {
                        NxGroup *group = currentDocument->getGroup(key);
                        if(group) {
                            if(argc > 2) {
                                group->setCheckState((commande == COMMAND_MUTE)?(0):(1), (argvDouble(argv, 2))?(Qt::Checked):(Qt::Unchecked));
                                actionCC2();
                            }
                            else
                                return (group->checkState((commande == COMMAND_MUTE)?(0):(1)) == Qt::Checked)?(1):(0);
                        }
                    }
                }
                return -1;
            }
            else if(commande == COMMAND_MOUSE) {
                if(argc > 1)
                    QCursor::setPos(argvDouble(argv, 1), argvDouble(argv, 2));
                return QString("%1 %2").arg(QCursor::pos().x()).arg(QCursor::pos().y());
            }
            else if(commande == COMMAND_MESSAGE_SEND) {
                if(argc > 1) {
                    QString mess = "1," + argvFullString(command, argv, 1);
                    NxTrigger *obj = new NxTrigger(this, 0, 0);
                    //qDebug("%s", qPrintable(mess));
                    obj->setMessagePatterns(mess);
                    obj->trig(0);
                    delete obj;
                    return true;
                }
                return false;
            }
            else if(commande == COMMAND_AUTOSIZE) {
                if(argc > 1) {
                    render->setTriggerAutosize(argvDouble(argv, 1));
                    view->toggleAutosize(argvDouble(argv, 1));
                }
                return render->getTriggerAutosize();
            }
            else if(argc > 1) {
                NxObjectDispatchProperty *object = getObject(argv.at(1));

                if(object) {
                    if(commande == COMMAND_REMOVE) {
                        if((object->getType() == ObjectsTypeCursor) || (object->getType() == ObjectsTypeCurve) || (object->getType() == ObjectsTypeTrigger)) {
                            removeObject((NxObject*)object);
                            return true;
                        }
                        return false;
                    }
                    if(commande == COMMAND_GROUP) {
                        if((object->getType() == ObjectsTypeCursor) || (object->getType() == ObjectsTypeCurve) || (object->getType() == ObjectsTypeTrigger)) {
                            if(argc > 2) {
                                NxObject *objectObj = (NxObject*)object;
                                QString groupId = argv.at(2);
                                if(groupId.isEmpty())
                                    groupId = documents[objectObj->getDocumentId()]->getCurrentGroup()->getId();
                                objectObj->dispatchProperty("groupId", groupId);
                            }
                            return object->getProperty("groupId");
                        }
                        return "";
                    }
                    if(commande == COMMAND_CURSOR_CURVE) {
                        if(object->getType() == ObjectsTypeCursor) {
                            NxCursor *cursor  = (NxCursor*)object;
                            if(argc > 2) {
                                NxObject *object2 = (NxObject*)getObject(argv.at(2), false);
                                if((object2) && (object2->getType() == ObjectsTypeCurve)) {
                                    NxCurve *curve = (NxCurve*)object2;
                                    cursor->setCurve(curve);
                                    cursor->calculate();
                                }
                            }
                            NxCurve *curve = cursor->getCurve();
                            if(curve)
                                return curve->getId();
                        }
                        return 0;
                    }
                    else if(commande == COMMAND_LABEL) {
                        if(argc > 2)
                            object->dispatchProperty("label", argvFullString(command, argv, 2));
                        return object->getProperty("label");
                    }

                    else if(commande == COMMAND_RESIZE) {
                        if(argc > 3)
                            object->dispatchProperty("resizeStr", argv.at(2) + " " + argv.at(3));
                        return object->getProperty("resizeStr");
                    }
                    else if(commande == COMMAND_RESIZEF) {
                        if(argc > 2)
                            object->dispatchProperty("resizeF", argvDouble(argv, 2));
                        return object->getProperty("resizeF");
                    }
                    else if(commande == COMMAND_CURSOR_WIDTH) {
                        if(argc > 2)
                            object->dispatchProperty("cursorWidth", argvDouble(argv, 2));
                        return object->getProperty("cursorWidth");
                    }
                    else if(commande == COMMAND_CURSOR_DEPTH) {
                        if(argc > 2)
                            object->dispatchProperty("cursorDepth", argvDouble(argv, 2));
                        return object->getProperty("cursorDepth");
                    }

                    else if(commande == COMMAND_LINE) {
                        if(argc > 3) {
                            object->dispatchProperty("lineStipple", argvDouble(argv, 2));
                            object->dispatchProperty("lineFactor", argvDouble(argv, 3));
                        }
                        return object->getProperty("lineStipple").toString() + " " + object->getProperty("lineFactor").toString();
                    }
                    else if(commande == COMMAND_SIZE) {
                        if(argc > 2)
                            object->dispatchProperty("size", argvDouble(argv, 2));
                        return object->getProperty("size");
                    }

                    else if(commande == COMMAND_CURSOR_START) {
                        if(argc > 4) {
                            object->dispatchProperty("easingStart", argvDouble(argv, 2));
                            object->dispatchProperty("start", argvFullString(command, argv, 4));
                        }
                        return object->getProperty("easingStart").toString() + " " + object->getProperty("start").toString();
                    }

                    else if(commande == COMMAND_CURSOR_SPEED) {
                        if(argc > 2) {
                            if((argc > 3) && (argv.at(2).toLower() == "auto"))
                                object->dispatchProperty("timeFactorAuto", argvDouble(argv, 3));
                            else
                                object->dispatchProperty("timeFactor", argvDouble(argv, 2));
                        }
                        return object->getProperty("timeFactor");
                    }
                    else if(commande == COMMAND_CURSOR_SPEEDF) {
                        if(argc > 2)
                            object->dispatchProperty("timeFactorF", argvDouble(argv, 2));
                        return object->getProperty("timeFactorF");
                    }
                    else if(commande == COMMAND_CURSOR_OFFSET) {
                        if(argc > 4) {
                            object->dispatchProperty("timeInitialOffset", argvDouble(argv, 2));
                            object->dispatchProperty("timeStartOffset",   argvDouble(argv, 3));
                            if(argv.at(4).toLower() == "end")   object->dispatchProperty("timeEndOffset", 0);
                            else                                object->dispatchProperty("timeEndOffset", argvDouble(argv, 4));
                        }
                        return object->getProperty("timeInitialOffset").toString() + " " + object->getProperty("timeStartOffset").toString() + " " + object->getProperty("timeEndOffset").toString();
                    }
                    else if(commande == COMMAND_CURSOR_BOUNDS_SOURCE) {
                        object->dispatchProperty("boundsSource", argvFullString(command, argv, 2));
                        return object->getProperty("boundsSource");
                    }
                    else if(commande == COMMAND_CURSOR_BOUNDS_TARGET) {
                        object->dispatchProperty("boundsTarget", argvFullString(command, argv, 2));
                        return object->getProperty("boundsTarget");
                    }
                    else if(commande == COMMAND_CURSOR_TIME) {
                        if(argc > 2)
                            object->dispatchProperty("timeLocal", argvDouble(argv, 2));
                        return object->getProperty("timeLocal");
                    }
                    else if(commande == COMMAND_CURSOR_TIME_PERCENT) {
                        if(argc > 2)
                            object->dispatchProperty("timeLocalPercent", argvDouble(argv, 2));
                        return object->getProperty("timeLocalPercent");
                    }
                    else if(commande == COMMAND_CURVE_INERTIE) {
                        if(argc > 2)
                            object->dispatchProperty("inertie", argvDouble(argv, 2));
                        return object->getProperty("inertie");
                    }
                    else if(commande == COMMAND_CURVE_POINT_RMV) {
                        if((argc > 2) && (object->getType() == ObjectsTypeCurve)) {
                            ((NxCurve*)object)->removePointAt(argvDouble(argv, 2));
                            return true;
                        }
                        return false;
                    }
                    else if(commande == COMMAND_CURVE_POINT_SHIFT) {
                        if((argc > 3) && (object->getType() == ObjectsTypeCurve)) {
                            ((NxCurve*)object)->shiftPointAt(argvDouble(argv, 2), argvDouble(argv, 3));
                            return true;
                        }
                        return false;
                    }
                    else if(commande == COMMAND_CURVE_POINT_TRANSLATE) {
                        if((argc > 2) && (object->getType() == ObjectsTypeCurve)) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->translate(NxPoint(argvDouble(argv, 2), argvDouble(argv, 3), argvDouble(argv, 4)));
                            return true;
                        }
                        return false;
                    }
                    else if(commande == COMMAND_CURVE_POINT_TRANSLATE2) {
                        if((argc > 2) && (object->getType() == ObjectsTypeCurve)) {
                            NxCurve *curve = (NxCurve*)object;
                            quint16 indexPoint = argvDouble(argv, 2);
                            if(indexPoint < curve->getPathPointsCount())
                                curve->translatePoint(indexPoint, NxPoint(argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5)));
                            NxCurvePoint pt = curve->getPathPointsAt(indexPoint);
                            return QString("%1 %2 %3  %4 %5 %6  %7 %8 %9").arg(pt.x()).arg(pt.y()).arg(pt.z()).arg(pt.c1.x()).arg(pt.c1.y()).arg(pt.c1.z()).arg(pt.c2.x()).arg(pt.c2.y()).arg(pt.c2.z());
                        }
                        return "0 0 0  0 0 0  0 0 0";
                    }
                    else if((commande == COMMAND_CURVE_POINT_X) || (commande == COMMAND_CURVE_POINT_Y) || (commande == COMMAND_CURVE_POINT_Z)) {
                        if((argc > 2) && (object->getType() == ObjectsTypeCurve)) {
                            NxCurve *curve = (NxCurve*)object;
                            quint16 indexPoint = argvDouble(argv, 2);
                            if(indexPoint < curve->getPathPointsCount()) {
                                NxCurvePoint ptAt = curve->getPathPointsAt(indexPoint);
                                if(commande == COMMAND_CURVE_POINT_X)   curve->setPointAt(indexPoint, NxPoint(argvDouble(argv, 3), ptAt.y(), ptAt.z()), ptAt.c1, ptAt.c2, ptAt.smooth);
                                if(commande == COMMAND_CURVE_POINT_Y)   curve->setPointAt(indexPoint, NxPoint(ptAt.x(), argvDouble(argv, 3), ptAt.z()), ptAt.c1, ptAt.c2, ptAt.smooth);
                                if(commande == COMMAND_CURVE_POINT_Z)   curve->setPointAt(indexPoint, NxPoint(ptAt.x(), ptAt.y(), argvDouble(argv, 3)), ptAt.c1, ptAt.c2, ptAt.smooth);
                                NxCurvePoint pt = curve->getPathPointsAt(indexPoint);
                                return QString("%1 %2 %3  %4 %5 %6  %7 %8 %9").arg(pt.x()).arg(pt.y()).arg(pt.z()).arg(pt.c1.x()).arg(pt.c1.y()).arg(pt.c1.z()).arg(pt.c2.x()).arg(pt.c2.y()).arg(pt.c2.z());
                            }
                        }
                        return "0 0 0  0 0 0  0 0 0";
                    }

                    else if(commande == COMMAND_CURVE_POINT) {
                        bool recalculate = true;
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            quint16 indexPoint = argvDouble(argv, 2);
                            if(argc >= 21)  // 3+18 (x, y, z, sx, sy, sz), (c1x, c1y, c1z, c1sx, c1sy, c1sz), (c2x, c2y, c2z, c2sx, c2sy, c2z)
                                curve->setPointAt(indexPoint,
                                                  NxPoint(argvDouble(argv, 3),  argvDouble(argv, 4),  argvDouble(argv, 5),  argvDouble(argv, 6),  argvDouble(argv, 7),  argvDouble(argv, 8)),
                                                  NxPoint(argvDouble(argv, 9),  argvDouble(argv, 10), argvDouble(argv, 11), argvDouble(argv, 12), argvDouble(argv, 13), argvDouble(argv, 14)),
                                                  NxPoint(argvDouble(argv, 15), argvDouble(argv, 16), argvDouble(argv, 17), argvDouble(argv, 18), argvDouble(argv, 19), argvDouble(argv, 20)), false, recalculate);
                            else if(argc >= 15)  // 3+12 (x, y, sx, sy), (c1x, c1y, c1sx, c1sy), (c2x, c2y, c2sx, c2sy)
                                curve->setPointAt(indexPoint,
                                                  NxPoint(argvDouble(argv, 3),  argvDouble(argv, 4),  0, argvDouble(argv, 5),  argvDouble(argv, 6),  0),
                                                  NxPoint(argvDouble(argv, 7),  argvDouble(argv, 8),  0, argvDouble(argv, 9),  argvDouble(argv, 10), 0),
                                                  NxPoint(argvDouble(argv, 11), argvDouble(argv, 12), 0, argvDouble(argv, 13), argvDouble(argv, 14), 0), false, recalculate);
                            else if(argc >= 12) // 3+9 (x, y, z), (c1x, c1y, c1z), (c2x, c2y, c2z)
                                curve->setPointAt(indexPoint,
                                                  NxPoint(argvDouble(argv, 3), argvDouble(argv, 4),  argvDouble(argv, 5)),
                                                  NxPoint(argvDouble(argv, 6), argvDouble(argv, 7),  argvDouble(argv, 8)),
                                                  NxPoint(argvDouble(argv, 9), argvDouble(argv, 10), argvDouble(argv, 11)), false, recalculate);
                            else if(argc >= 10) // 3+6+1 (x, y, z, sx, sy, sz) // REQUIRES A DUMMY ARGUMENT
                                curve->setPointAt(indexPoint, NxPoint(argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5), argvDouble(argv, 6), argvDouble(argv, 7), argvDouble(argv, 8)), false, recalculate);
                            else if(argc >= 9)  // 3+6 (x, y), (c1x, c1y), (c2x, c2y)
                                curve->setPointAt(indexPoint,
                                                  NxPoint(argvDouble(argv, 3), argvDouble(argv, 4)),
                                                  NxPoint(argvDouble(argv, 5), argvDouble(argv, 6)),
                                                  NxPoint(argvDouble(argv, 7), argvDouble(argv, 8)), false, recalculate);
                            else if(argc >= 7) // 3+4 (x, y, sx, sy)
                                curve->setPointAt(indexPoint, NxPoint(argvDouble(argv, 3), argvDouble(argv, 4), 0, argvDouble(argv, 5), argvDouble(argv, 6), 0), false, recalculate);
                            else if(argc >= 6) // 3+3 (x, y, z)
                                curve->setPointAt(indexPoint, NxPoint(argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5)), false, recalculate);
                            else if(argc >= 5) // 3+2 (x, y)
                                curve->setPointAt(indexPoint, NxPoint(argvDouble(argv, 3), argvDouble(argv, 4)), false, recalculate);
                            NxCurvePoint pt = curve->getPathPointsAt(indexPoint);
                            //return QString("%1 %2 %3  %4 %5 %6  %7 %8 %9").arg(pt.x()).arg(pt.y()).arg(pt.z()).arg(pt.c1.x()).arg(pt.c1.y()).arg(pt.c1.z()).arg(pt.c2.x()).arg(pt.c2.y()).arg(pt.c2.z());
                        }
                        return "0 0 0  0 0 0  0 0 0";
                    }
                    else if(commande == COMMAND_CURVE_POINT_SMOOTH) {
                        bool recalculate = true;
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc >= 9)      // 3+6 (x, y, z, sx, sy, sz)
                                curve->setPointAt(argvDouble(argv, 2), NxPoint(argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5), argvDouble(argv, 6), argvDouble(argv, 7), argvDouble(argv, 8)), true, recalculate);
                            else if(argc >= 7) // 3+4 (x, y, sx, sy)
                                curve->setPointAt(argvDouble(argv, 2), NxPoint(argvDouble(argv, 3), argvDouble(argv, 4), 0, argvDouble(argv, 5), argvDouble(argv, 6), 0), true, recalculate);
                            else if(argc >= 6) // 3+3 (x, y, z)
                                curve->setPointAt(argvDouble(argv, 2), NxPoint(argvDouble(argv, 3), argvDouble(argv, 4), argvDouble(argv, 5)), true, recalculate);
                            else if(argc >= 5) // 3+2 (x, y)
                                curve->setPointAt(argvDouble(argv, 2), NxPoint(argvDouble(argv, 3), argvDouble(argv, 4)), true, recalculate);
                            NxCurvePoint pt = curve->getPathPointsAt(argvDouble(argv, 2));
                            //return QString("%1 %2 %3  %4 %5 %6  %7 %8 %9").arg(pt.x()).arg(pt.y()).arg(pt.z()).arg(pt.c1.x()).arg(pt.c1.y()).arg(pt.c1.z()).arg(pt.c2.x()).arg(pt.c2.y()).arg(pt.c2.z());
                        }
                        return "0 0 0  0 0 0  0 0 0";
                    }

                    else if(commande == COMMAND_CURVE_TXT) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 4) {
                                curve->setText(argv.at(4), argv[3].replace("_", " ").trimmed());
                                curve->setResizeF(argvDouble(argv, 2));
                            }
                            return curve->getPathLength();
                        }
                        return 0;
                    }
                    else if(commande == COMMAND_CURVE_EQUATION) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 3)
                                curve->setEquation(argv.at(2), argvFullString(command, argv, 3));
                            return curve->getPathLength();
                        }
                        return 0;
                    }
                    else if(commande == COMMAND_CURVE_EQUATION_PARAM) {
                        object->dispatchProperty("equationParam", argvFullString(command, argv, 2));
                        return 0;
                    }
                    else if(commande == COMMAND_CURVE_LENGTH) {
                        object->dispatchProperty("pathLength", argvDouble(argv, 2));
                    }
                    else if(commande == COMMAND_CURVE_EQUATION_POINTS) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 2)
                                curve->setEquationPoints(argvDouble(argv, 2));
                            return curve->getEquationPoints();
                        }
                        return 0;
                    }
                    else if((commande == COMMAND_CURVE_SVG) || (commande == COMMAND_CURVE_PATH)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 3) {
                                curve->setSVG(argvFullString(command, argv, 3));
                                curve->setResizeF(argvDouble(argv, 2));
                            }
                            return curve->getPathLength();
                        }
                        return 0;
                    }
                    else if((commande == COMMAND_CURVE_SVG2) || (commande == COMMAND_CURVE_LINES)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 3) {
                                curve->setSVG2(argvFullString(command, argv, 3));
                                curve->setResizeF(argvDouble(argv, 2));
                            }
                            return curve->getPathLength();
                        }
                        return 0;
                    }
                    else if(commande == COMMAND_CURVE_IMG) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 3) {
                                curve->setImage(argvFullString(command, argv, 3));
                                curve->setResizeF(argvDouble(argv, 2));
                            }
                            return curve->getPathLength();
                        }
                        return 0;
                    }
                    else if(commande == COMMAND_CURVE_SVG) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 4) {
                                curve->setSVG(argvFullString(command, argv, 4));
                                curve->setResize(NxSize(argvDouble(argv, 2), argvDouble(argv, 3)));
                            }
                            return curve->getPathLength();
                        }
                        return 0;
                    }
                    else if(commande == COMMAND_CURVE_ELL) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(argc > 2)
                                curve->setEllipse(NxSize(argvDouble(argv, 2), argvDouble(argv, 3)));
                            return curve->getPathLength();
                        }
                        return 0;
                    }

                    else if(commande == COMMAND_POS) {
                        if(argc > 2)
                            object->dispatchProperty("posStr", argv.at(2) + " " + argv.at(3) + " " + argv.at(4));
                        return object->getProperty("posStr");
                    }
                    else if(commande == COMMAND_ACTIVE) {
                        if(argc > 2)
                            object->dispatchProperty("active", argvDouble(argv, 2));
                        return object->getProperty("active");
                    }

                    else if(commande == COMMAND_TRIG) {
                        object->dispatchProperty("forceTrig", true);
                        lastMessageAllow = true;
                        emit(updateTransport(timeLocalStr, lastMessage));
                        return true;
                    }

                    else if(commande == COMMAND_COLOR_GLOBAL) {
                        if(argc > 2) {
                            object->dispatchProperty("colorActive",          argvFullString(command, argv, 2));
                            object->dispatchProperty("colorInactive",        argvFullString(command, argv, 2));
                            object->dispatchProperty("colorActiveMessage",   argvFullString(command, argv, 2));
                            object->dispatchProperty("colorInactiveMessage", argvFullString(command, argv, 2));
                        }
                        return object->getProperty("colorActive");
                    }
                    else if(commande == COMMAND_COLOR_ACTIVE) {
                        if(argc > 2)
                            object->dispatchProperty("colorActive", argvFullString(command, argv, 2));
                        return object->getProperty("colorActive");
                    }
                    else if(commande == COMMAND_COLOR_INACTIVE) {
                        if(argc > 2)
                            object->dispatchProperty("colorInactive", argvFullString(command, argv, 2));
                        return object->getProperty("colorInactive");
                    }
                    else if(commande == COMMAND_COLOR_ACTIVE_MESSAGE) {
                        if(argc > 2)
                            object->dispatchProperty("colorActiveMessage", argvFullString(command, argv, 2));
                        return object->getProperty("colorActiveMessage");
                    }
                    else if(commande == COMMAND_COLOR_INACTIVE_MESSAGE) {
                        if(argc > 2)
                            object->dispatchProperty("colorInactiveMessage", argvFullString(command, argv, 2));
                        return object->getProperty("colorInactiveMessage");
                    }

                    else if(commande == COMMAND_COLOR_GLOBAL_HUE) {
                        if(argc > 2) {
                            object->dispatchProperty("colorActiveHue",          argvFullString(command, argv, 2));
                            object->dispatchProperty("colorInactiveHue",        argvFullString(command, argv, 2));
                            object->dispatchProperty("colorActiveMessageHue",   argvFullString(command, argv, 2));
                            object->dispatchProperty("colorInactiveMessageHue", argvFullString(command, argv, 2));
                        }
                        return object->getProperty("colorActiveHue");
                    }
                    else if((commande == COMMAND_COLOR_ACTIVE2) || (commande == COMMAND_COLOR_ACTIVE_HUE)) {
                        if(argc > 2)
                            object->dispatchProperty("colorActiveHue", argvFullString(command, argv, 2));
                        return object->getProperty("colorActiveHue");
                    }
                    else if((commande == COMMAND_COLOR_INACTIVE2) || (commande == COMMAND_COLOR_INACTIVE_HUE)) {
                        if(argc > 2)
                            object->dispatchProperty("colorInactiveHue", argvFullString(command, argv, 2));
                        return object->getProperty("colorInactiveHue");
                    }
                    else if((commande == COMMAND_COLOR_ACTIVE_MESSAGE2) || (commande == COMMAND_COLOR_ACTIVE_MESSAGE_HUE)) {
                        if(argc > 2)
                            object->dispatchProperty("colorActiveMessageHue", argvFullString(command, argv, 2));
                        return object->getProperty("colorActiveMessageHue");
                    }
                    else if((commande == COMMAND_COLOR_INACTIVE_MESSAGE2) || (commande == COMMAND_COLOR_INACTIVE_MESSAGE_HUE)) {
                        if(argc > 2)
                            object->dispatchProperty("colorInactiveMessageHue", argvFullString(command, argv, 2));
                        return object->getProperty("colorInactiveMessageHue");
                    }

                    else if(commande == COMMAND_MESSAGE) {
                        if(argc > 2)
                            object->dispatchProperty("messagePatterns", argvFullString(command, argv, 2));
                        return object->getProperty("messagePatterns");
                    }
                    else if(commande == COMMAND_TRIGGER_OFF) {
                        if(argc > 2)
                            object->dispatchProperty("triggerOff", argvDouble(argv, 2));
                        return object->getProperty("triggerOff");
                    }

                    else if(commande == COMMAND_TEXTURE_GLOBAL) {
                        if(argc > 2) {
                            object->dispatchProperty("textureActive",          argv.at(2));
                            object->dispatchProperty("textureInactive",        argv.at(2));
                            object->dispatchProperty("textureActiveMessage",   argv.at(2));
                            object->dispatchProperty("textureInactiveMessage", argv.at(2));
                        }
                        return object->getProperty("textureActive");
                    }
                    else if(commande == COMMAND_TEXTURE_ACTIVE) {
                        if(argc > 2)
                            object->dispatchProperty("textureActive", argv.at(2));
                        return object->getProperty("textureActive");
                    }
                    else if(commande == COMMAND_TEXTURE_INACTIVE) {
                        if(argc > 2)
                            object->dispatchProperty("textureInactive", argv.at(2));
                        return object->getProperty("textureInactive");
                    }
                    else if(commande == COMMAND_TEXTURE_ACTIVE_MESSAGE) {
                        if(argc > 2)
                            object->dispatchProperty("textureActiveMessage", argv.at(2));
                        return object->getProperty("textureActiveMessage");
                    }
                    else if(commande == COMMAND_TEXTURE_INACTIVE_MESSAGE) {
                        if(argc > 2)
                            object->dispatchProperty("textureInactiveMessage", argv.at(2));
                        return object->getProperty("textureInactiveMessage");
                    }
                    return object->getProperty("id");
                }
            }
        }
    }
    return 0;
}

void IanniX::sendMessage(void *_object, void *_trigger, void *_cursor, void *_collisionCurve, const NxPoint & collisionPoint, const NxPoint & collisionValue, const QString & status) {
    NxObject *object = (NxObject*)_object;
    if(object) {
        NxTrigger *trigger        = (NxTrigger*)_trigger;
        NxCursor  *cursor         = (NxCursor*)_cursor;
        NxCurve   *collisionCurve = (NxCurve*)_collisionCurve;
        NxCurve   *curve = 0;
        if(cursor)
            curve = cursor->getCurve();

        QStringList sentMessages;
        foreach(const QVector<QByteArray> & messagePattern, object->getMessagePatterns()) {
            if(messagesCache.contains(messagePattern.at(0)))
                message = messagesCache.value(messagePattern.at(0));
            else {
                message.setUrl(QUrl(messagePattern.at(0), QUrl::TolerantMode), &messageScriptEngine, ipOut, midiOut.replace(" ", "_"));
                messagesCache.insert(messagePattern.at(0), message);
            }
            if(message.parse(messagePattern, trigger, cursor, curve, collisionCurve, collisionPoint, collisionValue, status, inspector->nbTriggers, inspector->nbCursors, inspector->nbCurves, timeLocal, timeLocalStr)) {
                if(message.getType() == MessagesTypeDirect)
                    send(message);
                else if((message.getType() == MessagesTypeOsc) && (osc))
                    osc->send(message);
                else if((message.getType() == MessagesTypeHttp) && (http))
                    http->send(message);
                else if((message.getType() == MessagesTypeTcp) && (tcp))
                    tcp->send(message);
                else if((message.getType() == MessagesTypeUdp) && (udp))
                    udp->send(message);
                else if((message.getType() == MessagesTypeSerial) && (serial))
                    serial->send(message);
                else if((message.getType() == MessagesTypeMidi) && (midi))
                    midi->send(message);

                if(object->getSelectedHover())
                    sentMessages << message.getVerboseMessage();
            }
        }
        if((object->getSelectedHover()) && (sentMessages.count() > 0))
            object->setMessageLabel(sentMessages);
    }
}
QImage IanniX::takeScreenshot() {
    return render->grabFrameBuffer();
}

void IanniX::send(const ExtMessage & message) {
    //Launch
    execute(message.getAsciiMessage());

    //Log in the OSC console
    logOscReceive(message.getVerboseMessage());
}

QString IanniX::onOscReceive(const QString & protocol, const QString & host, const QString & port, const QString & destination, const QStringList & arguments) {
    QString retour = "";
    foreach(ExtScriptManager *document, activeScripts)
        retour += document->onOSCCall(protocol, host, port, destination, arguments);
    return retour;
}
QString IanniX::onDraw() {
    QString retour = "";
    foreach(ExtScriptManager *document, activeScripts)
        retour += document->onDrawCall(timeLocal);
    return retour;
}

void IanniX::askNxObject(void *_object, bool shift) {
    NxObject *object = (NxObject*)_object;
    if((object) && ((object->getType() == ObjectsTypeTrigger) || (object->getType() == ObjectsTypeCursor))) {
        if((shift) && (object->getType() == ObjectsTypeTrigger))
            ((NxTrigger*)object)->trig(0);
        else if((shift) && (object->getType() == ObjectsTypeCursor))
            timerTrig(object, true);
        else
            inspector->actionMessages();
    }
}
void IanniX::actionDrawFreeCurve() {
    if((render->getEditingMode() == EditingModeFree) && (render->getEditing()))
        editingStop();
    else {
        view->unToogleDraw(2);
        view->unToogleDraw(3);
        view->unToogleDraw(4);
        render->setEditingMode(EditingModeFree);
    }
}
void IanniX::actionDrawPointCurve() {
    if((render->getEditingMode() == EditingModePoint) && (render->getEditing()))
        editingStop();
    else {
        view->unToogleDraw(1);
        view->unToogleDraw(3);
        view->unToogleDraw(4);
        render->setEditingMode(EditingModePoint);
    }
}
void IanniX::actionDrawTriggers() {
    if((render->getEditingMode() == EditingModeTriggers) && (render->getEditing()))
        editingStop();
    else {
        view->unToogleDraw(1);
        view->unToogleDraw(2);
        view->unToogleDraw(4);
        render->setEditingMode(EditingModeTriggers);
    }
}
void IanniX::actionAddFreeCursor() {
    bool freeCursor = true;
    view->unToogleDraw(1);
    view->unToogleDraw(2);
    view->unToogleDraw(3);
    view->unToogleDraw(4);
    editingStop();
    pushSnapshot();
    foreach(const NxObject *object, *(render->getSelection())) {
        if(object->getType() == ObjectsTypeCurve) {
            freeCursor = false;
            NxCurve *curve = (NxCurve*)object;
            quint16 cursorId = execute(QString("add cursor auto")).toUInt();
            execute(QString("setCurve %1 %2").arg(cursorId).arg(curve->getId()));
            execute(QString("setPattern %1 0 0 1 0").arg(cursorId));
            execute(QString("setOffset %1 %2 0 end").arg(cursorId).arg(curve->getMaxOffset() / 2));
        }
    }
    if(freeCursor) {
        quint16 cursorId = execute(QString("add cursor auto")).toUInt();
        execute(QString("setPattern %1 0 0 1 0").arg(cursorId));
    }
}
void IanniX::actionCircleCurve() {
    if((render->getEditingMode() == EditingModeCircle) && (render->getEditing()))
        editingStop();
    else {
        view->unToogleDraw(1);
        view->unToogleDraw(2);
        view->unToogleDraw(3);
        render->setEditingMode(EditingModeCircle);
    }
}

void IanniX::editingStart(const NxPoint & point) {
    if(render->getEditing()) {
        if((render->getEditingMode() == EditingModeFree) || (render->getEditingMode() == EditingModePoint)) {
            editingStartPoint = point;
            freehandCurveIndex = 1;
            pushSnapshot();
            freehandCurveId = execute("add curve auto").toUInt();
            execute(QString("setPos %1 %2 %3 0").arg(freehandCurveId).arg(editingStartPoint.x()).arg(editingStartPoint.y()));
        }
        else if(render->getEditingMode() == EditingModeTriggers) {
            pushSnapshot();
            quint16 triggerId = execute("add trigger auto").toUInt();
            execute(QString("setPos %1 %2 %3 0").arg(triggerId).arg(point.x()).arg(point.y()));
        }
        else if(render->getEditingMode() == EditingModeCircle) {
            pushSnapshot();
            quint16 curveId = execute(QString("add curve auto")).toUInt();
            execute(QString("setPos %1 %2 %3 0").arg(curveId).arg(point.x()).arg(point.y()));
            execute(QString("setPointsEllipse %1 2 2").arg(curveId));
            quint16 cursorId = execute(QString("add cursor auto")).toUInt();
            execute(QString("setCurve %1 %2").arg(cursorId).arg(curveId));
        }
    }
}
void IanniX::editingStop() {
    if((render->getEditing()) && ((render->getEditingMode() == EditingModeFree) || (render->getEditingMode() == EditingModePoint))) {
        if(freehandCurveIndex > 1) {
            execute(QString("removePointAt %1 %2").arg(freehandCurveId).arg(freehandCurveIndex));
            quint16 cursorId = execute(QString("add cursor auto")).toUInt();
            execute(QString("setCurve %1 %2").arg(cursorId).arg(freehandCurveId));
            execute(QString("setPattern %1 0 0 1 0").arg(cursorId));
        }
        else
            execute(QString("remove %1").arg(freehandCurveId));
    }
    view->unToogleDraw(0);
    render->unsetEditing();
}
void IanniX::editingMove(const NxPoint & point, bool add) {
    /*
    if((render->getEditing()) && ((render->getEditingMode() == EditingModeFree) || (render->getEditingMode() == EditingModePoint))) {
        NxPoint newPoint = point - editingStartPoint;
        execute(QString("setSmoothPointAt %1 %2 %3 %4").arg(freehandCurveId).arg(freehandCurveIndex++).arg(newPoint.x()).arg(newPoint.y()));
    }
    */
    if((render->getEditing()) && (render->getEditingMode() == EditingModeFree)) {
        NxPoint newPoint = point - editingStartPoint;
        execute(QString("setSmoothPointAt %1 %2 %3 %4").arg(freehandCurveId).arg(freehandCurveIndex).arg(newPoint.x()).arg(newPoint.y()));
        if(add)
            freehandCurveIndex++;
    }
    else if((render->getEditing()) && (render->getEditingMode() == EditingModePoint)) {
        NxPoint newPoint = point - editingStartPoint;
        execute(QString("setPointAt %1 %2 %3 %4").arg(freehandCurveId).arg(freehandCurveIndex).arg(newPoint.x()).arg(newPoint.y()));
        if(add)
            freehandCurveIndex++;
    }
}
void IanniX::actionGridChange(qreal val) {
    render->getRenderOptions()->axisGrid = val;
}
void IanniX::actionGridOpacityChange(qreal val) {
    if(!render->getColorTheme()) {
        render->getRenderOptions()->colors["grid"] = QColor(255, 255, 255,  23*val);
        render->getRenderOptions()->colors["axis"] = QColor(255, 255, 255,  18*val);
    }
    else {
        render->getRenderOptions()->colors["grid"] = QColor(  0,   0,   0,  20*val);
        render->getRenderOptions()->colors["axis"] = QColor(  0,   0,   0,  13*val);
    }
}
void IanniX::actionShowEditor() {
    if(editor->isVisible()) {
        editor->close();
        view->toggleEditor(false);
    }
    else {
        editor->show();
        editor->raise();
        view->toggleEditor(true);
    }
}
void IanniX::actionShowTimer() {
    if(uitimer->isVisible()) {
        uitimer->close();
        view->toggleTimer(false);
    }
    else {
        uitimer->show();
        view->raise();
        view->toggleTimer(true);
    }
}
void IanniX::actionReloadScript() {
    actionProjectScript();
}

void IanniX::transportMessageChange(const QString & message) {
    transportObject->setMessagePatterns("1," + message);
}
void IanniX::syncMessageChange(const QString & message) {
    syncObject->setMessagePatterns("1," + message);
}
void IanniX::bundleMessageChange(const QString &host, quint16 port) {
    oscBundleHost = QHostAddress(host);
    oscBundlePort = port;
}

void IanniX::actionUnmuteGroups() {
    if(currentDocument) {
        foreach(NxGroup *group, currentDocument->groups) {
            if(group->checkState(0) == Qt::Unchecked)
                group->setCheckState(0, Qt::Checked);
        }
    }
}
void IanniX::actionUnmuteObjects() {
    if(currentDocument) {
        //Browse documents
        foreach(NxGroup *group, currentDocument->groups) {
            //Browse active/inactive objects
            for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
                //Browse all types of objects
                for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                    //Browse objects
                    foreach(NxObject *object, group->objects[activityIterator][typeIterator]) {
                        if(object->checkState(1) == Qt::Unchecked)
                            object->setCheckState(1, Qt::Checked);
                    }
                }
            }
        }
    }
}
void IanniX::actionUnsoloGroups() {
    if(currentDocument) {
        foreach(NxGroup *group, currentDocument->groups) {
            if(group->checkState(1) == Qt::Checked)
                group->setCheckState(1, Qt::Unchecked);
        }
    }
}
void IanniX::actionUnsoloObjects() {
    if(currentDocument) {
        //Browse documents
        foreach(NxGroup *group, currentDocument->groups) {
            //Browse active/inactive objects
            for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
                //Browse all types of objects
                for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                    //Browse objects
                    foreach(NxObject *object, group->objects[activityIterator][typeIterator]) {
                        if(object->checkState(2) == Qt::Checked)
                            object->setCheckState(2, Qt::Unchecked);
                    }
                }
            }
        }
    }
}

void IanniX::allowSyphonServer(bool val) {
#ifdef SYPHON_INSTALLED
    render->allowSyphonServer(val);
    transport->allowSyphonServer(val);
#endif
}

void IanniX::setIpOut(const QString & ip) {
    ipOut = ip;
    messagesCache.clear();
    //emit(ipOutStatus(false));
    /*
    if(ipOutId >= 0)
        QHostInfo::abortHostLookup(ipOutId);
        */
    //ipOutId = QHostInfo::lookupHost(ipOut, this, SLOT(ipOutStatusFound(QHostInfo)));
}
void IanniX::ipOutStatusFound(const QHostInfo &hostInfo) {
    qDebug("LA %s %d %d", qPrintable(hostInfo.errorString()), hostInfo.error(), hostInfo.lookupId());
    if(hostInfo.error() == QHostInfo::NoError) {
        emit(ipOutStatus(true));
        qDebug("ICI quand même ?");
    }
    else
        emit(ipOutStatus(false));
}
void IanniX::setMidiSyncClock(bool val) {
    acceptMidiSyncClock = val;
}
void IanniX::setMidiSyncSong(bool val) {
    acceptMidiSyncSong = val;
}

void IanniX::setMidiOut(const QString & midi) {
    midiOut = midi;
    messagesCache.clear();
}
void IanniX::setMidiOutNewDevice(const QString &midi) {
    inspector->setMidiOutNewDevice(midi);
}

void IanniX::actionCloseEvent(QCloseEvent *event) {
    quint16 nbFileNoSave = 0;
    foreach(const NxDocument *document, documents) {
        if(document->getHasChanged())
            nbFileNoSave++;
    }

    if(nbFileNoSave > 0) {
        QString ess = " " + tr("has");
        if(nbFileNoSave > 1)
            ess = tr("s have");
        int rep = QMessageBox::question(0, tr("Score save"), tr("%1 document%2 been changed without saving.\n\nDo you want to save modifications?").arg(nbFileNoSave).arg(ess), QMessageBox::SaveAll | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Cancel);
        if(rep == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
        else if(rep == QMessageBox::SaveAll)
            actionSave_all();
    }

    if(editor)
        editor->close();
    if(about)
        about->close();
    if(uitimer)
        uitimer->close();

    QSettings settings;
    settings.setValue("oscPort", inspector->getOSCPort());
    settings.setValue("udpPort", inspector->getUDPPort());
    settings.setValue("httpPort", inspector->getHttpPort());
    settings.setValue("tcpPort", inspector->getTCPPort());
    settings.setValue("ipOut", inspector->getIpOut());
    settings.setValue("midiOut", inspector->getMidiOut());
    settings.setValue("midiTempo", inspector->getMidiTempo());
    settings.setValue("acceptMidiSyncSong", inspector->getMidiSyncSong());
    settings.setValue("acceptMidiSyncClock", inspector->getMidiSyncClock());
    settings.setValue("serialPort", inspector->getSerialPort());
    settings.setValue("defaultMessageTransport", inspector->getTransportMessage());
    settings.setValue("defaultMessageSync", inspector->getSyncMessage());
    settings.setValue("bundleHost", inspector->getBundleHost());
    settings.setValue("bundlePort", inspector->getBundlePort());
    settings.setValue("colorTheme", render->getColorTheme());
    settings.setValue("opacityCurve", inspector->getViewCurveOpacityCheck());
    settings.setValue("autoresize", render->getTriggerAutosize());
    settings.setValue("objectLabel", view->getToggleLabel());
    settings.setValue("grid", render->getRenderOptions()->paintAxisGrid);

    event->accept();
}


void IanniX::actionUndo() {
    render->selectionClear(true);
    currentDocument->popSnapshot();
}
void IanniX::actionRedo() {
    render->selectionClear(true);
    currentDocument->popSnapshot(true);
}
void IanniX::actionSync() {
    QStringList commands = serialize().split(COMMAND_END);
    foreach(const QString & command, commands)
        sendMessage(syncObject, 0, 0, 0, NxPoint(), NxPoint(), command);
}

void IanniX::loadProject(const QString & projectFile) {
    if(fileWatcher.directories().contains(scriptDir.path()))
        fileWatcher.removePath(scriptDir.path());
    scriptDir = QFileInfo(projectFile).absoluteDir();
    fileWatcher.addPath(scriptDir.path() + QString(QDir::separator()));

    //Clear
    render->setDocument(0);
    activeScripts.clear();

    //projectScore->setText(0, scriptDir.dirName());
    //projectScript->setText(0, scriptDir.dirName());

    //Files
    fileWatcherChanged(scriptDir.path());
    if(projectScore->childCount() == 0)
        actionNew();
    else {
        inspector->getProjectFiles()->setCurrentItem(projectScore->child(0));
        actionProjectFiles();
    }
}
void IanniX::fileWatcherChanged(const QString & path) {
    QDir fileDir(path);

    //Scores
    fileWatcherFolder(QStringList() << "*.nxscore", fileDir, projectScore, true);
    fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", fileDir, projectScript, false);

    if(currentDocument) {
        for(quint16 indexChild = 0 ; indexChild < projectScore->childCount() ; indexChild++) {
            ExtScriptManager *document = (ExtScriptManager*)projectScore->child(indexChild);
            if(document->getScriptFile() == currentDocument->getScriptFile())
                inspector->getProjectFiles()->setCurrentItem(document);
        }
        view->setWindowTitle(tr("IanniX") + QString(" - ") + currentDocument->getScriptFile().baseName());
    }
}

void IanniX::fileWatcherFolder(QStringList extension, QDir dir, QTreeWidgetItem *parentList, bool isDocument) {
    QFileInfoList fileList = dir.entryInfoList(extension, QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    QList<ExtScriptManager*> removeList;
    for(quint16 indexChild = 0 ; indexChild < parentList->childCount() ; indexChild++)
        if(parentList->child(indexChild)->type() == 1024)
            removeList.append((ExtScriptManager*)parentList->child(indexChild));
    foreach(const QFileInfo & file, fileList) {
        bool create = true;

        for(quint16 indexChild = 0 ; indexChild < parentList->childCount() ; indexChild++) {
            if(parentList->child(indexChild)->type() == 1024) {
                ExtScriptManager *document = (ExtScriptManager*)parentList->child(indexChild);
                if(document->getScriptFile() == file) {
                    document->updateTitle();
                    create = false;
                    removeList.removeOne(document);
                }
            }
        }
        if(create) {
            if(isDocument) {
                NxDocument *document = new NxDocument(this, file, parentList);
                documents[document->getId()] = document;
            }
            else
                new ExtScriptManager(this, file, parentList, scriptDir);
        }
    }
    foreach(ExtScriptManager *document, removeList) {
        QString destroyKey = "";
        QHashIterator<QString, NxDocument*> documentIterator(documents);
        while (documentIterator.hasNext()) {
            documentIterator.next();
            if(documentIterator.value() == document)
                destroyKey = documentIterator.key();
        }
        if(!destroyKey.isEmpty())
            documents.remove(destroyKey);
        parentList->removeChild(document);
    }
    //parentList->sortChildren(0, Qt::AscendingOrder);
}

void IanniX::logOscSend(const QString & message) {
    if((lastMessageAllow) || (schedulerActivity == SchedulerOff)) {
        lastMessage = message;
        lastMessageAllow = false;
        if(schedulerActivity == SchedulerOff)
            emit(updateTransport(timeLocalStr, lastMessage));
    }
    if(oscConsoleActive)
        inspector->logOscSend(message);
}
void IanniX::logOscReceive(const QString & message) {
    if(lastMessageReceivedAllow) {
        lastMessageReceived = message;
        emit(newMessageArrived());
    }
    if(oscConsoleActive)
        inspector->logOscReceive(message);
}
QString IanniX::waitForMessage() {
    lastMessageReceivedAllow = true;
    lastMessageReceived = "";
    QEventLoop loop;
    connect(this, SIGNAL(newMessageArrived()), &loop, SLOT(quit()));
    loop.exec();
    lastMessageReceivedAllow = false;
    return lastMessageReceived;
}

void IanniX::pushSnapshot() {
    if(currentDocument)
        currentDocument->pushSnapshot();
}

void IanniX::actionPasteScript() {
    pushSnapshot();
    QString paste = QApplication::clipboard()->text();
    if(currentScript)
        currentScript->scriptEngine.evaluate(paste);
}
