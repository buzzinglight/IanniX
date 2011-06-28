#include "nxgroup.h"

NxGroup::NxGroup(NxObjectFactoryInterface *parent, QTreeWidget *parentList) :
    QObject(parent), QTreeWidgetItem(parentList) {
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
    setCheckState(0, Qt::Checked);
}
