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

#ifndef NXCURSOR_H
#define NXCURSOR_H

#include <QEasingCurve>
#include "geometry/nxeasing.h"
#include "messages/messagemanager.h"
#include "objects/nxcurve.h"
#include "objects/nxtrigger.h"

#ifndef M_PI
#define M_PI    (3.14159265358979323846)
#endif
#ifndef M_PI_2
#define M_PI_2	(1.57079632679489661923)
#endif

class NxCursor : public NxObject, public NxCursorAbstraction {
    Q_OBJECT

    Q_PROPERTY(QString setoffset            READ getOffset             WRITE setOffset)
    Q_PROPERTY(QString setpattern           READ getStart              WRITE setStart)
    Q_PROPERTY(quint16 setboundssourcemode  READ getBoundsSourceMode   WRITE setBoundsSourceMode)
    Q_PROPERTY(QString setboundssource      READ getBoundsSource       WRITE setBoundsSource)
    Q_PROPERTY(QString setboundstarget      READ getBoundsTarget       WRITE setBoundsTarget)
    Q_PROPERTY(QString setspeed             READ getTimeFactorStr      WRITE setTimeFactorStr)
    Q_PROPERTY(qreal   setspeedf            READ getTimeFactorF        WRITE setTimeFactorF)
    Q_PROPERTY(qreal   setwidth             READ getWidth              WRITE setWidth)
    Q_PROPERTY(qreal   setdepth             READ getDepth              WRITE setDepth)
    Q_PROPERTY(qreal   settime              READ getTimeLocal          WRITE setTimeLocal)
    Q_PROPERTY(qreal   settimepercent       READ getTimeLocalPercent   WRITE setTimeLocalPercent)
    Q_PROPERTY(bool    trig                 READ getForceTrig          WRITE setForceTrig)


public:
    explicit NxCursor(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem);
    void initializeCustom();
    ~NxCursor();

private:
    NxCurve *curve;
private:
    qreal factors, timeLocal, timeLocalOld, timeLocalAbsolute, time, timeOld, nextTimeOld;
    qreal timeLocalLastSend, timeLastSend;
    qreal timeStartOffset, timeEndOffset, timeInitialOffset;
    NxEasing easing;
    qreal timeFactor, timeFactorF;
    quint16 nbLoop, nbLoopOld;
    qreal width, depth;
    NxRect boundsSource, boundsTarget;
    bool previousCursorReliable, previousPreviousCursorReliable;
    QVector<qreal> start;
    //NxLine cursor, cursorOld;
    NxPolygon cursorPoly, cursorPolyOld;
    NxPoint cursorPosOld, cursorAngleOld;
    NxPoint cursorPos, cursorRelativePos, cursorAngle;
    NxPoint cursorPosLastSend, cursorRelativePosLastSend, cursorAngleLastSend;
    qreal cursorAngleCacheSinZ, cursorAngleCacheCosZ, cursorAngleCacheSinY, cursorAngleCacheCosY;
    GLuint glListCursor;
    quint16 boundsSourceMode;
public:
    inline quint8 getType() const {
        return ObjectsTypeCursor;
    }
    inline const QString getTypeStr() const {
        return "cursor";
    }

    inline void dragStart(const NxPoint &, bool) {
        posDrag = pos;
        isDrag = true;
    }
    inline void drag(const NxPoint & translation, const NxPoint & mousePos, bool multipleObjects) {
        if((curve) && (!multipleObjects)) {
            qreal snapSize = Global::objectSize;
            qreal pos = curve->intersects(NxRect(mousePos - NxPoint(snapSize, snapSize), mousePos + NxPoint(snapSize, snapSize)));
            if(pos > 0) {
                Application::current->execute(QString("%1 %2 %3").arg(COMMAND_CURSOR_TIME_PERCENT).arg(id).arg(pos), ExecuteSourceGui);
                Application::current->timerTrig(this, true);
            }
        }
        else if(!curve)
            dragParent(translation);
    }

    inline QString getPosStr() const {
        return QString("%1 %2 %3").arg(cursorPos.x()).arg(cursorPos.y()).arg(cursorPos.z());
    }

    inline QString getOffset() const {
        if(timeEndOffset == 0)  return QString("%1 %2 end").arg(timeInitialOffset).arg(timeStartOffset);
        else                    return QString("%1 %2 %3").arg(timeInitialOffset).arg(timeStartOffset).arg(timeEndOffset);
    }
    inline void setOffset(const QString & offset) {
        QStringList offsetItems = offset.split(" ", QString::SkipEmptyParts);
        if(offsetItems.count() > 2) {
            timeInitialOffset = offsetItems.at(0).toDouble();
            timeStartOffset   = offsetItems.at(1).toDouble();
            if(offsetItems.at(2).toLower() == "end")    timeEndOffset = 0;
            else                                        timeEndOffset = offsetItems.at(2).toDouble();
            setTime(0);
        }
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
    inline qreal getTimeLocalLastSend() const {
        return timeLocalLastSend;
    }
    inline void setTimeLocalPercent(qreal _timeLocalPercent) {
        if((curve) && (0 <= _timeLocalPercent) && (_timeLocalPercent <= 1)) {
            timeLocal = _timeLocalPercent * curve->getPathLength();
            timeLocalAbsolute = qAbs(timeLocal);
            timeLocalOld = timeLocal;
            setNbLoop(0);
            setTime(0);
        }
    }
    inline qreal getTimeLocalPercent() const {
        return time;
    }
    inline qreal getTimeLocalPercentLastSend() const {
        return timeLastSend;
    }

    inline void setStart(const QString & startStr) {
        QStringList startItems = startStr.split(" ", QString::SkipEmptyParts);

        if(startItems.count() > 2) {
            setEasing(startItems.at(0).toInt());
            startItems.removeFirst();
            //startItems.at(1).toInt(); UNUSED
            startItems.removeFirst();

            setNbLoop(0);
            setTime(0);
            start.clear();
            foreach(const QString & startItem, startItems) {
                bool valOk = false;
                qreal val = startItem.toDouble(&valOk);
                if(valOk)
                    start.append(val);
            }
            if(start.isEmpty())
                start.append(1);
        }
    }
    inline const QString getStart() const {
        QString retour;
        foreach(const qreal startItem, start)
            retour += QString::number(startItem) + " ";
        return (QString("%1 0 %2").arg(getEasing()).arg(retour)).trimmed();
    }

    inline QString getTimeFactorStr() const {
        if(curve) {
            if(lockPathLength)  return QString("lock %3").arg(timeFactor);
            else                return QString::number(timeFactor);
        }
        return QString();
    }
    inline void setTimeFactorStr(const QString & time) {
        QStringList timeItems = time.split(" ", QString::SkipEmptyParts);
        if(timeItems.count() > 1) {
            if(timeItems.at(0).toLower() == "autolock") {
                lockPathLength = true;
                setTimeFactorAuto(timeItems.at(1).toDouble());
            }
            if(timeItems.at(0).toLower() == "lock") {
                lockPathLength = true;
                setTimeFactor(timeItems.at(1).toDouble());
            }
            if(timeItems.at(0).toLower() == "auto") {
                lockPathLength = false;
                setTimeFactorAuto(timeItems.at(1).toDouble());
            }
        }
        else if(timeItems.count() > 0) {
            lockPathLength = false;
            setTimeFactor(timeItems.at(0).toDouble());
        }
    }


    inline void setNbLoop(quint16 _nbLoop) {
        nbLoop = _nbLoop;
    }
    inline quint16 getNbLoop() const {
        return nbLoop;
    }
    inline void setEasing(quint16 _easing) {
        easing.setType(_easing);
    }
    inline quint16 getEasing() const {
        return easing.getType();
    }

    inline void setTimeStartOffset(qreal _timeStartOffset) {
        timeStartOffset = _timeStartOffset;
        setTime(0);
    }
    inline qreal getTimeStartOffset() const {
        return timeStartOffset;
    }
    inline void setTimeEndOffset(qreal _timeEndOffset) {
        timeEndOffset = _timeEndOffset;
        setTime(0);
    }
    inline qreal getTimeEndOffset() const {
        return timeEndOffset;
    }
    inline void setTimeInitialOffset(qreal _timeInitialOffset) {
        timeInitialOffset = _timeInitialOffset;
        setTime(0);
    }
    inline qreal getTimeInitialOffset() const {
        return timeInitialOffset;
    }

    inline const NxPoint getCursorValue(const NxPoint & _pos) {
        if((boundsSourceMode == 2) || (!curve)) {
            boundsSource = Global::axisArea;
            boundsSource.translate(-Global::axisCenter);
        }
        NxRect _boundsSource = boundsSource;
        if(_boundsSource.width() == 0)  _boundsSource.setWidth(0.0001);
        if(_boundsSource.height() == 0) _boundsSource.setHeight(0.0001);
        if(_boundsSource.length() == 0) _boundsSource.setLength(-0.0001);
        return NxPoint( ((_pos.x() - _boundsSource.left())   / _boundsSource.width())  * boundsTarget.width()  + boundsTarget.left() ,
                        ((_pos.y() - _boundsSource.bottom()) / _boundsSource.height()) * boundsTarget.height() + boundsTarget.bottom(),
                        ((_pos.z() - _boundsSource.zTop())   / _boundsSource.length()) * boundsTarget.length() + boundsTarget.zTop() );
    }


    void setBoundsRect(quint16 index, qreal val, bool source);
    qreal getBoundsRect(quint16 index, bool source) const;
    void setBoundsRectStr(const QString & _bounds, bool source);
    const QString getBoundsRectStr(bool source) const;

    inline quint16 getBoundsSourceMode() const {
        return boundsSourceMode;
    }
    inline void setBoundsSourceMode(quint16 _boundsSourceMode) {
        boundsSourceMode = _boundsSourceMode;
        calcBoundingRect();
    }

    inline void setBoundsSource(const QString & bounds) {
        setBoundsRectStr(bounds, true);
    }
    inline void setBoundsTarget(const QString & bounds) {
        setBoundsRectStr(bounds, false);
    }
    inline const QString getBoundsSource() const {
        return getBoundsRectStr(true);
    }
    inline const QString getBoundsTarget() const {
        return getBoundsRectStr(false);
    }


    inline void setTimeFactor(qreal _timeFactor) {
        timeFactor = _timeFactor;
    }
    inline qreal getTimeFactor() const {
        return timeFactor;
    }
    inline void setTimeFactorAuto(qreal _timeFactorAuto) {
        if((curve) && (_timeFactorAuto))
            timeFactor = curve->getPathLength() / _timeFactorAuto;
    }
    inline qreal getTimeFactorAuto() const {
        return timeFactor;
    }
    inline void setTimeFactorF(qreal _timeFactorF) {
        timeFactorF = _timeFactorF;
    }
    inline qreal getTimeFactorF() const {
        return timeFactorF;
    }

    inline void setWidth(qreal _width) {
        width = _width;
        calculate();
    }
    inline qreal getWidth() const {
        return width;
    }

    inline void setDepth(qreal _depth) {
        depth = _depth;
        calculate();
    }
    inline qreal getDepth() const {
        return depth;
    }

    inline NxCurve* getCurve() const {
        return curve;
    }
    inline void* getCurveVoid() const {
        return curve;
    }
    inline void setCurve(NxCurve *_curve) {
        if(curve)
            curve->removeCursor(this);
        curve = _curve;
        if(curve)
            curve->addCursor(this);
        setTimeLocal(Transport::timeLocal);
        calculate();
    }

    bool contains(NxTrigger *trigger) const;
    bool trig(NxCurve *collisionCurve);

    inline void calcBoundingRect() {
        //Bounding rect + margin
        boundingRect = cursorPoly.boundingRect();
        boundingRect = boundingRect.normalized();
        if((boundsSourceMode < 2) && (curve)) {
            boundsSource = NxRect(curve->getBoundingRect().normalized().bottomLeft(), curve->getBoundingRect().normalized().topRight());
            if(boundsSourceMode == 1) {
                boundsSource.setWidth (boundsSource.width()  + width);
                boundsSource.setHeight(boundsSource.height() - width);
                boundsSource.setLength(boundsSource.length() - depth);
                boundsSource.translate(NxPoint(-width/2, width/2, depth/2));
            }
        }
        else if((boundsSourceMode == 2) || (!curve)) {
            boundsSource = Global::axisArea;
            boundsSource.translate(-Global::axisCenter);
        }
    }
    inline bool isMouseHover(const NxPoint & mouse) {
        qreal snapSize = Global::objectSize;
        NxRect mouseAdjusted = NxRect(mouse - NxPoint(snapSize, snapSize), mouse + NxPoint(snapSize, snapSize));
        if(mouseAdjusted.contains(cursorPos))
            return true;
        else
            return false;
        /*
        if((cursor.intersect(NxLine(mouseAdjusted.topLeft(), mouseAdjusted.bottomRight()), 0) == NxLine::BoundedIntersection) || (cursor.intersect(NxLine(mouseAdjusted.bottomLeft(), mouseAdjusted.topRight()), 0) == NxLine::BoundedIntersection))
            return true;
        else
            return false;
        */
    }


public:
    const QString serialize() const {
        QString retour;
        QString objectId = QString::number(getId());

        foreach(const QString &command, propertiesToSerialize.value(NxObjectDispatchProperty::source)) {
            if(command == COMMAND_ID) {
                retour += "\trun(\"" + QString("%1 %2 %3").arg(COMMAND_ADD).arg(getTypeStr()).arg(objectId) + "\");\n"; objectId = "current";
                retour += "\trun(\"" + QString("%1 %2 %3").arg(COMMAND_CURSOR_CURVE).arg(objectId).arg("lastCurve") + "\");\n";
            }
            else if(command != COMMAND_CURSOR_CURVE)
                retour += "\trun(\"" + QString("%1 %2 %3").arg(command).arg(objectId).arg(getProperty(qPrintable(command)).toString()) + "\");\n";
        }
        if(NxObjectDispatchProperty::source == ExecuteSourceCopyPaste)
            retour += "\trun(\"" + QString("%1 %2 %3").arg(COMMAND_CURSOR_TIME).arg(objectId).arg(getProperty(COMMAND_CURSOR_TIME).toString()) + "\");\n";
        if(!retour.isEmpty())
            retour += "\n";
        return retour;
    }


public:
    void calculate();
    inline const NxPolygon & getCurrentPolygon() const {
        return cursorPoly;
    }
    /*
    inline qreal getCurrentPosition() const {
        if(curve)   return time * curve->getPathLength() / qAbs(factors);
        else        return 0;
    }
    */
    inline const NxPoint & getCurrentValue() const {
        return cursorRelativePos;
    }
    inline const NxPoint & getCurrentAngle() const {
        return cursorAngle;
    }
    inline const NxPoint & getCurrentPos() const {
        return cursorPos;
    }
    inline const NxPoint & getCurrentValueLastSend() const {
        return cursorRelativePosLastSend;
    }
    inline const NxPoint & getCurrentAngleLastSend() const {
        return cursorAngleLastSend;
    }
    inline const NxPoint & getCurrentPosLastSend() const {
        return cursorPosLastSend;
    }


public:
    void paint();
    void trig(bool force = false);
    bool getForceTrig() { return false;}
    void setForceTrig(bool val) {
        Application::current->timerTrig(this, val);
    }


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
