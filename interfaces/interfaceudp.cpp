#include "interfaceudp.h"
#include "ui_interfaceudp.h"

InterfaceUdp::InterfaceUdp(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceUdp) {
    ui->setupUi(this);
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));
    socket = 0;

    //Interfaces link
    enable.setAction(ui->enable, "interfaceUdpEnable");
    port.setAction(ui->port,     "interfaceUdpPort");
    connect(&port, SIGNAL(triggered(qreal)), SLOT(portChanged()));
    port = 1235;
}

void InterfaceUdp::portChanged() {
    //Create a new UDP socket and bind signals
    if(socket)
        delete socket;
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(parseOSC()));

    if(socket->bind(port))  ui->port->setStyleSheet(ihmFeedbackOk);
    else                    ui->port->setStyleSheet(ihmFeedbackNok);
}



void InterfaceUdp::parseOSC() {
    //Parse all UDP datagram
    while(socket->hasPendingDatagrams()) {
        //Extract host, port & UDP datagram
        QHostAddress receivedHost;
        quint16 receivedPort;
        bufferISize = socket->readDatagram((char*)bufferI, 4096, &receivedHost, &receivedPort);
        bufferI[bufferISize] = 0;

        if(enable) {
            QString commands = bufferI;
            commands.replace(";", COMMAND_END);
            QStringList commandItems = commands.split(COMMAND_END, QString::SkipEmptyParts);;
            foreach(const QString & command, commandItems)
                MessageManager::incomingMessage(MessageIncomming("udp", receivedHost.toString(), receivedPort, "", command, command.split(" ", QString::SkipEmptyParts)));
        }
    }
}

bool InterfaceUdp::send(const Message &message, QStringList *messageSent) {
    if(!enable)
        return false;

    //Write a message on the opened socket
    socket->writeDatagram(message.getAsciiMessage() + ';' + '\n', message.getHost(), message.getPort());

    //Log in console
    MessageManager::logSend(message, messageSent);

    return true;
}

InterfaceUdp::~InterfaceUdp() {
    delete ui;
}
