/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
        factory->logOscReceive(reply->url().toString() + " " + command);
        factory->execute(command);
        factory->onOscReceive("http", reply->url().host(), QString::number(reply->url().port()), reply->url().path(), command.split(" ", QString::SkipEmptyParts));
    }
}

void ExtHttpManager::parseService(const QUrl &url) {
    qDebug("%s", qPrintable(url.toString()));
}
