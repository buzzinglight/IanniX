#ifndef MESSAGEMANAGERLOGINTERFACE_H
#define MESSAGEMANAGERLOGINTERFACE_H

#include <QObject>
#include <QVariant>
#include <QWidget>
#include "transport/transport.h"
#include "misc/application.h"
#include "geometry/nxpoint.h"
#include "iannix_cmd.h"

enum MessagesType     { MessagesTypeDirect, MessagesTypeOsc, MessagesTypeUdp, MessagesTypeTcp, MessagesTypeSyphon, MessagesTypeHttp, MessagesTypeSerial, MessagesTypeMidi };

class MessageLog {
private:
    QByteArray message;
public:
    explicit MessageLog() { }
    explicit MessageLog(const QString &_message) { message = qPrintable(_message);  }
    virtual const QByteArray getVerboseMessage() const { return message; }
};

class MessageManagerLogInterface {
public:
    virtual void logSend   (const MessageLog &, bool = false) {}
    virtual void logReceive(const MessageLog &, bool = false) {}
    virtual void logInfo   (const QString &)                  {}
};


class MessageIncomming : public MessageLog {
public:
    QString protocol, host;
    QVariant port;
    QString command, destination;
    QStringList arguments;

public:
    explicit MessageIncomming(const QString &_protocol, const QString &_host, const QVariant &_port, const QString &_destination, const QString &_command, const QStringList &_arguments) {
        protocol    = _protocol;
        host        = _host;
        port        = _port;
        command     = _command;
        destination = _destination;
        arguments   = _arguments;
    }

    const QByteArray getVerboseMessage() const {
        return qPrintable(QString("%1://%2:%3 %4").arg(protocol).arg(host).arg(port.toString()).arg(command));
    }
};

class NxCursorAbstraction {
public:
    virtual void* getCurveVoid() const = 0;
};
class MessageManagerDestination {
public:
    NxPoint collisionPoint, collisionValue;
    TransportStatus status;
    void *object;
    void *trigger;
    void *cursor;
    void *collisionCurve;
    void *curve;

public:
    explicit MessageManagerDestination(void *_object = 0, void *_trigger = 0, void *_cursor = 0, void *_collisionCurve = 0, const NxPoint &_collisionPoint = NxPoint(), const NxPoint &_collisionValue = NxPoint(), const TransportStatus &_status = TransportStatus()) {
        object            = _object;
        trigger           = _trigger;
        cursor            = _cursor;
        collisionCurve    = _collisionCurve;
        if(cursor)  curve = ((NxCursorAbstraction*)cursor)->getCurveVoid();
        else        curve = 0;
        collisionPoint    = _collisionPoint;
        collisionValue    = _collisionValue;
        status            = _status;
    }
};

class MessageDispatcher {
public:
    virtual QString incomingMessage(const MessageIncomming &source, bool needOutput = false) = 0;
};

/*
class MessageParser {
public:
    virtual void setUrl(const QUrl & url, QScriptEngine *_messageScriptEngine) = 0;
    virtual bool parse(const QVector<QByteArray> & patternItems, const MessageManagerDestination &destination) = 0;
};
*/

class Message;
class NetworkInterface : public QWidget {
public:
    QString ihmFeedbackNok, ihmFeedbackOk;
public:
    NetworkInterface(QWidget *parent = 0) : QWidget(parent) {
        ihmFeedbackOk  = "QAbstractSpinBox, QPlainTextEdit {background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));}";
        ihmFeedbackNok = "QAbstractSpinBox, QPlainTextEdit {background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));}";
    }
public:
    virtual bool send(const Message &)                  { return false; }
    virtual inline void networkBundle(bool)             {}
    virtual inline void networkManualParsing()          {}
    virtual inline void networkSynchro(bool)            {}
    virtual inline void networkSynchro(const QString &) {}
};



#endif // MESSAGEMANAGERLOGINTERFACE_H
