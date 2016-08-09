/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NXCURVE_H
#define NXCURVE_H

#include <QScriptEngine>
#include <QScriptValue>
#include <QVarLengthArray>
#include <QBitmap>
#include "geometry/qmuparser/muParser.h"
#include "nxobject.h"
#include "qmath.h"
#include "items/uipathpointsitem.h"
#include "../abstractionsgl.h"
#ifdef Q_OS_WIN
#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401
#endif

#define CURVE_PATH_POINTS   300

using namespace mu;

enum CurveType       { CurveTypePoints, CurveTypeEllipse, CurveTypeEquationCartesian, CurveTypeEquationPolar };

Q_DECLARE_METATYPE(QList<qreal>)

class NxCurve : public NxObject {
    Q_OBJECT

    Q_PROPERTY(CurveType curveType            READ getCurveType)

    Q_PROPERTY(bool      displaycurveeditor   READ getShowPathPointsEditor   WRITE setShowPathPointsEditor)
    Q_PROPERTY(bool      displaycurveresample READ getShowPathPointsResample WRITE setShowPathPointsResample)
    Q_PROPERTY(qreal     setelasticity        READ getInertie               WRITE setInertie)
    Q_PROPERTY(qreal     setlength            READ getPathLength            WRITE setPathLength)
    Q_PROPERTY(QString   setresize            READ getResizeStr             WRITE setResizeStr)
    Q_PROPERTY(qreal     setresizef           READ getResizeF               WRITE setResizeF)
    Q_PROPERTY(QString   setequation          READ getEquationStr           WRITE setEquationStr)
    Q_PROPERTY(QString   setequationparam     READ getEquationParamStr      WRITE setEquationParamStr)
    Q_PROPERTY(QString   setequationparamlist READ getEquationParamListStr  WRITE setEquationParamListStr)
    Q_PROPERTY(quint16   setequationnbpoints  READ getEquationPoints        WRITE setEquationPoints)
    Q_PROPERTY(QString   setpointsellipse     READ getEllipseStr            WRITE setEllipseStr)
    Q_PROPERTY(quint16   removepointat        READ getRemovePointAt         WRITE setRemovePointAt)
    Q_PROPERTY(QString   shiftpoints          READ getShiftPointAt          WRITE setShiftPointAt)
    Q_PROPERTY(QString   translatepoints      READ getTranslate             WRITE setTranslate)
    Q_PROPERTY(QString   translatepoint       READ getTranslatePoint        WRITE setTranslatePoint)
    Q_PROPERTY(QString   setpointsimg         READ getResizeStr             WRITE setImage)
    Q_PROPERTY(QString   setpointslines       READ getResizeStr             WRITE setSVG2)
    Q_PROPERTY(QString   setpointspath        READ getResizeStr             WRITE setSVG)
    Q_PROPERTY(QString   setpointstxt         READ getResizeStr             WRITE setText)
    Q_PROPERTY(QList<qreal> setpointxat       READ getPointAtList           WRITE setPointXAt)
    Q_PROPERTY(QList<qreal> setpointyat       READ getPointAtList           WRITE setPointYAt)
    Q_PROPERTY(QList<qreal> setpointzat       READ getPointAtList           WRITE setPointZAt)
    Q_PROPERTY(QList<qreal> setpointat        READ getPointAtList           WRITE setPointAtList)
    Q_PROPERTY(QList<qreal> setsmoothpointat  READ getPointAtList           WRITE setSmoothPointAtList)




public:
    explicit NxCurve(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem);
    void initializeCustom();
    ~NxCurve();

private:
    bool glListRecreateFromEditor;
    CurveType curveType;
    qreal pathLength;
    QList<NxObject*> cursors;
    UiPathPointsItems pathPoints, pathPointsDest;
    UiTreeView *pathPointsEditor;
    qreal inertie;
    qint16 selectedPathPointPoint, selectedPathPointControl1, selectedPathPointControl2;
    NxSize ellipseSize;
    GLuint glListCurve;
    QString equation;
    QHash<QString,qreal> equationVariables;
    qreal equationVariableT, equationNbPoints, equationVariableTSteps;
    Parser equationParser;
    bool equationIsValid, curveNeedUpdate;
    int equationNbEval;
public:
    void setPointXAt(const QList<qreal> &points) {
        quint16 indexPoint = points.at(0);
        if(indexPoint < getPathPointsCount()) {
            NxCurvePoint ptAt = getPathPointsAt(indexPoint);
            setPointAt(indexPoint, NxPoint(points.at(1), ptAt.y(), ptAt.z()), ptAt.c1, ptAt.c2, ptAt.smooth);
        }
    }
    void setPointYAt(const QList<qreal> &points) {
        quint16 indexPoint = points.at(0);
        if(indexPoint < getPathPointsCount()) {
            NxCurvePoint ptAt = getPathPointsAt(indexPoint);
            setPointAt(indexPoint, NxPoint(ptAt.x(), points.at(1), ptAt.z()), ptAt.c1, ptAt.c2, ptAt.smooth);
        }
    }
    void setPointZAt(const QList<qreal> &points) {
        quint16 indexPoint = points.at(0);
        if(indexPoint < getPathPointsCount()) {
            NxCurvePoint ptAt = getPathPointsAt(indexPoint);
            setPointAt(indexPoint, NxPoint(ptAt.x(), ptAt.y(), points.at(1)), ptAt.c1, ptAt.c2, ptAt.smooth);
        }
    }

    void setPointAtList(const QList<qreal> &points) {
        bool recalculate = true;
        if(points.count() > 18)  // 3+18 (x, y, z, sx, sy, sz), (c1x, c1y, c1z, c1sx, c1sy, c1sz), (c2x, c2y, c2z, c2sx, c2sy, c2z)
            setPointAt(points.at(0),
                       NxPoint(points.at(1),  points.at(2),  points.at(3),  points.at(4),  points.at(5),  points.at(6)),
                       NxPoint(points.at(7),  points.at(8),  points.at(9),  points.at(10), points.at(11), points.at(12)),
                       NxPoint(points.at(13), points.at(14), points.at(15), points.at(16), points.at(17), points.at(18)), false, recalculate);
        else if(points.count() > 12)  // 3+12 (x, y, sx, sy), (c1x, c1y, c1sx, c1sy), (c2x, c2y, c2sx, c2sy)
            setPointAt(points.at(0),
                       NxPoint(points.at(1),  points.at(2),  0, points.at(3),  points.at(4),  0),
                       NxPoint(points.at(5),  points.at(6),  0, points.at(7),  points.at(8),  0),
                       NxPoint(points.at(9),  points.at(10), 0, points.at(11), points.at(12), 0), false, recalculate);
        else if(points.count() > 9) // 3+9 (x, y, z), (c1x, c1y, c1z), (c2x, c2y, c2z)
            setPointAt(points.at(0),
                       NxPoint(points.at(1), points.at(2),  points.at(3)),
                       NxPoint(points.at(4), points.at(5),  points.at(6)),
                       NxPoint(points.at(7), points.at(8),  points.at(9)), false, recalculate);
        else if(points.count() > 7) // 3+6+1 (x, y, z, sx, sy, sz) // REQUIRES A DUMMY ARGUMENT
            setPointAt(points.at(0), NxPoint(points.at(1), points.at(2), points.at(3), points.at(4), points.at(5), points.at(6)), false, recalculate);
        else if(points.count() > 6)  // 3+6 (x, y), (c1x, c1y), (c2x, c2y)
            setPointAt(points.at(0),
                       NxPoint(points.at(1), points.at(2)),
                       NxPoint(points.at(3), points.at(4)),
                       NxPoint(points.at(5), points.at(6)), false, recalculate);
        else if(points.count() > 4) // 3+4 (x, y, sx, sy)
            setPointAt(points.at(2), NxPoint(points.at(1), points.at(2), 0, points.at(3), points.at(4), 0), false, recalculate);
        else if(points.count() > 3) // 3+3 (x, y, z)
            setPointAt(points.at(0), NxPoint(points.at(1), points.at(2), points.at(3)), false, recalculate);
        else if(points.count() > 2) // 3+2 (x, y)
            setPointAt(points.at(0), NxPoint(points.at(1), points.at(2)), false, recalculate);
    }
    void setSmoothPointAtList(const QList<qreal> &points) {
        bool recalculate = true;
        if(points.count() > 6)      // 3+6 (x, y, z, sx, sy, sz)
            setPointAt(points.at(0), NxPoint(points.at(1), points.at(2), points.at(3), points.at(4), points.at(5), points.at(6)), true, recalculate);
        else if(points.count() > 4) // 3+4 (x, y, sx, sy)
            setPointAt(points.at(0), NxPoint(points.at(1), points.at(2), 0, points.at(3), points.at(4), 0), true, recalculate);
        else if(points.count() > 3) // 3+3 (x, y, z)
            setPointAt(points.at(0), NxPoint(points.at(1), points.at(2), points.at(3)), true, recalculate);
        else if(points.count() > 2) // 3+2 (x, y)
            setPointAt(points.at(0), NxPoint(points.at(1), points.at(2)), true, recalculate);
    }
    QList<qreal> getPointAtList() const {
        return QList<qreal>();
    }


    void setEquationStr(const QString &val) {
        QStringList valItems = val.split(" ", QString::SkipEmptyParts);
        if(valItems.count() > 1)
            setEquation(valItems.at(0), val.mid(val.indexOf(valItems.at(1), val.indexOf(valItems.at(0))+valItems.at(0).length())).trimmed());
    }
    inline const QString getEquationStr() { return getEquationTypeStr() + " " + getEquation(); }
    void setEquation(const QString &type, const QString &_equation);
    void setEquationPoints(quint16 nbPoints);
    void setEquationParam(const QString &param, qreal value);
    void calcEquation();
    inline QString getEquation(bool readable = false) {
        if(readable) {
            QStringList equationStrs = equation.split(",");
            QString equationReturn = "";
            foreach(const QString &equationStr, equationStrs)
                equationReturn += equationStr.trimmed() + "\n,\n";
            if(equationStrs.count())
                equationReturn.chop(3);
            return equationReturn.trimmed();
        }
        else
            return equation;
    }
    inline qint16 getEquationType() const {
        if(curveType == CurveTypeEquationCartesian)
            return 0;
        else if(curveType == CurveTypeEquationPolar)
            return 1;
        return -1;
    }
    inline const QString getEquationTypeStr() const {
        if(curveType == CurveTypeEquationCartesian)
            return "cartesian";
        else if(curveType == CurveTypeEquationPolar)
            return "polar";
        return "";
    }
    inline quint16 getEquationPoints() const {
        return equationNbPoints;
    }
    inline QString getEquationParamStr() const {
        return QString();
    }
    inline QString getEquationParamListStr() const {
        return QString();
    }
    inline qreal getEquationParam(const QString &param) const {
        if(equationVariables.contains(param))   return equationVariables.value(param);
        else                                    return 0;
    }
    inline void setEquationParamStr(const QString &params) {
        QStringList paramsList = params.split(" ");
        if(paramsList.count() > 1)
            setEquationParam(paramsList.at(0), paramsList.at(1).toDouble());
    }
    inline void setEquationParamListStr(const QString &params) {
        QStringList paramsList = params.split(" ");
        for(quint16 paramsIndex = 0 ; paramsIndex < paramsList.count() ; paramsIndex++)
            setEquationParam(QString("k%1").arg(paramsIndex), paramsList.at(paramsIndex).toDouble());
    }
    inline void setPathLength(qreal _pathLength) {
        if(_pathLength > 0)
            pathLength = _pathLength;
        else
            curveNeedUpdate = true;
    }
    inline void setInertie(qreal _inertie) {
        inertie = _inertie;
    }
    inline qreal getInertie() {
        return inertie;
    }


    inline const NxCurvePoint & getPathPointsAt(quint16 index) const {
#ifdef KINECT_INSTALLED
        NxCurvePoint pt = pathPoints.at(qBound(0, (int)index, pathPoints.count()-1));
        if((Application::current) && (Application::current->kinect))
            pt.setZ(pos.z() + Application::current->kinect->getDepthAt(pos.x() + pt.x(), pos.y() + pt.y()));
        return pt;
#else
        return pathPoints.at(qBound(0, (int)index, pathPoints.count()-1));
#endif
    }
    inline const NxCurvePoint & getPathPointsDestAt(quint16 index) const {
        return pathPointsDest.at(qBound(0, (int)index, pathPointsDest.count()-1));
    }
    inline void updatePathPointsAt(quint16 index, const NxCurvePoint &pt) {
        pathPoints[qBound(0, (int)index, pathPoints.count()-1)] = pt;
    }

    void computeInertie();

    inline quint16 getPathPointsCount() const { return pathPoints.count(); }

    void resample(quint16 nbPoints, bool smooth = true, bool triggers = false);

    void isOnPathPoint();
    void isOnPathPoint(const NxRect & point);
    inline CurveType getCurveType() const {
        return curveType;
    }


    inline const UiPathPointsItems & getPathPoints() const {
        return pathPoints;
    }
    inline void setShowPathPointsEditor(bool show = true) {
        if(!pathPointsEditor) {
            pathPointsEditor = new UiTreeView(0);
            pathPointsEditor->resize(575, 270);
            pathPointsEditor->setWindowFlags(Qt::Tool);
            pathPointsEditor->setStyleSheet(Application::current->getMainWindow()->styleSheet() + pathPointsEditor->styleSheet() + "QWidget#UiTreeView { background-color: rgb(40, 40, 40); }");
            pathPoints.configure(tr("Path points"), pathPointsEditor, &glListRecreateFromEditor);
        }
        pathPointsEditor->setWindowTitle(tr("Curve #%1").arg(id));
        pathPoints.update();
        if(show)    pathPointsEditor->show();
        else        pathPointsEditor->hide();
    }
    void setShowPathPointsResample(bool = true);
    inline bool getShowPathPointsEditor() const   { return true; }
    inline bool getShowPathPointsResample() const { return true; }
    inline void setPathPoints(const UiPathPointsItems &_pathPoints) {
        pathPoints = _pathPoints;
        glListRecreate = true;
        calcBoundingRect();
        calculate();
    }

    inline void dragStart(const NxPoint &, bool multipleObjects) {
        isDrag = true;
        if(multipleObjects)
            selectedPathPointPoint = selectedPathPointControl1 = selectedPathPointControl2 = -1;
        if(selectedPathPointPoint >= 0)             posDrag = getPathPointsAt(selectedPathPointPoint);
        else if(selectedPathPointControl1 >= 0)     posDrag = getPathPointsAt(selectedPathPointControl1).c1;
        else if(selectedPathPointControl2 >= 0)     posDrag = getPathPointsAt(selectedPathPointControl2).c2;
        else                                        posDrag = pos;
    }
    inline void drag(const NxPoint & translation, const NxPoint &, bool multipleObjects) {
        if(multipleObjects)
            selectedPathPointPoint = selectedPathPointControl1 = selectedPathPointControl2 = -1;
        if(selectedPathPointPoint >= 0) {
            NxPoint newPoint1 = posDrag + translation - getPathPointsAt(0);
            NxPoint newPoint2 = posDrag + translation - getPathPointsAt(pathPoints.count()-1);
            if((selectedPathPointPoint == pathPoints.count()-1) && ((qAbs(newPoint1.x()) < (0.25 * Render::zoomLinear)) && (qAbs(newPoint1.y()) < (0.25 * Render::zoomLinear)) && (qAbs(newPoint1.z()) < (0.25 * Render::zoomLinear))))
                setPointAt(selectedPathPointPoint, getPathPointsAt(0), pathPoints.value(selectedPathPointPoint).c1, pathPoints.value(selectedPathPointPoint).c2, pathPoints.value(selectedPathPointPoint).smooth, true, true);
            else if((selectedPathPointPoint == 0) && ((qAbs(newPoint2.x()) < (0.25 * Render::zoomLinear)) && (qAbs(newPoint2.y()) < (0.25 * Render::zoomLinear)) && (qAbs(newPoint2.z()) < (0.25 * Render::zoomLinear))))
                setPointAt(selectedPathPointPoint, getPathPointsAt(pathPoints.count()-1), pathPoints.value(selectedPathPointPoint).c1, pathPoints.value(selectedPathPointPoint).c2, pathPoints.value(selectedPathPointPoint).smooth, true, true);
            else
                setPointAt(selectedPathPointPoint, posDrag + translation, pathPoints.value(selectedPathPointPoint).c1, pathPoints.value(selectedPathPointPoint).c2, pathPoints.value(selectedPathPointPoint).smooth, true, true);
        }
        else if(selectedPathPointControl1 >= 0) {
            if(selectedPathPointControl1 > 0)
                pathPoints[selectedPathPointControl1-1].smooth = false;
            setPointAt(selectedPathPointControl1, pathPoints.value(selectedPathPointControl1), posDrag + translation, pathPoints.value(selectedPathPointControl1).c2, pathPoints.value(selectedPathPointControl1).smooth, true, true);
        }
        else if(selectedPathPointControl2 >= 0) {
            pathPoints[selectedPathPointControl2].smooth = false;
            setPointAt(selectedPathPointControl2, pathPoints.value(selectedPathPointControl2), pathPoints.value(selectedPathPointControl2).c1, posDrag + translation, pathPoints.value(selectedPathPointControl2).smooth, true, true);
        }
        else
            dragParent(translation);

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

    inline qreal getPathLength() {
        update();
        return pathLength;
    }
    void addMousePointAt(const NxPoint & _mousePos, bool remove);
    void setRemovePointAt(quint16 index);
    inline quint16 getRemovePointAt() const { return 0.; }
    const NxPoint & setPointAt(quint16 index, const NxPoint & point, bool smooth, bool boundingRectCalculation = true, bool fromGui = false);
    const NxPoint & setPointAt(quint16 index, const NxPoint & point, const NxPoint & c1, const NxPoint & c2, bool smooth, bool boundingRectCalculation = true, bool fromGui = false);

    void setSVG(const QString & pathData);
    void setSVG2(const QString & polylineData);
    void setImage(const QString & filename);
    void setText(const QString & text);
    void setText(const QString & text, const QString & family);
    void setEllipse(const NxSize & size);
    void setEllipseStr(const QString &val) {
        QStringList valItems = val.split(" ", QString::SkipEmptyParts);
        if(valItems.count() > 1)
            setEllipse(NxSize(valItems.at(0).toDouble(), valItems.at(1).toDouble()));
    }
    const QString getEllipseStr() const {
        return QString("%1 %2").arg(getResize().width()/2).arg(getResize().height()/2);
    }

    bool shiftPointAt(quint16 index, qint8 direction, bool boundingRectCalculation = true);
    bool translate(const NxPoint & point);
    void translatePoint(quint16 pointIndex, const NxPoint & point);
    const QString getShiftPointAt() const { return QString(); }
    void setShiftPointAt(const QString &val) {
        QStringList valItems = val.split(" ", QString::SkipEmptyParts);
        if(valItems.count() > 1)
            shiftPointAt(valItems.at(0).toDouble(), valItems.at(1).toDouble());
    }
    const QString getTranslate() const { return QString(); }
    void setTranslate(const QString &val) {
        QStringList valItems = val.split(" ", QString::SkipEmptyParts);
        if(valItems.count() > 2)
            translate(NxPoint(valItems.at(0).toDouble(), valItems.at(1).toDouble(), valItems.at(2).toDouble()));
    }
    const QString getTranslatePoint() const { return QString(); }
    void setTranslatePoint(const QString &val) {
        QStringList valItems = val.split(" ", QString::SkipEmptyParts);
        if(valItems.count() > 3)
            translatePoint(valItems.at(0).toInt(), NxPoint(valItems.at(1).toDouble(), valItems.at(2).toDouble(), valItems.at(3).toDouble()));
    }


    void setPath(const QPainterPath &path);
    void resize(const NxSize & size);
    void resize(qreal sizeFactorW, qreal sizeFactorH);
    inline NxPoint getPointAt(quint16 index, qreal t);
    NxPoint getPointAt(qreal val, bool absoluteTime = false);
    NxPoint getAngleAt(qreal val, bool absoluteTime = false);
    qreal intersects(const NxRect &rect, NxPoint* collisionPoint = 0);

    inline void setResize(const NxSize & size) {
        resize(size);
        calculate();
        glListRecreate = true;
    }
    inline void setResizeStr(const QString & size) {
        QStringList sizeItems = size.split(" ", QString::SkipEmptyParts);
        if(sizeItems.count() > 1)
            setResize(NxSize(sizeItems.at(0).toDouble(), sizeItems.at(1).toDouble()));
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
        curveNeedUpdate = true;
        glListRecreate = true;
        if(cursors.count()) {
            if(colorActive   == "_simple_curve_active")   colorActive   = "_curve_active";
            if(colorInactive == "_simple_curve_inactive") colorInactive = "_curve_inactive";
        } else {
            if(colorActive   == "_curve_active")   colorActive   = "_simple_curve_active";
            if(colorInactive == "_curve_inactive") colorInactive = "_simple_curve_inactive";
        }
    }
    inline void removeCursor(NxObject *cursor) {
        qint16 index = cursors.lastIndexOf(cursor);
        if(index >= 0)
            cursors.removeAt(index);
        curveNeedUpdate = true;
        glListRecreate = true;
        if(cursors.count()) {
            if(colorActive   == "_simple_curve_active")   colorActive   = "_curve_active";
            if(colorInactive == "_simple_curve_inactive") colorInactive = "_curve_inactive";
        } else {
            if(colorActive   == "_curve_active")   colorActive   = "_simple_curve_active";
            if(colorInactive == "_curve_inactive") colorInactive = "_simple_curve_inactive";
        }
    }

    const QString serialize() const {
        QString retour;
        QString objectId = QString::number(getId());

        foreach(const QString &command, propertiesToSerialize.value(NxObjectDispatchProperty::source)) {
            if(command == COMMAND_ID) {
                retour += "\trun(\"" + QString("%1 %2 %3").arg(COMMAND_ADD).arg(getTypeStr()).arg(objectId) + "\");\n"; objectId = "current";
            }
            else if(command == COMMAND_CURVE_EQUATION_PARAM) {
                QHashIterator<QString, qreal> equationVariablesIterator(equationVariables);
                while(equationVariablesIterator.hasNext()) {
                    equationVariablesIterator.next();
                    retour += "\trun(\"" + QString("%1 current %2 %3").arg(COMMAND_CURVE_EQUATION_PARAM).arg(equationVariablesIterator.key()).arg(equationVariablesIterator.value()) + "\");\n";
                }
            }
            else if(command == COMMAND_CURVE_POINT) {
                QString idStr = QString::number(id);
                retour += "\tvar points" + idStr + " = [\n";
                for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
                    retour += QString("\t\t{x: %1, y: %2, z: %3, ").arg(getPathPointsAt(indexPathPoint).x()).arg(getPathPointsAt(indexPathPoint).y()).arg(getPathPointsAt(indexPathPoint).z());
                    retour += QString("c1x: %1, c1y: %2, c1z: %3, ").arg(getPathPointsAt(indexPathPoint).c1.x()).arg(getPathPointsAt(indexPathPoint).c1.y()).arg(getPathPointsAt(indexPathPoint).c1.z());
                    retour += QString("c2x: %1, c2y: %2, c2z: %3},\n").arg(getPathPointsAt(indexPathPoint).c2.x()).arg(getPathPointsAt(indexPathPoint).c2.y()).arg(getPathPointsAt(indexPathPoint).c2.z());
                }
                retour += "\t];\n";
                retour += "\tfor(var i = 0 ; i < points" + idStr + ".length ; i++)\n";
                retour += QString("\t\trun(\"%1 %2 \" + i + \" \" + points" + idStr + "[i].x + \" \" + points" + idStr + "[i].y + \" \" + points" + idStr + "[i].z + \" \" + points" + idStr + "[i].c1x + \" \" + points" + idStr + "[i].c1y + \" \" + points" + idStr + "[i].c1z + \" \" + points" + idStr + "[i].c2x + \" \" + points" + idStr + "[i].c2y + \" \" + points" + idStr + "[i].c2z);\n").arg(COMMAND_CURVE_POINT).arg(objectId);
            }
            else
                retour += "\trun(\"" + QString("%1 %2 %3").arg(command).arg(objectId).arg(getProperty(qPrintable(command)).toString()) + "\");\n";
        }

        foreach(const NxObject *cursor, cursors)
            retour += cursor->serialize();

        if(!retour.isEmpty())
            retour += "\n";

        return retour;
    }

public:
    void paint();
    inline void update() {
        if(curveNeedUpdate) {
            curveNeedUpdate = false;
            if((curveType == CurveTypeEquationCartesian) || (curveType == CurveTypeEquationPolar))
                calcEquation();
            calcBoundingRect();
        }
    }

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
