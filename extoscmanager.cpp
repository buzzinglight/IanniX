#include "extoscmanager.h"


ExtOscManager::ExtOscManager(NxObjectFactoryInterface *_factory)
    : QObject(_factory), ExtMessageManager(_factory) {
    //OSC adress of IanniX
    oscMatchAdress = "/iannix/";

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
                QString command = QString(addressBuffer).remove(oscMatchAdress) + " ";
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
                        command += QString().setNum(u.i) + " ";
                    }
                    //Float argument
                    else if(argumentsBuffer[indexDataBuffer] == 'f') {
                        union { float f; char ch[4]; } u;
                        u.ch[3] = bufferI[indexBuffer + 0];
                        u.ch[2] = bufferI[indexBuffer + 1];
                        u.ch[1] = bufferI[indexBuffer + 2];
                        u.ch[0] = bufferI[indexBuffer + 3];
                        indexBuffer += 4;
                        command += QString().setNum(u.f) + " ";
                    }
                    //String argument
                    else if(argumentsBuffer[indexDataBuffer] == 's') {
                        while((indexBuffer < bufferISize) && (bufferI[indexBuffer]) != 0)
                            command += bufferI[indexBuffer++];
                        indexBuffer++;
                        while(indexBuffer % 4 != 0)
                            indexBuffer++;
                        command += " ";
                    }
                    else
                        indexBuffer += 4;
                    indexDataBuffer++;
                }

                //Fire events (log, message and script mapping)
                QString url = "osc://" + receivedHost.toString() + ":" + QString().setNum(receivedPort) + QString(addressBuffer) + " ";
                factory->logOscReceive(url + command);
                factory->execute(command);
                factory->onOscReceive(url + command);
            }
        }
    }
}


void ExtOscManager::send(const ExtMessage & message) {
    //Write a message on the opened socket
    socket->writeDatagram(message.getBuffer(), message.getHost(), message.getPort());

    //Log in the OSC console
    factory->logOscSend(message.getVerboseMessage());
}
