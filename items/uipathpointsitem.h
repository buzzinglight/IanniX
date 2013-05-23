#ifndef UIPATHPOINTSITEM_H
#define UIPATHPOINTSITEM_H

#include "uitreeview.h"
#include "misc/options.h"
#include "misc/application.h"
#include "iannix_cmd.h"

class UiPathPointsItem : public UiSyncItem {
public:
    explicit UiPathPointsItem(UiSyncList *_baseList, UiSyncItem *_parent = 0);

public:
    quint16 index;
    NxCurvePoint point;
private:
    UiSyncList *baseList;
protected:
    QVariant data(int column, int role) const;
    void setData(int column, int role, const QVariant &value);

protected:
    void dataChanged() { emitDataChanged(); }
};



class UiPathPointsItems : public QList<NxCurvePoint>, public UiSyncItem, public UiSyncList {
public:
    explicit UiPathPointsItems(UiSyncItem *_parent = 0);
private:
    UiPathPointsItem* generateItem(UiSyncItem *otherItem, bool doInsert = true);
    UiPathPointsItem* generateItem(quint16 index, const NxCurvePoint &point, bool doInsert = true);

public:
    void configure(const QString &name, UiTreeView *, bool *_glListRecreate);
    void update();
    bool *glListRecreate;
protected:
    UiSyncItem* askForNewChild(UiSyncItem *i, bool isRoot);
    bool askForDeletion(UiSyncItem *i, bool);
    bool askForPaste(UiSyncItem *i, const QList<UiSyncItem *> &list);
    bool askForMove(UiSyncItem *i1, UiSyncItem *i2);
protected:
    const NxCurvePoint setValue(quint16 key, const NxCurvePoint &valeur);
protected:
    void dataChanged();
};

#endif // UIPATHPOINTSITEM_H
