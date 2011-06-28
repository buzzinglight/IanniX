#include "nxobject.h"

NxObject::NxObject(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
    QObject(parent), QTreeWidgetItem(ccParentItem) {
    renderOptions = _renderOptions;
    factory = parent;
    documentId.clear();
    groupId.clear();
    id = 0;
    active = ObjectsActivityInactive;
    pos = QPointF(0, 0);
    z = 0;
    parentObject = 0;
    selectedHover = false;
    selected = false;
    setMessageTimeInterval(1);
    isDrag = false;
    performCollision = false;
}
