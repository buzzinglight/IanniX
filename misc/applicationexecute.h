#ifndef APPLICATIONEXECUTE_H
#define APPLICATIONEXECUTE_H

#include <QVariant>
#include "iannix_spec.h"

class ApplicationExecute {
public:
    static ApplicationExecute *current;
public:
    virtual const QVariant execute(const QString & command, ExecuteSource source, bool createNewObjectIfExists = false, bool needOutput = false) = 0;
};

#endif // APPLICATIONEXECUTE_H
