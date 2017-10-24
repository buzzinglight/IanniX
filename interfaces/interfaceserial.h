/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (https://www.buzzinglight.com)

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

#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H

#include <QWidget>
#include "misc/options.h"
#include "messages/messagemanager.h"
#include "qextserialport/qextserialport.h"
#include "qextserialport/qextserialenumerator.h"

namespace Ui {
class InterfaceSerial;
}

class InterfaceSerial : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceSerial(QWidget *parent = 0);
    ~InterfaceSerial();

private:
    UiString portName;
    UiReal portBaud, portBits, portParity, portStop, portFlow;
    UiBool enable;
private slots:
    void portChanged();
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(Application::pathPatches.absoluteFilePath() + "/Arduino/").absoluteFilePath()));
    }

private:
    void timerEvent(QTimerEvent *);

private:
    QextSerialPort *port;
    QList<BaudRateType> baudrateEnum;
    QList<DataBitsType> databitsEnum;
    QList<ParityType>   parityEnum;
    QList<StopBitsType> stopbitsEnum;
    QList<FlowType>     flowEnum;
    QByteArray reception;
private slots:
    void parse();

public:
    bool send(const Message &message, QStringList *messageSent = 0);

private:
    Ui::InterfaceSerial *ui;
};

#endif // INTERFACESERIAL_H
