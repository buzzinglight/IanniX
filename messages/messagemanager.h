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
    static void addNetworkInterface(MessagesType type, NetworkInterface *interface);
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
    static QString incomingMessage(const MessageIncomming &source, bool needOutput = false);
    static void outgoingMessage(const MessageManagerDestination &destination);

signals:
    
public slots:
    
};

#endif // MESSAGEMANAGER_H
