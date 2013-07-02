#ifndef OPTIONS_H
#define OPTIONS_H

#include <QAction>
#include <QCheckBox>
#include <QPushButton>
#include <QDateTime>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QGLWidget>
#include <QLineEdit>
#include <QDesktopServices>
#include <QList>
#include <QStandardItem>
#include <QFileInfo>
#include <QTreeWidgetItem>
#include "geometry/nxrect.h"

class NxCurvePoint : public NxPoint {
public:
    NxPoint c1, c2;
    qreal   currentLength;
    NxRect  boundingRect;
    bool    smooth;
public:
    explicit NxCurvePoint() {
        currentLength = 0;
        smooth = false;
    }
};

class UiRenderTexture {
public:
    QString   name;
    QFileInfo filename;
    GLuint    texture;
    bool      loaded;
    NxRect    mapping;
public:
    explicit UiRenderTexture() { loaded = false; }
    explicit UiRenderTexture(const QString & _name, const QFileInfo & _filename, const NxRect & _mapping) {
        loaded   = false;
        name     = _name;
        filename = _filename;
        mapping  = _mapping;
    }
};


class UiSyncList {
public:
    virtual       UiRenderTexture* setValue (const QString &/*key*/,          UiRenderTexture *valeur)     { return valeur; }
    virtual const QVariant         setValue (const QString &/*key*/,    const QVariant        &valeur)     { return valeur; }
    virtual const QString          renameKey(const QString &oldKey,     const QVariant        &newKey)     { return renameKey(oldKey, newKey.toString()); }
    virtual const QString          renameKey(const QString &/*oldKey*/, const QString         &newKey)     { return newKey; }
    virtual const NxCurvePoint     setValue (      quint16  /*key*/,    const NxCurvePoint    &valeur)     { return valeur; }
    virtual const QVariant         setValue (      quint16  /*key*/,    const QVariant        &valeur)     { return valeur; }
    virtual       quint16          renameKey(      quint16  oldKey,     const QVariant        &newKey)     { return renameKey(oldKey, newKey.toInt()); }
    virtual       quint16          renameKey(      quint16  /*oldKey*/,       quint16          newKey)     { return newKey; }
};

class UiSyncItem : public QTreeWidgetItem {
public:
    explicit UiSyncItem(UiSyncItem *parent) : QTreeWidgetItem(parent) {
        parentItem = parent;
    }
public:
    UiSyncItem *parentItem;
    virtual void dataChanged() {}
public:
    virtual UiSyncItem* askForNewChild(UiSyncItem *i, bool isRoot)          { if(parentItem) return parentItem->askForNewChild(i, isRoot); else return 0; }
    virtual bool askForMove(UiSyncItem *i1, UiSyncItem *i2)                 { if(parentItem) return parentItem->askForMove    (i1, i2);    else return true; }
    virtual bool askForPaste(UiSyncItem *i, const QList<UiSyncItem*> &list) { if(parentItem) return parentItem->askForPaste   (i, list);   else return true; }
    virtual bool askForDeletion(UiSyncItem *i, bool dialog = false)         { if(parentItem) return parentItem->askForDeletion(i, dialog); else return true; }
    virtual bool askForSave(UiSyncItem *i, bool as = false)                 { if(parentItem) return parentItem->askForSave    (i, as);     else return true; }
    virtual bool canOpen(UiSyncItem *i) const                               { if(parentItem) return parentItem->canOpen       (i);         else return true; }
    virtual bool canSave(UiSyncItem *i) const                               { if(parentItem) return parentItem->canSave       (i);         else return true; }
    virtual bool askForOpen(UiSyncItem *i)                                  { if(parentItem) return parentItem->askForOpen    (i);         else return true; }
    virtual bool askForClose(UiSyncItem *i)                                 { if(parentItem) return parentItem->askForClose   (i);         else return true; }
    virtual bool askForImport(UiSyncItem *i, const QFileInfoList &list)     { if(parentItem) return parentItem->askForImport  (i, list);   else return true; }
public:
    virtual bool highlight(UiSyncItem *item = 0) {
        if(item) {
            treeWidget()->setCurrentItem(item);
            treeWidget()->scrollToItem(item);
            return true;
        }
        else if(((flags() & Qt::ItemIsSelectable) == Qt::ItemIsSelectable) && (treeWidget()))
            return highlight(this);
        else {
            for(quint16 childIndex = 0 ; childIndex < childCount() ; childIndex++)
                if(((UiSyncItem*)child(childIndex))->highlight())
                    return true;
        }
        return false;
    }
};

class UiOption : public QObject {
    Q_OBJECT

public:
    UiOption();

public:
    QString settingName;
    UiSyncItem *syncItem;
protected:
    inline void updateTree() { syncItem->dataChanged(); }
public:
    void setItemSync(UiSyncItem *_sync) { syncItem = _sync; }
public:
    virtual QVariant variant() const = 0;
    virtual void setVariant(const QVariant &val) = 0;
    virtual void applyToGui() = 0;

signals:
    void dataChanged();
};

class UiOptions {
public:
    static void add(UiOption *option, const QString &_settingName) {
        if(!_settingName.isEmpty()) {
            option->settingName = _settingName;
            options.append(option);
        }
    }
    static QList<UiOption*> options;
};




class UiBool : public UiOption {
    Q_OBJECT

protected:
    bool value;
    QAction *toolbarButton;
    QCheckBox *checkBox;
    QPushButton *button;
public:
    UiBool(bool _value = false);
    UiBool(const UiBool&);
    UiBool& operator= (const UiBool &);
    UiBool& operator= (bool);
    operator bool() const;
    bool val() const;
    void applyToGui();

private slots:
    void guiTrigged(bool);
signals:
    void triggered(bool);

public:
    void setAction(QAction*,     const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QCheckBox*,   const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QPushButton*, const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    QVariant variant() const {
        return val();
    }
    void setVariant(const QVariant &val) {
        operator =(val.toBool());
    }
};





class UiReal : public UiOption {
    Q_OBJECT

protected:
    qreal value;
    QSpinBox *spinBox;
    QDoubleSpinBox *doubleSpinBox;
    QComboBox *comboBox;
    QSlider *slider;
public:
    UiReal(qreal _value = 0);
    UiReal(const UiReal&);
    UiReal& operator= (const UiReal &);
    UiReal& operator= (qreal);
    operator qreal() const;
    qreal val() const;
    void applyToGui();

private slots:
    void guiTrigged(double);
    void guiTrigged(int);
signals:
    void triggered(qreal);

public:
    void setAction(QSpinBox*,       const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QDoubleSpinBox*, const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QSlider*,        const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QComboBox*,      const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    QVariant variant() const {
        return val();
    }
    void setVariant(const QVariant &val) {
        operator =(val.toDouble());
    }
};





class UiString : public UiOption {
    Q_OBJECT

protected:
    QString value;
    QLineEdit *edit;
    QSpinBox *spin;
    QPlainTextEdit *plainTextEdit;
    QComboBox *combo;
public:
    UiString(const QString &_value = "");
    UiString(const UiString&);
    UiString& operator= (const UiString &);
    UiString& operator= (const QString &);
    operator QString() const;
    QString val() const;
    void applyToGui();

private slots:
    void guiTrigged(QString);
    void guiTrigged();
signals:
    void triggered(QString);

public:
    void setAction(QLineEdit*,      const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QSpinBox*,       const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QPlainTextEdit*, const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    void setAction(QComboBox*,      const QString &_settingName = "", bool trigEvent = true, bool changeUi = false);
    QVariant variant() const {
        return val();
    }
    void setVariant(const QVariant &val) {
        operator =(val.toString());
    }
};



class UiFile : public UiString {
    Q_OBJECT

public:
    QFileInfo file;
    QDateTime lastWatcherUpdate;
public:
    UiFile(const QString &_value = "");
    UiFile(const QFileInfo &);
    UiFile(const UiFile&);
    UiFile& operator= (const UiFile &);
    UiFile& operator= (const QString &);
    UiFile& operator= (const QFileInfo &);
    operator QString() const;
};


#endif // OPTIONS_H
