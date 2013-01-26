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

#include "nxeasing.h"

QPixmap NxEasing::getPixmap() const {
    QPixmap pixmap(128, 128);
    pixmap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pixmap);
    painter.setPen(QPen(Qt::black, 2));
    QPointF pt1(0, pixmap.height()), pt2;
    for(quint16 x = 0 ; x < pixmap.width() ; x++) {
        pt2 = QPointF(x, pixmap.height() * (1-getValue((qreal)x / (qreal)pixmap.width())));
        painter.drawLine(pt1, pt2);
        pt1 = pt2;
    }
    painter.end();
    return pixmap;
}
