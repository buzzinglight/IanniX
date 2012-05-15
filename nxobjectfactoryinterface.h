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

#ifndef NXOBJECTFACTORYINTERFACE_H
#define NXOBJECTFACTORYINTERFACE_H

#include <QObject>
#include <QVariant>
#include <QPixmap>
#ifdef KINECT_INSTALLED
#include "extkinectmanager.h"
#endif
#include "iannix_spec.h"

class NxObjectFactoryInterface : public QObject {
    Q_OBJECT

public:
    explicit NxObjectFactoryInterface(QObject *parent):QObject(parent) {}

//KINECT
#ifdef KINECT_INSTALLED
public:
    ExtKinectManager *kinect;
#endif


public:
    virtual void setObjectActivity(void *_object, quint8 activeOld) = 0;
    virtual void setObjectGroupId(void *_object, const QString & groupIdOld) = 0;
    virtual QImage takeScreenshot() = 0;

public slots:
    virtual void askNxObject() = 0;
    virtual void sendMessage(void *_object = 0, void *_trigger = 0, void *_cursor = 0, void *_collisionCurve = 0, const NxPoint & collisionPoint = NxPoint(), const NxPoint & collisionValue = NxPoint(), const QString & status = QString()) = 0;
    virtual const QVariant execute(const QString & command, bool createNewObjectIfExists = false, bool dump = false) = 0;
    virtual QString onOscReceive(const QString & protocol, const QString & host, const QString & port, const QString & destination, const QStringList & arguments) = 0;
    virtual QString onDraw() = 0;
    virtual void logOscSend(const QString & message) = 0;
    virtual void logOscReceive(const QString & message) = 0;
    virtual void pushSnapshot() = 0;
    virtual qreal getTimeLocal() const = 0;
    virtual void readyToStart() = 0;
    virtual void setMidiOutNewDevice(const QString &midi) = 0;
};

#endif // NXOBJECTFACTORYINTERFACE_H
