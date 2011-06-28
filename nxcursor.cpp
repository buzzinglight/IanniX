#include "nxcursor.h"

NxCursor::NxCursor(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
        NxObject(parent, ccParentItem, _renderOptions) {
    curve = 0;
    setTimeLocal(0);
    time = 0;
    nbTimeOld = 0;
    loopGuard = 0;
    previousCursorReliable = false;
    cursorPoly = QPolygon(4);
    cursorPoly[0] = QPointF(0, 0);
    cursorPoly[1] = QPointF(0, 0);
    cursorPoly[2] = QPointF(0, 0);
    cursorPoly[3] = QPointF(0, 0);
    setNbLoop(0);
    setStart("1");
    setTimeFactor(1);
    setTimeFactorF(1);
    setWidth(1);
    setTime(0);
    setSize(2);
    setLineFactor(1);
    setLineStipple(0xFFFF);
    setColorActive("cursor_active");
    setColorInactive("cursor_inactive");
    setTimeStartOffset(0);
    setTimeEndOffset(-1);
    setTimeInitialOffset(0);
    setEasingStart(0);
    setEasingStartDuration(0);
    setBoundsSource("-10 10 10 -10");
    setBoundsTarget("0 1 1 0");
    boundsSourceIsBoundingRect = true;
}

void NxCursor::setTime(qreal delta) {
    if(curve) {
        delta = delta * getFatTimeFactor();
        timeLocal += delta;
        timeLocalAbsolute += fabs(delta);

        //Easing
        qreal timeLocalEasing = timeLocal;
        if((0 < timeLocalAbsolute) && (timeLocalAbsolute < easingStartDuration)) {
            timeLocalEasing = easingStartDuration * easing.valueForProgress(timeLocalAbsolute/easingStartDuration);
            if(timeLocal < 0)
                timeLocalEasing = -timeLocalEasing;
        }

        //Extract progress
        qreal timeTmp = 0;
        qint32 nbTime = 0;
        if(curve->getPathLength() > 0) {
            if(timeEndOffset < 0)
                timeTmp = (fmod(timeLocalEasing + timeInitialOffset, (curve->getPathLength()-timeStartOffset), &nbTime) + timeStartOffset) / curve->getPathLength();
            else
                timeTmp = (fmod(timeLocalEasing + timeInitialOffset, (timeEndOffset-timeStartOffset), &nbTime) + timeStartOffset) / curve->getPathLength();
        }

        //Loop detection
        if((loopGuard >= 15) && (time != timeTmp) && (nbTime != nbTimeOld) && (getFatTimeFactor() != 0))
            nbLoop++;

        if(nbLoopOld != nbLoop) {
            //qDebug("%d BOUCLE   nbLoop=%d time=%f > timeTmp=%f   nbTimeOld=%d > nbTime=%d || pattern=%f", id, nbLoop, time, timeTmp, nbTimeOld, nbTime, getFatTimeFactor());
            previousCursorReliable = false;
            loopGuard = 0;
            if(((getFatTimeFactor(nbLoop)>=0) && (getFatTimeFactor(nbLoop-1)>=0)) || ((getFatTimeFactor(nbLoop)<=0) && (getFatTimeFactor(nbLoop-1)<=0))){}
            else {
                timeTmp = time;
                if(timeTmp > 0.5)
                    timeTmp = 1;
                else
                    timeTmp = 0;
            }
        }
        else {
            //qDebug("%d NOBOUCLE nbLoop=%d time=%f > timeTmp=%f   nbTimeOld=%d > nbTime=%d || pattern=%f", id, nbLoop, time, timeTmp, nbTimeOld, nbTime, getFatTimeFactor());
            previousCursorReliable = true;
        }

        //Finaly
        loopGuard++;
        time = timeTmp;
        nbTimeOld = nbTime;
        nbLoopOld = nbLoop;
        calculate();
    }
}


void NxCursor::paint() {
    //Color
    if(active)
        color = (colorActive != "")?(renderOptions->colors.value(colorActive)):(colorActiveColor);
    else
        color = (colorInactive != "")?(renderOptions->colors.value(colorInactive)):(colorInactiveColor);

    if(color.alpha() > 0) {
        //Size of cursors
        qreal cacheSize = renderOptions->objectSize;

        //Mouse hover
        if(selectedHover)
            color = renderOptions->colors.value("object_hover");
        if(selected)
            color = renderOptions->colors.value("object_selection");

        //Start
        if((renderOptions->paintCursors) && (renderOptions->paintThisGroup) && ((renderOptions->paintZStart <= z) && (z <= renderOptions->paintZEnd)))
            glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        else
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.1);


        //Label
        if((renderOptions->paintLabel) && (label != ""))
            renderOptions->render->renderText(cursorPos.x(), cursorPos.y(), z, label, renderOptions->renderFont);
        if(selectedHover) {
            qreal startY = 0;
            foreach(const QString & messageLabelItem, messageLabel) {
                renderOptions->render->renderText(cursorPos.x(), cursorPos.y() + startY, z, messageLabelItem, renderOptions->renderFont);
                startY -= cacheSize * 1.5;
            }
        }

        //Cursor chasse-neige
        if(true) {
            glLineWidth(size);
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(lineFactor, lineStipple);
            glBegin(GL_LINE_STRIP);
            glVertex3f(cursorPoly.at(1).x(), cursorPoly.at(1).y(), z);
            glVertex3f(cursorPoly.at(2).x(), cursorPoly.at(2).y(), z);
            glEnd();
            glDisable(GL_LINE_STIPPLE);
        }

        //Debug
        /*
        if(cursorPolyPathIntersection.elementCount() > 0) {
            glLineWidth(3);
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(lineFactor, lineStipple);
            glBegin(GL_LINE_STRIP);
            for(quint16 pathPointsIndex = 0 ; pathPointsIndex < cursorPolyPathIntersection.elementCount() ; pathPointsIndex++)
                if(cursorPolyPathIntersection.elementAt(pathPointsIndex).isMoveTo()) {
                    glVertex3f(cursorPolyPathIntersection.elementAt(pathPointsIndex).x, cursorPolyPathIntersection.elementAt(pathPointsIndex).y, z);
                    glVertex3f(cursorPolyPathIntersection.elementAt(pathPointsIndex).x+0.1, cursorPolyPathIntersection.elementAt(pathPointsIndex).y+0.1, z);
                }
            glEnd();
            glDisable(GL_LINE_STIPPLE);
        }
        */

        //Cursor reader
        if(getFatTimeFactor()) {
            glLineWidth(1);
            glPushMatrix();
            glTranslatef(cursorPos.x(), cursorPos.y(), z);
            glRotatef(cursorAngle, 0, 0, 1);
            glBegin(GL_QUADS);
            glVertex3f(0, -cacheSize/2, 0);
            if(getFatTimeFactor() > 0)
                glVertex3f(cacheSize/2, 0, 0);
            else
                glVertex3f(-cacheSize/2, 0, 0);
            glVertex3f(0, cacheSize/2, 0);
            glVertex3f(0, -cacheSize/2, 0);
            glEnd();
            glPopMatrix();
        }
    }
}


void NxCursor::calculate() {
    //Cursor line
    if((curve) && (curve->getPathLength() > 0)) {
        if(curve->getCurveType() == CurveTypeEllipse) {
            cursorAngle = 2 * time * M_PI;
            cursorPos = curve->getPos() + QPointF(curve->getBoundingRect().width() * cos(cursorAngle), curve->getBoundingRect().height() * sin(cursorAngle)) / 2;
            cursorAngle = (cursorAngle + M_PI_2) * 180.0F / M_PI;
        }
        else {
            cursorPos = curve->getPointAt(time) + curve->getPos();
            if(time == 0)
                cursorAngle = -curve->getPath().angleAtPercent(time + 0.001);
            else
                cursorAngle = -curve->getPath().angleAtPercent(time);
        }
        z = curve->getZ();
    }
    else {
        QPointF cursorPosDelta = pos - cursorPos;
        cursorPos = pos;
        cursorAngle = 0;
        previousCursorReliable = true;

        if((cursorPosDelta.x() > 0) && (cursorPosDelta.y() >= 0))
            cursorAngle = atan(cursorPosDelta.y() / cursorPosDelta.x());
        else if((cursorPosDelta.x() <= 0) && (cursorPosDelta.y() > 0))
            cursorAngle = -atan(cursorPosDelta.x() / cursorPosDelta.y()) + M_PI_2;
        else if((cursorPosDelta.x() < 0) && (cursorPosDelta.y() <= 0))
            cursorAngle = atan(cursorPosDelta.y() / cursorPosDelta.x()) + M_PI;
        else if((cursorPosDelta.x() >= 0) && (cursorPosDelta.y() < 0))
            cursorAngle = -atan(cursorPosDelta.x() / cursorPosDelta.y()) + 3 * M_PI_2;

        cursorAngle *= 180.0F / M_PI;
    }
    if(cursorAngle != cursorAngle)
        cursorAngle = 0;
    cursorRelativePos = getCursorValue(cursorPos);

    //Calculate polygon (from previous cursor to actual cursor)
    cursor = QTransform().rotate(cursorAngle + 90).map(QLineF(-width/2, 0, width/2, 0));
    cursor.translate(cursorPos);
    if(previousCursorReliable) {
        cursorPoly[0] = previousCursor.p1();
        cursorPoly[1] = cursor.p1();
        cursorPoly[2] = cursor.p2();
        cursorPoly[3] = previousCursor.p2();
    }
    else {
        cursorPoly[0] = cursor.p1();
        cursorPoly[1] = cursor.p1();
        cursorPoly[2] = cursor.p2();
        cursorPoly[3] = cursor.p2();
    }

    calcBoundingRect();

    previousCursor = cursor;
}

void NxCursor::trig() {
    if((getFatTimeFactor() != 0) && (canSendOsc()))
        factory->sendMessage(this, 0, this);
}
