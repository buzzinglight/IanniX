/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "nxgroup.h"

NxGroup::NxGroup(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem) :
    QObject(parent), QTreeWidgetItem(ccParentItem) {
    setText(0, tr("GROUP"));
    setSolo(0);
    setMute(0);
    scale = scaleDest = 1;
}


void NxGroup::setMute(quint16 _val) {
    objectMute = _val;
    if(objectMute)  setIcon(1, NxObject::widgetIconActiveOff);
    else            setIcon(1, NxObject::widgetIconActiveOn);
}
void NxGroup::setSolo(quint16 _val) {
    objectSolo = _val;
    if(objectSolo)  setIcon(2, NxObject::widgetIconSoloOn);
    else            setIcon(2, NxObject::widgetIconSoloOff);
}

void NxGroup::widgetClick(int col) {
    if((col == 1) && (!id.isEmpty()))       Application::current->execute(QString("%1 %2 %3").arg(COMMAND_MUTE).arg(id).arg(1-objectMute), ExecuteSourceGui);
    else if((col == 2) && (!id.isEmpty()))  Application::current->execute(QString("%1 %2 %3").arg(COMMAND_SOLO).arg(id).arg(1-objectSolo), ExecuteSourceGui);
}


const QString NxGroup::serialize() const {
    QString retour;

    foreach(const QString &command, propertiesToSerialize.value(NxObjectDispatchProperty::source))
        retour += "\trun(\"" + QString("%1 %2 %3").arg(command).arg(getId()).arg(getPropertyFromGroup(qPrintable(command)).toString()) + "\");\n";
    if(!retour.isEmpty())
        retour += "\n";

    //Browse active/inactive objects
    for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
        //Browse all types of objects
        for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
            //Browse objects
            foreach(NxObject *object, objects[activityIterator][typeIterator]) {
                if(((typeIterator == ObjectsTypeCursor) && (((NxCursor*)object)->getCurve() == 0)) || (typeIterator == ObjectsTypeCurve) || (typeIterator == ObjectsTypeTrigger))
                    retour += object->serialize();
            }
        }
    }
    if(!retour.isEmpty())
        retour += "\n";
    return retour;
}
