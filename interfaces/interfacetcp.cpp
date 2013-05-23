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
    port = 3000;
}

InterfaceTcpServer::InterfaceTcpServer(QObject *parent) :
    QTcpServer(parent) {
}

void InterfaceTcp::portChanged() {
    if(tcpServer->portChanged(port.val()))  ui->port->setStyleSheet(ihmFeedbackOk);
    else                                    ui->port->setStyleSheet(ihmFeedbackNok);

}
bool InterfaceTcpServer::portChanged(quint16 port) {
    //Initialization
    close();
    return listen(QHostAddress::Any, port);
}


bool InterfaceTcp::send(const Message & message) {
    if(!enable)
        return false;
    return tcpServer->send(message);
}
bool InterfaceTcpServer::send(const Message & message) {
    bool ok = false;
    //Send request
    foreach(QTcpSocket *socket, sockets) {
        QByteArray xml;
        xml += "<OSCPACKET ADDRESS=\"" + socket->localAddress().toString() + "\" PORT=\"" + QByteArray::number(socket->localPort()) + "\" TIME=\"" + QByteArray::number(Transport::timeLocal) + "\"><MESSAGE NAME=\"/" + message.getAddress() + "\">" + message.getAsciiMessage() + "</MESSAGE></OSCPACKET>";
        xml += (char)0;
        socket->write(xml);
        socket->flush();

        //Log in console
        MessageManager::logSend(message);
        ok = true;
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
        QDomDocument xmlDoc;
        xmlDoc.setContent(socket->readAll());
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
    if(tcpServer->sockets.count() == 0)        ui->clients->setText(tr("No client connected"));
    else if(tcpServer->sockets.count() == 1)   ui->clients->setText(tr("1 client connected"));
    else                                       ui->clients->setText(tr("%1 clients connected").arg(tcpServer->sockets.count()));
}


InterfaceTcp::~InterfaceTcp() {
    delete ui;
}
