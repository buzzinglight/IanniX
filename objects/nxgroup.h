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
#include "nxcursor.h"
#include "nxcurve.h"

class NxGroup : public QObject, public NxObjectDispatchProperty, public QTreeWidgetItem {
    Q_OBJECT

    Q_PROPERTY(quint16 setmute READ getMute WRITE setMute)
    Q_PROPERTY(quint16 setsolo READ getSolo WRITE setSolo)

public:
    explicit NxGroup(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem);
    inline void dispatchProperty(const char *_property, const QVariant & value) {
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++)
            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++)
                //Browse objects
                foreach(NxObject *object, objects[activityIterator][typeIterator])
                    object->dispatchProperty(_property, value);
    }
    inline const QVariant getProperty(const char *_property) const {
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++)
            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++)
                //Browse objects
                foreach(NxObject *object, objects[activityIterator][typeIterator])
                    return object->getProperty(_property);
        return QVariant();
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
                foreach(const NxObject *object, objects[activityIterator][typeIterator]) {
                    boundingRect = boundingRect.united(object->getBoundingRect());
                }
            }
        }
        return boundingRect;
    }
    inline quint16 getCount(qint8 objectType = -1) const {
        quint16 counter = 0;
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++)
            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++)
                if((objectType < 0) || (typeIterator == objectType))
                    counter += objects[activityIterator][typeIterator].count();
        return counter;
    }

public:
    //activity + type + objectID = object !
    QHash< quint16, NxObject* > objects[ObjectsActivityLenght][ObjectsTypeLength];
    NxPoint rotation, rotationDest, translation, translationDest;
    qreal   scale, scaleDest;

protected:
    QString id;
public slots:
    inline void setId(const QString & _id) {
        id = _id;
        if(_id.isEmpty()) {
            if(!isHidden())
                setHidden(true);
        }
        else {
            if(isHidden())
                setHidden(false);
            setText(3, id);
            setText(4, id);
        }
    }
    inline const QString & getId() const {
        return id;
    }


private:
    quint16 objectSolo, objectMute;
public:
    bool isSolo()     const { return objectSolo >  0; }
    bool isNotMuted() const { return objectMute == 0; }
    bool isMuted()    const { return objectMute > 0; }
    quint16 getSolo()  const { return objectSolo; }
    quint16 getMute()  const { return objectMute; }
    void setSolo(quint16 _val);
    void setMute(quint16 _val);
    void widgetClick(int col);

public:
    const QString serialize() const;
    inline void dispatchPropertyToGroup(const char *_property, const QVariant & value) {
        propertyChanged(_property);
        setProperty(_property, value);
    }
    inline const QVariant getPropertyFromGroup(const char *_property) const {
        return property(_property);
    }
};


#endif // NXGROUP_H
