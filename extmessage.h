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
    ExtMessage() {
        type = MessagesTypeNo;
        hasAdd = false;
        messageScriptEngine = 0;
    }
    
    inline void setUrl(const QUrl & url, QScriptEngine *_messageScriptEngine, const QString &ipOut, const QString &midiOut) {
        messageScriptEngine = _messageScriptEngine;
        messageScriptValue = messageScriptEngine->globalObject();
        hasAdd = false;
        urlMessage = url;

        QString scheme = urlMessage.scheme().toLower();

        if(urlMessage.host().toLower() == "ip_out")
            urlMessage.setHost(ipOut);
        else if(urlMessage.host().toLower() == "midi_out")
            urlMessage.setHost(midiOut);
        urlMessageString = qPrintable(urlMessage.toString());
        address.clear();
        typetag.clear();
        arguments.clear();
        asciiMessage.clear();
        
        if(scheme == "osc") {
            type = MessagesTypeOsc;
            host = urlMessage.host().toLower();
            port = urlMessage.port();
            address += urlMessage.path();
            address += (char)0;
            pad(address);
            typetag += ',';
        }
        else if(scheme == "http") {
            type = MessagesTypeHttp;
        }
        else if(scheme == "tcp") {
            type = MessagesTypeTcp;
            address += urlMessage.authority() + urlMessage.path();
        }
        else if(scheme == "udp") {
            type = MessagesTypeUdp;
            host = urlMessage.host();
            port = urlMessage.port();
        }
        else if(scheme == "serial") {
            type = MessagesTypeSerial;
        }
        else if(scheme == "direct") {
            type = MessagesTypeDirect;
        }
        else if(scheme == "midi") {
            type = MessagesTypeMidi;
            midiPort = urlMessage.host().toLower();
            midiCommand = urlMessage.path().toLower();
        }
        else if(scheme == "mouse") {
            type = MessagesTypeMouse;
        }
        else if(scheme == "tablet") {
            type = MessagesTypeTablet;
        }
    }
    
    bool parse(const QVector<QByteArray> & patternItems, NxTrigger *trigger, NxCursor *cursor, NxCurve *curve, NxCurve *collisionCurve, const NxPoint & collisionPoint, const NxPoint & collisionValue, const QString & status, const quint16 nbTriggers, const quint16 nbCursors, const quint16 nbCurves, qreal globalTime, const QString &globalTimeVerbose) {
        bool suppressSend = false;
        verboseMessage = urlMessageString;
        midiValues.clear();
        asciiMessage.clear();
        buffer.clear();
        hasAdd = false;
        
        if(patternItems.count() >= 2) {
            //Messages
            for(quint16 patternIndex = 1 ; patternIndex < patternItems.count() ; patternIndex++) {
                QByteArray patternArgument = patternItems.at(patternIndex);
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
                        if(patternArgument.contains("trigger_label"))
                            messageScriptValue.setProperty("trigger_label", trigger->getLabel());
                        if(patternArgument.contains("trigger_xPos"))
                            messageScriptValue.setProperty("trigger_xPos", trigger->getPos().x());
                        if(patternArgument.contains("trigger_yPos"))
                            messageScriptValue.setProperty("trigger_yPos", trigger->getPos().y());
                        if(patternArgument.contains("trigger_zPos"))
                            messageScriptValue.setProperty("trigger_zPos", trigger->getPos().z());
                        if(patternArgument.contains("trigger_value_x"))
                            messageScriptValue.setProperty("trigger_value_x", (cursor)?(cursor->getCursorValue(trigger->getPos()).x()):(0));
                        if(patternArgument.contains("trigger_value_y"))
                            messageScriptValue.setProperty("trigger_value_y", (cursor)?(cursor->getCursorValue(trigger->getPos()).y()):(0));
                        if(patternArgument.contains("trigger_value_z"))
                            messageScriptValue.setProperty("trigger_value_z", (cursor)?(cursor->getCursorValue(trigger->getPos()).z()):(0));
                        if(patternArgument.contains("trigger_value"))
                            messageScriptValue.setProperty("trigger_value", trigger->getTrigged());
                        if(patternArgument.contains("trigger_distance")) {
                            NxPoint cursorPosDelta = (cursor)?(trigger->getPos() - cursor->getCurrentPos()):(NxPoint());
                            messageScriptValue.setProperty("trigger_distance", qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()));
                        }
                        if(patternArgument.contains("trigger_side")) {
                            qreal cursorAngle = fmod((cursor)?(cursor->getCurrentAngle()):(0),360);
                            float side = 0;
                            if(cursor) {
                                if(cursorAngle == 90) //cursor going straight up
                                    side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 1:0;
                                else if (cursorAngle == 270) //cursor going straight down
                                    side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 0:1;
                                else if(((0<cursorAngle) && (cursorAngle<90)) || ((270<cursorAngle) && (cursorAngle<360)) ) //cursor going to left
                                    side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 1:0;
                                else //cursor going to right
                                    side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 0:1;
                            }
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
                        if(patternArgument.contains("cursor_label"))
                            messageScriptValue.setProperty("cursor_label", cursor->getLabel());
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
                        if(patternArgument.contains("curve_label"))
                            messageScriptValue.setProperty("curve_label", curve->getLabel());
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
                        if(patternArgument.contains("collision_curve_group_id"))
                            messageScriptValue.setProperty("collision_curve_group_id", collisionCurve->getGroupId());
                        if(patternArgument.contains("collision_curve_document_id"))
                            messageScriptValue.setProperty("collision_curve_document_id", collisionCurve->getDocumentId());
                        if(patternArgument.contains("collision_curve_label"))
                            messageScriptValue.setProperty("collision_curve_label", collisionCurve->getLabel());
                        if(patternArgument.contains("collision_curve_xPos"))
                            messageScriptValue.setProperty("collision_curve_xPos", collisionCurve->getPos().x());
                        if(patternArgument.contains("collision_curve_yPos"))
                            messageScriptValue.setProperty("collision_curve_yPos", collisionCurve->getPos().y());
                        if(patternArgument.contains("collision_curve_zPos"))
                            messageScriptValue.setProperty("collision_curve_zPos", collisionCurve->getPos().z());
                        if(patternArgument.contains("collision_xPos"))
                            messageScriptValue.setProperty("collision_xPos", collisionPoint.x());
                        if(patternArgument.contains("collision_yPos"))
                            messageScriptValue.setProperty("collision_yPos", collisionPoint.y());
                        if(patternArgument.contains("collision_value_x"))
                            messageScriptValue.setProperty("collision_value_x", collisionValue.x());
                        if(patternArgument.contains("collision_value_y"))
                            messageScriptValue.setProperty("collision_value_y", collisionValue.y());
                        if((patternArgument.contains("collision_distance")) && (cursor)) {
                            NxPoint cursorPosDelta = (cursor)?(collisionPoint - cursor->getCurrentPos()):(NxPoint());
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
                        if(patternArgument.contains("global_time"))
                            messageScriptValue.setProperty("global_time", globalTime);
                        if(patternArgument.contains("global_time_verbose"))
                            messageScriptValue.setProperty("global_time_verbose", globalTimeVerbose);
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
                        else if(patternArgument == "trigger_label")
                            found = addString(trigger->getLabel(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_xPos")
                            found = addFloat(trigger->getPos().x(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_yPos")
                            found = addFloat(trigger->getPos().y(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_zPos")
                            found = addFloat(trigger->getPos().z(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_value_x")
                            found = addFloat((cursor)?(cursor->getCursorValue(trigger->getPos()).x()):(0), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_value_y")
                            found = addFloat((cursor)?(cursor->getCursorValue(trigger->getPos()).y()):(0), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_value_z")
                            found = addFloat((cursor)?(cursor->getCursorValue(trigger->getPos()).z()):(0), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_value")
                            found = addFloat(trigger->getTrigged(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_distance") {
                            NxPoint cursorPosDelta = (cursor)?(trigger->getPos() - cursor->getCurrentPos()):(NxPoint());
                            found = addFloat(qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()), patternArgument, patternIndex);
                        }
                        else if(patternArgument == "trigger_message_id")
                            found = addFloat(trigger->getMessageId(), patternArgument, patternIndex);
                        else if(patternArgument == "trigger_side") {
                            qreal cursorAngle = fmod((cursor)?(cursor->getCurrentAngle()):(0),360);
                            float side = 0;
                            if(cursor) {
                                if(cursorAngle == 90 ) //cursor going straight up
                                    side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 1:0;
                                else if (cursorAngle == 270) //cursor going straight down
                                    side = (trigger->getPos().x() > cursor->getCurrentPos().x()) ? 0:1;
                                else if(((0<cursorAngle) && (cursorAngle<90)) || ((270<cursorAngle) && (cursorAngle<360)) ) //cursor going to left
                                    side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 1:0;
                                else //cursor going to right
                                    side = (trigger->getPos().y() > cursor->getCurrentPos().y()) ? 0:1;
                            }
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
                        else if(patternArgument == "cursor_label")
                            found = addString(cursor->getLabel(), patternArgument, patternIndex);
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
                        else if(patternArgument == "curve_label")
                            found = addString(curve->getLabel(), patternArgument, patternIndex);
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
                        else if(patternArgument == "collision_curve_group_id")
                            found = addString(collisionCurve->getGroupId(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_curve_document_id")
                            found = addString(collisionCurve->getDocumentId(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_curve_label")
                            found = addString(collisionCurve->getLabel(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_curve_xPos")
                            found = addFloat(collisionCurve->getPos().x(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_curve_yPos")
                            found = addFloat(collisionCurve->getPos().y(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_curve_zPos")
                            found = addFloat(collisionCurve->getPos().z(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_xPos")
                            found = addFloat(collisionPoint.x(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_yPos")
                            found = addFloat(collisionPoint.y(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_value_x")
                            found = addFloat(collisionValue.x(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_value_y")
                            found = addFloat(collisionValue.y(), patternArgument, patternIndex);
                        else if(patternArgument == "collision_distance") {
                            NxPoint cursorPosDelta = (cursor)?(collisionPoint - cursor->getCurrentPos()):(NxPoint());
                            found = addFloat(qSqrt(cursorPosDelta.x()*cursorPosDelta.x() + cursorPosDelta.y()*cursorPosDelta.y() + cursorPosDelta.z()*cursorPosDelta.z()), patternArgument, patternIndex);
                        }
                    }
                    else {
                        if(patternArgument == "timetag")
                            found = addTimeTag(getTimeTag(), patternArgument, patternIndex);
                        else if(patternArgument == "status")
                            found = addString(status, patternArgument, patternIndex);
                        else if(patternArgument == "nb_triggers")
                            found = addFloat(nbTriggers, patternArgument, patternIndex);
                        else if(patternArgument == "nb_cursors")
                            found = addFloat(nbCursors, patternArgument, patternIndex);
                        else if(patternArgument == "nb_curves")
                            found = addFloat(nbCurves, patternArgument, patternIndex);
                        else if(patternArgument == "global_time")
                            found = addFloat(globalTime, patternArgument, patternIndex);
                        else if(patternArgument == "global_time_verbose")
                            found = addString(globalTimeVerbose, patternArgument, patternIndex);
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
                            found = addString(patternArgument, QString("custom %1").arg(patternIndex), patternIndex);
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
            else if((type == MessagesTypeTcp) || (type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect) || (type == MessagesTypeMouse) || (type == MessagesTypeTablet)) {
                asciiMessage = asciiMessage.trimmed();
            }
        }
        
        return (hasAdd && !suppressSend);
    }
    
private:
    inline qint64 getTimeTag() const {
        const qint64 january_1_1900 = -2208988800000ll;
        qint64 ntpMSecs = QDateTime::currentMSecsSinceEpoch() - january_1_1900;
        union { quint32 i[2]; qint64 t; } u;
        u.i[1] = ntpMSecs / 1000;
        u.i[0] = 0x100000000ll * (ntpMSecs % 1000) / 1000;
        return u.t;
    }
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
        else if(type == MessagesTypeTcp) {
            asciiMessage = asciiMessage + qPrintable("<argument type=\"s\" value=\"" + str + "\"/>");
            return true;
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect) || (type == MessagesTypeMouse) || (type == MessagesTypeTablet)) {
            asciiMessage = asciiMessage + " " + qPrintable(str);
            return true;
        }
        return true;
    }
    inline bool addFloat(float f, const QString & name, quint16) {
        verboseMessage = verboseMessage + " " + QByteArray::number(f);
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
            urlMessage.addQueryItem(name, QString::number(f));
            return true;
        }
        else if(type == MessagesTypeTcp) {
            asciiMessage = asciiMessage + qPrintable("<ARGUMENT TYPE=\"f\" VALUE=\"" + QString::number(f) + "\"/>");
            return true;
        }
        else if(type == MessagesTypeMidi) {
            midiValues.append(f);
            return true;
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect) || (type == MessagesTypeMouse) || (type == MessagesTypeTablet)) {
            asciiMessage = asciiMessage + " " + QByteArray::number(f);
            return true;
        }
        return true;
    }
    inline bool addTimeTag(qint64 t, const QString & name, quint16) {
        verboseMessage = verboseMessage + " " + QByteArray::number(t);
        hasAdd = true;
        if(type == MessagesTypeOsc) {
            union { qint64 t; char ch[8]; } u;
            u.t = t;
            arguments += u.ch[7];
            arguments += u.ch[6];
            arguments += u.ch[5];
            arguments += u.ch[4];
            arguments += u.ch[3];
            arguments += u.ch[2];
            arguments += u.ch[1];
            arguments += u.ch[0];
            typetag += 't';
            return true;
        }
        else if(type == MessagesTypeHttp) {
            urlMessage.addQueryItem(name, QString::number(t));
            return true;
        }
        else if(type == MessagesTypeTcp) {
            asciiMessage = asciiMessage + qPrintable("<ARGUMENT TYPE=\"t\" VALUE=\"" + QString::number(t) + "\"/>");
            return true;
        }
        else if(type == MessagesTypeMidi) {
            return true;
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect) || (type == MessagesTypeMouse) || (type == MessagesTypeTablet)) {
            asciiMessage = asciiMessage + " " + QByteArray::number(t);
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
    inline qreal getMidiValue(quint8 index) const {
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
    inline const QByteArray & getAddress() const {
        return address;
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
