#include "interfacetcp.h"
#include "ui_interfacetcp.h"

InterfaceTcp::InterfaceTcp(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceTcp) {
    ui->setupUi(this);
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));

    tcpServer = new InterfaceTcpServer(this);
    connect(tcpServer, SIGNAL(updateConnectedClients()),           SLOT(updateConnectedClients()));
    connect(tcpServer, SIGNAL(parseXml(QDomDocument,QTcpSocket*)), SLOT(parseXml(QDomDocument,QTcpSocket*)));

    //Interfaces link
    enable.setAction(ui->enable, "interfaceTcpEnable");
    port.setAction(ui->port,     "interfaceTcpPort");
    connect(&port, SIGNAL(triggered(qreal)), SLOT(portChanged()));
    type.setAction(QList<QRadioButton*>() << ui->typeRaw << ui->typeXml, "interfaceTcpXml");
    connect(&type, SIGNAL(triggered(qreal)), SLOT(typeChanged()));
    port = 3000;
}

InterfaceTcpServer::InterfaceTcpServer(QObject *parent) :
    QTcpServer(parent) {
    xmlMode = false;
}

void InterfaceTcp::portChanged() {
    if(tcpServer->portChanged(port.val()))  ui->port->setStyleSheet(ihmFeedbackOk);
    else                                    ui->port->setStyleSheet(ihmFeedbackNok);
}
void InterfaceTcp::typeChanged() {
    tcpServer->xmlMode = (type.val() > 0);
}
bool InterfaceTcpServer::portChanged(quint16 port) {
    //Initialization
    close();
    return listen(QHostAddress::Any, port);
}


bool InterfaceTcp::send(const Message &message, QStringList *messageSent) {
    if(!enable)
        return false;
    return tcpServer->send(message, messageSent);
}
bool InterfaceTcpServer::send(const Message &message, QStringList *messageSent) {
    bool ok = false;
    //Send request
    foreach(QTcpSocket *socket, sockets) {
        if(xmlMode) {
            QByteArray xml;
            xml += "<OSCPACKET ADDRESS=\"" + socket->localAddress().toString() + "\" PORT=\"" + QByteArray::number(socket->localPort()) + "\" TIME=\"" + QByteArray::number(Transport::timeLocal) + "\"><MESSAGE NAME=\"/" + message.getAddress() + "\">" + message.getAsciiMessageXml() + "</MESSAGE></OSCPACKET>";
            xml += (char)0;
            socket->write(xml);
            socket->flush();

            //Log in console
            MessageManager::logSend(message, messageSent);
            ok = true;
        }
        else {
            socket->write(message.getAsciiMessage());
            QString dataSent = message.getAsciiMessage();

            //Log in console
            MessageManager::logSend(message, messageSent);
            ok = true;
        }
    }
    return ok;
}


//TCP reception
void InterfaceTcpServer::incomingConnection(int socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),    this, SLOT(readClient()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discardClient()));
    socket->setSocketDescriptor(socketDescriptor);
    sockets.append(socket);
    emit(updateConnectedClients());
}
void InterfaceTcpServer::readClient() {
    QTcpSocket *socket = (QTcpSocket*)sender();
    if(socket->isReadable()) {
        if(xmlMode) {
            //XML parsing
            QDomDocument xmlDoc;
            xmlDoc.setContent(socket->readAll());
            emit(parseXml(xmlDoc, socket));
        }
        else {
            //RAW data
            QByteArray dataReceived = socket->readAll();
            QStringList arguments;
            for(quint16 indexBuffer = 0 ; indexBuffer < dataReceived.count() ; indexBuffer += 4) {
                union { float f; char ch[4]; } u;
                u.ch[3] = dataReceived[indexBuffer + 3];
                u.ch[2] = dataReceived[indexBuffer + 2];
                u.ch[1] = dataReceived[indexBuffer + 1];
                u.ch[0] = dataReceived[indexBuffer + 0];
                qreal val = u.f;
                arguments << QString::number(val);
            }
            MessageManager::incomingMessage(MessageIncomming("tcp", socket->peerAddress().toString(), socket->peerPort(), "tcp_raw", "", arguments));
        }
    }
}

void InterfaceTcp::parseXml(const QDomDocument &xmlDoc, QTcpSocket *socket) {
    if(!enable)
        return;

    //Racine
    QDomElement xmlPacket = xmlDoc.documentElement();

    //Parse les menaces
    QDomNode xmlOscMessage = xmlPacket.firstChild();
    while(!xmlOscMessage.isNull()) {
        QDomElement xmlMessage = xmlOscMessage.toElement();
        if((!xmlMessage.isNull()) && (xmlMessage.tagName().toUpper() == "MESSAGE")) {
            QString destination = xmlMessage.attribute("NAME");
            QDomNode xmlOscArgument = xmlMessage.firstChild();
            while(!xmlOscArgument.isNull()) {
                QDomElement xmlArgument = xmlOscArgument.toElement();
                if((!xmlArgument.isNull()) && (xmlArgument.tagName().toUpper() == "ARGUMENT")) {
                    QString command = xmlArgument.attribute("VALUE").replace("%20", " ");
                    MessageManager::incomingMessage(MessageIncomming("tcp", socket->peerAddress().toString(), socket->peerPort(), destination, command, command.split(" ", QString::SkipEmptyParts)));
                }
                xmlOscArgument = xmlOscArgument.nextSibling();
            }
        }
        xmlOscMessage = xmlOscMessage.nextSibling();
    }
}
void InterfaceTcpServer::discardClient() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    sockets.removeOne(socket);
    emit(updateConnectedClients());
    socket->deleteLater();
}


void InterfaceTcp::updateConnectedClients() {
    QString clients;
    foreach(QTcpSocket *socket, tcpServer->sockets)
        clients += QString("%1:%2\n").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    clients.chop(1);
    if(tcpServer->sockets.count() == 0)        ui->clients->setText(tr("No client connected"));
    else if(tcpServer->sockets.count() == 1)   ui->clients->setText(tr("1 client connected\n(%1)").arg(clients));
    else                                       ui->clients->setText(tr("%1 clients connected").arg(tcpServer->sockets.count()));
    ui->clients->setToolTip(clients);
}


InterfaceTcp::~InterfaceTcp() {
    delete ui;
}
