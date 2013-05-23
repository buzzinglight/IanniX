#ifndef UICOLORITEM_H
#define UICOLORITEM_H

#include "uitreeview.h"
#include "misc/options.h"
#include "misc/application.h"
#include "iannix_cmd.h"

class UiColorItem : public UiSyncItem {
public:
    explicit UiColorItem(UiSyncList *_baseList, UiSyncItem *_parent = 0);

public:
    QString name;
    QColor color;
private:
    UiSyncList *baseList;
protected:
    QVariant data(int column, int role) const;
    void setData(int column, int role, const QVariant &value);

protected:
    void dataChanged() { emitDataChanged(); }
};



class UiColorItems : public QMap<QString, QColor>, public UiSyncItem, public UiSyncList {
public:
    explicit UiColorItems(UiSyncItem *_parent = 0);
private:
    UiColorItem* generateItem(UiSyncItem *otherItem, bool doInsert = true, bool fromGui = true);
    UiColorItem* generateItem(const QString &name, const QColor &color, bool insert = true, bool fromGui = true);

public:
    QStringList changes;
    void configure(const QString &, UiTreeView *);
    bool update();
protected:
    UiSyncItem* askForNewChild(UiSyncItem *i, bool isRoot);
    bool askForDeletion(UiSyncItem *i, bool);
    bool askForPaste(UiSyncItem *i, const QList<UiSyncItem *> &list);
protected:
    const QVariant setValue(const QString &key, const QVariant &valeur);
    const QString renameKey(const QString &oldKey, const QString &newKey);
protected:
    void dataChanged();
};

#endif // UICOLORITEM_H
