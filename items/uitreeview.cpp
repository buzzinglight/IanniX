#include "uitreeview.h"
#include "ui_uitreeview.h"

UiTreeView::UiTreeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiTreeView) {
    ui->setupUi(this);
    currentDocument = 0;
    setAcceptDrops(true);
    connect(ui->view, SIGNAL(dropEvent(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(dropEvent(QTreeWidgetItem*,QTreeWidgetItem*)));
    showNew      (true);
    showRemove   (true);
    showCopy     (true);
    showPaste    (true);
    showDuplicate(true);
    showNewRoot  (false);
    showImport   (false);
    showOpen     (false);
    showSave     (false);
    showSaveAs   (false);
    importAsFiles = true;
}

UiTreeView::~UiTreeView() {
    delete ui;
}

QList<UiSyncItem*> UiTreeView::getSelection(bool shouldHaveParent) {
    QList<UiSyncItem*> retour;
    foreach(QTreeWidgetItem *item, ui->view->selectedItems()) {
        if(((shouldHaveParent) && (((UiSyncItem*)item)->parentItem)) || (!shouldHaveParent))
            retour << (UiSyncItem*)item;
    }
    if((retour.count() == 0) && (ui->view->topLevelItemCount()))
        retour.append(((UiSyncItem*)ui->view->topLevelItem(0)));
    return retour;
}

void UiTreeView::askImport(bool files) {
    QFileDialog *dialogFile = new QFileDialog(0);
    dialogFile->setDirectory(".");
    if(files) {
        dialogFile->setFileMode(QFileDialog::ExistingFiles);
        dialogFile->setNameFilters(QStringList() << "Image files (*.png *.xpm *.jpg)" << "Text files (*.txt)" << "Any files (*)");
        if(dialogFile->exec())
            askImport(dialogFile->selectedFiles());
    }
    else {
        dialogFile->setFileMode(QFileDialog::DirectoryOnly);
        if(dialogFile->exec())
            askImport(dialogFile->selectedFiles());
    }
}
void UiTreeView::askImport(QStringList filesStr) {
    filesStr.sort();
    QFileInfoList files;
    foreach(const QString &file, filesStr)
        files << QFileInfo(file);
    QList<UiSyncItem*> items = getSelection(false);
    foreach(UiSyncItem* item, items) {
        item->askForImport(item, files);
        break;
    }
    emit(actionImport(files));
}
void UiTreeView::askNew() {
    if(canOpen) {
        if((!currentDocument) || ((currentDocument) && (currentDocument->askForClose(currentDocument)))) {
            QList<UiSyncItem*> items = getSelection(false);
            foreach(UiSyncItem* item, items) {
                UiSyncItem *newItem = item->askForNewChild(item, false);
                if((newItem) && (newItem->askForOpen(newItem))) {
                    currentDocument = newItem;
                    emit(currentDocumentChanged(currentDocument));
                }
                return;
            }
        }
    }
    else {
        QList<UiSyncItem*> items = getSelection(false);
        foreach(UiSyncItem* item, items)
            item->askForNewChild(item, false);
    }
}
void UiTreeView::askSave(bool as) {
    if(currentDocument)
        currentDocument->askForSave(currentDocument, as);
}
void UiTreeView::askOpen() {
    if(canOpen) {
        foreach(QTreeWidgetItem *item, ui->view->selectedItems()) {
            UiSyncItem *syncItem = (UiSyncItem*)item;
            if((currentDocument) && (syncItem) && (currentDocument == syncItem))
                currentDocument->askForOpen(currentDocument);
            else if(syncItem->canOpen(syncItem)) {
                if(currentDocument)
                    currentDocument->askForClose(currentDocument);
                if(syncItem->askForOpen(syncItem)) {
                    currentDocument = syncItem;
                    emit(currentDocumentChanged(currentDocument));
                    break;
                }
            }
        }
    }
}
void UiTreeView::askNewRoot() {
    QList<UiSyncItem*> items = getSelection();
    foreach(UiSyncItem* item, items) {
        if(item->askForNewChild(item, true))
            break;
    }
}
void UiTreeView::askRemove() {
    QList<UiSyncItem*> items = getSelection();
    foreach(UiSyncItem* item, items)
        if(item->parentItem)
            if((item->askForDeletion(item, true)) && (currentDocument == item))
                currentDocument = 0;
}
void UiTreeView::askCopy() {
    selectionClipboard = getSelection();
}
void UiTreeView::askPaste() {
    foreach(QTreeWidgetItem *item, ui->view->selectedItems()) {
        if(((UiSyncItem*)item)->askForPaste((UiSyncItem*)item, selectionClipboard))
            break;
    }
}


void UiTreeView::action() {
    if(sender() == ui->actionAdd)
        askNew();
    else if(sender() == ui->actionAddRoot)
        askNewRoot();
    else if(sender() == ui->actionRemove)
        askRemove();
    else if(sender() == ui->actionImport)
        askImport(importAsFiles);
    else if(sender() == ui->actionDuplicate) {
        askCopy();
        askPaste();
    }
    else if(sender() == ui->actionSave)
        askSave();
    else if(sender() == ui->view)
        askOpen();
}

UiTreeViewWidget *UiTreeView::getTree() const {
    return ui->view;
}


void UiTreeView::configureColumns(const UiTreeViewOptions &options) {
    ui->view->headerItem()->setText(options.index, options.name);
    ui->view->header()->setResizeMode(options.index, options.resizeMode);
    ui->view->setItemDelegateForColumn(options.index, new UiTreeDelegate(options, ui->view->model(), this));
    if(options.width > 0)
        ui->view->setColumnWidth(options.index, options.width);
}


void UiTreeView::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}
void UiTreeView::dropEvent(QDropEvent *event) {
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        QStringList files;
        for(int i = 0; i < urlList.size() && i < 32; ++i)
            files << urlList.at(i).toLocalFile();;
        askImport(files);
        event->acceptProposedAction();
    }
}
void UiTreeView::dropEvent(QTreeWidgetItem *source, QTreeWidgetItem *destination) {
    if((source) && (destination))
        ((UiSyncItem*)source)->askForMove((UiSyncItem*)source, (UiSyncItem*)destination);
}




void UiTreeView::keyPressEvent(QKeyEvent *event) {
    if(ui->view->selectedItems().count()) {
        if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier) {
            if(event->key() == Qt::Key_C)
                askCopy();
            else if(event->key() == Qt::Key_V)
                askPaste();
            else if(event->key() == Qt::Key_D) {
                askCopy();
                askPaste();
            }
            else if(event->key() == Qt::Key_S)
                askSave(((event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier));
            else if(event->key() == Qt::Key_N)
                askNew();
            else if(event->key() == Qt::Key_Backspace)
                askRemove();
        }
    }
}


void UiTreeView::showImport   (bool val) { ui->actionImport   ->setVisible(val); }
void UiTreeView::showNew      (bool val) { ui->actionAdd      ->setVisible(val); }
void UiTreeView::showSave     (bool val) { ui->actionSave     ->setVisible(val); }
void UiTreeView::showNewRoot  (bool val) { ui->actionAddRoot  ->setVisible(val); }
void UiTreeView::showDuplicate(bool val) { ui->actionDuplicate->setVisible(val); }
void UiTreeView::showRemove   (bool val) { ui->actionRemove   ->setVisible(val); }
void UiTreeView::showOpen     (bool val) { canOpen = val; }
void UiTreeView::showSaveAs   (bool /*val*/) {  }
void UiTreeView::showCopy     (bool /*val*/) {  }
void UiTreeView::showPaste    (bool /*val*/) {  }

