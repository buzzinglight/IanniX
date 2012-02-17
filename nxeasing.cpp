#include "nxeasing.h"

NxEasing::NxEasing(QObject *parent) :
    QObject(parent) {
}

QPixmap NxEasing::getPixmap() const {
    QPixmap pixmap(128, 128);
    pixmap.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pixmap);
    painter.setPen(QPen(Qt::black, 2));
    QPointF pt1(0, pixmap.height()), pt2;
    for(quint16 x = 0 ; x < pixmap.width() ; x++) {
        pt2 = QPointF(x, pixmap.height() * (1-valueForProgress((qreal)x / (qreal)pixmap.width())));
        painter.drawLine(pt1, pt2);
        pt1 = pt2;
    }
    painter.end();
    return pixmap;
}
