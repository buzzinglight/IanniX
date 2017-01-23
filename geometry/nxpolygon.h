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
