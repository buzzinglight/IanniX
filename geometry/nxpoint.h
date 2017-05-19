/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (https://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

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
    NxPoint(qreal xpos, qreal ypos, qreal zpos, qreal sx, qreal sy, qreal sz);
    NxPoint(qreal xpos, qreal ypos, qreal zpos, qreal sx, qreal sy, qreal sz, qreal angleZ);
    NxPoint(float xpos, float ypos, float zpos, int dummy);

    bool isNull() const;

    qreal x() const;
    qreal y() const;
    qreal z() const;
    qreal sx() const;
    qreal sy() const;
    qreal sz() const;

    qreal angleZ() const;

    void setX(qreal x);
    void setY(qreal y);
    void setZ(qreal z);
    void setSx(qreal sx);
    void setSy(qreal sy);
    void setSz(qreal sz);

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
    float xp, yp, zp;
    float sxp, syp, szp;
    float angleZp;
};
Q_DECLARE_TYPEINFO(NxPoint, Q_MOVABLE_TYPE);

inline NxPoint::NxPoint()                                        : xp(0.0f), yp(0.0f), zp(0.0f), sxp(0.0f), syp(0.0f), szp(0.0f) {}
inline NxPoint::NxPoint(qreal xpos, qreal ypos)                  : xp(xpos), yp(ypos), zp(0.0f), sxp(0.0f), syp(0.0f), szp(0.0f) {}
inline NxPoint::NxPoint(qreal xpos, qreal ypos, qreal zpos)      : xp(xpos), yp(ypos), zp(zpos), sxp(0.0f), syp(0.0f), szp(0.0f) {}
inline NxPoint::NxPoint(float xpos, float ypos, float zpos, int) : xp(xpos), yp(ypos), zp(zpos), sxp(0.0f), syp(0.0f), szp(0.0f) {}
inline NxPoint::NxPoint(qreal xpos, qreal ypos, qreal zpos, qreal sx, qreal sy, qreal sz) : xp(xpos), yp(ypos), zp(zpos), sxp(sx), syp(sy), szp(sz) {}
inline NxPoint::NxPoint(qreal xpos, qreal ypos, qreal zpos, qreal sx, qreal sy, qreal sz, qreal angleZ) : xp(xpos), yp(ypos), zp(zpos), sxp(sx), syp(sy), szp(sz), angleZp(angleZ) {}

inline bool NxPoint::isNull() const {
    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp);
}

inline qreal NxPoint::x() const  { return qreal(xp); }
inline qreal NxPoint::y() const  { return qreal(yp); }
inline qreal NxPoint::z() const  { return qreal(zp); }
inline qreal NxPoint::sx() const { return qreal(sxp); }
inline qreal NxPoint::sy() const { return qreal(syp); }
inline qreal NxPoint::sz() const { return qreal(szp); }
inline qreal NxPoint::angleZ() const { return qreal(angleZp); }

inline void NxPoint::setX(qreal aX)   { xp = aX; }
inline void NxPoint::setY(qreal aY)   { yp = aY; }
inline void NxPoint::setZ(qreal aZ)   { zp = aZ; }
inline void NxPoint::setSx(qreal aSx) { sxp = aSx; }
inline void NxPoint::setSy(qreal aSy) { syp = aSy; }
inline void NxPoint::setSz(qreal aSz) { szp = aSz; }

inline NxPoint &NxPoint::operator+=(const NxPoint &vector) {
    xp += vector.xp;
    yp += vector.yp;
    zp += vector.zp;

    sxp += vector.sxp;
    syp += vector.syp;
    szp += vector.szp;

    return *this;
}

inline NxPoint &NxPoint::operator-=(const NxPoint &vector) {
    xp -= vector.xp;
    yp -= vector.yp;
    zp -= vector.zp;

    sxp -= vector.sxp;
    syp -= vector.syp;
    szp -= vector.szp;

    return *this;
}

inline NxPoint &NxPoint::operator*=(qreal factor) {
    xp *= factor;
    yp *= factor;
    zp *= factor;

    sxp *= factor;
    syp *= factor;
    szp *= factor;

    return *this;
}

inline NxPoint &NxPoint::operator*=(const NxPoint &vector) {
    xp *= vector.xp;
    yp *= vector.yp;
    zp *= vector.zp;

    sxp *= vector.sxp;
    syp *= vector.syp;
    szp *= vector.szp;

    return *this;
}

inline NxPoint &NxPoint::operator/=(qreal divisor) {
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;

    sxp *= divisor;
    syp *= divisor;
    szp *= divisor;

    return *this;
}

inline bool operator==(const NxPoint &v1, const NxPoint &v2) {
    return v1.xp == v2.xp && v1.yp == v2.yp && v1.zp == v2.zp && v1.sxp == v2.sxp && v1.syp == v2.syp && v1.szp == v2.szp;
}

inline bool operator!=(const NxPoint &v1, const NxPoint &v2) {
    return v1.xp != v2.xp || v1.yp != v2.yp || v1.zp != v2.zp || v1.sxp != v2.sxp || v1.syp != v2.syp || v1.szp != v2.szp;
}

inline const NxPoint operator+(const NxPoint &v1, const NxPoint &v2) {
    return NxPoint(v1.xp + v2.xp, v1.yp + v2.yp, v1.zp + v2.zp, v1.sxp + v2.sxp, v1.syp + v2.syp, v1.szp + v2.szp);
}

inline const NxPoint operator-(const NxPoint &v1, const NxPoint &v2) {
    return NxPoint(v1.xp - v2.xp, v1.yp - v2.yp, v1.zp - v2.zp, v1.sxp - v2.sxp, v1.syp - v2.syp, v1.szp - v2.szp);
}

inline const NxPoint operator*(qreal factor, const NxPoint &vector) {
    return NxPoint(vector.xp * factor, vector.yp * factor, vector.zp * factor, vector.sxp * factor, vector.syp * factor, vector.szp * factor);
}

inline const NxPoint operator*(const NxPoint &vector, qreal factor) {
    return NxPoint(vector.xp * factor, vector.yp * factor, vector.zp * factor, vector.sxp * factor, vector.syp * factor, vector.szp * factor);
}

inline const NxPoint operator*(const NxPoint &v1, const NxPoint& v2) {
    return NxPoint(v1.xp * v2.xp, v1.yp * v2.yp, v1.zp * v2.zp, v1.sxp * v2.sxp, v1.syp * v2.syp, v1.szp * v2.szp);
}

inline const NxPoint operator-(const NxPoint &vector) {
    return NxPoint(-vector.xp, -vector.yp, -vector.zp, -vector.sxp, -vector.syp, -vector.szp);
}

inline const NxPoint operator/(const NxPoint &vector, qreal divisor) {
    return NxPoint(vector.xp / divisor, vector.yp / divisor, vector.zp / divisor, vector.sxp / divisor, vector.syp / divisor, vector.szp / divisor);
}

inline bool qFuzzyCompare(const NxPoint& v1, const NxPoint& v2) {
    return qFuzzyCompare(v1.xp, v2.xp) &&
            qFuzzyCompare(v1.yp, v2.yp) &&
            qFuzzyCompare(v1.zp, v2.zp) &&
            qFuzzyCompare(v1.sxp, v2.sxp) &&
            qFuzzyCompare(v1.syp, v2.syp) &&
            qFuzzyCompare(v1.szp, v2.szp);
}

#endif
