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

#include "extoscmanager.h"


ExtOscManager::ExtOscManager(NxObjectFactoryInterface *_factory)
    : QObject(_factory), ExtMessageManager(_factory) {
    //OSC adress of IanniX
    oscMatchAdress = "/iannix/";
    bundleMessageId = 0;

    //Create a new UDP socket and bind signals
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(parseOSC()));
}

void ExtOscManager::openPort(quint16 _port) {
    //Initialization
    socket->close();
    if(socket->bind(_port))
        emit(openPortStatus(true));
    else
        emit(openPortStatus(false));
}


void ExtOscManager::parseOSC() {
    //Parse all UDP datagram
    while(socket->hasPendingDatagrams()) {
        //Extract host, port & UDP datagram
        QHostAddress receivedHost;
        quint16 receivedPort;
        bufferISize = socket->readDatagram((char*)bufferI, 4096, &receivedHost, &receivedPort);

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
                QString commandDestination = QString(addressBuffer).remove(oscMatchAdress);
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
                        QString commandValue = QString().setNum(u.i);
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
                        QString commandValue = QString().setNum(u.f);
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

                //Fire events (log, message and script mapping)
                factory->logOscReceive(tr("osc://%1:%2%3%4").arg(receivedHost.toString()).arg(receivedPort).arg(oscMatchAdress).arg(command));
                factory->execute(command);
                factory->onOscReceive("osc", receivedHost.toString(), QString::number(receivedPort), commandDestination, commandArguments);
            }
        }
    }
}


void ExtOscManager::send(const ExtMessage & message) {
    if((message.getPort() == bundlePort) && (message.getHost() == bundleHost))
        //Add message to bundle
        bundleMessages.append(message);
    else {
        //Write a message on the opened socket
        socket->writeDatagram(message.getBuffer(), message.getHost(), message.getPort());

        //Log in the OSC console
        factory->logOscSend(message.getVerboseMessage());
    }
}
void ExtOscManager::openBundle(QHostAddress &_bundleHost, quint16 _bundlePort) {
    bundleHost = _bundleHost;
    bundlePort = _bundlePort;
    bundleMessages.clear();
}
void ExtOscManager::closeBundle() {
    if((bundlePort) && (!bundleHost.isNull()) && (bundleMessages.count() > 0)) {
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

        factory->logOscSend("--- bundle start ---");
        foreach(const ExtMessage &bundleMessage, bundleMessages) {
            //Size of message
            union { int i; char ch[4]; } u;
            u.i = bundleMessage.getBuffer().count();
            messageBuffer += u.ch[3];
            messageBuffer += u.ch[2];
            messageBuffer += u.ch[1];
            messageBuffer += u.ch[0];
            //Message content
            messageBuffer += bundleMessage.getBuffer();
            //Log in the OSC console
            factory->logOscSend(bundleMessage.getVerboseMessage());
        }
        bundleMessages.clear();
        factory->logOscSend("--- bundle end ---");
        socket->writeDatagram(messageBuffer, QHostAddress("127.0.0.1"), 57120);
    }
}
