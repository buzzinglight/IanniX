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
    glListCursorRecreate = true;
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
    cursorPoly = NxPolygon(4);
    cursorPoly[0] = NxPoint();
    cursorPoly[1] = NxPoint();
    cursorPoly[2] = NxPoint();
    cursorPoly[3] = NxPoint();
    setNbLoop(0);
    setStart("1");
    setTimeFactor(1);
    setTimeFactorF(1);
    setWidth(1);
    setDepth(0);
    setTime(0);
    setSize(2);
    setLineFactor(1);
    setLineStipple(0xFFFF);
    setColorActive("cursor_active");
    setColorInactive("cursor_inactive");
    setTimeStartOffset(0);
    setTimeEndOffset(-1);
    setTimeInitialOffset(0);
    setEasing(0);
    setBoundsSource("-10 10 10 -10");
    setBoundsTarget("0 1 1 0");
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
        qreal timeStartOffsetReal   = timeStartOffset   * qAbs(factors);
        qreal timeEndOffsetReal     = timeEndOffset     * qAbs(factors);
        qreal timeLocalAbsoluteCopy = timeLocalAbsolute + timeInitialOffsetReal;
        qreal fakeCurveLength = curve->getPathLength() - timeStartOffsetReal;

        if(timeEndOffset > 0)
            fakeCurveLength = timeEndOffsetReal - timeStartOffsetReal;
        nbLoop = 0;
        if(timeLocalAbsoluteCopy > 0) {
            while((timeLocalAbsoluteCopy > fakeCurveLength) && (fakeCurveLength > 0)) {
                nbLoop++;
                timeLocalAbsoluteCopy -= fakeCurveLength;
            }
        }
        /*
        else {
            while((timeLocalAbsoluteCopy < 0) && (fakeCurveLength > 0)) {
                nbLoop++;
                timeLocalAbsoluteCopy += fakeCurveLength;
            }
        }
        */

        //Preparation of time difference
        if(!previousCursorReliable)
            timeOld = nextTimeOld;
        else
            timeOld = time;
        nextTimeOld = timeOld;
        previousCursorReliable = true;

        //Time calculation
        time = timeLocalAbsoluteCopy / fakeCurveLength;
        if(loopFactor >= 0)
            time = timeLocalAbsoluteCopy / fakeCurveLength;
        else if(loopFactor < 0)
            time = (fakeCurveLength - timeLocalAbsoluteCopy) / fakeCurveLength;

        if((time < 0) || (time > 1))
            previousCursorReliable = false;

        //Loop
        if(nbLoop != nbLoopOld) {
            previousCursorReliable = false;
            nextTimeOld = qRound(time)    / curve->getPathLength() * fakeCurveLength + timeStartOffsetReal / curve->getPathLength();
            time        = qRound(timeOld) / curve->getPathLength() * fakeCurveLength + timeStartOffsetReal / curve->getPathLength();
        }
        else
            time = time / curve->getPathLength() * fakeCurveLength + timeStartOffsetReal / curve->getPathLength();

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

        //cursorPos = pos;
        previousCursorReliable = true;

        if((cursorPosDelta.x() > 0) && (cursorPosDelta.y() >= 0))
            cursorAngle = (qAtan(cursorPosDelta.y() / cursorPosDelta.x())) * 180.0F / M_PI;
        else if((cursorPosDelta.x() <= 0) && (cursorPosDelta.y() > 0))
            cursorAngle = (-qAtan(cursorPosDelta.x() / cursorPosDelta.y()) + M_PI_2) * 180.0F / M_PI;
        else if((cursorPosDelta.x() < 0) && (cursorPosDelta.y() <= 0))
            cursorAngle = (qAtan(cursorPosDelta.y() / cursorPosDelta.x()) + M_PI) * 180.0F / M_PI;
        else if((cursorPosDelta.x() >= 0) && (cursorPosDelta.y() < 0))
            cursorAngle = (-qAtan(cursorPosDelta.x() / cursorPosDelta.y()) + 3 * M_PI_2) * 180.0F / M_PI;
    }
    if(cursorAngle != cursorAngle)
        cursorAngle = 0;
    cursorRelativePos = getCursorValue(cursorPos);

    //Calculate polygon (from previous cursor to actual cursor)
    QLineF cursorTmp = QTransform().rotate(cursorAngle + 90).map(QLineF(-width/2, 0, width/2, 0));
    cursor = NxLine(cursorTmp.x1(), cursorTmp.y1(), cursorTmp.x2(), cursorTmp.y2());
    cursor.translate(cursorPos);
    QLineF cursorOldTmp = QTransform().rotate(cursorAngleOld + 90).map(QLineF(-width/2, 0, width/2, 0));
    cursorOld = NxLine(cursorOldTmp.x1(), cursorOldTmp.y1(), cursorOldTmp.x2(), cursorOldTmp.y2());
    cursorOld.translate(cursorPosOld);

    QLineF diag1(cursor.p1().x(),cursor.p1().y(),cursor.p2().x(),cursor.p2().y());
    QLineF diag2(cursorOld.p1().x(),cursorOld.p1().y(),cursorOld.p2().x(),cursorOld.p2().y());
    QPointF intersectionPoint;

    if (diag1.intersect(diag2, &intersectionPoint) == QLineF::BoundedIntersection) {  ////GC//// Fix crossed diagonal in cursorPoly
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

    calcBoundingRect();

    previousCursor = cursor;
    if((curve) && (curve->getPathLength() > 0)) {
    }
    else {
        if((cursorPos.sx() != cursorPosOld.sx()) || (cursorPos.sy() != cursorPosOld.sy()) || (cursorPos.sz() != cursorPosOld.sz()))
            glListCursorRecreate = true;
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
        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

        //Cursor chasse-neige
        if((previousCursorReliable) && (0.0F <= time) && (time <= 1.0F) && (start.at(nbLoop % start.count()) != 0)) {
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
            glBegin(GL_LINES);
            glVertex3f(cursorPoly.at(1).x(), cursorPoly.at(1).y(), cursorPoly.at(1).z());
            glVertex3f(cursorPoly.at(2).x(), cursorPoly.at(2).y(), cursorPoly.at(2).z());
            glEnd();
            glDisable(GL_LINE_STIPPLE);
            glLineWidth(1);

            //Cursor reader
            if((previousCursorReliable) || (!curve)) {
                glPushMatrix();
                glTranslatef(cursorPos.x(), cursorPos.y(), cursorPos.z());
                glRotatef(cursorAngle, 0, 0, 1);
                qreal size2 = cacheSize/2;
                glBegin(GL_TRIANGLE_FAN);
                if(hasActivity) {
                    if((time - timeOld) >= 0)  glVertex3f(size2, 0, 0);
                    else                       glVertex3f(-size2, 0, 0);
                }
                glVertex3f(0, -size2, 0);
                glVertex3f(0, size2, 0);
                glEnd();

                glPopMatrix();
            }

            //Special feature YEOSU
            if(true && ((cursorPos.sx()) || (cursorPos.sy()) || (cursorPos.sz()))) {
                glPushMatrix();
                glTranslatef(cursorPos.x(), cursorPos.y(), cursorPos.z());
                glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF() / 16.F);

                if(glListCursorRecreate) {
                    glNewList(glListCursor, GL_COMPILE);
                    qreal lats = 20, longs = 20;
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
                    glListCursorRecreate = false;
                }
                glCallList(glListCursor);
                glPopMatrix();
            }
        }
    }
}

void NxCursor::trig() {
    if((((previousCursorReliable) && (hasActivity)) || (!curve)) && (canSendOsc())) {
        factory->sendMessage(this, 0, this);
        incMessageId();
    }
}

bool NxCursor::contains(NxTrigger *trigger) {
    if((trigger->getActive()) && (trigger->getPos().z() == cursorPoly[0].z()) && (cursorPoly.containsPoint(trigger->getPos(), Qt::OddEvenFill)))
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

