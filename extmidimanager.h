#ifndef EXTMIDIMANAGER_H
#define EXTMIDIMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include "extmessage.h"
#include "qrtmidi/RtMidi.h"

#define MASK_CHANNEL      0x0f
#define MASK_STATUS       0xf0
#define MASK_SAFETY       0x7f

#define STATUS_NOTEOFF    0x80
#define STATUS_NOTEON     0x90
#define STATUS_CTLCHG     0xB0
#define STATUS_PROGRAM    0xC0


void midiCallback(double deltatime, std::vector< unsigned char > *receivedMessage, void *userData);

class ExtMidiManager : public QObject, public ExtMessageManager {
    Q_OBJECT

private:
    QHash<QString, RtMidiIn*> portIn;
    QHash<QString, RtMidiOut*> portOut;

public:
    ExtMidiManager(NxObjectFactoryInterface *_factory);

public:
    void send(const ExtMessage & message);

public slots:
    void receivedMessage(const QString & url);
 };

#endif // EXTMIDIMANAGER_H
