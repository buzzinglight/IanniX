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

#ifndef OSCMANAGER_H
#define OSCMANAGER_H

#include <QByteArray>
#include "extmessage.h"

class ExtOscManager : public QObject, public ExtMessageManager {
    Q_OBJECT

public:
    ExtOscManager(NxObjectFactoryInterface *_factory);

private:
    QUdpSocket *socket;
    QString oscMatchAdress;
    QHostAddress bundleHost;
    quint16 bundlePort;
    QList<ExtMessage> bundleMessages;
    quint64 bundleMessageId;

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
    void setBundleMessageId(qint64 _bundleMessageId) { bundleMessageId = _bundleMessageId; }
    void openBundle(QHostAddress &_bundleHost, quint16 _bundlePort);
    void closeBundle();
private slots:
    void parseOSC();
};


#endif
