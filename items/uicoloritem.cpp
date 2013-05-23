#include "uicoloritem.h"

UiColorItems::UiColorItems(UiSyncItem *_parent) :
    UiSyncItem(_parent) {
    parentItem = _parent;
}



void UiColorItems::configure(const QString &, UiTreeView *tree) {
    tree->getTree()->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    tree->configureColumns(UiTreeViewOptions(0, "Color", "color", ""           , QHeaderView::Fixed,   50));
    tree->configureColumns(UiTreeViewOptions(1, "Name" , "edit" , "margin:0px;", QHeaderView::Stretch, 210));
    tree->getTree()->addTopLevelItem(this);
    setFlags(Qt::ItemIsEnabled);
    setData(0, Qt::DisplayRole, "");
    setData(1, Qt::DisplayRole, "");
}
UiColorItem* UiColorItems::generateItem(UiSyncItem *otherItem, bool doInsert, bool fromGui) {
    if(otherItem->parentItem)   return generateItem(((UiColorItem*)otherItem)->name, ((UiColorItem*)otherItem)->color, doInsert, fromGui);
    else                        return 0;
}
UiColorItem* UiColorItems::generateItem(const QString &name, const QColor &color, bool doInsert, bool fromGui) {
    UiColorItem *item = new UiColorItem(this, this);
    item->name  = name;
    item->color = color;
    quint16 iterations = 1;
    while((item->name.isEmpty()) || ((doInsert) && (contains(item->name))))
        item->name = name + QString("_%1").arg(iterations++);
    if(doInsert)
        insert(item->name, item->color);
    if(fromGui)
        Application::current->execute(QString("%1 %2 %3 %4 %5 %6").arg(COMMAND_GLOBAL_COLOR).arg(item->name).arg(item->color.red()).arg(item->color.green()).arg(item->color.blue()).arg(item->color.alpha()), ExecuteSourceInformative);
    return item;
}
bool UiColorItems::update() {
    while(childCount()) delete child(0);
    QMapIterator<QString, QColor> iterator(*this);
    while (iterator.hasNext()) {
        iterator.next();
        generateItem(iterator.key(), iterator.value(), false, false);
    }
    dataChanged();
    treeWidget()->expandItem(this);
    return true;
}

void UiColorItems::dataChanged() {
    treeWidget()->sortItems(1, Qt::AscendingOrder);
}

UiSyncItem* UiColorItems::askForNewChild(UiSyncItem *i, bool) {
    UiColorItem *item = 0;
    if((i) && (i->parentItem))  item = generateItem(i);
    else                        item = generateItem("new_color", Qt::white);
    dataChanged();
    highlight(item);
    changes << item->name;
    return item;
}
bool UiColorItems::askForDeletion(UiSyncItem *i, bool) {
    //qDebug("[DELETE COLOR]");
    UiColorItem *item = (UiColorItem*)i;
    remove(item->name);
    delete item;
    dataChanged();
    return true;
}
bool UiColorItems::askForPaste(UiSyncItem*, const QList<UiSyncItem*> &listItems) {
    foreach(UiSyncItem *listItem, listItems)
        changes << generateItem(listItem)->name;
    dataChanged();
    return false;
}
const QString UiColorItems::renameKey(const QString &oldKey, const QString &newKey) {
    if(oldKey == newKey)
        return newKey;
    QString correctNewKey = newKey;
    correctNewKey = correctNewKey.replace(" ", "_");
    quint16 iterations = 1;
    while((correctNewKey.isEmpty()) || (contains(correctNewKey)))
        correctNewKey = newKey + QString("_%1").arg(iterations++);
    setValue(correctNewKey, value(oldKey));
    remove(oldKey);
    changes << correctNewKey;
    dataChanged();
    return correctNewKey;
}
const QVariant UiColorItems::setValue(const QString &key, const QVariant &valeur) {
    QColor color = valeur.value<QColor>();
    (*this)[key] = color;
    changes << key;
    Application::current->execute(QString("%1 %2 %3 %4 %5 %6").arg(COMMAND_GLOBAL_COLOR).arg(key).arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()), ExecuteSourceInformative);
    dataChanged();
    return valeur;
}





UiColorItem::UiColorItem(UiSyncList *_baseList, UiSyncItem *_parent) :
    UiSyncItem(_parent) {
    baseList = _baseList;
    //qDebug("[CREATION COLOR]");
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
}

QVariant UiColorItem::data(int column, int role) const {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if(column == 0) return color;
        if(column == 1) return name;
    }
    return QTreeWidgetItem::data(column, role);
}
void UiColorItem::setData(int column, int role, const QVariant &value) {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if(column == 0) color = baseList->setValue(name, value).value<QColor>();
        if(column == 1) name  = baseList->renameKey(name, value);
        dataChanged();
        return;
    }
    return QTreeWidgetItem::setData(column, role, value);
}
