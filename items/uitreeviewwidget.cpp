#include "uitreeviewwidget.h"

UiTreeViewWidget::UiTreeViewWidget(QWidget *parent) :
    QTreeWidget(parent) {
    setAcceptDrops(true);
}

void UiTreeViewWidget::dragEnterEvent(QDragEnterEvent *event) {
    QTreeWidget::dragEnterEvent(event);
}
void UiTreeViewWidget::dropEvent(QDropEvent *event) {
    emit(dropEvent(currentItem(), itemAt(event->pos())));
    event->acceptProposedAction();
}
