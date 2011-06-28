#ifndef EXTUDPMANAGER_H
#define EXTUDPMANAGER_H

#include "extmessage.h"

class ExtUdpManager : public QObject, public ExtMessageManager {
    Q_OBJECT

private:
    QUdpSocket *socket;
    char bufferI[4096];
    quint16 bufferISize;

public:
    ExtUdpManager(NxObjectFactoryInterface *_factory);

public slots:
    void openPort(quint16);
signals:
    void openPortStatus(bool);

private slots:
    void parseOSC();

public:
    void send(const ExtMessage & message);
};

#endif // EXTUDPMANAGER_H
