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

#ifndef NXRECT_H
#define NXRECT_H

#include <QVariant>
#include "nxpoint.h"
#include "nxsize.h"

class NxRect {
public:
    NxRect() { xp = yp = zp = 0.; w = h = l = 0.; }
    NxRect(const NxPoint &topleft, const NxSize &size);
    NxRect(const NxPoint &topleft, const NxPoint &bottomRight);
    NxRect(qreal left, qreal top, qreal width, qreal height);
    NxRect(qreal left, qreal top, qreal z, qreal width, qreal height, qreal length);
    NxRect(const QRect &rect);

    bool isNull() const;
    bool isEmpty() const;
    bool isValid() const;
    NxRect normalized() const;

    inline qreal left()    const { return xp; }
    inline qreal right()   const { return xp + w; }
    inline qreal top()     const { return yp; }
    inline qreal bottom()  const { return yp + h; }
    inline qreal zTop()    const { return zp; }
    inline qreal zBottom() const { return zp + l; }

    inline qreal x() const;
    inline qreal y() const;
    inline qreal z() const;
    inline void setLeft(qreal pos);
    inline void setRight(qreal pos);
    inline void setTop(qreal pos);
    inline void setBottom(qreal pos);
    inline void setzTop(qreal pos);
    inline void setzBottom(qreal pos);
    inline void setX(qreal pos) { setLeft(pos); }
    inline void setY(qreal pos) { setTop(pos); }

    inline NxPoint topLeft() const     { return NxPoint(xp,   yp,   zp); }
    inline NxPoint topRight() const    { return NxPoint(xp+w, yp,   zp); }
    inline NxPoint bottomLeft() const  { return NxPoint(xp,   yp+h, zp+l); }
    inline NxPoint bottomRight() const { return NxPoint(xp+w, yp+h, zp+l); }
    inline NxPoint center() const;

    void setTopLeft(const NxPoint &p);
    void setBottomRight(const NxPoint &p);
    void setTopRight(const NxPoint &p);
    void setBottomLeft(const NxPoint &p);

    void moveLeft(qreal pos);
    void moveTop(qreal pos);
    void moveRight(qreal pos);
    void moveBottom(qreal pos);
    void moveTopLeft(const NxPoint &p);
    void moveBottomRight(const NxPoint &p);
    void moveTopRight(const NxPoint &p);
    void moveBottomLeft(const NxPoint &p);
    void moveCenter(const NxPoint &p);

    void translate(qreal dx, qreal dy, qreal dz);
    void translate(const NxPoint &p);

    NxRect translated(qreal dx, qreal dy, qreal dz) const;
    NxRect translated(const NxPoint &p) const;

    void moveTo(qreal x, qreal y, qreal z);
    void moveTo(const NxPoint &p);

    void setRect(qreal x, qreal y, qreal z, qreal w, qreal h, qreal l);
    void getRect(qreal *x, qreal *y, qreal *z, qreal *w, qreal *h, qreal *l) const;

    void setCoords(qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2);
    void getCoords(qreal *x1, qreal *y1, qreal *z1, qreal *x2, qreal *y2, qreal *z2) const;

    inline void adjust(qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2);
    inline NxRect adjusted(qreal x1, qreal y1, qreal z1, qreal x2, qreal y2, qreal z2) const;

    NxSize size() const;
    qreal width() const;
    qreal height() const;
    qreal length() const;
    void setWidth(qreal w);
    void setHeight(qreal h);
    void setLength(qreal l);
    void setSize(const NxSize &s);

    NxRect operator|(const NxRect &r) const;
    NxRect operator&(const NxRect &r) const;
    NxRect& operator|=(const NxRect &r);
    NxRect& operator&=(const NxRect &r);

    bool contains(const NxPoint &p) const;
    bool contains(qreal x, qreal y, qreal z) const;
    bool contains(const NxRect &r) const;
    NxRect unite(const NxRect &r) const;  // ### Qt 5: make QT4_SUPPORT
    NxRect united(const NxRect &other) const;
    NxRect intersect(const NxRect &r) const;  // ### Qt 5: make QT4_SUPPORT
    NxRect intersected(const NxRect &other) const;
    bool intersects(const NxRect &r) const;

    friend bool operator==(const NxRect &, const NxRect &);
    friend bool operator!=(const NxRect &, const NxRect &);

private:
    qreal xp;
    qreal yp;
    qreal zp;
    qreal w;
    qreal h;
    qreal l;
};
Q_DECLARE_TYPEINFO(NxRect, Q_MOVABLE_TYPE);

bool operator==(const NxRect &, const NxRect &);
bool operator!=(const NxRect &, const NxRect &);


/*****************************************************************************
  NxRect inline member functions
 *****************************************************************************/

inline NxRect::NxRect(qreal aleft, qreal atop, qreal az, qreal awidth, qreal aheight, qreal alength)
    : xp(aleft), yp(atop), zp(az), w(awidth), h(aheight), l(alength)
{}

inline NxRect::NxRect(qreal aleft, qreal atop, qreal awidth, qreal aheight)
    : xp(aleft), yp(atop), zp(0), w(awidth), h(aheight), l(0)
{}

inline NxRect::NxRect(const NxPoint &atopLeft, const NxSize &asize)
{
    xp = atopLeft.x();
    yp = atopLeft.y();
    zp = atopLeft.z();
    w = asize.width();
    h = asize.height();
    l = asize.length();
}

inline NxRect::NxRect(const NxPoint &atopLeft, const NxPoint &abottomRight)
{
    xp = atopLeft.x();
    yp = atopLeft.y();
    zp = atopLeft.z();
    w = abottomRight.x() - xp;
    h = abottomRight.y() - yp;
    l = abottomRight.z() - zp;
}


inline bool NxRect::isNull() const
{ return w == 0. && h == 0. && l == 0.; }

inline bool NxRect::isEmpty() const
{ return w <= 0. || h <= 0. || l <= 0.; }

inline bool NxRect::isValid() const
{ return w > 0. && h > 0. && l > 0.; }

inline qreal NxRect::x() const
{ return xp; }

inline qreal NxRect::y() const
{ return yp; }

inline qreal NxRect::z() const
{ return zp; }

inline void NxRect::setLeft(qreal pos)    { qreal diff = pos - xp; xp += diff; w -= diff; }
inline void NxRect::setRight(qreal pos)   { w = pos - xp; }
inline void NxRect::setTop(qreal pos)     { qreal diff = pos - yp; yp += diff; h -= diff; }
inline void NxRect::setBottom(qreal pos)  { h = pos - yp; }
inline void NxRect::setzTop(qreal pos)    { l = pos - zp; }
inline void NxRect::setzBottom(qreal pos) { qreal diff = pos - zp; zp += diff; l -= diff; }


inline void NxRect::setTopLeft(const NxPoint &p)     { setLeft(p.x());  setTop(p.y());    setzTop(p.z()); }
inline void NxRect::setTopRight(const NxPoint &p)    { setRight(p.x()); setTop(p.y());    setzTop(p.z()); }
inline void NxRect::setBottomLeft(const NxPoint &p)  { setLeft(p.x());  setBottom(p.y()); setzBottom(p.z()); }
inline void NxRect::setBottomRight(const NxPoint &p) { setRight(p.x()); setBottom(p.y()); setzBottom(p.z()); }

inline NxPoint NxRect::center() const
{ return NxPoint(xp + w/2, yp + h/2, zp + l/2); }

inline void NxRect::moveLeft(qreal pos) { xp = pos; }

inline void NxRect::moveTop(qreal pos) { yp = pos; }

inline void NxRect::moveRight(qreal pos) { xp = pos - w; }

inline void NxRect::moveBottom(qreal pos) { yp = pos - h; }

inline void NxRect::moveTopLeft(const NxPoint &p) { moveLeft(p.x()); moveTop(p.y()); }

inline void NxRect::moveTopRight(const NxPoint &p) { moveRight(p.x()); moveTop(p.y()); }

inline void NxRect::moveBottomLeft(const NxPoint &p) { moveLeft(p.x()); moveBottom(p.y()); }

inline void NxRect::moveBottomRight(const NxPoint &p) { moveRight(p.x()); moveBottom(p.y()); }

inline void NxRect::moveCenter(const NxPoint &p) { xp = p.x() - w/2; yp = p.y() - h/2; }

inline qreal NxRect::width() const
{ return w; }

inline qreal NxRect::height() const
{ return h; }

inline qreal NxRect::length() const
{ return l; }

inline NxSize NxRect::size() const
{ return NxSize(w, h, l); }

inline void NxRect::translate(qreal dx, qreal dy, qreal dz)
{
    xp += dx;
    yp += dy;
    zp += dz;
}

inline void NxRect::translate(const NxPoint &p)
{
    xp += p.x();
    yp += p.y();
    zp += p.z();
}

inline void NxRect::moveTo(qreal ax, qreal ay, qreal az)
{
    xp = ax;
    yp = ay;
    zp = az;
}

inline void NxRect::moveTo(const NxPoint &p)
{
    xp = p.x();
    yp = p.y();
    zp = p.z();
}

inline NxRect NxRect::translated(qreal dx, qreal dy, qreal dz) const
{ return NxRect(xp + dx, yp + dy, zp + dz, w, h, l); }

inline NxRect NxRect::translated(const NxPoint &p) const
{ return NxRect(xp + p.x(), yp + p.y(), zp + p.z(), w, h, l); }

inline void NxRect::getRect(qreal *ax, qreal *ay, qreal *az, qreal *aaw, qreal *aah, qreal *aal) const
{
    *ax = this->xp;
    *ay = this->yp;
    *az = this->zp;
    *aaw = this->w;
    *aah = this->h;
    *aal = this->l;
}

inline void NxRect::setRect(qreal ax, qreal ay, qreal az, qreal aaw, qreal aah, qreal aal)
{
    this->xp = ax;
    this->yp = ay;
    this->zp = az;
    this->w = aaw;
    this->h = aah;
    this->l = aal;
}

inline void NxRect::getCoords(qreal *xp1, qreal *yp1, qreal *zp1, qreal *xp2, qreal *yp2, qreal *zp2) const
{
    *xp1 = xp;
    *yp1 = yp;
    *zp1 = zp;
    *xp2 = xp + w;
    *yp2 = yp + h;
    *zp2 = zp + l;
}

inline void NxRect::setCoords(qreal xp1, qreal yp1, qreal zp1, qreal xp2, qreal yp2, qreal zp2)
{
    xp = xp1;
    yp = yp1;
    zp = zp1;
    w = xp2 - xp1;
    h = yp2 - yp1;
    l = zp2 - zp1;
}

inline void NxRect::adjust(qreal xp1, qreal yp1, qreal zp1, qreal xp2, qreal yp2, qreal zp2)
{ xp += xp1; yp += yp1; zp += zp1; w += xp2 - xp1; h += yp2 - yp1; l += zp2 - zp1; }

inline NxRect NxRect::adjusted(qreal xp1, qreal yp1, qreal zp1, qreal xp2, qreal yp2, qreal zp2) const
{ return NxRect(xp + xp1, yp + yp1, zp + zp1, w + xp2 - xp1, h + yp2 - yp1, l + zp2 - zp1); }

inline void NxRect::setWidth(qreal aw)
{ this->w = aw; }

inline void NxRect::setHeight(qreal ah)
{ this->h = ah; }

inline void NxRect::setLength(qreal al)
{ this->l = al; }


inline void NxRect::setSize(const NxSize &s)
{
    w = s.width();
    h = s.height();
    l = s.length();
}

inline bool NxRect::contains(qreal ax, qreal ay, qreal az) const
{
    return contains(NxPoint(ax, ay, az));
}

inline NxRect& NxRect::operator|=(const NxRect &r)
{
    *this = *this | r;
    return *this;
}

inline NxRect& NxRect::operator&=(const NxRect &r)
{
    *this = *this & r;
    return *this;
}

inline NxRect NxRect::intersect(const NxRect &r) const
{
    return *this & r;
}

inline NxRect NxRect::intersected(const NxRect &r) const
{
    return intersect(r);
}

inline NxRect NxRect::unite(const NxRect &r) const
{
    return *this | r;
}

inline NxRect NxRect::united(const NxRect &r) const
{
    return unite(r);
}

inline bool operator==(const NxRect &r1, const NxRect &r2)
{
    return qFuzzyCompare(r1.xp, r2.xp) && qFuzzyCompare(r1.yp, r2.yp) && qFuzzyCompare(r1.zp, r2.zp)
           && qFuzzyCompare(r1.w, r2.w) && qFuzzyCompare(r1.h, r2.h) && qFuzzyCompare(r1.l, r2.l);
}

inline bool operator!=(const NxRect &r1, const NxRect &r2)
{
    return !qFuzzyCompare(r1.xp, r2.xp) || !qFuzzyCompare(r1.yp, r2.yp) || !qFuzzyCompare(r1.zp, r2.zp)
           || !qFuzzyCompare(r1.w, r2.w) || !qFuzzyCompare(r1.h, r2.h) || !qFuzzyCompare(r1.l, r2.l);
}

#endif // NXRECT_H
