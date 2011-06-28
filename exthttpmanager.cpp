#include "exthttpmanager.h"

ExtHttpManager::ExtHttpManager(NxObjectFactoryInterface *_factory)
    : QObject(_factory), ExtMessageManager(_factory) {
    //Initialization
    factory = _factory;

    //Manager
    http = new QNetworkAccessManager(this);
    connect(http, SIGNAL(finished(QNetworkReply*)), SLOT(parse(QNetworkReply*)));

    //Browsers
    QDesktopServices::setUrlHandler("iannix", this, "parseService");
}

void ExtHttpManager::send(const ExtMessage & message) {
    //Send request
    http->get(QNetworkRequest(message.getUrlMessage()));

    //Log in the OSC console
    factory->logOscSend(message.getVerboseMessage());
}

void ExtHttpManager::parse(QNetworkReply *reply) {
    QStringList commandItems = QString(reply->readAll()).split(COMMAND_END, QString::SkipEmptyParts);;
    foreach(const QString & command, commandItems) {
        //Fire events (log, message and script mapping)
        QString url = reply->url().toString() + " ";
        factory->logOscReceive(url + command);
        factory->execute(command);
        factory->onOscReceive(url + command);
    }
}

void ExtHttpManager::parseService(const QUrl &url) {
    qDebug("%s", qPrintable(url.toString()));
}
