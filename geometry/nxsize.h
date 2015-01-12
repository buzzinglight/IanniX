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

#ifndef NXSIZE_H
#define NXSIZE_H

#include <QVariant>

class NxSize {
public:
    NxSize();
    NxSize(qreal w, qreal h);
    NxSize(qreal w, qreal h, qreal l);

    bool isNull() const;
    bool isEmpty() const;
    bool isValid() const;

    qreal width() const;
    qreal height() const;
    qreal length() const;
    void setWidth(qreal w);
    void setHeight(qreal h);
    void setLength(qreal l);
    void transpose();

    void scale(qreal w, qreal h, qreal l, Qt::AspectRatioMode mode);
    void scale(const NxSize &s, Qt::AspectRatioMode mode);

    qreal &rwidth();
    qreal &rheight();
    qreal &rlength();

    NxSize &operator+=(const NxSize &);
    NxSize &operator-=(const NxSize &);
    NxSize &operator*=(qreal c);
    NxSize &operator/=(qreal c);

    friend inline bool operator==(const NxSize &, const NxSize &);
    friend inline bool operator!=(const NxSize &, const NxSize &);
    friend inline const NxSize operator+(const NxSize &, const NxSize &);
    friend inline const NxSize operator-(const NxSize &, const NxSize &);
    friend inline const NxSize operator*(const NxSize &, qreal);
    friend inline const NxSize operator*(qreal, const NxSize &);
    friend inline const NxSize operator/(const NxSize &, qreal);

private:
    qreal wd;
    qreal ht;
    qreal lg;
};
Q_DECLARE_TYPEINFO(NxSize, Q_MOVABLE_TYPE);


/*****************************************************************************
  NxSize inline functions
 *****************************************************************************/

inline NxSize::NxSize()
{ wd = ht = lg = -1.; }

inline NxSize::NxSize(qreal w, qreal h, qreal l)
{ wd = w; ht = h; lg = l; }

inline NxSize::NxSize(qreal w, qreal h)
{ wd = w; ht = h; lg = 0; }

inline bool NxSize::isNull() const
{ return qIsNull(wd) && qIsNull(ht) && qIsNull(lg); }

inline bool NxSize::isEmpty() const
{ return wd <= 0. || ht <= 0.; }

inline bool NxSize::isValid() const
{ return wd >= 0. && ht >= 0.; }

inline qreal NxSize::width() const
{ return wd; }

inline qreal NxSize::height() const
{ return ht; }

inline qreal NxSize::length() const
{ return lg; }

inline void NxSize::setWidth(qreal w)
{ wd = w; }

inline void NxSize::setHeight(qreal h)
{ ht = h; }

inline void NxSize::setLength(qreal l)
{ lg = l; }

inline void NxSize::scale(qreal w, qreal h, qreal l, Qt::AspectRatioMode mode)
{ scale(NxSize(w, h, l), mode); }

inline qreal &NxSize::rwidth()
{ return wd; }

inline qreal &NxSize::rheight()
{ return ht; }

inline qreal &NxSize::rlength()
{ return lg; }

inline NxSize &NxSize::operator+=(const NxSize &s)
{ wd += s.wd; ht += s.ht; lg += s.lg; return *this; }

inline NxSize &NxSize::operator-=(const NxSize &s)
{ wd -= s.wd; ht -= s.ht; lg -= s.lg; return *this; }

inline NxSize &NxSize::operator*=(qreal c)
{ wd *= c; ht *= c; lg *= c; return *this; }

inline bool operator==(const NxSize &s1, const NxSize &s2)
{ return qFuzzyCompare(s1.wd, s2.wd) && qFuzzyCompare(s1.ht, s2.ht) && qFuzzyCompare(s1.lg, s2.lg); }

inline bool operator!=(const NxSize &s1, const NxSize &s2)
{ return !qFuzzyCompare(s1.wd, s2.wd) || !qFuzzyCompare(s1.ht, s2.ht) || !qFuzzyCompare(s1.lg, s2.lg); }

inline const NxSize operator+(const NxSize & s1, const NxSize & s2)
{ return NxSize(s1.wd+s2.wd, s1.ht+s2.ht, s1.lg+s2.lg); }

inline const NxSize operator-(const NxSize &s1, const NxSize &s2)
{ return NxSize(s1.wd-s2.wd, s1.ht-s2.ht, s1.lg-s2.lg); }

inline const NxSize operator*(const NxSize &s, qreal c)
{ return NxSize(s.wd*c, s.ht*c, s.lg*c); }

inline const NxSize operator*(qreal c, const NxSize &s)
{ return NxSize(s.wd*c, s.ht*c, s.lg*c); }

inline NxSize &NxSize::operator/=(qreal c) {
    Q_ASSERT(!qFuzzyIsNull(c));
    wd = wd/c; ht = ht/c; lg = lg/c;
    return *this;
}

inline const NxSize operator/(const NxSize &s, qreal c) {
    Q_ASSERT(!qFuzzyIsNull(c));
    return NxSize(s.wd/c, s.ht/c, s.lg/c);
}

#endif // NXSIZE_H
