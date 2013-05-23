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
    bool send(const Message & );
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
    UiReal port;
    UiBool enable;
    QString htmlTemplate;
private slots:
    void portChanged();
    void parseRequest(QNetworkReply*);
    void parseSocket(QTcpSocket*);
    void openExamples() {
        QDesktopServices::openUrl(QUrl("http://127.0.0.1:" + QString::number(port) + "/", QUrl::TolerantMode));
    }

public:
    bool send(const Message & message);

private:
    Ui::InterfaceHttp *ui;
};

#endif // INTERFACEHTTP_H
