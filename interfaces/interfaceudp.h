#ifndef INTERFACEUDP_H
#define INTERFACEUDP_H

#include <QWidget>
#include "misc/options.h"
#include "messages/messagemanager.h"

namespace Ui {
class InterfaceUdp;
}

class InterfaceUdp : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceUdp(QWidget *parent = 0);
    ~InterfaceUdp();

private:
    UiReal port;
    UiBool enable;
private slots:
    void portChanged();
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/PureData/").absoluteFilePath()));
    }

private:
    QUdpSocket *socket;
    char bufferI[4096];
    quint16 bufferISize;
private slots:
    void parseOSC();

public:
    bool send(const Message &message, QStringList *messageSent = 0);

private:
    Ui::InterfaceUdp *ui;
};

#endif // INTERFACEUDP_H
