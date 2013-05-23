#ifndef INTERFACEOSC_H
#define INTERFACEOSC_H

#include <QWidget>
#include <QByteArray>
#include <QNetworkInterface>
#include "misc/options.h"
#include "messages/messagemanager.h"
#include "gui/uihelp.h"

namespace Ui {
class InterfaceOsc;
}

class InterfaceOsc : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceOsc(QWidget *parent = 0);
    ~InterfaceOsc();

private:
    UiReal bundlePort;
    UiReal port;
    UiString bundleHost;
    UiBool enable;
private slots:
    void portChanged();
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/MaxMSP/").absoluteFilePath()));
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/PureData/").absoluteFilePath()));
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/Processing/").absoluteFilePath()));
    }

private:
    QUdpSocket *socket;
    QString oscMatchAdress;
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
    bool send(const Message & message);
    void networkBundle(bool start);
    void networkSynchro(bool start);
    void networkSynchro(const QString &info);

private:
    Ui::InterfaceOsc *ui;
};

#endif // INTERFACEOSC_H
