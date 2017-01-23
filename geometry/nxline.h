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

#ifndef NXLINE_H
#define NXLINE_H

#include <QtCore/qmath.h>
#include <qnumeric.h>
#include "nxpoint.h"

class NxLine {
public:

    enum IntersectType { NoIntersection, BoundedIntersection, UnboundedIntersection };

    inline NxLine();
    inline NxLine(const NxPoint &pt1, const NxPoint &pt2);
    inline NxLine(qreal x1, qreal y1, qreal x2, qreal y2);
    inline NxLine(qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2);

    bool isNull() const;

    inline NxPoint p1() const;
    inline NxPoint p2() const;

    inline qreal x1() const;
    inline qreal y1() const;
    inline qreal z1() const;

    inline qreal x2() const;
    inline qreal y2() const;
    inline qreal z2() const;

    inline qreal dx() const;
    inline qreal dy() const;
    inline qreal dz() const;

    qreal length() const;
    void setLength(qreal len);

    // ### Qt 5: rename intersects() or intersection() and rename IntersectType IntersectionType
    IntersectType intersect(const NxLine &l, NxPoint *intersectionPoint) const;

    NxPoint pointAt(qreal t) const;
    inline void translate(const NxPoint &p);
    inline void translate(qreal dx, qreal dy, qreal dz);

    inline NxLine translated(const NxPoint &p) const;
    inline NxLine translated(qreal dx, qreal dy, qreal dz) const;

    inline void setP1(const NxPoint &p1);
    inline void setP2(const NxPoint &p2);
    inline void setPoints(const NxPoint &p1, const NxPoint &p2);
    inline void setLine(qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2);

    inline bool operator==(const NxLine &d) const;
    inline bool operator!=(const NxLine &d) const { return !(*this == d); }

private:
    NxPoint pt1, pt2;
};
Q_DECLARE_TYPEINFO(NxLine, Q_MOVABLE_TYPE);

/*******************************************************************************
 * class NxLine inline members
 *******************************************************************************/

inline NxLine::NxLine()
{
}

inline NxLine::NxLine(const NxPoint &apt1, const NxPoint &apt2)
    : pt1(apt1), pt2(apt2)
{
}

inline NxLine::NxLine(qreal x1pos, qreal y1pos, qreal x2pos, qreal y2pos)
    : pt1(x1pos, y1pos, 0), pt2(x2pos, y2pos, 0)
{
}

inline NxLine::NxLine(qreal x1pos, qreal y1pos, qreal z1pos, qreal x2pos, qreal y2pos, qreal z2pos)
    : pt1(x1pos, y1pos, z1pos), pt2(x2pos, y2pos, z2pos)
{
}

inline qreal NxLine::x1() const
{
    return pt1.x();
}

inline qreal NxLine::y1() const
{
    return pt1.y();
}

inline qreal NxLine::z1() const
{
    return pt1.z();
}

inline qreal NxLine::x2() const
{
    return pt2.x();
}

inline qreal NxLine::y2() const
{
    return pt2.y();
}

inline qreal NxLine::z2() const
{
    return pt2.z();
}

inline NxPoint NxLine::p1() const
{
    return pt1;
}

inline NxPoint NxLine::p2() const
{
    return pt2;
}

inline qreal NxLine::dx() const
{
    return pt2.x() - pt1.x();
}

inline qreal NxLine::dy() const
{
    return pt2.y() - pt1.y();
}

inline qreal NxLine::dz() const
{
    return pt2.z() - pt1.z();
}

inline void NxLine::translate(const NxPoint &point)
{
    pt1 += point;
    pt2 += point;
}

inline void NxLine::translate(qreal adx, qreal ady, qreal adz)
{
    this->translate(NxPoint(adx, ady, adz));
}

inline NxLine NxLine::translated(const NxPoint &p) const
{
    return NxLine(pt1 + p, pt2 + p);
}

inline NxLine NxLine::translated(qreal adx, qreal ady, qreal adz) const
{
    return translated(NxPoint(adx, ady, adz));
}

inline NxPoint NxLine::pointAt(qreal t) const
{
    qreal vx = pt2.x() - pt1.x();
    qreal vy = pt2.y() - pt1.y();
    qreal vz = pt2.z() - pt1.z();
    return NxPoint(pt1.x() + vx * t, pt1.y() + vy * t, pt2.z() + vz * t);
}


inline void NxLine::setP1(const NxPoint &aP1)
{
    pt1 = aP1;
}

inline void NxLine::setP2(const NxPoint &aP2)
{
    pt2 = aP2;
}

inline void NxLine::setPoints(const NxPoint &aP1, const NxPoint &aP2)
{
    pt1 = aP1;
    pt2 = aP2;
}

inline void NxLine::setLine(qreal aX1, qreal aY1, qreal aZ1, qreal aX2, qreal aY2, qreal aZ2)
{
    pt1 = NxPoint(aX1, aY1, aZ1);
    pt2 = NxPoint(aX2, aY2, aZ2);
}


inline bool NxLine::operator==(const NxLine &d) const
{
    return pt1 == d.pt1 && pt2 == d.pt2;
}


#endif // NXLINE_H
