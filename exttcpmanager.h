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

#ifndef EXTTCPMANAGER_H
#define EXTTCPMANAGER_H

#include "extmessage.h"
#include <QTcpServer>
#include <QDomDocument>

class ExtTcpManager : public QTcpServer, public ExtMessageManager {
    Q_OBJECT

public:
    ExtTcpManager(NxObjectFactoryInterface *_factory);
private:
    QList<QTcpSocket*> sockets;

public slots:
    void openPort(quint16 port);
signals:
    void openPortStatus(bool);
    void clientsStatus(quint16 nb);

public:
    void send(const ExtMessage & );

protected:
    void incomingConnection(int socketDescriptor);
private slots:
    void readClient();
    void discardClient();
};

#endif // EXTTCPMANAGER_H
