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
    textLock = false;
    itemLock = false;
    patternNbValues = 0;

    trees.clear();
    trees << qMakePair(ui->value1, ui->value1Label);
    trees << qMakePair(ui->value2, ui->value2Label);
    trees << qMakePair(ui->value3, ui->value3Label);
    trees << qMakePair(ui->value4, ui->value4Label);
    trees << qMakePair(ui->value5, ui->value5Label);
    trees << qMakePair(ui->value6, ui->value6Label);

    for(quint16 treeIndex = 0 ; treeIndex < trees.count() ; treeIndex++)
        trees.at(treeIndex).first->setColumnWidth(0, 150);

    QTreeWidget* tree = trees.first().first;
    for(quint16 treeIndex = 1 ; treeIndex < trees.count() ; treeIndex++) {
        trees.at(treeIndex).first->clear();
        for(quint16 i = 0 ; i < tree->topLevelItemCount() ; i++) {
            QTreeWidgetItem *topLevelItem = tree->topLevelItem(i);
            QTreeWidgetItem *newTopLevelItem = new QTreeWidgetItem(QStringList() << topLevelItem->text(0) << topLevelItem->text(1));
            trees.at(treeIndex).first->addTopLevelItem(newTopLevelItem);

            for(quint16 j = 0 ; j < topLevelItem->childCount() ; j++) {
                QTreeWidgetItem *item = topLevelItem->child(j);
                newTopLevelItem->addChild(new QTreeWidgetItem(QStringList() << item->text(0) << item->text(1)));
            }
        }
    }

    ui->protocol->setColumnWidth(0, 150);
    ui->hostMIDI->setColumnWidth(0, 150);
    ui->addressMIDI->setColumnWidth(0, 150);
    ui->hostOSC->setColumnWidth(0, 150);
    ui->addressOSC->setColumnWidth(0, 150);
    ui->port->setColumnWidth(0, 150);
}

ExtOscPatternEditor::~ExtOscPatternEditor() {
    delete ui;
}

const QString ExtOscPatternEditor::getPattern() const {
    QString messagePattern = "";
    if(ui->protocol->currentItem()) {
        QString protocol = ui->protocol->currentItem()->text(0);
        messagePattern += protocol + "://";
        if(((protocol == "osc") || (protocol == "http")) && (ui->hostOSC->currentItem()) && (ui->port->currentItem()) && (ui->addressOSC->currentItem())) {
            QString ip = ui->hostOSC->currentItem()->text(0);
            quint16 port = ui->port->currentItem()->text(0).toUInt();
            if(ip == "")  ip = "ip_out";
            if(port > 0)  messagePattern += ip + ":" + QString::number(port );
            else          messagePattern += ip;

            QString address = ui->addressOSC->currentItem()->text(0);
            if(address.startsWith("/")) messagePattern += address;
            else                        messagePattern += "/" + address;
        }
        else if(((protocol == "udp") || (protocol == "tcp")) && (ui->hostOSC->currentItem()) && (ui->port->currentItem())) {
            QString ip = ui->hostOSC->currentItem()->text(0);
            quint16 port = ui->port->currentItem()->text(0).toUInt();
            if(ip == "")  ip = "ip_out";
            if(port > 0)  messagePattern += ip + ":" + QString::number(port );
            else          messagePattern += ip;
        }
        else if((protocol == "midi") && (ui->hostMIDI->currentItem()) && (ui->hostMIDI->currentItem())) {
            QString host = ui->hostMIDI->currentItem()->text(0);
            QString address = ui->addressMIDI->currentItem()->text(0);
            if(host == "")  host = "midi_out";
            if(address.startsWith("/")) messagePattern += host + address;
            else                        messagePattern += host + "/" + address;
        }

        if((patternNbValues >= 1) && (ui->value1->currentItem()) && (ui->value1->currentItem()->text(0) != ""))  messagePattern += " " + ui->value1->currentItem()->text(0);
        if((patternNbValues >= 2) && (ui->value2->currentItem()) && (ui->value2->currentItem()->text(0) != ""))  messagePattern += " " + ui->value2->currentItem()->text(0);
        if((patternNbValues >= 3) && (ui->value3->currentItem()) && (ui->value3->currentItem()->text(0) != ""))  messagePattern += " " + ui->value3->currentItem()->text(0);
        if((patternNbValues >= 4) && (ui->value4->currentItem()) && (ui->value4->currentItem()->text(0) != ""))  messagePattern += " " + ui->value4->currentItem()->text(0);
        if((patternNbValues >= 5) && (ui->value5->currentItem()) && (ui->value5->currentItem()->text(0) != ""))  messagePattern += " " + ui->value5->currentItem()->text(0);
        if((patternNbValues >= 6) && (ui->value6->currentItem()) && (ui->value6->currentItem()->text(0) != ""))  messagePattern += " " + ui->value6->currentItem()->text(0);
    }
    return messagePattern;
}

void ExtOscPatternEditor::setPattern(const QString &pattern, bool refreshText) {
    setPattern(NxObject::parseMessagesPattern(pattern).first(), refreshText);
}

void ExtOscPatternEditor::setPattern(const QVector<QByteArray > & messagePatternItems, bool refreshText) {
    itemLock = true;
    QString pattern = "";
    bool first = true;
    quint16 valueIndex = 0;
    patternNbValues = 6;
    foreach(const QByteArray & messagePatternItem, messagePatternItems) {
        if(first) {
            QUrl urlMessage = QUrl(messagePatternItem, QUrl::TolerantMode);
            if(urlMessage.isValid())
                ui->patternEdit->setStyleSheet("");
            else
                ui->patternEdit->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");

            setCurrentItem(ui->protocol, ui->protocolLabel, urlMessage.scheme());
            if((urlMessage.scheme() == "osc") || (urlMessage.scheme() == "http")) {
                setCurrentItem(ui->hostOSC, ui->hostOSCLabel, urlMessage.host());
                setCurrentItem(ui->port, ui->portLabel, QString::number(urlMessage.port()));
                setCurrentItem(ui->addressOSC, ui->addressOSCLabel, urlMessage.path());

                ui->hostMIDI->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMIDI->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                ui->value1Label->setText(tr("VALUE 1"));
                ui->value2Label->setText(tr("VALUE 2"));
                ui->value3Label->setText(tr("VALUE 3"));
                ui->value3->setVisible(true);
                ui->value3Label->setVisible(true);
                ui->value4->setVisible(true);
                ui->value4Label->setVisible(true);
                ui->value5->setVisible(true);
                ui->value5Label->setVisible(true);
                ui->value6->setVisible(true);
                ui->value6Label->setVisible(true);
            }
            else if((urlMessage.scheme() == "udp") || (urlMessage.scheme() == "tcp")) {
                setCurrentItem(ui->hostOSC, ui->hostOSCLabel, urlMessage.host());
                setCurrentItem(ui->port, ui->portLabel, QString::number(urlMessage.port()));
                ui->addressOSC->setVisible(false);
                ui->addressOSCLabel->setVisible(false);
                ui->hostMIDI->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMIDI->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                ui->value1Label->setText(tr("VALUE 1"));
                ui->value2Label->setText(tr("VALUE 2"));
                ui->value3Label->setText(tr("VALUE 3"));
                ui->value3->setVisible(true);
                ui->value3Label->setVisible(true);
                ui->value4->setVisible(true);
                ui->value4Label->setVisible(true);
                ui->value5->setVisible(true);
                ui->value5Label->setVisible(true);
                ui->value6->setVisible(true);
                ui->value6Label->setVisible(true);
            }
            else if(urlMessage.scheme() == "midi") {
                setCurrentItem(ui->hostMIDI, ui->hostMIDILabel, urlMessage.host());
                setCurrentItem(ui->addressMIDI, ui->addressMIDILabel, urlMessage.path());
                ui->hostOSC->setVisible(false);
                ui->hostOSCLabel->setVisible(false);
                ui->port->setVisible(false);
                ui->portLabel->setVisible(false);
                ui->addressOSC->setVisible(false);
                ui->addressOSCLabel->setVisible(false);

                ui->value1Label->setText(tr("MIDI CHANNEL"));
                if(urlMessage.path().toLower() == "/note") {
                    ui->value2Label->setText(tr("NOTE NUMBER"));
                    ui->value3Label->setText(tr("NOTE VELOCITY"));
                    ui->value3->setVisible(true);
                    ui->value3Label->setVisible(true);
                    patternNbValues = 3;
                }
                else if(urlMessage.path().toLower() == "/pgm") {
                    ui->value2Label->setText(tr("PROGRAM ID"));
                    ui->value3->setVisible(false);
                    ui->value3Label->setVisible(false);
                    patternNbValues = 2;
                }
                else if(urlMessage.path().toLower() == "/cc") {
                    ui->value2Label->setText(tr("CONTROLLER ID"));
                    ui->value3Label->setText(tr("CONTROLLER VALUE"));
                    ui->value3->setVisible(true);
                    ui->value3Label->setVisible(true);
                    patternNbValues = 3;
                }
                else if(urlMessage.path().toLower() == "/bend") {
                    ui->value2Label->setText(tr("BEND VALUE"));
                    ui->value3->setVisible(false);
                    ui->value3Label->setVisible(false);
                    patternNbValues = 2;
                }
                else
                    patternNbValues = 3;
                ui->value4->setVisible(false);
                ui->value4Label->setVisible(false);
                ui->value5->setVisible(false);
                ui->value5Label->setVisible(false);
                ui->value6->setVisible(false);
                ui->value6Label->setVisible(false);
            }
            else {
                ui->hostOSC->setVisible(false);
                ui->hostOSCLabel->setVisible(false);
                ui->port->setVisible(false);
                ui->portLabel->setVisible(false);
                ui->addressOSC->setVisible(false);
                ui->addressOSCLabel->setVisible(false);
                ui->hostMIDI->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMIDI->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                ui->value1Label->setText(tr("VALUE 1"));
                ui->value2Label->setText(tr("VALUE 2"));
                ui->value3Label->setText(tr("VALUE 3"));
                ui->value2->setVisible(true);
                ui->value2Label->setVisible(true);
                ui->value3->setVisible(true);
                ui->value3Label->setVisible(true);
                ui->value4->setVisible(true);
                ui->value4Label->setVisible(true);
                ui->value5->setVisible(true);
                ui->value5Label->setVisible(true);
                ui->value6->setVisible(true);
                ui->value6Label->setVisible(true);
            }

            first = false;
        }
        else {
            if(valueIndex < trees.count()) {
                if(valueIndex < patternNbValues)
                    setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second, messagePatternItem, false);
                else
                    setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second, "", false);
            }
            valueIndex++;
        }
        if(valueIndex < patternNbValues)
            pattern += messagePatternItem + " ";
    }
    itemLock = false;
    if(refreshText)
        currentItemChanged();
}

void ExtOscPatternEditor::setCurrentItem(QTreeWidget *tree, QLabel *label, const QString &value, bool forceVisible) {
    QTreeWidgetItem *itemCustom = tree->topLevelItem(tree->topLevelItemCount()-1), *itemChanged = 0;
    for(quint16 i = 0 ; i < tree->topLevelItemCount() ; i++) {
        QTreeWidgetItem *topLevelItem = tree->topLevelItem(i);
        if(topLevelItem->text(0).toLower() == value.toLower()) {
            tree->setCurrentItem(topLevelItem);
            tree->scrollToItem(topLevelItem);
            itemChanged = topLevelItem;
            break;
        }
        for(quint16 j = 0 ; j < topLevelItem->childCount() ; j++) {
            QTreeWidgetItem *item = topLevelItem->child(j);
            if(item->text(0).toLower() == value.toLower()) {
                tree->setCurrentItem(item);
                tree->scrollToItem(item);
                itemChanged = item;
                break;
            }
        }
    }
    if(itemCustom) {
        if(!itemChanged) {
            itemCustom->setText(0, value);
            tree->setCurrentItem(itemCustom);
            tree->scrollToItem(itemCustom);
        }
        else if(itemChanged != itemCustom)
            itemCustom->setText(0, "________");

    }
    if(forceVisible) {
        tree->setVisible(true);
        label->setVisible(true);
    }
}

void ExtOscPatternEditor::currentItemChanged() {
    if(!itemLock) {
        textLock = true;
        ui->patternEdit->setPlainText(getPattern());
        setPattern(ui->patternEdit->toPlainText(), false);
        textLock = false;
    }
}
void ExtOscPatternEditor::textPatternChanged() {
    if(!textLock)
        setPattern(ui->patternEdit->toPlainText(), false);
}


void ExtOscPatternEditor::actionRemove() {
    emit(actionRouteRemove(this));
}
