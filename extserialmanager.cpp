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

#include "extserialmanager.h"

ExtSerialManager::ExtSerialManager(NxObjectFactoryInterface *_factory)
    : QObject(_factory), ExtMessageManager(_factory) {
    //Initialization
    factory = _factory;

    baudrateEnum["BAUD50"] = BAUD50;
    baudrateEnum["BAUD75"] = BAUD75;
    baudrateEnum["BAUD110"] = BAUD110;
    baudrateEnum["BAUD134"] = BAUD134;
    baudrateEnum["BAUD150"] = BAUD150;
    baudrateEnum["BAUD200"] = BAUD200;
    baudrateEnum["BAUD300"] = BAUD300;
    baudrateEnum["BAUD600"] = BAUD600;
    baudrateEnum["BAUD1200"] = BAUD1200;
    baudrateEnum["BAUD1800"] = BAUD1800;
    baudrateEnum["BAUD2400"] = BAUD2400;
    baudrateEnum["BAUD4800"] = BAUD4800;
    baudrateEnum["BAUD9600"] = BAUD9600;
    baudrateEnum["BAUD14400"] = BAUD14400;
    baudrateEnum["BAUD19200"] = BAUD19200;
    baudrateEnum["BAUD38400"] = BAUD38400;
    baudrateEnum["BAUD56000"] = BAUD56000;
    baudrateEnum["BAUD57600"] = BAUD57600;
    baudrateEnum["BAUD76800"] = BAUD76800;
    baudrateEnum["BAUD115200"] = BAUD115200;
    baudrateEnum["BAUD128000"] = BAUD128000;
    baudrateEnum["BAUD256000"] = BAUD256000;

    databitsEnum["DATA_5"] = DATA_5;
    databitsEnum["DATA_6"] = DATA_6;
    databitsEnum["DATA_7"] = DATA_7;
    databitsEnum["DATA_8"] = DATA_8;

    parityEnum["PAR_NONE"] = PAR_NONE;
    parityEnum["PAR_ODD"] = PAR_ODD;
    parityEnum["PAR_EVEN"] = PAR_EVEN;
    parityEnum["PAR_MARK"] = PAR_MARK;
    parityEnum["PAR_SPACE"] = PAR_SPACE;

    stopbitsEnum["STOP_1"] = STOP_1;
    stopbitsEnum["STOP_1_5"] = STOP_1_5;
    stopbitsEnum["STOP_2"] = STOP_2;

    flowEnum["FLOW_OFF"] = FLOW_OFF;
    flowEnum["FLOW_HARDWARE"] = FLOW_HARDWARE;
    flowEnum["FLOW_XONXOFF"] = FLOW_XONXOFF;
}

void ExtSerialManager::openPort(const QString & _port) {
    QStringList ports = _port.split(":", QString::SkipEmptyParts);
    if(ports.count() == 6) {
        portname = ports.at(0);
        baudrate = baudrateEnum[ports.at(1)];
        databits = databitsEnum[ports.at(2)];
        parity = parityEnum[ports.at(3)];
        stopbits = stopbitsEnum[ports.at(4)];
        flow = flowEnum[ports.at(5)];

        port = new QextSerialPort(portname, QextSerialPort::EventDriven);
        if(port) {
            port->setBaudRate(baudrate);
            port->setFlowControl(flow);
            port->setParity(parity);
            port->setDataBits(databits);
            port->setStopBits(stopbits);
            port->open(QIODevice::ReadWrite);

            connect(port, SIGNAL(readyRead()), this, SLOT(parse()));

            //qDebug("SerialPort %s %d", qPrintable(portname), port->isOpen());
            emit(openPortStatus(port->isOpen()));
        }
    }
}

void ExtSerialManager::parse() {
    QByteArray reception;
    int a = port->bytesAvailable();
    reception.resize(a);
    port->read(reception.data(), reception.size());

    bool nextMessage = true;
    while(nextMessage) {
        nextMessage = false;
        quint16 index = 0;
        QString command;
        while((index < reception.size()) && (!nextMessage)) {
            if(reception.at(index) == COMMAND_END_BYTE) {
                reception.remove(0, index+1);
                index = 0;

                command.remove(COMMAND_END);

                //Fire events (log, message and script mapping)
                QString url = "serial://" + portname + "/ ";
                factory->logOscReceive(url + command);
                factory->execute(command);
                factory->onOscReceive(url + command);
                qDebug(">%s<", qPrintable(command));
            }
            else
                command += reception.at(index);
            index++;
        }
    }
}

void ExtSerialManager::send(const ExtMessage & message) {
    //Write a message on the opened socket
    port->write(message.getAsciiMessage() + COMMAND_END_BYTE);

    //Log in the OSC console
    factory->logOscSend(message.getVerboseMessage());
}
