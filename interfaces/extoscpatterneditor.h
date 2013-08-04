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

#ifndef EXTOSCPATTERNEDITOR_H
#define EXTOSCPATTERNEDITOR_H

#include <QCompleter>
#include <QWidget>
#include <QPlainTextEdit>
#include <QDir>
#include "gui/uimessagebox.h"
#include "misc/application.h"
#include "objects/nxobject.h"
#include "misc/help.h"

namespace Ui {
    class ExtOscPatternEditor;
}
class QPlainTextEditWithFocus : public QPlainTextEdit {
    Q_OBJECT
public:
    QPlainTextEditWithFocus(QWidget *parent = 0):
        QPlainTextEdit(parent) {}
signals:
    void focusOut();
    void focusIn();
protected:
    void focusOutEvent(QFocusEvent *e) {  QPlainTextEdit::focusOutEvent(e);  emit(focusOut());   }
    void focusInEvent(QFocusEvent *e)  {  QPlainTextEdit::focusInEvent(e);   emit(focusIn());    }
};
class QComboBoxWithFocus : public QComboBox {
    Q_OBJECT
public:
    QComboBoxWithFocus(QWidget *parent = 0):
        QComboBox(parent) {}
signals:
    void focusOut();
    void focusIn();
protected:
    void focusOutEvent(QFocusEvent *e) {  QComboBox::focusOutEvent(e);  emit(focusOut());   }
    void focusInEvent(QFocusEvent *e)  {  QComboBox::focusInEvent(e);   emit(focusIn());    }
};

class ExtOscPatternEditor : public QWidget{
    Q_OBJECT

public:
    explicit ExtOscPatternEditor(QWidget *parent);
    ~ExtOscPatternEditor();

private:
    bool textLock, itemLock;
    QList< QPair<QComboBoxWithFocus*, QPair<QLabel*, QPushButton* > > > trees;
    QList< QPushButton > treesButton;
    quint16 patternNbValues;
    bool wasLearning, isTrigger;

public:
    const QString getPattern() const;
    void setPattern(const QString &pattern, bool refreshText);
    void setPattern(const QVector<QByteArray> &messagePatternItems, bool refreshText, bool _isTrigger);
    void setCurrentItem(QComboBox *combo, QLabel *label, const QString &value, bool forceVisible = true);
    QString getItem(QComboBox *combo, const QString &valDefault, const QString &prefix = "") const;
    QString getItem(QComboBox *combo, qint32 valDefault) const;
    void addTemplate(QString text, bool enabled = false);

signals:
    void actionRouteRemove(ExtOscPatternEditor*);
    void actionRouteFocus(QComboBox*,QPlainTextEdit*);

public slots:
    void currentItemChanged();
    void textPatternChanged();
    void clearApattern();
    void fieldFocusIn();
    void learn();
    void applyTemplate();


private:
    Ui::ExtOscPatternEditor *ui;
};

#endif // EXTOSCPATTERNEDITOR_H
