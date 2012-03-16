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

#include "exttcpmanager.h"

ExtTcpManager::ExtTcpManager(NxObjectFactoryInterface *_factory)
    : QTcpServer(_factory), ExtMessageManager(_factory) {
    //Initialization
    factory = _factory;

    //Initialization
    factory = _factory;
}

void ExtTcpManager::openPort(quint16 port) {
    //Initialization
    close();
    if(listen(QHostAddress::Any, port))
        emit(openPortStatus(true));
    else
        emit(openPortStatus(false));
    emit(clientsStatus(sockets.count()));
}


void ExtTcpManager::send(const ExtMessage & message) {
    //Send request
    foreach(QTcpSocket *socket, sockets) {
        QByteArray xml;
        xml += "<OSCPACKET ADDRESS=\"" + socket->localAddress().toString() + "\" PORT=\"" + QByteArray::number(socket->localPort()) + "\" TIME=\"" + QByteArray::number(factory->getTimeLocal()) + "\"><MESSAGE NAME=\"/" + message.getAddress() + "\">" + message.getAsciiMessage() + "</MESSAGE></OSCPACKET>";
        xml += (char)0;
        socket->write(xml);
        socket->flush();

        //Log in the OSC console
        factory->logOscSend("tcp://" + socket->peerAddress().toString() + ":" + QString::number(socket->peerPort()) + "/ " + QString(xml));
    }
}

//TCP reception
void ExtTcpManager::incomingConnection(int socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),    this, SLOT(readClient()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discardClient()));
    socket->setSocketDescriptor(socketDescriptor);
    sockets.append(socket);
    factory->logOscReceive(tr("New TCP client connected") + QString(": %1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
    emit(clientsStatus(sockets.count()));
}
void ExtTcpManager::readClient() {
    QTcpSocket *socket = (QTcpSocket*)sender();
    if(socket->isReadable()) {
        QDomDocument xmlDoc;
        xmlDoc.setContent(socket->readAll());

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
                        factory->execute(command);
                        factory->logOscReceive(QString("tcp://%1:%2%3 %4").arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(destination).arg(command));
                        factory->onOscReceive("tcp", socket->peerAddress().toString(), QString::number(socket->peerPort()), destination, command.split(" ", QString::SkipEmptyParts));
                    }
                    xmlOscArgument = xmlOscArgument.nextSibling();
                }
            }
            xmlOscMessage = xmlOscMessage.nextSibling();
        }
    }
}
void ExtTcpManager::discardClient() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    sockets.removeOne(socket);
    emit(clientsStatus(sockets.count()));
    socket->deleteLater();
}
