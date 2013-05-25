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


#include "nxobject.h"

NxObject::NxObject(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem) :
    QObject(parent), QTreeWidgetItem(ccParentItem) {
    groupId.clear();
    id = 0;
    messageTimeNowOld = 0;
    parentObject = 0;
    selectedHover = false;
    selected = false;
    hasActivity = false;
    hasActivityOld = false;
    glListRecreate = true;
    isDrag = false;
    performCollision = false;
    active = ObjectsActivityActive;
    setForeground(0, Qt::gray);
    setMessageId(0);
    lineFactor = 1;
    lineStipple = 0xFFFF;
    initialize(true);
}
void NxObject::initialize(bool firstTime) {
    if(!firstTime) {
        setGroupId("");
        setActive(1);
    }
    setSolo(0);
    setMute(0);
    setPos(NxPoint());
    setMessageTimeInterval(1);
    setMessagePatterns("");
    setLabel("");
}


void NxObject::setMessagePatterns(const QString & messagePatternsStr) {
    messagePatterns.clear();
    messageLabel.clear();
    performCollision = false;

    QString messagePatternsStrTemp = messagePatternsStr;

    QVector<QByteArray> messagePattern;
    QString messagePatternItem = "";
    QString messageLabelItem = "";
    quint16 messagePatternItemJS = 0;
    bool first = true;

    messagePatternsStrTemp.append(' '); //Pad with a space to simplify end-string handling

    for(quint16 messagePatternsStrIndex = 0 ; messagePatternsStrIndex < messagePatternsStrTemp.count() ; messagePatternsStrIndex++) {

        QChar messagePatternsStrChar = messagePatternsStrTemp.at(messagePatternsStrIndex);
        if((!messagePatternItemJS) && (messagePatternsStrChar == ' ')) {
            if(messagePatternItem.count() > 0)
                messagePattern.append(qPrintable(messagePatternItem));

            messageLabelItem.append(qPrintable(QString(messagePatternItem + " ")));
            if(messagePatternItem.contains("collision_"))
                performCollision = true;
            messagePatternItem = "";
        }
        else if((messagePatternItemJS) && (messagePatternsStrChar == '}')) {
            messagePatternItemJS--;
            if(!messagePatternItemJS) {
                if(messagePatternItem.count() > 0) {
                    messagePattern.append(qPrintable(QString("{" + messagePatternItem + "}")));
                    messageLabelItem.append(qPrintable(QString("{" + messagePatternItem + "}")));
                    if(messagePatternItem.contains("collision_"))
                        performCollision = true;
                }
                messagePatternItem = "";
            }
            else
                messagePatternItem += messagePatternsStrChar;
        }
        else if((!messagePatternItemJS) && (messagePatternsStrChar == ',')) {
            if(messagePatternItem.count() > 0) {
                if(first) {
                    quint16 interval = messagePatternItem.toUInt();
                    if(interval > 0) {
                        //qDebug("-- %d -- ", interval);
                        setMessageTimeInterval(interval);
                    }
                }
                else {
                    messagePattern.append(qPrintable(messagePatternItem));
                    messageLabel.append(messageLabelItem);
                }
            }
            first = false;
            if(messagePattern.count() > 0)
                messagePatterns.append(messagePattern);
            messagePatternItem = "";
            messagePattern.clear();
            messageLabelItem = "";
            messagePatternItemJS = 0;
        }
        else if(messagePatternsStrChar == '{') {
            if(!messagePatternItemJS)
                messagePatternItem = "";
            else
                messagePatternItem += messagePatternsStrChar;
            messagePatternItemJS++;
        }
        else {
            messagePatternItem += messagePatternsStrChar;
        }
    }

    if (messagePatternItem.count() > 0) {   //Should only get here if curly brackets are unbalanced to the left
        messageLabelItem.append(qPrintable(QString("{" + messagePatternItem)));
        messagePattern.append(qPrintable(QString("{" + messagePatternItem)));
    }

    if (messageLabelItem.count() > 0)
        messageLabel.append(qPrintable(messageLabelItem));

    if(messagePattern.count() > 0)
        messagePatterns.append(messagePattern);
}

QVector< QVector<QByteArray> > NxObject::parseMessagesPattern(const QString & messagePatternsStr, quint16 *messageInterval) {
    QVector< QVector<QByteArray> > messagePatterns;

    QVector<QByteArray> messagePattern;
    QString messagePatternItem = "";
    quint16 messagePatternItemJS = 0;
    bool first = true;
    for(quint16 messagePatternsStrIndex = 0 ; messagePatternsStrIndex < messagePatternsStr.count() ; messagePatternsStrIndex++) {
        QChar messagePatternsStrChar = messagePatternsStr.at(messagePatternsStrIndex);
        if((!messagePatternItemJS) && (messagePatternsStrChar == ' ')) {
            if(messagePatternItem.count() > 0)
                messagePattern.append(qPrintable(messagePatternItem));
            messagePatternItem = "";
        }
        else if((messagePatternItemJS) && (messagePatternsStrChar == '}')) {
            messagePatternItemJS--;
            if(!messagePatternItemJS) {
                if(messagePatternItem.count() > 0)
                    messagePattern.append(qPrintable(QString("{" + messagePatternItem + "}")));
                messagePatternItem = "";
            }
            else
                messagePatternItem += messagePatternsStrChar;
        }
        else if((!messagePatternItemJS) && (messagePatternsStrChar == ',')) {
            if(messagePatternItem.count() > 0) {
                if(first) {
                    quint16 interval = messagePatternItem.toUInt();
                    if((interval > 0) && (messageInterval))
                        *messageInterval = interval;
                }
                else
                    messagePattern.append(qPrintable(messagePatternItem));
            }
            first = false;
            if(messagePattern.count() > 0)
                messagePatterns.append(messagePattern);
            messagePatternItem = "";
            messagePattern.clear();
        }
        else if(messagePatternsStrChar == '{') {
            if(!messagePatternItemJS)
                messagePatternItem = "";
            else
                messagePatternItem += messagePatternsStrChar;
            messagePatternItemJS++;
        }
        else {
            messagePatternItem += messagePatternsStrChar;
        }
    }
    if(messagePatternItem.count() > 0)
        messagePattern.append(qPrintable(messagePatternItem));
    if(messagePattern.count() > 0)
        messagePatterns.append(messagePattern);

    return messagePatterns;
}

void NxObject::dispatchProperty(const char *_property, const QVariant & value) {
    QStringList asCurvePoints = QStringList() << COMMAND_CURVE_POINT_RMV << COMMAND_CURVE_TXT << COMMAND_CURVE_LINES << COMMAND_CURVE_POINT << COMMAND_CURVE_POINT_TRANSLATE << COMMAND_CURVE_POINT_SHIFT << COMMAND_CURVE_EDITOR << COMMAND_CURVE_PATH << COMMAND_CURVE_POINT_SMOOTH << COMMAND_CURVE_POINT_X << COMMAND_CURVE_POINT_Y << COMMAND_CURVE_POINT_Z << COMMAND_CURVE_POINT_TRANSLATE2;
    if(asCurvePoints.contains(QString(_property))) propertyChanged(COMMAND_CURVE_POINT);
    else                                           propertyChanged(_property);
    setProperty(_property, value);
}






QIcon NxObject::widgetIconActiveOff;
QIcon NxObject::widgetIconActiveOn;
QIcon NxObject::widgetIconSoloOff;
QIcon NxObject::widgetIconSoloOn;

void NxObject::setMute(quint16 _val) {
    objectMute = _val;
    if(objectMute)  setIcon(1, widgetIconActiveOff);
    else            setIcon(1, widgetIconActiveOn);
}
void NxObject::setSolo(quint16 _val) {
    objectSolo = _val;
    if(objectSolo)  setIcon(2, widgetIconSoloOn);
    else            setIcon(2, widgetIconSoloOff);
}

void NxObject::widgetClick(int col) {
    if(col == 1)        Application::current->execute(QString("%1 %2 %3").arg(COMMAND_MUTE).arg(id).arg(1-objectMute), ExecuteSourceGui);
    else if(col == 2)   Application::current->execute(QString("%1 %2 %3").arg(COMMAND_SOLO).arg(id).arg(1-objectSolo), ExecuteSourceGui);
}
