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

#include "extoscpatternask.h"
#include "ui_extoscpatternask.h"

ExtOscPatternAsk::ExtOscPatternAsk(QWidget *parent, QList<NxObject*> *_objects) :
    QDialog(parent),
    ui(new Ui::ExtOscPatternAsk) {
    ui->setupUi(this);
    objects = _objects;
    QStringList messagePatterns;
    onlyCurves = true;
    foreach(const NxObject *object, *objects) {
        if(object->getType() != ObjectsTypeCurve)
            onlyCurves = false;
        foreach(const QVector<QByteArray> & messagePatternItems, object->getMessagePatterns()) {
            QString messagePattern;
            foreach(const QByteArray & messagePatternItem, messagePatternItems)
                messagePattern += messagePatternItem + " ";
            messagePattern = messagePattern.trimmed();
            if(!messagePatterns.contains(messagePattern)) {
                messagePatterns.append(messagePattern);

                ExtOscPatternEditor *patternEditor = new ExtOscPatternEditor(this);
                connect(patternEditor, SIGNAL(actionRouteRemove(ExtOscPatternEditor*)), SLOT(actionRemoveMessage(ExtOscPatternEditor*)));
                ui->tabs->addTab(patternEditor, tr("Message %1").arg(ui->tabs->count()+1));
                ui->tabs->setCurrentIndex(ui->tabs->count()-1);
                patternLists.append(patternEditor);
                patternEditor->setPattern(messagePatternItems, true);
            }
        }
    }
    QRect screen = QApplication::desktop()->geometry();
    move(screen.center() - rect().center());
}

ExtOscPatternAsk::~ExtOscPatternAsk() {
    delete ui;
}

void ExtOscPatternAsk::changeEvent(QEvent *e) {
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void ExtOscPatternAsk::mousePressEvent(QMouseEvent *) {
    /*
    foreach(ExtOscPatternEditor *patternList, patternLists)
        patternList->editFocusOut();
        */
}

const QString ExtOscPatternAsk::getMessagePatterns() const {
    QString messagePattern = "";
    foreach(const ExtOscPatternEditor *patternList, patternLists)
        messagePattern += ", " + patternList->getPattern();
    if(messagePattern.count() > 0)
        messagePattern = "0" + messagePattern;
    return messagePattern;
}

void ExtOscPatternAsk::actionAddMessage() {
    QSettings settings;
    bool isTrigger = false;
    bool isCursor = false;
    foreach(const NxObject *object, *objects) {
        if(object->getType() == ObjectsTypeCursor)
            isCursor = true;
        else if(object->getType() == ObjectsTypeTrigger)
            isTrigger = true;
    }
    QString messagePatternItem = "";
    if((isCursor) && (!isTrigger))
        messagePatternItem = settings.value("defaultMessageCursor").toString();
    else if((!isCursor) && (isTrigger))
        messagePatternItem = settings.value("defaultMessageTrigger").toString();
    else
        messagePatternItem = settings.value("defaultMessage").toString();


    QVector< QVector<QByteArray > > messagePatternItemsList = NxObject::parseMessagesPattern(messagePatternItem);
    foreach(const QVector<QByteArray > & messagePatternItems, messagePatternItemsList) {
        ExtOscPatternEditor *patternEditor = new ExtOscPatternEditor(this);
        connect(patternEditor, SIGNAL(actionRouteRemove(ExtOscPatternEditor*)), SLOT(actionRemoveMessage(ExtOscPatternEditor*)));
        ui->tabs->addTab(patternEditor, tr("Message %1").arg(ui->tabs->count()+1));
        ui->tabs->setCurrentIndex(ui->tabs->count()-1);
        patternLists.append(patternEditor);
        patternEditor->setPattern(messagePatternItems, true);
    }
}

void ExtOscPatternAsk::actionRemoveMessage(ExtOscPatternEditor *editor) {
    if(editor) {
        ui->tabs->removeTab(ui->tabs->currentIndex());
        delete editor;
    }
}
