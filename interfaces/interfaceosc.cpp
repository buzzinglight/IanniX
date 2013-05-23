#include "interfaceosc.h"
#include "ui_interfaceosc.h"

InterfaceOsc::InterfaceOsc(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceOsc) {
    ui->setupUi(this);
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));

    //OSC adress of IanniX
    oscMatchAdress = "/iannix/";
    bundleMessageId = 0;

    bundlePort = 0;
    bundleMessageId = 0;

    //Create a new UDP socket and bind signals
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(parseOSC()));

    //Interfaces link
    enable.setAction(ui->enable,         "interfaceOscEnable");
    bundlePort.setAction(ui->bundlePort, "interfaceOscBundlePort");
    port.setAction(ui->port,             "interfaceOscPort");
    bundleHost.setAction(ui->bundleIp,   "interfaceOscBundleHost");
    connect(&port, SIGNAL(triggered(qreal)), SLOT(portChanged()));
    MessageManager::aliases["ip_out"].setAction(ui->aliasPort, "interfaceOscPortAlias");
    MessageManager::aliases["ip_out"]  = "127.000.000.001";
    port = 1234;
    bundlePort = 57130;
    bundleHost = "127.000.000.001";
}

void InterfaceOsc::portChanged() {
    socket->close();
    if(socket->bind(port))  ui->port->setStyleSheet(ihmFeedbackOk);
    else                    ui->port->setStyleSheet(ihmFeedbackNok);
    UiHelp::oscPort = port;
}


void InterfaceOsc::parseOSC() {
    //Parse all UDP datagram
    while(socket->hasPendingDatagrams()) {
        //Extract host, port & UDP datagram
        QHostAddress receivedHost;
        quint16 receivedPort;
        bufferISize = socket->readDatagram((char*)bufferI, 4096, &receivedHost, &receivedPort);


        if(enable) {
            quint16 indexBuffer = 0;
            //Parse UDP content
            while(indexBuffer < bufferISize) {
                indexAddressBuffer = 0;
                indexArgumentsBuffer = 0;

                //Looking for '/'
                while((indexBuffer < bufferISize) && (bufferI[indexBuffer] != '/'))
                    indexBuffer++;

                //Parse header
                if((bufferI[indexBuffer] =='/') && (bufferISize%4 == 0)) {
                    //OSC Adress
                    while((indexBuffer < bufferISize) && (bufferI[indexBuffer] != 0))
                        addressBuffer[indexAddressBuffer++] = bufferI[indexBuffer++];
                    addressBuffer[indexAddressBuffer] = 0;

                    //Looking for ','
                    while((indexBuffer < bufferISize) && (bufferI[indexBuffer++] != ',')) {}

                    //OSC arguments type
                    indexBuffer--;
                    while((indexBuffer < bufferISize) && (bufferI[++indexBuffer] != 0))
                        argumentsBuffer[indexArgumentsBuffer++] = bufferI[indexBuffer];
                    argumentsBuffer[indexArgumentsBuffer] = 0;
                    indexBuffer++;

                    //Index modulo 4
                    while((indexBuffer < bufferISize) && ((indexBuffer++)%4 != 0)) {}
                    indexBuffer--;


                    //Parse content
                    QString commandDestination = QString(addressBuffer).remove(oscMatchAdress);
                    QString command = commandDestination + " ";
                    QStringList commandArguments;
                    quint16 indexDataBuffer = 0;
                    while((indexBuffer < bufferISize) && (indexDataBuffer < indexArgumentsBuffer)) {
                        //Integer argument
                        if(argumentsBuffer[indexDataBuffer] == 'i') {
                            union { int i; char ch[4]; } u;
                            u.ch[3] = bufferI[indexBuffer + 0];
                            u.ch[2] = bufferI[indexBuffer + 1];
                            u.ch[1] = bufferI[indexBuffer + 2];
                            u.ch[0] = bufferI[indexBuffer + 3];
                            indexBuffer += 4;
                            QString commandValue = QString::number(u.i);
                            command += commandValue + " ";
                            commandArguments << commandValue;
                        }
                        //Float argument
                        else if(argumentsBuffer[indexDataBuffer] == 'f') {
                            union { float f; char ch[4]; } u;
                            u.ch[3] = bufferI[indexBuffer + 0];
                            u.ch[2] = bufferI[indexBuffer + 1];
                            u.ch[1] = bufferI[indexBuffer + 2];
                            u.ch[0] = bufferI[indexBuffer + 3];
                            indexBuffer += 4;
                            QString commandValue = QString::number(u.f);
                            command += commandValue + " ";
                            commandArguments << commandValue;
                        }
                        //String argument
                        else if(argumentsBuffer[indexDataBuffer] == 's') {
                            QString commandValue = "";
                            while((indexBuffer < bufferISize) && (bufferI[indexBuffer]) != 0)
                                commandValue += bufferI[indexBuffer++];
                            indexBuffer++;
                            while(indexBuffer % 4 != 0)
                                indexBuffer++;
                            command += commandValue + " ";
                            commandArguments << commandValue;
                        }
                        else
                            indexBuffer += 4;
                        indexDataBuffer++;
                    }

                    MessageManager::incomingMessage(MessageIncomming("osc", receivedHost.toString(), receivedPort, commandDestination, command, commandArguments));

                    if(command.toLower().startsWith("/transport play"))
                        Transport::syncStart();
                    else if(command.toLower().startsWith("/transport stop"))
                        Transport::syncStop();
                    else if(command.toLower().startsWith("/transport fastrewind"))
                        Transport::syncGoto(0);
                }
            }
        }
    }
}

void InterfaceOsc::networkSynchro(bool start) {
    if(start)   networkSynchro(QString("play"));
    else        networkSynchro(QString("stop"));
}
void InterfaceOsc::networkSynchro(const QString &info) {
    MessageManager::outgoingMessage(MessageManagerDestination(MessageManager::transportObject, 0, 0, 0, NxPoint(), NxPoint(), TransportStatus(MessageManager::transportNbTriggers, MessageManager::transportNbCursors, MessageManager::transportNbCurves, info)));
}



bool InterfaceOsc::send(const Message & message) {
    if(!enable)
        return false;

    if((message.getPort() == bundlePort) && (message.getHost() == QHostAddress(bundleHost)))
        //Add message to bundle
        bundleMessages.append(message);
    else {
        //Write a message on the opened socket
        socket->writeDatagram(message.getBuffer(), message.getHost(), message.getPort());

        //Log in console
        MessageManager::logSend(message);
    }
    return true;
}
void InterfaceOsc::networkBundle(bool start) {
    if(start)
        bundleMessages.clear();
    else if((bundlePort) && (bundleMessages.count()) && (!QHostAddress(bundleHost).isNull())) {
        QByteArray messageBuffer;
        //Bundle
        messageBuffer += "#bundle";
        messageBuffer += (char)0;
        //Timecode
        union { int i; char ch[8]; } u;
        u.i = bundleMessageId++;
        messageBuffer += u.ch[7];
        messageBuffer += u.ch[6];
        messageBuffer += u.ch[5];
        messageBuffer += u.ch[4];
        messageBuffer += u.ch[3];
        messageBuffer += u.ch[2];
        messageBuffer += u.ch[1];
        messageBuffer += u.ch[0];

        foreach(const Message &bundleMessage, bundleMessages) {
            //Size of message
            union { int i; char ch[4]; } u;
            u.i = bundleMessage.getBuffer().count();
            messageBuffer += u.ch[3];
            messageBuffer += u.ch[2];
            messageBuffer += u.ch[1];
            messageBuffer += u.ch[0];
            //Message content
            messageBuffer += bundleMessage.getBuffer();
            //Log in console
            MessageManager::logSend(bundleMessage);
        }
        bundleMessages.clear();
        socket->writeDatagram(messageBuffer, QHostAddress("127.0.0.1"), 57120);
    }
}


InterfaceOsc::~InterfaceOsc() {
    delete ui;
}
