#ifndef EXTTCPMANAGER_H
#define EXTTCPMANAGER_H

#include "extmessage.h"

class ExtTcpManager : public QObject, public ExtMessageManager {
    Q_OBJECT

public:
    ExtTcpManager(NxObjectFactoryInterface *_factory);

public slots:
    void openPort(quint16) {}
signals:
    void openPortStatus(bool);

public:
    void send(const ExtMessage & ) {}
};

#endif // EXTTCPMANAGER_H
