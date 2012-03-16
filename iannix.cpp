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
    currentDocument = 0;
    currentScript = 0;
    projectScore = 0;
    freehandCurveId = 0;
    lastMessageAllow = true;
    oscBundleHost = QHostAddress("127.0.0.2");
    oscBundlePort = 0;
    scriptDir = QDir::current();
    cpu = new NxCpu(this);

    splash = new UiSplash(0);
    splash->show();
    QTimer::singleShot(1500, this, SLOT(closeSplash()));

    iconAppPlay  = QIcon(QPixmap(":icons/res_appicon_play.png"));
    iconAppPause = QIcon(QPixmap(":icons/res_appicon_pause.png"));

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
    connect(view, SIGNAL(actionRouteSnapGrid()), SLOT(actionSnapGrid()));
    connect(view, SIGNAL(actionRouteShowEditor()), SLOT(actionShowEditor()));
    connect(view, SIGNAL(actionRouteReloadScript()), SLOT(actionReloadScript()));
    connect(view, SIGNAL(actionRouteCloseEvent(QCloseEvent*)), SLOT(actionCloseEvent(QCloseEvent*)));
    connect(view, SIGNAL(actionRouteAbout()), SLOT(actionLogo()));
    connect(view, SIGNAL(actionRouteImportSVG(QString)),            SLOT(actionImportSVG(QString)));
    connect(view, SIGNAL(actionRouteImportImage(QString)),          SLOT(actionImportImage(QString)));
    connect(view, SIGNAL(actionRouteImportBackground(QString)),     SLOT(actionImportBackground(QString)));
    connect(view, SIGNAL(actionRouteImportText(QString,QString)),   SLOT(actionImportText(QString,QString)));
    connect(view, SIGNAL(actionRouteSelectionModeChange(bool,bool,bool)), SLOT(actionSelectionModeChange(bool,bool,bool)));

    //Transport
    transport = view->getTransport();
    connect(transport, SIGNAL(actionRouteFast_rewind()), SLOT(actionFast_rewind()));
    connect(transport, SIGNAL(actionRoutePlay_pause()), SLOT(actionPlay_pause()));
    connect(transport, SIGNAL(actionRouteLogo()), SLOT(actionLogo()));
    connect(transport, SIGNAL(actionRouteGoto()), SLOT(actionGoto()));
    connect(transport, SIGNAL(actionRouteSetOpenGL()), SLOT(actionSetOpenGL()));
    connect(transport, SIGNAL(actionRouteSetScheduler()), SLOT(actionSetScheduler()));
    connect(transport, SIGNAL(actionRouteSpeed()), SLOT(actionSpeed()));
    connect(this, SIGNAL(updateTransport(QString,QString)), transport, SLOT(updateTransport(QString,QString)));

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
    render->zoom();
    render->resizeGL();
    render->updateGL();
    render->loadTexture("background", scriptDir.absoluteFilePath("Tools/background.jpg"), NxRect(NxPoint(), NxPoint()));
    render->loadTexture("trigger_active", scriptDir.absoluteFilePath("Tools/trigger.png"), NxRect(NxPoint(-1, 1), NxPoint(1, -1)));
    render->loadTexture("trigger_inactive", scriptDir.absoluteFilePath("Tools/trigger.png"), NxRect(NxPoint(-1, 1), NxPoint(1, -1)));
    render->loadTexture("trigger_active_message", scriptDir.absoluteFilePath("Tools/trigger_message.png"), NxRect(NxPoint(-1, 1), NxPoint(1, -1)));
    render->loadTexture("trigger_inactive_message", scriptDir.absoluteFilePath("Tools/trigger_message.png"), NxRect(NxPoint(-1, 1), NxPoint(1, -1)));

    //Message script engine
    QScriptValue messageScript = messageScriptEngine.globalObject();
    messageScript = messageScriptEngine.evaluate(ExtScriptManager::loadLibrary(scriptDir));

    //Objet transport
    transportObject = new NxTrigger(this, 0, render->getRenderOptions());
    syncObject = new NxTrigger(this, 0, render->getRenderOptions());

    //Editor
    editor = new UiEditor(0);

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

#ifdef KINECT_INSTALLED
    kinect = 0;
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
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
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
    //if((forceSettings) || (!settings.childKeys().contains("édefaultMessageTrigger")))
    settings.setValue("defaultMessageTrigger", "osc://127.0.0.1:57120/trigger trigger_id trigger_xPos trigger_yPos trigger_zPos cursor_id");
    //if((forceSettings) || (!settings.childKeys().contains("defaultMessageCursor")))
    settings.setValue("defaultMessageCursor", "osc://127.0.0.1:57120/cursor cursor_id cursor_value_x cursor_value_y cursor_xPos cursor_yPos cursor_zPos");
    //if((forceSettings) || (!settings.childKeys().contains("defaultMessage")))
    settings.setValue("defaultMessage", "osc://127.0.0.1:57120/object trigger_id cursor_id");
    if((forceSettings) || (!settings.childKeys().contains("defaultMessageTransport")))
        settings.setValue("defaultMessageTransport", "osc://127.0.0.1:57120/transport status nb_triggers nb_cursors nb_curves");
    //settings.setValue("defaultMessageSync", "osc://127.0.0.1:57120/iannix/ status");
    settings.setValue("defaultMessageSync", "");
    if((forceSettings) || (!settings.childKeys().contains("defaultMessageSync")))
        settings.setValue("defaultMessageSync", "osc://127.0.0.1:57120/iannix/ status");
    if((forceSettings) || (!settings.childKeys().contains("updatePeriod")))
        settings.setValue("updatePeriod", 1);

    if((forceSettings) || (!settings.childKeys().contains("bundleHost")))
        settings.setValue("bundleHost", "127.0.0.1");
    if((forceSettings) || (!settings.childKeys().contains("bundlePort")))
        settings.setValue("bundlePort", "57121");

    if((forceSettings) || (!settings.childKeys().contains("colorTheme")))
        settings.setValue("colorTheme", false);
    if((forceSettings) || (!settings.childKeys().contains("opacityCurve")))
        settings.setValue("opacityCurve", false);

    inspector->setOSCPort(settings.value("oscPort").toUInt());
    inspector->setUDPPort(settings.value("udpPort").toUInt());
    inspector->setTCPPort(settings.value("tcpPort").toUInt());
    inspector->setHttpPort(settings.value("httpPort").toUInt());
    inspector->setSerialPort(settings.value("serialPort").toString());
    inspector->setTransportMessage(settings.value("defaultMessageTransport").toString());
    inspector->setSyncMessage(settings.value("defaultMessageSync").toString());
    inspector->setBundleMessage(settings.value("bundleHost").toString(), settings.value("bundlePort").toUInt());
    defaultMessageTrigger = settings.value("defaultMessageTrigger").toString();
    defaultMessageCursor = settings.value("defaultMessageCursor").toString();
    render->setColorTheme(settings.value("colorTheme").toBool());
    view->setColorTheme(render->getColorTheme());
    inspector->setViewCurveOpacityCheck(settings.value("opacityCurve").toBool());

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

    //Projet par défault
    loadProject("Project/root.root");
    actionFast_rewind();

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
    if(tracks != "") {
        QFile edlOut("EDL-out.js");
        if(edlOut.open(QFile::WriteOnly)) {
            tracks = QString("var data = [\n%1];").arg(tracks);
            edlOut.write(qPrintable(tracks));
            edlOut.close();
        }
    }
    */
    startTimer(1000);
}

void IanniX::actionImportSVG(const QString &filename) {
    qreal scale = 0.01;
    bool ok = false;
    scale = QInputDialog::getDouble(0, tr("SVG Import"), tr("SVG coordinates system & IanniX coordinates system are differents.\nYou need to scale the SVG to fit in IanniX.\n\nPlease enter a scale value:"), scale, 0.001, 10., 3, &ok);
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
    scale = QInputDialog::getDouble(0, tr("Image import"), tr("Image coordinates system & IanniX coordinates system are differents.\nYou need to scale the image to fit in IanniX.\n\nPlease enter a scale value:"), scale, 0.001, 10., 3, &ok);
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
        scale = QInputDialog::getDouble(0, tr("Image import"), tr("Image coordinates system & IanniX coordinates system are differents.\nYou need to scale the image to fit in IanniX.\n\nPlease enter a scale value:"), scale, 0.001, 10., 3, &ok);
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
    if(fontReal == "") {
        ok = false;
        QFont fontFont = QFontDialog::getFont(&ok);
        if(ok)
            fontReal = fontFont.family();
        else
            return;
    }

    fontReal = fontReal.replace(" ", "_");
    ok = false;
    scale = QInputDialog::getDouble(0, tr("Text import"), tr("Text coordinates system & IanniX coordinates system are differents.\nYou need to scale the text to fit in IanniX.\n\nPlease enter a scale value:"), scale, 0.001, 10., 3, &ok);
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
        timer->start();
        renderMeasure.start();
    }
    else
        timer->stop();
    transport->setPlay_pause(getScheduler());
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

void IanniX::timerEvent(QTimerEvent *) {
    transport->setPerfCpu(QString().setNum((quint16)qRound(cpu->cpu)));
}
void IanniX::timerTick() {
    qreal delta = renderMeasure.elapsed() / 1000.0F;
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
    renderMeasure.start();

    //Open a bundle if necessary
    if((forceTimeLocal) && (osc))
        osc->setBundleMessageId(0);
    if(osc)
        osc->openBundle(oscBundleHost, oscBundlePort);

    //Browse documents
    QRect cursorBoundingRectSearch;
    //QHashIterator<QString, NxDocument*> documentIterator(documents);
    /*while (documentIterator.hasNext())*/ {
        //documentIterator.next();
        NxDocument *document = currentDocument; //documentIterator.value();

        //Browse groups
        if(document) {
            QMapIterator<QString, NxGroup*> groupIterator(document->groups);
            while (groupIterator.hasNext()) {
                groupIterator.next();
                NxGroup *group = groupIterator.value();

                //Browse active/inactive objects
                for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {

                    //Browse cursors
                    QHashIterator<quint16, NxObject*> objectIterator(group->objects[activityIterator][ObjectsTypeCursor]);
                    while (objectIterator.hasNext()) {
                        objectIterator.next();
                        NxCursor *cursor = (NxCursor*)objectIterator.value();

                        //Cursor reset
                        if(forceTimeLocal) {
                            cursor->setTimeLocal(timeLocal);
                            cursor->setMessageId(0);
                        }

                        //Set time for a cursor
                        cursor->setTime(delta * render->getRenderOptions()->timeFactor);

                        //Is cursor active ?
                        if((!forceTimeLocal) && (cursor->getActive()) && (group->checkState(0) == Qt::Checked)) {
                            //Messages
                            cursor->trig();

                            //Bounding search
                            cursorBoundingRectSearch = cursor->getBoundingRectSearch();

                            //Browse groups
                            QMapIterator<QString, NxGroup*> groupIteratorTrigger(document->groups);
                            while (groupIteratorTrigger.hasNext()) {
                                groupIteratorTrigger.next();
                                NxGroup *group = groupIteratorTrigger.value();

                                //Browse active triggers
                                QHashIterator<quint16, NxObject*> objectIteratorTrigger(group->objects[ObjectsActivityActive][ObjectsTypeTrigger]);
                                while (objectIteratorTrigger.hasNext()) {
                                    objectIteratorTrigger.next();

                                    NxTrigger *trigger = (NxTrigger*)objectIteratorTrigger.value();

                                    //Check the collision
                                    if(cursor->contains(trigger))
                                        trigger->trig(cursor);
                                }

                                //Browse active triggers
                                QHashIterator<quint16, NxObject*> objectIteratorCurve(group->objects[ObjectsActivityActive][ObjectsTypeCurve]);
                                while (objectIteratorCurve.hasNext()) {
                                    objectIteratorCurve.next();

                                    NxCurve *curve = (NxCurve*)objectIteratorCurve.value();

                                    //Check the collision
                                    cursor->trig(curve);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    onDraw();

    //Close the bundle if necessary
    if(osc)
        osc->closeBundle();

    if(timeTransportRefresh >= 0.06) {
        timeTransportRefresh = 0;
        QString timeStr = "";

        quint16 min = timeLocal / 60;
        if(min < 10) timeStr += "00";
        else if(min < 100) timeStr += "0";
        timeStr += QString().setNum(min) + ":";

        quint8 sec = (int)floor(timeLocal) % 60;
        if(sec < 10) timeStr += "0";
        timeStr += QString().setNum(sec) + ":";

        quint16 milli = (timeLocal - floor(timeLocal)) * 1000;
        if(milli < 10)       timeStr += "00";
        else if(milli < 100) timeStr += "0";
        timeStr += QString().setNum(milli);

        emit(updateTransport(timeStr, lastMessage));
        lastMessageAllow = true;
    }
    if(timePerfRefresh >= 1) {
        transport->setPerfScheduler(QString().setNum((quint16)qRound(1000.0F*timePerfRefresh/timePerfCounter)));
        timePerfRefresh = 0;
        timePerfCounter = 0;
    }

    if(forceTimeLocal)
        forceTimeLocal = false;
}

void IanniX::checkForUpdates() {
    QString url = "http://www.iannix.org/download/updates.php?id=" + QSettings().value("id").toString() + "&package=" + (QCoreApplication::applicationName() + "__" + QCoreApplication::applicationVersion()).toLower().replace(" ", "_").replace(".", "_");
    qDebug("Checking for updates %s", qPrintable(url));
    updateManager->get(QNetworkRequest(QUrl(url, QUrl::TolerantMode)));
}
void IanniX::checkForUpdatesFinished(QNetworkReply *reply) {
    if(reply->error() != QNetworkReply::NoError) {
        qDebug("Network error. %s", qPrintable(reply->errorString()));
    }
    else {
        QSettings().setValue("lastUpdate", QDateTime::currentDateTime());
        QString info = reply->readAll().trimmed();
        if(info.length() > 0) {
            QMessageBox message;
            message.setWindowTitle(tr("IanniX Update Center"));
            message.setText(tr("An update has been detected on the server."));
            message.setInformativeText(tr("Would you like to update IanniX with the new version ?"));
            message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            message.setDefaultButton(QMessageBox::Yes);
            message.setDetailedText(info);
            int rep = message.exec();
            if(rep == QMessageBox::Yes)
                QDesktopServices::openUrl(QUrl("http://www.iannix.org", QUrl::TolerantMode));
        }
    }
}

void IanniX::actionToggle_Inspector() {
    if(inspector->isVisible())
        inspector->parentWidget()->hide();
    else
        inspector->parentWidget()->show();
    view->activateWindow();;
}
void IanniX::actionToggle_Transport() {
    if(transport->isVisible())
        transport->parentWidget()->hide();
    else
        transport->parentWidget()->show();
    view->activateWindow();
}
void IanniX::actionToggle_Autosize() {
    if(render->getTriggerAutosize())
        render->setTriggerAutosize(false);
    else
        render->setTriggerAutosize(true);
}

void IanniX::actionPlay_pause() {
    if(getScheduler()) {
        setScheduler(SchedulerOff);
        sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "stop");
    }
    else {
        setScheduler(SchedulerOn);
        sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "play");
    }
    view->activateWindow();
}
void IanniX::actionFast_rewind() {
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
void IanniX::actionGoto(qreal gotoTime) {
    timeLocal = gotoTime;
    forceTimeLocal = true;
    if(schedulerActivity == SchedulerOff)
        setScheduler(SchedulerOneShot);
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
    render->centerOn(center);
}
void IanniX::actionCC2() {
    QList<NxGroup*> groups = inspector->getSelectedCC2Object();
    NxPoint center;
    quint16 centerCounter = 0;

    render->selectionClear(true);
    foreach(NxGroup* group, groups) {
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                //Browse objects
                QHashIterator<quint16, NxObject*> objectIterator(group->objects[activityIterator][typeIterator]);
                while (objectIterator.hasNext()) {
                    objectIterator.next();
                    NxObject *object = objectIterator.value();
                    render->selectionAdd(object);
                    center += object->getPos();
                    centerCounter++;
                }
            }
        }
    }
    center /= centerCounter;
    render->centerOn(center);
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
        QString text = QInputDialog::getText(0, tr("New score"), tr("Enter the name of your new score:"), QLineEdit::Normal, "New Document " + QDateTime::currentDateTime().toString("MMddhhmmss"), &ok);
        if((ok) && (text != "")) {
            if(!QFile::exists(scriptDir.absoluteFilePath(text +  ".nxscore"))) {
                QFile newFile(scriptDir.absoluteFilePath(text +  ".nxscore"));
                if(newFile.open(QIODevice::WriteOnly)) {
                    newFile.write("");
                    newFile.close();
                }
            }
            else {
                QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QMessageBox::Ok);
            }
        }
    }
}

/*
void IanniX::actionNew_script() {  ///CG///
    if(projectScore) {
        bool ok;
        QString text = QInputDialog::getText(0, tr("New score"), tr("Enter the name of your new score:"), QLineEdit::Normal, "New Document " + QDateTime::currentDateTime().toString("MMddhhmmss"), &ok);
        if((ok) && (text != "")) {
            if(!QFile::exists(scriptDir.absoluteFilePath(text +  ".nxscore"))) {
                QFile newFile(scriptDir.absoluteFilePath(text +  ".nxscore"));
                if(newFile.open(QIODevice::WriteOnly)) {
                    newFile.write("");
                    newFile.close();
                }
            }
            else {
                QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QMessageBox::Ok);
            }
        }
    }

}
*/

void IanniX::actionOpen() {
    QString fileName = QFileDialog::getExistingDirectory(0, tr("Open IanniX Project Folder"), QString("./scores/"));
    if(fileName != "")
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
    //if(currentDocument) {
    //    bool ok;
    //    QString text = QInputDialog::getText(0, tr("File rename"), tr("Enter the desired name of your score:"), QLineEdit::Normal, currentDocument->getScriptFile().baseName(), &ok);
    //    if((ok) && (text != ""))
    //        currentDocument->rename(currentDocument->getScriptFile().absoluteFilePath().replace(currentDocument->getScriptFile().baseName()+".", text+"."));
    //}
    if(currentDocument) {
        bool ok;
        ExtScriptManager *fileList = (ExtScriptManager*)inspector->getProjectFiles()->currentItem();
        QString text = QInputDialog::getText(0, tr("File rename"), tr("New name of script:"), QLineEdit::Normal, fileList->getScriptFile().baseName(), &ok);
        QString f = fileList->getScriptFile().absoluteFilePath().replace(fileList->getScriptFile().baseName()+".", text+".");
        if((ok) && (f != "")) {
            if(!QFile::exists(f)) {
                QFile::rename(fileList->getScriptFile().absoluteFilePath(), f);
            }
            else {
                QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be renamed! A file with this name exists in your project."), QMessageBox::Ok);
            }
        }
    }
}
void IanniX::actionRemove() {
    //if(currentDocument) {
    //   int rep = QMessageBox::question(0, tr("File remove"), tr("The file will be removed from your disk. Are you sure?"), QMessageBox::Yes | QMessageBox::No);
    //   if(rep == QMessageBox::Yes)
    //      currentDocument->remove();
    //}
    ExtScriptManager *fileList = (ExtScriptManager*)inspector->getProjectFiles()->currentItem();
    if(currentDocument) {
        int rep = QMessageBox::question(0, tr("File remove"), tr("The file will be removed from your disk. Are you sure?"), QMessageBox::Yes | QMessageBox::No);

        if(rep == QMessageBox::Yes) {
            QFile::remove(fileList->getScriptFile().absoluteFilePath());
        }
    }
}
void IanniX::actionDuplicateScore() {
    if(currentDocument) {
        bool ok;
        QString text = QInputDialog::getText(0, tr("File duplication"), tr("Enter the desired name of the duplicated score"), QLineEdit::Normal, currentDocument->getScriptFile().baseName(), &ok);
        if((ok) && (text != "")) {
            currentDocument->setNewFilename(currentDocument->getScriptFile().absoluteFilePath().replace(currentDocument->getScriptFile().baseName()+".", text+"."));
            currentDocument->save(render->getRenderOptions());
        }
    }
}

void IanniX::actionSave_all() {
    QHashIterator<QString, NxDocument*> documentIterator(documents);
    while (documentIterator.hasNext()) {
        documentIterator.next();
        NxDocument *document = documentIterator.value();
        document->save(render->getRenderOptions());
    }
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
            QMenu menu(inspector);
            QAction *openProject = menu.addAction(tr("Open Project Folder"));
            QAction *newFile = menu.addAction(tr("New"));
            QAction *duplicateFile = menu.addAction(tr("Duplicate"));
            QAction *renameFile = menu.addAction(tr("Rename"));
            QAction *removeFile = menu.addAction(tr("Remove"));
            QAction *ret = menu.exec(inspector->getProjectFiles()->mapToGlobal(point));

            if (ret == openProject) {
                actionOpen();
            } else {
                if (ret == newFile) {
                    actionNew();
                } else if (ret == duplicateFile) {
                    if(currentDocument) {
                        bool ok;
                        QString text = QInputDialog::getText(0, tr("File duplication"), tr("Name of duplicate script:"), QLineEdit::Normal, fileList->getScriptFile().baseName(), &ok);
                        QString f = fileList->getScriptFile().absoluteFilePath().replace(fileList->getScriptFile().baseName()+".", text+".");
                        if((ok) && (f != "")) {
                            if(!QFile::exists(f)) {
                                QFile::copy(fileList->getScriptFile().absoluteFilePath(), f);
                            }
                            else {
                                QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QMessageBox::Ok);
                            }
                        }
                    }
                } else if (ret == renameFile) {
                    actionRename();
                } else if (ret == removeFile) {
                    actionRemove();
                }
                QDir examplesDir("./Examples/");
                QDir libDir("./Tools/");
                QDir projectDir("./Project/");
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
        if(scriptList) {
            QMenu menu(inspector);
            QAction *runFile = menu.addAction(tr("Run"));
            QAction *openFile = menu.addAction(tr("Open"));
            QAction *externalOpenFile = menu.addAction(tr("Open with default external editor"));
            QAction *newFile = menu.addAction(tr("New"));
            QAction *duplicateFile = menu.addAction(tr("Duplicate"));
            QAction *renameFile = menu.addAction(tr("Rename"));
            QAction *removeFile = menu.addAction(tr("Remove"));
            QAction *ret = menu.exec(inspector->getProjectScripts()->mapToGlobal(point));

            if(ret == runFile) {
                actionProjectScripts();
            } else if (ret == openFile) {
                editor->openFile(scriptList->getScriptFile());
            } else if (ret == externalOpenFile) {
                fileWatcher.addPath(scriptList->getScriptFile().absoluteFilePath());
                QDesktopServices::openUrl(QUrl("file:///" + scriptList->getScriptFile().absoluteFilePath().replace("\\", "/"), QUrl::TolerantMode));
            } else {
                if (ret == newFile) {
                    if(currentDocument) {
                        bool ok;
                        QString text = QInputDialog::getText(0, tr("New script"), tr("Name of new script:"), QLineEdit::Normal, "New Document " + QDateTime::currentDateTime().toString("MMddhhmmss"), &ok);
                        QString f = scriptList->getScriptFile().absoluteFilePath().replace(scriptList->getScriptFile().baseName()+".", text+".");
                        if((ok) && (text != "")) {
                            if(!QFile::exists(f)) {
                                QFile newFile(f);
                                if(newFile.open(QIODevice::WriteOnly)) {
                                    QTextStream out(&newFile);
                                    out << "//Script \"" << text << "\"\n//Insert requests for global variables:\nfunction onConfigure() {\n    //title(\"enter title here\");\n    //ask(\"prompt\", \"groupName\", \"variableName\", defaultValue);\n};\n//Insert code to create score:\nfunction onCreate() {\n\n\n};\n";
                                    newFile.close();
                                }
                            }
                            else {
                                QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QMessageBox::Ok);
                            }
                        }
                    }
                } else if (ret == duplicateFile) {
                    if(currentDocument) {
                        bool ok;
                        QString text = QInputDialog::getText(0, tr("File duplication"), tr("Name of duplicate script:"), QLineEdit::Normal, scriptList->getScriptFile().baseName(), &ok);
                        QString f = scriptList->getScriptFile().absoluteFilePath().replace(scriptList->getScriptFile().baseName()+".", text+".");
                        if((ok) && (f != "")) {
                            if(!QFile::exists(f)) {
                                QFile::copy(scriptList->getScriptFile().absoluteFilePath(), f);
                            }
                            else {
                                QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be created! A file with this name exists in your project."), QMessageBox::Ok);
                            }
                        }
                    }
                } else if (ret == renameFile) {
                    if(currentDocument) {
                        bool ok;
                        QString text = QInputDialog::getText(0, tr("File rename"), tr("New name of script:"), QLineEdit::Normal, scriptList->getScriptFile().baseName(), &ok);
                        QString f = scriptList->getScriptFile().absoluteFilePath().replace(scriptList->getScriptFile().baseName()+".", text+".");
                        if((ok) && (f != "")) {
                            if(!QFile::exists(f)) {
                                QFile::rename(scriptList->getScriptFile().absoluteFilePath(), f);
                            }
                            else {
                                QMessageBox::information(0, tr("Filename conflict"), tr("The file can't be renamed! A file with this name exists in your project."), QMessageBox::Ok);
                            }
                        }
                    }
                } else if (ret == removeFile) {
                    if(currentDocument) {
                        int rep = QMessageBox::question(0, tr("File remove"), tr("The file will be removed from your disk. Are you sure?"), QMessageBox::Yes | QMessageBox::No);
                        if(rep == QMessageBox::Yes) {
                            QFile::remove(scriptList->getScriptFile().absoluteFilePath());
                        }
                    }
                }
                QDir examplesDir("./Examples/");
                QDir libDir("./Tools/");
                QDir projectDir("./Project/");
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", libDir, libScript, false);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", examplesDir, exampleScript, false);
                fileWatcherFolder(QStringList() << "*.nxscript" << "*.nxstyle", projectDir, projectScript, false);
            }
        }
    }
}




NxGroup* IanniX::addGroup(const QString & documentId, const QString & groupId) {
    NxGroup *group = new NxGroup(this, inspector->getViewGroup(), inspector->getWasGroupChecked(groupId));
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
            foreach(NxObject *object, curve->getCursors())
                commands << COMMAND_REMOVE + " " + QString().setNum(object->getId()) + COMMAND_END;
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
            inspector->updateWasGroupChecked(group);
            delete group;
        }

        render->selectionClear(true);

        delete object;
    }
}


const QVariant IanniX::execute(const QString & command, bool createNewObjectIfExists, bool) {
    QStringList arguments = command.split(" ", QString::SkipEmptyParts);
    if((arguments.count() > 0) && (currentDocument)) {
        QString commande = arguments.at(0).toLower();
        if((commande == COMMAND_ADD) && (arguments.count() >= 3)) {
            bool ok = false;
            qint16 id = arguments.at(2).toUInt(&ok);
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
            //sendMessage(syncObject, 0, 0, 0, NxPoint(), NxPoint(), commandReplace.replace("auto", QString().setNum(id)));

            NxObject *object = 0;
            QString type = arguments.at(1).toLower();
            if(type == "curve")
                object = new NxCurve(this, inspector->getCurveItem(), render->getRenderOptions());
            else if(type == "cursor")
                object = new NxCursor(this, inspector->getCursorItem(), render->getRenderOptions());
            else
                object = new NxTrigger(this, inspector->getTriggerItem(), render->getRenderOptions());

            if(object) {
                object->dispatchProperty("documentId", currentDocument->getId());
                object->dispatchProperty("groupId", "");
                object->dispatchProperty("id", id);
                object->dispatchProperty("active", ObjectsActivityActive);
                object->dispatchProperty("posStr", "0 0");
                if(object->getType() == ObjectsTypeTrigger)
                    object->dispatchProperty("messagePatterns", "1,"+defaultMessageTrigger);
                else if(object->getType() == ObjectsTypeCursor)
                    object->dispatchProperty("messagePatterns", "20,"+defaultMessageCursor);
                object->setParentObject(parentObject);

                if(parentObject) {
                    NxPoint posOffset(0.5, -0.5);
                    /*
                    if(parentObject->getParentObject())
                        posOffset = parentObject->getPos() - parentObject->getParentObject()->getPos();
                    */
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
            //sendMessage(syncObject, 0, 0, 0, NxPoint(), NxPoint(), command);

            if((commande == COMMAND_TEXTURE) && (arguments.count() >= 7)) {
                QString filename = command.mid(command.indexOf(arguments.at(6), command.indexOf(arguments.at(5))+arguments.at(5).length())).trimmed();
                if(!QFile().exists(filename))
                    filename = scriptDir.absoluteFilePath(filename);
                render->loadTexture(arguments.at(1).trimmed(), filename, NxRect(NxPoint(arguments.at(2).toDouble(), arguments.at(3).toDouble()), NxPoint(arguments.at(4).toDouble(), arguments.at(5).toDouble())));
            }
            else if((commande == COMMAND_GLOBAL_COLOR) && (arguments.count() >= 6)) {
                render->getRenderOptions()->colors[arguments.at(1)] = QColor(arguments.at(2).toDouble(), arguments.at(3).toDouble(), arguments.at(4).toDouble(), arguments.at(5).toDouble());
            }
            else if(((commande == COMMAND_GLOBAL_COLOR2) || (commande == COMMAND_GLOBAL_COLOR_HUE)) && (arguments.count() >= 6)) {
                QColor color;
                color.setHsv(arguments.at(2).toDouble(), arguments.at(3).toDouble(), arguments.at(4).toDouble(), arguments.at(5).toDouble());
                render->getRenderOptions()->colors[arguments.at(1)] = color;
            }
            else if((commande == COMMAND_ZOOM) && (arguments.count() >= 2)) {
                render->zoom(arguments.at(1).toDouble());
            }
            else if((commande == COMMAND_ROTATE) && (arguments.count() >= 4)) { ///CG/// Add command to set rotationX, rotationY, rotationZ;
                NxPoint _rotation(arguments.at(1).toDouble(),arguments.at(2).toDouble(),arguments.at(3).toDouble());
                render->rotateTo(_rotation);
            }
            else if((commande == COMMAND_CENTER) && (arguments.count() >= 3)) {
                render->getRenderOptions()->axisCenterDest = NxPoint(-arguments.at(1).toDouble(), -arguments.at(2).toDouble());
                render->zoom();
            }
            else if((commande == COMMAND_PLAY) && (arguments.count() >= 2)) {
                if(arguments.at(1).toDouble() != 0) {
                    transport->setSpeed(arguments.at(1).toDouble());
                    setScheduler(SchedulerOn);
                    sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "play");
                }
                else {
                    setScheduler(SchedulerOff);
                    sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "stop");
                }
                actionSpeed();
            }
            else if((commande == COMMAND_TITLE) && (arguments.count() >= 1)) {
                return view->windowTitle();
            }
            else if((commande == COMMAND_STOP) && (arguments.count() >= 1)) {
                setScheduler(SchedulerOff);
                sendMessage(transportObject, 0, 0, 0, NxPoint(), NxPoint(), "stop");
                actionSpeed();
            }
            else if((commande == COMMAND_GOTO) && (arguments.count() >= 2)) {
                actionGoto(arguments.at(1).toDouble());
            }
            else if((commande == COMMAND_GOTO) && (arguments.count() >= 1)) {
                return timeLocal;
            }
            else if((commande == COMMAND_SLEEP) && (arguments.count() >= 2)) {
                QMutex mutex;
                QWaitCondition sleep;
                sleep.wait(&mutex, arguments.at(1).toDouble());
            }
            else if((commande == COMMAND_FF) && (arguments.count() >= 1)) {
                actionFast_rewind();
            }
            else if((commande == COMMAND_LOG) && (arguments.count() >= 2)) {
                lastMessage = command.mid(command.indexOf(arguments.at(1), command.indexOf(arguments.at(0))+1)).trimmed();
                this->logOscReceive(tr("Script:") + QString(" %1").arg(lastMessage));
            }
            else if((commande == COMMAND_CLEAR) && (arguments.count() >= 1)) {
                if(currentDocument) {
                    pushSnapshot();
                    currentDocument->clear();
                }
            }
            else if((commande == COMMAND_SNAP_POP) && (arguments.count() >= 2)) {
                if(currentDocument) {
                    render->selectionClear(true);
                    currentDocument->popSnapshot(command.mid(command.indexOf(arguments.at(1), command.indexOf(arguments.at(0))+arguments.at(0).length())).trimmed());
                }
            }
            else if((commande == COMMAND_SNAP_PUSH) && (arguments.count() >= 2)) {
                if(currentDocument)
                    currentDocument->pushSnapshot(command.mid(command.indexOf(arguments.at(1), command.indexOf(arguments.at(0))+arguments.at(0).length())).trimmed());
            }
            else if((commande == COMMAND_SNAP_POP) && (arguments.count() >= 1)) {
                if(currentDocument) {
                    render->selectionClear(true);
                    currentDocument->popSnapshot();
                }
            }
            else if((commande == COMMAND_SNAP_PUSH) && (arguments.count() >= 1)) {
                pushSnapshot();
            }
            else if((commande == COMMAND_SPEED) && (arguments.count() >= 2)) {
                transport->setSpeed(arguments.at(1).toDouble());
                return transport->getSpeed();
            }
            else if((commande == COMMAND_SPEED) && (arguments.count() >= 1)) {
                return transport->getSpeed();
            }
            else if((commande == COMMAND_TOGGLE_GROUP) && (arguments.count() >= 3)) {
                Qt::CheckState state = Qt::Unchecked;
                if(arguments.at(2).toUInt() > 0)
                    state = Qt::Checked;
                if((currentDocument) && (currentDocument->groups.contains(arguments.at(1))))
                    currentDocument->groups.value(arguments.at(1))->setCheckState(0, state);
            }
            else if((commande == COMMAND_MOUSE) && (arguments.count() >= 3)) {
                QCursor::setPos(arguments.at(1).toInt(), arguments.at(2).toInt());
            }
            else if((commande == COMMAND_MESSAGE_SEND) && (arguments.count() >= 2)) {
                QString mess = "1," + command.mid(command.indexOf(arguments.at(1), command.indexOf(arguments.at(0))+arguments.at(0).length()));
                NxTrigger *obj = new NxTrigger(this, 0, 0);
                obj->setMessagePatterns(mess);
                obj->trig(0);
                delete obj;
            }
            else if((commande == COMMAND_AUTOSIZE) && (arguments.count() >= 2)) {
                render->setTriggerAutosize(arguments.at(1).toDouble());
            }

            else if(arguments.count() >= 2) {
                QString objTxt;
                objTxt = qPrintable(arguments.at(1));
                NxObjectDispatchProperty *object = getObject(objTxt);

                if(object) {
                    if((commande == COMMAND_REMOVE) && (arguments.count() >= 2)) {
                        if((object->getType() == ObjectsTypeCursor) || (object->getType() == ObjectsTypeCurve) || (object->getType() == ObjectsTypeTrigger)) {
                            NxObject *objectObj = (NxObject*)object;
                            removeObject(objectObj);
                        }
                        return 0;
                    }
                    else if((commande == COMMAND_GROUP) && (arguments.count() >= 3)) {
                        if((object->getType() == ObjectsTypeCursor) || (object->getType() == ObjectsTypeCurve) || (object->getType() == ObjectsTypeTrigger)) {
                            NxObject *objectObj = (NxObject*)object;
                            QString groupId = arguments.at(2);
                            if(groupId == "")
                                groupId = documents[objectObj->getDocumentId()]->getCurrentGroup()->getId();
                            objectObj->dispatchProperty("groupId", groupId);
                        }
                    }

                    else if((commande == COMMAND_CURSOR_CURVE) && (arguments.count() >= 2)) {
                        if(object->getType() == ObjectsTypeCursor) {
                            NxCursor *cursor = (NxCursor*)object;
                            NxObject *object2 = (NxObject*)getObject(qPrintable(arguments.at(2)), false);
                            if((object2) && (object2->getType() == ObjectsTypeCurve)) {
                                NxCurve *curve = (NxCurve*)object2;
                                cursor->setCurve(curve);
                                cursor->calculate();
                                return curve->getPathLength();
                            }
                        }
                    }

                    else if((commande == COMMAND_LABEL) && (arguments.count() >= 3)) {
                        object->dispatchProperty("label", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }

                    else if((commande == COMMAND_RESIZE) && (arguments.count() >= 4)) {
                        object->dispatchProperty("resizeStr", arguments.at(2) + " " + arguments.at(3));
                    }
                    else if((commande == COMMAND_RESIZEF) && (arguments.count() >= 3)) {
                        object->dispatchProperty("resizeF", arguments.at(2).toDouble());
                    }

                    else if((commande == COMMAND_CURSOR_WIDTH) && (arguments.count() >= 3)) {
                        object->dispatchProperty("cursorWidth", arguments.at(2).toDouble());
                    }

                    else if((commande == COMMAND_LINE) && (arguments.count() >= 4)) {
                        object->dispatchProperty("lineStipple", arguments.at(2).toDouble());
                        object->dispatchProperty("lineFactor", arguments.at(3).toDouble());
                    }
                    else if((commande == COMMAND_SIZE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("size", arguments.at(2).toDouble());
                    }

                    else if((commande == COMMAND_CURSOR_START) && (arguments.count() >= 5)) {
                        object->dispatchProperty("easingStart", arguments.at(2).toDouble());
                        object->dispatchProperty("start", command.mid(command.indexOf(arguments.at(4), command.indexOf(arguments.at(3))+arguments.at(3).length())).trimmed());
                    }

                    else if((commande == COMMAND_CURSOR_SPEED) && (arguments.count() >= 4)) {
                        if(arguments.at(2) == "auto")
                            object->dispatchProperty("timeFactorAuto", arguments.at(3).toDouble());
                    }
                    else if((commande == COMMAND_CURSOR_SPEED) && (arguments.count() >= 3)) {
                        object->dispatchProperty("timeFactor", arguments.at(2).toDouble());
                    }
                    else if((commande == COMMAND_CURSOR_SPEEDF) && (arguments.count() >= 3)) {
                        object->dispatchProperty("timeFactorF", arguments.at(2).toDouble());
                    }
                    else if((commande == COMMAND_CURSOR_OFFSET) && (arguments.count() >= 5)) {
                        object->dispatchProperty("timeInitialOffset", arguments.at(2).toDouble());
                        object->dispatchProperty("timeStartOffset", arguments.at(3).toDouble());
                        if(arguments.at(4).toLower() == "end")
                            object->dispatchProperty("timeEndOffset", -1);
                        else
                            object->dispatchProperty("timeEndOffset", arguments.at(4).toDouble());
                    }
                    else if((commande == COMMAND_CURSOR_BOUNDS_SOURCE) && (arguments.count() >= 6)) {
                        object->dispatchProperty("boundsSource", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if((commande == COMMAND_CURSOR_BOUNDS_TARGET) && (arguments.count() >= 6)) {
                        object->dispatchProperty("boundsTarget", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if((commande == COMMAND_CURSOR_TIME) && (arguments.count() >= 3)) {
                        object->dispatchProperty("timeLocal", arguments.at(2).toDouble());
                    }


                    else if((commande == COMMAND_CURVE_POINT_RMV) && (arguments.count() >= 3)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->removePointAt(arguments.at(2).toDouble());
                        }
                    }
                    else if((commande == COMMAND_CURVE_POINT_SHIFT) && (arguments.count() >= 4)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->shiftPointAt(arguments.at(2).toUInt(), arguments.at(3).toInt());
                        }
                    }
                    else if((commande == COMMAND_CURVE_POINT_TRANSLATE) && (arguments.count() >= 5)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->translate(NxPoint(arguments.at(2).toDouble(), arguments.at(3).toDouble(), arguments.at(4).toDouble()));
                        }
                    }
                    else if((commande == COMMAND_CURVE_POINT) && (arguments.count() >= 5)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(arguments.count() >= 21)  // 3+18 (x, y, z, sx, sy, sz), (c1x, c1y, c1z, c1sx, c1sy, c1sz), (c2x, c2y, c2z, c2sx, c2sy, c2z)
                                curve->setPointAt(arguments.at(2).toDouble(),
                                                  NxPoint(arguments.at(3).toDouble(),  arguments.at(4).toDouble(),  arguments.at(5).toDouble(),  arguments.at(6).toDouble(),  arguments.at(7).toDouble(),  arguments.at(8).toDouble()),
                                                  NxPoint(arguments.at(9).toDouble(),  arguments.at(10).toDouble(), arguments.at(11).toDouble(), arguments.at(12).toDouble(), arguments.at(13).toDouble(), arguments.at(14).toDouble()),
                                                  NxPoint(arguments.at(15).toDouble(), arguments.at(16).toDouble(), arguments.at(17).toDouble(), arguments.at(18).toDouble(), arguments.at(19).toDouble(), arguments.at(20).toDouble()), false);
                            else if(arguments.count() >= 15)  // 3+12 (x, y, sx, sy), (c1x, c1y, c1sx, c1sy), (c2x, c2y, c2sx, c2sy)
                                curve->setPointAt(arguments.at(2).toDouble(),
                                                  NxPoint(arguments.at(3).toDouble(),  arguments.at(4).toDouble(),  0, arguments.at(5).toDouble(),  arguments.at(6).toDouble(),  0),
                                                  NxPoint(arguments.at(7).toDouble(),  arguments.at(8).toDouble(),  0, arguments.at(9).toDouble(),  arguments.at(10).toDouble(), 0),
                                                  NxPoint(arguments.at(11).toDouble(), arguments.at(12).toDouble(), 0, arguments.at(13).toDouble(), arguments.at(14).toDouble(), 0), false);
                            else if(arguments.count() >= 12) // 3+9 (x, y, z), (c1x, c1y, c1z), (c2x, c2y, c2z)
                                curve->setPointAt(arguments.at(2).toDouble(),
                                                  NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble(),  arguments.at(5).toDouble()),
                                                  NxPoint(arguments.at(6).toDouble(), arguments.at(7).toDouble(),  arguments.at(8).toDouble()),
                                                  NxPoint(arguments.at(9).toDouble(), arguments.at(10).toDouble(), arguments.at(11).toDouble()), false);
                            else if(arguments.count() >= 10) // 3+6 (x, y, z, sx, sy, sz) // REQUIRES A DUMMY ARGUMENT
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble(), arguments.at(5).toDouble(), arguments.at(6).toDouble(), arguments.at(7).toDouble(), arguments.at(8).toDouble()), false);
                            else if(arguments.count() >= 9)  // 3+6 (x, y), (c1x, c1y), (c2x, c2y)
                                curve->setPointAt(arguments.at(2).toDouble(),
                                                  NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble()),
                                                  NxPoint(arguments.at(5).toDouble(), arguments.at(6).toDouble()),
                                                  NxPoint(arguments.at(7).toDouble(), arguments.at(8).toDouble()), false);
                            else if(arguments.count() >= 7) // 3+4 (x, y, sx, sy)
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble(), 0, arguments.at(5).toDouble(), arguments.at(6).toDouble(), 0), false);
                            else if(arguments.count() >= 6) // 3+3 (x, y, z)
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble(), arguments.at(5).toDouble()), false);
                            else if(arguments.count() >= 5) // 3+2 (x, y)
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble()), false);
                            return curve->getPathLength();
                        }
                    }
                    else if((commande == COMMAND_CURVE_POINT_SMOOTH) && (arguments.count() >= 5)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            if(arguments.count() >= 9)      // 3+6 (x, y, z, sx, sy, sz)
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble(), arguments.at(5).toDouble(), arguments.at(6).toDouble(), arguments.at(7).toDouble(), arguments.at(8).toDouble()), true);
                            else if(arguments.count() >= 7) // 3+4 (x, y, sx, sy)
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble(), 0, arguments.at(5).toDouble(), arguments.at(6).toDouble(), 0), true);
                            else if(arguments.count() >= 6) // 3+3 (x, y, z)
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble(), arguments.at(5).toDouble()), true);
                            else if(arguments.count() >= 5) // 3+2 (x, y)
                                curve->setPointAt(arguments.at(2).toDouble(), NxPoint(arguments.at(3).toDouble(), arguments.at(4).toDouble()), true);
                        }
                    }

                    else if((commande == COMMAND_CURVE_TXT) && (arguments.count() >= 5)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->setText(arguments.at(4), arguments[3].replace("_", " ").trimmed());
                            curve->setResizeF(arguments.at(2).toDouble());
                            return curve->getPathLength();
                        }
                    }
                    else if(((commande == COMMAND_CURVE_SVG) || (commande == COMMAND_CURVE_PATH)) && (arguments.count() >= 4)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->setSVG(command.mid(command.indexOf(arguments.at(3), command.indexOf(arguments.at(2))+arguments.at(2).length())).trimmed());
                            curve->setResizeF(arguments.at(2).toDouble());
                            return curve->getPathLength();
                        }
                    }
                    else if(((commande == COMMAND_CURVE_SVG2) || (commande == COMMAND_CURVE_LINES)) && (arguments.count() >= 4)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->setSVG2(command.mid(command.indexOf(arguments.at(3), command.indexOf(arguments.at(2))+arguments.at(2).length())).trimmed());
                            curve->setResizeF(arguments.at(2).toDouble());
                            return curve->getPathLength();
                        }
                    }
                    else if((commande == COMMAND_CURVE_IMG) && (arguments.count() >= 4)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->setImage(command.mid(command.indexOf(arguments.at(3), command.indexOf(arguments.at(2))+arguments.at(2).length())).trimmed());
                            curve->setResizeF(arguments.at(2).toDouble());
                            return curve->getPathLength();
                        }
                    }

                    //Compatibility
                    else if((commande == COMMAND_CURVE_SVG) && (arguments.count() >= 5)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->setSVG(command.mid(command.indexOf(arguments.at(4), command.indexOf(arguments.at(3))+arguments.at(2).length())).trimmed());
                            curve->setResize(NxSize(arguments.at(2).toDouble(), arguments.at(3).toDouble()));
                            return curve->getPathLength();
                        }
                    }

                    else if((commande == COMMAND_CURVE_ELL) && (arguments.count() >= 4)) {
                        if(object->getType() == ObjectsTypeCurve) {
                            NxCurve *curve = (NxCurve*)object;
                            curve->setEllipse(NxSize(arguments.at(2).toDouble(), arguments.at(3).toDouble()));
                            return curve->getPathLength();
                        }
                    }

                    else if((commande == COMMAND_POS) && (arguments.count() >= 5)) {
                        object->dispatchProperty("posStr", arguments.at(2) + " " + arguments.at(3) + " " + arguments.at(4));
                    }
                    else if((commande == COMMAND_ACTIVE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("active", arguments.at(2).toDouble());
                    }

                    else if((commande == COMMAND_COLOR_GLOBAL) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorActive", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                        object->dispatchProperty("colorInactive", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                        object->dispatchProperty("colorActiveMessage", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                        object->dispatchProperty("colorInactiveMessage", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if((commande == COMMAND_COLOR_ACTIVE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorActive", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if((commande == COMMAND_COLOR_INACTIVE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorInactive", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if((commande == COMMAND_COLOR_ACTIVE_MESSAGE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorActiveMessage", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if((commande == COMMAND_COLOR_INACTIVE_MESSAGE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorInactiveMessage", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }

                    else if((commande == COMMAND_COLOR_GLOBAL_HUE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorActiveHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                        object->dispatchProperty("colorInactiveHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                        object->dispatchProperty("colorActiveMessageHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                        object->dispatchProperty("colorInactiveMessageHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if(((commande == COMMAND_COLOR_ACTIVE2) || (commande == COMMAND_COLOR_ACTIVE_HUE)) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorActiveHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if(((commande == COMMAND_COLOR_INACTIVE2) || (commande == COMMAND_COLOR_INACTIVE_HUE)) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorInactiveHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if(((commande == COMMAND_COLOR_ACTIVE_MESSAGE2) || (commande == COMMAND_COLOR_ACTIVE_MESSAGE_HUE)) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorActiveMessageHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if(((commande == COMMAND_COLOR_INACTIVE_MESSAGE2) || (commande == COMMAND_COLOR_INACTIVE_MESSAGE_HUE)) && (arguments.count() >= 3)) {
                        object->dispatchProperty("colorInactiveMessageHue", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }

                    else if((commande == COMMAND_MESSAGE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("messagePatterns", command.mid(command.indexOf(arguments.at(2), command.indexOf(arguments.at(1))+arguments.at(1).length())).trimmed());
                    }
                    else if((commande == COMMAND_TRIGGER_OFF) && (arguments.count() >= 3)) {
                        object->dispatchProperty("triggerOff", arguments.at(2));
                    }

                    else if((commande == COMMAND_TEXTURE_GLOBAL) && (arguments.count() >= 3)) {
                        object->dispatchProperty("textureActive", arguments.at(2));
                        object->dispatchProperty("textureInactive", arguments.at(2));
                        object->dispatchProperty("textureActiveMessage", arguments.at(2));
                        object->dispatchProperty("textureInactiveMessage", arguments.at(2));
                    }
                    else if((commande == COMMAND_TEXTURE_ACTIVE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("textureActive", arguments.at(2));
                    }
                    else if((commande == COMMAND_TEXTURE_INACTIVE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("textureInactive", arguments.at(2));
                    }
                    else if((commande == COMMAND_TEXTURE_ACTIVE_MESSAGE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("textureActiveMessage", arguments.at(2));
                    }
                    else if((commande == COMMAND_TEXTURE_INACTIVE_MESSAGE) && (arguments.count() >= 3)) {
                        object->dispatchProperty("textureInactiveMessage", arguments.at(2));
                    }

                    return object->getProperty("id").toDouble();
                }
            }
        }
    }
    return 0;
}

void IanniX::sendMessage(void *_object, void *_trigger, void *_cursor, void *_collisionCurve, const NxPoint & collisionPoint, const NxPoint & collisionValue, const QString & status) {
    NxObject *object = (NxObject*)_object;
    if(object) {
        NxTrigger *trigger = (NxTrigger*)_trigger;
        NxCursor *cursor = (NxCursor*)_cursor;
        NxCurve* collisionCurve = (NxCurve*)_collisionCurve;
        NxCurve *curve = 0;
        if(cursor)
            curve = cursor->getCurve();

        QStringList sentMessages;
        foreach(const QVector<QByteArray> & messagePattern, object->getMessagePatterns()) {
            if(messagesCache.contains(messagePattern.at(0)))
                message = messagesCache.value(messagePattern.at(0));
            else {
                message.setUrl(QUrl(messagePattern.at(0), QUrl::TolerantMode), &messageScriptEngine);
                messagesCache.insert(messagePattern.at(0), message);
            }
            if(message.parse(messagePattern, trigger, cursor, curve, collisionCurve, collisionPoint, collisionValue, status, inspector->nbTriggers, inspector->nbCursors, inspector->nbCurves)) {
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
    return render->grabFrameBuffer(false);
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

void IanniX::askNxObject() {
    inspector->actionMessages();
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
    foreach(NxObject *object, *(render->getSelection())) {
        if(object->getType() == ObjectsTypeCurve) {
            freeCursor = false;
            NxCurve *curve = (NxCurve*)object;
            quint16 cursorId = execute(QString("add cursor auto")).toUInt();
            execute(QString("setCurve %1 %2").arg(cursorId).arg(curve->getId()));
            execute(QString("setPattern %1 0 0 1").arg(cursorId));
            execute(QString("setOffset %1 %2 0 end").arg(cursorId).arg(curve->getMaxOffset() / 2));
        }
    }
    if(freeCursor) {
        quint16 cursorId = execute(QString("add cursor auto")).toUInt();
        execute(QString("setPattern %1 0 0 1").arg(cursorId));
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
            execute(QString("setPattern %1 0 0 1").arg(cursorId));
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
void IanniX::actionSnapGrid() {
    render->actionSnapGrid();
}
void IanniX::actionShowEditor() {
    editor->show();
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

void IanniX::actionCloseEvent(QCloseEvent *event) {
    quint16 nbFileNoSave = 0;
    QHashIterator<QString, NxDocument*> documentIterator(documents);
    while (documentIterator.hasNext()) {
        documentIterator.next();
        NxDocument *document = documentIterator.value();
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

    QSettings settings;
    settings.setValue("oscPort", inspector->getOSCPort());
    settings.setValue("udpPort", inspector->getUDPPort());
    settings.setValue("httpPort", inspector->getHttpPort());
    settings.setValue("serialPort", inspector->getSerialPort());
    settings.setValue("defaultMessageTransport", inspector->getTransportMessage());
    settings.setValue("defaultMessageSync", inspector->getSyncMessage());
    settings.setValue("bundleHost", inspector->getBundleHost());
    settings.setValue("bundlePort", inspector->getBundlePort());
    settings.setValue("colorTheme", render->getColorTheme());
    settings.setValue("opacityCurve", inspector->getViewCurveOpacityCheck());

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
    qDebug("ICI");
    QStringList commands = currentDocument->serialize(render->getRenderOptions()).split(COMMAND_END);
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
        if(destroyKey != "")
            documents.remove(destroyKey);
        parentList->removeChild(document);
    }
    parentList->sortChildren(0, Qt::AscendingOrder);
}

void IanniX::logOscSend(const QString & message) {
    if(lastMessageAllow) {
        lastMessage = message;
        lastMessageAllow = false;
    }
    if(oscConsoleActive)
        inspector->logOscSend(message);
}
void IanniX::logOscReceive(const QString & message) {
    if(oscConsoleActive)
        inspector->logOscReceive(message);
}
void IanniX::pushSnapshot() {
    if(currentDocument)
        currentDocument->pushSnapshot();
}

