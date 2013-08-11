#include "uifileitem.h"

QIcon UiFileItem::iconFile;
QIcon UiFileItem::iconFileOpened;
QIcon UiFileItem::iconFolder;
bool  UiFileItem::showDateTime = true;
QStringList UiFileItem::forbiddenDirs;
QStringList UiFileItem::allowedExtensions;

UiFileItem::UiFileItem(const QFileInfo &file, UiFileItem *_parent, QFileSystemWatcher *_watcher) :
    QObject(_parent), UiSyncItem(_parent) {
    isOpened = false;
    currentDepth = -1;
    watcher = _watcher;

    allowedExtensions << "nxscore" << "nxscript" << "nxstyle" << "iannix";
    forbiddenDirs << "Templates";

    if(!watcher) {
        watcher = new QFileSystemWatcher(this);
        connect(watcher, SIGNAL(directoryChanged(QString)), SLOT(fileWatcherDirChanged(QString)));
        connect(watcher, SIGNAL(fileChanged(QString)),      SLOT(fileWatcherFileChanged(QString)));
    }
    isFile = true;
    populate(file);
    highlight();
}

const QString UiFileItem::dateToString(const QDateTime &date) {
    quint16 daysTo = date.daysTo(QDateTime::currentDateTime());

    if(daysTo > 7)
        return date.toString("yyyy-MM-dd hh:mm");
    else if(daysTo > 1)
        return date.toString("dddd, hh:mm");
    else
        return tr("Today, ") + date.toString("hh:mm");
}

QVariant UiFileItem::data(int column, int role) const {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if(column == 0) return filename.variant();
        if(showDateTime) {
            if(column == 1) {
                if(filename.file.exists()) return dateToString(filename.file.lastModified());
                else                        return "-";
            }
            if(column == 2) return openInFinder.variant();
        }
        else
            if(column == 1) return openInFinder.variant();
    }
    return QTreeWidgetItem::data(column, role);
}
void UiFileItem::setData(int column, int role, const QVariant &value) {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        if(column == 0) return filename.setVariant(value);
        if(((!showDateTime) && (column == 1)) || ((showDateTime) && (column == 2))) return openInFinder.setVariant(value);
    }
    return QTreeWidgetItem::setData(column, role, value);
}


void UiFileItem::populate(const QFileInfo &file) {
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    filename = file;
    filename.lastWatcherUpdate = QDateTime::currentDateTime();
    if(filename.file.isDir()) {
        isFile = false;
        QString filepath = filename.file.absoluteFilePath();
        if(filepath.endsWith("/")) {
            filepath.chop(1);
            filename = QFileInfo(filepath);
        }
        if(parentItem)  setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
        else            setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled);
        for(quint16 colIndex = 0 ; colIndex < 3 ; colIndex++)
            setForeground(colIndex, Qt::lightGray);
        setIcon(0, iconFolder);
    }
    else if(filename.file.isFile()) {
        isFile  = true;
        filename    .setItemSync(this);
        openInFinder.setItemSync(this);
        setIcon(0, iconFile);
    }
    connect(&filename,     SIGNAL(triggered(QString)), SLOT(fileRename()));
    connect(&openInFinder, SIGNAL(triggered(bool)),    SLOT(fileShowInFinder()));
}



bool UiFileItem::askForDeletion(UiSyncItem *, bool dialog) {
    if(dialog) {
        int rep = (new UiMessageBox())->display(tr("Score deletion"), tr("You are about to delete this file. Are you sure?"), QDialogButtonBox::Yes | QDialogButtonBox::No);
        if(rep) {
#ifdef Q_OS_MAC
            fileRename(filename.file, QFileInfo(QDesktopServices::storageLocation(QDesktopServices::HomeLocation) + "/.Trash/" + filename.file.fileName()));
#else
            QFile::remove(filename.file.absoluteFilePath());
#endif
            delete this;
        }
    }
    else if(!isOpened) {
        if(dialog) {
            delete this;
        }
        else
            delete this;
        return true;
    }
    return false;
}
UiSyncItem* UiFileItem::askForNewChild(UiSyncItem*, bool isRoot) {
    UiFileItem *creationItem = (UiFileItem*)parentItem;
    if((filename.file.isDir()) || (isRoot))
        creationItem = this;
    if(creationItem) {
        UiFileItem *item = creationItem;
        if(isRoot) {
            if(creationItem->filename.file.isDir()) QDir().mkpath(fileGetName(QFileInfo(creationItem->filename.file.absoluteFilePath() + "/New Folder")).absoluteFilePath());
            else                                    QDir().mkpath(fileGetName(QFileInfo(creationItem->filename.file.absolutePath()     + "/New Folder")).absoluteFilePath());
            creationItem->fileWatcherDirChanged(QString());
            return creationItem;
        }
        else {
            QString prefix = filename.file.absolutePath() + "/";
            if(filename.file.isDir())
                prefix = filename.file.absoluteFilePath() + "/";
            QFileInfo file(prefix + "New score.iannix");
            item = new UiFileItem(file, creationItem, watcher);
            treeWidget()->setCurrentItem(item);
            treeWidget()->scrollToItem(item);
        }
        //Sorting
        if(creationItem->childCount())
            creationItem->sortChildren(0, Qt::AscendingOrder);
        return item;
    }
    return 0;
}
bool UiFileItem::askForMove(UiSyncItem*, UiSyncItem *_dest) {
    UiFileItem *dest = (UiFileItem*)_dest;
    if(dest->filename.file.isDir()) return fileRename(filename.file, QFileInfo(dest->filename.file.absoluteFilePath() + "/" + filename.file.fileName()), this);
    else                            return fileRename(filename.file, QFileInfo(dest->filename.file.absolutePath()     + "/" + filename.file.fileName()), this);
    return false;
}

bool UiFileItem::askForPaste(UiSyncItem*, const QList<UiSyncItem *> &selections) {
    foreach(UiSyncItem* selection, selections) {
        UiFileItem *item = (UiFileItem*)selection, *creationItem = (UiFileItem*)parentItem;
        if(item->filename.file.isFile()) {
            if((filename.file.isDir()) && (item->filename.file != filename.file))
                creationItem = this;
            if((creationItem) && (fileCopy(item->filename.file, fileGetName(QFileInfo(creationItem->filename.file.absoluteFilePath() + "/" + item->filename.file.fileName())))))
                creationItem->fileWatcherDirChanged(QString());
        }
    }
    return true;
}
bool UiFileItem::askForClose(UiSyncItem*) {
    if(watcher) {
        if(watcher->files().count())
            watcher->removePaths(watcher->files());
    }
    setFont(0, font(1));
    isOpened = false;
    fileClose();
    return true;
}
bool UiFileItem::askForOpen(UiSyncItem*) {
    if(isOpened) {
        if(filename.file.exists())
            fileReload();
    }
    else {
        if((filename.file.exists()) && (!watcher->files().contains(filename.file.absoluteFilePath())))
            watcher->addPath(filename.file.absoluteFilePath());
        isOpened = true;
        fileOpen();
    }
    return isOpened;
}
bool UiFileItem::askForSave(UiSyncItem*, bool as) {
    if((!filename.file.exists()) || (as)) {
        QString file = QFileDialog::getSaveFileName(0, "Save score", filename.file.absoluteFilePath(), QString("IanniX score (*.iannix)"));
        if(!file.isEmpty()) {
            filename = QFileInfo(file);
            setIcon(0, iconFile);
            fileSave();
            syncWith(QFileInfoList() << filename.file, treeWidget());
            return true;
        }
    }
    else
        fileSave();
    return false;
}
bool UiFileItem::askForImport(UiSyncItem*, const QFileInfoList &list) {
    syncWith(list, treeWidget());
    return true;
}




const QFileInfo UiFileItem::fileGetName(const QFileInfo &base) {
    QFileInfo retour = base;
    quint16 iteration = 0;
    while(retour.exists()) {
        QString suffix = " ";
        if(iteration == 0)      suffix += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm");
        else if(iteration == 1) suffix += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
        else if(iteration == 2) suffix += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz");
        else                    suffix += QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + QString(" (%1)").arg(iteration);
        retour = QFileInfo(base.absolutePath() + "/" + base.baseName() + suffix + ((base.isDir())?(""):("." + base.completeSuffix())));
        iteration++;
    }
    return retour;
}
bool UiFileItem::fileCopy(const QFileInfo &source, const QFileInfo &dest) {
    return QFile::copy(source.absoluteFilePath(), dest.absoluteFilePath());
}
void UiFileItem::fileRename() {
    fileRename(filename.file.absoluteFilePath(), filename.val(), this);
}
bool UiFileItem::fileRename(const QFileInfo &source, const QString &newNameWithoutSuffix, UiFileItem *item) {
    if(source.isFile()) return fileRename(source, QFileInfo(source.absolutePath() + "/" + newNameWithoutSuffix + "." + source.suffix()), item);
    else                return fileRename(source, QFileInfo(source.absolutePath() + "/" + newNameWithoutSuffix),                         item);
}
bool UiFileItem::fileRename(const QFileInfo &source, const QFileInfo &destination, UiFileItem *item) {
    if(source != destination) {
        QFileInfo correctDestination = fileGetName(destination);
        if(QFile::rename(source.absoluteFilePath(), correctDestination.absoluteFilePath())) {
            if(item)
                item->filename = QFileInfo(correctDestination.absoluteFilePath());
            return true;
        }
    }
    return false;
}


UiFileItem* UiFileItem::find(const QFileInfo &search, QTreeWidget *tree) {
    for(quint16 i = 0 ; i < tree->topLevelItemCount() ; i++) {
        UiFileItem *item = ((UiFileItem*)tree->topLevelItem(i))->find(search);
        if(item)
            return item;
    }
    return 0;
}
UiFileItem* UiFileItem::find(const QFileInfo &search) {
    if(filename.file == search)
        return this;
    else {
        for(quint16 childIndex = 0 ; childIndex < childCount() ; childIndex++) {
            UiFileItem *item = ((UiFileItem*)child(childIndex))->find(search);
            if(item)
                return item;
        }
    }
    return 0;
}


void UiFileItem::syncWith(const QFileInfoList &files, QTreeWidget *treeWidget) {
    foreach(const QFileInfo &file, files) {
        UiFileItem *existingItem = 0;
        for(quint16 i = 0 ; i < treeWidget->topLevelItemCount() ; i++) {
            UiFileItem *searchItem = ((UiFileItem*)treeWidget->topLevelItem(i))->find(file);
            if(searchItem) {
                existingItem = searchItem;
                treeWidget->setCurrentItem(existingItem);
                treeWidget->scrollToItem(existingItem);
                break;
            }
        }
        if((!existingItem) && (file.exists())) {
            if(conformFile(file)) {
                UiFileItem *baseItem = new UiFileItem(file, 0, 0);
                treeWidget->addTopLevelItem(baseItem);
                treeWidget->sortItems(0, Qt::AscendingOrder);
                baseItem->syncWith(5);
                baseItem->highlight();
            }
        }
    }
}
void UiFileItem::syncWith(qint16 depth) {
    QStringList directories;
    if(filename.file.isDir()) {
        directories.append(filename.file.absoluteFilePath());
        directories.append(syncWith(QDir(filename.file.absoluteFilePath()), depth));
    }
    if(watcher)
        foreach(const QString &directory, directories)
            if(!watcher->directories().contains(directory))
                watcher->addPath(directory);
}
QStringList UiFileItem::syncWith(const QDir &dir, qint16 depth) {
    QStringList directories;
    if(currentDepth < 0)
        currentDepth = depth;
    if(currentDepth < 0)
        return directories;

    //Listing
    QFileInfoList files = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);

    //List all existing objects
    QHash<QString, UiFileItem*> pathChildren;
    for(quint16 childIndex = 0 ; childIndex < childCount() ; childIndex++) {
        UiFileItem *item = (UiFileItem*)child(childIndex);
        pathChildren.insert(item->filename.file.absoluteFilePath(), item);
    }

    //Parse files
    foreach(const QFileInfo &file, files) {
        QString fileAbsolutePath = file.absoluteFilePath();
        UiFileItem *item = 0;
        if(pathChildren.contains(fileAbsolutePath)) {
            item = pathChildren.value(fileAbsolutePath);
            pathChildren.remove(fileAbsolutePath);
        }
        if(item) {
            if(item->filename.file.isDir())
                item->fileWatcherDirChanged(QString());
        }
        else {
            if(conformFile(file)) {
                item = new UiFileItem(file, this, watcher);
                if( file.isDir())                   directories.append(file.absoluteFilePath());
                if((file.isDir()) && (depth > 0))   directories.append(item->syncWith(QDir(fileAbsolutePath + "/"), currentDepth-1));
            }
        }
    }

    //Remove deleted elements
    QMutableHashIterator<QString, UiFileItem*> pathChild(pathChildren);
    while (pathChild.hasNext()) {
        pathChild.next();
        pathChild.value()->askForDeletion(pathChild.value());
        pathChildren.remove(pathChild.key());
    }

    //Sorting
    sortChildren(0, Qt::AscendingOrder);
    return directories;
}
bool UiFileItem::highlight(UiSyncItem *item) {
    if(item) {
        treeWidget()->setCurrentItem(item);
        treeWidget()->scrollToItem(item);
        return true;
    }
    else if(((flags() & Qt::ItemIsSelectable) == Qt::ItemIsSelectable) && (treeWidget()))
        return highlight(this);
    else {
        for(quint16 childIndex = 0 ; childIndex < childCount() ; childIndex++)
            if((((UiFileItem*)child(childIndex))->filename.file.isFile()) && (((UiFileItem*)child(childIndex))->highlight()))
                return true;
        for(quint16 childIndex = 0 ; childIndex < childCount() ; childIndex++)
            if((((UiFileItem*)child(childIndex))->filename.file.isDir())  && (((UiFileItem*)child(childIndex))->highlight()))
                return true;
    }
    return false;
}



void UiFileItem::fileWatcherDirChanged(QString dir) {
    if(watcher) {
        UiFileItem *itemConcerned = find(QFileInfo(dir));
        if((itemConcerned) && (itemConcerned != this)) {
            itemConcerned->fileWatcherDirChanged(dir);
            return;
        }
    }
    if(filename.lastWatcherUpdate.msecsTo(QDateTime::currentDateTime()) > 1000) {
        filename.lastWatcherUpdate = QDateTime::currentDateTime();
        if(filename.file.isDir()) {
            if(QDir(filename.file.absoluteFilePath()).exists())     syncWith(currentDepth);
            else                                                    askForDeletion(this);
        }
    }
}
void UiFileItem::fileWatcherFileChanged(QString file) {
    if(watcher) {
        UiFileItem *itemConcerned = find(QFileInfo(file));
        if((itemConcerned) && (itemConcerned != this)) {
            itemConcerned->fileWatcherFileChanged(file);
            return;
        }
    }
    if(filename.lastWatcherUpdate.msecsTo(QDateTime::currentDateTime()) > 1000) {
        filename.lastWatcherUpdate = QDateTime::currentDateTime();
        if(isOpened)
            fileReload();
    }
}

void UiFileItem::fileShowInFinder() {
#ifdef Q_OS_MAC
    QStringList scriptArgs;
    scriptArgs << QLatin1String("-e") << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"").arg(filename.file.absoluteFilePath());
    QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
    scriptArgs.clear();
    scriptArgs << QLatin1String("-e") << QLatin1String("tell application \"Finder\" to activate");
    QProcess::execute("/usr/bin/osascript", scriptArgs);
#endif
}
void UiFileItem::fileShowInOS() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(filename.file.absoluteFilePath()));
}

void UiFileItem::configure(UiTreeView *tree, bool _showDateTime) {
    iconFolder     = QIcon(":/items/res_item_folder.png");
    iconFile       = QIcon(":/items/res_item_file.png");
    iconFileOpened = QIcon(":/items/res_item_file_opened.png");
    showDateTime = _showDateTime;

    tree->getTree()->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);
    tree->getTree()->setIndentation(15);
    tree->getTree()->setHeaderHidden(false);

    quint16 columnIndex = 0;
    tree->configureColumns(    UiTreeViewOptions(columnIndex++, "Filename", "edit"     , "margin:0px;", QHeaderView::Stretch, 410, 20, 20));
    if(showDateTime)
        tree->configureColumns(UiTreeViewOptions(columnIndex++, "Date"    , ""         , ""           , QHeaderView::Fixed,   120, 20, 20));
    UiTreeViewOptions col3 =   UiTreeViewOptions(columnIndex++, ""        , "checkboxS", ""           , QHeaderView::Fixed,   30 , 20, 20);
    col3.iconCheckedOn = col3.iconCheckedOff = QPixmap(":/items/res_item_reveal.png");
    tree->configureColumns(col3);
}


bool UiFileItem::conformFile(const QFileInfo &file) {
    if(file.isDir())
        return !forbiddenDirs.contains(file.baseName());
    else if(file.isFile()) {
        if(allowedExtensions.count())
            return allowedExtensions.contains(file.suffix());
        else
            return true;
    }
    return false;
}
