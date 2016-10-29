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

#include "interfaceosc.h"
#include "ui_interfaceosc.h"

InterfaceOsc::InterfaceOsc(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceOsc) {
    ui->setupUi(this);
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));
    socket = 0;

    bonjourMenu = new QMenu(this);
    connect(ui->bonjour,       SIGNAL(released()), SLOT(openBonjour()));
    connect(ui->bonjourBundle, SIGNAL(released()), SLOT(openBonjour()));
    connect(ui->bonjourPortIn, SIGNAL(released()), SLOT(openBonjour()));
#ifdef ZEROCONF_AS_BROWSER
    bonjourListCurrent = -1;
    bonjourResolver = 0;
    bonjourRegisterIn = bonjourRegisterOut = 0;
    bonjourBrowser = 0;
#endif
    bonjourScan();

    //OSC adress of IanniX
    oscMatchAdressIanniX    = "/iannix/";
    oscMatchAdressTransport = "/transport/";
    bundleMessageId = 0;

    bundlePort = 0;
    bundleMessageId = 0;

    //Interfaces link
    enable.setAction(ui->enable,         "interfaceOscEnable");
    bundlePort.setAction(ui->bundlePort, "interfaceOscBundlePort");
    port.setAction(ui->port,             "interfaceOscPort");
    bundleHost.setAction(ui->bundleIp,   "interfaceOscBundleHost");
    connect(&port, SIGNAL(triggered(qreal)), SLOT(portChanged()));
    MessageManager::aliases["ip_out"]  .setAction(ui->aliasIp,   "interfaceOscOutIp");
    MessageManager::aliases["port_out"].setAction(ui->aliasPort, "interfaceOscOutPort");
    connect(&MessageManager::aliases["port_out"], SIGNAL(triggered(QString)), SLOT(portOutChanged()));
    MessageManager::aliases["ip_out"]   = "127.0.0.1";
    MessageManager::aliases["port_out"] = "57120";
    port = 1234;
    bundlePort = 57130;
    bundleHost = "127.0.0.1";
}

void InterfaceOsc::portChanged() {
    //Create a new UDP socket and bind signals
    if(socket)
        delete socket;
    socket = new QUdpSocket(this);
    socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(socket, SIGNAL(readyRead()), SLOT(parseOSC()));

    if(socket->bind(port))  ui->port->setStyleSheet(ihmFeedbackOk);
    else                    ui->port->setStyleSheet(ihmFeedbackNok);

    UiHelp::oscPort = port;

#ifdef ZEROCONF_AS_SERVICE
    if(bonjourRegisterIn) delete bonjourRegisterIn;
    bonjourRegisterIn = new BonjourServiceRegister(this);
    bonjourRegisterIn->registerService(BonjourRecord(tr("To IanniX"), "_osc._udp", ""), port);
#endif
}
void InterfaceOsc::portOutChanged() {
#ifdef ZEROCONF_AS_SERVICE
    if(bonjourRegisterOut) delete bonjourRegisterOut;
    bonjourRegisterOut = new BonjourServiceRegister(this);
    bonjourRegisterOut->registerService(BonjourRecord(tr("From IanniX"), "_osc._udp", ""), MessageManager::aliases["port_out"].val().toDouble());
#endif
}

#ifdef ZEROCONF_AS_BROWSER
void InterfaceOsc::currentBonjourRecordsChanged(const QList<BonjourRecord> &list) {
    foreach(const BonjourRecord &record, list) {
        bool toAdd = true;
        for(quint16 i = 0 ; i < bonjourServices.count() ; i++) {
            if((bonjourServices.at(i).record == record)) {
                toAdd = false;
                bonjourServices[i].reset();
            }
        }
        if(toAdd)
            bonjourServices.append(BonjourService(record));
    }
    bonjourIsScanning = false;
    bonjourRecordResolved();
}
void InterfaceOsc::bonjourRecordResolved() {
    if(bonjourListCurrent < 0) {
        for(quint16 i = 0 ; i < bonjourServices.count() ; i++) {
            if(bonjourServices.at(i).port == 0) {
                bonjourListCurrent = i;
                bonjourResolver = new BonjourServiceResolver(this);
                connect(bonjourResolver, SIGNAL(bonjourRecordResolved(const QHostInfo &, int)), this, SLOT(bonjourRecordResolved(const QHostInfo &, int)));
                bonjourResolver->resolveBonjourRecord(bonjourServices.at(i).record);
                return;
            }
        }
    }
}
void InterfaceOsc::bonjourRecordResolved(const QHostInfo &info, int port) {
    //qDebug("> %d Scan RES", QDateTime::currentDateTime().currentMSecsSinceEpoch());
    if((bonjourListCurrent >= 0) && (info.addresses().count())) {
        bonjourServices[bonjourListCurrent].host = info.addresses().first();
        bonjourServices[bonjourListCurrent].port = port;
        //qDebug(">>%s (%d)", qPrintable(bonjourServices.at(bonjourListCurrent).record.serviceName), bonjourServices.at(bonjourListCurrent).port);
        bonjourListCurrent = -1;
    }
    bonjourRecordResolved();
}
#endif
void InterfaceOsc::bonjourScan() {
    //Templates
    QFileInfoList files = QDir(Application::pathApplication.absoluteFilePath() + "/Tools/Templates/").entryInfoList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    files <<              QDir(Application::pathDocuments.absoluteFilePath()   + "/Templates/").entryInfoList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    foreach(const QFileInfo &file, files) {
        QString header;
        QMultiHash<QString, QString> params;
        QFile templateFile(file.absoluteFilePath());
        if(templateFile.open(QFile::ReadOnly)) {
            QStringList templatesLong = QString(templateFile.readAll()).split("\n", QString::SkipEmptyParts);
            foreach(const QString &templateLong, templatesLong) {
                if(templateLong.startsWith("["))
                    header = templateLong.toLower();
                else if(header == "[general]") {
                    QStringList templateLongSplit = templateLong.split("=");
                    if(templateLongSplit.count() > 1) {
                        QString key = templateLongSplit.at(0).toLower(), value = templateLongSplit.at(1);
                        params.insert(key, value);
                    }
                }
            }
        }

        //Interfaces
        if(params.contains("name")) {
            QHashIterator<QString, QString> paramsIterator(params);
            while (paramsIterator.hasNext()) {
                paramsIterator.next();
                if(paramsIterator.key() == "interface") {
                    bool toAdd = true;
                    QStringList paramsSplit = paramsIterator.value().split(" | ");
                    if(paramsSplit.count() > 1) {
                        QString serviceName = QString("%1 (%2)").arg(params.value("name")).arg(paramsSplit.at(1).trimmed());
                        for(quint16 i = 0 ; i < bonjourServices.count() ; i++)
                            if((bonjourServices.at(i).name == serviceName))
                                toAdd = false;
                        if(toAdd) {
                            QStringList paramsSplit2 = paramsSplit.at(0).trimmed().split(":");
                            if(paramsSplit2.count() > 1)
                                bonjourServices.append(BonjourService(serviceName, QHostAddress(paramsSplit2.at(0).trimmed()), paramsSplit2.at(1).toUInt()));
                        }
                    }
                }
            }
        }
    }

    //IPs
    QList<BonjourService> toAddServices;
    foreach(const QNetworkInterface &interf, QNetworkInterface::allInterfaces()) {
        foreach(const QNetworkAddressEntry &addressEntry, interf.addressEntries()) {
            if(addressEntry.ip().toIPv4Address() > 0)           toAddServices.append(BonjourService(tr("Network %1 (my IP)").arg(interf.humanReadableName()), addressEntry.ip(), 0));
            if(addressEntry.broadcast().toIPv4Address() > 0)    toAddServices.append(BonjourService(tr("Network %1 (broadcast)").arg(interf.humanReadableName()), addressEntry.broadcast(), 0));
        }
    }
    foreach(const BonjourService &toAddService, toAddServices) {
        bool toAdd = true;
        for(quint16 i = 0 ; i < bonjourServices.count() ; i++)
            if((bonjourServices.at(i).name == toAddService.name))
                toAdd = false;
        if(toAdd)
            bonjourServices.append(toAddService);
    }

#ifdef ZEROCONF_AS_BROWSER
    if(!bonjourBrowser) delete bonjourBrowser;
    if(!bonjourIsScanning) {
        //qDebug("> %d Scan Bonjour", QDateTime::currentDateTime().currentMSecsSinceEpoch());
        bonjourBrowser = new BonjourServiceBrowser(this);
        connect(bonjourBrowser, SIGNAL(currentBonjourRecordsChanged(const QList<BonjourRecord> &)), SLOT(currentBonjourRecordsChanged(const QList<BonjourRecord> &)));
        bonjourBrowser->browseForServiceType("_osc._udp");
        bonjourIsScanning = true;
    }
#endif

    qSort(bonjourServices.begin(), bonjourServices.end(), BonjourService::sort);
    QTimer::singleShot(5000, this, SLOT(bonjourScan()));
}
void InterfaceOsc::openBonjour() {
    bonjourMenu->clear();
    QAction *lastAction = 0;
    for(quint16 i = 0 ; i < bonjourServices.count() ; i++) {
        QString hostname = bonjourServices.at(i).host.toString();
        if(hostname == "::1")
            hostname = "127.0.0.1";

        if((!bonjourServices.at(i).host.isNull()) && (bonjourServices.at(i).port > 0))
            lastAction = bonjourServices[i].setAction(bonjourMenu->addAction(QString("%1 on %2:%3").arg(bonjourServices.at(i).name).arg(bonjourServices.at(i).host.toString()).arg(bonjourServices.at(i).port)));
        else if((!bonjourServices.at(i).host.isNull()) && (sender() != ui->bonjourPortIn))
            lastAction = bonjourServices[i].setAction(bonjourMenu->addAction(QString("%1 on %2").arg(bonjourServices.at(i).name).arg(bonjourServices.at(i).host.toString())));
        else if(bonjourServices.at(i).port > 0)
            lastAction = bonjourServices[i].setAction(bonjourMenu->addAction(QString("%1 on %2").arg(bonjourServices.at(i).name).arg(bonjourServices.at(i).port)));

        if((lastAction) && (bonjourServices.at(i).isBonjour) && (!((hostname.contains(".")) && (bonjourServices.at(i).port > 0))))
            lastAction->setEnabled(false);
    }
    if(sender() == ui->bonjour)         bonjourMenu->insertSeparator(bonjourMenu->addAction(tr("Reset to localhost on 57120")));
    if(sender() == ui->bonjourBundle)   bonjourMenu->insertSeparator(bonjourMenu->addAction(tr("Reset to localhost on 57130")));
    if(sender() == ui->bonjourPortIn)   bonjourMenu->insertSeparator(bonjourMenu->addAction(tr("Reset to 1234")));
    bonjourMenu->insertSeparator(bonjourMenu->addAction(tr("Refresh list")));
    QAction *retour = bonjourMenu->exec(QCursor::pos());
    if(retour) {
        if(retour->text().toLower().contains("refresh"))
            bonjourScan();
        else if(retour->text().toLower().contains("reset")) {
            if(sender() == ui->bonjour) {
                MessageManager::aliases["ip_out"]   = "127.0.0.1";
                MessageManager::aliases["port_out"] = "57120";
            }
            if(sender() == ui->bonjourBundle) {
                bundleHost = "127.0.0.1";
                bundlePort = 57130;
            }
            if(sender() == ui->bonjourPortIn)
                port = 1234;
        }
        else {
            foreach(const BonjourService &service, bonjourServices) {
                if(service.action == retour) {
                    QString hostname = service.host.toString();
                    if(hostname == "::1")
                        hostname = "127.0.0.1";
                    if(sender() == ui->bonjour) {
                        if(!service.host.isNull())
                            MessageManager::aliases["ip_out"] = hostname;
                        if(service.port > 0)
                            MessageManager::aliases["port_out"] = QString::number(service.port);
                    }
                    if(sender() == ui->bonjourBundle) {
                        if(!service.host.isNull())
                            bundleHost = hostname;
                        if(service.port > 0)
                            bundlePort = service.port;
                    }
                    if(sender() == ui->bonjourPortIn)
                        if(service.port > 0)
                            port = service.port;
                    return;
                }
            }
        }
    }
}


void InterfaceOsc::parseOSC() {
    //Parse all UDP datagram
    while(socket->hasPendingDatagrams()) {
        //Extract host, port & UDP datagram
        QHostAddress receivedHost;
        quint16 receivedPort;
        bufferISize = socket->readDatagram((char*)bufferI, 4096, &receivedHost, &receivedPort);


        if(enable) {
            quint16 indexBuffer = 0;
            //Parse UDP content
            while(indexBuffer < bufferISize) {
                indexAddressBuffer = 0;
                indexArgumentsBuffer = 0;

                //Looking for '/'
                while((indexBuffer < bufferISize) && (bufferI[indexBuffer] != '/'))
                    indexBuffer++;

                //Parse header
                if((bufferI[indexBuffer] =='/') && (bufferISize%4 == 0)) {
                    //OSC Adress
                    while((indexBuffer < bufferISize) && (bufferI[indexBuffer] != 0))
                        addressBuffer[indexAddressBuffer++] = bufferI[indexBuffer++];
                    addressBuffer[indexAddressBuffer] = 0;

                    //Looking for ','
                    while((indexBuffer < bufferISize) && (bufferI[indexBuffer++] != ',')) {}

                    //OSC arguments type
                    indexBuffer--;
                    while((indexBuffer < bufferISize) && (bufferI[++indexBuffer] != 0))
                        argumentsBuffer[indexArgumentsBuffer++] = bufferI[indexBuffer];
                    argumentsBuffer[indexArgumentsBuffer] = 0;
                    indexBuffer++;

                    //Index modulo 4
                    while((indexBuffer < bufferISize) && ((indexBuffer++)%4 != 0)) {}
                    indexBuffer--;


                    //Parse content
                    QString commandDestination = QString(addressBuffer).remove(oscMatchAdressIanniX).remove(oscMatchAdressTransport);
                    QString command = commandDestination + " ";
                    QStringList commandArguments;
                    quint16 indexDataBuffer = 0;
                    while((indexBuffer < bufferISize) && (indexDataBuffer < indexArgumentsBuffer)) {
                        //Integer argument
                        if(argumentsBuffer[indexDataBuffer] == 'i') {
                            union { int i; char ch[4]; } u;
                            u.ch[3] = bufferI[indexBuffer + 0];
                            u.ch[2] = bufferI[indexBuffer + 1];
                            u.ch[1] = bufferI[indexBuffer + 2];
                            u.ch[0] = bufferI[indexBuffer + 3];
                            indexBuffer += 4;
                            QString commandValue = QString::number(u.i);
                            command += commandValue + " ";
                            commandArguments << commandValue;
                        }
                        //Float argument
                        else if(argumentsBuffer[indexDataBuffer] == 'f') {
                            union { float f; char ch[4]; } u;
                            u.ch[3] = bufferI[indexBuffer + 0];
                            u.ch[2] = bufferI[indexBuffer + 1];
                            u.ch[1] = bufferI[indexBuffer + 2];
                            u.ch[0] = bufferI[indexBuffer + 3];
                            indexBuffer += 4;
                            QString commandValue = QString::number(u.f);
                            command += commandValue + " ";
                            commandArguments << commandValue;
                        }
                        //String argument
                        else if(argumentsBuffer[indexDataBuffer] == 's') {
                            QString commandValue = "";
                            while((indexBuffer < bufferISize) && (bufferI[indexBuffer]) != 0)
                                commandValue += bufferI[indexBuffer++];
                            indexBuffer++;
                            while(indexBuffer % 4 != 0)
                                indexBuffer++;
                            command += commandValue + " ";
                            commandArguments << commandValue;
                        }
                        else
                            indexBuffer += 4;
                        indexDataBuffer++;
                    }

                    MessageManager::incomingMessage(MessageIncomming("osc", receivedHost.toString(), receivedPort, commandDestination, command, commandArguments));

                    /*
                    Application::synchroLoopGuard = this;
                    if(command.toLower().startsWith("transport play"))
                        Application::current->execute(COMMAND_PLAY, ExecuteSourceNetwork);
                    else if(command.toLower().startsWith("transport stop"))
                        Application::current->execute(COMMAND_STOP, ExecuteSourceNetwork);
                    else if(command.toLower().startsWith("transport fastrewind")) {
                        Application::current->execute(COMMAND_FF, ExecuteSourceNetwork);
                    }
                    else if(command.toLower().startsWith("transport goto")) {
                        qreal time = command.remove("transport goto").trimmed().toDouble();
                        if(time == 0)   Application::current->execute(COMMAND_FF, ExecuteSourceNetwork);
                        else            Application::current->execute(QString("%1 %2").arg(COMMAND_GOTO).arg(time), ExecuteSourceNetwork);
                    }
                    Application::synchroLoopGuard = 0;
                    */
                }
            }
        }
    }
}

void InterfaceOsc::networkSynchro(bool start) {
    if(start)   networkSynchro(QString(COMMAND_PLAY));
    else {
        if(Transport::timeLocal == 0)
            networkSynchro(QString(COMMAND_FF));
        networkSynchro(QString(COMMAND_STOP));
    }
}
void InterfaceOsc::networkSynchro(const QString &info) {
    MessageManager::outgoingMessage(MessageManagerDestination(MessageManager::transportObject, 0, 0, 0, NxPoint(), NxPoint(), TransportStatus(MessageManager::transportNbTriggers, MessageManager::transportNbCursors, MessageManager::transportNbCurves, info)));
}



bool InterfaceOsc::send(const Message &message, QStringList *messageSent) {
    if(!enable)
        return false;

    if((message.getPort() == bundlePort) && (message.getHost() == QHostAddress(bundleHost))) {
        //Add message to bundle
        bundleMessages.append(message);
    }
    else {
        //Write a message on the opened socket
        socket->writeDatagram(message.getBuffer(), message.getHost(), message.getPort());

        //Log in console
        MessageManager::logSend(message, messageSent);
    }
    return true;
}
void InterfaceOsc::networkBundle(bool start) {
    if(start)
        bundleMessages.clear();
    else if((bundlePort) && (bundleMessages.count()) && (!QHostAddress(bundleHost).isNull())) {
        QByteArray messageBuffer;
        //Bundle
        messageBuffer += "#bundle";
        messageBuffer += (char)0;
        //Timecode
        union { int i; char ch[8]; } u;
        u.i = bundleMessageId++;
        messageBuffer += u.ch[7];
        messageBuffer += u.ch[6];
        messageBuffer += u.ch[5];
        messageBuffer += u.ch[4];
        messageBuffer += u.ch[3];
        messageBuffer += u.ch[2];
        messageBuffer += u.ch[1];
        messageBuffer += u.ch[0];

        foreach(const Message &bundleMessage, bundleMessages) {
            //Size of message
            union { int i; char ch[4]; } u;
            u.i = bundleMessage.getBuffer().count();
            messageBuffer += u.ch[3];
            messageBuffer += u.ch[2];
            messageBuffer += u.ch[1];
            messageBuffer += u.ch[0];
            //Message content
            messageBuffer += bundleMessage.getBuffer();
            //Log in console
            MessageManager::logSend(bundleMessage);
        }
        bundleMessages.clear();
        socket->writeDatagram(messageBuffer, QHostAddress(bundleHost), bundlePort);
    }
}


InterfaceOsc::~InterfaceOsc() {
    delete ui;
}
