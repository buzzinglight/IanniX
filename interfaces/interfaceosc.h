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

#ifndef INTERFACEOSC_H
#define INTERFACEOSC_H

#include <QTimer>
#include <QWidget>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostInfo>
#include "misc/options.h"
#include "messages/messagemanager.h"
#include "gui/uihelp.h"
#ifdef ZEROCONF_AS_BROWSER
#include "zeroconf/bonjourserviceresolver.h"
#include "zeroconf/bonjourservicebrowser.h"
#endif
#ifdef ZEROCONF_AS_SERVICE
#include "zeroconf/bonjourserviceregister.h"
#endif

namespace Ui {
class InterfaceOsc;
}

class BonjourService {
#ifdef ZEROCONF_AS_BROWSER
public:
    explicit BonjourService(const BonjourRecord &_record) { reset(); setAction(); record = _record; name = record.serviceName; isBonjour = true }
public:
    BonjourRecord record;
#endif

public:
    bool isBonjour;
    explicit BonjourService(const QString &_name, QHostAddress _host, quint16 _port)   { reset(); setAction(); isBonjour = false; name = _name; host = _host; port = _port; }
    void reset()                         { port = 0;  }
    QAction* setAction(QAction *_action = 0) { action = _action; return action; }
public:
    QString name;
    QHostAddress host;
    quint16 port;
    QAction *action;
public:
    static bool sort(const BonjourService &first, const BonjourService &second) {
        return first.name < second.name;
    }
};

class InterfaceOsc : public NetworkInterface {
    Q_OBJECT

public:
    explicit InterfaceOsc(QWidget *parent = 0);
    ~InterfaceOsc();

private:
    UiReal port, bundlePort;
    UiString bundleHost;
    UiBool enable;

private:
    QMenu *bonjourMenu;
    QList<BonjourService> bonjourServices;
private slots:
    void openBonjour();
    void bonjourScan();
#ifdef ZEROCONF_AS_BROWSER
private:
    qint16 bonjourListCurrent;
    BonjourServiceBrowser  *bonjourBrowser;
    BonjourServiceResolver *bonjourResolver;
    bool bonjourIsScanning;
private slots:
    void currentBonjourRecordsChanged(const QList<BonjourRecord> &);
    void bonjourRecordResolved();
    void bonjourRecordResolved(const QHostInfo &, int);
#endif
#ifdef ZEROCONF_AS_SERVICE
public:
    BonjourServiceRegister *bonjourRegisterIn, *bonjourRegisterOut;
#endif

private slots:
    void portChanged();
    void portOutChanged();
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(Application::pathApplication.absoluteFilePath() + "/Patches/MaxMSP/").absoluteFilePath()));
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(Application::pathApplication.absoluteFilePath() + "/Patches/PureData/").absoluteFilePath()));
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(Application::pathApplication.absoluteFilePath() + "/Patches/Processing/").absoluteFilePath()));
    }

private:
    QUdpSocket *socket;
    QString oscMatchAdressIanniX, oscMatchAdressTransport;
    QList<Message> bundleMessages;
    quint64 bundleMessageId;
private:
    quint8 bufferI[4096*4], bufferO[4096*4];
    qint16 bufferISize, bufferOSize;
    char addressBuffer[255], argumentsBuffer[255];
    quint16 indexAddressBuffer, indexArgumentsBuffer;
public slots:
    void parseOSC();

public:
    bool send(const Message &message, QStringList *messageSent = 0);
    void networkBundle(bool start);
    void networkSynchro(bool start);
    void networkSynchro(const QString &info);

private:
    Ui::InterfaceOsc *ui;
};

#endif // INTERFACEOSC_H
