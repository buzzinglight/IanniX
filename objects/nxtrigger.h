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
#include "messages/messagemanager.h"

class NxTrigger : public NxObject {
    Q_OBJECT

    Q_PROPERTY(QString settextureactive   READ getTextureActive   WRITE setTextureActive)
    Q_PROPERTY(QString settextureinactive READ getTextureInactive WRITE setTextureInactive)
    Q_PROPERTY(qreal   settriggeroff      READ getTriggerOff      WRITE setTriggerOff)
    Q_PROPERTY(bool    trig               READ getForceTrig       WRITE setForceTrig)

public:
    explicit NxTrigger(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem);
    void initializeCustom();

private:
    qreal cacheSize;
    QString textureActive, textureInactive;
    NxObject *cursorTrigged;
    QColor colorTrigged;
    qreal triggerOff;
    static GLuint glListTrigger;
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
    inline qreal getTriggerOff() const {
        return triggerOff;
    }
    inline void setTriggerOff(qreal _triggerOff) {
        triggerOff = _triggerOff;
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

    const QString serialize() const {
        QString retour = "";
        QString objectId = QString::number(getId());

        foreach(const QString &command, propertiesToSerialize.value(NxObjectDispatchProperty::source)) {
            if(command == COMMAND_ID) {
                retour += "\trun(\"" + QString("%1 %2 %3").arg(COMMAND_ADD).arg(getTypeStr()).arg(objectId) + "\");\n"; objectId = "current";
            }
            else                      retour += "\trun(\"" + QString("%1 %2 %3").arg(command).arg(objectId).arg(getProperty(qPrintable(command)).toString()) + "\");\n";
        }
        if(!retour.isEmpty())
            retour += "\n";
        return retour;
    }

public:
    void trig(NxObject *cursor);
    bool getForceTrig() { return false;}
    void setForceTrig(bool) {
        trig(0);
    }

private slots:
    void trigEnd();

public:
    void paint();
};

#endif // NXTRIGGER_H
