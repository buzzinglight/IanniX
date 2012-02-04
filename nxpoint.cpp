#include "nxpoint.h"
#include <QtCore/qdebug.h>
#include <QtCore/qvariant.h>
#include <QtCore/qmath.h>

qreal NxPoint::length() const {
    return qSqrt(xp * xp + yp * yp + zp * zp + tp * tp);
}

qreal NxPoint::lengthSquared() const {
    return xp * xp + yp * yp + zp * zp + tp * tp;
}

NxPoint NxPoint::normalized() const {
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp) +
                 double(zp) * double(zp) +
                 double(tp) * double(tp);
    if (qFuzzyIsNull(len - 1.0f))
        return *this;
    else if (!qFuzzyIsNull(len))
        return *this / qSqrt(len);
    else
        return NxPoint();
}

void NxPoint::normalize() {
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp) +
                 double(zp) * double(zp) +
                 double(tp) * double(tp);
    if (qFuzzyIsNull(len - 1.0f) || qFuzzyIsNull(len))
        return;

    len = qSqrt(len);

    xp /= len;
    yp /= len;
    zp /= len;
    tp /= len;
}

qreal NxPoint::dotProduct(const NxPoint& v1, const NxPoint& v2) {
    return v1.xp * v2.xp + v1.yp * v2.yp + v1.zp * v2.zp + v1.tp * v2.tp;
}
