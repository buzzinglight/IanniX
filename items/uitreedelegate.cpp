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

#include "uitreedelegate.h"

UiTreeDelegate::UiTreeDelegate(const UiTreeViewOptions &_options, QAbstractItemModel *_model, QObject *parent) :
    QItemDelegate(parent) {
    options = _options;
    options.model = _model;
}
QWidget *UiTreeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    if(options.type.startsWith("spin")) {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(-999999);
        editor->setMaximum( 999999);
        editor->setStyleSheet(options.styleSheet);
        return editor;
    }
    else if(options.type.startsWith("doublespin")) {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setMinimum(-999999);
        editor->setMaximum( 999999);
        editor->setDecimals(2);
        editor->setStyleSheet(options.styleSheet);
        return editor;
    }
    else if((options.type.startsWith("file")) && (options.model)) {
        QFileDialog *dialog = new QFileDialog(0);
        dialog->setFileMode(options.dialogFile->fileMode());
        dialog->setNameFilters(options.dialogFile->nameFilters());
        dialog->setDirectory(QFileInfo(index.model()->data(index, Qt::EditRole).toString()).absoluteDir());
        dialog->selectFile(index.model()->data(index, Qt::EditRole).toString());
        if(dialog->exec()) {
            foreach(const QString &selectedFile, dialog->selectedFiles()) {
                options.model->setData(index, selectedFile, Qt::EditRole);
                break;
            }
        }
    }
    else if(options.type.startsWith("color")) {
        QColor color = options.model->data(index).value<QColor>();
        color = QColorDialog::getColor(color, 0, "Color selector", QColorDialog::ShowAlphaChannel);
        if(color.isValid())
            options.model->setData(index, color, Qt::EditRole);
    }
    else if(options.type.startsWith("edit")) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setStyleSheet(options.styleSheet);
        return editor;
    }
    return 0;
}

void UiTreeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if(editor) {
        if(options.type.startsWith("spin"))
            (static_cast<QSpinBox*>(editor))->setValue(index.model()->data(index, Qt::EditRole).toInt());
        else if(options.type.startsWith("doublespin"))
            (static_cast<QDoubleSpinBox*>(editor))->setValue(index.model()->data(index, Qt::EditRole).toDouble());
        else if(options.type.startsWith("edit"))
            (static_cast<QLineEdit*>(editor))->setText(index.model()->data(index, Qt::EditRole).toString());
    }
}

void UiTreeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    if(editor) {
        if(options.type.startsWith("spin")) {
            QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
            spinBox->interpretText();
            model->setData(index, spinBox->value(), Qt::EditRole);
        }
        else if(options.type.startsWith("doublespin")) {
            QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
            spinBox->interpretText();
            model->setData(index, spinBox->value(), Qt::EditRole);
        }
        else if(options.type.startsWith("edit"))
            model->setData(index, (static_cast<QLineEdit*>(editor))->text(), Qt::EditRole);
    }
}

void UiTreeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    if(editor)
        editor->setGeometry(option.rect);
}

void UiTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if(!index.parent().isValid()) {
        drawBackground(painter, option, index);
        if(index.column() == 0)
            QItemDelegate::paint(painter, option, index);
    }
    else if(options.type.startsWith("checkbox")) {
        drawBackground(painter, option, index);
        if((options.type.startsWith("checkboxS")) && ((option.state & QStyle::State_Selected) != QStyle::State_Selected))
            return;
        else if(!index.data().toString().isEmpty()) {
            if(options.iconCheckedOff.isNull())
                drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
            else {
                qreal correctWidth = option.rect.height() * options.iconCheckedOn.width() / options.iconCheckedOn.height();
                QRect rect = QRect(option.rect.topLeft(), QSize(correctWidth, option.rect.height())).translated(option.rect.width()/2 - correctWidth/2, 0);
                painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
                if(index.data().toBool())   painter->drawPixmap(rect, options.iconCheckedOn);
                else                        painter->drawPixmap(rect, options.iconCheckedOff);
            }
            drawFocus(painter, option, option.rect);
        }
    }
    else if(options.type.startsWith("color")) {
        drawBackground(painter, option, index);
        if(options.model->data(index).canConvert(QVariant::Color)) {
            QRect realRect = option.rect.adjusted(2, 2, -2, -2);
            QColor color = options.model->data(index).value<QColor>();
            if(color.alpha() < 255) {
                QSize pad(5, 5);
                QColor padColor[2];
                padColor[0] = Qt::white;
                padColor[1] = Qt::lightGray;
                quint16 padColorIndexX = 0, padColorIndexY = 0;
                for(quint16 x = realRect.topLeft().x() ; x < realRect.bottomRight().x() ; x += pad.width()) {
                    padColorIndexY = 0;
                    for(quint16 y = realRect.topLeft().y() ; y < realRect.bottomRight().y() ; y += pad.height()) {
                        padColorIndexY++;
                        painter->fillRect(QRect(QPoint(x, y), pad), padColor[(padColorIndexX+padColorIndexY)%2]);
                    }
                    padColorIndexX++;
                }
            }
            painter->fillRect(realRect, color);
        }
    }
    else if(options.type.startsWith("action")) { }
    else
        QItemDelegate::paint(painter, option, index);
}


bool UiTreeDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if((options.type.startsWith("checkbox")) && ((event->type() == QEvent::MouseButtonRelease) || (event->type() == QEvent::MouseButtonDblClick))) {
        if((!index.data().toString().isEmpty()) && (event->type() == QEvent::MouseButtonRelease))
            return model->setData(index, (static_cast<Qt::CheckState>(index.data(Qt::EditRole).toInt()) == Qt::Unchecked ? Qt::Checked : Qt::Unchecked), Qt::EditRole);
        else
            return true;
    }
    if((options.type.startsWith("action")) && ((event->type() == QEvent::MouseButtonRelease) || (event->type() == QEvent::MouseButtonDblClick))) {
        emit(action(index));
        return true;
    }
    return QItemDelegate::editorEvent(event, model, option, index);
}

QSize UiTreeDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &index) const {
    if(!index.parent().isValid())   return QSize(options.width, options.rootHeight);
    else                            return QSize(options.width, options.height);
}
