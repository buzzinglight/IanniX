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

#include "nxpoint.h"
#include <QtCore/qdebug.h>
#include <QtCore/qvariant.h>
#include <QtCore/qmath.h>

qreal NxPoint::length() const {
    return qSqrt(xp * xp + yp * yp + zp * zp);
}

qreal NxPoint::lengthSquared() const {
    return xp * xp + yp * yp + zp * zp;
}

NxPoint NxPoint::normalized() const {
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp) +
                 double(zp) * double(zp);
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
                 double(zp) * double(zp);
    if (qFuzzyIsNull(len - 1.0f) || qFuzzyIsNull(len))
        return;

    len = qSqrt(len);

    xp /= len;
    yp /= len;
    zp /= len;
}

qreal NxPoint::dotProduct(const NxPoint& v1, const NxPoint& v2) {
    return v1.xp * v2.xp + v1.yp * v2.yp + v1.zp * v2.zp;
}
