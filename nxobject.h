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
#include "uirenderoptions.h"
#include "nxobjectfactoryinterface.h"

#define ObjectsTypeLength       3
#define ObjectsActivityLenght   2
enum ObjectsType     { ObjectsTypeCurve=0, ObjectsTypeTrigger=1, ObjectsTypeCursor=2, ObjectsTypeGroup=3, ObjectsTypeDocument=4, ObjectsTypeScheduler=5 };
enum ObjectsActivity { ObjectsActivityInactive=0, ObjectsActivityActive=1 };

class NxObject : public QObject, public NxObjectDispatchProperty, public QTreeWidgetItem {
    Q_OBJECT
    Q_PROPERTY(bool    selectedHover       READ getSelectedHover       WRITE setSelectedHover)
    Q_PROPERTY(bool    selected            READ getSelected            WRITE setSelected)
    Q_PROPERTY(quint16 id                  READ getId                  WRITE setId)
    Q_PROPERTY(QString groupId             READ getGroupId             WRITE setGroupId)
    Q_PROPERTY(QString documentId          READ getDocumentId          WRITE setDocumentId)
    Q_PROPERTY(QString label               READ getLabel               WRITE setLabel)
    Q_PROPERTY(QString posStr              READ getPosStr              WRITE setPosStr)
    Q_PROPERTY(qreal   size                READ getSize                WRITE setSize)
    Q_PROPERTY(quint16 lineFactor          READ getLineFactor          WRITE setLineFactor)
    Q_PROPERTY(quint16 lineStipple         READ getLineStipple         WRITE setLineStipple)
    Q_PROPERTY(bool    active              READ getActive              WRITE setActive)
    Q_PROPERTY(QString colorActive         READ getColorActive         WRITE setColorActive)
    Q_PROPERTY(QString colorInactive       READ getColorInactive       WRITE setColorInactive)
    Q_PROPERTY(QString colorActiveHue      READ getColorActive         WRITE setColorActiveHue)
    Q_PROPERTY(QString colorInactiveHue    READ getColorInactive       WRITE setColorInactiveHue)
    Q_PROPERTY(QString messagePatterns     READ getMessagePatternsStr  WRITE setMessagePatterns)
    Q_PROPERTY(quint16 messageTimeInterval READ getMessageTimeInterval WRITE setMessageTimeInterval)

public:
    bool operator<(const QTreeWidgetItem &other) const {
        return (text(0).toUInt() < other.text(0).toUInt());
    }

public:
    explicit NxObject(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions);

public:
    virtual void paint() { }
    inline void dispatchProperty(const QString & property, const QVariant & value) {
        setProperty(qPrintable(property), value);
    }
    inline const QVariant getProperty(const QString & _property) const {
        return property(qPrintable(_property));
    }

protected:
    UiRenderOptions *renderOptions;
    NxObjectFactoryInterface *factory;
    quint16 id;
    QString groupId, documentId;
    quint8 active;
    quint64 messageId;
    NxPoint pos, posDrag, posOffset;
    qreal size;
    quint16 lineFactor, lineStipple;
    QColor  color, colorActiveColor, colorInactiveColor, colorActiveColorMessage, colorInactiveColorMessage;
    QString colorActive, colorInactive, colorActiveMessage, colorInactiveMessage;
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

    inline void setId(quint16 _id) {
        id = _id;
        setText(3, QString::number(id));
    }
    inline quint16 getId() const {
        return id;
    }
    inline void setGroupId(const QString & _groupId) {
        QString groupIdOld = groupId;
        groupId = _groupId;
        setText(4, groupId);
        factory->setObjectGroupId(this, groupIdOld);
    }
    inline const QString & getGroupId() const {
        return groupId;
    }
    inline void setDocumentId(const QString & _documentId) {
        documentId = _documentId;
    }
    inline const QString & getDocumentId() const {
        return documentId;
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
        if((pos != _pos) && (factory)) {
            pos = _pos + posOffset;
            posOffset = NxPoint();
            calcBoundingRect();
            calculate();
        }
    }
    inline void setPosStr(const QString & pos) {
        QStringList posItems = pos.split(" ", QString::SkipEmptyParts);
        if(posItems.count() >= 3)
            setPos(NxPoint(posItems[0].toDouble(), posItems[1].toDouble(), posItems[2].toDouble()));
    }
    inline const NxPoint & getPos() const {
        return pos;
    }
    inline QString getPosStr() const {
        return QString("%1 %2 %3").arg(pos.x()).arg(pos.y()).arg(pos.z());
    }
    /*
    inline const NxPoint getPosTransform() const {
        return renderOptions->transform(pos);
    }
    */
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
    inline void setLineStipple(quint16 _lineStipple) {
        lineStipple = _lineStipple;
    }
    inline quint16 getLineStipple() const {
        return lineStipple;
    }
    inline void setLineFactor(quint16 _lineFactor) {
        lineFactor = _lineFactor;
    }
    inline quint16 getLineFactor() const {
        return lineFactor;
    }

    inline virtual void dragStart() {
        posDrag = pos;
        isDrag = true;
    }
    inline virtual void drag(const NxPoint & translation) {
        setPos(posDrag + translation);
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

    inline void setActive(quint8 _active) {
        if(factory) {
            quint8 activeOld = active;
            active = _active;
            factory->setObjectActivity(this, activeOld);
            /*
            if(active)
                setCheckState(0, Qt::Checked);
            else
                setCheckState(0, Qt::Unchecked);
            */
        }
    }
    inline quint8 getActive() const {
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
    inline const QString & getColorActive() const {
        return colorActive;
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
    inline const QString & getColorInactive() const {
        return colorInactive;
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
            messagePatternsStr += ",";
        }
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


    virtual QString serializeCustom() const { return ""; }
    inline QString serialize() const {
        QString retour;
        retour += QString(COMMAND_ADD + " %1 %2").arg(getTypeStr()).arg(getId()) + COMMAND_END;
        retour += QString(COMMAND_POS + " %1 %2 %3 %4").arg("current").arg(getPos().x()).arg(getPos().y()).arg(getPos().z()) + COMMAND_END;
        retour += QString(COMMAND_ACTIVE + " %1 %2").arg("current").arg(getActive()) + COMMAND_END;
        retour += QString(COMMAND_GROUP + " %1 %2").arg("current").arg(getGroupId()) + COMMAND_END;

        if(!colorActive.isEmpty())
            retour += QString(COMMAND_COLOR_ACTIVE + " %1 %2").arg("current").arg(getColorActive()) + COMMAND_END;
        else
            retour += QString(COMMAND_COLOR_ACTIVE + " %1 %2 %3 %4 %5").arg("current").arg(getColorActiveColor().red()).arg(getColorActiveColor().green()).arg(getColorActiveColor().blue()).arg(getColorActiveColor().alpha()) + COMMAND_END;
        if(!colorInactive.isEmpty())
            retour += QString(COMMAND_COLOR_INACTIVE + " %1 %2").arg("current").arg(getColorInactive()) + COMMAND_END;
        else
            retour += QString(COMMAND_COLOR_INACTIVE + " %1 %2 %3 %4 %5").arg("current").arg(getColorInactiveColor().red()).arg(getColorInactiveColor().green()).arg(getColorInactiveColor().blue()).arg(getColorInactiveColor().alpha()) + COMMAND_END;

        retour += QString(COMMAND_SIZE + " %1 %2").arg("current").arg(getSize()) + COMMAND_END;
        retour += QString(COMMAND_MESSAGE + " %1 %2, %3").arg("current").arg(QString::number(messageTimeInterval)).arg(getMessagePatternsStr()) + COMMAND_END;
        retour += QString(COMMAND_LABEL + " %1 %2").arg("current").arg(getLabel()) + COMMAND_END;
        retour += serializeCustom();
        return retour;
    }


    static QVector< QVector<QByteArray> > parseMessagesPattern(const QString & messagePatternsStr, quint16 *messageInterval = 0);

signals:

public slots:

};

#endif // NXOBJECT_H
