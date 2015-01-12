/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

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

#include "extscriptvariableask.h"
#include "ui_extscriptvariableask.h"

ExtScriptVariableAsk::ExtScriptVariableAsk(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ExtScriptVariableAsk) {
    ui->setupUi(this);
    ui->variablesList->setColumnWidth(0, 165);
    ui->variablesList->setColumnWidth(1, 100);
}

ExtScriptVariableAsk::~ExtScriptVariableAsk() {
    delete ui;
}

void ExtScriptVariableAsk::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void ExtScriptVariableAsk::clear() {
    ui->variablesList->clear();
}

void ExtScriptVariableAsk::ask(const QString & group, const QString & prompt, const QString & value, const QString & def) {
    QTreeWidgetItem *topLevel = 0;
    for(quint16 index = 0 ; index < ui->variablesList->topLevelItemCount() ; index++) {
        if(ui->variablesList->topLevelItem(index)->text(0) == group) {
            topLevel = ui->variablesList->topLevelItem(index);
            break;
        }
    }

    if(!topLevel) {
        topLevel = new QTreeWidgetItem(ui->variablesList);
        topLevel->setText(0, group);
    }
    ExtScriptVariable *variable = new ExtScriptVariable(topLevel);
    variable->setInfos(group, prompt, value, def);
    variables.append(variable);
}
void ExtScriptVariableAsk::meta(const QString & _title) {
    title = _title;
}

const QList<ExtScriptVariable*> & ExtScriptVariableAsk::ask() {
    if(variables.count() > 0) {
        ui->variablesList->expandAll();
        setWindowTitle(title);
        exec();
        foreach(ExtScriptVariable *variable, variables)
            variable->setDef(variable->text(1));
    }
    else
        accept();
    return variables;
}
