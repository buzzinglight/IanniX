#ifndef NXEASING_H
#define NXEASING_H

#include <QObject>
#include <QEasingCurve>
#include <QPixmap>
#include <QPainter>

class NxEasing : public QObject {
    Q_OBJECT
public:
    explicit NxEasing(QObject *parent = 0);

private:
    QEasingCurve easing;

public:
    inline void setType(quint16 type)   { easing.setType((QEasingCurve::Type)type); }
    inline quint16 getType() const      { return easing.type(); }
    inline qreal valueForProgress(qreal progress) const { return easing.valueForProgress(progress); }

public:
    QPixmap getPixmap() const;
    
signals:
    
public slots:
    
};

#endif // NXEASING_H
