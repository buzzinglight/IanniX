#ifndef NXPOLYGON_H
#define NXPOLYGON_H

#include <QVector>
#include "nxpoint.h"
#include "nxrect.h"
#include "math.h"

class NxPolygon : public QVector<NxPoint> {
public:
    inline NxPolygon() {}
    inline ~NxPolygon() {}
    inline NxPolygon(int size);
    inline NxPolygon(const NxPolygon &a) : QVector<NxPoint>(a) {}
    inline NxPolygon(const QVector<NxPoint> &v) : QVector<NxPoint>(v) {}
    NxPolygon(const QPolygon &a);

    NxRect boundingRect() const;
    bool containsPoint(const NxPoint &pt, Qt::FillRule fillRule) const;
};

inline NxPolygon::NxPolygon(int asize) : QVector<NxPoint>(asize) {}

#endif // NXPOLYGON_H
