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

#ifndef INTERFACEMIDI_H
#define INTERFACEMIDI_H

#include <QWidget>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include "misc/options.h"
#include "qrtmidi/RtMidi.h"
#include "messages/messagemanager.h"

#define MASK_CHANNEL      0x0f
#define MASK_STATUS       0xf0
#define MASK_SAFETY       0x7f

#define STATUS_NOTEOFF    0x80
#define STATUS_NOTEON     0x90
#define STATUS_AFTERTOUCH 0xA0
#define STATUS_CTLCHG     0xB0
#define STATUS_PROGRAM    0xC0
#define STATUS_PRESSURE   0xD0
#define STATUS_BEND       0xE0

#define MIDI_CLOCK        0xF8
#define MIDI_TICK         0xF9
#define MIDI_START        0xFA
#define MIDI_STOP         0xFC
#define MIDI_CONTINUE     0xFB
#define MIDI_SPP          0xF2
#define MIDI_TIMECODE     0xF1

#define kMTCFrames      0
#define kMTCSeconds     1
#define kMTCMinutes     2
#define kMTCHours       3

void midiCallback(double deltatime, std::vector< unsigned char > *receivedMessage, void *userData);


class ExtMidiMTC : public QObject {
    Q_OBJECT
public:
    qreal decode(quint16);

private:
    int     port, channel, status, byteOne, byteTwo;
    double  timestamp;
};

namespace Ui {
class InterfaceMidi;
}

class InterfaceMidi : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceMidi(QWidget *parent = 0);
    void clear();
    ~InterfaceMidi();

public:
    static UiBool syncTransportIn, syncTransportOut;
    static QString midiNotes[12];
    static QString getNoteName(quint16 noteValue);
private:
    UiReal syncBpm;
    UiString portAlias;
    UiBool enable;

private:
    QHash<QString, RtMidiIn*> portIn;
    QHash<QString, RtMidiOut*> portOut;
    QList<QPair<QString, QStringList> > receivedMessages;
    QStringList receivedCommands;
    QMutex mutex;
    static QString portOutName, portInName;
private:
    const QString getPortName(QString port) {
        return qPrintable(port.replace(" ", "_").replace("/", "_").toLower().trimmed());
    }

public:
    ExtMidiMTC midiMtc;

protected:
    void timerEvent(QTimerEvent *);

public:
    bool send(const Message &message, QStringList *messageSent = 0);
    void sendNote(const QString & portname, quint8 channel, qreal   note,       qreal velocity);
    void sendCC  (const QString & portname, quint8 channel, quint16 controller, qreal value);
    void sendPGM (const QString & portname, quint8 channel, quint16 program);
    void sendBend(const QString & portname, quint8 channel, qreal   bendvalue);
    void networkSynchro(bool start);
private:
    void sendSPPStart();
    void sendSPPStop();
    void sendSPPTime(qreal time);

public slots:
    void receivedMessage(const QString & destination, const QStringList &arguments);
    void receivedMidiRealtime(quint8 type, quint8 val1, quint8 val2);
    void networkManualParsing();
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/Ableton Live/").absoluteFilePath()));
    }
    void downloadMidiJack() {
        QDesktopServices::openUrl(QUrl("http://www.nerds.de/data/setuploopbe1.exe"));
    }

private:
    Ui::InterfaceMidi *ui;
};


class ExtMidiNoteOff : public QObject {
    Q_OBJECT

private:
    QString portname;
    quint8 channel;
    quint16 note;
    InterfaceMidi *manager;

public:
    ExtMidiNoteOff(InterfaceMidi *_manager, const QString & _portname, quint8 _channel, quint16 _note, quint16 delay) {
        manager = _manager;
        portname = _portname;
        channel = _channel;
        note = _note;
        startTimer(delay);
    }
protected:
    void timerEvent(QTimerEvent *e) {
        manager->sendNote(portname, channel, note, 0);
        killTimer(e->timerId());
        delete this;
    }
};



#endif // INTERFACEMIDI_H
