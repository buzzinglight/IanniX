#ifndef NXOBJECTFACTORYINTERFACE_H
#define NXOBJECTFACTORYINTERFACE_H

#include <QObject>
#include <QVariant>
#include <QRect>

class NxObjectFactoryInterface : public QObject {
    Q_OBJECT;

public:
    explicit NxObjectFactoryInterface(QObject *parent):QObject(parent) {}

public:
    virtual void setObjectActivity(void *_object, quint8 activeOld) = 0;
    virtual void setObjectLocal(void *_object, QRect localOld) = 0;
    virtual void setObjectGroupId(void *_object, const QString & groupIdOld) = 0;

public slots:
    virtual void askNxObject() = 0;
    virtual void sendMessage(void *_object = 0, void *_trigger = 0, void *_cursor = 0, void *_collisionCurve = 0, const QPointF & collisionPoint = QPointF(), const QPointF & collisionValue = QPointF(), const QString & status = QString()) = 0;
    virtual const QVariant execute(const QString & command, bool createNewObjectIfExists = false) = 0;
    virtual void onOscReceive(const QString & message) = 0;
    virtual void onDraw() = 0;
    virtual void logOscSend(const QString & message) = 0;
    virtual void logOscReceive(const QString & message) = 0;
    virtual void pushSnapshot() = 0;
};

#endif // NXOBJECTFACTORYINTERFACE_H
