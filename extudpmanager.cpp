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

#include "extudpmanager.h"

ExtUdpManager::ExtUdpManager(NxObjectFactoryInterface *_factory)
    : QObject(_factory), ExtMessageManager(_factory) {
    //Initialization
    factory = _factory;

    //Create a new UDP socket and bind signals
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(parseOSC()));
}

void ExtUdpManager::openPort(quint16 _port) {
    //Initialization
    socket->close();
    if(socket->bind(_port))
        emit(openPortStatus(true));
    else
        emit(openPortStatus(false));
}


void ExtUdpManager::parseOSC() {
    //Parse all UDP datagram
    while(socket->hasPendingDatagrams()) {
        //Extract host, port & UDP datagram
        QHostAddress receivedHost;
        quint16 receivedPort;
        bufferISize = socket->readDatagram((char*)bufferI, 4096, &receivedHost, &receivedPort);
        bufferI[bufferISize] = 0;

        QString commands = bufferI;
        commands.replace(";", COMMAND_END);
        QStringList commandItems = commands.split(COMMAND_END, QString::SkipEmptyParts);;
        foreach(const QString & command, commandItems) {
            //Fire events (log, message and script mapping)
            factory->logOscReceive(tr("udp://%1:%2/%3").arg(receivedHost.toString()).arg(receivedPort).arg(command));
            factory->execute(command);
            factory->onOscReceive("udp", receivedHost.toString(), QString::number(receivedPort), "", command.split(" ", QString::SkipEmptyParts));
        }
    }
}

void ExtUdpManager::send(const ExtMessage & message) {
    //Write a message on the opened socket
    socket->writeDatagram(message.getAsciiMessage() + ';' + '\n', message.getHost(), message.getPort());

    //Log in the OSC console
    factory->logOscSend(message.getVerboseMessage());
}
