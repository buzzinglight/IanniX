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

#include "messagemanager.h"
#include "objects/nxobject.h"

QList<MessageManagerLogInterface*>      MessageManager::logs;
Message                                 MessageManager::message;
QHash<QByteArray, Message>              MessageManager::messagesCache;
QHash<MessagesType, NetworkInterface*>  MessageManager::interfaces;
QHash<QString, UiString>                MessageManager::aliases;
MessageDispatcher*                      MessageManager::dispatcher        = 0;
MessageManagerLog*                      MessageManager::messageManagerLog = 0;
QScriptEngine*                          MessageManager::scriptEngine      = 0;
void*                                   MessageManager::transportObject   = 0;
void*                                   MessageManager::syncObject        = 0;
quint16 MessageManager::transportNbTriggers = 0;
quint16 MessageManager::transportNbCursors  = 0;
quint16 MessageManager::transportNbCurves   = 0;
quint16 MessageManager::transportNbGroups   = 0;

void MessageManager::setInterfaces(MessageDispatcher *_dispatcher, QScriptEngine *_scriptEngine, QLayout *logLayout, QLayout *logMiniLayout) {
    if(_dispatcher)
        dispatcher   = _dispatcher;
    if(_scriptEngine)
        scriptEngine = _scriptEngine;
    if(logLayout) {
        messageManagerLog = new MessageManagerLog(logLayout);
        logs.append(messageManagerLog);
    }
    if(logMiniLayout)
        logs.append(new MessageManagerLogMini(logMiniLayout));
}

void MessageManager::addNetworkInterface(MessagesType type, NetworkInterface *networkInterface) {
    if(networkInterface)
        interfaces.insert(type, networkInterface);
}
void MessageManager::deleteNetworkInterface() {
    foreach(NetworkInterface *networkInterface, interfaces)
        networkInterface->clear();
    interfaces.clear();
}

void MessageManager::networkBundle(bool open) {
    foreach(NetworkInterface *networkInterface, interfaces)
        networkInterface->networkBundle(open);
}
void MessageManager::networkManualParsing() {
    foreach(NetworkInterface *networkInterface, interfaces)
        networkInterface->networkManualParsing();
}
void MessageManager::networkSynchro(bool start) {
    foreach(NetworkInterface *networkInterface, interfaces) {
        if(networkInterface != Application::synchroLoopGuard)
            networkInterface->networkSynchro(start);
    }
}

void MessageManager::logSend(const MessageLog &message, QStringList *sentMessage) {
    foreach(MessageManagerLogInterface *log, logs)
        log->logSend(message, sentMessage);
}
void MessageManager::logReceive(const MessageLog &message, QStringList *sentMessage) {
    foreach(MessageManagerLogInterface *log, logs)
        log->logReceive(message, sentMessage);
}
void MessageManager::logInfo(const QString &message) {
    foreach(MessageManagerLogInterface *log, logs)
        log->logInfo(message);
}
QString MessageManager::incomingMessage(const MessageIncomming &source, bool needOutput, bool needToScript) {
    if(needToScript) {
        foreach(MessageManagerLogInterface *log, logs)
            log->logReceive(source);
    }
    if(dispatcher)
        return dispatcher->incomingMessage(source, needOutput, needToScript);
    return QString();
}

void MessageManager::outgoingMessage(const MessageManagerDestination &destination) {
    if((destination.object) && (Application::current->hasStarted)) {
        QStringList sentMessages;
        foreach(const QVector<QByteArray> &messagePattern, ((NxObject*)destination.object)->getMessagePatterns()) {
            if(messagesCache.contains(messagePattern.at(0)))
                message = messagesCache.value(messagePattern.at(0));
            else {
                message.setUrl(messagePattern.at(0), scriptEngine, aliases);
                messagesCache.insert(messagePattern.at(0), message);
            }
            if(message.parse(messagePattern, destination)) {
                if(((NxObject*)destination.object)->getSelectedHover())
                    interfaces[message.getType()]->send(message, &sentMessages);
                else
                    interfaces[message.getType()]->send(message);
            }
        }
        if((((NxObject*)destination.object)->getSelectedHover()) && (sentMessages.count()))
            ((NxObject*)destination.object)->setMessageLabel(sentMessages);
    }
}
