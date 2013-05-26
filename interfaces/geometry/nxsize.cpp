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

#include "nxsize.h"

void NxSize::transpose() {
    qreal tmp = wd;
    wd = ht;
    ht = tmp;
}

void NxSize::scale(const NxSize &s, Qt::AspectRatioMode mode) {
    if (mode == Qt::IgnoreAspectRatio || qIsNull(wd) || qIsNull(ht) || qIsNull(lg)) {
        wd = s.wd;
        ht = s.ht;
        lg = s.lg;
    } else {
        bool useHeight;
        qreal rw = s.ht * wd / ht;

        if (mode == Qt::KeepAspectRatio) {
            useHeight = (rw <= s.wd);
        } else { // mode == Qt::KeepAspectRatioByExpanding
            useHeight = (rw >= s.wd);
        }

        if (useHeight) {
            wd = rw;
            ht = s.ht;
            lg = s.lg;
        } else {
            ht = s.wd * ht / wd;
            wd = s.wd;
            lg = s.lg;
        }
    }
}

