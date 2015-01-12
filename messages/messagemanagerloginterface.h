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
    virtual const QByteArray getVerboseMessage(bool=false) const { return message; }
};

class MessageManagerLogInterface {
public:
    virtual void logSend   (const MessageLog &, QStringList* = 0) {}
    virtual void logReceive(const MessageLog &, QStringList* = 0) {}
    virtual void logInfo   (const QString &)                      {}
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

    const QByteArray getVerboseMessage(bool withDestination = false) const {
        QString portStr = port.toString();
        QString retour = protocol + "://";
        if(!host   .isEmpty()) retour += host;
        if(!portStr.isEmpty()) retour += ":" + portStr;
        if(withDestination) {
            if(!destination.isEmpty())
                retour += "/" + destination;
            foreach(const QString &argument, arguments)
                retour += "\t" + argument;
        }
        else if(!command.isEmpty()) retour += "\t" + command;
        return qPrintable(retour);
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
    virtual QString incomingMessage(const MessageIncomming &source, bool needOutput = false, bool needToScript = true) = 0;
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
        ihmFeedbackOk  = "QAbstractSpinBox, QComboBox, QPlainTextEdit {background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));}";
        ihmFeedbackNok = "QAbstractSpinBox, QComboBox, QPlainTextEdit {background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));}";
    }
public:
    virtual void clear() {}
    virtual bool send(const Message &, QStringList* =0) { return false; }
    virtual inline void networkBundle(bool)             {}
    virtual inline void networkManualParsing()          {}
    virtual inline void networkSynchro(bool)            {}
    virtual inline void networkSynchro(const QString &) {}
};



#endif // MESSAGEMANAGERLOGINTERFACE_H
