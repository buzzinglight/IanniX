#include "interfacemidi.h"
#include "ui_interfacemidi.h"

UiBool  InterfaceMidi::syncTransportIn  = true;
UiBool  InterfaceMidi::syncTransportOut = true;
QString InterfaceMidi::portInName    = "from_iannix";
QString InterfaceMidi::portOutName   = "to_iannix";

QString InterfaceMidi::midiNotes[12] = {"C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};

InterfaceMidi::InterfaceMidi(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceMidi) {
    ui->setupUi(this);
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));

    portOutName = "From IanniX";
    portInName  = "To IanniX";

    try {
        portOut.insert(getPortName(portOutName), new RtMidiOut(RtMidi::UNSPECIFIED, portOutName.toStdString()));
        portIn .insert(getPortName(portInName),  new RtMidiIn (RtMidi::UNSPECIFIED, portInName .toStdString()));

#if !defined(__LINUX_ALSASEQ__) && !defined(__MACOSX_CORE__)
        if (portOut.value(getPortName(portOutName))->getPortCount() == 0)
            portOut.remove(getPortName(portOutName));
        if (portIn.value(getPortName(portInName))->getPortCount() == 0)
            portIn.remove(getPortName(portInName));
#endif
#if defined(__LINUX_ALSASEQ__) || defined(__MACOSX_CORE__)
        if(portOut.value(getPortName(portOutName)) != 0)
            portOut.value(getPortName(portOutName))->openVirtualPort(portOutName.toStdString());
        if(portIn.value(getPortName(portInName)) != 0)
            portIn .value(getPortName(portInName))->openVirtualPort(portInName .toStdString());
        if(ui->aliasPort->findText(portOutName) < 0)
            ui->aliasPort->addItem(portOutName);
#endif
    } catch (RtError& err) {}
    if(portIn.value(getPortName(portInName))) {
        portIn.value(getPortName(portInName))->setCallback(&midiCallback, this);
        portIn.value(getPortName(portInName))->ignoreTypes(true, false, true);
    }

    //Interfaces link
    enable.setAction(ui->enable,          "interfaceMidiEnable");
    syncTransportIn .setAction(ui->syncTransportIn,  "interfaceMidiSyncTransportIn");
    syncTransportOut.setAction(ui->syncTransportOut, "interfaceMidiSyncTransportOut");
    syncBpm.setAction(ui->bpm,            "interfaceMidiSyncBpm");
    MessageManager::aliases["midi_out"].setAction(ui->aliasPort, "interfaceMidiPortAlias");

    //syncClock.setAction(ui->syncClock,    "interfaceMidiSyncClock");
#ifdef Q_OS_WIN
    MessageManager::aliases["midi_out"] = "Microsoft GS Wavetable Synth";
#else
    MessageManager::aliases["midi_out"] = portOutName;
#endif
    syncBpm = 120;

    startTimer(5000);
}

QString InterfaceMidi::getNoteName(quint16 noteValue) {
    return QString("%1%2").arg(midiNotes[noteValue % 12]).arg((noteValue / 12)-1);
}


void InterfaceMidi::timerEvent(QTimerEvent*) {
    RtMidiIn *portListIn = new RtMidiIn();
    quint8 portListInCount = portListIn->getPortCount();
    for(quint8 portListInIndex = 0; portListInIndex < portListInCount ; portListInIndex++) {
        try {
            QString portName = QString::fromStdString(portListIn->getPortName(portListInIndex));
            if((!portIn.contains(getPortName(portName))) && (portName != portOutName)) {
                portIn.insert(getPortName(portName), new RtMidiIn());
                portIn.value(getPortName(portName))->openPort(portListInIndex);
                portIn.value(getPortName(portName))->setCallback(&midiCallback, this);
                portIn.value(getPortName(portName))->ignoreTypes(true, true, true);
            }
        }
        catch(RtError &err) {}
    }
    delete portListIn;

    RtMidiOut *portListOut = new RtMidiOut();
    quint8 portListOutCount = portListOut->getPortCount();
    for(quint8 portListOutIndex = 0; portListOutIndex < portListOutCount ; portListOutIndex++) {
        try {
            QString portName = QString::fromStdString(portListOut->getPortName(portListOutIndex));
            if((!portOut.contains(getPortName(portName))) && (portName != portInName)) {
                if(ui->aliasPort->findText(portName) < 0)
                    ui->aliasPort->addItem(portName);
                portOut.insert(getPortName(portName), new RtMidiOut());
                portOut.value(getPortName(portName))->openPort(portListOutIndex);
            }
        }
        catch(RtError &err) {}
    }
    delete portListOut;
}

bool InterfaceMidi::send(const Message &_message, QStringList *messageSent) {
    if(!enable)
        return false;

    Message message  = _message;
    quint8 channel   = qBound(1, (int)message.getMidiValue(0), 16);
    QString portname = message.getMidiPort();
    QString command  = message.getMidiCommand().toLower();

    //Send request
    if(command == "/notef") {
        message.setMidiValue(1, qBound(0, (int)(message.getMidiValue(1)*127.), 127));
        message.setMidiValue(2, qBound(0, (int)(message.getMidiValue(2)*127.), 127));
    }
    else if(command == "/ccf")
        message.setMidiValue(2, qBound(0, (int)(message.getMidiValue(2)*127.), 127));
    else if(command == "/pgmf")
        message.setMidiValue(1, message.getMidiValue(1)*127.);
    else if(command == "/bendf")
        message.setMidiValue(1, message.getMidiValue(1)*127.);


    if((command == "/note") || (command == "/notef")) {
        message.setMidiValue(1, message.getMidiValue(1), getNoteName(message.getMidiValue(1)));
        message.setMidiValue(3, message.getMidiValue(3), QString("%1 s.").arg(message.getMidiValue(3)));
        sendNote(portname, channel, message.getMidiValue(1), message.getMidiValue(2));
        qreal duration = message.getMidiValue(3) * 1000.;
        if(duration > 0)
            new ExtMidiNoteOff(this, portname, channel, message.getMidiValue(1), duration);
    }
    else if((command == "/cc") || (command == "/ccf"))
        sendCC  (portname, channel, message.getMidiValue(1), message.getMidiValue(2));
    else if((command == "/pgm") || (command == "/pgmf"))
        sendPGM (portname, channel, message.getMidiValue(1));
    else if((command == "/bend") || (command == "/bendf"))
        sendBend(portname, channel, message.getMidiValue(1));

    //Log in console
    MessageManager::logSend(message, messageSent);

    return true;
}

void InterfaceMidi::sendNote(const QString & portname, quint8 channel, qreal _note, qreal _velocity) {
    std::vector<unsigned char> message;
    quint16 note     = qBound(0, (int)_note,     127);
    quint16 velocity = qBound(0, (int)_velocity, 127);

    note = (note > 0x7f) ? 0x7f : note;
    velocity = (velocity > 0x7f) ? 0x7f : velocity;

    if(velocity > 0)
        message.push_back(STATUS_NOTEON + ((channel-1) & MASK_CHANNEL));
    else
        message.push_back(STATUS_NOTEOFF + ((channel-1) & MASK_CHANNEL));

    message.push_back(note & MASK_SAFETY);
    message.push_back(velocity & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
        } catch (RtError& err) { }
    }
}
void InterfaceMidi::sendCC(const QString & portname, quint8 channel, quint16 controller, qreal _value) {
    std::vector<unsigned char> message;
    quint16 value = qBound(0, (int)_value, 127);

    controller = (controller > 0x7f) ? 0x7f : controller;
    value      = (value > 0x7f) ? 0x7f : value;

    // Controller: 0xB0 + channel, ctl, val
    message.push_back(STATUS_CTLCHG + ((channel-1) & MASK_CHANNEL));
    message.push_back(controller & MASK_SAFETY);
    message.push_back(value & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
        } catch (RtError& err) { }
    }
}
void InterfaceMidi::sendPGM(const QString & portname, quint8 channel, quint16 program) {
    std::vector<unsigned char> message;
    program = (program > 0x7f) ? 0x7f : program;

    // Program: 0xC0 + channel, pgm
    message.push_back(STATUS_PROGRAM + ((channel-1) & MASK_CHANNEL));
    message.push_back(program & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
        } catch (RtError& err) {  }
    }
}
void InterfaceMidi::sendBend(const QString & portname, quint8 channel, qreal _bendvalue) {
    std::vector<unsigned char> message;
    quint16 bendvalue = _bendvalue;
    bendvalue = (bendvalue > 0x3fff) ? 0x3fff : bendvalue;

    // Bend: 0xE0 + channel, 7LeastSigBits, 7MostSigBits
    quint8 lsb = 0x7f & bendvalue;
    quint8 msb = 0x7f & (bendvalue >> 7);

    message.push_back(STATUS_BEND + ((channel-1) & MASK_CHANNEL));
    message.push_back(lsb & MASK_SAFETY);
    message.push_back(msb & MASK_SAFETY);

    if((message.size() > 0) && (portOut.contains(portname))) {
        try {
            portOut.value(portname)->sendMessage(&message);
        } catch (RtError& err) { }
    }
}
void InterfaceMidi::networkSynchro(bool start) {
    if(syncTransportOut) {
        if(start) {
            sendSPPTime(Transport::timeLocal);
            sendSPPStart();
        }
        else
            sendSPPStop();
    }
}

void InterfaceMidi::sendSPPStart() {
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
void InterfaceMidi::sendSPPStop() {
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
void InterfaceMidi::sendSPPTime(qreal time) {
    quint16 slaveTime = (time / ((60. / syncBpm) / 16.)) / 4.;
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

void InterfaceMidi::receivedMessage(const QString & destination, const QStringList & arguments) {
    if(!enable)
        return;

    mutex.lock();
    receivedMessages << qMakePair(destination, arguments);
    mutex.unlock();
}
void InterfaceMidi::networkManualParsing() {
    mutex.lock();
    while(receivedMessages.count()) {
        //Fire events (log, message and script mapping)
        QString command = receivedMessages.first().first;
        //foreach(const QString &commandArgs, receivedMessages.first().second) {
        for(quint16 i = 0 ; i < receivedMessages.first().second.count() ; i++) {
            if((receivedMessages.first().first == "note") && (i == 1))
                command += QString(" %1 (%2)").arg(receivedMessages.first().second.at(i)).arg(getNoteName(receivedMessages.first().second.at(i).toInt()));
            else
                command += " " + receivedMessages.first().second.at(i);
        }
        MessageManager::incomingMessage(MessageIncomming("midi", "midiin", QVariant(), receivedMessages.first().first, command, QStringList() << receivedMessages.first().second));
        receivedMessages.removeFirst();
    }
    while(receivedCommands.count()) {
        Application::synchroLoopGuard = this;
        Application::current->execute(receivedCommands.first(), ExecuteSourceNetwork);
        Application::synchroLoopGuard = 0;
        receivedCommands.removeFirst();
    }
    mutex.unlock();
}
void InterfaceMidi::receivedMidiRealtime(quint8 type, quint8 val1, quint8 val2) {
    if(syncTransportIn) {
        mutex.lock();
        if(type == MIDI_SPP) {
            qreal time = (128*val2 + val1) * 4 * ((60. / syncBpm) / 16);
            if(time == 0)   receivedCommands << COMMAND_FF;
            else            receivedCommands << QString("%1 %2").arg(COMMAND_GOTO).arg(time);
        }
        else if((type == MIDI_CLOCK) || (type == MIDI_TICK) || (type == MIDI_TIMECODE)) {
            //qreal delta = (60. / syncBpm) / 24.;
            //qreal slaveTime = midiMtc.decode(val1);
            //qDebug("TIMECODE %f", slaveTime);
        }
        else if(type == MIDI_CONTINUE)
            receivedCommands << COMMAND_PLAY;
        else if(type == MIDI_STOP)
            receivedCommands << COMMAND_STOP;
        else if(type == MIDI_START)
            receivedCommands << COMMAND_PLAY;
        mutex.unlock();
    }
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

void InterfaceMidi::clear() {
    foreach(RtMidiIn  *port, portIn)
        delete port;
    portIn.clear();
    foreach(RtMidiOut *port, portOut)
        delete port;
    portOut.clear();
}
InterfaceMidi::~InterfaceMidi() {
    clear();
    delete ui;
}


void midiCallback(double, std::vector< unsigned char > *receivedMessage, void *userData) {
    InterfaceMidi *midi = (InterfaceMidi*)userData;
    quint8 receivedMessageBytes = receivedMessage->size();
    if(receivedMessageBytes > 0) {
        quint8 status = receivedMessage->at(0) & MASK_STATUS;
        quint8 channel = (receivedMessage->at(0) & MASK_CHANNEL) + 1;

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
        case STATUS_BEND:
            midi->receivedMessage("bend", QStringList() << QString::number(channel) << QString::number(receivedMessage->at(1)));
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
