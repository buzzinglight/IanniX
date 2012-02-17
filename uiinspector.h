#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "nxdocument.h"
#include "uirender.h"
#include "extoscpatternask.h"
#include "nxobjectfactoryinterface.h"

namespace Ui {
    class UiInspector;
}

class UiInspector : public QWidget {
    Q_OBJECT

public:
    explicit UiInspector(QWidget *parent = 0);
    ~UiInspector();

protected:
    void changeEvent(QEvent *e);

private:
    NxObjectFactoryInterface *factory;
    QTreeWidgetItem *triggerItem, *curveItem, *cursorItem;
    bool actionInfoLock;
    bool idConflict;   ////CG//// Indicates the id in the inspector spinbox conflicts with an existing id
public:
    quint16 nbTriggers, nbCurves, nbCursors;
public slots:
    void setMousePos(const NxPoint & pos);
    void setMouseZoom(qreal zoom);
    void logOscSend(const QString &);
    void logOscReceive(const QString &);
    void actionTabChange(int tab)     { emit(actionRouteTabChange(tab)); }
    void actionViewChange()           { emit(actionRouteViewChange()); }
    void actionCC()                   { emit(actionRouteCC()); }
    void actionCC2()                  { emit(actionRouteCC2()); }
    void actionProjectFiles()         { emit(actionRouteProjectFiles()); }
    void actionProjectScripts()       { emit(actionRouteProjectScripts()); }
    void actionProjectScriptsContext(const QPoint & point)  { emit(actionRouteProjectScriptsContext(point)); }
    void actionProjectFilesContext(const QPoint & point)  { emit(actionRouteProjectFilesContext(point)); }
    void actionInfo();
    void actionInfoID();
    void actionColor();
    void actionNetwork();
    void actionInfoGroup();
    void actionMessages();

    void changeID_success(bool result, quint16 newId);   ////CG////

    QList<NxObject*> getSelectedCCObject() const;
    QList<NxGroup*> getSelectedCC2Object() const;
    inline QTreeWidgetItem *getTriggerItem() const {
        return triggerItem;
    }
    inline QTreeWidgetItem *getCurveItem() const {
        return curveItem;
    }
    inline QTreeWidgetItem *getCursorItem() const {
        return cursorItem;
    }
    QTreeWidget* getViewGroup() const;
    qreal getViewZStart() const;
    qreal getViewZEnd() const;
    QTreeWidget* getProjectFiles() const;
    QTreeWidget* getProjectScripts() const;
    inline void setFactory(NxObjectFactoryInterface *_factory) {
        factory = _factory;
    }

public:
    void clearCCselections(); ////CG////
    quint16 getCurrentTab() const;
    void setCurrentTab(quint16);
    bool getViewTriggerCheck() const;
    void setViewTriggerCheck(bool);
    bool getViewCurveCheck() const;
    void setViewCurveCheck(bool);
    bool getViewCursorCheck() const;
    void setViewCursorCheck(bool);
public slots:
    void setOSCOk(bool);
    void setUDPOk(bool);
    void setSerialOk(bool);
    void setOSCPort(quint16 port);
    void setUDPPort(quint16 port);
    void setSerialPort(const QString & port);
    void setTransportMessage(const QString & message);
    void setSyncMessage(const QString & message);
    quint16 getOSCPort();
    quint16 getUDPPort();
    const QString getSerialPort();
    const QString getTransportMessage();
    const QString getSyncMessage();

private:
    void timerEvent(QTimerEvent *);
    bool needRefresh;
public slots:
    void refresh();
    void askRefresh() {
        needRefresh = true;
    }
    void change(quint16 indexObject, QDoubleSpinBox *spin, qreal val, qreal prevVal);
    void change(quint16 indexObject, QSpinBox *spin, qint32 val, qint32 prevVal);
    void change(quint16 indexObject, QPushButton *spin, const QString & val, const QString & prevVal);
    void change(quint16 indexObject, QCheckBox *spin, quint8 val, quint8 prevVal);
    void change(quint16 indexObject, QLineEdit *spin, const QString & val, const QString & prevVal);
    void change(quint16 indexObject, QComboBox *spin, const QString & val, const QString & prevVal);
    void change(quint16 indexObject, QComboBox *spin, quint16 val, quint16 prevVal);

    void colorComboAdd(QComboBox *spin, QStringList values);


signals:
    void actionRouteTabChange(int);
    void actionRouteViewChange();
    void actionRouteCC();
    void actionRouteCC2();
    void actionRouteProjectFiles();
    void actionRouteProjectScripts();
    void actionRouteProjectStyles();
    void actionRouteProjectScriptsContext(QPoint);
    void actionRouteProjectFilesContext(QPoint);
    void actionRouteProjectStylesContext(QPoint);
    void actionChangeID(quint16,quint16); ////CG////
    void oscPortChange(quint16);
    void udpPortChange(quint16);
    void serialPortChange(const QString &);
    void transportMessageChange(const QString &);
    void syncMessageChange(const QString &);
    void actionIDchange();

private:
    UiRender *render;
public:
    inline void setRender(UiRender *_render) {
        render = _render;
    }


private:
    Ui::UiInspector *ui;
};

#endif // INSPECTOR_H
