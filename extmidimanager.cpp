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
                    midi->receivedMessage(QString("midi://midiin/note %1 %2 0").arg(channel).arg(receivedMessage->at(1)));
                else
                    midi->receivedMessage(QString("midi://midiin/note %1 %2 %3").arg(channel).arg(receivedMessage->at(1)).arg(velocity));
            }
            break;
        case STATUS_CTLCHG:
            midi->receivedMessage(QString("midi://midiin/cc %1 %2 %3").arg(channel).arg(receivedMessage->at(1)).arg(receivedMessage->at(2)));
            break;
        case STATUS_PROGRAM:
            midi->receivedMessage(QString("midi://midiin/pgm %1 %2").arg(channel).arg(receivedMessage->at(1)));
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
    std::vector<unsigned char> message;
    if(command == "/note") {
        quint8 note = _message.getMidiValue(1);
        quint8 velocity = _message.getMidiValue(2);
        if(velocity > 0)
            message.push_back(STATUS_NOTEON + (channel & MASK_CHANNEL));
        else
            message.push_back(STATUS_NOTEOFF + (channel & MASK_CHANNEL));
        message.push_back(note & MASK_SAFETY);
        message.push_back(velocity & MASK_SAFETY);
    }
    else if(command == "/cc") {
        quint8 controller = _message.getMidiValue(1);
        quint8 value = _message.getMidiValue(2);
        // Controller: 0xB0 + channel, ctl, val
        message.push_back(STATUS_CTLCHG + (channel & MASK_CHANNEL));
        message.push_back(controller & MASK_SAFETY);
        message.push_back(value & MASK_SAFETY);
    }
    else if(command == "/pgm") {
        quint8 program = _message.getMidiValue(1);
        // Program: 0xC0 + channel, pgm
        message.push_back(STATUS_PROGRAM + (channel & MASK_CHANNEL));
        message.push_back(program & MASK_SAFETY);
    }
    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
            //Log in the OSC console
            factory->logOscSend(_message.getVerboseMessage());
        } catch (RtError& err) {
            factory->logOscSend(QString::fromStdString(err.getMessage()));
        }
    }
}

void ExtMidiManager::receivedMessage(const QString & url) {
    //Fire events (log, message and script mapping)
    factory->logOscReceive(url);
    factory->onOscReceive(url);
}

