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

#ifndef UICOLORITEM_H
#define UICOLORITEM_H

#include "misc/applicationexecute.h"
#include "uitreeview.h"
#include "misc/options.h"
#include "iannix_cmd.h"

class UiColorItem : public UiSyncItem {
public:
    explicit UiColorItem(UiSyncList *_baseList, UiSyncItem *_parent = 0);

public:
    QString name;
    QColor color;
private:
    UiSyncList *baseList;
protected:
    QVariant data(int column, int role) const;
    void setData(int column, int role, const QVariant &value);

protected:
    void dataChanged() { emitDataChanged(); }
};



class UiColorItems : public QMap<QString, QColor>, public UiSyncItem, public UiSyncList {
public:
    explicit UiColorItems(UiSyncItem *_parent = 0);
private:
    UiColorItem* generateItem(UiSyncItem *otherItem, bool doInsert = true, bool fromGui = true);
    UiColorItem* generateItem(const QString &name, const QColor &color, bool insert = true, bool fromGui = true);

public:
    QStringList changes;
    void configure(const QString &, UiTreeView *);
    bool update();
protected:
    UiSyncItem* askForNewChild(UiSyncItem *i, bool isRoot);
    bool askForDeletion(UiSyncItem *i, bool);
    bool askForPaste(UiSyncItem *i, const QList<UiSyncItem *> &list);
protected:
    const QVariant setValue(const QString &key, const QVariant &valeur);
    const QString renameKey(const QString &oldKey, const QString &newKey);
protected:
    void dataChanged();
};

#endif // UICOLORITEM_H
