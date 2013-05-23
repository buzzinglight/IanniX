#ifndef UIFILEITEM_H
#define UIFILEITEM_H

#include <QProcess>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>
#include <QFileSystemWatcher>
#include <QTreeWidgetItem>
#include "uitreeview.h"
#include "misc/options.h"

class UiFileItem : public QObject, public UiSyncItem {
    Q_OBJECT

private:
    UiBool       openInFinder;
    qint16       currentDepth;
public:
    UiFile filename;
    bool isFile;
    bool isOpened;
    static QIcon iconFile, iconFolder;

public:
    explicit UiFileItem(const QFileInfo &file, UiFileItem *_parent, QFileSystemWatcher *_watcher);
protected:
    QVariant data(int column, int role) const;
    void setData(int column, int role, const QVariant &value);
public:
    virtual void fileOpen()   { emit(askFileOpen());/*qDebug("Ouverture du fichier %s", qPrintable(filename.file.absoluteFilePath()));*/ }
    virtual void fileSave()   { emit(askFileSave());/*qDebug("Sauvegarde du fichier %s", qPrintable(filename.file.absoluteFilePath()));*/ }
    virtual void fileReload() { emit(askFileReload());/*qDebug("Reload du fichier %s", qPrintable(filename.file.absoluteFilePath()));*/ }
    virtual void fileClose()  { emit(askFileClose());/*qDebug("Fermeture du fichier %s", qPrintable(filename.file.absoluteFilePath()));*/ }
signals:
    void askFileOpen();
    void askFileSave();
    void askFileReload();
    void askFileClose();


public:
    static void syncWith(const QFileInfoList &files, QTreeWidget *treeWidget);
    static void configure(UiTreeView *);
protected:
    void syncWith(qint16 depth);
    UiFileItem* find(const QFileInfo &search);
    QFileSystemWatcher *watcher;
protected:
    void populate(const QFileInfo &file);
    QStringList syncWith(const QDir &dir, qint16 depth = -1);
    bool highlight(UiSyncItem *item = 0);
    static const QFileInfo fileGetName(const QFileInfo &base);
    static bool fileCopy  (const QFileInfo &source, const QFileInfo &dest);
    static bool fileRename(const QFileInfo &source, const QString &newNameWithoutSuffix, UiFileItem *item = 0);
    static bool fileRename(const QFileInfo &source, const QFileInfo &destination, UiFileItem *item = 0);
    static QStringList allowedExtensions;
protected slots:
    void dataChanged() { emitDataChanged(); }
    void fileRename();
    void fileShowInFinder();
    void fileWatcherDirChanged(QString);
    void fileWatcherFileChanged(QString);
    bool askForDeletion(UiSyncItem*, bool dialog = false);
    UiSyncItem *askForNewChild(UiSyncItem*, bool isRoot);
    bool askForMove(UiSyncItem*, UiSyncItem *destination);
    bool askForPaste(UiSyncItem*, const QList<UiSyncItem*> &);
    bool canOpen(UiSyncItem*) const { return isFile; }
    bool canSave(UiSyncItem*) const { return filename.file.exists() && (isOpened); }
    bool askForOpen(UiSyncItem*);
    bool askForClose(UiSyncItem*);
    bool askForSave(UiSyncItem*, bool as = false);
};

#endif // UIFILEITEM_H
