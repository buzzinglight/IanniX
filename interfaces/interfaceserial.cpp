#include "interfaceserial.h"
#include "ui_interfaceserial.h"

InterfaceSerial::InterfaceSerial(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceSerial) {
    ui->setupUi(this);
    port = 0;
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));

    baudrateEnum << BAUD110;
    baudrateEnum << BAUD300;
    baudrateEnum << BAUD600;
    baudrateEnum << BAUD1200;
    baudrateEnum << BAUD2400;
    baudrateEnum << BAUD4800;
    baudrateEnum << BAUD9600;
    baudrateEnum << BAUD19200;
    baudrateEnum << BAUD38400;
    baudrateEnum << BAUD57600;
    baudrateEnum << BAUD115200;

    databitsEnum << DATA_5;
    databitsEnum << DATA_6;
    databitsEnum << DATA_7;
    databitsEnum << DATA_8;

    parityEnum   << PAR_NONE;
    parityEnum   << PAR_ODD;
    parityEnum   << PAR_EVEN;
    parityEnum   << PAR_SPACE;

    stopbitsEnum << STOP_1;
    stopbitsEnum << STOP_2;

    flowEnum     << FLOW_OFF;
    flowEnum     << FLOW_HARDWARE;
    flowEnum     << FLOW_XONXOFF;

    //Interfaces link
    enable.setAction(ui->enable, "interfaceSerialEnable");

    portName  .setAction(ui->portCombo,   "interfaceSerialPortname");
    portBaud  .setAction(ui->baudCombo,   "interfaceSerialBaud");
    portBits  .setAction(ui->bitsCombo,   "interfaceSerialBits");
    portParity.setAction(ui->parityCombo, "interfaceSerialParity");
    portStop  .setAction(ui->stopCombo,   "interfaceSerialStop");
    portFlow  .setAction(ui->flowCombo,   "interfaceSerialFlow");
    connect(&portName,   SIGNAL(triggered(QString)), SLOT(portChanged()));
    connect(&portBaud,   SIGNAL(triggered(qreal)),   SLOT(portChanged()));
    connect(&portBits,   SIGNAL(triggered(qreal)),   SLOT(portChanged()));
    connect(&portParity, SIGNAL(triggered(qreal)),   SLOT(portChanged()));
    connect(&portStop,   SIGNAL(triggered(qreal)),   SLOT(portChanged()));
    connect(&portFlow,   SIGNAL(triggered(qreal)),   SLOT(portChanged()));

    portBaud   = 10;
    portBits   = 3;
    portParity = 0;
    portStop   = 0;
    portFlow   = 0;

    //Valeurs par défaut
    /*
    portStr = "COM1\nBAUD115200\nDATA_8\nPAR_NONE\nSTOP_1\nFLOW_OFF";
    portStr = "/dev/tty.usbmodemfa141\nBAUD115200\nDATA_8\nPAR_NONE\nSTOP_1\nFLOW_OFF";
    */

    timerEvent(0);
    startTimer(5000);
}

void InterfaceSerial::timerEvent(QTimerEvent *) {
    QList<QextPortInfo> portsInfo = QextSerialEnumerator::getPorts();
    foreach(const QextPortInfo &portInfo, portsInfo)
        if(ui->portCombo->findText(portInfo.portName) < 0)
            ui->portCombo->addItem(portInfo.portName);
}

void InterfaceSerial::portChanged() {
    if(enable) {
        if(port) {
            port->close();
            delete port;
        }
        port = new QextSerialPort(portName, QextSerialPort::EventDriven);
        if(port) {
            port->setBaudRate(baudrateEnum.at(portBaud.val()));
            port->setFlowControl(flowEnum .at(portFlow.val()));
            port->setParity(parityEnum    .at(portParity.val()));
            port->setDataBits(databitsEnum.at(portBits.val()));
            port->setStopBits(stopbitsEnum.at(portStop.val()));
            port->open(QIODevice::ReadWrite);

            connect(port, SIGNAL(readyRead()), this, SLOT(parse()));

            if(port->isOpen())  ui->portCombo->setStyleSheet(ihmFeedbackOk);
            else                ui->portCombo->setStyleSheet(ihmFeedbackNok);
        }
    }
}

void InterfaceSerial::parse() {
    QByteArray receptionTmp;
    int a = port->bytesAvailable();
    receptionTmp.resize(a);
    port->read(receptionTmp.data(), receptionTmp.size());

    if(enable) {
        reception.append(receptionTmp);
        bool nextMessage = true;
        while(nextMessage) {
            nextMessage = false;
            quint16 index = 0;
            QString command;
            while((index < reception.size()) && (!nextMessage)) {
                if(reception.at(index) == COMMAND_END_BYTE) {
                    reception = reception.remove(0, index);
                    index = 0;
                    command = command.remove('\n');
                    command = command.remove('\r');

                    if(command != "")
                        MessageManager::incomingMessage(MessageIncomming("serial", portName, 0, "", command, command.split(" ", QString::SkipEmptyParts)));
                    command = "";
                }
                else
                    command += reception.at(index);
                index++;
            }
        }
    }
}

bool InterfaceSerial::send(const Message &message, QStringList *messageSent) {
    if(!enable)
        return false;

    //Write a message on the opened socket
    port->write(message.getAsciiMessage() + COMMAND_END_BYTE);

    //Log in console
    MessageManager::logSend(message, messageSent);

    return true;
}

InterfaceSerial::~InterfaceSerial() {
    delete ui;
}
