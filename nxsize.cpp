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

