#ifndef OSCMANAGER_H
#define OSCMANAGER_H

#include "extmessage.h"

class ExtOscManager : public QObject, public ExtMessageManager {
    Q_OBJECT

public:
    ExtOscManager(NxObjectFactoryInterface *_factory);

private:
    QUdpSocket *socket;
    QString oscMatchAdress;

private:
    quint8 bufferI[4096], bufferO[4096];
    quint16 bufferISize, bufferOSize;
    char addressBuffer[255], argumentsBuffer[255];
    quint16 indexAddressBuffer, indexArgumentsBuffer;

public slots:
    void openPort(quint16);
signals:
    void openPortStatus(bool);

public:
    void send(const ExtMessage & message);
private slots:
    void parseOSC();
};


#endif
