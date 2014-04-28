/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INTERFACETCP_H
#define INTERFACETCP_H

#include <QTcpServer>
#include <QDomDocument>
#include "misc/options.h"
#include "messages/messagemanager.h"

namespace Ui {
class InterfaceTcp;
}

class InterfaceTcpServer : public QTcpServer {
    Q_OBJECT

public:
    InterfaceTcpServer(QObject *parent);

public:
    bool xmlMode;
    QList<QTcpSocket*> sockets;
    bool send(const Message &message, QStringList *messageSent = 0);
public:
    bool portChanged(quint16 port);
protected:
    void incomingConnection(int socketDescriptor);
private slots:
    void readClient();
    void discardClient();
signals:
    void updateConnectedClients();
    void parseXml(const QDomDocument&, QTcpSocket*);
};

class InterfaceTcp : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceTcp(QWidget *parent = 0);
    ~InterfaceTcp();

private:
    InterfaceTcpServer *tcpServer;
    UiReal port;
    UiBool enable;
    UiReal type;
private slots:
    void portChanged();
    void typeChanged();
    void updateConnectedClients();
    void parseXml(const QDomDocument&, QTcpSocket*);
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/Adobe Flash/").absoluteFilePath()));
    }

public:
    bool send(const Message &message, QStringList *messageSent = 0);

private:
    Ui::InterfaceTcp *ui;
};

#endif // INTERFACETCP_H
