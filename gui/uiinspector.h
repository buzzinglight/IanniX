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
#include "misc/application.h"
#include "objects/nxdocument.h"
#include "gui/uimessagebox.h"
#include "render/uirender.h"
#include "interfaces/extoscpatternask.h"
#include "messages/messagemanager.h"

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
    bool actionInfoLock;

public slots:
    void addInterfaces();
    void setMousePos(const NxPoint & pos);
    void setMouseZoom(qreal zoom);
    void setRotationAngles(const NxPoint & pos);
    void actionTabChange(int tab);
    void actionCC(QTreeWidgetItem* item,int col)            { emit(actionRouteCC(item, col)); }
    void actionCC()                                         { emit(actionRouteCC(0, 0)); }
    void actionCCButton();
    void actionInfo();
    void actionInfoID();
    void actionColor();
    void actionTexture();
    void actionInfoGroup();
    void actionMessages();

    QPair<QList<NxGroup *>, UiRenderSelection> getSelectedCCObject() const;
    QTreeWidgetItem *getObjectRootItem() const;
    UiTreeView* getFileWidget() const;

private:
    void timerEvent(QTimerEvent *);
    bool needRefresh;
public slots:
    void showRessourcesTab(const QString &value);
    void showSpaceTab();
    void showConfigTab();
    void clearCCselections();
    void refresh();
    void askRefresh() {  needRefresh = true; }
    void change(quint16 indexObject, QRadioButton   *spin, bool            val, bool            prevVal);
    void change(quint16 indexObject, QDoubleSpinBox *spin, qreal           val, qreal           prevVal);
    void change(quint16 indexObject, QSpinBox       *spin, qint32          val, qint32          prevVal);
    void change(quint16 indexObject, QPushButton    *spin, const QString & val, const QString & prevVal);
    void change(quint16 indexObject, QCheckBox      *spin, quint8          val, quint8          prevVal);
    void change(quint16 indexObject, QLineEdit      *spin, const QString & val, const QString & prevVal);
    void change(quint16 indexObject, QPlainTextEdit *spin, const QString & val, const QString & prevVal);
    void change(quint16 indexObject, QComboBox      *spin, const QString & val, const QString & prevVal, bool isColor = true);
    void change(quint16 indexObject, QComboBox      *spin, qint16          val, qint16          prevVal);

    void colorComboAdd(QComboBox *spin, QStringList values);
    void textureComboAdd(QComboBox *spin, QStringList values);


signals:
    void actionRouteCC(QTreeWidgetItem*,int);
    void actionRouteProjectFiles();
    void actionRouteProjectScripts();

    void actionUnsoloGroups();
    void actionUnsoloObjects();
    void actionUnmuteGroups();
    void actionUnmuteObjects();

private:
    UiRender *render;
    quint16 lastTabBeforeRessources;
public:
    inline void setRender(UiRender *_render) {  render = _render;  }

public:
    QAction *toolbarButton;
protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *);
private:
    Ui::UiInspector *ui;
};

#endif // INSPECTOR_H
