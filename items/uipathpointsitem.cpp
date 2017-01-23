/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (https://www.buzzinglight.com)

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

#include "uipathpointsitem.h"

UiPathPointsItems::UiPathPointsItems(UiSyncItem *_parent) :
    UiSyncItem(_parent) {
    parentItem    = _parent;
}


UiPathPointsItem* UiPathPointsItems::generateItem(UiSyncItem *otherItem, bool doInsert) {
    if(otherItem->parentItem)   return generateItem(((UiPathPointsItem*)otherItem)->index+1, ((UiPathPointsItem*)otherItem)->point, doInsert);
    else                        return 0;
}
UiPathPointsItem* UiPathPointsItems::generateItem(quint16 index, const NxCurvePoint &point, bool doInsert) {
    UiPathPointsItem *item = new UiPathPointsItem(this, this);
    item->index = index;
    item->point = point;
    if(doInsert)
        insert(index, point);
    return item;
}


void UiPathPointsItems::update() {
    quint16 currentIndex = 0;
    if((treeWidget()->currentItem()) && (((UiSyncItem*)treeWidget()->currentItem())->parentItem))
        currentIndex = ((UiPathPointsItem*)treeWidget()->currentItem())->index;

    //Existing
    QList<UiPathPointsItem*> childrenItems;
    for(quint16 i = 0 ; i < childCount() ; i++)
        childrenItems << (UiPathPointsItem*)child(i);

    for(quint16 i = 0 ; i < count() ; i++) {
        UiPathPointsItem *item = 0;
        for(quint16 j = 0 ; j < childrenItems.count() ; j++) {
            if(at(i) == childrenItems.at(j)->point) {
                item = childrenItems.at(j);
                childrenItems.removeAt(j);
                break;
            }
        }
        if(item)    item->index = i;
        else        generateItem(i, at(i), false);
    }

    //Remove exitings
    foreach(UiPathPointsItem *childrenItem, childrenItems)
        delete childrenItem;

    treeWidget()->sortItems(0, Qt::AscendingOrder);
    treeWidget()->expandItem(this);
    dataChanged();
    for(quint16 i = 0 ; i < childCount() ; i++) {
        if(((UiPathPointsItem*)child(i))->index == currentIndex) {
            treeWidget()->setCurrentItem(child(i));
            treeWidget()->scrollToItem(child(i));
            break;
        }
    }
}

void UiPathPointsItems::configure(const QString &name, UiTreeView *tree, bool *_glListRecreate) {
    glListRecreate = _glListRecreate;
    tree->getTree()->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    tree->getTree()->setHeaderHidden(false);
    tree->configureColumns(UiTreeViewOptions( 0, "Index" , "edit"      , "margin:0px;", QHeaderView::Fixed,         1));
    tree->configureColumns(UiTreeViewOptions( 1, "X"     , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions( 2, "Y"     , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions( 3, "Z"     , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions( 4, "Smooth", "checkbox",   "margin:0px;", QHeaderView::Interactive,  30));
    tree->configureColumns(UiTreeViewOptions( 5, "c1 X"  , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions( 6, "c1 Y"  , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions( 7, "c1 Z"  , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions( 8, "c2 X"  , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions( 9, "c2 Y"  , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->configureColumns(UiTreeViewOptions(10, "c2 Z"  , "doublespin", "margin:0px;", QHeaderView::Interactive,  60));
    tree->getTree()->addTopLevelItem(this);

    setFlags(Qt::ItemIsEnabled);
    setData(0, Qt::DisplayRole, name);
    setData(1, Qt::DisplayRole, "");
    setData(2, Qt::DisplayRole, "");
}
void UiPathPointsItems::dataChanged() {
    for(quint16 i = 0 ; i < count() ; i++)
        ((UiPathPointsItem*)child(i))->index = i;
    *glListRecreate = true;
}

UiSyncItem* UiPathPointsItems::askForNewChild(UiSyncItem *i, bool) {
    UiPathPointsItem *item = 0;
    if((i) && (i->parentItem))   item = generateItem(i);
    else                         item = generateItem(0, NxCurvePoint());
    update();
    highlight(item);
    return item;
}
bool UiPathPointsItems::askForDeletion(UiSyncItem *i, bool) {
    UiPathPointsItem *item = (UiPathPointsItem*)i;
    //qDebug("[DELETE POINT] %d", item->index);
    removeAt(item->index);
    update();
    return true;
}
bool UiPathPointsItems::askForPaste(UiSyncItem*, const QList<UiSyncItem*> &listItems) {
    foreach(UiSyncItem *listItem, listItems)
        generateItem(listItem);
    update();
    return false;
}
bool UiPathPointsItems::askForMove(UiSyncItem *i1, UiSyncItem *i2) {
    //if(destination->parentItem)
    quint16 indexSource      = ((UiPathPointsItem*)i1)->index;
    quint16 indexDestination = 0;
    if(i2->parentItem)  indexDestination = ((UiPathPointsItem*)i2)->index;
    else                indexDestination = 0;
    if(indexSource == indexDestination)
        return false;
    move(indexSource, indexDestination);
    update();
    return true;
}

const NxCurvePoint UiPathPointsItems::setValue(quint16 key, const NxCurvePoint &valeur) {
    (*this)[key] = valeur;
    dataChanged();
    return valeur;
}





UiPathPointsItem::UiPathPointsItem(UiSyncList *_baseList, UiSyncItem *_parent) :
    UiSyncItem(_parent) {
    baseList = _baseList;
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
    //qDebug("[CREATION POINT]");
}

QVariant UiPathPointsItem::data(int column, int role) const {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if(column ==  0) return index;
        if(column ==  1) return QString::number(point.x(), 'f', 2);
        if(column ==  2) return QString::number(point.y(), 'f', 2);
        if(column ==  3) return QString::number(point.z(), 'f', 2);
        if(column ==  4) return point.smooth;
        if(column ==  5) return QString::number(point.c1.x(), 'f', 2);
        if(column ==  6) return QString::number(point.c1.y(), 'f', 2);
        if(column ==  7) return QString::number(point.c1.z(), 'f', 2);
        if(column ==  8) return QString::number(point.c2.x(), 'f', 2);
        if(column ==  9) return QString::number(point.c2.y(), 'f', 2);
        if(column == 10) return QString::number(point.c2.z(), 'f', 2);
    }
    return QTreeWidgetItem::data(column, role);
}
void UiPathPointsItem::setData(int column, int role, const QVariant &value) {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if(column ==  1) point.setX(value.toDouble());
        if(column ==  2) point.setY(value.toDouble());
        if(column ==  3) point.setZ(value.toDouble());
        if(column ==  4) point.smooth = value.toBool();
        if(column ==  5) point.c1.setX(value.toDouble());
        if(column ==  6) point.c1.setY(value.toDouble());
        if(column ==  7) point.c1.setZ(value.toDouble());
        if(column ==  8) point.c2.setX(value.toDouble());
        if(column ==  9) point.c2.setY(value.toDouble());
        if(column == 10) point.c2.setZ(value.toDouble());
        baseList->setValue(index, point);
        dataChanged();
        return;
    }
    return QTreeWidgetItem::setData(column, role, value);
}
