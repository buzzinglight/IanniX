#ifndef EXTSERIALMANAGER_H
#define EXTSERIALMANAGER_H

#include "extmessage.h"
#include "qextserialport/qextserialport.h"

class ExtSerialManager : public QObject, public ExtMessageManager {
    Q_OBJECT

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

public:
    ExtSerialManager(NxObjectFactoryInterface *_factory);

public:
    void send(const ExtMessage & message);

public slots:
    void openPort(const QString &);
signals:
    void openPortStatus(bool);

private slots:
    void parse();
};

#endif // EXTSERIALMANAGER_H
