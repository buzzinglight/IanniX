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

#ifndef EXTSCRIPTVARIABLEASK_H
#define EXTSCRIPTVARIABLEASK_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
    class ExtScriptVariableAsk;
}


class ExtScriptVariable : public QTreeWidgetItem {

public:
    ExtScriptVariable(QTreeWidgetItem *topLevel) : QTreeWidgetItem(topLevel) {
        setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
    }

private:
    QString group, prompt, value, def;
public:
    void setInfos(const QString & _group, const QString & _prompt, const QString & _value, const QString & _def) {
        group = _group;
        prompt = _prompt;
        value = _value;
        def = _def;
        setText(0, prompt);
        setText(1, def);
    }
    inline const QString & getGroup() const     { return group; }
    inline const QString & getPrompt() const    { return prompt; }
    inline const QString & getValue() const     { return value; }
    inline bool isDefFloat() const              { bool ok = false; def.toDouble(&ok); return ok; }
    inline const QString & getDefStr() const    { return def; }
    inline qreal getDefFloat() const            { return def.toDouble(); }
    inline void setDef(const QString & _def)    { def = _def; }
};


class ExtScriptVariableAsk : public QDialog {
    Q_OBJECT

public:
    explicit ExtScriptVariableAsk(QWidget *parent = 0);
    ~ExtScriptVariableAsk();

protected:
    void changeEvent(QEvent *e);

private:
    QList<ExtScriptVariable*> variables;
    QString title;
public:
    const QList<ExtScriptVariable*> & ask();
    inline const QString & getTitle() const {
        return title;
    }
    void clear();
    void ask(const QString & group, const QString & prompt, const QString & value, const QString & def);
    void meta(const QString & _title);

private:
    Ui::ExtScriptVariableAsk *ui;
};

#endif // EXTSCRIPTVARIABLEASK_H
