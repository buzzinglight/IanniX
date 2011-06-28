#include "exttcpmanager.h"

ExtTcpManager::ExtTcpManager(NxObjectFactoryInterface *_factory)
    : QObject(_factory), ExtMessageManager(_factory) {
    //Initialization
    factory = _factory;

    //Create a new UDP socket and bind signals
    /*
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, port, QUdpSocket::ShareAddress);
    connect(socket, SIGNAL(readyRead()), SLOT(parseOSC()));
    */
}
