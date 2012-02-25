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

#include "extmidimanager.h"


void midiCallback(double, std::vector< unsigned char > *receivedMessage, void *userData) {
    ExtMidiManager *midi = (ExtMidiManager*)userData;
    quint8 receivedMessageBytes = receivedMessage->size();
    if(receivedMessageBytes > 0) {
        quint8 status = receivedMessage->at(0) & MASK_STATUS;
        quint8 channel = receivedMessage->at(0) & MASK_CHANNEL;

        switch(status) {
        case STATUS_NOTEOFF:
        case STATUS_NOTEON: {
            quint8 velocity = receivedMessage->at(2);
            if ((status == STATUS_NOTEOFF) || (velocity == 0))
                midi->receivedMessage("note", QStringList() << QString::number(channel) << QString::number(receivedMessage->at(1)) << "0");
            else
                midi->receivedMessage("note", QStringList() << QString::number(channel) << QString::number(receivedMessage->at(1)) << QString::number(velocity));
        }
            break;
        case STATUS_CTLCHG:
            midi->receivedMessage("cc", QStringList() << QString::number(channel) << QString::number(receivedMessage->at(1)) << QString::number(receivedMessage->at(2)));
            break;
        case STATUS_PROGRAM:
            midi->receivedMessage("pgm", QStringList() << QString::number(channel) << QString::number(receivedMessage->at(1)));
            break;
        }
    }
}

ExtMidiManager::ExtMidiManager(NxObjectFactoryInterface *_factory)
    : QObject(_factory), ExtMessageManager(_factory) {
    //Initialization
    factory = _factory;

    QString portOutName = "IanniX_Out";
    QString portInName = "IanniX_In";

    RtMidiIn *portListIn = new RtMidiIn();
    quint8 portListInCount = portListIn->getPortCount();
    for(quint8 portListInIndex = 0; portListInIndex < portListInCount ; portListInIndex++) {
        try {
            QString portName = QString::fromStdString(portListIn->getPortName(portListInIndex));
            portName = portName.replace(" ", "");
            portName = portName.replace("/", "");
            factory->logOscSend("MIDI In Found : " + portName);
            qDebug("%s", qPrintable("MIDI In Found : " + portName));
            portName = portName.toLower();
            portIn.insert(portName, new RtMidiIn());
            portIn.value(portName)->openPort(portListInIndex);
            portIn.value(portName)->setCallback(&midiCallback, this);
            portIn.value(portName)->ignoreTypes(true, true, true);
        }
        catch(RtError &err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
    delete portListIn;

    RtMidiOut *portListOut = new RtMidiOut();
    quint8 portListOutCount = portListOut->getPortCount();
    for(quint8 portListOutIndex = 0; portListOutIndex < portListOutCount ; portListOutIndex++) {
        try {
            QString portName = QString::fromStdString(portListOut->getPortName(portListOutIndex));
            portName = portName.replace(" ", "");
            portName = portName.replace("/", "");
            factory->logOscSend("MIDI Out Found : " + portName);
            qDebug("%s", qPrintable("MIDI Out Found : " + portName));
            portName = portName.toLower();
            portOut.insert(portName, new RtMidiOut());
            portOut.value(portName)->openPort(portListOutIndex);
        }
        catch(RtError &err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
    delete portListOut;

    try {
        portOutName = portOutName.toLower();
        portInName = portInName.toLower();
        portOut.insert(portOutName, new RtMidiOut(portOutName.toStdString()));
        portIn.insert(portInName, new RtMidiIn(portInName.toStdString()));
#if !defined(__LINUX_ALSASEQ__) && !defined(__MACOSX_CORE__)
        if (portOut.value(portOutName)->getPortCount() == 0)
            portOut.remove(portOutName);
        if (portIn.value(portInName)->getPortCount() == 0)
            portIn.remove(portInName);
#endif
#if defined(__LINUX_ALSASEQ__) || defined(__MACOSX_CORE__)
        if(portOut.value(portOutName) != 0)
            portOut.value(portOutName)->openVirtualPort(portOutName.toStdString());
        if(portIn.value(portInName) != 0)
            portIn.value(portInName)->openVirtualPort(portInName.toStdString());
#endif
    } catch (RtError& err) {
        factory->logOscSend(QString::fromStdString(err.getMessage()));
    }
    if(portIn.value(portInName)) {
        portIn.value(portInName)->setCallback(&midiCallback, this);
        portIn.value(portInName)->ignoreTypes(true, true, true);
    }
}

void ExtMidiManager::send(const ExtMessage & _message) {
    quint8 channel = _message.getMidiValue(0);
    QString portname = _message.getMidiPort().toLower();
    QString command = _message.getMidiCommand().toLower();

    //Send request
    if(command == "/note") {
        sendNote(portname, channel, _message.getMidiValue(1), _message.getMidiValue(2));
        quint16 duration = _message.getMidiValue(3);
        if(duration > 0)
            new ExtMidiNoteOff(this, portname, channel, _message.getMidiValue(1), duration);
    }
    else if(command == "/cc")
        sendCC(portname, channel, _message.getMidiValue(1), _message.getMidiValue(2));
    else if(command == "/pgm")
        sendPGM(portname, channel, _message.getMidiValue(1));
    else if(command == "/bend")
        sendBend(portname, channel, _message.getMidiValue(1));
}

void ExtMidiManager::sendNote(const QString & portname, quint8 channel, quint16 note, quint16 velocity) {
    std::vector<unsigned char> message;

    note = (note > 0x7f) ? 0x7f : note;
    velocity = (velocity > 0x7f) ? 0x7f : velocity;

    if(velocity > 0)
        message.push_back(STATUS_NOTEON + (channel & MASK_CHANNEL));
    else
        message.push_back(STATUS_NOTEOFF + (channel & MASK_CHANNEL));

    message.push_back(note & MASK_SAFETY);
    message.push_back(velocity & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
            //Log in the OSC console
            factory->logOscSend(tr("MIDI %1 on ch. %2, send note(%3)=%4").arg(portname).arg(channel).arg(note).arg(velocity));
        } catch (RtError& err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
}
void ExtMidiManager::sendCC(const QString & portname, quint8 channel, quint16 controller, quint16 value) {
    std::vector<unsigned char> message;
    controller = (controller > 0x7f) ? 0x7f : controller;
    value = (value > 0x7f) ? 0x7f : value;

    // Controller: 0xB0 + channel, ctl, val
    message.push_back(STATUS_CTLCHG + (channel & MASK_CHANNEL));
    message.push_back(controller & MASK_SAFETY);
    message.push_back(value & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
            //Log in the OSC console
            factory->logOscSend(tr("MIDI %1 on ch. %2, send CC(%3)=%4").arg(portname).arg(channel).arg(controller).arg(value));
        } catch (RtError& err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
}
void ExtMidiManager::sendPGM(const QString & portname, quint8 channel, quint16 program) {
    std::vector<unsigned char> message;
    program = (program > 0x7f) ? 0x7f : program;

    // Program: 0xC0 + channel, pgm
    message.push_back(STATUS_PROGRAM + (channel & MASK_CHANNEL));
    message.push_back(program & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
            //Log in the OSC console
            factory->logOscSend(tr("MIDI %1 on ch. %2, send PGM=%3").arg(portname).arg(channel).arg(program));
        } catch (RtError& err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
}
void ExtMidiManager::sendBend(const QString & portname, quint8 channel, quint16 bendvalue) {
    std::vector<unsigned char> message;
    bendvalue = (bendvalue > 0x3fff) ? 0x3fff : bendvalue;

    // Bend: 0xE0 + channel, 7LeastSigBits, 7MostSigBits
    quint8 lsb = 0x7f & bendvalue;
    quint8 msb = 0x7f & (bendvalue  >> 7);

    message.push_back(STATUS_BEND + (channel & MASK_CHANNEL));
    message.push_back(lsb & MASK_SAFETY);
    message.push_back(msb & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
            //Log in the OSC console
            factory->logOscSend(tr("MIDI %1 on ch. %2, send bend=%3").arg(portname).arg(channel).arg(bendvalue));
        } catch (RtError& err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
}


void ExtMidiManager::receivedMessage(const QString & destination, const QStringList & arguments) {
    //Fire events (log, message and script mapping)
    QString verbose = "midi://midiin/" + destination;
    foreach(const QString &argument, arguments)
        verbose += " " + argument;
    factory->logOscReceive(verbose);
    factory->onOscReceive("midi", "midiin", "", destination, arguments);
}

