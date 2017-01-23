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

#include "nxrect.h"

NxRect NxRect::normalized() const {
    NxRect r = *this;
    if (r.w < 0) {
        r.xp += r.w;
        r.w = -r.w;
        r.l = r.l;
    }
    if (r.h < 0) {
        r.yp += r.h;
        r.h = -r.h;
        r.l = r.l;
    }
    return r;
}

bool NxRect::contains(const NxPoint &p) const {
    qreal l = xp;
    qreal r = xp;
    if (w < 0)
        l += w;
    else
        r += w;
    if (l == r) // null rect
        return false;

    if (p.x() < l || p.x() > r)
        return false;

    qreal t = yp;
    qreal b = yp;
    if (h < 0)
        t += h;
    else
        b += h;
    if (t == b) // null rect
        return false;

    if (p.y() < t || p.y() > b)
        return false;

    return true;
}

bool NxRect::contains(const NxRect &r) const {
    qreal l1 = xp;
    qreal r1 = xp;
    if (w < 0)
        l1 += w;
    else
        r1 += w;
    if (l1 == r1) // null rect
        return false;

    qreal l2 = r.xp;
    qreal r2 = r.xp;
    if (r.w < 0)
        l2 += r.w;
    else
        r2 += r.w;
    if (l2 == r2) // null rect
        return false;

    if (l2 < l1 || r2 > r1)
        return false;

    qreal t1 = yp;
    qreal b1 = yp;
    if (h < 0)
        t1 += h;
    else
        b1 += h;
    if (t1 == b1) // null rect
        return false;

    qreal t2 = r.yp;
    qreal b2 = r.yp;
    if (r.h < 0)
        t2 += r.h;
    else
        b2 += r.h;
    if (t2 == b2) // null rect
        return false;

    if (t2 < t1 || b2 > b1)
        return false;

    /*
    qreal f1 = zp;
    qreal ff1 = zp;
    if (l < 0)
        f1 += l;
    else
        ff1 += l;
    if (f1 == ff1) // null rect
        return false;

    qreal f2 = r.zp;
    qreal ff2 = r.zp;
    if (r.h < 0)
        f2 += r.l;
    else
        ff2 += r.l;
    if (f2 == f2) // null rect
        return false;

    if (f2 < ff1 || f2 > ff1)
        return false;
    */
    return true;
}


NxRect NxRect::operator|(const NxRect &r) const {
    if (isNull())
        return r;
    if (r.isNull())
        return *this;

    qreal left = xp;
    qreal right = xp;
    if (w < 0)
        left += w;
    else
        right += w;

    if (r.w < 0) {
        left = qMin(left, r.xp + r.w);
        right = qMax(right, r.xp);
    } else {
        left = qMin(left, r.xp);
        right = qMax(right, r.xp + r.w);
    }

    qreal top = yp;
    qreal bottom = yp;
    if (h < 0)
        top += h;
    else
        bottom += h;

    if (r.h < 0) {
        top = qMin(top, r.yp + r.h);
        bottom = qMax(bottom, r.yp);
    } else {
        top = qMin(top, r.yp);
        bottom = qMax(bottom, r.yp + r.h);
    }

    return NxRect(left, top, right - left, bottom - top);
}

NxRect NxRect::operator&(const NxRect &r) const {
    qreal l1 = xp;
    qreal r1 = xp;
    if (w < 0)
        l1 += w;
    else
        r1 += w;
    if (l1 == r1) // null rect
        return NxRect();

    qreal l2 = r.xp;
    qreal r2 = r.xp;
    if (r.w < 0)
        l2 += r.w;
    else
        r2 += r.w;
    if (l2 == r2) // null rect
        return NxRect();

    if (l1 >= r2 || l2 >= r1)
        return NxRect();

    qreal t1 = yp;
    qreal b1 = yp;
    if (h < 0)
        t1 += h;
    else
        b1 += h;
    if (t1 == b1) // null rect
        return NxRect();

    qreal t2 = r.yp;
    qreal b2 = r.yp;
    if (r.h < 0)
        t2 += r.h;
    else
        b2 += r.h;
    if (t2 == b2) // null rect
        return NxRect();

    if (t1 >= b2 || t2 >= b1)
        return NxRect();

    NxRect tmp;
    tmp.xp = qMax(l1, l2);
    tmp.yp = qMax(t1, t2);
    tmp.w = qMin(r1, r2) - tmp.xp;
    tmp.h = qMin(b1, b2) - tmp.yp;
    return tmp;
}


bool NxRect::intersects(const NxRect &r) const {
    qreal l1 = xp;
    qreal r1 = xp;
    if (w < 0)
        l1 += w;
    else
        r1 += w;
    if (l1 == r1) // null rect
        return false;

    qreal l2 = r.xp;
    qreal r2 = r.xp;
    if (r.w < 0)
        l2 += r.w;
    else
        r2 += r.w;
    if (l2 == r2) // null rect
        return false;

    if (l1 >= r2 || l2 >= r1)
        return false;

    qreal t1 = yp;
    qreal b1 = yp;
    if (h < 0)
        t1 += h;
    else
        b1 += h;
    if (t1 == b1) // null rect
        return false;

    qreal t2 = r.yp;
    qreal b2 = r.yp;
    if (r.h < 0)
        t2 += r.h;
    else
        b2 += r.h;
    if (t2 == b2) // null rect
        return false;

    if (t1 >= b2 || t2 >= b1)
        return false;

    return true;
}
