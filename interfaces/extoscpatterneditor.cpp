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
    textLock  = false;
    itemLock  = false;
    isTrigger = false;
    patternNbValues = 0;

    trees.clear();
    trees << qMakePair(ui->argument1Combo, qMakePair(ui->argument1Label, ui->argument1Clear));
    trees << qMakePair(ui->argument2Combo, qMakePair(ui->argument2Label, ui->argument2Clear));
    trees << qMakePair(ui->argument3Combo, qMakePair(ui->argument3Label, ui->argument3Clear));
    trees << qMakePair(ui->argument4Combo, qMakePair(ui->argument4Label, ui->argument4Clear));
    trees << qMakePair(ui->argument5Combo, qMakePair(ui->argument5Label, ui->argument5Clear));
    trees << qMakePair(ui->argument6Combo, qMakePair(ui->argument6Label, ui->argument6Clear));
    trees << qMakePair(ui->argument7Combo, qMakePair(ui->argument7Label, ui->argument7Clear));
    trees << qMakePair(ui->argument8Combo, qMakePair(ui->argument8Label, ui->argument8Clear));
    trees << qMakePair(ui->argument9Combo, qMakePair(ui->argument9Label, ui->argument9Clear));
    trees << qMakePair(ui->argument10Combo, qMakePair(ui->argument10Label, ui->argument10Clear));

    foreach(const HelpInfo &info, Help::categories["protocols"].infos)
        ui->protocolCombo->addItem(info.keyword + QString(" - ") + info.title);
    foreach(const HelpInfo &info, Help::categories["hostIp"].infos)
        ui->hostIpCombo->addItem(info.keyword + QString(" - ") + info.title);
    foreach(const HelpInfo &info, Help::categories["hostMidi"].infos)
        ui->hostMidiCombo->addItem(info.keyword + QString(" - ") + info.title);
    foreach(const HelpInfo &info, Help::categories["port"].infos)
        ui->portCombo->addItem(info.keyword + QString(" - ") + info.title);
    foreach(const HelpInfo &info, Help::categories["addressOsc"].infos)
        ui->addressOscCombo->addItem(info.keyword + QString(" - ") + info.title);
    foreach(const HelpInfo &info, Help::categories["addressMidi"].infos)
        ui->addressMidiCombo->addItem(info.keyword + QString(" - ") + info.title);
    for(quint16 treeIndex = 0 ; treeIndex < trees.count() ; treeIndex++) {
        QStringList completerHelp;
        foreach(const HelpInfo &info, Help::categories["values"].infos) {
            trees.at(treeIndex).first->addItem(info.keyword + QString(" - ") + info.title);
            completerHelp << info.keyword + QString(" - ") + info.title;
        }
        QCompleter *completer = new QCompleter(completerHelp, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        trees.at(treeIndex).first->setCompleter(completer);
    }


    //Templates
    ui->templates->clear();
    addTemplate("Templates", true);
    addTemplate("--");
    QFileInfoList files = QDir(Global::pathApplication.absoluteFilePath() + "/Tools/Templates/").entryInfoList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    files <<              QDir(Global::pathDocuments.absoluteFilePath()   + "/Templates/").entryInfoList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    bool firstTemplate = true;
    QString title;
    foreach(const QFileInfo &file, files) {
        QString header;
        QHash<QString, QString> params;
        QFile templateFile(file.absoluteFilePath());
        if(templateFile.open(QFile::ReadOnly)) {
            QStringList templatesLong = QString(templateFile.readAll()).split("\n", QString::SkipEmptyParts);
            foreach(const QString &templateLong, templatesLong) {
                if(templateLong.startsWith("["))
                    header = templateLong.toLower();
                else if(header == "[general]") {
                    QStringList templateLongSplit = templateLong.split("=");
                    if(templateLongSplit.count() > 1) {
                        QString key = templateLongSplit.at(0).toLower(), value = templateLongSplit.at(1);
                        params.insert(key, value);
                        if(key == "name")
                            title = value;
                    }
                }
                else if(header == "[messages]") {
                    if(!title.isEmpty()) {
                        if(!firstTemplate)
                            addTemplate("--");
                        firstTemplate = false;
                        addTemplate(title);
                        title.clear();
                    }
                    addTemplate("          " + templateLong.trimmed(), true);
                }
            }
        }
    }
}

ExtOscPatternEditor::~ExtOscPatternEditor() {
    delete ui;
}

const QString ExtOscPatternEditor::getPattern() const {
    QString messagePattern = "";
    QString protocol = getItem(ui->protocolCombo, "osc");
    messagePattern += protocol + "://";
    if((protocol == "osc") || (protocol == "http"))
        messagePattern += getItem(ui->hostIpCombo, "ip_out") + ":" + getItem(ui->portCombo, "port_out") + getItem(ui->addressOscCombo, "/iannix", "/");
    else if(protocol == "udp")
        messagePattern += getItem(ui->hostIpCombo, "ip_out") + ":" + getItem(ui->portCombo, "port_out");
    else if(protocol == "midi")
        messagePattern += getItem(ui->hostMidiCombo, "midi_out") + getItem(ui->addressMidiCombo, "/ccf", "/");

    for(quint16 treeIndex = 0 ; treeIndex < trees.count() ; treeIndex++) {
        QString value = getItem(trees.at(treeIndex).first, "");
        if((!value.isEmpty()) && (patternNbValues > treeIndex))
            messagePattern += " " + value;
    }

    return messagePattern;
}

void ExtOscPatternEditor::setPattern(const QString &pattern, bool refreshText) {
    QVector< QVector<QByteArray> > messagePatternItems = NxObject::parseMessagesPattern(pattern);
    if(messagePatternItems.count() > 0)
        setPattern(messagePatternItems.first(), refreshText, isTrigger);
}

void ExtOscPatternEditor::setPattern(const QVector<QByteArray > & messagePatternItems, bool refreshText, bool _isTrigger) {
    isTrigger = _isTrigger;
    itemLock = true;
    bool first = true;
    quint16 valueIndex = 0;
    patternNbValues = trees.count();
    foreach(const QByteArray & messagePatternItem, messagePatternItems) {
        if(first) {
            QString messagePatternItemCpy = messagePatternItem.trimmed();
            messagePatternItemCpy.replace("port_out", "1");

            QUrl urlMessage = QUrl(messagePatternItemCpy, QUrl::TolerantMode);
            if(urlMessage.isValid())    ui->patternEdit->setStyleSheet("");
            else                        ui->patternEdit->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");

            setCurrentItem(ui->protocolCombo, ui->protocolLabel, urlMessage.scheme().toLower());

            if((urlMessage.scheme().toLower() == "osc") || (urlMessage.scheme().toLower() == "http")) {
                if(wasLearning) setCurrentItem(ui->hostIpCombo,     ui->hostOSCLabel,    "ip_out");
                else            setCurrentItem(ui->hostIpCombo,     ui->hostOSCLabel,    urlMessage.host());
                if((wasLearning) || (urlMessage.port() < 10))   setCurrentItem(ui->portCombo, ui->portLabel, "port_out");
                else                                            setCurrentItem(ui->portCombo, ui->portLabel, QString::number(urlMessage.port()));
                setCurrentItem(ui->addressOscCombo, ui->addressOSCLabel, urlMessage.path());

                ui->hostMidiCombo->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMidiCombo->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                for(quint16 i = 0 ; i < trees.count() ; i++) {
                    trees.at(i).first ->setVisible(true);
                    trees.at(i).second.first->setVisible(true);
                    trees.at(i).second.second->setVisible(true);
                    if(urlMessage.scheme().toLower() == "osc")  trees.at(i).second.first->setText(tr("VALUE %1").arg(i+1));
                    else                                        trees.at(i).second.first->setText(tr("QUERY ARG. %1").arg(i+1));
                }
            }
            else if(urlMessage.scheme() == "udp") {
                if(wasLearning) setCurrentItem(ui->hostIpCombo,     ui->hostOSCLabel,    "ip_out");
                else            setCurrentItem(ui->hostIpCombo,     ui->hostOSCLabel,    urlMessage.host());
                if(urlMessage.port() < 10)  setCurrentItem(ui->portCombo, ui->portLabel, "port_out");
                else                        setCurrentItem(ui->portCombo, ui->portLabel, QString::number(urlMessage.port()));
                ui->addressOscCombo->setVisible(false);
                ui->addressOSCLabel->setVisible(false);
                ui->hostMidiCombo->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMidiCombo->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                for(quint16 i = 0 ; i < trees.count() ; i++) {
                    trees.at(i).first ->setVisible(true);
                    trees.at(i).second.first->setVisible(true);
                    trees.at(i).second.second->setVisible(true);
                    trees.at(i).second.first->setText(tr("VALUE %1").arg(i+1));
                }
            }
            else if(urlMessage.scheme() == "midi") {
                if(wasLearning) setCurrentItem(ui->hostMidiCombo,    ui->hostMIDILabel,    "midi_out");
                else            setCurrentItem(ui->hostMidiCombo,    ui->hostMIDILabel,    urlMessage.host());
                setCurrentItem(ui->addressMidiCombo, ui->addressMIDILabel, urlMessage.path());
                ui->hostIpCombo->setVisible(false);
                ui->hostOSCLabel->setVisible(false);
                ui->portCombo->setVisible(false);
                ui->portLabel->setVisible(false);
                ui->addressOscCombo->setVisible(false);
                ui->addressOSCLabel->setVisible(false);

                trees.at(0).second.first->setText(tr("MIDI CHANNEL"));
                if((urlMessage.path().toLower() == "/note") || (urlMessage.path().toLower() == "/notef")) {
                    trees.at(1).second.first->setText(tr("NOTE NUMBER"));
                    trees.at(2).second.first->setText(tr("VELOCITY"));
                    trees.at(3).second.first->setText(tr("DURATION"));
                    patternNbValues = 4;
                }
                else if((urlMessage.path().toLower() == "/pgm") || (urlMessage.path().toLower() == "/pgmf")) {
                    trees.at(1).second.first->setText(tr("PROGRAM ID"));
                    patternNbValues = 2;
                }
                else if((urlMessage.path().toLower() == "/cc") || (urlMessage.path().toLower() == "/ccf")) {
                    trees.at(1).second.first->setText(tr("CONTROLLER ID"));
                    trees.at(2).second.first->setText(tr("VALUE"));
                    patternNbValues = 3;
                }
                else if((urlMessage.path().toLower() == "/bend") || (urlMessage.path().toLower() == "/bendf")) {
                    trees.at(1).second.first->setText(tr("VALUE"));
                    patternNbValues = 2;
                }
                else
                    patternNbValues = 0;

                for(quint16 i = 0 ; i < patternNbValues ; i++) {
                    trees.at(i).first ->setVisible(true);
                    trees.at(i).second.first->setVisible(true);
                    trees.at(i).second.second->setVisible(true);
                }
                for(quint16 i = patternNbValues ; i < trees.count() ; i++) {
                    trees.at(i).first ->setVisible(false);
                    trees.at(i).second.first->setVisible(false);
                    trees.at(i).second.second->setVisible(false);
                }
            }
            else {
                ui->hostIpCombo->setVisible(false);
                ui->hostOSCLabel->setVisible(false);
                ui->portCombo->setVisible(false);
                ui->portLabel->setVisible(false);
                ui->addressOscCombo->setVisible(false);
                ui->addressOSCLabel->setVisible(false);
                ui->hostMidiCombo->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMidiCombo->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                for(quint16 i = 0 ; i < trees.count() ; i++) {
                    trees.at(i).first ->setVisible(true);
                    trees.at(i).second.first->setVisible(true);
                    trees.at(i).second.second->setVisible(true);
                    if(urlMessage.scheme() == "direct") trees.at(i).second.first->setText(tr("COMMAND %1").arg(i+1));
                    else                                trees.at(i).second.first->setText(tr("XML NODE %1").arg(i+1));
                }
            }
            first = false;
        }
        else {
            if(valueIndex < trees.count()) {
                if(valueIndex < patternNbValues)    setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second.first, messagePatternItem, false);
                else                                setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second.first, "",                 false);
            }
            valueIndex++;
        }
    }
    for(; valueIndex < patternNbValues ; valueIndex++)
        setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second.first, "", false);

    itemLock = false;
    wasLearning = false;
    if(refreshText)
        currentItemChanged();
}

void ExtOscPatternEditor::setCurrentItem(QComboBox *combo, QLabel *label, const QString &value, bool forceVisible) {
    bool ok = false;
    for(quint16 i = 0 ; i < combo->count() ; i++) {
        QString val = combo->itemText(i).split(QString(" - "), QString::KeepEmptyParts).at(0);
        if(val == value) {
            combo->setCurrentIndex(i);
            ok = true;
            break;
        }
    }
    if(!ok) {
        combo->setEditText(value);
    }
    if(forceVisible) {
        combo->setVisible(true);
        label->setVisible(true);
    }
}

QString ExtOscPatternEditor::getItem(QComboBox *combo, const QString &valDefault, const QString &prefix) const {
    QString val = combo->currentText().split(QString(" - "), QString::KeepEmptyParts).at(0);
    if(!val.isEmpty()) {
        if(!prefix.isEmpty()) {
            if(val.startsWith(prefix))  return val;
            else                        return prefix + val;
        }
        return val;
    }
    else
        return valDefault;
}
QString ExtOscPatternEditor::getItem(QComboBox *combo, qint32 valDefault) const {
    qint32 val = getItem(combo, "0").toInt();
    if(val > 0) return QString::number(val);
    else        return QString::number(valDefault);
}
void ExtOscPatternEditor::addTemplate(QString text, bool enabled) {
    if(text.trimmed() == "--")      ui->templates->insertSeparator(ui->templates->count());
    else                            ui->templates->addItem(text);
    if(!enabled)
        qobject_cast<QStandardItemModel*>(ui->templates->model())->item(ui->templates->count()-1)->setEnabled(false);
}

void ExtOscPatternEditor::currentItemChanged() {
    if(!itemLock) {
        textLock = true;
        ui->patternEdit->setPlainText(getPattern());
        setPattern(ui->patternEdit->toPlainText().replace("\t", " "), false);
        textLock = false;
    }
}
void ExtOscPatternEditor::textPatternChanged() {
    if(!textLock)
        setPattern(ui->patternEdit->toPlainText().replace("\t", " "), false);
    emit(actionRouteFocus(0, (QPlainTextEdit*)sender()));
}

void ExtOscPatternEditor::clearApattern() {
    if(sender() == ui->argument1Clear)  setCurrentItem(trees.at(0).first, trees.at(0).second.first, "");
    if(sender() == ui->argument2Clear)  setCurrentItem(trees.at(1).first, trees.at(1).second.first, "");
    if(sender() == ui->argument3Clear)  setCurrentItem(trees.at(2).first, trees.at(2).second.first, "");
    if(sender() == ui->argument4Clear)  setCurrentItem(trees.at(3).first, trees.at(3).second.first, "");
    if(sender() == ui->argument5Clear)  setCurrentItem(trees.at(4).first, trees.at(4).second.first, "");
    if(sender() == ui->argument6Clear)  setCurrentItem(trees.at(5).first, trees.at(5).second.first, "");
    if(sender() == ui->argument7Clear)  setCurrentItem(trees.at(6).first, trees.at(6).second.first, "");
    if(sender() == ui->argument8Clear)  setCurrentItem(trees.at(7).first, trees.at(7).second.first, "");
    if(sender() == ui->argument9Clear)  setCurrentItem(trees.at(8).first, trees.at(8).second.first, "");
    if(sender() == ui->argument10Clear)  setCurrentItem(trees.at(9).first, trees.at(9).second.first, "");
    if(sender() == ui->patternClear) {
        itemLock = true;
        textLock = true;
        for(quint16 i = 0 ; i < trees.count() ; i++)
            setCurrentItem(trees.at(i).first, trees.at(i).second.first, "");
        ui->patternEdit->setPlainText("");
        textLock = false;
        itemLock = false;
        currentItemChanged();
    }
}

void ExtOscPatternEditor::fieldFocusIn() {
    if(sender() == ui->patternEdit)
        emit(actionRouteFocus(0, (QPlainTextEdit*)sender()));
    else
        emit(actionRouteFocus((QComboBox*)sender(), 0));
}

void ExtOscPatternEditor::learn() {
    UiMessageBox *displayBox = new UiMessageBox();
    displayBox->display(tr("MIDI/OSC learn"), tr("Please send an event to IanniX\n\nMove a slider on your surface control or press a MIDI note…"));
    QString message = Application::current->waitForMessage();
    if(!message.isEmpty()) {
        QStringList messageArguments = message.split("\t", QString::SkipEmptyParts);
        QString messageRecomposed;
        QString valuePrefix = "cursor_";
        if(isTrigger)
            valuePrefix = "trigger_";
        if(message.contains("/note")) {
            for(quint16 i = 0 ; i < qMin(4, messageArguments.count()) ; i++) {
                QString messageArgument = messageArguments.at(i);
                if(i == 0)      messageRecomposed += messageArgument.replace("/note", "/notef") + " ";
                else if(i == 1) messageRecomposed += messageArgument + " "; //Canal
                else if(i == 2) messageRecomposed += valuePrefix + "value_y "; //Note
                else if(i == 3) messageRecomposed += valuePrefix + "value_x "; //Velocity
            }
            messageRecomposed += " 1";
        }
        else if(message.contains("/cc")) {
            for(quint16 i = 0 ; i < qMin(4, messageArguments.count()) ; i++) {
                QString messageArgument = messageArguments.at(i);
                if(i == 0)      messageRecomposed += messageArgument.replace("/cc", "/ccf") + " ";
                else if(i == 1) messageRecomposed += messageArgument + " "; //Canal
                else if(i == 2) messageRecomposed += messageArgument + " "; //CC ID
                else if(i == 3) messageRecomposed += valuePrefix + "value_y "; //Value
            }
        }
        else if((message.contains("/pgm")) || (message.contains("/bend"))) {
            for(quint16 i = 0 ; i < qMin(3, messageArguments.count()) ; i++) {
                QString messageArgument = messageArguments.at(i);
                if(i == 0)      messageRecomposed += messageArgument.replace("/bend", "/bendf").replace("/pgm", "/pgmf") + " ";
                else if(i == 1) messageRecomposed += messageArgument + " "; //Canal
                else if(i == 2) messageRecomposed += valuePrefix + "value_y "; //Value
            }
        }
        else
            messageRecomposed = message;
        wasLearning = true;
        ui->patternEdit->setPlainText(messageRecomposed.trimmed());
        ui->patternEdit->setPlainText(getPattern());
    }
    displayBox->hide();
    delete displayBox;
}

void ExtOscPatternEditor::applyTemplate() {
    if(ui->templates->currentText().length()) {
        QStringList temp = ui->templates->currentText().split(" | ");
        if(temp.count() > 1)
            ui->patternEdit->setPlainText(temp.first().trimmed());
    }
}
