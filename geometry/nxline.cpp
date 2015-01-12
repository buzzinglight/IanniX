/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

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

#include "nxline.h"

bool NxLine::isNull() const {
    return (qFuzzyCompare(pt1.x(), pt2.x()) && qFuzzyCompare(pt1.y(), pt2.y())) ? true : false;
}

qreal NxLine::length() const {
    qreal x = pt2.x() - pt1.x();
    qreal y = pt2.y() - pt1.y();
    qreal z = pt2.z() - pt1.z();
    return qSqrt(x*x + y*y + z*z);
}

NxLine::IntersectType NxLine::intersect(const NxLine &l, NxPoint *intersectionPoint) const {
    // ipmlementation is based on Graphics Gems III's "Faster Line Segment Intersection"
    const NxPoint a = pt2 - pt1;
    const NxPoint b = l.pt1 - l.pt2;
    const NxPoint c = pt1 - l.pt1;

    const qreal denominator = a.y() * b.x() - a.x() * b.y();
    if (denominator == 0 || !qIsFinite(denominator))
        return NoIntersection;

    const qreal reciprocal = 1 / denominator;
    const qreal na = (b.y() * c.x() - b.x() * c.y()) * reciprocal;
    if (intersectionPoint)
        *intersectionPoint = pt1 + a * na;

    if (na < 0 || na > 1)
        return UnboundedIntersection;

    const qreal nb = (a.x() * c.y() - a.y() * c.x()) * reciprocal;
    if (nb < 0 || nb > 1)
        return UnboundedIntersection;

    return BoundedIntersection;
}
