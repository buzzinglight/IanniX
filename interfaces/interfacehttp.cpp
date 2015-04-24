/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "interfacehttp.h"
#include "ui_interfacehttp.h"

InterfaceHttp::InterfaceHttp(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceHttp) {
    ui->setupUi(this);

    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));

    //HTTP server
    httpServer = new InterfaceHttpServer(this);
    connect(httpServer, SIGNAL(parseRequest(QNetworkReply*)), SLOT(parseRequest(QNetworkReply*)));
    connect(httpServer, SIGNAL(parseSocket(QTcpSocket*)),     SLOT(parseSocket(QTcpSocket*)));

    //Websockets server
    webSocketServer = new WebSocketServer(this);
    connect(webSocketServer, SIGNAL(newConnection()), SLOT(webSocketsNewConnection()));

    //Html template
    QFile htmlTemplateFile(Application::pathApplication.absoluteFilePath() + "/Tools/HTML Template.html");
    if(htmlTemplateFile.open(QFile::ReadOnly)) {
        htmlTemplate = htmlTemplateFile.readAll();
        htmlTemplateFile.close();
    }

    //Interfaces link
    enable.setAction(ui->enable, "interfaceHttpEnable");
    port.setAction(ui->port,     "interfaceHttpPort");
    connect(&port, SIGNAL(triggered(qreal)), SLOT(portChanged()));
    port = 1236;
    webSocketsPort.setAction(ui->portWebSockets, "interfaceHttpWebSocketsPort");
    connect(&webSocketsPort, SIGNAL(triggered(qreal)), SLOT(portWebSocketsChanged()));
    webSocketsPort = 1237;
}

InterfaceHttpServer::InterfaceHttpServer(QObject *parent) :
    QTcpServer(parent) {
    http = new QNetworkAccessManager(this);
    connect(http, SIGNAL(finished(QNetworkReply*)), SLOT(parse(QNetworkReply*)));
}


void InterfaceHttp::portChanged() {
    if(httpServer->portChanged(port.val()))  ui->port->setStyleSheet(ihmFeedbackOk);
    else                                     ui->port->setStyleSheet(ihmFeedbackNok);
}
void InterfaceHttp::portWebSocketsChanged() {
    webSocketServer->close();
    if(webSocketServer->listen(QHostAddress::Any, webSocketsPort.val()))   ui->portWebSockets->setStyleSheet(ihmFeedbackOk);
    else                                                                   ui->portWebSockets->setStyleSheet(ihmFeedbackNok);
}
bool InterfaceHttpServer::portChanged(quint16 port) {
    //Initialization
    close();
    return listen(QHostAddress::Any, port);
}


void InterfaceHttp::webSocketsNewConnection() {
    WebSocket *webSocket = webSocketServer->nextPendingConnection();
    connect(webSocket, SIGNAL(textMessageReceived(QString)),      SLOT(webSocketsProcessMessage(QString)));
    connect(webSocket, SIGNAL(binaryMessageReceived(QByteArray)), SLOT(webSocketsProcessBinaryMessage(QByteArray)));
    connect(webSocket, SIGNAL(disconnected()),                    SLOT(webSocketsSocketDisconnected()));
    webSocketClients << webSocket;
    webSocketsUpdateConnectedClients();
}
void InterfaceHttp::webSocketsProcessMessage(const QString &message) {
    WebSocket *webSocket = qobject_cast<WebSocket *>(sender());
    if(webSocket) {
        QStringList commandItems = message.split(COMMAND_END, QString::SkipEmptyParts);;
        QString response;
        foreach(const QString & command, commandItems)
            response += MessageManager::incomingMessage(MessageIncomming("http", webSocket->peerAddress().toString(), webSocket->peerPort(), "", command, command.split(" ", QString::SkipEmptyParts)), true, (command != "goto"));
        if(!response.isEmpty())
            webSocket->send(response);
    }
}
void InterfaceHttp::webSocketsProcessBinaryMessage(const QByteArray &) {
    WebSocket *webSocket = qobject_cast<WebSocket *>(sender());
    if(webSocket) {
    }
}
void InterfaceHttp::webSocketsSocketDisconnected() {
    WebSocket *webSocket = qobject_cast<WebSocket *>(sender());
    if(webSocket) {
        webSocketClients.removeAll(webSocket);
        webSocket->deleteLater();
    }
    webSocketsUpdateConnectedClients();
}
void InterfaceHttp::webSocketsUpdateConnectedClients() {
    QString clientsWebSockets;
    foreach(WebSocket *webSocket, webSocketClients)
        clientsWebSockets += QString("%1:%2\n").arg(webSocket->peerAddress().toString()).arg(webSocket->peerPort());
    clientsWebSockets.chop(1);
    if(webSocketClients.count() == 0)        ui->clientsWebSockets->setText(tr("No websocket connected"));
    else if(webSocketClients.count() == 1)   ui->clientsWebSockets->setText(tr("1 websocket connected\n(%1)").arg(clientsWebSockets));
    else                                     ui->clientsWebSockets->setText(tr("%1 websockets connected").arg(webSocketClients.count()));
    ui->clientsWebSockets->setToolTip(clientsWebSockets);
}



bool InterfaceHttp::send(const Message &message, QStringList *messageSent) {
    if(!enable)
        return false;

    return httpServer->send(message, messageSent);
}
bool InterfaceHttpServer::send(const Message &message, QStringList *messageSent) {
    //Send request
    http->get(QNetworkRequest(message.getUrlMessage()));

    //Log in console
    MessageManager::logSend(message, messageSent);

    return true;
}


void InterfaceHttpServer::parse(QNetworkReply *reply) {
    emit(parseRequest(reply));
}
void InterfaceHttp::parseRequest(QNetworkReply *reply) {
    if(!enable)
        return;

    QStringList commandItems = QString(reply->readAll()).split(COMMAND_END, QString::SkipEmptyParts);;
    foreach(const QString & command, commandItems)
        MessageManager::incomingMessage(MessageIncomming("http", reply->url().host(), reply->url().port(), reply->url().path(), command, command.split(" ", QString::SkipEmptyParts)));
}


//HTTP reception
void InterfaceHttpServer::incomingConnection(int socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),    this, SLOT(readClient()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discardClient()));
    socket->setSocketDescriptor(socketDescriptor);
}
void InterfaceHttpServer::readClient() {
    QTcpSocket *socket = (QTcpSocket*)sender();
    if(socket->canReadLine())
        emit(parseSocket(socket));
}
void InterfaceHttp::parseSocket(QTcpSocket *socket) {
    if(!enable)
        return;

    QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
    if((tokens.count() > 1) && (tokens.at(0) == "GET")) {
        QUrl url(tokens.at(1));

        QList<QString> commands;
        QPair<QString,qint8> picFormat;
        picFormat.first = "png";
        picFormat.second = -1;
        bool isPic = false, isSync = false;
#ifdef QT4
        QList< QPair<QString, QString> > tokens = url.queryItems();
#else
        QList< QPair<QString, QString> > tokens = QUrlQuery(url.query()).queryItems();
#endif
        for(quint16 index = 0 ; index < tokens.count() ; index++) {
            QString first = tokens.at(index).first.toLower();
            if((first == "png") || (first == "jpg") || (first == "mjpg")) {
                isPic = true;
                picFormat.first  = first;
                picFormat.second = tokens.at(index).second.toInt();
            }
            else if(first == "sync")
                isSync = true;
            else
                commands.append(tokens.at(index).second);
        }

        QTextStream os(socket);
        if((commands.count() > 0) && (!isPic) && (!isSync)) {
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/plain; charset=\"utf-8\"\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "\r\n";

            QString response;
            foreach(const QString & command, commands)
                response += MessageManager::incomingMessage(MessageIncomming("http", socket->peerAddress().toString(), socket->peerPort(), url.path(), command, command.split(" ", QString::SkipEmptyParts)), true, (command != "goto")) + "\n";

            os << response;
        }
        else if(isSync) {
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/plain; charset=\"utf-8\"\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "\r\n";

            NxObjectDispatchProperty::source = ExecuteSourceCopyPaste;
            os << Application::current->serialize();
        }
        else if(isPic) {
            if((picFormat.first == "png") || (picFormat.first == "jpg")) {
                os << "HTTP/1.0 200 Ok\r\n"
                      "Content-Type: image/jpeg\r\n"
                      "Access-Control-Allow-Origin: *\r\n"
                      "\r\n";

                QByteArray byteArray;
                QBuffer buffer(&byteArray);
                if(picFormat.second == 0)
                    picFormat.second = -1;
                Application::takeScreenshot().save(&buffer, qPrintable(picFormat.first), picFormat.second);

                os.flush();
                socket->write(byteArray);
            }
            else if(picFormat.first == "mjpg") {
            }
        }
        else {
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/html; charset=\"utf-8\"\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "\r\n";

            os << htmlTemplate;
        }

        socket->close();
        if(socket->state() == QTcpSocket::UnconnectedState)
            delete socket;
    }
}
void InterfaceHttpServer::discardClient() {
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();
}

InterfaceHttp::~InterfaceHttp() {
    delete ui;
}
