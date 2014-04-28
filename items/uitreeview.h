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

#ifndef UITREEVIEW_H
#define UITREEVIEW_H

#include <QWidget>
#include <QDropEvent>
#include <QTreeWidget>
#include <QUrl>
#include <QComboBox>
#include "uitreeviewwidget.h"
#include "uitreedelegate.h"
#include "misc/options.h"

namespace Ui {
class UiTreeView;
}


class UiTreeView : public QWidget {
    Q_OBJECT
    
public:
    explicit UiTreeView(QWidget *parent = 0);
    ~UiTreeView();

public:
    UiTreeViewWidget* getTree() const;
public:
    void configureColumns(const UiTreeViewOptions &options);

public slots:
    void action();
signals:
    void actionImport(const QFileInfoList &);

private:
    bool canOpen;
    QList<UiSyncItem*> selectionClipboard;
    QList<UiSyncItem*> getSelection(bool shouldHaveParent = true);
    UiSyncItem *currentDocument;
public:
    bool importAsFiles;
    UiSyncItem* getCurrentDocument() const { return currentDocument; }
public:
    void askImport(QStringList files);
    void askImport(bool files);
    void askNew();
    void askSave(bool as = false);
    void askOpen();
    void askNewRoot();
    void askRemove();
    void askCopy();
    void askPaste();

public:
    void showImport   (bool val);
    void showNew      (bool val);
    void showOpen     (bool val);
    void showSave     (bool val);
    void showSaveAs   (bool val);
    void showNewRoot  (bool val);
    void showRemove   (bool val);
    void showCopy     (bool val);
    void showPaste    (bool val);
    void showDuplicate(bool val);

signals:
    void currentDocumentChanged(UiSyncItem *);

protected:
    void keyPressEvent(QKeyEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
private slots:
    void dropEvent(QTreeWidgetItem *source, QTreeWidgetItem *destination);

private:
    Ui::UiTreeView *ui;
};

#endif // UITREEVIEW_H
