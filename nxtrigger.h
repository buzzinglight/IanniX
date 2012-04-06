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

#ifndef NXTRIGGER_H
#define NXTRIGGER_H

#include "nxobject.h"

class NxTrigger : public NxObject {
    Q_OBJECT
    Q_PROPERTY(QString textureActive           READ getTextureActive          WRITE setTextureActive)
    Q_PROPERTY(QString textureInactive         READ getTextureInactive        WRITE setTextureInactive)
    Q_PROPERTY(QString textureActiveMessage    READ getTextureActiveMessage   WRITE setTextureActiveMessage)
    Q_PROPERTY(QString textureInactiveMessage  READ getTextureInactiveMessage WRITE setTextureInactiveMessage)
    Q_PROPERTY(QString colorActiveMessage      READ getColorActiveMessage     WRITE setColorActiveMessage)
    Q_PROPERTY(QString colorInactiveMessage    READ getColorInactiveMessage   WRITE setColorInactiveMessage)
    Q_PROPERTY(QString colorActiveMessageHue   READ getColorActiveMessage     WRITE setColorActiveMessageHue)
    Q_PROPERTY(QString colorInactiveMessageHue READ getColorInactiveMessage   WRITE setColorInactiveMessageHue)
    Q_PROPERTY(qreal   triggerOff              READ getTriggerOff             WRITE setTriggerOff)

public:
    explicit NxTrigger(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions);

private:
    qreal cacheSize;
    QString textureActive, textureInactive, textureActiveMessage, textureInactiveMessage;
    NxObject *cursorTrigged;
    QColor colorTrigged;
    qreal triggerOff;
public:
    inline quint8 getType() const {
        return ObjectsTypeTrigger;
    }
    inline const QString getTypeStr() const {
        return "trigger";
    }
    inline qreal getTrigged() const {
        if(cursorTrigged)
            return 127;
        else
            return 0;
    }

    inline void setTextureActive(const QString & _textureActive) {
        textureActive = _textureActive;
    }
    inline const QString & getTextureActive() const {
        return textureActive;
    }
    inline void setTextureInactive(const QString & _textureInactive) {
        textureInactive = _textureInactive;
    }
    inline const QString & getTextureInactive() const {
        return textureInactive;
    }
    inline void setTextureActiveMessage(const QString & _textureActiveMessage) {
        textureActiveMessage = _textureActiveMessage;
    }
    inline const QString & getTextureActiveMessage() const {
        return textureActiveMessage;
    }
    inline void setTextureInactiveMessage(const QString & _textureInactiveMessage) {
        textureInactiveMessage = _textureInactiveMessage;
    }
    inline const QString & getTextureInactiveMessage() const {
        return textureInactiveMessage;
    }
    inline qreal getTriggerOff() const {
        return triggerOff;
    }
    inline void setTriggerOff(qreal _triggerOff) {
        triggerOff = _triggerOff;
    }

    inline void setColorActiveMessage(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorActiveMessage = "";
            colorActiveColorMessage = QColor(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
        }
        else {
            colorActiveMessage = _color;
        }
    }
    inline void setColorActiveMessageHue(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorActiveMessage = "";
            QColor color;
            color.setHsv(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
            colorActiveColorMessage = color;
        }
        else {
            colorActiveMessage = _color;
        }
    }
    inline const QString & getColorActiveMessage() const {
        return colorActiveMessage;
    }
    inline const QColor & getColorActiveColorMessage() const {
        return colorActiveColorMessage;
    }
    inline const QString getColorActiveMessageVerbose() const {
        if(!colorActiveMessage.isEmpty())
            return colorActiveMessage;
        else
            return QString("%1 %2 %3 %4").arg(colorActiveColorMessage.red()).arg(colorActiveColorMessage.green()).arg(colorActiveColorMessage.blue()).arg(colorActiveColorMessage.alpha());
    }
    inline void setColorInactiveMessage(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorInactiveMessage = "";
            colorInactiveColorMessage = QColor(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
        }
        else
            colorInactiveMessage = _color;
    }
    inline void setColorInactiveMessageHue(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorInactiveMessage = "";
            QColor color;
            color.setHsv(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
            colorInactiveColorMessage = color;
        }
        else
            colorInactiveMessage = _color;
    }
    inline const QString & getColorInactiveMessage() const {
        return colorInactiveMessage;
    }
    inline const QColor & getColorInactiveColorMessage() const {
        return colorInactiveColorMessage;
    }
    inline const QString getColorInactiveMessageVerbose() const {
        if(!colorInactiveMessage.isEmpty())
            return colorInactiveMessage;
        else
            return QString("%1 %2 %3 %4").arg(colorInactiveColorMessage.red()).arg(colorInactiveColorMessage.green()).arg(colorInactiveColorMessage.blue()).arg(colorInactiveColorMessage.alpha());
    }





public:
    inline void calcBoundingRect() {
        //Bounding rect
        boundingRect = NxRect(-cacheSize, -cacheSize, cacheSize*2, cacheSize*2);
        boundingRect.translate(pos);
        boundingRect = boundingRect.normalized();
    }
    inline bool isMouseHover(const NxPoint & mouse) {
        if(boundingRect.contains(mouse))
            return true;
        else
            return false;
    }

    QString serializeCustom() {
        QString retour = "";
        retour += QString(COMMAND_TRIGGER_OFF + " %1 %2").arg("current").arg(getTriggerOff()) + COMMAND_END;
        retour += QString(COMMAND_TEXTURE_ACTIVE + " %1 %2").arg("current").arg(getTextureActive()) + COMMAND_END;
        retour += QString(COMMAND_TEXTURE_INACTIVE + " %1 %2").arg("current").arg(getTextureInactive()) + COMMAND_END;
        retour += QString(COMMAND_TEXTURE_ACTIVE_MESSAGE + " %1 %2").arg("current").arg(getTextureActiveMessage()) + COMMAND_END;
        retour += QString(COMMAND_TEXTURE_INACTIVE_MESSAGE + " %1 %2").arg("current").arg(getTextureInactiveMessage()) + COMMAND_END;
        if(!colorActiveMessage.isEmpty())
            retour += QString(COMMAND_COLOR_ACTIVE_MESSAGE + " %1 %2").arg("current").arg(getColorActiveMessage()) + COMMAND_END;
        else
            retour += QString(COMMAND_COLOR_ACTIVE_MESSAGE + " %1 %2 %3 %4 %5").arg("current").arg(getColorActiveColorMessage().red()).arg(getColorActiveColorMessage().green()).arg(getColorActiveColorMessage().blue()).arg(getColorActiveColorMessage().alpha()) + COMMAND_END;
        if(!colorInactiveMessage.isEmpty())
            retour += QString(COMMAND_COLOR_INACTIVE_MESSAGE + " %1 %2").arg("current").arg(getColorInactiveMessage()) + COMMAND_END;
        else
            retour += QString(COMMAND_COLOR_INACTIVE_MESSAGE + " %1 %2 %3 %4 %5").arg("current").arg(getColorInactiveColorMessage().red()).arg(getColorInactiveColorMessage().green()).arg(getColorInactiveColorMessage().blue()).arg(getColorInactiveColorMessage().alpha()) + COMMAND_END;
        return retour;
    }

public:
    void trig(NxObject *cursor);
private slots:
    void trigEnd();

public:
    void paint();
};

#endif // NXTRIGGER_H
