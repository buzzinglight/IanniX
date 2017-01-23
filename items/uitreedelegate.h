/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (https://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UITREEDELEGATE_H
#define UITREEDELEGATE_H

#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMouseEvent>
#include <QLineEdit>
#include <QCheckBox>
#include <QEvent>
#include <QPainter>
#include <QFileDialog>
#include <QColorDialog>
#include <QPushButton>
#include <QHeaderView>
#include <QPixmap>

class UiTreeViewOptions {
public:
    QAbstractItemModel *model;
    quint16 index;
    QString name, type, styleSheet;
    qint16 width, height, rootHeight;
    QPixmap iconCheckedOff, iconCheckedOn;
    QFileDialog *dialogFile;
    QColorDialog *dialogColor;
    QHeaderView::ResizeMode resizeMode;
public:
    UiTreeViewOptions() {
        model       = 0;
        width       = -1;
        index       = 0;
        dialogFile  = 0;
        dialogColor = 0;
    }
    explicit UiTreeViewOptions(quint16 _index, const QString &_name, const QString &_type = QString(), const QString &_styleSheet = QString(), QHeaderView::ResizeMode _resizeMode = QHeaderView::ResizeToContents, qint16 _width = -1, qint16 _rootHeight = 1, qint16 _height = 20) {
        model       = 0;
        index       = _index;
        name        = _name;
        type        = _type;
        styleSheet  = _styleSheet;
        resizeMode  = _resizeMode;
        width       = _width;
        height      = _height;
        rootHeight  = _rootHeight;
    }
};
class UiTreeDelegate : public QItemDelegate {
    Q_OBJECT

private:
    UiTreeViewOptions options;

public:
    explicit UiTreeDelegate(const UiTreeViewOptions &_options, QAbstractItemModel *_model, QObject *parent);

public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const;
signals:
    void action(const QModelIndex &index);
};


#endif // UITREEDELEGATE_H
