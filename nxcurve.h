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

#ifndef NXCURVE_H
#define NXCURVE_H

#include "nxobject.h"
#include <QScriptEngine>
#include <QScriptValue>
#include "qmuparser/muParser.h"
#include "qmath.h"

#define CURVE_PATH_POINTS   300

using namespace mu;

class NxCurvePoint : public NxPoint {
public:
    NxCurvePoint() {
        currentLength = 0;
        smooth = false;
    }

    NxPoint c1, c2;
    qreal currentLength;
    NxRect boundingRect;
    bool smooth;
};

enum CurveType       { CurveTypePoints, CurveTypeEllipse, CurveTypeEquationCartesian, CurveTypeEquationPolar };

class NxCurve : public NxObject {
    Q_OBJECT
    Q_PROPERTY(qreal     pathLength  READ getPathLength)
    Q_PROPERTY(CurveType curveType   READ getCurveType)
    Q_PROPERTY(QString   resizeStr   READ getResizeStr   WRITE setResizeStr)
    Q_PROPERTY(qreal     resizeF     READ getResizeF     WRITE setResizeF)

public:
    explicit NxCurve(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions);
    ~NxCurve();

private:
    CurveType curveType;
    qreal pathLength;
    QList<NxObject*> cursors;
    QList<NxCurvePoint> pathPoints;
    qint16 selectedPathPointPoint, selectedPathPointControl1, selectedPathPointControl2;
    NxSize ellipseSize;
    GLuint glListCurve;

    QString equation;
    QHash<QString,qreal> equationVariables;
    qreal equationVariableT, equationNbPoints, equationVariableTSteps;
    Parser equationParser;
    bool equationIsValid;
    int equationNbEval;
public:
    void setEquation(const QString &type, const QString &_equation);
    void setEquationPoints(quint16 nbPoints);
    void setEquationParam(const QString &param, qreal value);
    void calcEquation();
    inline QString getEquation() {
        return equation;
    }
    inline quint16 getEquationPoints() {
        return equationNbPoints;
    }

    inline const NxCurvePoint & getPathPointsAt(quint16 index) const {
#ifdef KINECT_INSTALLED
        NxCurvePoint pt = pathPoints.at(qMax(0, qMin((int)index, pathPoints.count()-1)));
        if((factory) && (factory->kinect))
            pt.setZ(pos.z() + factory->kinect->getDepthAt(pos.x() + pt.x(), pos.y() + pt.y()));
        return pt;
#else
        return pathPoints.at(qMax(0, qMin((int)index, pathPoints.count()-1)));
#endif
    }
    inline quint16 getPathPointsCount() const { return pathPoints.count(); }

    void resample(quint16 nbPoints);

    void isOnPathPoint(const NxRect & point);
    inline CurveType getCurveType() const {
        return curveType;
    }

    inline const QList<NxCurvePoint> & getPathPoints() const {
        return pathPoints;
    }
    inline void setPathPoints(const QList<NxCurvePoint> &_pathPoints) {
        pathPoints = _pathPoints;
        glListRecreate = true;
        calculate();
        calcBoundingRect();
    }

    inline void dragStart(const NxPoint &) {
        isDrag = true;
        if(selectedPathPointPoint >= 0)
            posDrag = getPathPointsAt(selectedPathPointPoint);
        else if(selectedPathPointControl1 >= 0)
            posDrag = getPathPointsAt(selectedPathPointControl1).c1;
        else if(selectedPathPointControl2 >= 0)
            posDrag = getPathPointsAt(selectedPathPointControl2).c2;
        else
            posDrag = pos;
    }
    inline void drag(const NxPoint & translation, const NxPoint &) {
        if(selectedPathPointPoint >= 0)
            setPointAt(selectedPathPointPoint, posDrag + translation, pathPoints.value(selectedPathPointPoint).c1, pathPoints.value(selectedPathPointPoint).c2, pathPoints.value(selectedPathPointPoint).smooth);
        else if(selectedPathPointControl1 >= 0) {
            if(selectedPathPointControl1 > 0)
                pathPoints[selectedPathPointControl1-1].smooth = false;
            setPointAt(selectedPathPointControl1, pathPoints.value(selectedPathPointControl1), posDrag + translation, pathPoints.value(selectedPathPointControl1).c2, pathPoints.value(selectedPathPointControl1).smooth);
        }
        else if(selectedPathPointControl2 >= 0) {
            pathPoints[selectedPathPointControl2].smooth = false;
            setPointAt(selectedPathPointControl2, pathPoints.value(selectedPathPointControl2), pathPoints.value(selectedPathPointControl2).c1, posDrag + translation, pathPoints.value(selectedPathPointControl2).smooth);
        }
        else
            setPos(posDrag + translation);

        foreach(NxObject *object, cursors)
            object->calculate();
    }


    inline quint8 getType() const {
        return ObjectsTypeCurve;
    }
    inline const QString getTypeStr() const {
        return "curve";
    }
    inline const QList<NxObject*> & getCursors() const {
        return cursors;
    }
    inline qreal getMaxOffset() const {
        //qreal maxOffset = 0;
        return cursors.count()-1;
    }

    inline qreal getPathLength() const  { return pathLength; }
    void addMousePointAt(const NxPoint & _mousePos, bool remove);
    void removePointAt(quint16 index);
    const NxPoint & setPointAt(quint16 index, const NxPoint & point, bool smooth, bool boundingRectCalculation = true);
    const NxPoint & setPointAt(quint16 index, const NxPoint & point, const NxPoint & c1, const NxPoint & c2, bool smooth, bool boundingRectCalculation = true);
    void shiftPointAt(quint16 index, qint8 direction, bool boundingRectCalculation = true);
    void setSVG(const QString & pathData);
    void setSVG2(const QString & polylineData);
    void setImage(const QString & filename);
    void setText(const QString & text, const QString & family);
    void setEllipse(const NxSize & size);
    void setPath(const QPainterPath &path);
    void resize(const NxSize & size);
    void resize(qreal sizeFactorW, qreal sizeFactorH);
    void translate(const NxPoint & point);
    void translatePoint(quint16 pointIndex, const NxPoint & point);
    inline NxPoint getPointAt(quint16 index, qreal t);
    NxPoint getPointAt(qreal val, bool absoluteTime = false);
    qreal getAngleAt(qreal val, bool absoluteTime = false);
    qreal intersects(const NxRect &rect, NxPoint* collisionPoint = 0);

    inline void setResize(const NxSize & size) {
        resize(size);
        calculate();
        glListRecreate = true;
    }
    inline void setResizeStr(const QString & size) {
        QStringList sizeItems = size.split(" ", QString::SkipEmptyParts);
        if(sizeItems.count() >= 2)
            setResize(NxSize(sizeItems[0].toDouble(), sizeItems[1].toDouble()));
    }
    inline const NxSize getResize() const {
        return boundingRect.size();
    }
    inline QString getResizeStr() const {
        return QString("%1 %2").arg(boundingRect.size().width()).arg(boundingRect.size().height());
    }
    inline void setResizeF(qreal sizeF) {
        resize(sizeF, sizeF);
        calcBoundingRect();
        calculate();
        foreach(NxObject *object, cursors)
            object->calculate();
    }
    inline qreal getResizeF() const {
        return 1;
    }

public:
    inline void calculate() {
        foreach(NxObject *object, cursors)
            object->calculate();
    }
    void calcBoundingRect();
    bool isMouseHover(const NxPoint & mouse);


    inline void addCursor(NxObject *cursor) {
        cursors.append(cursor);
        glListRecreate = true;
    }
    inline void removeCursor(NxObject *cursor) {
        qint16 index = cursors.lastIndexOf(cursor);
        if(index >= 0)
            cursors.removeAt(index);
        glListRecreate = true;
    }

    QString serializeCustom(bool hasAScript) const {
        QString retour = "";
        QString prefix = "", postfix = COMMAND_END;
        if(hasAScript) {
            prefix = "run(\"";
            postfix =  "\");" + COMMAND_END;
        }
        if(curveType == CurveTypeEllipse)
            retour += prefix + QString(COMMAND_CURVE_ELL + " %1 %2 %3").arg("current").arg(getResize().width()/2).arg(getResize().height()/2) + postfix;
        else {
            if(hasAScript) {
                QString idStr = QString::number(id);
                retour += "var points" + idStr + " = [\n";
                for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
                    retour += QString("\t{x: %1, y: %2, z: %3, ").arg(getPathPointsAt(indexPathPoint).x()).arg(getPathPointsAt(indexPathPoint).y()).arg(getPathPointsAt(indexPathPoint).z());
                    retour += QString("c1x: %1, c1y: %2, c1z: %3, ").arg(getPathPointsAt(indexPathPoint).c1.x()).arg(getPathPointsAt(indexPathPoint).c1.y()).arg(getPathPointsAt(indexPathPoint).c1.z());
                    retour += QString("c2x: %1, c2y: %2, c2z: %3},\n").arg(getPathPointsAt(indexPathPoint).c2.x()).arg(getPathPointsAt(indexPathPoint).c2.y()).arg(getPathPointsAt(indexPathPoint).c2.z());
                }
                retour += "];" + COMMAND_END;
                retour += "for(var i = 0 ; i < points" + idStr + ".length ; i++)" + COMMAND_END;
                retour += "\trun(\"setPointAt current \" + i + \" \" + points" + idStr + "[i].x + \" \" + points" + idStr + "[i].y + \" \" + points" + idStr + "[i].z + \" \" + points" + idStr + "[i].c1x + \" \" + points" + idStr + "[i].c1y + \" \" + points" + idStr + "[i].c1z + \" \" + points" + idStr + "[i].c2x + \" \" + points" + idStr + "[i].c2y + \" \" + points" + idStr + "[i].c2z);" + COMMAND_END;
            }
            else {
                for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
                    retour += prefix + QString(COMMAND_CURVE_POINT + " %1  %2  %3 %4 %5  ").arg("current").arg(indexPathPoint).arg(getPathPointsAt(indexPathPoint).x()).arg(getPathPointsAt(indexPathPoint).y()).arg(getPathPointsAt(indexPathPoint).z());
                    retour += prefix + QString("%1 %2 %3  ").arg(getPathPointsAt(indexPathPoint).c1.x()).arg(getPathPointsAt(indexPathPoint).c1.y()).arg(getPathPointsAt(indexPathPoint).c1.z());
                    retour += prefix + QString("%1 %2 %3").arg(getPathPointsAt(indexPathPoint).c2.x()).arg(getPathPointsAt(indexPathPoint).c2.y()).arg(getPathPointsAt(indexPathPoint).c2.z()) + postfix;
                }
            }
            if((getLineStipple() != 0xFFFF) || (getLineFactor() != 1))
                retour += prefix + QString(COMMAND_LINE + " %1 %2 %3").arg("current").arg(getLineStipple()).arg(getLineFactor()) + postfix;
        }
        if(!colorActive.isEmpty()) {
            if(getColorActive() != "curve_active")
                retour += prefix + QString(COMMAND_COLOR_ACTIVE + " %1 %2").arg("current").arg(getColorActive()) + postfix;
        }
        else
            retour += prefix + QString(COMMAND_COLOR_ACTIVE + " %1 %2 %3 %4 %5").arg("current").arg(getColorActiveColor().red()).arg(getColorActiveColor().green()).arg(getColorActiveColor().blue()).arg(getColorActiveColor().alpha()) + postfix;
        if(!colorInactive.isEmpty()) {
            if(getColorInactive() != "curve_inactive")
                retour += prefix + QString(COMMAND_COLOR_INACTIVE + " %1 %2").arg("current").arg(getColorInactive()) + postfix;
        }
        else
            retour += prefix + QString(COMMAND_COLOR_INACTIVE + " %1 %2 %3 %4 %5").arg("current").arg(getColorInactiveColor().red()).arg(getColorInactiveColor().green()).arg(getColorInactiveColor().blue()).arg(getColorInactiveColor().alpha()) + postfix;
        if(getSize() != 1.2)
            retour += prefix + QString(COMMAND_SIZE + " %1 %2").arg("current").arg(getSize()) + postfix;

        foreach(const NxObject *cursor, cursors)
            retour += cursor->serialize(hasAScript);
        return retour;
    }

public:
    void paint();

};

void pathArcSegment(QPainterPath &path,
                    qreal xc, qreal yc,
                    qreal th0, qreal th1,
                    qreal rx, qreal ry, qreal xAxisRotation);
void pathArc(QPainterPath &path,
             qreal               rx,
             qreal               ry,
             qreal               x_axis_rotation,
             int         large_arc_flag,
             int         sweep_flag,
             qreal               x,
             qreal               y,
             qreal curx, qreal cury);
bool parsePathDataFast(const QString &dataStr, QPainterPath &path);
void parseNumbersArray(const QChar *&str, QVarLengthArray<qreal, 8> &points);

#endif // NXCURVE_H
