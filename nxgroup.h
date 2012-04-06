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

#ifndef NXGROUP_H
#define NXGROUP_H

#include <QObject>
#include <QTreeWidgetItem>
#include "nxtrigger.h"
#include "nxcurve.h"
#include "nxcursor.h"

class NxGroup : public QObject, public NxObjectDispatchProperty, public QTreeWidgetItem {
    Q_OBJECT
public:
    explicit NxGroup(NxObjectFactoryInterface *parent, QTreeWidget *parentItem, Qt::CheckState state);
    inline void dispatchProperty(const QString & property, const QVariant & value) {
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {

            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                //Browse objects
                QHashIterator<quint16, NxObject*> objectIterator(objects[activityIterator][typeIterator]);
                while (objectIterator.hasNext()) {
                    objectIterator.next();
                    NxObject *object = objectIterator.value();
                    object->dispatchProperty(property, value);
                }
            }
        }
    }
    inline const QVariant getProperty(const QString &) const {
        return id;
    }
    inline quint8 getType() const {
        return ObjectsTypeGroup;
    }
    inline const QString getTypeStr() const {
        return "group";
    }
    inline const NxRect getBoundingRect() const {
        NxRect boundingRect;

        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {

            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {

                //Browse objects
                QHashIterator<quint16, NxObject*> objectIterator(objects[activityIterator][typeIterator]);
                while (objectIterator.hasNext()) {
                    objectIterator.next();
                    NxObject *object = objectIterator.value();
                    boundingRect = boundingRect.united(object->getBoundingRect());
                }
            }
        }
        return boundingRect;
    }
    inline quint16 getCount() const {
        quint16 counter = 0;
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                //Browse objects
                QHashIterator<quint16, NxObject*> objectIterator(objects[activityIterator][typeIterator]);
                while (objectIterator.hasNext()) {
                    objectIterator.next();
                    counter++;
                }
            }
        }
        return counter;
    }

public:
    //activity + type + objectID = object !
    QHash< quint16, NxObject* > objects[ObjectsActivityLenght][ObjectsTypeLength];

protected:
    QString id;
public slots:
    inline void setId(const QString & _id) {
        id = _id;
        setText(0, tr("Group") + " " + id);
    }
    inline const QString & getId() const {
        return id;
    }
};


#endif // NXGROUP_H
