#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H

#include <QWidget>
#include "misc/options.h"
#include "messages/messagemanager.h"
#include "qextserialport/qextserialport.h"

namespace Ui {
class InterfaceSerial;
}

class InterfaceSerial : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceSerial(QWidget *parent = 0);
    ~InterfaceSerial();

private:
    UiString portStr;
    UiBool enable;
private slots:
    void portChanged();
    void openExamples() {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("Patches/Arduino/").absoluteFilePath()));
    }

private:
    QextSerialPort *port;
    QString portname;
    BaudRateType baudrate;
    DataBitsType databits;
    ParityType parity;
    StopBitsType stopbits;
    FlowType flow;
    QMap<QString, BaudRateType> baudrateEnum;
    QMap<QString, DataBitsType> databitsEnum;
    QMap<QString, ParityType> parityEnum;
    QMap<QString, StopBitsType> stopbitsEnum;
    QMap<QString, FlowType> flowEnum;
    QByteArray reception;
private slots:
    void parse();

public:
    bool send(const Message & message);

private:
    Ui::InterfaceSerial *ui;
};

#endif // INTERFACESERIAL_H
