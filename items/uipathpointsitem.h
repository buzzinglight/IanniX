/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

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

#ifndef UIPATHPOINTSITEM_H
#define UIPATHPOINTSITEM_H

#include "uitreeview.h"
#include "misc/options.h"
#include "iannix_cmd.h"

class UiPathPointsItem : public UiSyncItem {
public:
    explicit UiPathPointsItem(UiSyncList *_baseList, UiSyncItem *_parent = 0);

public:
    quint16 index;
    NxCurvePoint point;
private:
    UiSyncList *baseList;
protected:
    QVariant data(int column, int role) const;
    void setData(int column, int role, const QVariant &value);

protected:
    void dataChanged() { emitDataChanged(); }
};



class UiPathPointsItems : public QList<NxCurvePoint>, public UiSyncItem, public UiSyncList {
public:
    explicit UiPathPointsItems(UiSyncItem *_parent = 0);
private:
    UiPathPointsItem* generateItem(UiSyncItem *otherItem, bool doInsert = true);
    UiPathPointsItem* generateItem(quint16 index, const NxCurvePoint &point, bool doInsert = true);

public:
    void configure(const QString &name, UiTreeView *, bool *_glListRecreate);
    void update();
    bool *glListRecreate;
protected:
    UiSyncItem* askForNewChild(UiSyncItem *i, bool isRoot);
    bool askForDeletion(UiSyncItem *i, bool);
    bool askForPaste(UiSyncItem *i, const QList<UiSyncItem *> &list);
    bool askForMove(UiSyncItem *i1, UiSyncItem *i2);
protected:
    const NxCurvePoint setValue(quint16 key, const NxCurvePoint &valeur);
protected:
    void dataChanged();
};

#endif // UIPATHPOINTSITEM_H
