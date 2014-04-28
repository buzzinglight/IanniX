/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

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

#ifndef NXEASING_H
#define NXEASING_H

#include <QEasingCurve>
#include <QPixmap>
#include <QPainter>

class NxEasing {
private:
    QEasingCurve easing;

public:
    const QPixmap getPixmap() const;

public:
    inline void setType(quint16 type)           { easing.setType((QEasingCurve::Type)type); }
    inline quint16 getType() const              { return easing.type(); }
    inline qreal getValue(qreal progress) const { return qBound(0., easing.valueForProgress(progress), 1.); }
};

#endif // NXEASING_H
