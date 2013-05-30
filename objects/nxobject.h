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

#ifndef NXOBJECT_H
#define NXOBJECT_H

#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

#include <QObject>
#include <QColor>
#include <QHash>
#include <QHashIterator>
#include <QGLWidget>
#include <QPainter>
#include <QTimer>
#include <QTreeWidgetItem>
#include <QtCore/qmath.h>
#include "iannix_spec.h"
#include "iannix_cmd.h"
#include "render/uirenderoptions.h"
#include "misc/application.h"
#include "transport/transport.h"

#define ObjectsTypeLength       3
#define ObjectsActivityLenght   2
enum ObjectsType     { ObjectsTypeCurve=0, ObjectsTypeTrigger=1, ObjectsTypeCursor=2, ObjectsTypeGroup=3, ObjectsTypeDocument=4, ObjectsTypeScheduler=5, ObjectsTypeSelection=6  };
enum ObjectsActivity { ObjectsActivityInactive=0, ObjectsActivityActive=1 };

class NxObject : public QObject, public NxObjectDispatchProperty, public QTreeWidgetItem {
    Q_OBJECT

    Q_PROPERTY(quint16 setid               READ getId                   WRITE setId)
    Q_PROPERTY(QString setline             READ getLineStr              WRITE setLineStr)
    Q_PROPERTY(QString setgroup            READ getGroupId              WRITE setGroupId)
    Q_PROPERTY(quint16 setactive           READ getActive               WRITE setActive)
    Q_PROPERTY(quint16 setmute             READ getMute                 WRITE setMute)
    Q_PROPERTY(quint16 setsolo             READ getSolo                 WRITE setSolo)
    Q_PROPERTY(qreal   setposx             READ getPosX                 WRITE setPosX)
    Q_PROPERTY(qreal   setposy             READ getPosY                 WRITE setPosY)
    Q_PROPERTY(qreal   setposz             READ getPosZ                 WRITE setPosZ)
    Q_PROPERTY(qreal   setsize             READ getSize                 WRITE setSize)
    Q_PROPERTY(quint16 setmessageinterval  READ getMessageTimeInterval  WRITE setMessageTimeInterval)
    Q_PROPERTY(QString setpos              READ getPosStr               WRITE setPosStr)
    Q_PROPERTY(QString setmessage          READ getMessagePatternsStr   WRITE setMessagePatterns)
    Q_PROPERTY(QString setlabel            READ getLabel                WRITE setLabel)
    Q_PROPERTY(QString settranslate        READ getPosTranslateStr      WRITE setPosTranslateStr)
    Q_PROPERTY(QString setcoloractive      READ getColorActiveVerbose   WRITE setColorActive)
    Q_PROPERTY(QString setcolorinactive    READ getColorInactiveVerbose WRITE setColorInactive)
    Q_PROPERTY(QString setcoloractivehue   READ getColorActiveVerbose   WRITE setColorActiveHue)
    Q_PROPERTY(QString setcolorinactivehue READ getColorInactiveVerbose WRITE setColorInactiveHue)



public:
    bool operator<(const QTreeWidgetItem &other) const {
        int column = treeWidget()->sortColumn();
        //Columns : TYPE, ACTIVE, SOLO, ID, GROUP ID
        if(    (column == 1) || (column == 2))  return icon(column).cacheKey() < other.icon(column).cacheKey();
        else if(column == 3)                    return text(column).toUInt()   < other.text(column).toUInt();
        else                                    return text(column).toLower()  < other.text(column).toLower();
    }

public:
    explicit NxObject(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem);
    void initialize(bool firstTime = false);
    virtual void initializeCustom() {}

public:
    virtual void paint() { }
    void dispatchProperty(const char *_property, const QVariant & value);
    inline const QVariant getProperty(const char *_property) const { return property(_property); }

protected:
    quint16 id;
    QString groupId;
    quint16 active;
    quint64 messageId;
    NxPoint pos, posDrag, posOffset;
    qreal size;
    quint16 lineFactor, lineStipple;
    QColor  color, colorActiveColor, colorInactiveColor, colorActiveColorMessage, colorInactiveColorMessage;
    QString colorActive, colorInactive;
    bool colorGlobal;
    NxRect boundingRect;
    QString label;
    QStringList messageLabel;
    bool selectedHover, selected, hasActivity, hasActivityOld;
    QVector< QVector<QByteArray> > messagePatterns;
    QDateTime messageTime;
    qint64 messageTimeNowOld;
    quint16 messageTimeInterval;
    NxObject *parentObject;
    bool isDrag, performCollision;
    bool glListRecreate;
    bool lockPathLength;
public slots:
    inline void setPosOffset(const NxPoint & _posOffset) {
        posOffset = _posOffset;
    }
    inline void setParentObject(NxObject *_parentObject) {
        parentObject = _parentObject;
    }
    inline NxObject *getParentObject() const {
        return parentObject;
    }

    inline bool getPerformCollision() const {
        return performCollision;
    }

    inline void setSelectedHover(bool _selectedHover) {
        selectedHover = _selectedHover;
    }
    inline bool getSelectedHover() const {
        return selectedHover;
    }
    inline void setSelected(bool _selected) {
        selected = _selected;
    }
    inline bool getSelected() const {
        return selected;
    }

    inline bool getHasActivity() const {
        return hasActivity;
    }

    inline bool getLockPathLength() const               { return lockPathLength; }
    inline void setLockPathLength(bool _lockPathLength) { lockPathLength = _lockPathLength; }

    inline void setInitialId(quint16 _id) {
        id = _id;
    }
    inline void setId(quint16 _id) {
        quint16 oldId = id;
        id = _id;
        setText(3, QString::number(id));
        Application::current->setObjectId(this, oldId);
    }
    inline quint16 getId() const {
        return id;
    }
    inline void setGroupId(const QString & _groupId) {
        QString groupIdOld = groupId;
        groupId = _groupId;
        setText(4, groupId);
        Application::current->setObjectGroupId(this, groupIdOld);
    }
    inline const QString & getGroupId() const {
        return groupId;
    }

    inline void setLabel(const QString & _label) {
        label = _label;
    }
    inline const QString & getLabel() const {
        return label;
    }

    inline void setMessageLabel(const QStringList & _messageLabel) {
        messageLabel = _messageLabel;
    }
    inline const QStringList & getMessageLabel() const {
        return messageLabel;
    }


    inline void setMessageId(quint64 _messageId) {
        messageId = _messageId;
    }
    inline quint64 getMessageId() const {
        return messageId;
    }
    inline void incMessageId() {
        messageId++;
    }


    inline void setPos(const NxPoint & _pos) {
        if(pos != _pos) {
            pos = _pos + posOffset;
            posOffset = NxPoint();
            calcBoundingRect();
            calculate();
        }
    }
    inline void setPosStr(const QString & pos) {
        QStringList posItems = pos.split(" ", QString::SkipEmptyParts);
        if(posItems.count() > 2)
            setPos(NxPoint(posItems.at(0).toDouble(), posItems.at(1).toDouble(), posItems.at(2).toDouble()));
        else if(posItems.count() > 1)
            setPos(NxPoint(posItems.at(0).toDouble(), posItems.at(1).toDouble(), 0));
    }
    inline void setPosTranslateStr(const QString & posTranslate) {
        QStringList posItems = posTranslate.split(" ", QString::SkipEmptyParts);
        if(posItems.count() > 2)
            setPos(pos + NxPoint(posItems.at(0).toDouble(), posItems.at(1).toDouble(), posItems.at(2).toDouble()));
        else if(posItems.count() > 1)
            setPos(pos + NxPoint(posItems.at(0).toDouble(), posItems.at(1).toDouble(), 0));
    }
    inline void setPosX(qreal val) { setPos(NxPoint(val, pos.y(), pos.z())); }
    inline qreal getPosX() const { return pos.x(); }
    inline void setPosY(qreal val) { setPos(NxPoint(pos.x(), val, pos.z())); }
    inline qreal getPosY() const { return pos.y(); }
    inline void setPosZ(qreal val) { setPos(NxPoint(pos.x(), pos.y(), val)); }
    inline qreal getPosZ() const { return pos.z(); }
    inline const NxPoint & getPos() const {
        return pos;
    }
    inline virtual QString getPosStr() const {
        return QString("%1 %2 %3").arg(pos.x()).arg(pos.y()).arg(pos.z());
    }
    inline QString getPosTranslateStr() const {
        return QString("%1 %2 %3").arg(pos.x()).arg(pos.y()).arg(pos.z());
    }

    inline QString getLineStr() const {
        return QString("%1 %2").arg(getLineStipple()).arg(getLineFactor());
    }
    inline void setLineStr(const QString & line) {
        QStringList lineItems = line.split(" ", QString::SkipEmptyParts);
        if(lineItems.count() > 1) {
            lineStipple = lineItems.at(0).toInt();
            lineFactor  = lineItems.at(1).toInt();
        }
    }

    virtual void calcBoundingRect() = 0;
    virtual bool isMouseHover(const NxPoint & mouse) = 0;

    inline void setSize(qreal _size) {
        size = _size;
        glListRecreate = true;
        calcBoundingRect();
    }
    inline qreal getSize() const {
        return size;
    }
    inline quint16 getLineStipple() const {
        return lineStipple;
    }
    inline quint16 getLineFactor() const {
        return lineFactor;
    }

    inline virtual void dragStart(const NxPoint &, bool) {
        posDrag = pos;
        isDrag = true;
    }
    inline virtual void drag(const NxPoint &translation, const NxPoint &, bool) {
        dragParent(translation);
    }
    inline void dragParent(const NxPoint &translation) {
        setPos(posDrag + translation);
        Application::current->execute(QString("%1 %2 %3 %4 %5").arg(COMMAND_POS).arg(id).arg(pos.x()).arg(pos.y()).arg(pos.z()), ExecuteSourceInformative);
    }
    inline virtual void dragStop() {
        posDrag = pos;
        isDrag = false;
    }
    inline const NxPoint getPosDrag() const { return posDrag; }
    virtual void calculate() {}

    inline const NxRect & getBoundingRect() const {
        return boundingRect;
    }

    inline void setActive(quint16 _active) {
        quint16 activeOld = active;
        active = _active;
        Application::current->setObjectActivity(this, activeOld);
    }
    inline quint16 getActive() const {
        return active;
    }

    inline void setColorActive(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorActive = "";
            colorActiveColor = QColor(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
        }
        else {
            colorActive = _color;
        }
    }
    inline void setColorActiveHue(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorActive = "";
            QColor color;
            color.setHsv(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
            colorActiveColor = color;
        }
        else {
            colorActive = _color;
        }
    }
    inline const QColor & getColorActiveColor() const {
        return colorActiveColor;
    }
    inline const QString getColorActiveVerbose() const {
        if(!colorActive.isEmpty())
            return colorActive;
        else
            return QString("%1 %2 %3 %4").arg(colorActiveColor.red()).arg(colorActiveColor.green()).arg(colorActiveColor.blue()).arg(colorActiveColor.alpha());
    }
    inline void setColorInactive(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorInactive = "";
            colorInactiveColor = QColor(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
        }
        else
            colorInactive = _color;
    }
    inline void setColorInactiveHue(const QString & _color) {
        QStringList colorItem = _color.split(" ", QString::SkipEmptyParts);
        if(colorItem.count() == 4) {
            colorInactive = "";
            QColor color;
            color.setHsv(colorItem.at(0).toDouble(), colorItem.at(1).toDouble(), colorItem.at(2).toDouble(), colorItem.at(3).toDouble());
            colorInactiveColor = color;
        }
        else
            colorInactive = _color;
    }
    inline const QColor & getColorInactiveColor() const {
        return colorInactiveColor;
    }
    inline const QString getColorInactiveVerbose() const {
        if(!colorInactive.isEmpty())
            return colorInactive;
        else
            return QString("%1 %2 %3 %4").arg(colorInactiveColor.red()).arg(colorInactiveColor.green()).arg(colorInactiveColor.blue()).arg(colorInactiveColor.alpha());
    }



    inline const QColor & getCurrentColor() const {
        return color;
    }

    void setMessagePatterns(const QString & messagePatternsStr);
    inline const QVector< QVector<QByteArray> > & getMessagePatterns() const {
        return messagePatterns;
    }
    inline const QString getMessagePatternsStr() const {
        QString messagePatternsStr;
        foreach(const QVector<QByteArray> & messagePattern, messagePatterns) {
            foreach(const QByteArray & messagePatternItem, messagePattern)
                messagePatternsStr += messagePatternItem + " ";
            messagePatternsStr += ", ";
        }
        messagePatternsStr = QString::number(messageTimeInterval) + ", " + messagePatternsStr;
        return messagePatternsStr.trimmed();
    }
    inline bool canSendOsc() {
        qint64 messageTimeNow = messageTime.currentMSecsSinceEpoch();
        if((messageTimeInterval > 0) && ((messageTimeNow - messageTimeNowOld) >= messageTimeInterval)) {
            messageTimeNowOld = messageTimeNow;
            return true;
        }
        else
            return false;
    }
    inline void setMessageTimeInterval(quint16 _messageTimeInterval) {
        messageTimeInterval = _messageTimeInterval;
    }
    inline quint16 getMessageTimeInterval() const {
        return messageTimeInterval;
    }


    virtual const QString serialize() const = 0;


    static QVector< QVector<QByteArray> > parseMessagesPattern(const QString & messagePatternsStr, quint16 *messageInterval = 0);

signals:

public slots:



public:
    static QIcon widgetIconActiveOff, widgetIconActiveOn, widgetIconSoloOff, widgetIconSoloOn;
private:
    quint16 objectSolo, objectMute;
public:
    bool isSolo()       const { return objectSolo >  0; }
    bool isNotMuted()   const { return objectMute == 0; }
    bool isMuted()      const { return objectMute > 0; }
    quint16 getSolo()   const { return objectSolo; }
    quint16 getMute()   const { return objectMute; }
    void setSolo(quint16 _val);
    void setMute(quint16 _val);
    void widgetClick(int col);
};

#endif // NXOBJECT_H
