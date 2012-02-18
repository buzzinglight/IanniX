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

#ifndef NXPOINT_H
#define NXPOINT_H

#include <QVariant>

class NxPoint{
public:
    NxPoint();
    NxPoint(qreal xpos, qreal ypos);
    NxPoint(qreal xpos, qreal ypos, qreal zpos);
    NxPoint(qreal xpos, qreal ypos, qreal zpos, qreal tpos);

    bool isNull() const;

    qreal x() const;
    qreal y() const;
    qreal z() const;
    qreal t() const;

    void setX(qreal x);
    void setY(qreal y);
    void setZ(qreal z);
    void setT(qreal t);

    qreal length() const;
    qreal lengthSquared() const;

    NxPoint normalized() const;
    void normalize();

    NxPoint &operator+=(const NxPoint &vector);
    NxPoint &operator-=(const NxPoint &vector);
    NxPoint &operator*=(qreal factor);
    NxPoint &operator*=(const NxPoint &vector);
    NxPoint &operator/=(qreal divisor);

    static qreal dotProduct(const NxPoint& v1, const NxPoint& v2);

    friend inline bool operator==(const NxPoint &v1, const NxPoint &v2);
    friend inline bool operator!=(const NxPoint &v1, const NxPoint &v2);
    friend inline const NxPoint operator+(const NxPoint &v1, const NxPoint &v2);
    friend inline const NxPoint operator-(const NxPoint &v1, const NxPoint &v2);
    friend inline const NxPoint operator*(qreal factor, const NxPoint &vector);
    friend inline const NxPoint operator*(const NxPoint &vector, qreal factor);
    friend inline const NxPoint operator*(const NxPoint &v1, const NxPoint& v2);
    friend inline const NxPoint operator-(const NxPoint &vector);
    friend inline const NxPoint operator/(const NxPoint &vector, qreal divisor);

    friend inline bool qFuzzyCompare(const NxPoint& v1, const NxPoint& v2);

    QPoint toPoint() const;
    QPointF toPointF() const;

private:
    float xp, yp, zp, tp;

    NxPoint(float xpos, float ypos, float zpos, float wpos, int dummy);
};
Q_DECLARE_TYPEINFO(NxPoint, Q_MOVABLE_TYPE);

inline NxPoint::NxPoint() : xp(0.0f), yp(0.0f), zp(0.0f), tp(0.0f) {}

inline NxPoint::NxPoint(qreal xpos, qreal ypos) : xp(xpos), yp(ypos), zp(0.0f), tp(0.0f) {}

inline NxPoint::NxPoint(qreal xpos, qreal ypos, qreal zpos) : xp(xpos), yp(ypos), zp(zpos), tp(0.0f) {}

inline NxPoint::NxPoint(qreal xpos, qreal ypos, qreal zpos, qreal wpos) : xp(xpos), yp(ypos), zp(zpos), tp(wpos) {}

inline NxPoint::NxPoint(float xpos, float ypos, float zpos, float wpos, int) : xp(xpos), yp(ypos), zp(zpos), tp(wpos) {}

inline bool NxPoint::isNull() const {
    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp) && qIsNull(tp);
}

inline qreal NxPoint::x() const { return qreal(xp); }
inline qreal NxPoint::y() const { return qreal(yp); }
inline qreal NxPoint::z() const { return qreal(zp); }
inline qreal NxPoint::t() const { return qreal(tp); }

inline void NxPoint::setX(qreal aX) { xp = aX; }
inline void NxPoint::setY(qreal aY) { yp = aY; }
inline void NxPoint::setZ(qreal aZ) { zp = aZ; }
inline void NxPoint::setT(qreal aT) { tp = aT; }

inline NxPoint &NxPoint::operator+=(const NxPoint &vector) {
    xp += vector.xp;
    yp += vector.yp;
    zp += vector.zp;
    tp += vector.tp;
    return *this;
}

inline NxPoint &NxPoint::operator-=(const NxPoint &vector) {
    xp -= vector.xp;
    yp -= vector.yp;
    zp -= vector.zp;
    tp -= vector.tp;
    return *this;
}

inline NxPoint &NxPoint::operator*=(qreal factor) {
    xp *= factor;
    yp *= factor;
    zp *= factor;
    tp *= factor;
    return *this;
}

inline NxPoint &NxPoint::operator*=(const NxPoint &vector) {
    xp *= vector.xp;
    yp *= vector.yp;
    zp *= vector.zp;
    tp *= vector.tp;
    return *this;
}

inline NxPoint &NxPoint::operator/=(qreal divisor) {
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;
    tp /= divisor;
    return *this;
}

inline bool operator==(const NxPoint &v1, const NxPoint &v2) {
    return v1.xp == v2.xp && v1.yp == v2.yp && v1.zp == v2.zp && v1.tp == v2.tp;
}

inline bool operator!=(const NxPoint &v1, const NxPoint &v2) {
    return v1.xp != v2.xp || v1.yp != v2.yp || v1.zp != v2.zp || v1.tp != v2.tp;
}

inline const NxPoint operator+(const NxPoint &v1, const NxPoint &v2) {
    return NxPoint(v1.xp + v2.xp, v1.yp + v2.yp, v1.zp + v2.zp, v1.tp + v2.tp, 1);
}

inline const NxPoint operator-(const NxPoint &v1, const NxPoint &v2) {
    return NxPoint(v1.xp - v2.xp, v1.yp - v2.yp, v1.zp - v2.zp, v1.tp - v2.tp, 1);
}

inline const NxPoint operator*(qreal factor, const NxPoint &vector) {
    return NxPoint(vector.xp * factor, vector.yp * factor, vector.zp * factor, vector.tp * factor, 1);
}

inline const NxPoint operator*(const NxPoint &vector, qreal factor) {
    return NxPoint(vector.xp * factor, vector.yp * factor, vector.zp * factor, vector.tp * factor, 1);
}

inline const NxPoint operator*(const NxPoint &v1, const NxPoint& v2) {
    return NxPoint(v1.xp * v2.xp, v1.yp * v2.yp, v1.zp * v2.zp, v1.tp * v2.tp, 1);
}

inline const NxPoint operator-(const NxPoint &vector) {
    return NxPoint(-vector.xp, -vector.yp, -vector.zp, -vector.tp, 1);
}

inline const NxPoint operator/(const NxPoint &vector, qreal divisor) {
    return NxPoint(vector.xp / divisor, vector.yp / divisor, vector.zp / divisor, vector.tp / divisor, 1);
}

inline bool qFuzzyCompare(const NxPoint& v1, const NxPoint& v2) {
    return qFuzzyCompare(v1.xp, v2.xp) &&
           qFuzzyCompare(v1.yp, v2.yp) &&
           qFuzzyCompare(v1.zp, v2.zp) &&
           qFuzzyCompare(v1.tp, v2.tp);
}

#endif
