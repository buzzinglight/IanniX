#ifndef NXCURVE_H
#define NXCURVE_H

#include <QPainterPath>
#include "nxobject.h"

#define CURVE_PATH_POINTS   300

typedef struct _NxCurvePoint {
    QPointF point;
    QPointF c1, c2;
} NxCurvePoint;
Q_DECLARE_TYPEINFO(NxCurvePoint, Q_PRIMITIVE_TYPE);

enum CurveType       { CurveTypePoints, CurveTypeSVG, CurveTypeSVG2, CurveTypeImage, CurveTypeText, CurveTypeEllipse };

class NxCurve : public NxObject {
    Q_OBJECT;
    Q_PROPERTY(qreal pathLength READ getPathLength);
    Q_PROPERTY(CurveType curveType READ getCurveType);
    Q_PROPERTY(QSizeF resize READ getResize WRITE setResize);
    Q_PROPERTY(qreal resizeF READ getResizeF WRITE setResizeF);

public:
    explicit NxCurve(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions);

private:
    QPainterPath path;
    qreal pathLength;
    QPointF pathPointsCache[CURVE_PATH_POINTS+1];
    QVector<NxObject*> cursors;
    QVector<NxCurvePoint> pathPoints;
    qint16 selectedPathPointPoint, selectedPathPointControl;
    CurveType curveType;
    QString svgPath, imageFilename, textText, textFamily;
public:
    inline void isOnPathPoint(const QRectF & point) {
        if(!isDrag) {
            selectedPathPointPoint = -1;
            selectedPathPointControl = -1;
            for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++) {
                if(point.contains(pathPoints.at(indexPathPoint).point)) {
                    selectedPathPointPoint = indexPathPoint;
                    selectedPathPointControl = -1;
                    break;
                }
                else if(point.contains(pathPoints.at(indexPathPoint).point + pathPoints.at(indexPathPoint).c1)) {
                    selectedPathPointPoint = -1;
                    selectedPathPointControl = indexPathPoint;
                    break;
                }
            }
        }
    }
    inline CurveType getCurveType() const {
        return curveType;
    }

    inline void dragStart() {
        isDrag = true;
        if(selectedPathPointPoint >= 0)
            posDrag = pathPoints.at(selectedPathPointPoint).point;
        else if(selectedPathPointControl >= 0)
            posDrag = pathPoints.at(selectedPathPointControl).c1;
        else
            posDrag = pos;
    }
    inline void drag(const QPointF & translation) {
        if(selectedPathPointPoint >= 0)
            setPointAt(selectedPathPointPoint, posDrag + translation, pathPoints.value(selectedPathPointPoint).c1, pathPoints.value(selectedPathPointPoint).c2);
        else if(selectedPathPointControl >= 0)
            setPointAt(selectedPathPointControl, pathPoints.value(selectedPathPointControl).point, posDrag + translation, pathPoints.value(selectedPathPointControl).c2);
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
    inline const QVector<NxObject*> & getCursors() const {
        return cursors;
    }
    inline qreal getMaxOffset() const {
        //qreal maxOffset = 0;
        return cursors.count()-1;
    }

    inline const QPainterPath & getPath() const { return path; }
    inline qreal getPathLength() const  { return pathLength; }
    void addMousePointAt(const QPointF & _mousePos);
    void setPointAt(quint16 index, const QPointF & point, const QPointF & c1 = QPointF(0, 0), const QPointF & c2 = QPointF(0, 0));
    void setPointAt(const QPointF & point, const QPointF & c1 = QPointF(0, 0), const QPointF & c2 = QPointF(0, 0));
    void setSVG(const QString & pathData);
    void setSVG2(const QString & polylineData);
    void setImage(const QString & filename);
    void setText(const QString & text, const QString & family);
    void setEllipse(const QSizeF & size);
    void resize(const QSizeF & size);
    void resize(qreal sizeFactorW, qreal sizeFactorH);
    void translate(const QPointF & point);
    void computePoints();
    inline QPointF getPointAt(float percent) {
        return path.pointAtPercent(qMin(1.0F, qMax(0.0F, percent)));
    }

    inline void setResize(const QSizeF & size) {
        resize(size);
        pathLength = path.length();
        calcBoundingRect();
        computePoints();
        calculate();
        foreach(NxObject *object, cursors)
            object->calculate();
    }
    inline const QSizeF getResize() const {
        return boundingRect.size();
    }
    inline void setResizeF(qreal sizeF) {
        resize(sizeF, sizeF);
        pathLength = path.length();
        calcBoundingRect();
        computePoints();
        calculate();
        foreach(NxObject *object, cursors)
            object->calculate();
    }
    inline qreal getResizeF() const {
        return 0;
    }

public:
    inline void calculate() {
        foreach(NxObject *object, cursors)
            object->calculate();
    }
    inline void calcBoundingRect() {
        //Bounding rect
        if(path.elementCount() > 0)
            boundingRect = path.boundingRect();
        boundingRect.translate(pos);
        boundingRect = boundingRect.normalized();
    }
    inline bool isMouseHover(const QPointF & mouse) {
        if(path.intersects(QRectF((mouse - pos) - QPointF(renderOptions->objectSize/2, renderOptions->objectSize/2), (mouse - pos) + QPointF(renderOptions->objectSize/2, renderOptions->objectSize/2))))
            return true;
        else
            return false;
    }


    inline void addCursor(NxObject *cursor) {
        cursors.append(cursor);
    }
    inline void removeCursor(NxObject *cursor) {
        qint16 index = cursors.lastIndexOf(cursor);
        if(index >= 0)
            cursors.remove(index);
    }

    QString serializeCustom() {
        QString retour = "";
        if(curveType == CurveTypeEllipse) {
            retour += QString(COMMAND_CURVE_ELL + " %1 %2 %3").arg("current").arg(getResize().width()).arg(getResize().height()) + COMMAND_END;
            retour += QString(COMMAND_RESIZE + " %1 %2 %3").arg("current").arg(getResize().width()).arg(getResize().height()) + COMMAND_END;
        }
        else if(curveType == CurveTypeText) {
            retour += QString(COMMAND_CURVE_TXT + " %1 1 %2 %3").arg("current").arg(textFamily).arg(textText) + COMMAND_END;
            retour += QString(COMMAND_RESIZE + " %1 %2 %3").arg("current").arg(getResize().width()).arg(getResize().height()) + COMMAND_END;
        }
        else {
            for(quint16 indexPathPoint = 0 ; indexPathPoint < pathPoints.count() ; indexPathPoint++)
                retour += QString(COMMAND_CURVE_POINT + " %1 %2 %3 %4 %5 %6 %7 %8").arg("current").arg(indexPathPoint).arg(pathPoints.at(indexPathPoint).point.x()).arg(pathPoints.at(indexPathPoint).point.y()).arg(pathPoints.at(indexPathPoint).c1.x()).arg(pathPoints.at(indexPathPoint).c1.y()).arg(pathPoints.at(indexPathPoint).c2.x()).arg(pathPoints.at(indexPathPoint).c2.y()) + COMMAND_END;
            retour += QString(COMMAND_LINE + " %1 %2 %3").arg("current").arg(getLineStipple()).arg(getLineFactor()) + COMMAND_END;
        }
        foreach(NxObject *cursor, cursors)
            retour += cursor->serialize();
        return retour;
    }

public:
    void paint();

};

#endif // NXCURVE_H
