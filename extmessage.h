#ifndef EXTMESSAGE_H
#define EXTMESSAGE_H

#include <QUdpSocket>
#include <QTcpSocket>
#include <QStringList>
#include "nxdocument.h"
#include "nxobjectfactoryinterface.h"

enum MessagesType     { MessagesTypeNo, MessagesTypeDirect, MessagesTypeOsc, MessagesTypeUdp, MessagesTypeTcp, MessagesTypeHttp, MessagesTypeSerial, MessagesTypeMidi };

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
    QList<quint8> midiValues;
    bool hasAdd;
public:
    ExtMessage() {
        type = MessagesTypeNo;
        hasAdd = false;
    }

    inline void setUrl(const QUrl & url) {
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
    }

    inline bool parse(const QVector<QByteArray> & patternItems, NxTrigger *trigger, NxCursor *cursor, NxCurve *curve, NxCurve *collisionCurve, const QPointF & collisionPoint, const QPointF & collisionValue, const QString & status, const quint16 nbTriggers, const quint16 nbCursors, const quint16 nbCurves) {
        quint16 patternIndex = 1;
        verboseMessage = qPrintable(urlMessageString);
        midiValues.clear();
        asciiMessage = "";
        buffer.clear();
        hasAdd = false;

        if(patternItems.count() >= 2) {
            //Bind values
            for( ; patternIndex < patternItems.count() ; patternIndex++) {
                QString patternArgument = patternItems.at(patternIndex);
                if((trigger) && (patternArgument == "trigger_id"))
                    addFloat(trigger->getId(), "trigger_id", patternIndex);
                else if((trigger) && (patternArgument == "trigger_group_id"))
                    addString(trigger->getGroupId(), "trigger_group_id", patternIndex);
                else if((trigger) && (patternArgument == "trigger_document_id"))
                    addString(trigger->getDocumentId(), "trigger_document_id", patternIndex);
                else if((trigger) && (patternArgument == "trigger_xPos"))
                    addFloat(trigger->getPos().x(), "trigger_xPos", patternIndex);
                else if((trigger) && (patternArgument == "trigger_yPos"))
                    addFloat(trigger->getPos().y(), "trigger_yPos", patternIndex);
                else if((trigger) && (patternArgument == "trigger_value"))
                    addFloat(trigger->getTrigged(), "trigger_value", patternIndex);
                else if((cursor) && (patternArgument == "cursor_id"))
                    addFloat(cursor->getId(), "cursor_id", patternIndex);
                else if((cursor) && (patternArgument == "cursor_group_id"))
                    addString(cursor->getGroupId(), "cursor_group_id", patternIndex);
                else if((cursor) && (patternArgument == "cursor_document_id"))
                    addString(cursor->getDocumentId(), "cursor_document_id", patternIndex);
                else if((cursor) && (patternArgument == "cursor_xPos"))
                    addFloat(cursor->getCurrentPos().x(), "cursor_xPos", patternIndex);
                else if((cursor) && (patternArgument == "cursor_yPos"))
                    addFloat(cursor->getCurrentPos().y(), "cursor_yPos", patternIndex);
                else if((cursor) && (patternArgument == "cursor_value_x"))
                    addFloat(cursor->getCurrentValue().x(), "cursor_value_x", patternIndex);
                else if((cursor) && (patternArgument == "cursor_value_y"))
                    addFloat(cursor->getCurrentValue().y(), "cursor_value_y", patternIndex);
                else if((cursor) && (patternArgument == "cursor_time"))
                    addFloat(cursor->getCurrentPosition(), "cursor_time", patternIndex);
                else if((cursor) && (patternArgument == "cursor_time_percent"))
                    addFloat(cursor->getCurrentPositionPercent(), "cursor_time_percent", patternIndex);
                else if((cursor) && (patternArgument == "cursor_angle"))
                    addFloat(cursor->getCurrentAngle(), "cursor_angle", patternIndex);
                else if((cursor) && (patternArgument == "cursor_nb_loop"))
                    addFloat(cursor->getNbLoop(), "cursor_nb_loop", patternIndex);
                else if((curve) && (patternArgument == "curve_id"))
                    addFloat(curve->getId(), "curve_id", patternIndex);
                else if((curve) && (patternArgument == "curve_group_id"))
                    addString(curve->getGroupId(), "curve_group_id", patternIndex);
                else if((curve) && (patternArgument == "curve_document_id"))
                    addString(curve->getDocumentId(), "curve_document_id", patternIndex);
                else if((curve) && (patternArgument == "curve_xPos"))
                    addFloat(curve->getPos().x(), "curve_xPos", patternIndex);
                else if((curve) && (patternArgument == "curve_yPos"))
                    addFloat(curve->getPos().y(), "curve_yPos", patternIndex);
                else if(patternArgument == "collision_curve_id") {
                    if(collisionCurve)
                        addFloat(collisionCurve->getId(), "collision_curve_id", patternIndex);
                }
                else if(patternArgument == "collision_xPos") {
                    if(collisionCurve)
                        addFloat(collisionPoint.x(), "collision_xPos", patternIndex);
                }
                else if(patternArgument == "collision_yPos") {
                    if(collisionCurve)
                        addFloat(collisionPoint.y(), "collision_yPos", patternIndex);
                }
                else if(patternArgument == "collision_value_x") {
                    if(collisionCurve)
                        addFloat(collisionValue.x(), "collision_value_x", patternIndex);
                }
                else if(patternArgument == "collision_value_y") {
                    if(collisionCurve)
                        addFloat(collisionValue.y(), "collision_value_y", patternIndex);
                }
                else if(patternArgument == "status")
                    addString(status, "status", patternIndex);

                else if(patternArgument == "nb_triggers")
                    addFloat(nbTriggers, "nb_triggers", patternIndex);
                else if(patternArgument == "nb_cursors")
                    addFloat(nbCursors, "nb_cursors", patternIndex);
                else if(patternArgument == "nb_curves")
                    addFloat(nbCurves, "nb_curves", patternIndex);

                else {
                    //If value is not a keyword, add raw value
                    bool ok = false;
                    qreal val = patternArgument.toDouble(&ok);
                    if(ok)
                        addFloat(val, qPrintable(QString("custom %1").arg(patternIndex)), patternIndex);
                    else
                        addString(qPrintable(patternArgument), qPrintable(QString("custom %1").arg(patternIndex)), patternIndex);
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
            else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
                asciiMessage = asciiMessage.trimmed();
            }
        }

        return hasAdd;
    }

private:
    /*
    inline void addInt(int i, const char *name, quint16) {
        verboseMessage = verboseMessage + " " + conversionTemp.setNum(i);
        hasAdd = true;
        if(type == MessagesTypeOsc) {
            union { int i; char ch[4]; } u;
            u.i = i;
            arguments += u.ch[3];
            arguments += u.ch[2];
            arguments += u.ch[1];
            arguments += u.ch[0];
            typetag += 'i';
        }
        else if(type == MessagesTypeMidi) {
            midiValues.append(i);
        }
        else if(type == MessagesTypeHttp) {
            urlMessage.addQueryItem(name, QString().setNum(i));
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
            asciiMessage = asciiMessage + " " + conversionTemp.setNum(i);
        }
    }
    */
    inline void addString(const QString & str, const char *name, quint16) {
        verboseMessage = verboseMessage + " " + qPrintable(str);
        hasAdd = true;
        if(type == MessagesTypeOsc) {
            arguments += str;
            arguments += (char)0;
            pad(arguments);
            typetag += 's';
        }
        else if(type == MessagesTypeHttp) {
            urlMessage.addQueryItem(name, str);
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
            asciiMessage = asciiMessage + " " + qPrintable(str);
        }
    }
    inline void addFloat(float f, const char *name, quint16) {
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
        }
        else if(type == MessagesTypeHttp) {
            urlMessage.addQueryItem(name, QString().setNum(f));
        }
        else if(type == MessagesTypeMidi) {
            midiValues.append(f);
        }
        else if((type == MessagesTypeSerial) || (type == MessagesTypeUdp) || (type == MessagesTypeDirect)) {
            asciiMessage = asciiMessage + " " + conversionTemp.setNum(f);
        }
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
    inline quint8 getMidiValue(quint8 index) const {
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
