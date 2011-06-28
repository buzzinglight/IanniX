#include "nxcurve.h"

NxCurve::NxCurve(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
        NxObject(parent, ccParentItem, _renderOptions) {
    path = QPainterPath(QPointF(0, 0));
    calcBoundingRect();
    setSize(1.2);
    setLineFactor(1);
    setLineStipple(0xFFFF);
    setColorActive("curve_active");
    setColorInactive("curve_inactive");
    selectedPathPointPoint = -1;
    selectedPathPointControl = -1;
    curveType = CurveTypePoints;
    setMessageTimeInterval(20);
    //setSVG("/Users/Guillaume/Documents/buzzinglight/Projets/Coduys/IanniX/IanniX/scores/svg.svg", "SVG", QSizeF(10, 10));
    //setText("toto", "Lucida Sans", 12);
    //setImage("/Users/Guillaume/Documents/buzzinglight/Projets/Coduys/IanniX/IanniX/scores/image.png", QSizeF(10, 10));
}

void NxCurve::paint() {
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

        //Start
        if((renderOptions->paintCurves) && (renderOptions->paintThisGroup) && ((renderOptions->paintZStart <= z) && (z <= renderOptions->paintZEnd)))
            glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        else
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.1);

        glPushMatrix();
        glTranslatef(pos.x(), pos.y(), z);

        //Label
        if((renderOptions->paintLabel) && (label != ""))
            renderOptions->render->renderText(0, 0, 0, label, renderOptions->renderFont);

        //Draw
        glLineWidth(size);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(lineFactor, lineStipple);
        glBegin(GL_LINE_STRIP);
        for(quint16 pathPointsIndex = 0 ; pathPointsIndex <= CURVE_PATH_POINTS ; pathPointsIndex++)
            glVertex3f(pathPointsCache[pathPointsIndex].x(), pathPointsCache[pathPointsIndex].y(), 0);
        glEnd();
        glDisable(GL_LINE_STIPPLE);

        /*
        QPainterPath line;
        QRectF line2(0, 0, 0.01, 1);
        line2.translate(-pos);
        line.addRect(line2);
        QPainterPath pt = path.intersected(line);
        qDebug("%d", pt.elementCount());
        for(quint16 pathPointsIndex = 0 ; pathPointsIndex < pt.elementCount() ; pathPointsIndex++)
            qDebug("\t%f %f", pt.elementAt(pathPointsIndex).x, pt.elementAt(pathPointsIndex).y);
        */

        //Selection
        if(selected) {
            glLineWidth(1);
            for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
                NxCurvePoint pathPoint = pathPoints.at(indexPathPoint);
                if(selectedPathPointPoint == indexPathPoint)
                    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
                else
                    glColor4f(color.redF(), color.greenF(), color.blueF(), 0.7);
                glBegin(GL_QUADS);
                glVertex3f(pathPoint.point.x() - renderOptions->objectSize/4, pathPoint.point.y() - renderOptions->objectSize/4, 0);
                glVertex3f(pathPoint.point.x() + renderOptions->objectSize/4, pathPoint.point.y() - renderOptions->objectSize/4, 0);
                glVertex3f(pathPoint.point.x() + renderOptions->objectSize/4, pathPoint.point.y() + renderOptions->objectSize/4, 0);
                glVertex3f(pathPoint.point.x() - renderOptions->objectSize/4, pathPoint.point.y() + renderOptions->objectSize/4, 0);
                glEnd();

                if(selectedPathPointControl == indexPathPoint)
                    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
                else
                    glColor4f(color.redF(), color.greenF(), color.blueF(), 0.7);
                glBegin(GL_LINE_STRIP);
                glVertex3f((pathPoint.point+pathPoint.c1).x() - renderOptions->objectSize/4, (pathPoint.point+pathPoint.c1).y() - renderOptions->objectSize/4, 0);
                glVertex3f((pathPoint.point+pathPoint.c1).x() + renderOptions->objectSize/4, (pathPoint.point+pathPoint.c1).y() - renderOptions->objectSize/4, 0);
                glVertex3f((pathPoint.point+pathPoint.c1).x() + renderOptions->objectSize/4, (pathPoint.point+pathPoint.c1).y() + renderOptions->objectSize/4, 0);
                glVertex3f((pathPoint.point+pathPoint.c1).x() - renderOptions->objectSize/4, (pathPoint.point+pathPoint.c1).y() + renderOptions->objectSize/4, 0);
                glVertex3f((pathPoint.point+pathPoint.c1).x() - renderOptions->objectSize/4, (pathPoint.point+pathPoint.c1).y() - renderOptions->objectSize/4, 0);
                glEnd();
            }
        }

        //End
        glPopMatrix();
    }
}

void NxCurve::addMousePointAt(const QPointF & _mousePos) {
    QPointF mousePos = _mousePos - pos;

    qint16 indexInsert = -1;
    QPointF minDeltaPosition(99999, 99999);
    for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++) {
        QPointF deltaPosition;

        QPointF deltaPositionTmp1, deltaPositionTmp2;
        if(indexPoint == 0)
            deltaPositionTmp1 = mousePos;
        else
            deltaPositionTmp1 = pathPoints.at(indexPoint-1).point - mousePos;
        deltaPositionTmp2 = pathPoints.at(indexPoint).point - mousePos;

        deltaPosition.setX(sqrt(deltaPositionTmp1.x()*deltaPositionTmp1.x()+deltaPositionTmp1.y()*deltaPositionTmp1.y()));
        deltaPosition.setY(sqrt(deltaPositionTmp2.x()*deltaPositionTmp2.x()+deltaPositionTmp2.y()*deltaPositionTmp2.y()));

        if((deltaPosition.x() < minDeltaPosition.x()) && (deltaPosition.y() < minDeltaPosition.y())) {
            minDeltaPosition = deltaPosition;
            indexInsert = indexPoint;
        }
    }

    if(indexInsert >= 0) {
        NxCurvePoint pt;
        pt.point = mousePos;
        if(indexInsert < pathPoints.count())
            pathPoints.insert(indexInsert, pt);
        else
            pathPoints.append(pt);
    }
}

void NxCurve::setPointAt(const QPointF & point, const QPointF & c1, const QPointF & c2) {
    setPointAt(pathPoints.count(), point, c1, c2);
}
void NxCurve::setPointAt(quint16 index, const QPointF & point, const QPointF & c1, const QPointF & c2) {
    NxCurvePoint pointStruct;
    pointStruct.point = point;
    pointStruct.c1 = c1;
    pointStruct.c2 = c2;
    if(index >= pathPoints.count())
        pathPoints.append(pointStruct);
    else
        pathPoints[index] = pointStruct;

    //Rebuild path
    path = QPainterPath();
    foreach(const NxCurvePoint & pathPoint, pathPoints) {
        if((pathPoint.c1 == QPointF(0, 0)) && (pathPoint.c2 == QPointF(0, 0)))
            path.lineTo(pathPoint.point);
        else if(pathPoint.c2 == QPointF(0, 0))
            path.quadTo(pathPoint.point+pathPoint.c1, pathPoint.point);
        else
            path.cubicTo(pathPoint.point+pathPoint.c1, pathPoint.point+pathPoint.c2, pathPoint.point);
        //path.cubicTo(pathPoint.point+pathPoint.c1, pathPoint.point+pathPoint.c2, pathPoint.point);
    }

    //Length
    pathLength = path.length();
    calcBoundingRect();
    computePoints();
}

void NxCurve::setSVG(const QString & pathData) {
    curveType = CurveTypeSVG;
    svgPath = pathData;
    path = QPainterPath();

    QStringList tokens = pathData.split(QRegExp("(?=[A-Za-z])"), QString::SkipEmptyParts);
    QPointF firstPoint;
    bool firstCommand = true;
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
        case 'A':
            //qDebug("arcAbs");
            break;
        case 'a':
            //qDebug("arcRel");
            break;
        case 'C':
            //qDebug("curvetoCubicAbs (%f %f - %f %f) %f %f", params.at(0), params.at(1), params.at(2), params.at(3), params.at(4), params.at(5));
            setPointAt(QPointF(params.at(4), params.at(5)), QPointF(params.at(0), params.at(1)) - QPointF(params.at(4), params.at(5)), QPointF(params.at(2), params.at(3)) - QPointF(params.at(4), params.at(5)));
            break;
        case 'c':
            //qDebug("curvetoCubicRel (%f %f - %f %f) %f %f", params.at(0), params.at(1), params.at(2), params.at(3), params.at(4), params.at(5));
            setPointAt(path.currentPosition() + QPointF(params.at(4), params.at(5)), QPointF(params.at(0), params.at(1)) - QPointF(params.at(4), params.at(5)), QPointF(params.at(2), params.at(3)) - QPointF(params.at(4), params.at(5)));
            break;
        case 'H':
            //qDebug("linetoHorizontalAbs %f", params.at(0));
            setPointAt(QPointF(params.at(0), path.currentPosition().y()));
            break;
        case 'h':
            //qDebug("linetoHorizontalRel %f", params.at(0));
            setPointAt(path.currentPosition() + QPointF(params.at(0), 0));
            break;
        case 'L':
            //qDebug("linetoAbs %f %f", params.at(0), params.at(1));
            setPointAt(QPointF(params.at(0), params.at(1)));
            break;
        case 'l':
            //qDebug("linetoRel %f %f", params.at(0), params.at(1));
            setPointAt(path.currentPosition() + QPointF(params.at(0), params.at(1)));
            break;
        case 'M':
            //qDebug("movetoAbs %f %f", params.at(0), params.at(1));
            setPointAt(QPointF(params.at(0), params.at(1)));
            break;
        case 'm':
            //qDebug("movetoRel %f %f", params.at(0), params.at(1));
            setPointAt(path.currentPosition() + QPointF(params.at(0), params.at(1)));
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
        case 'V':
            //qDebug("linetoVerticalAbs %f", params.at(0));
            setPointAt(QPointF(path.currentPosition().x(), params.at(0)));
            break;
        case 'v':
            //qDebug("linetoVerticalRel %f", params.at(0));
            setPointAt(path.currentPosition() + QPointF(0, params.at(0)));
            break;

        case 'Z':
        case 'z':
            //qDebug("closePath");
            setPointAt(firstPoint);
            break;
        }
        if(firstCommand)
            firstPoint = path.currentPosition();
        firstCommand = false;
    }

    //Scale
    translate(-firstPoint);
    resize(1, -1);
    pathLength = path.length();
    calcBoundingRect();
    computePoints();
    setPos(firstPoint);
}
void NxCurve::setSVG2(const QString & polylineData) {
    curveType = CurveTypeSVG2;
    svgPath = polylineData;
    path = QPainterPath();

    QStringList tokens = polylineData.split(" ", QString::SkipEmptyParts);
    QPointF firstPoint;
    bool firstCommand = true;
    foreach(const QString & token, tokens) {
        QStringList tokenParams = token.split(",", QString::SkipEmptyParts);
        if(tokenParams.count() == 2) {
            setPointAt(QPointF(tokenParams.at(0).toDouble(), tokenParams.at(1).toDouble()));
        }
        if(firstCommand)
            firstPoint = path.currentPosition();
        firstCommand = false;
    }

    //Scale
    translate(-firstPoint);
    resize(1, 1);
    pathLength = path.length();
    calcBoundingRect();
    computePoints();
    setPos(firstPoint);
}

void NxCurve::setImage(const QString & filename) {
    curveType = CurveTypeImage;
    imageFilename = filename;

    //Load image
    QFileInfo file(filename);
    QPixmap pixmap(filename);

    //Create mask
    QBitmap bitmap(pixmap.createHeuristicMask());
    bitmap.save(file.dir().absolutePath() + QDir::separator() + file.baseName() + "_mask.png");

    //Create path
    pathPoints.clear();
    path = QPainterPath();
    QPainterPath pathTmp = QPainterPath();
    pathTmp.addRegion(QRegion(bitmap));

    //Simplify path
    pathTmp = pathTmp.simplified();
    QPointF firstPoint;
    for(quint16 pathPointsIndex = 0 ; pathPointsIndex <= CURVE_PATH_POINTS ; pathPointsIndex++) {
        if(pathPointsIndex == 0)
            firstPoint = pathTmp.pointAtPercent(0);
        setPointAt(pathTmp.pointAtPercent(qMin(1.0F, qMax(0.0F, (float)pathPointsIndex/CURVE_PATH_POINTS))));
    }

    //Scale
    translate(-firstPoint);
    resize(1, -1);
    pathLength = path.length();
    calcBoundingRect();
    computePoints();
}
void NxCurve::setEllipse(const QSizeF & size) {
    curveType = CurveTypeEllipse;

    //Draw ellipse
    pathPoints.clear();
    path = QPainterPath();
    path.addEllipse(QPointF(0, 0), size.width(), size.height());

    //Calculations
    resize(1, 1);
    pathLength = path.length();
    calcBoundingRect();
    computePoints();
}

void NxCurve::setText(const QString & text, const QString & family) {
    curveType = CurveTypeText;
    textText = text;
    textFamily = family;
    QFont font(family);
    font.setPixelSize(50);

    //Draw text
    pathPoints.clear();
    path = QPainterPath();
    path.addText(0, 0, font, text);

    //Calculations
    resize(1, -1);
    pathLength = path.length();
    calcBoundingRect();
    computePoints();
}
void NxCurve::resize(qreal sizeFactorW, qreal sizeFactorH) {
    QSizeF sizeFactor(sizeFactorW, sizeFactorH);
    if((curveType == CurveTypeText) || (curveType == CurveTypeEllipse)) {
        QMatrix scale;
        scale.scale(sizeFactor.width(), sizeFactor.height());
        path = path * scale;
    }
    else {
        for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++)
            setPointAt(indexPoint, QPointF(pathPoints.at(indexPoint).point.x() * sizeFactor.width(), pathPoints.at(indexPoint).point.y() * sizeFactor.height()), QPointF(pathPoints.at(indexPoint).c1.x() * sizeFactor.width(), pathPoints.at(indexPoint).c1.y() * sizeFactor.height()), QPointF(pathPoints.at(indexPoint).c2.x() * sizeFactor.width(), pathPoints.at(indexPoint).c2.y() * sizeFactor.height()));
    }
}
void NxCurve::resize(const QSizeF & size) {
    QSizeF sizeFactor(size.width() / path.boundingRect().width(), size.height() / path.boundingRect().height());
    resize(sizeFactor.width(), sizeFactor.height());
}
void NxCurve::translate(const QPointF & point) {
    for(quint16 indexPoint = 0 ; indexPoint < pathPoints.count() ; indexPoint++)
        setPointAt(indexPoint, pathPoints.at(indexPoint).point + point, pathPoints.at(indexPoint).c1, pathPoints.at(indexPoint).c2);
}
void NxCurve::computePoints() {
    for(quint16 pathPointsIndex = 0 ; pathPointsIndex <= CURVE_PATH_POINTS ; pathPointsIndex++)
        pathPointsCache[pathPointsIndex] = getPointAt((float)pathPointsIndex/(float)CURVE_PATH_POINTS);
}
