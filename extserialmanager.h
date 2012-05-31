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

#ifndef EXTSERIALMANAGER_H
#define EXTSERIALMANAGER_H

#include "extmessage.h"
#include "qextserialport/qextserialport.h"

class ExtSerialManager : public QObject, public ExtMessageManager {
    Q_OBJECT

private:
    QextSerialPort *port;
    QString portname;
    BaudRateType baudrate;
    DataBitsType databits;
    ParityType parity;
    StopBitsType stopbits;
    FlowType flow;
    QMap<QString, BaudRateType> baudrateEnum;
    QMap<QString, DataBitsType> databitsEnum;
    QMap<QString, ParityType> parityEnum;
    QMap<QString, StopBitsType> stopbitsEnum;
    QMap<QString, FlowType> flowEnum;
    QByteArray reception;

public:
    ExtSerialManager(NxObjectFactoryInterface *_factory);

public:
    void send(const ExtMessage & message);

public slots:
    void openPort(const QString &);
signals:
    void openPortStatus(bool);

private slots:
    void parse();
};

#endif // EXTSERIALMANAGER_H
