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

#include "nxpolygon.h"

/*
static void qt_polygon_isect_line(const NxPoint &p1, const NxPoint &p2, const NxPoint &pos, int *winding)
{
    qreal x1 = p1.x();
    qreal y1 = p1.y();
    //qreal z1 = p1.z();
    qreal x2 = p2.x();
    qreal y2 = p2.y();
    //qreal z2 = p2.z();
    qreal y = pos.y();

    int dir = 1;

    if (qFuzzyCompare(y1, y2)) {
        // ignore horizontal lines according to scan conversion rule
        return;
    } else if (y2 < y1) {
        qreal x_tmp = x2; x2 = x1; x1 = x_tmp;
        qreal y_tmp = y2; y2 = y1; y1 = y_tmp;
        dir = -1;
    }

    if (y >= y1 && y < y2) {
        qreal x = x1 + ((x2 - x1) / (y2 - y1)) * (y - y1);

        // count up the winding number if we're
        if (x<=pos.x()) {
            (*winding) += dir;
        }
    }
}
*/

NxRect NxPolygon::boundingRect() const {
    if (isEmpty())
        return NxRect(0, 0, 0, 0, 0, 0);
    register const NxPoint *pd = constData();
    qreal minx, maxx, miny, maxy, minz, maxz;
    minx = maxx = pd->x();
    miny = maxy = pd->y();
    minz = maxz = pd->z();
    ++pd;
    for (int i = 1; i < size(); ++i) {
        if (pd->x() < minx)
            minx = pd->x();
        else if (pd->x() > maxx)
            maxx = pd->x();
        if (pd->y() < miny)
            miny = pd->y();
        else if (pd->y() > maxy)
            maxy = pd->y();
        if (pd->z() < minz)
            minz = pd->z();
        else if (pd->z() > maxz)
            maxz = pd->z();
        ++pd;
    }
    return NxRect(minx,miny,minz, maxx - minx, maxy - miny, maxz - minz);
}


bool NxPolygon::containsPoint(const NxPoint &pt, Qt::FillRule) const
{
    if (isEmpty())
        return false;

    /*
    int winding_number = 0;

    NxPoint last_pt = at(0);
    NxPoint last_start = at(0);
    for (int i = 1; i < size(); ++i) {
        const NxPoint &e = at(i);
        qt_polygon_isect_line(last_pt, e, pt, &winding_number);
        last_pt = e;
    }

    // implicitly close last subpath
    if (last_pt != last_start)
        qt_polygon_isect_line(last_pt, last_start, pt, &winding_number);

    return (fillRule == Qt::WindingFill
            ? (winding_number != 0)
            : ((winding_number % 2) != 0));
    */
    //qint16 sum = 0, sum2 = 0;
    bool first = true, direction = true, directionOk = false;
    for(quint16 i = 0 ; i < count() ; i++) {
        NxPoint pt0 = at(i), pt1 = at((i+1)%count());
        qreal val = (pt.y() - pt0.y()) * (pt1.x() - pt0.x()) - (pt.x() - pt0.x()) * (pt1.y() - pt0.y());
        if(val > 0) {
            if((!direction) && (directionOk) && (!first))
                return false;
            direction = true;
            directionOk = true;
        }
        else if(val < 0) {
            if((direction) && (directionOk) && (!first))
                return false;
            direction = false;
            directionOk = true;
        }
        first = false;
    }
    return true;
}
