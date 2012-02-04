#ifndef IANNIX_SPEC_H
#define IANNIX_SPEC_H

#include <QObject>
#include "nxpoint.h"
#include "nxrect.h"
#include "nxline.h"
#include "nxpolygon.h"

class NxObjectDispatchProperty {
public:
    virtual quint8 getType() const = 0;
    virtual const QString getTypeStr() const = 0;
    virtual void dispatchProperty(const QString & property, const QVariant & value) = 0;
    virtual const QVariant getProperty(const QString & property) const = 0;
};


#endif // IANNIX_SPEC_H
