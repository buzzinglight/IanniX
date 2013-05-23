#ifndef UITREEVIEWWIDGET_H
#define UITREEVIEWWIDGET_H

#include <QTreeWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

class UiTreeViewWidget : public QTreeWidget {
    Q_OBJECT
public:
    explicit UiTreeViewWidget(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    
signals:
    void dropEvent(QTreeWidgetItem*, QTreeWidgetItem*);
    
public slots:
    
};

#endif // UITREEVIEWWIDGET_H
