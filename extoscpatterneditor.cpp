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

#include "extoscpatterneditor.h"
#include "ui_extoscpatterneditor.h"

ExtOscPatternEditor::ExtOscPatternEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtOscPatternEditor) {
    ui->setupUi(this);
    ui->patternList->clear();
    ui->patternEdit->setPlainText("");
}

ExtOscPatternEditor::~ExtOscPatternEditor() {
    delete ui;
}


void ExtOscPatternEditor::addVariable(const QString &variable) {
    QListWidgetItem *item = new QListWidgetItem(variable, ui->patternList);
    item->setFlags(Qt::ItemIsSelectable | /*Qt::ItemIsEditable | */Qt::ItemIsEnabled);
}

const QString ExtOscPatternEditor::getPattern() {
    QString messagePattern = "";
    for(quint16 index = 0 ; index < ui->patternList->count() ; index++)
        messagePattern += ui->patternList->item(index)->text() + " ";
    return messagePattern;
}

void ExtOscPatternEditor::listDoubleClick() {
    ui->patternEdit->setPlainText(getPattern());
    ui->stackedWidget->setCurrentIndex(1);
}
void ExtOscPatternEditor::editFocusOut() {
    if(!ui->patternEdit->toPlainText().isEmpty()) {
        ui->patternList->clear();
        QVector< QVector<QByteArray > > messagePatternItemsList = NxObject::parseMessagesPattern(ui->patternEdit->toPlainText().replace("\t", " "));
        foreach(const QVector<QByteArray > & messagePatternItems, messagePatternItemsList) {
            foreach(const QByteArray & messagePatternItem, messagePatternItems)
                addVariable(messagePatternItem);
        }
    }
    ui->stackedWidget->setCurrentIndex(0);
}
void ExtOscPatternEditor::actionRemove() {
    emit(actionRouteRemove(this));
}
