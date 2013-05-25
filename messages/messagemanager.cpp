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

void MessageManager::addNetworkInterface(MessagesType type, NetworkInterface *interface) {
    if(interface)
        interfaces.insert(type, interface);
}

void MessageManager::networkBundle(bool open) {
    foreach(NetworkInterface *interface, interfaces)
        interface->networkBundle(open);
}
void MessageManager::networkManualParsing() {
    foreach(NetworkInterface *interface, interfaces)
        interface->networkManualParsing();
}
void MessageManager::networkSynchro(bool start) {
    foreach(NetworkInterface *interface, interfaces) {
        if(interface != Application::synchroLoopGuard)
            interface->networkSynchro(start);
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
    qDebug("%s", qPrintable(message));
    foreach(MessageManagerLogInterface *log, logs)
        log->logInfo(message);
}
QString MessageManager::incomingMessage(const MessageIncomming &source, bool needOutput) {
    foreach(MessageManagerLogInterface *log, logs)
        log->logReceive(source);
    if(dispatcher)
        return dispatcher->incomingMessage(source, needOutput);
    return QString();
}

void MessageManager::outgoingMessage(const MessageManagerDestination &destination) {
    if(destination.object) {
        QStringList sentMessages;
        foreach(const QVector<QByteArray> &messagePattern, ((NxObject*)destination.object)->getMessagePatterns()) {
            if(messagesCache.contains(messagePattern.at(0)))
                message = messagesCache.value(messagePattern.at(0));
            else {
                message.setUrl(QUrl(messagePattern.at(0), QUrl::TolerantMode), scriptEngine, aliases);
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
