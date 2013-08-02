#ifndef INTERFACEOSC_H
#define INTERFACEOSC_H

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
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/MaxMSP/").absoluteFilePath()));
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/PureData/").absoluteFilePath()));
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/Processing/").absoluteFilePath()));
    }

private:
    QUdpSocket *socket;
    QString oscMatchAdressIanniX, oscMatchAdressTransport;
    QList<Message> bundleMessages;
    quint64 bundleMessageId;
private:
    quint8 bufferI[4096], bufferO[4096];
    quint16 bufferISize, bufferOSize;
    char addressBuffer[255], argumentsBuffer[255];
    quint16 indexAddressBuffer, indexArgumentsBuffer;
private slots:
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
