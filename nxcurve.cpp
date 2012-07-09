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

Q_CORE_EXPORT double qstrtod(const char *s00, char const **se, bool *ok);


NxCurve::NxCurve(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
    NxObject(parent, ccParentItem, _renderOptions) {
    calcBoundingRect();
    glListCurve = glGenLists(1);
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
NxCurve::~NxCurve() {
    glDeleteLists(glListCurve, 1);
}

void NxCurve::paint() {
#ifdef KINECT_INSTALLED

#endif

    //Color
    if(active)
        color = (!colorActive.isEmpty())?(renderOptions->colors.value(colorActive)):(colorActiveColor);
    else
        color = (!colorInactive.isEmpty())?(renderOptions->colors.value(colorInactive)):(colorInactiveColor);

    if(color.alpha() > 0) {
        //Mouse hover
        if(selectedHover)
            color = renderOptions->colors.value("object_hover");
        if(selected)
            color = renderOptions->colors.value("object_selection");

        //Hide curve if a cursor is present but inactive
        if((renderOptions->paintCurvesOpacity) && (cursors.count() > 0)) {
            bool display = false;
            foreach(const NxObject *cursor, cursors)
                if(cursor->getHasActivity()) {
                    display = true;
                    break;
                }
            if(!display)
                color.setAlpha(color.alpha() / 4);
        }

        //Start
        bool opacityCheck = (renderOptions->paintCurves) && (renderOptions->paintThisGroup) && ((renderOptions->paintZStart <= pos.z()) && (pos.z() <= renderOptions->paintZEnd));

        if(!renderOptions->allowSelectionCurves)
            color.setAlphaF(color.alphaF()/3);

        if(opacityCheck)
            glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        else
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.1);

        glPushMatrix();
        glTranslatef(pos.x(), pos.y(), pos.z());

        //Label
        if((opacityCheck) && (renderOptions->paintLabel) && (!label.isEmpty())) {
            NxPoint pt = getPathPointsAt(0);
            renderOptions->render->renderText(pt.x(), pt.y(), pt.z(), label, renderOptions->renderFont);
        }

        //Draw
        if((glListRecreate) || (renderOptions->forceLists)) {
            glNewList(glListCurve, GL_COMPILE_AND_EXECUTE);
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
                        NxPoint _c1 = getPathPointsAt(indexPoint+1).c1, _c2 = getPathPointsAt(indexPoint+1).c2;
                        NxPoint c1 = p1 + _c1, c2 = p2 + _c2;

                        if((_c1 == NxPoint()) && (_c2 == NxPoint())) {
                            glBegin(GL_LINES);
                            glVertex3f(p1.x(), p1.y(), p1.z());
                            glVertex3f(p2.x(), p2.y(), p2.z());
                            glEnd();
                        }
                        else {
                            GLfloat ctrlpoints[4][3] = {
                                { p1.x(), p1.y(), p1.z() }, { c1.x(), c1.y(), c1.z() },
                                { c2.x(), c2.y(), c2.z() }, { p2.x(), p2.y(), p2.z() } };
                            glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
                            glEnable(GL_MAP1_VERTEX_3);
                            glBegin(GL_LINE_STRIP);
                            for(GLfloat t = 0.0f ; t <= 1.0f ; t += 0.02f)
                                glEvalCoord1f(t);
                            glEnd();
                            glDisable(GL_MAP1_VERTEX_3);
                        }

                        //if((selected) && (indexPoint == selectedPathPointPoint))
                        //    renderOptions->render->renderText(p1.x(), p1.y(), p1.z(), QString::number(indexPoint), renderOptions->renderFont);
                    }
                }
            }
            glDisable(GL_LINE_STIPPLE);
            glEndList();
            glListRecreate = false;
        }
        else
            glCallList(glListCurve);

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
                qreal squareSize = (0.15 * renderOptions->zoomLinear) / 4;
                glVertex3f(p1.x() - squareSize, p1.y() - squareSize, p1.z());
                glVertex3f(p1.x() + squareSize, p1.y() - squareSize, p1.z());
                glVertex3f(p1.x() + squareSize, p1.y() + squareSize, p1.z());
                glVertex3f(p1.x() - squareSize, p1.y() + squareSize, p1.z());
                glEnd();


                if((indexPoint+1) < pathPoints.count()) {
                    NxPoint c1 = p1 + getPathPointsAt(indexPoint+1).c1;
                    /*if(selectedPathPointControl1 >= 0)
                        qDebug("%d", selectedPathPointControl1);*/
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
    glListRecreate = true;
    if((pathPoints.count() > 2) && (index < pathPoints.count()))
        pathPoints.removeAt(index);

    //Length
    calcBoundingRect();
}

void NxCurve::shiftPointAt(quint16 index, qint8 direction, bool boundingRectCalculation) {
    if(index < pathPoints.count()) {
        qint16 indexPoint;
        if((direction < 0) && (index > 1)) {
            NxPoint ptDelta = pathPoints[index] - pathPoints[index-1];
            pathPoints.removeAt(index);
            for(indexPoint = (index-1) ; indexPoint >= 0 ; indexPoint--)
                setPointAt(indexPoint, pathPoints[indexPoint] + ptDelta, pathPoints[indexPoint].c1, pathPoints[indexPoint].c2, pathPoints[indexPoint].smooth, false);
        }
        else if((direction >= 0) && (index < pathPoints.count()-1)) {
            NxPoint ptDelta = pathPoints[index] - pathPoints[index+1];
            pathPoints.removeAt(index);
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
    glListRecreate = true;
    if(index >= pathPoints.count()) {
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
        pathPoints.append(pointStruct);
    }
    else {
        pathPoints[index].setX(point.x());
        pathPoints[index].setY(point.y());
        pathPoints[index].setZ(point.z());
        pathPoints[index].setSx(point.sx());
        pathPoints[index].setSy(point.sy());
        pathPoints[index].setSz(point.sz());
        pathPoints[index].c1 = c1;
        pathPoints[index].c2 = c2;
        pathPoints[index].smooth = smooth;
    }


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

    QPainterPath pathTmp = QPainterPath();
    parsePathDataFast(pathData, pathTmp);
    setPath(pathTmp);
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
}
void NxCurve::setEllipse(const NxSize & size) {
    curveType = CurveTypeEllipse;
    ellipseSize = size;

    //Draw ellipse
    pathPoints.clear();

    //Calculations
    calcBoundingRect();
    resize(1, 1);
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
    //calcBoundingRect();
    NxSize sizeFactor(size.width() / boundingRect.width(), size.height() / boundingRect.height());
    resize(sizeFactor.width(), sizeFactor.height());
}
void NxCurve::translate(const NxPoint & point) {
    for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++)
        setPointAt(indexPoint, getPathPointsAt(indexPoint) + point, getPathPointsAt(indexPoint).c1, getPathPointsAt(indexPoint).c2, getPathPointsAt(indexPoint).smooth, false);
    calcBoundingRect();
}

void NxCurve::translatePoint(quint16 indexPoint, const NxPoint &point) {
    setPointAt(indexPoint, getPathPointsAt(indexPoint) + point, getPathPointsAt(indexPoint).c1, getPathPointsAt(indexPoint).c2, getPathPointsAt(indexPoint).smooth, false);
}


inline NxPoint NxCurve::getPointAt(quint16 index, qreal t) const {
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

NxPoint NxCurve::getPointAt(qreal val, bool absoluteTime) const {
    if(curveType == CurveTypeEllipse) {
        qreal angle = 2 * val * M_PI;
        return NxPoint(boundingRect.width() * qCos(angle) / 2, boundingRect.height() * qSin(angle) / 2, 0);
    }
    else {
        qreal length = 0, lengthOld = 0;
        qreal lengthTarget = (absoluteTime)?(val):(pathLength * val);
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
qreal NxCurve::getAngleAt(qreal val, bool absoluteTime) const {
    qreal angle = 0;
    if(curveType == CurveTypeEllipse)
        angle = -((2 * val * M_PI) + M_PI_2) * 180.0F / M_PI;
    else {
        NxPoint deltaPos = getPointAt(val - 0.001, absoluteTime) - getPointAt(val, absoluteTime);
        if((deltaPos.x() > 0) && (deltaPos.y() >= 0))
            angle = qAtan(deltaPos.y() / deltaPos.x());
        else if((deltaPos.x() <= 0) && (deltaPos.y() > 0))
            angle = -qAtan(deltaPos.x() / deltaPos.y()) + M_PI_2;
        else if((deltaPos.x() < 0) && (deltaPos.y() <= 0))
            angle = qAtan(deltaPos.y() / deltaPos.x()) + M_PI;
        else if((deltaPos.x() >= 0) && (deltaPos.y() < 0))
            angle = -qAtan(deltaPos.x() / deltaPos.y()) + 3 * M_PI_2;

        angle = -angle * 180.0F / M_PI + 180;
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
        qreal step = 0.01;
        NxPoint minGlobal(9999,9999,9999,9999), maxGlobal(-9999,-9999,-9999,-9999);
        for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count()-1 ; indexPoint++) {
            NxPoint min(9999,9999,9999,9999), max(-9999,-9999,-9999,-9999);
            NxPoint pt = getPointAt(indexPoint, 0);
            for(qreal t = 0 ; t <= 1+step ; t += step) {
                //Longueur
                NxPoint ptNext = getPointAt(indexPoint, t + step);
                NxPoint delta  = ptNext - pt;
                if(t <= 1)
                    pathLength += qSqrt((delta.x()*delta.x()) + (delta.y()*delta.y()) + (delta.z()*delta.z()));

                //Bounding local
                if(pt.x() < min.x())  min.setX(pt.x());
                if(pt.y() < min.y())  min.setY(pt.y());
                if(pt.z() < min.z())  min.setZ(pt.z());
                if(pt.x() > max.x())  max.setX(pt.x());
                if(pt.y() > max.y())  max.setY(pt.y());
                if(pt.z() > max.z())  max.setZ(pt.z());
                pt = ptNext;
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

qreal NxCurve::intersects(const NxRect &rect, NxPoint* collisionPoint) const {
    qreal step = 0.001;
    NxRect rectCursor = rect;
    if(rectCursor.width()  == 0)  rectCursor.setWidth(0.001);
    if(rectCursor.height() == 0)  rectCursor.setHeight(0.001);
    if(rectCursor.length() == 0)  rectCursor.setLength(0.001);
    if(curveType == CurveTypeEllipse) {
        if(boundingRect.intersects(rectCursor)) {
            NxPoint pt1 = getPointAt(0);
            for(qreal t = 0 ; t <= 1+step ; t += step) {
                NxPoint pt2 = getPointAt(t+step);
                NxRect rectCurve = NxRect(pt1, pt2).translated(pos);
                if(rectCurve.width()  == 0)  rectCurve.setWidth(0.001);
                if(rectCurve.height() == 0)  rectCurve.setHeight(0.001);
                if(rectCurve.length() == 0)  rectCurve.setLength(0.001);
                if(rectCurve.intersects(rectCursor)) {
                    if(collisionPoint)
                        *collisionPoint = (pt1+pt2)/2 + pos;
                    return t;
                }
                pt1 = pt2;
            }
        }
    }
    else {
        if(boundingRect.intersects(rectCursor)) {
            for(quint16 indexPathPoint = 1 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
                if(getPathPointsAt(indexPathPoint).boundingRect.intersects(rectCursor)) {
                    NxPoint pt1 = getPointAt(indexPathPoint-1, (qreal)0);
                    for(qreal t = 0 ; t <= 1+step ; t += step) {
                        NxPoint pt2 = getPointAt(indexPathPoint-1, t+step);
                        NxRect rectCurve = NxRect(pt1, pt2).translated(pos);
                        if(rectCurve.width()  == 0)  rectCurve.setWidth(0.001);
                        if(rectCurve.height() == 0)  rectCurve.setHeight(0.001);
                        if(rectCurve.length() == 0)  rectCurve.setLength(0.001);
                        if(rectCurve.intersects(rectCursor)) {
                            if(collisionPoint)
                                *collisionPoint = (pt1+pt2)/2 + pos;
                            return (getPathPointsAt(indexPathPoint-1).currentLength + (getPathPointsAt(indexPathPoint).currentLength - getPathPointsAt(indexPathPoint-1).currentLength) * t) / pathLength;
                        }
                        pt1 = pt2;
                    }
                }
            }
        }
    }
    return -1;
}

void NxCurve::resample(quint16 nbPoints) {
    qreal percentStep = 1.0 / (qreal)nbPoints;
    QList<NxPoint> pts;
    for(qreal percent = 0 ; percent <= 1 ; percent += percentStep)
        pts.append(getPointAt(percent));
    pathPoints.clear();
    foreach(const NxPoint &pt, pts) {
        NxCurvePoint cPt;
        cPt.setX(pt.x());
        cPt.setY(pt.y());
        cPt.setZ(pt.z());
        pathPoints.append(cPt);
    }
    curveType = CurveTypePoints;
    calcBoundingRect();
    glListRecreate = true;
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





/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSvg module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
void pathArcSegment(QPainterPath &path,
                           qreal xc, qreal yc,
                           qreal th0, qreal th1,
                           qreal rx, qreal ry, qreal xAxisRotation)
{
    qreal sinTh, cosTh;
    qreal a00, a01, a10, a11;
    qreal x1, y1, x2, y2, x3, y3;
    qreal t;
    qreal thHalf;

    sinTh = qSin(xAxisRotation * (M_PI / 180.0));
    cosTh = qCos(xAxisRotation * (M_PI / 180.0));

    a00 =  cosTh * rx;
    a01 = -sinTh * ry;
    a10 =  sinTh * rx;
    a11 =  cosTh * ry;

    thHalf = 0.5 * (th1 - th0);
    t = (8.0 / 3.0) * qSin(thHalf * 0.5) * qSin(thHalf * 0.5) / qSin(thHalf);
    x1 = xc + qCos(th0) - t * qSin(th0);
    y1 = yc + qSin(th0) + t * qCos(th0);
    x3 = xc + qCos(th1);
    y3 = yc + qSin(th1);
    x2 = x3 + t * qSin(th1);
    y2 = y3 - t * qCos(th1);

    path.cubicTo(a00 * x1 + a01 * y1, a10 * x1 + a11 * y1,
                 a00 * x2 + a01 * y2, a10 * x2 + a11 * y2,
                 a00 * x3 + a01 * y3, a10 * x3 + a11 * y3);
}

void pathArc(QPainterPath &path,
                    qreal               rx,
                    qreal               ry,
                    qreal               x_axis_rotation,
                    int         large_arc_flag,
                    int         sweep_flag,
                    qreal               x,
                    qreal               y,
                    qreal curx, qreal cury)
{
    qreal sin_th, cos_th;
    qreal a00, a01, a10, a11;
    qreal x0, y0, x1, y1, xc, yc;
    qreal d, sfactor, sfactor_sq;
    qreal th0, th1, th_arc;
    int i, n_segs;
    qreal dx, dy, dx1, dy1, Pr1, Pr2, Px, Py, check;

    rx = qAbs(rx);
    ry = qAbs(ry);

    sin_th = qSin(x_axis_rotation * (M_PI / 180.0));
    cos_th = qCos(x_axis_rotation * (M_PI / 180.0));

    dx = (curx - x) / 2.0;
    dy = (cury - y) / 2.0;
    dx1 =  cos_th * dx + sin_th * dy;
    dy1 = -sin_th * dx + cos_th * dy;
    Pr1 = rx * rx;
    Pr2 = ry * ry;
    Px = dx1 * dx1;
    Py = dy1 * dy1;
    /* Spec : check if radii are large enough */
    check = Px / Pr1 + Py / Pr2;
    if (check > 1) {
        rx = rx * qSqrt(check);
        ry = ry * qSqrt(check);
    }

    a00 =  cos_th / rx;
    a01 =  sin_th / rx;
    a10 = -sin_th / ry;
    a11 =  cos_th / ry;
    x0 = a00 * curx + a01 * cury;
    y0 = a10 * curx + a11 * cury;
    x1 = a00 * x + a01 * y;
    y1 = a10 * x + a11 * y;
    /* (x0, y0) is current point in transformed coordinate space.
       (x1, y1) is new point in transformed coordinate space.

       The arc fits a unit-radius circle in this space.
    */
    d = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
    sfactor_sq = 1.0 / d - 0.25;
    if (sfactor_sq < 0) sfactor_sq = 0;
    sfactor = qSqrt(sfactor_sq);
    if (sweep_flag == large_arc_flag) sfactor = -sfactor;
    xc = 0.5 * (x0 + x1) - sfactor * (y1 - y0);
    yc = 0.5 * (y0 + y1) + sfactor * (x1 - x0);
    /* (xc, yc) is center of the circle. */

    th0 = qAtan2(y0 - yc, x0 - xc);
    th1 = qAtan2(y1 - yc, x1 - xc);

    th_arc = th1 - th0;
    if (th_arc < 0 && sweep_flag)
        th_arc += 2 * M_PI;
    else if (th_arc > 0 && !sweep_flag)
        th_arc -= 2 * M_PI;

    n_segs = qCeil(qAbs(th_arc / (M_PI * 0.5 + 0.001)));

    for (i = 0; i < n_segs; i++) {
        pathArcSegment(path, xc, yc,
                       th0 + i * th_arc / n_segs,
                       th0 + (i + 1) * th_arc / n_segs,
                       rx, ry, x_axis_rotation);
    }
}
bool parsePathDataFast(const QString &dataStr, QPainterPath &path)
{
    qreal x0 = 0, y0 = 0;              // starting point
    qreal x = 0, y = 0;                // current point
    char lastMode = 0;
    QPointF ctrlPt;
    const QChar *str = dataStr.constData();
    const QChar *end = str + dataStr.size();

    while (str != end) {
        while (str->isSpace())
            ++str;
        QChar pathElem = *str;
        ++str;
        QChar endc = *end;
        *const_cast<QChar *>(end) = 0; // parseNumbersArray requires 0-termination that QStringRef cannot guarantee
        QVarLengthArray<qreal, 8> arg;
        parseNumbersArray(str, arg);
        *const_cast<QChar *>(end) = endc;
        if (pathElem == QLatin1Char('z') || pathElem == QLatin1Char('Z'))
            arg.append(0);//dummy
        const qreal *num = arg.constData();
        int count = arg.count();
        while (count > 0) {
            qreal offsetX = x;        // correction offsets
            qreal offsetY = y;        // for relative commands
            switch (pathElem.unicode()) {
            case 'm': {
                if (count < 2) {
                    num++;
                    count--;
                    break;
                }
                x = x0 = num[0] + offsetX;
                y = y0 = num[1] + offsetY;
                num += 2;
                count -= 2;
                path.moveTo(x0, y0);

                // As per 1.2  spec 8.3.2 The "moveto" commands
                // If a 'moveto' is followed by multiple pairs of coordinates without explicit commands,
                // the subsequent pairs shall be treated as implicit 'lineto' commands.
                pathElem = QLatin1Char('l');
            }
                break;
            case 'M': {
                if (count < 2) {
                    num++;
                    count--;
                    break;
                }
                x = x0 = num[0];
                y = y0 = num[1];
                num += 2;
                count -= 2;
                path.moveTo(x0, y0);

                // As per 1.2  spec 8.3.2 The "moveto" commands
                // If a 'moveto' is followed by multiple pairs of coordinates without explicit commands,
                // the subsequent pairs shall be treated as implicit 'lineto' commands.
                pathElem = QLatin1Char('L');
            }
                break;
            case 'z':
            case 'Z': {
                x = x0;
                y = y0;
                count--; // skip dummy
                num++;
                path.closeSubpath();
            }
                break;
            case 'l': {
                if (count < 2) {
                    num++;
                    count--;
                    break;
                }
                x = num[0] + offsetX;
                y = num[1] + offsetY;
                num += 2;
                count -= 2;
                path.lineTo(x, y);

            }
                break;
            case 'L': {
                if (count < 2) {
                    num++;
                    count--;
                    break;
                }
                x = num[0];
                y = num[1];
                num += 2;
                count -= 2;
                path.lineTo(x, y);
            }
                break;
            case 'h': {
                x = num[0] + offsetX;
                num++;
                count--;
                path.lineTo(x, y);
            }
                break;
            case 'H': {
                x = num[0];
                num++;
                count--;
                path.lineTo(x, y);
            }
                break;
            case 'v': {
                y = num[0] + offsetY;
                num++;
                count--;
                path.lineTo(x, y);
            }
                break;
            case 'V': {
                y = num[0];
                num++;
                count--;
                path.lineTo(x, y);
            }
                break;
            case 'c': {
                if (count < 6) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF c1(num[0] + offsetX, num[1] + offsetY);
                QPointF c2(num[2] + offsetX, num[3] + offsetY);
                QPointF e(num[4] + offsetX, num[5] + offsetY);
                num += 6;
                count -= 6;
                path.cubicTo(c1, c2, e);
                ctrlPt = c2;
                x = e.x();
                y = e.y();
                break;
            }
            case 'C': {
                if (count < 6) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF c1(num[0], num[1]);
                QPointF c2(num[2], num[3]);
                QPointF e(num[4], num[5]);
                num += 6;
                count -= 6;
                path.cubicTo(c1, c2, e);
                ctrlPt = c2;
                x = e.x();
                y = e.y();
                break;
            }
            case 's': {
                if (count < 4) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF c1;
                if (lastMode == 'c' || lastMode == 'C' ||
                        lastMode == 's' || lastMode == 'S')
                    c1 = QPointF(2*x-ctrlPt.x(), 2*y-ctrlPt.y());
                else
                    c1 = QPointF(x, y);
                QPointF c2(num[0] + offsetX, num[1] + offsetY);
                QPointF e(num[2] + offsetX, num[3] + offsetY);
                num += 4;
                count -= 4;
                path.cubicTo(c1, c2, e);
                ctrlPt = c2;
                x = e.x();
                y = e.y();
                break;
            }
            case 'S': {
                if (count < 4) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF c1;
                if (lastMode == 'c' || lastMode == 'C' ||
                        lastMode == 's' || lastMode == 'S')
                    c1 = QPointF(2*x-ctrlPt.x(), 2*y-ctrlPt.y());
                else
                    c1 = QPointF(x, y);
                QPointF c2(num[0], num[1]);
                QPointF e(num[2], num[3]);
                num += 4;
                count -= 4;
                path.cubicTo(c1, c2, e);
                ctrlPt = c2;
                x = e.x();
                y = e.y();
                break;
            }
            case 'q': {
                if (count < 4) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF c(num[0] + offsetX, num[1] + offsetY);
                QPointF e(num[2] + offsetX, num[3] + offsetY);
                num += 4;
                count -= 4;
                path.quadTo(c, e);
                ctrlPt = c;
                x = e.x();
                y = e.y();
                break;
            }
            case 'Q': {
                if (count < 4) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF c(num[0], num[1]);
                QPointF e(num[2], num[3]);
                num += 4;
                count -= 4;
                path.quadTo(c, e);
                ctrlPt = c;
                x = e.x();
                y = e.y();
                break;
            }
            case 't': {
                if (count < 2) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF e(num[0] + offsetX, num[1] + offsetY);
                num += 2;
                count -= 2;
                QPointF c;
                if (lastMode == 'q' || lastMode == 'Q' ||
                        lastMode == 't' || lastMode == 'T')
                    c = QPointF(2*x-ctrlPt.x(), 2*y-ctrlPt.y());
                else
                    c = QPointF(x, y);
                path.quadTo(c, e);
                ctrlPt = c;
                x = e.x();
                y = e.y();
                break;
            }
            case 'T': {
                if (count < 2) {
                    num += count;
                    count = 0;
                    break;
                }
                QPointF e(num[0], num[1]);
                num += 2;
                count -= 2;
                QPointF c;
                if (lastMode == 'q' || lastMode == 'Q' ||
                        lastMode == 't' || lastMode == 'T')
                    c = QPointF(2*x-ctrlPt.x(), 2*y-ctrlPt.y());
                else
                    c = QPointF(x, y);
                path.quadTo(c, e);
                ctrlPt = c;
                x = e.x();
                y = e.y();
                break;
            }
            case 'a': {
                if (count < 7) {
                    num += count;
                    count = 0;
                    break;
                }
                qreal rx = (*num++);
                qreal ry = (*num++);
                qreal xAxisRotation = (*num++);
                qreal largeArcFlag  = (*num++);
                qreal sweepFlag = (*num++);
                qreal ex = (*num++) + offsetX;
                qreal ey = (*num++) + offsetY;
                count -= 7;
                qreal curx = x;
                qreal cury = y;
                pathArc(path, rx, ry, xAxisRotation, int(largeArcFlag),
                        int(sweepFlag), ex, ey, curx, cury);

                x = ex;
                y = ey;
            }
                break;
            case 'A': {
                if (count < 7) {
                    num += count;
                    count = 0;
                    break;
                }
                qreal rx = (*num++);
                qreal ry = (*num++);
                qreal xAxisRotation = (*num++);
                qreal largeArcFlag  = (*num++);
                qreal sweepFlag = (*num++);
                qreal ex = (*num++);
                qreal ey = (*num++);
                count -= 7;
                qreal curx = x;
                qreal cury = y;
                pathArc(path, rx, ry, xAxisRotation, int(largeArcFlag),
                        int(sweepFlag), ex, ey, curx, cury);

                x = ex;
                y = ey;
            }
                break;
            default:
                return false;
            }
            lastMode = pathElem.toLatin1();
        }
    }
    return true;
}
static inline bool isDigit(ushort ch)
{
    static quint16 magic = 0x3ff;
    return ((ch >> 4) == 3) && (magic >> (ch & 15));
}

static qreal toDouble(const QChar *&str)
{
    const int maxLen = 255;//technically doubles can go til 308+ but whatever
    char temp[maxLen+1];
    int pos = 0;

    if (*str == QLatin1Char('-')) {
        temp[pos++] = '-';
        ++str;
    } else if (*str == QLatin1Char('+')) {
        ++str;
    }
    while (isDigit(str->unicode()) && pos < maxLen) {
        temp[pos++] = str->toLatin1();
        ++str;
    }
    if (*str == QLatin1Char('.') && pos < maxLen) {
        temp[pos++] = '.';
        ++str;
    }
    while (isDigit(str->unicode()) && pos < maxLen) {
        temp[pos++] = str->toLatin1();
        ++str;
    }
    bool exponent = false;
    if ((*str == QLatin1Char('e') || *str == QLatin1Char('E')) && pos < maxLen) {
        exponent = true;
        temp[pos++] = 'e';
        ++str;
        if ((*str == QLatin1Char('-') || *str == QLatin1Char('+')) && pos < maxLen) {
            temp[pos++] = str->toLatin1();
            ++str;
        }
        while (isDigit(str->unicode()) && pos < maxLen) {
            temp[pos++] = str->toLatin1();
            ++str;
        }
    }

    temp[pos] = '\0';

    qreal val;
    if (!exponent && pos < 10) {
        int ival = 0;
        const char *t = temp;
        bool neg = false;
        if(*t == '-') {
            neg = true;
            ++t;
        }
        while(*t && *t != '.') {
            ival *= 10;
            ival += (*t) - '0';
            ++t;
        }
        if(*t == '.') {
            ++t;
            int div = 1;
            while(*t) {
                ival *= 10;
                ival += (*t) - '0';
                div *= 10;
                ++t;
            }
            val = ((qreal)ival)/((qreal)div);
        } else {
            val = ival;
        }
        if (neg)
            val = -val;
    } else {
#if defined(Q_WS_QWS) && !defined(Q_OS_VXWORKS)
        if(sizeof(qreal) == sizeof(float))
            val = strtof(temp, 0);
        else
#endif
        {
            bool ok = false;
            val = qstrtod(temp, 0, &ok);
        }
    }
    return val;

}
void parseNumbersArray(const QChar *&str, QVarLengthArray<qreal, 8> &points)
{
    while (str->isSpace())
        ++str;
    while (isDigit(str->unicode()) ||
           *str == QLatin1Char('-') || *str == QLatin1Char('+') ||
           *str == QLatin1Char('.')) {

        points.append(toDouble(str));

        while (str->isSpace())
            ++str;
        if (*str == QLatin1Char(','))
            ++str;

        //eat the rest of space
        while (str->isSpace())
            ++str;
    }
}
