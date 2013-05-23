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

#ifndef IANNIX_SPEC_H
#define IANNIX_SPEC_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include "geometry/nxpoint.h"
#include "geometry/nxrect.h"
#include "geometry/nxline.h"
#include "geometry/nxpolygon.h"

enum ExecuteSource { ExecuteSourceSystem, ExecuteSourceGui, ExecuteSourceScript, ExecuteSourceNetwork, ExecuteSourceInformative, ExecuteSourceCopyPaste };

class NxObjectDispatchProperty {
protected:
    QMap<ExecuteSource, QStringList> propertiesToSerialize;
public:
    static ExecuteSource source;

public:
    void propertyChanged(const char *_property);

public:
    virtual quint8         getType() const    { return 0;         }
    virtual const QString  getTypeStr() const { return QString(); }
    virtual void           dispatchProperty(const char *_property, const QVariant & value) = 0;
    virtual const QVariant getProperty(const char *_property) const = 0;
};


#endif // IANNIX_SPEC_H
