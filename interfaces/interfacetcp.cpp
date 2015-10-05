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

#include "interfacetcp.h"
#include "ui_interfacetcp.h"

InterfaceTcp::InterfaceTcp(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceTcp) {
    ui->setupUi(this);
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));

    tcpServer = new InterfaceTcpServer(this);
    connect(tcpServer, SIGNAL(updateConnectedClients()),           SLOT(updateConnectedClients()));
    connect(tcpServer, SIGNAL(parseXml(QDomDocument,QTcpSocket*)), SLOT(parseXml(QDomDocument,QTcpSocket*)));

    //Interfaces link
    enable.setAction(ui->enable, "interfaceTcpEnable");
    port.setAction(ui->port,     "interfaceTcpPort");
    connect(&port, SIGNAL(triggered(qreal)), SLOT(portChanged()));
    type.setAction(QList<QRadioButton*>() << ui->typeRaw << ui->typeXml, "interfaceTcpXml");
    connect(&type, SIGNAL(triggered(qreal)), SLOT(typeChanged()));
    port = 3000;
}

InterfaceTcpServer::InterfaceTcpServer(QObject *parent) :
    QTcpServer(parent) {
    xmlMode = false;
}

void InterfaceTcp::portChanged() {
    if(tcpServer->portChanged(port.val()))  ui->port->setStyleSheet(ihmFeedbackOk);
    else                                    ui->port->setStyleSheet(ihmFeedbackNok);
}
void InterfaceTcp::typeChanged() {
    tcpServer->xmlMode = (type.val() > 0);
}
bool InterfaceTcpServer::portChanged(quint16 port) {
    //Initialization
    close();
    return listen(QHostAddress::Any, port);
}


bool InterfaceTcp::send(const Message &message, QStringList *messageSent) {
    if(!enable)
        return false;
    return tcpServer->send(message, messageSent);
}
bool InterfaceTcpServer::send(const Message &message, QStringList *messageSent) {
    bool ok = false;
    QByteArray bytes;
    if(xmlMode) {
        //bytes += "<OSCPACKET ADDRESS=\"" + socket->localAddress().toString() + "\" PORT=\"" + QByteArray::number(socket->localPort()) + "\" TIME=\"" + QByteArray::number(Transport::timeLocal) + "\"><MESSAGE NAME=\"/" + message.getAddress() + "\">" + message.getAsciiMessageXml() + "</MESSAGE></OSCPACKET>";
        bytes += "<OSCPACKET TIME=\"" + QByteArray::number(Transport::timeLocal) + "\"><MESSAGE NAME=\"/" + message.getAddress() + "\">" + message.getAsciiMessageXml() + "</MESSAGE></OSCPACKET>";
        bytes += (char)0;
    }
    else {
        foreach(const QVariant &valeur, message.verboseValues) {
            bool isFloat = false;
            union { float f; char ch[4]; } u;
            u.f = valeur.toFloat(&isFloat);
            if(!isFloat)
                bytes.append(valeur.toString());
            else {
                bytes.append(u.ch[0]);
                bytes.append(u.ch[1]);
                bytes.append(u.ch[2]);
                bytes.append(u.ch[3]);
            }
        }
    }

    //Send request
    foreach(QTcpSocket *socket, sockets) {
        socket->write(bytes);
        socket->flush();

        //Log in console
        MessageManager::logSend(message, messageSent);
        ok = true;
    }
    return ok;
}


//TCP reception
#ifdef QT4
void InterfaceTcpServer::incomingConnection(int handle) {
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),    this, SLOT(readClient()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discardClient()));
    socket->setSocketDescriptor(handle);
    sockets.append(socket);
    emit(updateConnectedClients());
}
#else
void InterfaceTcpServer::incomingConnection(qintptr handle) {
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),    this, SLOT(readClient()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discardClient()));
    socket->setSocketDescriptor(handle);
    sockets.append(socket);
    emit(updateConnectedClients());
}
#endif
void InterfaceTcpServer::readClient() {
    QTcpSocket *socket = (QTcpSocket*)sender();
    if(socket->isReadable()) {
        if(xmlMode) {
            //XML parsing
            QDomDocument xmlDoc;
            xmlDoc.setContent(socket->readAll());
            emit(parseXml(xmlDoc, socket));
        }
        else {
            //RAW data
            QByteArray dataReceived = socket->readAll();
            QStringList arguments;
            for(quint16 indexBuffer = 0 ; indexBuffer < dataReceived.count() ; indexBuffer += 4) {
                union { float f; char ch[4]; } u;
                u.ch[0] = dataReceived[indexBuffer + 0];
                u.ch[1] = dataReceived[indexBuffer + 1];
                u.ch[2] = dataReceived[indexBuffer + 2];
                u.ch[3] = dataReceived[indexBuffer + 3];
                qreal val = u.f;
                arguments << QString::number(val);
            }
            MessageManager::incomingMessage(MessageIncomming("tcp", socket->peerAddress().toString(), socket->peerPort(), "tcp_raw", "", arguments));
        }
    }
}

void InterfaceTcp::parseXml(const QDomDocument &xmlDoc, QTcpSocket *socket) {
    if(!enable)
        return;

    //Racine
    QDomElement xmlPacket = xmlDoc.documentElement();

    //Parse les menaces
    QDomNode xmlOscMessage = xmlPacket.firstChild();
    while(!xmlOscMessage.isNull()) {
        QDomElement xmlMessage = xmlOscMessage.toElement();
        if((!xmlMessage.isNull()) && (xmlMessage.tagName().toUpper() == "MESSAGE")) {
            QString destination = xmlMessage.attribute("NAME");
            QDomNode xmlOscArgument = xmlMessage.firstChild();
            while(!xmlOscArgument.isNull()) {
                QDomElement xmlArgument = xmlOscArgument.toElement();
                if((!xmlArgument.isNull()) && (xmlArgument.tagName().toUpper() == "ARGUMENT")) {
                    QString command = xmlArgument.attribute("VALUE").replace("%20", " ");
                    MessageManager::incomingMessage(MessageIncomming("tcp", socket->peerAddress().toString(), socket->peerPort(), destination, command, command.split(" ", QString::SkipEmptyParts)));
                }
                xmlOscArgument = xmlOscArgument.nextSibling();
            }
        }
        xmlOscMessage = xmlOscMessage.nextSibling();
    }
}
void InterfaceTcpServer::discardClient() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    sockets.removeOne(socket);
    emit(updateConnectedClients());
    socket->deleteLater();
}


void InterfaceTcp::updateConnectedClients() {
    QString clients;
    foreach(QTcpSocket *socket, tcpServer->sockets)
        clients += QString("%1:%2\n").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    clients.chop(1);
    if(tcpServer->sockets.count() == 0)        ui->clients->setText(tr("No client connected"));
    else if(tcpServer->sockets.count() == 1)   ui->clients->setText(tr("1 client connected\n(%1)").arg(clients));
    else                                       ui->clients->setText(tr("%1 clients connected").arg(tcpServer->sockets.count()));
    ui->clients->setToolTip(clients);
}


InterfaceTcp::~InterfaceTcp() {
    delete ui;
}
