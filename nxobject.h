#ifndef NXOBJECT_H
#define NXOBJECT_H

#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

#include <QObject>
#include <QPointF>
#include <QColor>
#include <QHash>
#include <QHashIterator>
#include <QGLWidget>
#include <QPainter>
#include <QTimer>
#include <QTreeWidgetItem>
#include <math.h>
#include "uirenderoptions.h"
#include "nxobjectfactoryinterface.h"

#define ObjectsTypeLength       3
#define ObjectsActivityLenght   2
enum ObjectsType     { ObjectsTypeCurve=0, ObjectsTypeTrigger=1, ObjectsTypeCursor=2, ObjectsTypeGroup=3, ObjectsTypeDocument=4, ObjectsTypeScheduler=5 };
enum ObjectsActivity { ObjectsActivityInactive=0, ObjectsActivityActive=1 };

#define COMMAND_END_BYTE        '\n'
#define COMMAND_END             QString(COMMAND_END_BYTE)
#define COMMAND_ADD             QString("add")
#define COMMAND_REMOVE          QString("remove")
#define COMMAND_CLEAR           QString("clear")
#define COMMAND_GROUP           QString("setgroup")
#define COMMAND_TRIGGER_OFF     QString("settriggeroff")
#define COMMAND_CURSOR_CURVE    QString("setcurve")
#define COMMAND_CURSOR_WIDTH    QString("setwidth")
#define COMMAND_CURSOR_START    QString("setpattern")
#define COMMAND_CURSOR_SPEED    QString("setspeed")
#define COMMAND_CURSOR_SPEEDF   QString("setspeedf")
#define COMMAND_CURSOR_OFFSET   QString("setoffset")
#define COMMAND_CURSOR_BOUNDS_SOURCE   QString("setboundssource")
#define COMMAND_CURSOR_BOUNDS_TARGET   QString("setboundstarget")
#define COMMAND_CURSOR_TIME     QString("settime")
#define COMMAND_CURVE_POINT	 QString("setpointat")
#define COMMAND_CURVE_TXT	 QString("setpointstxt")
#define COMMAND_CURVE_SVG	 QString("setpointssvg")
#define COMMAND_CURVE_SVG2	 QString("setpointssvg2")
#define COMMAND_CURVE_IMG	 QString("setpointsimg")
#define COMMAND_CURVE_ELL	 QString("setpointsellipse")
#define COMMAND_SIZE            QString("setsize")
#define COMMAND_RESIZE          QString("setresize")
#define COMMAND_RESIZEF         QString("setresizef")
#define COMMAND_LINE            QString("setline")
#define COMMAND_POS             QString("setpos")
#define COMMAND_ACTIVE          QString("setactive")
#define COMMAND_LABEL           QString("setlabel")
#define COMMAND_MESSAGE         QString("setmessage")
#define COMMAND_MESSAGE_SEND    QString("sendosc")
#define COMMAND_TEXTURE         QString("registertexture")
#define COMMAND_GLOBAL_COLOR    QString("registercolor")
#define COMMAND_GLOBAL_COLOR2   QString("registercolor2")
#define COMMAND_TEXTURE_ACTIVE  QString("settextureactive")
#define COMMAND_TEXTURE_INACTIVE  QString("settextureinactive")
#define COMMAND_TEXTURE_ACTIVE_MESSAGE  QString("settextureactivemessage")
#define COMMAND_TEXTURE_INACTIVE_MESSAGE  QString("settextureinactivemessage")
#define COMMAND_COLOR_ACTIVE    QString("setcoloractive")
#define COMMAND_COLOR_INACTIVE  QString("setcolorinactive")
#define COMMAND_COLOR_ACTIVE_MESSAGE    QString("setcoloractivemessage")
#define COMMAND_COLOR_INACTIVE_MESSAGE  QString("setcolorinactivemessage")
#define COMMAND_COLOR_ACTIVE2    QString("setcoloractive2")
#define COMMAND_COLOR_INACTIVE2  QString("setcolorinactive2")
#define COMMAND_COLOR_ACTIVE_MESSAGE2    QString("setcoloractivemessage2")
#define COMMAND_COLOR_INACTIVE_MESSAGE2  QString("setcolorinactivemessage2")
#define COMMAND_AUTOSIZE        QString("autosize")
#define COMMAND_ZOOM            QString("zoom")
#define COMMAND_CENTER          QString("center")
#define COMMAND_PLAY            QString("play")
#define COMMAND_STOP            QString("stop")
#define COMMAND_FF              QString("fastrewind")
#define COMMAND_SPEED           QString("speed")
#define COMMAND_SNAP_PUSH       QString("pushsnapshot")
#define COMMAND_SNAP_POP        QString("popsnapshot")
#define COMMAND_LOG             QString("log")


class NxObjectDispatchProperty {
public:
    virtual quint8 getType() const = 0;
    virtual const QString getTypeStr() const = 0;
    virtual void dispatchProperty(const QString & property, const QVariant & value) = 0;
    virtual const QVariant getProperty(const QString & property) const = 0;
};


class NxObject : public QObject, public NxObjectDispatchProperty, public QTreeWidgetItem {
    Q_OBJECT;
    Q_PROPERTY(QRect local READ getLocal);
    Q_PROPERTY(bool selectedHover READ getSelectedHover WRITE setSelectedHover);
    Q_PROPERTY(bool selected READ getSelected WRITE setSelected);
    Q_PROPERTY(quint16 id READ getId WRITE setId);
    Q_PROPERTY(QString groupId READ getGroupId WRITE setGroupId);
    Q_PROPERTY(QString documentId READ getDocumentId WRITE setDocumentId);
    Q_PROPERTY(QString label READ getLabel WRITE setLabel);
    Q_PROPERTY(QPointF pos READ getPos WRITE setPos);
    Q_PROPERTY(qreal z READ getZ WRITE setZ);
    Q_PROPERTY(qreal size READ getSize WRITE setSize);
    Q_PROPERTY(quint16 lineFactor READ getLineFactor WRITE setLineFactor);
    Q_PROPERTY(quint16 lineStipple READ getLineStipple WRITE setLineStipple);
    Q_PROPERTY(QRectF boundingRect READ getBoundingRect);
    Q_PROPERTY(bool active READ getActive WRITE setActive);
    Q_PROPERTY(QString colorActive READ getColorActive WRITE setColorActive);
    Q_PROPERTY(QString colorInactive READ getColorInactive WRITE setColorInactive);
    Q_PROPERTY(QString colorActive2 READ getColorActive WRITE setColorActive2);
    Q_PROPERTY(QString colorInactive2 READ getColorInactive WRITE setColorInactive2);
    Q_PROPERTY(QString messagePatterns READ getMessagePatternsStr WRITE setMessagePatterns);
    Q_PROPERTY(quint16 messageTimeInterval READ getMessageTimeInterval WRITE setMessageTimeInterval);

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
    QPointF pos, posDrag, posOffset;
    qreal z, size;
    quint16 lineFactor, lineStipple;
    QColor  color, colorActiveColor, colorInactiveColor, colorActiveColorMessage, colorInactiveColorMessage;
    QString colorActive, colorInactive, colorActiveMessage, colorInactiveMessage;
    bool colorGlobal;
    QRectF boundingRect;
    QString label;
    QStringList messageLabel;
    bool selectedHover, selected;
    QVector< QVector<QByteArray> > messagePatterns;
    QTime messageTime;
    quint16 messageTimeInterval;
    NxObject *parentObject;
    bool isDrag, performCollision;
public slots:
    inline const QRect getLocal() const {
        return QRect(floor(pos.x() / 10) * 10, floor(pos.y() / 10) * 10, floor(z / 10) * 10, 0);
    }

    inline void setPosOffset(const QPointF & _posOffset) {
        posOffset = _posOffset;
    }
    inline void setParentObject(NxObject *_parentObject) {
        parentObject = _parentObject;
    }
    inline NxObject *getParentObject() const {
        return parentObject;
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

    inline void setId(quint16 _id) {
        id = _id;
        setText(0, QString().setNum(id));
    }
    inline quint16 getId() const {
        return id;
    }
    inline void setGroupId(const QString & _groupId) {
        QString groupIdOld = groupId;
        groupId = _groupId;
        setText(1, groupId);
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

    inline void setPos(const QPointF & _pos) {
        if((pos != _pos) && (factory)) {
            QRect localOld = getLocal();
            pos = _pos + posOffset;
            posOffset = QPointF(0, 0);
            calcBoundingRect();
            calculate();
            factory->setObjectLocal(this, localOld);
        }
    }
    inline const QPointF & getPos() const {
        return pos;
    }
    /*
    inline const QPointF getPosTransform() const {
        return renderOptions->transform(pos);
    }
    */
    inline void setZ(qreal _z) {
        if(factory) {
            QRect localOld = getLocal();
            z = _z;
            factory->setObjectLocal(this, localOld);
        }
    }
    inline qreal getZ() const {
        return z;
    }
    virtual void calcBoundingRect() = 0;
    virtual bool isMouseHover(const QPointF & mouse) = 0;

    inline void setSize(qreal _size) {
        size = _size;
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
    inline virtual void drag(const QPointF & translation) {
        setPos(posDrag + translation);
    }
    inline virtual void dragStop() {
        posDrag = pos;
        isDrag = false;
    }
    virtual void calculate() {}

    inline const QRectF & getBoundingRect() const {
        return boundingRect;
    }

    inline void setActive(quint8 _active) {
        if(factory) {
            quint8 activeOld = active;
            active = _active;
            factory->setObjectActivity(this, activeOld);
            if(active)
                setText(2, tr("active"));
            else
                setText(2, tr("inactive"));
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
    inline void setColorActive2(const QString & _color) {
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
        if(colorActive != "")
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
    inline void setColorInactive2(const QString & _color) {
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
        if(colorInactive != "")
            return colorInactive;
        else
            return QString("%1 %2 %3 %4").arg(colorInactiveColor.red()).arg(colorInactiveColor.green()).arg(colorInactiveColor.blue()).arg(colorInactiveColor.alpha());
    }



    inline const QColor & getCurrentColor() const {
        return color;
    }

    inline void setMessagePatterns(const QString & _messagePatterns) {
        messagePatterns.clear();
        messageLabel.clear();
        performCollision = false;
        QStringList messagePatternsArray = _messagePatterns.split(",", QString::SkipEmptyParts);
        bool first = true;
        foreach(const QString & messagePattern, messagePatternsArray) {
            QString messageLabelItem = "";
            if(first) {
                setMessageTimeInterval(messagePattern.toUInt());
                first = false;
            }
            else {
                QStringList messagePatternStrings = messagePattern.split(" ", QString::SkipEmptyParts);
                QVector<QByteArray> messagePattern;
                foreach(QString messagePatternString, messagePatternStrings) {
                    messagePattern.append(qPrintable(messagePatternString));
                    messageLabelItem += messagePatternString + " ";
                    if(messagePatternString.contains("collision_"))
                        performCollision = true;
                }
                messagePatterns.append(messagePattern);
                messageLabel.append(messageLabelItem);
            }
        }
    }
    inline void setMessagePatterns(QVector< QVector<QByteArray> > _messagePatterns) {
        performCollision = false;
        messagePatterns = _messagePatterns;
        messageLabel.clear();
        foreach(const QVector<QByteArray> & _messagePattern, _messagePatterns) {
            QString messageLabelItem = "";
            foreach(const QByteArray & _messagePatternByte, _messagePattern) {
                messageLabelItem += _messagePatternByte + " ";
                if(_messagePatternByte.contains("collision_"))
                    performCollision = true;
            }
            messageLabel.append(messageLabelItem);
        }
    }
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
        if((messageTimeInterval > 0) && (messageTime.elapsed() >= messageTimeInterval)) {
            messageTime.start();
            return true;
        }
        else
            return false;
    }
    inline void setMessageTimeInterval(quint16 _messageTimeInterval) {
        messageTimeInterval = _messageTimeInterval;
    }
    inline quint16 getMessageTimeInterval() {
        return messageTimeInterval;
    }


    virtual QString serializeCustom() { return ""; }
    inline QString serialize() {
        QString retour;
        retour += QString(COMMAND_ADD + " %1 %2").arg(getTypeStr()).arg(getId()) + COMMAND_END;
        retour += QString(COMMAND_POS + " %1 %2 %3 %4").arg("current").arg(getPos().x()).arg(getPos().y()).arg(getZ()) + COMMAND_END;
        retour += QString(COMMAND_ACTIVE + " %1 %2").arg("current").arg(getActive()) + COMMAND_END;
        retour += QString(COMMAND_GROUP + " %1 %2").arg("current").arg(getGroupId()) + COMMAND_END;

        if(colorActive != "")
            retour += QString(COMMAND_COLOR_ACTIVE + " %1 %2").arg("current").arg(getColorActive()) + COMMAND_END;
        else
            retour += QString(COMMAND_COLOR_ACTIVE + " %1 %2 %3 %4 %5").arg("current").arg(getColorActiveColor().red()).arg(getColorActiveColor().green()).arg(getColorActiveColor().blue()).arg(getColorActiveColor().alpha()) + COMMAND_END;
        if(colorInactive != "")
            retour += QString(COMMAND_COLOR_INACTIVE + " %1 %2").arg("current").arg(getColorInactive()) + COMMAND_END;
        else
            retour += QString(COMMAND_COLOR_INACTIVE + " %1 %2 %3 %4 %5").arg("current").arg(getColorInactiveColor().red()).arg(getColorInactiveColor().green()).arg(getColorInactiveColor().blue()).arg(getColorInactiveColor().alpha()) + COMMAND_END;

        retour += QString(COMMAND_SIZE + " %1 %2").arg("current").arg(getSize()) + COMMAND_END;
        retour += QString(COMMAND_MESSAGE + " %1 %2, %3").arg("current").arg(QString().setNum(messageTimeInterval)).arg(getMessagePatternsStr()) + COMMAND_END;
        retour += QString(COMMAND_LABEL + " %1 %2").arg("current").arg(getLabel()) + COMMAND_END;
        retour += serializeCustom();
        return retour;
    }


signals:

public slots:

};

#endif // NXOBJECT_H
