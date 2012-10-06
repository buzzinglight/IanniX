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

#include "nxcursor.h"

NxCursor::NxCursor(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
    NxObject(parent, ccParentItem, _renderOptions) {
    glListCursor = glGenLists(1);
    curve = 0;
    setTimeLocal(0);
    nextTimeOld = 0;
    timeOld = 0;
    time = 0;
    timeLocal = 0;
    timeLocalOld = 0;
    timeLocalAbsolute = 0;
    previousCursorReliable = false;
    previousPreviousCursorReliable = false;
    cursorPoly = NxPolygon(4);
    cursorPoly[0] = NxPoint();
    cursorPoly[1] = NxPoint();
    cursorPoly[2] = NxPoint();
    cursorPoly[3] = NxPoint();
    setNbLoop(0);
    setStart("1 0");
    setTimeFactor(1);
    setTimeFactorF(1);
    setWidth(1);
    setDepth(0);
    setTime(0);
    setSize(1.2);
    setLineFactor(1);
    setLineStipple(0xFFFF);
    setColorActive("cursor_active");
    setColorInactive("cursor_inactive");
    setTimeStartOffset(0);
    setTimeEndOffset(0);
    setTimeInitialOffset(0);
    setEasing(0);
    setBoundsSource("-10 10 -10 10 -10 10");
    setBoundsTarget("0 1 0 1 0 1");
    boundsSourceIsBoundingRect = true;
}
NxCursor::~NxCursor() {
    glDeleteLists(glListCursor, 1);
}

void NxCursor::setTime(qreal delta) {
    if(curve) {
        timeLocalOld = timeLocal;

        qint16 indexOfZero = start.indexOf(0);
        qreal loopFactor = start.at(nbLoop % start.count());
        if((indexOfZero > 0) && (nbLoop > indexOfZero))
            loopFactor = 0;

        factors = timeFactor * timeFactorF * loopFactor;
        timeLocalAbsolute += delta * timeFactor * timeFactorF * qAbs(loopFactor);
        if(time >= 0)
            timeLocal     += delta * factors;
        else
            timeLocal = 0;

        qreal timeInitialOffsetReal = timeInitialOffset * qAbs(factors);
        qreal timeStartOffsetReal   = timeStartOffset  ;// * qAbs(factors);
        qreal timeEndOffsetReal     = timeEndOffset    ;// * qAbs(factors);
        qreal timeLocalAbsoluteCopy = timeLocalAbsolute + timeInitialOffsetReal;
        qreal fakeCurveLength = curve->getPathLength() - timeStartOffsetReal;

        if(timeEndOffset > 0)
            fakeCurveLength = timeEndOffsetReal - timeStartOffsetReal;
        nbLoop = 0;
        if(fakeCurveLength > 0) {
            if(timeLocalAbsoluteCopy > 0) {
                while(timeLocalAbsoluteCopy > fakeCurveLength) {
                    if((indexOfZero > 0) && (nbLoop >= (indexOfZero-1)))
                        break;
                    else {
                        nbLoop++;
                        timeLocalAbsoluteCopy -= fakeCurveLength;
                    }
                }
            }
            else {
                while(timeLocalAbsoluteCopy < timeInitialOffsetReal) {
                    if((indexOfZero > 0) && (nbLoop >= (indexOfZero-1)))
                        break;
                    else {
                        nbLoop++;
                        timeLocalAbsoluteCopy += fakeCurveLength;
                    }
                }
            }
        }

        //Preparation of time difference
        if(!previousCursorReliable)
            timeOld = nextTimeOld;
        else
            timeOld = time;
        nextTimeOld = timeOld;
        previousCursorReliable = true;

        //Time calculation
        if(loopFactor >= 0)
            time = timeLocalAbsoluteCopy / fakeCurveLength;
        else
            time = (fakeCurveLength - timeLocalAbsoluteCopy) / fakeCurveLength;

        if((time < 0) || (time > 1))
            previousCursorReliable = false;

        //Loop
        if(nbLoop != nbLoopOld) {
            previousCursorReliable = false;
            nextTimeOld = qRound(time)    / curve->getPathLength() * fakeCurveLength + timeStartOffsetReal / curve->getPathLength();
            time        = qRound(timeOld) / curve->getPathLength() * fakeCurveLength + timeStartOffsetReal / curve->getPathLength();
        }
        else {
            time = time / curve->getPathLength() * fakeCurveLength + timeStartOffsetReal / curve->getPathLength();
        }

        //Finaly
        nbLoopOld = nbLoop;
        calculate();

        //Activity
        if(qAbs(timeLocal - timeLocalOld) < 0.00001) {
            if(!hasActivityOld)
                hasActivity = false;
            hasActivityOld = false;
        }
        else {
            hasActivity = true;
            hasActivityOld = true;
        }
    }
}


void NxCursor::calculate() {
    //Cursor line
    if((curve) && (curve->getPathLength() > 0)) {
        qreal timeReal = easing.getValue(time), timeOldReal = easing.getValue(timeOld);
        cursorPos = curve->getPointAt(timeReal) + curve->getPos();

        if(timeReal == 0)
            cursorAngle = -curve->getAngleAt(timeReal + 0.001);
        else if(timeReal == 1)
            cursorAngle = -curve->getAngleAt(timeReal - 0.001);
        else
            cursorAngle = -curve->getAngleAt(timeReal);

        cursorPosOld = curve->getPointAt(timeOldReal) + curve->getPos();

        if(timeOldReal == 0)
            cursorAngleOld = -curve->getAngleAt(timeOldReal + 0.001);
        else if(timeOldReal == 1)
            cursorAngleOld = -curve->getAngleAt(timeOldReal - 0.001);
        else
            cursorAngleOld = -curve->getAngleAt(timeOldReal);

        //Infos en +
        //NxPoint cursorPosDelta = cursorPosOld - cursorPos;
        cursorAngleRoll = 0;//-qSin(cursorPosDelta.x() * M_PI) * 180 * 2;
        cursorAnglePitch = 0;//qSin(cursorPosDelta.y() * M_PI) * 180 * 5;
    }
    else {
        cursorPos = pos;

        NxPoint cursorPosDelta = cursorPosOld - cursorPos;
        previousCursorReliable = true;
        previousPreviousCursorReliable = true;

        if((cursorPosDelta.x() > 0) && (cursorPosDelta.y() >= 0))
            cursorAngle = (qAtan(cursorPosDelta.y() / cursorPosDelta.x())) * 180.0F / M_PI;
        else if((cursorPosDelta.x() <= 0) && (cursorPosDelta.y() > 0))
            cursorAngle = (-qAtan(cursorPosDelta.x() / cursorPosDelta.y()) + M_PI_2) * 180.0F / M_PI;
        else if((cursorPosDelta.x() < 0) && (cursorPosDelta.y() <= 0))
            cursorAngle = (qAtan(cursorPosDelta.y() / cursorPosDelta.x()) + M_PI) * 180.0F / M_PI;
        else if((cursorPosDelta.x() >= 0) && (cursorPosDelta.y() < 0))
            cursorAngle = (-qAtan(cursorPosDelta.x() / cursorPosDelta.y()) + 3 * M_PI_2) * 180.0F / M_PI;
        //cursorAngle = 45;
    }

    if(cursorAngle != cursorAngle)
        cursorAngle = 0;
    cursorRelativePos = getCursorValue(cursorPos);

    //Calculate polygon (from previous cursor to actual cursor)
    QLineF cursorTmp = QTransform().rotate(cursorAngle + 90.0F).map(QLineF(-width/2.0F, 0, width/2.0F, 0));
    cursor = NxLine(cursorTmp.x1(), cursorTmp.y1(), cursorTmp.x2(), cursorTmp.y2());
    cursor.translate(cursorPos);

    //Loop guard
    if(!previousPreviousCursorReliable) {
        previousPreviousCursorReliable = true;
        cursorOld = cursor;
    }
    if(!previousCursorReliable) {
        previousPreviousCursorReliable = false;
        cursorOld = cursor;
    }

    //Cross Poly guard
    QLineF diag1(cursor.p1().x(),cursor.p1().y(),cursor.p2().x(),cursor.p2().y());
    QLineF diag2(cursorOld.p1().x(),cursorOld.p1().y(),cursorOld.p2().x(),cursorOld.p2().y());
    QPointF intersectionPoint;

    if(diag1.intersect(diag2, &intersectionPoint) == QLineF::BoundedIntersection) {
        cursorPoly[0] = cursor.p1();
        cursorPoly[1] = cursorOld.p1();
        cursorPoly[2] = cursor.p2();
        cursorPoly[3] = cursorOld.p2();
    } else {
        cursorPoly[0] = cursorOld.p1();
        cursorPoly[1] = cursor.p1();
        cursorPoly[2] = cursor.p2();
        cursorPoly[3] = cursorOld.p2();
    }


    if(false)
        qDebug("%d %d %f %f - %f %f  ==>  %f %f - %f %f", previousCursorReliable, previousPreviousCursorReliable, cursorOld.p1().x(), cursorOld.p1().y(), cursorOld.p2().x(), cursorOld.p2().y(), cursor.p1().x(), cursor.p1().y(), cursor.p2().x(), cursor.p2().y());

    if(false)
        qDebug("%d %d %f %f %d || %f %f => %f %f", id, nbLoop, timeLocalAbsolute, time, previousCursorReliable, cursorOld.p1().x(), cursorOld.p2().y(), cursor.p1().x(), cursor.p2().y());

    calcBoundingRect();

    cursorOld = cursor;
    previousCursor = cursor;
    if((cursorPos.sx() != cursorPosOld.sx()) || (cursorPos.sy() != cursorPosOld.sy()) || (cursorPos.sz() != cursorPosOld.sz()))
        glListRecreate = true;
    if((curve) && (curve->getPathLength() > 0)) {
    }
    else {
        cursorPosOld = cursorPos;
        cursorAngleOld = cursorAngle;
    }
}


void NxCursor::paint() {
    //Color
    if(active)
        color = (!colorActive.isEmpty())?(renderOptions->colors.value(colorActive)):(colorActiveColor);
    else
        color = (!colorInactive.isEmpty())?(renderOptions->colors.value(colorInactive)):(colorInactiveColor);

    if(color.alpha() > 0) {
        //Size of cursors
        qreal cacheSize = renderOptions->objectSize;

        //Mouse hover
        if(selectedHover)
            color = renderOptions->colors.value("object_hover");
        if(selected)
            color = renderOptions->colors.value("object_selection");

        //Start
        bool opacityCheck = ((renderOptions->paintCursors) && (renderOptions->paintThisGroup) && ((renderOptions->paintZStart <= pos.z()) && (pos.z() <= renderOptions->paintZEnd)));
        if(!opacityCheck)
            color.setAlphaF(0.1);

        if(!renderOptions->allowSelectionCursors)
            color.setAlphaF(color.alphaF()/3);

        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

        //Cursor chasse-neige
        if((0.0F <= time) && (time <= 1.0F) && (start.at(nbLoop % start.count()) != 0)) {
            //Label
            if((opacityCheck) && (renderOptions->paintLabel) && (!label.isEmpty()))
                renderOptions->render->renderText(cursorPos.x(), cursorPos.y(), cursorPos.z(), label, renderOptions->renderFont);
            if(selectedHover) {
                qreal startY = 0;
                foreach(const QString & messageLabelItem, messageLabel) {
                    renderOptions->render->renderText(cursorPos.x(), cursorPos.y() + startY, cursorPos.z(), messageLabelItem, renderOptions->renderFont);
                    startY -= cacheSize * 1.5;
                }
            }

            glLineWidth(size);
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(lineFactor, lineStipple);
            if(depth == 0) {
                glBegin(GL_LINE_STRIP);
                glVertex3f(cursorPoly.at(1).x(), cursorPoly.at(1).y(), cursorPoly.at(1).z());
                glVertex3f(cursorPoly.at(2).x(), cursorPoly.at(2).y(), cursorPoly.at(2).z());
                glEnd();
            }
            else {
                glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF()/5.);
                glBegin(GL_QUADS);
                glVertex3f(cursorPoly.at(1).x(), cursorPoly.at(1).y(), cursorPoly.at(1).z()+depth/2);
                glVertex3f(cursorPoly.at(2).x(), cursorPoly.at(2).y(), cursorPoly.at(2).z()+depth/2);
                glVertex3f(cursorPoly.at(2).x(), cursorPoly.at(2).y(), cursorPoly.at(2).z()-depth/2);
                glVertex3f(cursorPoly.at(1).x(), cursorPoly.at(1).y(), cursorPoly.at(1).z()-depth/2);
                glEnd();

                glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
                glBegin(GL_LINE_LOOP);
                glVertex3f(cursorPoly.at(1).x(), cursorPoly.at(1).y(), cursorPoly.at(1).z()+depth/2);
                glVertex3f(cursorPoly.at(2).x(), cursorPoly.at(2).y(), cursorPoly.at(2).z()+depth/2);
                glVertex3f(cursorPoly.at(2).x(), cursorPoly.at(2).y(), cursorPoly.at(2).z()-depth/2);
                glVertex3f(cursorPoly.at(1).x(), cursorPoly.at(1).y(), cursorPoly.at(1).z()-depth/2);
                glEnd();
            }
            glDisable(GL_LINE_STIPPLE);
            glLineWidth(1);

            //Cursor reader
            glPushMatrix();
            glTranslatef(cursorPos.x(), cursorPos.y(), cursorPos.z());
            glRotatef(cursorAngle, 0, 0, 1);
            qreal size2 = cacheSize/2 * 1.5 * qMin(1., width) * 0.7;
            glBegin(GL_TRIANGLE_FAN);
            glLineWidth(2);
            if(hasActivity) {
                if((time - timeOld) >= 0)  glVertex3f(size2, 0, 0);
                else                       glVertex3f(-size2, 0, 0);
            }
            glVertex3f(0, -size2, 0);
            glVertex3f(0, size2, 0);
            glLineWidth(1);
            glEnd();
            glPopMatrix();

            //Special feature YEOSU
            if((true) && ((cursorPos.sx()) || (cursorPos.sy()) || (cursorPos.sz()))) {
                glPushMatrix();
                glTranslatef(cursorPos.x(), cursorPos.y(), cursorPos.z());
                glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF() / 8.F);
                if(curve)
                    glLineWidth(curve->getSize());
                else
                    glLineWidth(1);

                if((glListRecreate) || (renderOptions->forceLists)) {
                    glNewList(glListCursor, GL_COMPILE_AND_EXECUTE);
                    qreal lats = 40, longs = 40;
                    qreal rx = cursorPos.sx(), ry = cursorPos.sy(), rz = cursorPos.sz();
                    glBegin(GL_LINE_STRIP);
                    for(quint16 i = 0; i <= lats; i++) {
                        qreal lat0 = M_PI * (-0.5 + (qreal)(i - 1) / lats);
                        qreal lat1 = M_PI * (-0.5 + (qreal)(i    ) / lats);
                        qreal z0  = qSin(lat0) * rz, zr0 = qCos(lat0);
                        qreal z1  = qSin(lat1) * rz, zr1 = qCos(lat1);

                        for(quint16 j = 0; j <= longs; j++) {
                            qreal lng = 2 * M_PI * (qreal)(j - 1) / longs;
                            qreal x = qCos(lng) * rx;
                            qreal y = qSin(lng) * ry;
                            glNormal3f(x * zr0, y * zr0, z0);
                            glVertex3f(x * zr0, y * zr0, z0);
                            glNormal3f(x * zr1, y * zr1, z1);
                            glVertex3f(x * zr1, y * zr1, z1);
                        }
                    }
                    glEnd();
                    glEndList();
                    glListRecreate = false;
                }
                else
                    glCallList(glListCursor);
                glPopMatrix();
            }

            //Mapping area
            if((selectedHover) || (selected)) {
                glPushMatrix();
                glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF() / 2.F);
                glLineWidth(1);
                glEnable(GL_LINE_STIPPLE);
                glLineStipple(1, 255);
                glBegin(GL_LINE_LOOP);
                glVertex3f(boundsSource.topLeft().x(),     boundsSource.topLeft().y(),     boundsSource.topLeft().z());
                glVertex3f(boundsSource.topRight().x(),    boundsSource.topRight().y(),    boundsSource.topRight().z());
                glVertex3f(boundsSource.bottomRight().x(), boundsSource.bottomRight().y(), boundsSource.bottomRight().z());
                glVertex3f(boundsSource.bottomLeft().x(),  boundsSource.bottomLeft().y(),  boundsSource.bottomLeft().z());
                glEnd();
                glDisable(GL_LINE_STIPPLE);
                renderOptions->render->renderText(boundsSource.topLeft().x()     - 0.50, boundsSource.topLeft().y()     - 0.12, 0, QString::number(boundsTarget.topLeft().y(),     'f', 3), renderOptions->renderFont);
                renderOptions->render->renderText(boundsSource.bottomLeft().x()  - 0.50, boundsSource.bottomLeft().y()  - 0.00, 0, QString::number(boundsTarget.bottomLeft().y(),  'f', 3), renderOptions->renderFont);
                renderOptions->render->renderText(boundsSource.bottomLeft().x()  - 0.00, boundsSource.bottomLeft().y()  - 0.22, 0, QString::number(boundsTarget.bottomLeft().x(),  'f', 3), renderOptions->renderFont);
                renderOptions->render->renderText(boundsSource.bottomRight().x() - 0.40, boundsSource.bottomRight().y() - 0.22, 0, QString::number(boundsTarget.bottomRight().x(), 'f', 3), renderOptions->renderFont);
                glPopMatrix();
            }
        }
    }
}

void NxCursor::trig(bool force) {
    if((force) || ((((previousCursorReliable) && (hasActivity)) || (!curve)) && (canSendOsc()))) {
        factory->sendMessage(this, 0, this);
        incMessageId();
    }
}

bool NxCursor::contains(NxTrigger *trigger) const {
    if((previousCursorReliable) && (trigger->getActive()) && ((trigger->getPos().z()-depth/2 <= cursorPoly[0].z()) && (cursorPoly[0].z()) <= trigger->getPos().z()+depth/2) && (cursorPoly.containsPoint(trigger->getPos(), Qt::OddEvenFill)))
        return true;
    else
        return false;
}
bool NxCursor::trig(NxCurve *collisionCurve) {
    if((performCollision) && (collisionCurve) && (collisionCurve->getActive()) && (collisionCurve != curve)) {
        NxPoint collisionPoint;
        qreal percent = collisionCurve->intersects(boundingRect, &collisionPoint);
        if(percent >= 0) {
            factory->sendMessage(this, 0, this, collisionCurve, collisionPoint, getCursorValue(collisionPoint));
            return true;
        }
        return false;
    }
    else
        return false;
}

