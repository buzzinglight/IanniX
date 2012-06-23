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
        case MASK_STATUS: {
            quint8 msg1 = receivedMessage->at(0);
            if(msg1 == MIDI_SPP) {
                quint8 msg2 = receivedMessage->at(1);
                quint8 msg3 = receivedMessage->at(2);
                midi->receivedMidiRealtime(msg1, msg2, msg3);
            }
            else if (msg1 == MIDI_CLOCK)
                midi->receivedMidiRealtime(msg1, 0 ,0);
            else if (msg1 == MIDI_TIMECODE){
                quint8 msg2 = receivedMessage->at(1);
                midi->receivedMidiRealtime(msg1, msg2 ,0);
            }
            else
                midi->receivedMidiRealtime(msg1, 0, 0);
            break;
        }
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

    midiTempo = 120;

    QString portOutName = "IanniX_Out";
    QString portInName = "IanniX_In";

    refreshList();

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
        factory->setMidiOutNewDevice("IanniX_Out");
#endif
    } catch (RtError& err) {
        factory->logOscSend(QString::fromStdString(err.getMessage()));
    }
    if(portIn.value(portInName)) {
        portIn.value(portInName)->setCallback(&midiCallback, this);
        portIn.value(portInName)->ignoreTypes(true, false, true);
    }
}

void ExtMidiManager::refreshList() {

    RtMidiIn *portListIn = new RtMidiIn();
    quint8 portListInCount = portListIn->getPortCount();
    for(quint8 portListInIndex = 0; portListInIndex < portListInCount ; portListInIndex++) {
        try {
            QString portName = QString::fromStdString(portListIn->getPortName(portListInIndex));
            portName = portName.replace(" ", "");
            portName = portName.replace("/", "");
            portName = portName.toLower();
            if(!portIn.contains(portName)) {
                portIn.insert(portName, new RtMidiIn());
                portIn.value(portName)->openPort(portListInIndex);
                portIn.value(portName)->setCallback(&midiCallback, this);
                portIn.value(portName)->ignoreTypes(true, true, true);
            }
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
            portName = portName.toLower();
            if(!portOut.contains(portName)) {
                factory->setMidiOutNewDevice(portName);
                portOut.insert(portName, new RtMidiOut());
                portOut.value(portName)->openPort(portListOutIndex);
            }
        }
        catch(RtError &err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
    delete portListOut;
}

void ExtMidiManager::send(const ExtMessage & _message) {
    quint8 channel = _message.getMidiValue(0);
    QString portname = _message.getMidiPort().toLower();
    QString command = _message.getMidiCommand().toLower();

    //Send request
    if(command == "/note") {
        sendNote(portname, channel, _message.getMidiValue(1), _message.getMidiValue(2));
        qreal duration = _message.getMidiValue(3) * 1000.;
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
void ExtMidiManager::sendSPPStart() {
    std::vector<unsigned char> message;
    message.push_back(MIDI_CONTINUE);
    if(message.size() > 0) {
        foreach(RtMidiOut *port, portOut) {
            try {
                port->sendMessage(&message);
            } catch (RtError& err) {
            }
        }
    }
}
void ExtMidiManager::sendSPPStop() {
    std::vector<unsigned char> message;
    message.push_back(MIDI_STOP);
    if(message.size() > 0) {
        foreach(RtMidiOut *port, portOut) {
            try {
                port->sendMessage(&message);
            } catch (RtError& err) {
            }
        }
    }
}
void ExtMidiManager::sendSPPTime(qreal time) {
    quint16 slaveTime = (time / ((60. / midiTempo) / 16.)) / 4.;
    qint8 val2 = slaveTime / 128, val1 = slaveTime % 128;

    std::vector<unsigned char> message;
    message.push_back(MIDI_SPP);
    message.push_back(val1);
    message.push_back(val2);
    if(message.size() > 0) {
        foreach(RtMidiOut *port, portOut) {
            try {
                port->sendMessage(&message);
            } catch (RtError& err) {
            }
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
void ExtMidiManager::receivedMidiRealtime(quint8 type, quint8 val1, quint8 val2) {
    if(type == MIDI_SPP)
        factory->syncGoto((128*val2 + val1) * 4 * ((60. / midiTempo) / 16));
    else if(type == MIDI_CLOCK)
        factory->syncTimer((60. / midiTempo) / 24.);
    else if(type == MIDI_TIMECODE){
        qreal slaveTime = midiMtc.decode(val1);
        qDebug("TIMECODE %f", slaveTime);
    }
    else if(type == MIDI_TICK)
        qDebug("TICK");
    else if(type == MIDI_CONTINUE)
        factory->syncStart();
    else if(type == MIDI_STOP)
        factory->syncStop();
    else if(type == MIDI_START)
        factory->syncStart();
    else
        qDebug("MIDI Sync Error");
}

void ExtMidiManager::setMidiTempo(qreal _midiTempo) {
    midiTempo = _midiTempo;
}





qreal ExtMidiMTC::decode(quint16 msg) {
    int times[4]   = {0, 0, 0, 0};
    QString szType = "";
    int numFrames  = 100;
    qreal smpteTime = 0;

    int messageIndex        = msg >> 4;
    int value               = msg & 0x0F;
    int timeIndex           = messageIndex>>1;
    bool bNewFrame          = messageIndex % 4 == 0;

    if(bNewFrame) {
        times[kMTCFrames]++;
        if(times[kMTCFrames] >= numFrames) {
            times[kMTCFrames] %= numFrames;
            times[kMTCSeconds]++;
            if(times[kMTCSeconds] >= 60) {
                times[kMTCSeconds] %= 60;
                times[kMTCMinutes]++;
                if(times[kMTCMinutes] >= 60) {
                    times[kMTCMinutes] %= 60;
                    times[kMTCHours]++;
                }
            }
        }
        Q_ASSERT_X(numFrames > 0, "MTCDecoder", "Error in received MIDI Time Code");
        smpteTime = (qreal)(3600*times[kMTCHours] + 60*times[kMTCMinutes] + times[kMTCSeconds] + times[kMTCFrames]) / (qreal)numFrames;
    }


    if(messageIndex % 2 == 0)   times[timeIndex]  = value;
    else                        times[timeIndex] |= value<<4;

    if(messageIndex == 7) {
        times[kMTCHours] &= 0x1F;
        int smpteType = value >> 1;
        switch(smpteType) {
        case 0: numFrames = 24; szType = "24 fps"; break;
        case 1: numFrames = 25; szType = "25 fps"; break;
        case 2: numFrames = 30; szType = "30 fps (drop-frame)"; break;
        case 3: numFrames = 30; szType = "30 fps"; break;
        default: numFrames = 100; szType = " **** unknown SMPTE type ****";
        }
    }
    return smpteTime;
}

