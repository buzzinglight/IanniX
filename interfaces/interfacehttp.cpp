#include "interfacehttp.h"
#include "ui_interfacehttp.h"

InterfaceHttp::InterfaceHttp(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceHttp) {
    ui->setupUi(this);
    connect(ui->examples, SIGNAL(released()), SLOT(openExamples()));

    httpServer = new InterfaceHttpServer(this);
    connect(httpServer, SIGNAL(parseRequest(QNetworkReply*)), SLOT(parseRequest(QNetworkReply*)));
    connect(httpServer, SIGNAL(parseSocket(QTcpSocket*)),     SLOT(parseSocket(QTcpSocket*)));

    //Html template
    QFile htmlTemplateFile("Tools/HTML Template.html");
    if(htmlTemplateFile.open(QFile::ReadOnly)) {
        htmlTemplate = htmlTemplateFile.readAll();
        htmlTemplateFile.close();
    }

    //Interfaces link
    enable.setAction(ui->enable, "interfaceHttpEnable");
    port.setAction(ui->port,     "interfaceHttpPort");
    connect(&port, SIGNAL(triggered(qreal)), SLOT(portChanged()));
    port = 1236;
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
bool InterfaceHttpServer::portChanged(quint16 port) {
    //Initialization
    close();
    return listen(QHostAddress::Any, port);
}


bool InterfaceHttp::send(const Message & message) {
    if(!enable)
        return false;
    return httpServer->send(message);
}
bool InterfaceHttpServer::send(const Message & message) {
    //Send request
    http->get(QNetworkRequest(message.getUrlMessage()));

    //Log in console
    MessageManager::logSend(message);

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
        for(quint16 index = 0 ; index < url.queryItems().count() ; index++) {
            QString first = url.queryItems().at(index).first.toLower();
            if((first == "png") || (first == "jpg") || (first == "mjpg")) {
                isPic = true;
                picFormat.first  = first;
                picFormat.second = url.queryItems().at(index).second.toInt();
            }
            else if(first == "sync") {
                isSync = true;
            }
            else
                commands.append(url.queryItems().at(index).second);
        }
#endif

        QTextStream os(socket);
        if((commands.count() > 0) && (!isPic) && (!isSync)) {
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/plain; charset=\"utf-8\"\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "\r\n";

            QString response = "";
            foreach(const QString & command, commands)
                response += MessageManager::incomingMessage(MessageIncomming("http", socket->peerAddress().toString(), socket->peerPort(), url.path(), command, command.split(" ", QString::SkipEmptyParts)), true);
            os << response;
        }
        else if(isSync) {
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/plain; charset=\"utf-8\"\r\n"
                  "Access-Control-Allow-Origin: *\r\n"
                  "\r\n";

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
