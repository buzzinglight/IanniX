#ifndef NXCURSOR_H
#define NXCURSOR_H

#include <QEasingCurve>
#include "nxcurve.h"
#include "nxtrigger.h"

#ifndef M_PI
#define M_PI    (3.14159265358979323846)
#endif
#ifndef M_PI_2
#define M_PI_2	(1.57079632679489661923)
#endif


class NxCursor : public NxObject {
    Q_OBJECT
    Q_PROPERTY(QString start READ getStart WRITE setStart)
    Q_PROPERTY(qreal timeStartOffset READ getTimeStartOffset WRITE setTimeStartOffset)
    Q_PROPERTY(qreal timeInitialOffset READ getTimeInitialOffset WRITE setTimeInitialOffset)
    Q_PROPERTY(qreal timeEndOffset READ getTimeEndOffset WRITE setTimeEndOffset)
    Q_PROPERTY(QString boundsSource READ getBoundsSource WRITE setBoundsSource)
    Q_PROPERTY(QString boundsTarget READ getBoundsTarget WRITE setBoundsTarget)
    Q_PROPERTY(qreal timeFactor READ getTimeFactor WRITE setTimeFactor)
    Q_PROPERTY(qreal timeFactorAuto READ getTimeFactorAuto WRITE setTimeFactorAuto)
    Q_PROPERTY(qreal timeFactorF READ getTimeFactorF WRITE setTimeFactorF)
    Q_PROPERTY(qreal cursorWidth READ getWidth WRITE setWidth)
    Q_PROPERTY(qreal cursorDepth READ getDepth WRITE setDepth)
    Q_PROPERTY(qreal easingStartDuration READ getEasingStartDuration WRITE setEasingStartDuration)
    Q_PROPERTY(quint16 easingStart READ getEasingStart WRITE setEasingStart)
    Q_PROPERTY(quint16 nbLoop READ getNbLoop WRITE setNbLoop)
    Q_PROPERTY(qreal timeLocal READ getTimeLocal WRITE setTimeLocal)


public:
    explicit NxCursor(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions);

private:
    NxCurve *curve;
private:
    qreal timeLocal, timeLocalOld, timeLocalAbsolute, time, timeOld, nextTimeOld;
    qreal timeStartOffset, timeEndOffset, timeInitialOffset;
    qreal easingStartDuration;
    QEasingCurve easing;
    qreal timeFactor, timeFactorF;
    quint16 nbLoop, nbLoopOld;
    qreal width, depth;
    NxRect boundsSource, boundsTarget;
    bool boundsSourceIsBoundingRect;
    NxLine previousCursor;
    bool previousCursorReliable;
    QRect boundingRectSearch;
    QVector<qreal> start;
    NxLine cursor, cursorOld;
public:
    inline quint8 getType() const {
        return ObjectsTypeCursor;
    }
    inline const QString getTypeStr() const {
        return "cursor";
    }

    void setTime(qreal delta);
    inline void setTimeLocal(qreal _timeLocal) {
        timeLocal = _timeLocal * timeFactor;
        timeLocalAbsolute = qAbs(timeLocal);
        timeLocalOld = timeLocal;
        setNbLoop(0);
        setTime(0);
    }
    inline qreal getTimeLocal() const {
        return timeLocal;
    }

    inline void setStart(const QString & startStr) {
        QStringList startItems = startStr.split(" ", QString::SkipEmptyParts);
        setNbLoop(0);
        setTime(0);
        start.clear();
        foreach(const QString & startItem, startItems)
            start.append(startItem.toDouble());
    }
    inline const QString getStart() {
        QString retour;
        foreach(qreal startItem, start)
            retour += QString().setNum(startItem) + " ";
        return retour.trimmed();
    }

    inline void setNbLoop(quint16 _nbLoop) {
        nbLoop = _nbLoop;
    }
    inline quint16 getNbLoop() {
        return nbLoop;
    }
    inline void setEasingStart(quint16 _easingStart) {
        easing.setType((QEasingCurve::Type)_easingStart);
    }
    inline quint16 getEasingStart() {
        return (quint16)easing.type();
    }
    inline void setEasingStartDuration(qreal _easingStartDuration) {
        easingStartDuration = _easingStartDuration;
    }
    inline qreal getEasingStartDuration() {
        return easingStartDuration;
    }

    inline void setTimeStartOffset(qreal _timeStartOffset) {
        timeStartOffset = _timeStartOffset;
        setTime(0);
    }
    inline qreal getTimeStartOffset() {
        return timeStartOffset;
    }
    inline void setTimeEndOffset(qreal _timeEndOffset) {
        timeEndOffset = _timeEndOffset;
        setTime(0);
    }
    inline qreal getTimeEndOffset() {
        return timeEndOffset;
    }
    inline void setTimeInitialOffset(qreal _timeInitialOffset) {
        timeInitialOffset = _timeInitialOffset;
        setTime(0);
    }
    inline qreal getTimeInitialOffset() {
        return timeInitialOffset;
    }

    inline const NxPoint getCursorValue(const NxPoint & _pos) const {
        NxRect _boundsSource = boundsSource;
        if(_boundsSource.width() == 0)  _boundsSource.setWidth(0.0001);
        if(_boundsSource.height() == 0) _boundsSource.setHeight(0.0001);
        if(_boundsSource.length() == 0) _boundsSource.setLength(0.0001);
        return NxPoint( ((_pos.x() - _boundsSource.left())   / _boundsSource.width())  * boundsTarget.width() + boundsTarget.left() ,
                        ((_pos.y() - _boundsSource.bottom()) / _boundsSource.height()) * boundsTarget.height() + boundsTarget.bottom() );
    }

    inline void setBoundsSource(const QString & _bounds) {
        QStringList bounds = _bounds.split(" ", QString::SkipEmptyParts);
        if(bounds.count() == 4) {
            boundsSource = NxRect(NxPoint(bounds[0].toDouble(), bounds[1].toDouble()), NxPoint(bounds[2].toDouble(), bounds[3].toDouble()));
            boundsSourceIsBoundingRect = false;
        }
    }
    inline const QString getBoundsSource() {
        return QString("%1 %2 %3 %4").arg(boundsSource.topLeft().x()).arg(boundsSource.topLeft().y()).arg(boundsSource.bottomRight().x()).arg(boundsSource.bottomRight().y());
    }
    inline void setBoundsTarget(const QString & _bounds) {
        QStringList bounds = _bounds.split(" ", QString::SkipEmptyParts);
        if(bounds.count() == 4)
            boundsTarget = NxRect(NxPoint(bounds[0].toDouble(), bounds[1].toDouble()), NxPoint(bounds[2].toDouble(), bounds[3].toDouble()));
    }
    inline const QString getBoundsTarget() {
        return QString("%1 %2 %3 %4").arg(boundsTarget.topLeft().x()).arg(boundsTarget.topLeft().y()).arg(boundsTarget.bottomRight().x()).arg(boundsTarget.bottomRight().y());
    }


    inline void setTimeFactor(qreal _timeFactor) {
        timeFactor = _timeFactor;
    }
    inline qreal getTimeFactor() {
        return timeFactor;
    }
    inline void setTimeFactorAuto(qreal _timeFactorAuto) {
        if((curve) && (_timeFactorAuto))
            timeFactor = curve->getPathLength() / _timeFactorAuto;
    }
    inline qreal getTimeFactorAuto() {
        if((curve) && (timeFactor))
            return curve->getPathLength() / timeFactor;
        else
            return 0;
    }
    inline void setTimeFactorF(qreal _timeFactorF) {
        timeFactorF = _timeFactorF;
    }
    inline qreal getTimeFactorF() {
        return timeFactorF;
    }

    inline void setWidth(qreal _width) {
        width = _width;
        calculate();
    }
    inline qreal getWidth() {
        return width;
    }

    inline void setDepth(qreal _depth) {
        depth = _depth;
        calculate();
    }
    inline qreal getDepth() {
        return depth;
    }

    inline NxCurve* getCurve() {
        return curve;
    }
    inline void setCurve(NxCurve *_curve) {
        if(curve)
            curve->removeCursor(this);
        curve = _curve;
        if(curve)
            curve->addCursor(this);
        calculate();
    }

    bool contains(NxTrigger *trigger);
    bool trig(NxCurve *collisionCurve);

    inline void calcBoundingRect() {
        //Bounding rect + margin
        boundingRect = cursorPoly.boundingRect();
        boundingRectSearch.setTopLeft(QPoint(floor(boundingRect.topLeft().x() / 10.0F) * 10 - 1, floor(boundingRect.topRight().y() / 10.0F) * 10 - 1));
        boundingRectSearch.setBottomRight(QPoint(ceil(boundingRect.bottomRight().x() / 10.0F) * 10 + 1, ceil(boundingRect.bottomRight().y() / 10.0F) * 10 + 1));
        boundingRect = boundingRect.normalized();
        boundingRectSearch = boundingRectSearch.normalized();

        if((boundsSourceIsBoundingRect) && (curve))
            boundsSource = NxRect(curve->getBoundingRect().normalized().bottomLeft(), curve->getBoundingRect().normalized().topRight());
    }
    inline bool isMouseHover(const NxPoint & mouse) {
        NxRect mouseAdjusted = NxRect(mouse - NxPoint(renderOptions->objectSize/2, renderOptions->objectSize/2), mouse + NxPoint(renderOptions->objectSize/2, renderOptions->objectSize/2));
        if((cursor.intersect(NxLine(mouseAdjusted.topLeft(), mouseAdjusted.bottomRight()), 0) == NxLine::BoundedIntersection) || (cursor.intersect(NxLine(mouseAdjusted.bottomLeft(), mouseAdjusted.topRight()), 0) == NxLine::BoundedIntersection))
            return true;
        else
            return false;
    }
    inline QRect getBoundingRectSearch()  { return boundingRectSearch; }


public:
    QString serializeCustom() {
        QString retour = "";
        if(curve) {
            retour += QString(COMMAND_CURSOR_CURVE + " %1 %2").arg("current").arg("lastCurve") + COMMAND_END;
            retour += QString(COMMAND_LINE + " %1 %2 %3").arg("current").arg(getLineStipple()).arg(getLineFactor()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_OFFSET + " %1 %2 %3 %4").arg("current").arg(getTimeInitialOffset()).arg(getTimeStartOffset()).arg(getTimeEndOffset()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_BOUNDS_SOURCE + " %1 %2").arg("current").arg(getBoundsSource()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_BOUNDS_TARGET + " %1 %2").arg("current").arg(getBoundsTarget()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_SPEED + " %1 %2").arg("current").arg(getTimeFactor()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_SPEEDF + " %1 %2").arg("current").arg(getTimeFactorF()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_WIDTH + " %1 %2").arg("current").arg(getWidth()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_START + " %1 %2 %3 %4").arg("current").arg(getEasingStart()).arg(getEasingStartDuration()).arg(getStart()) + COMMAND_END;
            retour += QString(COMMAND_CURSOR_TIME + " %1 %2").arg("current").arg(getTimeLocal()) + COMMAND_END;
        }
        return retour;
    }


private:
    NxPolygon cursorPoly;
    NxPoint cursorPos, cursorPosOld, cursorRelativePos;
    qreal cursorAngle, cursorAngleOld;
public:
    void calculate();
    inline const NxPolygon & getCurrentPolygon() {
        return cursorPoly;
    }
    inline qreal getCurrentPositionPercent() {
        return time;
    }
    inline qreal getCurrentPosition() {
        if(curve)
            return time * curve->getPathLength();
        else
            return 0;
    }
    inline const NxPoint & getCurrentValue() {
        return cursorRelativePos;
    }
    inline qreal getCurrentAngle() {
        return cursorAngle;
    }
    inline const NxPoint & getCurrentPos() {
        return cursorPos;
    }


public:
    void paint();
    void trig();


private:
    inline qreal fmod(qreal a, qreal b, qint32 *nb) {
        if(b)
            *nb = (qint32)floor(a / b);
        else
            *nb = 0;
        return a - (qreal)(*nb) * b;
    }
};
#endif // NXCURSOR_H
