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
#include "nxdocument.h"
#include "nxobjectfactoryinterface.h"

enum MessagesType     { MessagesTypeNo, MessagesTypeDirect, MessagesTypeOsc, MessagesTypeUdp, MessagesTypeTcp, MessagesTypeHttp, MessagesTypeSerial, MessagesTypeMidi, MessagesTypeMouse, MessagesTypeTablet };

class ExtMessage {
private:
    QByteArray arguments, typetag, address, buffer;
    QByteArray verboseMessage, asciiMessage, conversionTemp;
    QString midiCommand, midiPort;
    QUrl urlMessage;
    QString urlMessageString;
    QHostAddress host;
    quint16 port;
    MessagesType type;
    QList<quint16> midiValues;
    QScriptEngine *messageScriptEngine;
    QScriptValue messageScriptValue, messageScriptResult;
    bool hasAdd;
public:
    ExtMessage() {
        type = MessagesTypeNo;
        hasAdd = false;
        messageScriptEngine = 0;
    }
    
    inline void setUrl(const QUrl & url, QScriptEngine *_messageScriptEngine) {
        messageScriptEngine = _messageScriptEngine;
        messageScriptValue = messageScriptEngine->globalObject();
        hasAdd = false;
        urlMessage = url;
        urlMessageString = urlMessage.toString();
        address.clear();
        typetag.clear();
        arguments.clear();
        asciiMessage.clear();
        
        if(urlMessage.scheme().toLower() == "osc") {
            type = MessagesTypeOsc;
            host = urlMessage.host().toLower();
            port = urlMessage.port();
            address += urlMessage.path();
            address += (char)0;
            pad(address);
            typetag += ',';
        }
        else if(urlMessage.scheme().toLower() == "http") {
            type = MessagesTypeHttp;
        }
        else if(urlMessage.scheme().toLower() == "tcp") {
            type = MessagesTypeTcp;
        }
        else if(urlMessage.scheme().toLower() == "udp") {
            type = MessagesTypeUdp;
            host = urlMessage.host();
            port = urlMessage.port();
        }
        else if(urlMessage.scheme().toLower() == "serial") {
            type = MessagesTypeSerial;
        }
        else if(urlMessage.scheme().toLower() == "direct") {
            type = MessagesTypeDirect;
        }
        else if(urlMessage.scheme().toLower() == "midi") {
            type = MessagesTypeMidi;
            midiPort = urlMessage.host().toLower();
            midiCommand = urlMessage.path().toLower();
        }
        else if(urlMessage.scheme().toLower() == "mouse") {
            type = MessagesTypeMouse;
        }
        else if(urlMessage.scheme().toLower() == "tablet") {
            type = MessagesTypeTablet;
        }
    }
    
    bool parse(const QVector<QByteArray> & patternItems, NxTrigger *trigger, NxCursor *cursor, NxCurve *curve, NxCurve *collisionCurve, const NxPoint & collisionPoint, const NxPoint & collisionValue, const QString & status, const quint16 nbTriggers, const quint16 nbCursors, const quint16 nbCurves) {
        bool suppressSend = false;
        verboseMessage = qPrintable(urlMessageString);
        midiValues.clear();
        asciiMessage = "";
        buffer.clear();
        hasAdd = false;
        
        if(patternItems.count() >= 2) {
            //Messages
            for(quint16 patternIndex = 1 ; patternIndex < patternItems.count() ; patternIndex++) {
                QString patternArgument = patternItems.at(patternIndex);
                bool found = false;
                
                if((patternArgument.at(0) == '{') && (messageScriptEngine)) {
                    patternArgument = patternArgument.trimmed().remove(0, 1);
                    patternArgument.chop(1);

                    if(trigger) {
                        if(patternArgument.contains("trigger_id"))
                            messageScriptValue.setProperty("trigger_id", trigger->getId());
                        if(patternArgument.contains("trigger_group_id"))
                            messageScriptValue.setProperty("trigger_group_id", trigger->getGroupId());
                        if(patternArgument.contains("trigger_document_id"))
                            messageScriptValue.setProperty("trigger_document_id", trigger->getDocumentId());
                        if(patternArgument.contains("trigger_xPos"))
                            messageScriptValue.setProperty("trigger_xPos", trigger->getPos().x());
                        if(patternArgument.contains("trigger_yPos"))
                            messageScriptValue.setProperty("trigger_yPos", trigger->getPos().y());
                        if(patternArgument.contains("trigger_zPos"))
                            messageScriptValue.setProperty("trigger_zPos", trigger->getPos().z());
                        if(patternArgument.contains("trigger_value"))
                            messageScriptValue.setProperty("trigger_value", trigger->getTrigged());
                        if(patternArgument.contains("trigger_distance")) {
                            NxPoint cursorPosDelta = trigger->getPos() - cursor->getCurrentPos();
                            messageScriptValue.setProperty("trigger_distance", qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()));
                        }
                        if(patternArgument.contains("trigger_side")) {
                            qreal cursorAngle = fmod(cursor->getCurrentAngle(),360);
                            float side = 0;
                            if (cursorAngle == 90 ) //cursor going straight up
                                side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 1:0;
                            else if (cursorAngle == 270) //cursor going straight down
                                side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 0:1;
                            else if(((0<cursorAngle) && (cursorAngle<90)) || ((270<cursorAngle) && (cursorAngle<360)) ) //cursor going to left
                                side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 1:0;
                            else //cursor going to right
                                side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 0:1;
                            messageScriptValue.setProperty("trigger_side", side);
                        }
                        if(patternArgument.contains("trigger_message_id"))
                            messageScriptValue.setProperty("trigger_message_id", (quint32)trigger->getMessageId());
                    }
                    if(cursor) {
                        if(patternArgument.contains("cursor_id")) {
                            messageScriptValue.setProperty("cursor_id", cursor->getId());
                            //qDebug("%d", tat);
                        }
                        if(patternArgument.contains("cursor_group_id"))
                            messageScriptValue.setProperty("cursor_group_id", cursor->getGroupId());
                        if(patternArgument.contains("cursor_document_id"))
                            messageScriptValue.setProperty("cursor_document_id", cursor->getDocumentId());
                        if(patternArgument.contains("cursor_xPos"))
                            messageScriptValue.setProperty("cursor_xPos", cursor->getCurrentPos().x());
                        if(patternArgument.contains("cursor_yPos"))
                            messageScriptValue.setProperty("cursor_yPos", cursor->getCurrentPos().y());
                        if(patternArgument.contains("cursor_zPos"))
                            messageScriptValue.setProperty("cursor_zPos", cursor->getCurrentPos().z());
                        if(patternArgument.contains("cursor_sxPos"))
                            messageScriptValue.setProperty("cursor_sxPos", cursor->getCurrentPos().sx());
                        if(patternArgument.contains("cursor_syPos"))
                            messageScriptValue.setProperty("cursor_syPos", cursor->getCurrentPos().sy());
                        if(patternArgument.contains("cursor_szPos"))
                            messageScriptValue.setProperty("cursor_szPos", cursor->getCurrentPos().sz());
                        if(patternArgument.contains("cursor_value_x"))
                            messageScriptValue.setProperty("cursor_value_x", cursor->getCurrentValue().x());
                        if(patternArgument.contains("cursor_value_y"))
                            messageScriptValue.setProperty("cursor_value_y", cursor->getCurrentValue().y());
                        if(patternArgument.contains("cursor_value_z"))
                            messageScriptValue.setProperty("cursor_value_z", cursor->getCurrentValue().z());
                        if(patternArgument.contains("cursor_value_sx"))
                            messageScriptValue.setProperty("cursor_value_sx", cursor->getCurrentValue().sx());
                        if(patternArgument.contains("cursor_value_sy"))
                            messageScriptValue.setProperty("cursor_value_sy", cursor->getCurrentValue().sy());
                        if(patternArgument.contains("cursor_value_sz"))
                            messageScriptValue.setProperty("cursor_value_sz", cursor->getCurrentValue().sz());
                        if(patternArgument.contains("cursor_time"))
                            messageScriptValue.setProperty("cursor_time", cursor->getCurrentPosition());
                        if(patternArgument.contains("cursor_time_percent"))
                            messageScriptValue.setProperty("cursor_time_percent", cursor->getCurrentPositionPercent());
                        if(patternArgument.contains("cursor_angle"))
                            messageScriptValue.setProperty("cursor_angle", fmod(cursor->getCurrentAngle(),360));
                        if(patternArgument.contains("cursor_nb_loop"))
                            messageScriptValue.setProperty("cursor_nb_loop", cursor->getNbLoop());
                        if(patternArgument.contains("cursor_message_id"))
                            messageScriptValue.setProperty("cursor_message_id", (quint32)cursor->getMessageId());
                    }
                    if(curve) {
                        if(patternArgument.contains("curve_id"))
                            messageScriptValue.setProperty("curve_id", curve->getId());
                        if(patternArgument.contains("curve_group_id"))
                            messageScriptValue.setProperty("curve_group_id", curve->getGroupId());
                        if(patternArgument.contains("curve_document_id"))
                            messageScriptValue.setProperty("curve_document_id", curve->getDocumentId());
                        if(patternArgument.contains("curve_xPos"))
                            messageScriptValue.setProperty("curve_xPos", curve->getPos().x());
                        if(patternArgument.contains("curve_yPos"))
                            messageScriptValue.setProperty("curve_yPos", curve->getPos().y());
                        if(patternArgument.contains("curve_zPos"))
                            messageScriptValue.setProperty("curve_zPos", curve->getPos().z());
                    }
                    if(collisionCurve) {
                        if(patternArgument.contains("collision_curve_id"))
                            messageScriptValue.setProperty("collision_curve_id", collisionCurve->getId());
                        if(patternArgument.contains("collision_xPos"))
                            messageScriptValue.setProperty("collision_xPos", collisionPoint.x());
                        if(patternArgument.contains("collision_yPos"))
                            messageScriptValue.setProperty("collision_yPos", collisionPoint.y());
                        if(patternArgument.contains("collision_value_x"))
                            messageScriptValue.setProperty("collision_value_x", collisionValue.x());
                        if(patternArgument.contains("collision_value_y"))
                            messageScriptValue.setProperty("collision_value_y", collisionValue.y());
                        if(patternArgument.contains("collision_distance")) {
                            NxPoint cursorPosDelta = collisionPoint - cursor->getCurrentPos();
                            messageScriptValue.setProperty("collision_distance", qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()));
                        }
                    }
                    {
                        if(patternArgument.contains("status"))
                            messageScriptValue.setProperty("status", status);

                        if(patternArgument.contains("nb_triggers"))
                            messageScriptValue.setProperty("nb_triggers", nbTriggers);
                        if(patternArgument.contains("nb_cursors"))
                            messageScriptValue.setProperty("nb_cursors", nbCursors);
                        if(patternArgument.contains("nb_curves"))
                            messageScriptValue.setProperty("nb_curves", nbCurves);
                    }

                    messageScriptResult = messageScriptEngine->evaluate(patternArgument);
                    if(messageScriptResult.isError())
                        addString("**error**", patternArgument, patternIndex);
                    else if(messageScriptResult.isString()) {
                        if(messageScriptResult.toString() == "suppress")
                            suppressSend = true;
                        else
                            found = addString(messageScriptResult.toString(), QString("script %1").arg(patternIndex), patternIndex);
                    }
                    else
                        found = addFloat(messageScriptResult.toNumber(), QString("script %1").arg(patternIndex), patternIndex);


                }
                else {
                    if(trigger) {
                        if(patternArgument == "trigger_id")
                            found = addFloat(trigger->getId(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_group_id")
                            found = addString(trigger->getGroupId(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_document_id")
                            found = addString(trigger->getDocumentId(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_xPos")
                            found = addFloat(trigger->getPos().x(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_yPos")
                            found = addFloat(trigger->getPos().y(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_zPos")
                            found = addFloat(trigger->getPos().z(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_value")
                            found = addFloat(trigger->getTrigged(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_distance") {
                            NxPoint cursorPosDelta = trigger->getPos() - cursor->getCurrentPos();
                            found = addFloat(qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()), patternArgument, patternIndex);
                        }
                        else if(patternArgument == "trigger_message_id")
                            found = addFloat(trigger->getMessageId(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_side") {
                            qreal cursorAngle = fmod(cursor->getCurrentAngle(),360);
                            float side = 0;
                            if (cursorAngle == 90 ) //cursor going straight up
                                side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 1:0;
                            else if (cursorAngle == 270) //cursor going straight down
                                side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 0:1;
                            else if(((0<cursorAngle) && (cursorAngle<90)) || ((270<cursorAngle) && (cursorAngle<360)) ) //cursor going to left
                                side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 1:0;
                            else //cursor going to right
                                side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 0:1;
                            found = addFloat(side, patternArgument, patternIndex);
                        }
                    }
                    if(cursor) {
                        if(patternArgument == "cursor_id")
                            found = addFloat(cursor->getId(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_group_id")
                            found = addString(cursor->getGroupId(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_document_id")
                            found = addString(cursor->getDocumentId(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_xPos")
                            found = addFloat(cursor->getCurrentPos().x(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_yPos")
                            found = addFloat(cursor->getCurrentPos().y(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_zPos")
                            found = addFloat(cursor->getCurrentPos().z(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_sxPos")
                            found = addFloat(cursor->getCurrentPos().sx(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_syPos")
                            found = addFloat(cursor->getCurrentPos().sy(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_szPos")
                            found = addFloat(cursor->getCurrentPos().sz(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_value_x")
                            found = addFloat(cursor->getCurrentValue().x(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_value_y")
                            found = addFloat(cursor->getCurrentValue().y(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_value_z")
                            found = addFloat(cursor->getCurrentValue().z(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_value_sx")
                            found = addFloat(cursor->getCurrentValue().sx(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_value_sy")
                            found = addFloat(cursor->getCurrentValue().sy(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_value_sz")
                            found = addFloat(cursor->getCurrentValue().sz(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_time")
                            found = addFloat(cursor->getCurrentPosition(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_time_percent")
                            found = addFloat(cursor->getCurrentPositionPercent(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_angle")
                            found = addFloat(fmod(cursor->getCurrentAngle(),360), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_nb_loop")
                            found = addFloat(cursor->getNbLoop(), patternArgument, patternIndex);
                        else if(patternArgument == "cursor_message_id")
                            found = addFloat(cursor->getMessageId(), patternArgument, patternIndex);
                    }
                    if(curve) {
                        if(patternArgument == "curve_id")
                            found = addFloat(curve->getId(), patternArgument, patternIndex);
                        else if(patternArgument == "curve_group_id")
                            found = addString(curve->getGroupId(), patternArgument, patternIndex);
                        else if(patternArgument == "curve_document_id")
                            found = addString(curve->getDocumentId(), patternArgument, patternIndex);
                        else if(patternArgument == "curve_xPos")
                            found = addFloat(curve->getPos().x(), patternArgument, patternIndex);
                        else if(patternArgument == "curve_yPos")
                            found = addFloat(curve->getPos().y(), patternArgument, patternIndex);
                        else if(patternArgument == "curve_zPos")
                            found = addFloat(curve->getPos().z(), patternArgument, patternIndex);
                    }
                    if(collisionCurve) {
                        if(patternArgument == "collision_curve_id")
                            found = addFloat(collisionCurve->getId(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_xPos")
                            found = addFloat(collisionPoint.x(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_yPos")
                            found = addFloat(collisionPoint.y(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_value_x")
                            found = addFloat(collisionValue.x(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_value_y")
                            found = addFloat(collisionValue.y(), patternArgument, patternIndex);
                        else if((patternArgument == "collision_distance") && (cursor)) {
                            NxPoint cursorPosDelta = collisionPoint - cursor->getCurrentPos();
                            found = addFloat(qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()), patternArgument, patternIndex);
                        }
                    }
                    else {
                        if(patternArgument == "status")
                            found = addString(status, patternArgument, patternIndex);
                        else if(patternArgument == "nb_triggers")
                            found = addFloat(nbTriggers, patternArgument, patternIndex);
                        else if(patternArgument == "nb_cursors")
                            found = addFloat(nbCursors, patternArgument, patternIndex);
                        else if(patternArgument == "nb_curves")
                            found = addFloat(nbCurves, patternArgument, patternIndex);
                    }
                }
                
                if(!found) {
                    if(patternArgument.startsWith("collision_"))
                        suppressSend = true;
                    else {
                        //If value is not a keyword, add raw value
                        bool ok = false;
                        qreal val = patternArgument.toDouble(&ok);
                        if(ok)
                            found = addFloat(val, QString("custom %1").arg(patternIndex), patternIndex);
                        else
                            found = addString(qPrintable(patternArgument), QString("custom %1").arg(patternIndex), patternIndex);
                    }
                }
            }

            
            if(type == MessagesTypeHttp)
                verboseMessage = qPrintable(urlMessage.toString());
            else if(type == MessagesTypeOsc) {
                buffer += address;
                buffer += typetag;
                buffer += (char)0;
                pad(buffer);
                buffer += arguments;
            }
            else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect) || (type == MessagesTypeMouse) || (type == MessagesTypeTablet)) {
                asciiMessage = asciiMessage.trimmed();
            }
        }
        
        return (hasAdd && !suppressSend);
    }
    
private:
    /*
    inline void addInt(int i, const char *name, quint16) {
            union { int i; char ch[4]; } u;
            u.i = i;
            arguments += u.ch[3];
            arguments += u.ch[2];
            arguments += u.ch[1];
            arguments += u.ch[0];
            typetag += 'i';
    }
    */
    inline bool addString(QString str, const QString & name, quint16) {
        str = str.replace("_", " ");
        verboseMessage = verboseMessage + " " + qPrintable(str);
        hasAdd = true;
        if(type == MessagesTypeOsc) {
            arguments += str;
            arguments += (char)0;
            pad(arguments);
            typetag += 's';
            return true;
        }
        else if(type == MessagesTypeHttp) {
            urlMessage.addQueryItem(name, str);
            return true;
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect) || (type == MessagesTypeMouse) || (type == MessagesTypeTablet)) {
            asciiMessage = asciiMessage + " " + qPrintable(str);
            return true;
        }
        return true;
    }
    inline bool addFloat(float f, const QString & name, quint16) {
        verboseMessage = verboseMessage + " " + conversionTemp.setNum(f);
        hasAdd = true;
        if(type == MessagesTypeOsc) {
            union { float f; char ch[4]; } u;
            u.f = f;
            arguments += u.ch[3];
            arguments += u.ch[2];
            arguments += u.ch[1];
            arguments += u.ch[0];
            typetag += 'f';
            return true;
        }
        else if(type == MessagesTypeHttp) {
            urlMessage.addQueryItem(name, QString().setNum(f));
            return true;
        }
        else if(type == MessagesTypeMidi) {
            midiValues.append(f);
            return true;
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect) || (type == MessagesTypeMouse) || (type == MessagesTypeTablet)) {
            asciiMessage = asciiMessage + " " + conversionTemp.setNum(f);
            return true;
        }
        return true;
    }
    inline void pad(QByteArray & b) const {
        while (b.size() % 4 != 0)
            b += (char)0;
    }
    
public:
    inline MessagesType getType() const {
        return type;
    }
    
    inline const QByteArray & getBuffer() const {
        return buffer;
    }
    inline const QHostAddress & getHost() const {
        return host;
    }
    inline quint16 getPort() const {
        return port;
    }
    
    
    inline const QString & getMidiCommand() const {
        return midiCommand;
    }
    inline const QString & getMidiPort() const {
        return midiPort;
    }
    inline quint16 getMidiValue(quint8 index) const {
        if(index < midiValues.count())
            return midiValues.at(index);
        else
            return 0;
    }
    
    inline const QUrl & getUrlMessage() const {
        return urlMessage;
    }
    
    inline const QByteArray & getVerboseMessage() const {
        return verboseMessage;
    }
    inline const QByteArray & getAsciiMessage() const {
        return asciiMessage;
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
