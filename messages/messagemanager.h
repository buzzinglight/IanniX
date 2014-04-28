/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

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

#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "messages/message.h"
#include "messagemanagerlog.h"
#include "messagemanagerlogmini.h"

class MessageManager : public QObject {
    Q_OBJECT

public:
    static void *transportObject, *syncObject;
    static quint16 transportNbTriggers, transportNbCursors, transportNbCurves, transportNbGroups;
    static QList<MessageManagerLogInterface*> logs;
    static MessageDispatcher *dispatcher;
    static QHash<QByteArray, Message> messagesCache;
    static Message message;
    static QHash<MessagesType, NetworkInterface*> interfaces;
    static QHash<QString, UiString> aliases;
    static QScriptEngine *scriptEngine;
private:
    static MessageManagerLog* messageManagerLog;

public:
    static void setInterfaces(MessageDispatcher *_dispatcher = 0, QScriptEngine *_scriptEngine = 0, QLayout *logWidget = 0, QLayout *logMiniWidget = 0);
    static void addNetworkInterface(MessagesType type, NetworkInterface *networkInterface);
    static void deleteNetworkInterface();
    static inline void setLogVisibility(bool logVisible) {
        if(messageManagerLog) messageManagerLog->logEnable = logVisible;
    }

public:
    static void networkManualParsing();
    static void networkBundle(bool open);
    static void networkSynchro(bool start);

public:
    static void logSend   (const MessageLog &message, QStringList *sentMessage = 0);
    static void logReceive(const MessageLog &message, QStringList *sentMessage = 0);
    static void logInfo   (const QString &message);
    static QString incomingMessage(const MessageIncomming &source, bool needOutput = false, bool needToScript = true);
    static void outgoingMessage(const MessageManagerDestination &destination);

signals:
    
public slots:
    
};

#endif // MESSAGEMANAGER_H
