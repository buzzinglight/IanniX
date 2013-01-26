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

#ifndef EXTMESSAGE_H
#define EXTMESSAGE_H

#include <qmath.h>
#include <QScriptEngine>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QStringList>
#include "objects/nxobjectfactoryinterface.h"
#include "objects/nxdocument.h"

enum MessagesType     { MessagesTypeNo, MessagesTypeDirect, MessagesTypeOsc, MessagesTypeUdp, MessagesTypeTcp, MessagesTypeHttp, MessagesTypeSerial, MessagesTypeMidi, MessagesTypeMouse, MessagesTypeTablet };

class ExtMessage {
private:
    QByteArray arguments, typetag, address, buffer;
    QByteArray verboseMessage, asciiMessage;
    QString midiCommand, midiPort;
    QUrl urlMessage;
    QByteArray urlMessageString;
    QHostAddress host;
    quint16 port;
    MessagesType type;
    QList<qreal> midiValues;
    QScriptEngine *messageScriptEngine;
    QScriptValue messageScriptValue, messageScriptResult;
    bool hasAdd;
public:
    ExtMessage();
    void setUrl(const QUrl & url, QScriptEngine *_messageScriptEngine, const QString &ipOut, const QString &midiOut);
    bool parse(const QVector<QByteArray> & patternItems, NxTrigger *trigger, NxCursor *cursor, NxCurve *curve, NxCurve *collisionCurve, const NxPoint & collisionPoint, const NxPoint & collisionValue, const QString & status, const quint16 nbTriggers, const quint16 nbCursors, const quint16 nbCurves, qreal globalTime, const QString &globalTimeVerbose);
    
private:
    qint64 getTimeTag() const;
    //void addInt(int i, const char *name, quint16);
    bool addString(QString str, const QString & name, quint16);
    bool addFloat(float f, const QString & name, quint16);
    bool addTimeTag(qint64 t, const QString & name, quint16);
    inline void pad(QByteArray & b) const {
        while (b.size() % 4 != 0)
            b += (char)0;
    }
    
public:
    inline MessagesType getType() const                 {   return type;            }
    
    inline const QByteArray & getBuffer() const         {   return buffer;          }
    inline const QHostAddress & getHost() const         {   return host;            }
    inline quint16 getPort() const                      {   return port;            }
    
    inline const QString & getMidiCommand() const       {   return midiCommand;     }
    inline const QString & getMidiPort() const          {   return midiPort;        }
    inline const QByteArray & getVerboseMessage() const {   return verboseMessage;  }
    inline const QByteArray & getAsciiMessage() const   {   return asciiMessage;    }
    inline const QByteArray & getAddress() const        {   return address;         }
    inline const QUrl & getUrlMessage() const           {   return urlMessage;      }

    inline qreal getMidiValue(quint8 index) const {
        if(index < midiValues.count())
            return midiValues.at(index);
        else
            return 0;
    }
};


class ExtMessageManager {
protected:
    NxObjectFactoryInterface *factory;
    
public:
    ExtMessageManager(NxObjectFactoryInterface *_factory) { factory = _factory; }
    virtual void send(const ExtMessage & message) = 0;
};





#endif // EXTMESSAGE_H
