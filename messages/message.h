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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <qmath.h>
#include <QScriptEngine>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QStringList>
#include "messages/messagemanagerloginterface.h"
#include "misc/application.h"

class Message : public MessageLog {
private:
    QByteArray      arguments, typetag, address, buffer;
    QString         midiCommand, midiPort;
    QUrl            urlMessage;
    QByteArray      urlMessageString;
    QByteArray      asciiMessage;
private:
    bool            hasAdd, isTransportMessage;
    QScriptValue    messageScriptValue, messageScriptResult;
private:
    QHostAddress    host;
    quint16         port;
    MessagesType    type;
    QList<qreal>    midiValues;
    QList<QVariant> verboseValues;
    QScriptEngine  *messageScriptEngine;

public:
    Message();
public:
    void setUrl(const QUrl & url, QScriptEngine *_messageScriptEngine, const QHash<QString, UiString> &aliases);
    bool parse(const QVector<QByteArray> & patternItems, const MessageManagerDestination &destination);
    
private:
    bool addString(QString str, const QString & name, quint16);
    bool addFloat(float f, const QString & name, quint16);
    bool addTimeTag(qint64 t, const QString & name, quint16);
private:
    qint64 generateTimeTag() const;
    inline void pad(QByteArray & b) const {
        while (b.size() % 4 != 0)
            b += (char)0;
    }
    
public:
    inline       MessagesType   getType()         const {   return type;                }
    
    inline const bool           isTransport()     const {   return isTransportMessage;  }
    inline const QByteArray &   getBuffer()       const {   return buffer;              }
    inline const QHostAddress & getHost()         const {   return host;                }
    inline       quint16        getPort()         const {   return port;                }
    
    inline const QString &      getMidiCommand()  const {   return midiCommand;         }
    inline const QString &      getMidiPort()     const {   return midiPort;            }
    inline const QByteArray &   getAsciiMessage() const {   return asciiMessage;        }
    inline const QByteArray &   getAddress()      const {   return address;             }
    inline const QUrl &         getUrlMessage()   const {   return urlMessage;          }

    const QByteArray getVerboseMessage(bool withDestination=false) const;
    inline qreal getMidiValue(quint8 index) const {
        if(index < midiValues.count())  return midiValues.at(index);
        else                            return 0;
    }
    inline void setMidiValue(quint8 index, qreal value, const QString &extraInfo = "") {
        if(index < midiValues.count()) {
            if(extraInfo.isEmpty()) verboseValues[index] = value;
            else                    verboseValues[index] = QString("%1 (%2)").arg(value).arg(extraInfo);
            midiValues[index]    = value;
        }
    }
};




#endif // MESSAGE_H
