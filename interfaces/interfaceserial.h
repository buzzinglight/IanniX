#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H

#include <QWidget>
#include "misc/options.h"
#include "messages/messagemanager.h"
#include "qextserialport/qextserialport.h"
#include "qextserialport/qextserialenumerator.h"

namespace Ui {
class InterfaceSerial;
}

class InterfaceSerial : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceSerial(QWidget *parent = 0);
    ~InterfaceSerial();

private:
    UiString portName;
    UiReal portBaud, portBits, portParity, portStop, portFlow;
    UiBool enable;
private slots:
    void portChanged();
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/Arduino/").absoluteFilePath()));
    }

private:
    void timerEvent(QTimerEvent *);

private:
    QextSerialPort *port;
    QList<BaudRateType> baudrateEnum;
    QList<DataBitsType> databitsEnum;
    QList<ParityType>   parityEnum;
    QList<StopBitsType> stopbitsEnum;
    QList<FlowType>     flowEnum;
    QByteArray reception;
private slots:
    void parse();

public:
    bool send(const Message &message, QStringList *messageSent = 0);

private:
    Ui::InterfaceSerial *ui;
};

#endif // INTERFACESERIAL_H
