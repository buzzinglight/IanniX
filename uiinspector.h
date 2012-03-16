/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    QList<QString> wasGroupChecked;
    bool actionInfoLock;
    bool idConflict;   ////CG//// Indicates the id in the inspector spinbox conflicts with an existing id
public:
    quint16 nbTriggers, nbCurves, nbCursors;
    inline Qt::CheckState getWasGroupChecked(const QString & groupId) {
        if(wasGroupChecked.contains(groupId))
            return Qt::Unchecked;
        else
            return Qt::Checked;
    }
    inline void updateWasGroupChecked(NxGroup *group) {
        if((group->checkState(0) == Qt::Checked) && (wasGroupChecked.contains(group->getId())))
            wasGroupChecked.removeOne(group->getId());
        else if((group->checkState(0) == Qt::Unchecked) && (!wasGroupChecked.contains(group->getId())))
            wasGroupChecked.append(group->getId());
    }

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
    bool getViewCurveOpacityCheck() const;
    void setViewCurveOpacityCheck(bool);
public slots:
    void setOSCOk(bool);
    void setUDPOk(bool);
    void setTCPOk(bool);
    void setHttpOk(bool);
    void setSerialOk(bool);
    void setOSCPort(quint16 port);
    void setTCPPort(quint16 port);
    void setTCPClients(quint16 nb);
    void setUDPPort(quint16 port);
    void setHttpPort(quint16 port);
    void setSerialPort(const QString & port);
    void setTransportMessage(const QString & message);
    void setSyncMessage(const QString & message);
    void setBundleMessage(const QString & message, quint16 port);
    quint16 getOSCPort();
    quint16 getUDPPort();
    quint16 getHttpPort();
    const QString getSerialPort();
    const QString getTransportMessage();
    const QString getSyncMessage();
    const QString getBundleHost();
    quint16 getBundlePort();

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
    void tcpPortChange(quint16);
    void httpPortChange(quint16);
    void bundleMessageChange(const QString &, quint16);
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
