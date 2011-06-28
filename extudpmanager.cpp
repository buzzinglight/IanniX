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
        qDebug("||%s||", qPrintable(commands));
        QStringList commandItems = commands.split(COMMAND_END, QString::SkipEmptyParts);;
        foreach(const QString & command, commandItems) {
            //Fire events (log, message and script mapping)
            QString url = "udp://" + receivedHost.toString() + ":" + QString().setNum(receivedPort) + "/ ";
            factory->logOscReceive(url + command);
            factory->execute(command);
            factory->onOscReceive(url + command);
        }
    }
}

void ExtUdpManager::send(const ExtMessage & message) {
    //Write a message on the opened socket
    socket->writeDatagram(message.getAsciiMessage() + ';' + '\n', message.getHost(), message.getPort());

    //Log in the OSC console
    factory->logOscSend(message.getVerboseMessage());
}
