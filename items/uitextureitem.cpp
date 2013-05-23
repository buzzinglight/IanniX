#include "uitextureitem.h"

UiTextureItems::UiTextureItems(UiSyncItem *_parent) :
    UiSyncItem(_parent) {
    parentItem = _parent;
}

void UiTextureItems::configure(const QString &, UiTreeView *tree) {
    tree->getTree()->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    tree->getTree()->setHeaderHidden(false);
    tree->configureColumns(UiTreeViewOptions(        2, "X",        "doublespin", "margin:0px" , QHeaderView::Interactive, 47));
    tree->configureColumns(UiTreeViewOptions(        3, "Y",        "doublespin", "margin:0px" , QHeaderView::Interactive, 47));
    tree->configureColumns(UiTreeViewOptions(        4, "Width",    "doublespin", "margin:0px" , QHeaderView::Interactive, 47));
    tree->configureColumns(UiTreeViewOptions(        5, "Height",   "doublespin", "margin:0px" , QHeaderView::Interactive, 47));
    tree->configureColumns(UiTreeViewOptions(        0, "Name",     "edit"      , "margin:0px;", QHeaderView::Interactive, 85));
    UiTreeViewOptions optionFile = UiTreeViewOptions(1, "Filename", "file"      , ""           , QHeaderView::Interactive, 55);
    optionFile.dialogFile = new QFileDialog(0);
    optionFile.dialogFile->setDirectory(".");
    optionFile.dialogFile->setFileMode(QFileDialog::ExistingFile);
    optionFile.dialogFile->setNameFilters(QStringList() << "Image files (*.png *.jpg *.jpeg)");
    tree->configureColumns(optionFile);

    tree->getTree()->addTopLevelItem(this);
    setFlags(Qt::ItemIsEnabled);
    setData(0, Qt::DisplayRole, "");
    setData(1, Qt::DisplayRole, "");
}
UiTextureItem* UiTextureItems::generateItem(UiSyncItem *otherItem, bool doInsert, bool fromGui) {
    if(otherItem->parentItem)   return generateItem(((UiTextureItem*)otherItem)->name, ((UiTextureItem*)otherItem)->texture, doInsert, fromGui);
    else                        return 0;
}
UiTextureItem* UiTextureItems::generateItem(const QString &name, UiRenderTexture *texture, bool doInsert, bool fromGui) {
    UiTextureItem *item = new UiTextureItem(this, this);
    item->name    = name;
    item->texture = texture;
    quint16 iterations = 1;
    while((item->name.isEmpty()) || ((doInsert) && (contains(item->name))))
        item->name = name + QString("_%1").arg(iterations++);
    texture->name = item->name;
    if(doInsert)
        insert(item->name, item->texture);
    if(fromGui)
        Application::current->execute(QString("%1 %2 %3  %4 %5 %6 %7").arg(COMMAND_TEXTURE).arg(item->name).arg(item->texture->mapping.topLeft().x()).arg(item->texture->mapping.topLeft().y()).arg(item->texture->mapping.bottomRight().x()).arg(item->texture->mapping.bottomRight().y()).arg(item->texture->filename.fileName()), ExecuteSourceInformative);
    return item;
}
void UiTextureItems::update() {
    while(childCount()) delete child(0);
    QMapIterator<QString, UiRenderTexture*> iterator(*this);
    while (iterator.hasNext()) {
        iterator.next();
        generateItem(iterator.key(), iterator.value(), false, false);
    }
    dataChanged();
    treeWidget()->expandItem(this);
}

void UiTextureItems::dataChanged() {
    treeWidget()->sortItems(0, Qt::AscendingOrder);
}

bool UiTextureItems::askForImport(UiSyncItem *, const QFileInfoList &list) {
    UiSyncItem *item = 0;
    foreach(const QFileInfo &file, list)
        if((file.suffix().toLower() == "png") || (file.suffix().toLower() == "jpg") || (file.suffix().toLower() == "jpeg"))
            item = generateItem("background", new UiRenderTexture(file.baseName(), file, NxRect(-4, 4, 8, -8)));
    dataChanged();
    if(item)
        highlight(item);
    return true;
}
bool UiTextureItems::askForDeletion(UiSyncItem *i, bool) {
    //qDebug("[DELETE TEXTURE]");
    UiTextureItem *item = (UiTextureItem*)i;
    remove(item->name);
    delete item;
    dataChanged();
    return true;
}
bool UiTextureItems::askForPaste(UiSyncItem*, const QList<UiSyncItem*> &listItems) {
    foreach(UiSyncItem *listItem, listItems)
        generateItem(listItem);
    dataChanged();
    return false;
}
const QString UiTextureItems::renameKey(const QString &oldKey, const QString &newKey) {
    if(oldKey == newKey)
        return newKey;
    QString correctNewKey = newKey;
    correctNewKey = correctNewKey.replace(" ", "_");
    quint16 iterations = 1;
    while((correctNewKey.isEmpty()) || (contains(correctNewKey)))
        correctNewKey = newKey + QString("_%1").arg(iterations++);
    UiRenderTexture *texture = value(oldKey);
    texture->name = correctNewKey;
    (*this)[correctNewKey] = texture;
    remove(oldKey);
    dataChanged();
    return correctNewKey;
}
UiRenderTexture* UiTextureItems::setValue(const QString &key, UiRenderTexture *texture) {
    (*this)[key] = texture;
    Application::current->execute(QString("%1 %2 %3  %4 %5 %6 %7").arg(COMMAND_TEXTURE).arg(key).arg(texture->mapping.topLeft().x()).arg(texture->mapping.topLeft().y()).arg(texture->mapping.bottomRight().x()).arg(texture->mapping.bottomRight().y()).arg(texture->filename.fileName()), ExecuteSourceInformative);
    dataChanged();
    return texture;
}





UiTextureItem::UiTextureItem(UiSyncList *_baseList, UiSyncItem *_parent) :
    UiSyncItem(_parent) {
    baseList = _baseList;
    //qDebug("[CREATION TEXTURE]");
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
}

QVariant UiTextureItem::data(int column, int role) const {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if(column == 0) return name;
        if(column == 1) {
            if(texture->filename.exists())  return texture->filename.fileName();
            else                            return "...";
        }
        if(column == 2) return  texture->mapping.center().x();
        if(column == 3) return  texture->mapping.center().y();
        if(column == 4) return  texture->mapping.width();
        if(column == 5) return -texture->mapping.height();
    }
    return QTreeWidgetItem::data(column, role);
}
void UiTextureItem::setData(int column, int role, const QVariant &value) {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        qreal mCenterX = texture->mapping.center().x();
        qreal mCenterY = texture->mapping.center().y();
        qreal mWidth   = texture->mapping.width();
        qreal mHeight  = texture->mapping.height();
        if(column == 0) name = baseList->renameKey(name, value.toString());
        if(column == 1) { texture->filename = value.toString(); texture->loaded = false; }
        if(column == 2) mCenterX =  value.toDouble();
        if(column == 3) mCenterY =  value.toDouble();
        if(column == 4) mWidth   =  value.toDouble();
        if(column == 5) mHeight  = -value.toDouble();
        texture->mapping = NxRect(NxPoint(mCenterX-mWidth/2, mCenterY-mHeight/2), NxSize(mWidth, mHeight));
        baseList->setValue(name, texture);
        dataChanged();
        return;
    }
    return QTreeWidgetItem::setData(column, role, value);
}
