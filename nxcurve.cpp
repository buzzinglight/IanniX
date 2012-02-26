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

#include "nxcurve.h"

NxCurve::NxCurve(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
    NxObject(parent, ccParentItem, _renderOptions) {
    calcBoundingRect();
    setSize(1.2);
    setLineFactor(1);
    setLineStipple(0xFFFF);
    setColorActive("curve_active");
    setColorInactive("curve_inactive");
    selectedPathPointPoint = -1;
    selectedPathPointControl1 = -1;
    selectedPathPointControl2 = -1;
    curveType = CurveTypePoints;
    setPointAt(0, NxPoint(), NxPoint(), NxPoint(), false);
    setMessageTimeInterval(20);
}

void NxCurve::paint() {
#ifdef KINECT_INSTALLED

#endif

    //Color
    if(active)
        color = (colorActive != "")?(renderOptions->colors.value(colorActive)):(colorActiveColor);
    else
        color = (colorInactive != "")?(renderOptions->colors.value(colorInactive)):(colorInactiveColor);

    if(color.alpha() > 0) {
        //Mouse hover
        if(selectedHover)
            color = renderOptions->colors.value("object_hover");
        if(selected)
            color = renderOptions->colors.value("object_selection");

        //Hide curve if a cursor is present but inactive
        if((renderOptions->paintCurvesOpacity) && (cursors.count() > 0)) {
            bool display = false;
            foreach(NxObject *cursor, cursors)
                if(cursor->getHasActivity()) {
                    display = true;
                    break;
                }
            if(!display)
                color.setAlpha(color.alpha() / 4);
        }

        //Start
        if((renderOptions->paintCurves) && (renderOptions->paintThisGroup) && ((renderOptions->paintZStart <= pos.z()) && (pos.z() <= renderOptions->paintZEnd)))
            glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        else
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.1);

        glPushMatrix();
        glTranslatef(pos.x(), pos.y(), pos.z());

        //Label
        if((renderOptions->paintLabel) && (label != "")) {
            NxPoint pt = getPathPointsAt(0);
            renderOptions->render->renderText(pt.x(), pt.y(), pt.z(), label, renderOptions->renderFont);
        }

        //Draw
        glLineWidth(size);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(lineFactor, lineStipple);
        if(curveType == CurveTypeEllipse) {
            glBegin(GL_LINE_LOOP);
            for(qreal angle = 0 ; angle <= 2*M_PI ; angle += 0.1)
                glVertex3f(ellipseSize.width() * qCos(angle), ellipseSize.height() * qSin(angle), 0);
            glEnd();
        }
        else {
            for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++) {
                if(indexPoint < pathPoints.count()-1) {
                    NxPoint p1 = getPathPointsAt(indexPoint), p2 = getPathPointsAt(indexPoint+1);
                    NxPoint c1 = p1 + getPathPointsAt(indexPoint+1).c1, c2 = p2 + getPathPointsAt(indexPoint+1).c2;

                    GLfloat ctrlpoints[4][3] = {
                        { p1.x(), p1.y(), p1.z() }, { c1.x(), c1.y(), c1.z() },
                        { c2.x(), c2.y(), c2.z() }, { p2.x(), p2.y(), p2.z() } };
                    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
                    glEnable(GL_MAP1_VERTEX_3);
                    glBegin(GL_LINE_STRIP);
                    for(GLfloat t = 0.0f ; t <= 1.05f ; t += 0.05f)
                        glEvalCoord1f(t);
                    glEnd();
                    glDisable(GL_MAP1_VERTEX_3);
                }
            }
        }
        glDisable(GL_LINE_STIPPLE);

        //Selection
        if(selected) {
            glLineWidth(1);
            for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++) {
                NxPoint p1 = getPathPointsAt(indexPoint);

                if(selectedPathPointPoint == indexPoint)
                    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
                else
                    glColor4f(color.redF(), color.greenF(), color.blueF(), 0.5);
                glBegin(GL_QUADS);
                glVertex3f(p1.x() - renderOptions->objectSize/4, p1.y() - renderOptions->objectSize/4, p1.z());
                glVertex3f(p1.x() + renderOptions->objectSize/4, p1.y() - renderOptions->objectSize/4, p1.z());
                glVertex3f(p1.x() + renderOptions->objectSize/4, p1.y() + renderOptions->objectSize/4, p1.z());
                glVertex3f(p1.x() - renderOptions->objectSize/4, p1.y() + renderOptions->objectSize/4, p1.z());
                glEnd();


                if((indexPoint+1) < pathPoints.count()) {
                    NxPoint c1 = p1 + getPathPointsAt(indexPoint+1).c1;
                    if(selectedPathPointControl1 == indexPoint+1)
                        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
                    else
                        glColor4f(color.redF(), color.greenF(), color.blueF(), 0.5);
                    glBegin(GL_LINES);
                    glVertex3f(p1.x(), p1.y(), p1.z());
                    glVertex3f(c1.x(), c1.y(), c1.z());
                    glEnd();

                    NxPoint p2 = getPathPointsAt(indexPoint+1), c2 = p2 + getPathPointsAt(indexPoint+1).c2;
                    if(selectedPathPointControl2 == indexPoint+1)
                        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
                    else
                        glColor4f(color.redF(), color.greenF(), color.blueF(), 0.5);
                    glBegin(GL_LINES);
                    glVertex3f(p2.x(), p2.y(), p2.z());
                    glVertex3f(c2.x(), c2.y(), c2.z());
                    glEnd();
                }
            }
        }

        //End
        glPopMatrix();
    }
}

void NxCurve::addMousePointAt(const NxPoint & _mousePos, bool remove) {
    NxRect mouseRect = NxRect(_mousePos - NxPoint(renderOptions->objectSize/2, renderOptions->objectSize/2, renderOptions->objectSize/2), _mousePos + NxPoint(renderOptions->objectSize/2, renderOptions->objectSize/2, renderOptions->objectSize/2));

    for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++) {
        if(mouseRect.contains(pos + pathPoints[indexPoint])) {
            if(remove)
                removePointAt(indexPoint);
            else {
                if(pathPoints[indexPoint].smooth) {
                    pathPoints[indexPoint].smooth = false;
                    pathPoints[indexPoint].c2 = NxPoint();
                    if(indexPoint < pathPoints.count()) {
                        pathPoints[indexPoint+1].smooth = false;
                        pathPoints[indexPoint+1].c1 = NxPoint();
                    }
                }
                else
                    pathPoints[indexPoint].smooth = true;
                setPointAt(0, getPathPointsAt(0), getPathPointsAt(0).c1, getPathPointsAt(0).c2, getPathPointsAt(0).smooth);
            }
            return;
        }
    }

    NxPoint collistionPoint;
    qreal lengthTarget = intersects(mouseRect, &collistionPoint);
    if(lengthTarget >= 0) {
        qreal length = 0;
        lengthTarget *= pathLength;
        for(quint16 indexPoint = 1 ; indexPoint < pathPoints.count() ; indexPoint++) {
            length = getPathPointsAt(indexPoint).currentLength;
            if(length >= lengthTarget) {
                NxCurvePoint pt;
                pt.setX(collistionPoint.x());
                pt.setY(collistionPoint.y());
                pt.setZ(collistionPoint.z());
                pt.c1 = NxPoint(0, 0, 0);
                pt.c2 = NxPoint(0, 0, 0);
                pt -= pos;
                if(indexPoint < pathPoints.count()) {
                    pathPoints.insert(indexPoint, pt);
                    pathPoints[indexPoint].smooth = pathPoints[indexPoint+1].smooth;
                }
                else {
                    pathPoints.append(pt);
                    pathPoints[indexPoint].smooth = pathPoints[indexPoint-1].smooth;
                }
                setPointAt(0, getPathPointsAt(0), getPathPointsAt(0).c1, getPathPointsAt(0).c2, getPathPointsAt(0).smooth);
                calcBoundingRect();
                return;
            }
        }
    }
}

void NxCurve::removePointAt(quint16 index) {
    if((pathPoints.count() > 2) && (index < pathPoints.count()))
        pathPoints.remove(index);

    //Length
    calcBoundingRect();
}

const void NxCurve::shiftPointAt(quint16 index, qint8 direction, bool boundingRectCalculation) {
    if(index < pathPoints.count()) {
        qint16 indexPoint;
        if((direction < 0) && (index > 1)) {
            NxPoint ptDelta = pathPoints[index] - pathPoints[index-1];
            pathPoints.remove(index);
            for(indexPoint = (index-1) ; indexPoint >= 0 ; indexPoint--)
                setPointAt(indexPoint, pathPoints[indexPoint] + ptDelta, pathPoints[indexPoint].c1, pathPoints[indexPoint].c2, pathPoints[indexPoint].smooth, false);
        }
        else if((direction >= 0) && (index < pathPoints.count()-1)) {
            NxPoint ptDelta = pathPoints[index] - pathPoints[index+1];
            pathPoints.remove(index);
            for(indexPoint = index ; indexPoint < pathPoints.count() ; indexPoint++)
                setPointAt(indexPoint, pathPoints[indexPoint] + ptDelta, pathPoints[indexPoint].c1, pathPoints[indexPoint].c2, pathPoints[indexPoint].smooth, false);
        }
    }
    if(boundingRectCalculation)
        calcBoundingRect();
}
const NxPoint & NxCurve::setPointAt(quint16 index, const NxPoint & point, bool smooth, bool boundingRectCalculation) {
    return setPointAt(index, point, NxPoint(), NxPoint(), smooth, boundingRectCalculation);
}
const NxPoint & NxCurve::setPointAt(quint16 index, const NxPoint & point, const NxPoint & c1, const NxPoint & c2, bool smooth, bool boundingRectCalculation) {
    NxCurvePoint pointStruct;
    pointStruct.setX(point.x());
    pointStruct.setY(point.y());
    pointStruct.setZ(point.z());
    pointStruct.setSx(point.sx());
    pointStruct.setSy(point.sy());
    pointStruct.setSz(point.sz());
    pointStruct.c1 = c1;
    pointStruct.c2 = c2;
    pointStruct.smooth = smooth;
    if(index >= pathPoints.count())
        pathPoints.append(pointStruct);
    else
        pathPoints[index] = pointStruct;


    //NxPoint ptBefore;
    for(quint16 indexPathPoint = 1 ; indexPathPoint < pathPoints.count()-1 ; indexPathPoint++) {
        if(getPathPointsAt(indexPathPoint).smooth) {
            NxPoint ptBefore = getPathPointsAt(indexPathPoint - 1);
            NxPoint pt       = getPathPointsAt(indexPathPoint);
            NxPoint ptAfter  = getPathPointsAt(indexPathPoint + 1);
            NxPoint ptDelta  = (ptAfter - ptBefore) / 4;
            //qreal distanceBefore = qSqrt((pt-ptBefore).x()*(pt-ptBefore).x() + (pt-ptBefore).y()*(pt-ptBefore).y() + (pt-ptBefore).z()*(pt-ptBefore).z());
            //qreal distanceAfter  = qSqrt((pt-ptAfter).x()*(pt-ptAfter).x() + (pt-ptAfter).y()*(pt-ptAfter).y() + (pt-ptAfter).z()*(pt-ptAfter).z());
            pathPoints[indexPathPoint].c2   = -ptDelta;// * (distanceBefore / (distanceBefore + distanceAfter));
            pathPoints[indexPathPoint+1].c1 =  ptDelta;// * (distanceAfter  / (distanceBefore + distanceAfter));
            ptBefore = pt;
        }
    }


    //Length
    if(boundingRectCalculation)
        calcBoundingRect();

    return point;
}

void NxCurve::setSVG(const QString & pathData) {
    curveType = CurveTypePoints;
    pathPoints.clear();

    QStringList tokens = pathData.split(QRegExp("(?=[A-Za-z])"), QString::SkipEmptyParts);
    quint16 index = 0;
    NxPoint currentPoint = NxPoint();
    NxPoint firstPoint;
    foreach(QString token, tokens) {
        QString command = "";
        char svgCommand = token.at(0).toLatin1();
        command += token.left(1) + " ";
        token.remove(0, 1);
        token.replace("-", ",-");
        token.replace(" ", ",");
        QList<qreal> params;
        QStringList tokenParams = token.split(",", QString::SkipEmptyParts);
        foreach(const QString & tokenParam, tokenParams) {
            command += tokenParam + " , ";
            params.append(tokenParam.toDouble());
        }

        switch(svgCommand) {
        case 'C':
            //Cubic curve to
            currentPoint = setPointAt(index, NxPoint(params.at(4), params.at(5)), NxPoint(params.at(0), params.at(1)) - NxPoint(params.at(4), params.at(5)), NxPoint(params.at(2), params.at(3)) - NxPoint(params.at(4), params.at(5)), false);
            break;
        case 'c':
            //Cubic curve to
            currentPoint = setPointAt(index, currentPoint + NxPoint(params.at(4), params.at(5)), NxPoint(params.at(0), params.at(1)) - NxPoint(params.at(4), params.at(5)), NxPoint(params.at(2), params.at(3)) - NxPoint(params.at(4), params.at(5)), false);
            break;
        case 'H':
            //Horizontal line to
            currentPoint = setPointAt(index, NxPoint(params.at(0), currentPoint.y()), NxPoint(), NxPoint(), false);
            break;
        case 'h':
            //Horizontal line to
            currentPoint = setPointAt(index, currentPoint + NxPoint(params.at(0), 0), NxPoint(), NxPoint(), false);
            break;
        case 'L':
            //Line to
            currentPoint = setPointAt(index, NxPoint(params.at(0), params.at(1)), NxPoint(), NxPoint(), false);
            break;
        case 'l':
            //Line to
            currentPoint = setPointAt(index, currentPoint + NxPoint(params.at(0), params.at(1)), NxPoint(), NxPoint(), false);
            break;
        case 'M':
            //Move to
            currentPoint = setPointAt(index, NxPoint(params.at(0), params.at(1)), NxPoint(), NxPoint(), false);
            break;
        case 'm':
            //Move to
            currentPoint = setPointAt(index, currentPoint + NxPoint(params.at(0), params.at(1)), NxPoint(), NxPoint(), false);
            break;
        case 'V':
            //Vertical line to
            currentPoint = setPointAt(index, NxPoint(currentPoint.x(), params.at(0)), NxPoint(), NxPoint(), false);
            break;
        case 'v':
            //Vertical line to
            currentPoint = setPointAt(index, currentPoint + NxPoint(0, params.at(0)), NxPoint(), NxPoint(), false);
            break;

        case 'Z':
        case 'z':
            setPointAt(index++, firstPoint, false);
            break;

        case 'A':
            //qDebug("arcAbs");
            break;
        case 'a':
            //qDebug("arcRel");
            break;

        case 'Q':
            //qDebug("curvetoQuadraticAbs");
            break;
        case 'q':
            //qDebug("curvetoQuadraticRel");
            break;

        case 'S':
            //qDebug("curvetoCubicSmoothAbs");
            break;
        case 's':
            //qDebug("curvetoCubicSmoothRel");
            break;

        case 'T':
            //qDebug("curvetoQuadraticSmoothAbs");
            break;
        case 't':
            //qDebug("curvetoQuadraticSmoothRel");
            break;
        }
        if(index == 0)
            firstPoint = currentPoint;
        index++;
    }

    //Scale
    resize(1, -1);
    calcBoundingRect();
}
void NxCurve::setSVG2(const QString & polylineData) {
    curveType = CurveTypePoints;
    pathPoints.clear();

    QStringList tokens = polylineData.split(" ", QString::SkipEmptyParts);
    quint16 index = 0;
    foreach(const QString & token, tokens) {
        QStringList tokenParams = token.split(",", QString::SkipEmptyParts);
        if(tokenParams.count() == 2)
            setPointAt(index++, NxPoint(tokenParams.at(0).toDouble(), tokenParams.at(1).toDouble()), NxPoint(), NxPoint(), false);
    }

    //Scale
    resize(1, 1);
    calcBoundingRect();
}

void NxCurve::setImage(const QString & filename) {
    curveType = CurveTypePoints;

    //Load image
    QFileInfo file(filename);
    QPixmap pixmap(filename);

    //Create mask
    QBitmap bitmap(pixmap.createHeuristicMask());
    //bitmap.save(file.dir().absolutePath() + QDir::separator() + file.baseName() + "_mask.png");

    //Create path
    pathPoints.clear();
    QPainterPath pathTmp = QPainterPath();
    pathTmp.addRegion(QRegion(bitmap));

    //Simplify path
    setPath(pathTmp.simplified());

    //Scale
    resize(1, -1);
    calcBoundingRect();
}
void NxCurve::setEllipse(const NxSize & size) {
    curveType = CurveTypeEllipse;
    ellipseSize = size;

    //Draw ellipse
    pathPoints.clear();
    /*
    curveType = CurveTypePoints;
    qreal kappa = 0.5522847498308;
    quint16 index = 0;
    setPointAt(index++, NxPoint( 1,  0));
    setPointAt(index++, NxPoint( 0,  1), NxPoint(0, kappa),  NxPoint(kappa, 0));
    setPointAt(index++, NxPoint(-1,  0), NxPoint(-kappa, 0), NxPoint(0, kappa));
    setPointAt(index++, NxPoint( 0, -1), NxPoint(0, -kappa), NxPoint(-kappa, 0));
    setPointAt(index++, NxPoint( 1,  0), NxPoint(kappa, 0),  NxPoint(0, -kappa));
    */

    //Calculations
    resize(1, 1);
    calcBoundingRect();
}

void NxCurve::setText(const QString & text, const QString & family) {
    curveType = CurveTypePoints;
    QFont font(family);
    font.setPixelSize(50);

    //Draw text
    QPainterPath pathTmp = QPainterPath();
    pathTmp.addText(0, 0, font, text);
    setPath(pathTmp);
}

void NxCurve::setPath(const QPainterPath &path) {
    pathPoints.clear();
    quint16 index = 0;
    for(quint16 elementIndex = 0 ; elementIndex < path.elementCount() ; elementIndex++) {
        const QPainterPath::Element &e = path.elementAt(elementIndex);
        switch (e.type) {
        case QPainterPath::MoveToElement:
        {
            setPointAt(index++, NxPoint(e.x, e.y), NxPoint(), NxPoint(), false);
            break;
        }
        case QPainterPath::LineToElement:
        {
            setPointAt(index++, NxPoint(e.x, e.y), NxPoint(), NxPoint(), false);
            break;
        }
        case QPainterPath::CurveToElement:
        {
            const QPainterPath::Element &p1 = path.elementAt(elementIndex-1);
            const QPainterPath::Element &c1 = e;
            const QPainterPath::Element &c2 = path.elementAt(elementIndex+1);
            const QPainterPath::Element &p2 = path.elementAt(elementIndex+2);
            setPointAt(index++, NxPoint(p2.x, p2.y), NxPoint(c1.x - p1.x, c1.y - p1.y), NxPoint(c2.x - p2.x, c2.y - p2.y), false);
            elementIndex += 2;
            break;
        }
        default:
            break;
        }
    }

    //Calculations
    resize(1, -1);
    calcBoundingRect();
}

void NxCurve::resize(qreal sizeFactorW, qreal sizeFactorH) {
    NxSize sizeFactor(sizeFactorW, sizeFactorH);
    if(curveType == CurveTypeEllipse) {
        ellipseSize.setWidth(ellipseSize.width()   * sizeFactorW);
        ellipseSize.setHeight(ellipseSize.height() * sizeFactorH);
    }
    else {
        for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++)
            setPointAt(indexPoint, NxPoint(getPathPointsAt(indexPoint).x() * sizeFactor.width(), getPathPointsAt(indexPoint).y() * sizeFactor.height()), NxPoint(getPathPointsAt(indexPoint).c1.x() * sizeFactor.width(), getPathPointsAt(indexPoint).c1.y() * sizeFactor.height()), NxPoint(getPathPointsAt(indexPoint).c2.x() * sizeFactor.width(), getPathPointsAt(indexPoint).c2.y() * sizeFactor.height()), getPathPointsAt(indexPoint).smooth, false);
    }
    calcBoundingRect();
}
void NxCurve::resize(const NxSize & size) {
    calcBoundingRect();
    NxSize sizeFactor(size.width() / boundingRect.width(), size.height() / boundingRect.height());
    resize(sizeFactor.width(), sizeFactor.height());
}
void NxCurve::translate(const NxPoint & point) {
    for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++)
        setPointAt(indexPoint, getPathPointsAt(indexPoint) + point, getPathPointsAt(indexPoint).c1, getPathPointsAt(indexPoint).c2, getPathPointsAt(indexPoint).smooth, false);
    calcBoundingRect();
}


inline NxPoint NxCurve::getPointAt(quint16 index, qreal t) {
    NxPoint p1 = getPathPointsAt(index), p2 = getPathPointsAt(index+1);
    NxPoint c1 = getPathPointsAt(index+1).c1, c2 = getPathPointsAt(index+1).c2;
    qreal mt = 1 - t;
    if((c1 == NxPoint()) && (c2 == NxPoint())) {
        return NxPoint( p1. x()*mt + p2. x()*t,
                        p1. y()*mt + p2. y()*t,
                        p1. z()*mt + p2. z()*t,
                        p1.sx()*mt + p2.sx()*t,
                        p1.sy()*mt + p2.sy()*t,
                        p1.sz()*mt + p2.sz()*t);
    }
    else {
        NxPoint p1c = p1 + c1, p2c = p2 + c2;
        qreal t2 = t*t, t3 = t2*t, mt2 = mt*mt, mt3 = mt2*mt;
        return NxPoint( p1. x()*mt3 + 3*p1c. x()*t*mt2 + 3*p2c. x()*t2*mt + p2. x()*t3,
                        p1. y()*mt3 + 3*p1c. y()*t*mt2 + 3*p2c. y()*t2*mt + p2. y()*t3,
                        p1. z()*mt3 + 3*p1c. z()*t*mt2 + 3*p2c. z()*t2*mt + p2. z()*t3,
                        p1.sx()*mt3 + 3*p1c.sx()*t*mt2 + 3*p2c.sx()*t2*mt + p2.sx()*t3,
                        p1.sy()*mt3 + 3*p1c.sy()*t*mt2 + 3*p2c.sy()*t2*mt + p2.sy()*t3,
                        p1.sz()*mt3 + 3*p1c.sz()*t*mt2 + 3*p2c.sz()*t2*mt + p2.sz()*t3);
    }
}

NxPoint NxCurve::getPointAt(qreal percent) {
    if(curveType == CurveTypeEllipse) {
        qreal angle = 2 * percent * M_PI;
        return NxPoint(boundingRect.width() * qCos(angle) / 2, boundingRect.height() * qSin(angle) / 2, 0);
    }
    else {
        qreal length = 0, lengthOld = 0, lengthTarget = pathLength * percent;
        quint16 index = 0;
        for(quint16 indexPoint = 1 ; indexPoint < pathPoints.count() ; indexPoint++) {
            length = getPathPointsAt(indexPoint).currentLength;
            if(length >= lengthTarget) {
                index = indexPoint - 1;
                break;
            }
            lengthOld = length;
        }
        return getPointAt(index, (lengthTarget - lengthOld) / (length - lengthOld));
    }
}
qreal NxCurve::getAngleAt(qreal percent) {
    qreal angle = 0;
    if(curveType == CurveTypeEllipse)
        angle = -((2 * percent * M_PI) + M_PI_2) * 180.0F / M_PI;
    else {
        NxPoint deltaPos = getPointAt(percent+0.001) - getPointAt(percent);
        if((deltaPos.x() > 0) && (deltaPos.y() >= 0))
            angle = qAtan(deltaPos.y() / deltaPos.x());
        else if((deltaPos.x() <= 0) && (deltaPos.y() > 0))
            angle = -qAtan(deltaPos.x() / deltaPos.y()) + M_PI_2;
        else if((deltaPos.x() < 0) && (deltaPos.y() <= 0))
            angle = qAtan(deltaPos.y() / deltaPos.x()) + M_PI;
        else if((deltaPos.x() >= 0) && (deltaPos.y() < 0))
            angle = -qAtan(deltaPos.x() / deltaPos.y()) + 3 * M_PI_2;

        angle = -angle * 180.0F / M_PI;
    }
    return angle;
}


void NxCurve::calcBoundingRect() {
    pathLength = 0;
    if(curveType == CurveTypeEllipse) {
        //Longueur
        pathLength = M_PI * qSqrt(0.5 * (boundingRect.width()*boundingRect.width() + boundingRect.height()*boundingRect.height()));

        //Bounding
        boundingRect = NxRect(-ellipseSize.width(), -ellipseSize.height(), 2*ellipseSize.width(), 2*ellipseSize.height());
    }
    else {
        qreal step = 0.05;
        NxPoint minGlobal(9999,9999,9999,9999), maxGlobal(-9999,-9999,-9999,-9999);
        for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count()-1 ; indexPoint++) {
            NxPoint min(9999,9999,9999,9999), max(-9999,-9999,-9999,-9999);
            for(qreal t = 0 ; t <= 1+step ; t += step) {
                //Longueur
                NxPoint pt = getPointAt(indexPoint, t), delta = getPointAt(indexPoint, t + step) - pt;
                if(t <= 1)
                    pathLength += qSqrt((delta.x()*delta.x()) + (delta.y()*delta.y()) + (delta.z()*delta.z()));

                //Bounding local
                if(pt.x() < min.x())  min.setX(pt.x());
                if(pt.y() < min.y())  min.setY(pt.y());
                if(pt.z() < min.z())  min.setZ(pt.z());
                if(pt.x() > max.x())  max.setX(pt.x());
                if(pt.y() > max.y())  max.setY(pt.y());
                if(pt.z() > max.z())  max.setZ(pt.z());
            }
            pathPoints[indexPoint+1].currentLength = pathLength;
            if(min.x() == max.x())  max.setX(max.x() + 0.001);
            if(min.y() == max.y())  max.setY(max.y() + 0.001);
            if(min.z() == max.z())  max.setZ(max.z() + 0.001);
            pathPoints[indexPoint+1].boundingRect = NxRect(min, max).translated(pos);

            //Bounding général
            if(min.x() < minGlobal.x())  minGlobal.setX(min.x());
            if(min.y() < minGlobal.y())  minGlobal.setY(min.y());
            if(min.z() < minGlobal.z())  minGlobal.setZ(min.z());
            if(max.x() > maxGlobal.x())  maxGlobal.setX(max.x());
            if(max.y() > maxGlobal.y())  maxGlobal.setY(max.y());
            if(max.z() > maxGlobal.z())  maxGlobal.setZ(max.z());
        }
        boundingRect = NxRect(minGlobal, maxGlobal);
    }
    boundingRect.translate(pos);
    boundingRect = boundingRect.normalized();
}


bool NxCurve::isMouseHover(const NxPoint &mouse) {
    NxRect mouseRect = NxRect(mouse - NxPoint(renderOptions->objectSize/2, renderOptions->objectSize/2, renderOptions->objectSize/2), mouse + NxPoint(renderOptions->objectSize/2, renderOptions->objectSize/2, renderOptions->objectSize/2));
    if(intersects(mouseRect) >= 0)
        return true;
    else if(selected) {
        for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
            NxPoint pt = pos + getPathPointsAt(indexPathPoint);
            NxPoint c2 = pt + getPathPointsAt(indexPathPoint).c2;

            if(mouseRect.contains(pt))
                return true;
            else if(mouseRect.contains(c2))
                return true;

            if(indexPathPoint > 0) {
                NxPoint c1 = pos + getPathPointsAt(indexPathPoint-1) + getPathPointsAt(indexPathPoint).c1;
                if(mouseRect.contains(c1))
                    return true;
            }
        }
    }
    return false;
}

qreal NxCurve::intersects(NxRect rect, NxPoint* collisionPoint) {
    qreal step = 0.001;
    if(curveType == CurveTypeEllipse) {
        if(boundingRect.intersects(rect)) {
            for(qreal t = 0 ; t <= 1+step ; t += step) {
                NxPoint pt1 = getPointAt(t), pt2 = getPointAt(t+step);
                NxRect rectCurve = NxRect(pt1, pt2).translated(pos);
                if(rectCurve.width()  == 0)  rectCurve.setWidth(0.001);
                if(rectCurve.height() == 0)  rectCurve.setHeight(0.001);
                if(rectCurve.length() == 0)  rectCurve.setLength(0.001);
                if(rectCurve.intersects(rect)) {
                    if(collisionPoint)
                        *collisionPoint = (pt1+pt2)/2 + pos;
                    return t;
                }
            }
        }
    }
    else {
        if(boundingRect.intersects(rect)) {
            for(quint16 indexPathPoint = 1 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
                if(getPathPointsAt(indexPathPoint).boundingRect.intersects(rect)) {
                    for(qreal t = 0 ; t <= 1+step ; t += step) {
                        NxPoint pt1 = getPointAt(indexPathPoint-1, t), pt2 = getPointAt(indexPathPoint-1, t+step);
                        NxRect rectCurve = NxRect(pt1, pt2).translated(pos);
                        if(rectCurve.width()  == 0)  rectCurve.setWidth(0.001);
                        if(rectCurve.height() == 0)  rectCurve.setHeight(0.001);
                        if(rectCurve.length() == 0)  rectCurve.setLength(0.001);
                        if(rectCurve.intersects(rect)) {
                            if(collisionPoint)
                                *collisionPoint = (pt1+pt2)/2 + pos;
                            return (getPathPointsAt(indexPathPoint-1).currentLength + (getPathPointsAt(indexPathPoint).currentLength - getPathPointsAt(indexPathPoint-1).currentLength) * t) / pathLength;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void NxCurve::isOnPathPoint(const NxRect & point) {
    if(!isDrag) {
        selectedPathPointPoint = -1;
        selectedPathPointControl1 = -1;
        selectedPathPointControl2 = -1;
        for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
            NxPoint pt = getPathPointsAt(indexPathPoint);
            NxPoint c2 = pt + getPathPointsAt(indexPathPoint).c2;

            if(point.contains(pt)) {
                selectedPathPointPoint = indexPathPoint;
                break;
            }
            else if(point.contains(c2)) {
                selectedPathPointControl2 = indexPathPoint;
                break;
            }

            if(indexPathPoint > 0) {
                NxPoint c1 = getPathPointsAt(indexPathPoint-1) + getPathPointsAt(indexPathPoint).c1;
                if(point.contains(c1)) {
                    selectedPathPointControl1 = indexPathPoint;
                    break;
                }
            }
        }
    }
}
