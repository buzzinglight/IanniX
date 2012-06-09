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

#ifndef NXEASING_H
#define NXEASING_H

#include <QEasingCurve>
#include <QPixmap>
#include <QPainter>

class NxEasing {
private:
    QEasingCurve easing;

public:
    inline void setType(quint16 type)           { easing.setType((QEasingCurve::Type)type); }
    inline quint16 getType() const              { return easing.type(); }
    inline qreal getValue(qreal progress) const { return qMin(1., qMax(0., easing.valueForProgress(progress))); }

public:
    QPixmap getPixmap() const;

};

#endif // NXEASING_H
