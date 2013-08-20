#ifndef INTERFACEHTTP_H
#define INTERFACEHTTP_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QTcpServer>
#include <QDir>
#include <QBuffer>
#include <QApplication>
#include "misc/options.h"
#include "messages/messagemanager.h"
#include "qwebsockets/websocketserver.h"
#include "qwebsockets/websocket.h"


namespace Ui {
class InterfaceHttp;
}

class InterfaceHttpServer : public QTcpServer {
    Q_OBJECT

public:
    InterfaceHttpServer(QObject *parent);

private:
    QNetworkAccessManager *http;

public:
    bool send(const Message &message, QStringList *messageSent = 0);
public:
    bool portChanged(quint16 port);
protected:
    void incomingConnection(int socketDescriptor);
private slots:
    void readClient();
    void discardClient();
    void parse(QNetworkReply*);
signals:
    void parseRequest(QNetworkReply*);
    void parseSocket(QTcpSocket*);
};



class InterfaceHttp : public NetworkInterface {
    Q_OBJECT
    
public:
    explicit InterfaceHttp(QWidget *parent = 0);
    ~InterfaceHttp();

private:
    InterfaceHttpServer *httpServer;
private slots:
    void portChanged();
    void parseRequest(QNetworkReply*);
    void parseSocket(QTcpSocket*);

private:
    WebSocketServer*  webSocketServer;
    QList<WebSocket*> webSocketClients;
private slots:
    void portWebSocketsChanged();
    void webSocketsNewConnection();
    void webSocketsProcessMessage(const QString &message);
    void webSocketsProcessBinaryMessage(const QByteArray &message);
    void webSocketsSocketDisconnected();
    void webSocketsUpdateConnectedClients();


private:
    UiReal port, webSocketsPort;
    UiBool enable;
    QString htmlTemplate;
private slots:
    void openExamples() {
        QDesktopServices::openUrl(QUrl("http://127.0.0.1:" + QString::number(port) + "/"));
    }


public:
    bool send(const Message &message, QStringList *messageSent = 0);


private:
    Ui::InterfaceHttp *ui;
};

#endif // INTERFACEHTTP_H
