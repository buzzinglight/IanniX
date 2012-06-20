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
    trees << qMakePair(ui->argument1Combo, ui->argument1Label);
    trees << qMakePair(ui->argument2Combo, ui->argument2Label);
    trees << qMakePair(ui->argument3Combo, ui->argument3Label);
    trees << qMakePair(ui->argument4Combo, ui->argument4Label);
    trees << qMakePair(ui->argument5Combo, ui->argument5Label);
    trees << qMakePair(ui->argument6Combo, ui->argument6Label);

    /*
    QCompleter *completer = new QCompleter(this);
    completer->setModel(ui->completerArguments->model());
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setPopup(ui->completerArguments);
    ui->lineEdit->setCompleter(completer);
    */

    QList< QPair<QString, QString> > protocolList;
    protocolList << qMakePair(QString("osc"),                   tr("OpenSoundControl message"));
    protocolList << qMakePair(QString("direct"),                tr("Recursive/loopback message (sent directly to IanniX)"));
    protocolList << qMakePair(QString("midi"),                  tr("MIDI message (control change, note on/off or program change)"));
    protocolList << qMakePair(QString("serial"),                tr("Serial message (UART/RS232)"));
    protocolList << qMakePair(QString("http"),                  tr("HTTP request to a webpage/webservice (GET)"));
    protocolList << qMakePair(QString("udp"),                   tr("Raw UDP message (compatible with PureData)"));
    protocolList << qMakePair(QString("tcp"),                   tr("XML over TCP message (compatible with Flash/Director)"));
    for(quint16 i = 0 ; i < protocolList.count() ; i++)
        ui->protocolCombo->addItem(protocolList.at(i).first + QString(" - ") + protocolList.at(i).second);

    QList< QPair<QString, QString> > hostIpList;
    hostIpList << qMakePair(QString("ip_out"),                  tr("Destination is the default IP set in \"Network\" tab"));
    hostIpList << qMakePair(QString("127.0.0.1"),               tr("Destination is your own computer"));
    for(quint16 i = 0 ; i < hostIpList.count() ; i++)
        ui->hostIpCombo->addItem(hostIpList.at(i).first + QString(" - ") + hostIpList.at(i).second);

    QList< QPair<QString, QString> > hostMidiList;
    hostMidiList << qMakePair(QString("midi_out"),              tr("Destination is the default MIDI device set in \"Network\" tab"));
    hostMidiList << qMakePair(QString("IanniX_Out"),            tr("MIDI device created by IanniX (Mac & Linux only)"));
    for(quint16 i = 0 ; i < hostMidiList.count() ; i++)
        ui->hostMidiCombo->addItem(hostMidiList.at(i).first + QString(" - ") + hostMidiList.at(i).second);

    QList< QPair<QString, QString> > portList;
    portList << qMakePair(QString("57120"),                     tr("Default port used by IanniX"));
    portList << qMakePair(QString("1234"),                      tr("IanniX OSC default input"));
    for(quint16 i = 0 ; i < portList.count() ; i++)
        ui->portCombo->addItem(portList.at(i).first + QString(" - ") + portList.at(i).second);

    QList< QPair<QString, QString> > addressOscList;
    addressOscList << qMakePair(QString("/trigger"),            tr("Default address used for triggers"));
    addressOscList << qMakePair(QString("/cursor"),             tr("Default address used for cursors"));
    addressOscList << qMakePair(QString("/transport"),          tr("Default address used for transport messages"));
    addressOscList << qMakePair(QString("/iannix"),             tr("Default address used to reach IanniX"));
    for(quint16 i = 0 ; i < addressOscList.count() ; i++)
        ui->addressOscCombo->addItem(addressOscList.at(i).first + QString(" - ") + addressOscList.at(i).second);

    QList< QPair<QString, QString> > addressMidiList;
    addressMidiList << qMakePair(QString("/cc"),                tr("Send a control change"));
    addressMidiList << qMakePair(QString("/bend"),              tr("Send a bend"));
    addressMidiList << qMakePair(QString("/pgm"),               tr("Send a program change"));
    addressMidiList << qMakePair(QString("/note"),              tr("Send a note"));
    for(quint16 i = 0 ; i < addressMidiList.count() ; i++)
        ui->addressMidiCombo->addItem(addressMidiList.at(i).first + QString(" - ") + addressMidiList.at(i).second);

    QList< QPair<QString, QString> > argumentList;
    argumentList << qMakePair(QString("trigger_id"),            tr("Returns the ID of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_group_id"),		tr("Returns the group name of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_document_id"),	tr("Returns the document name of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_label"),         tr("Returns the label of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_xPos"),          tr("Returns the x coordinate of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_yPos"),          tr("Returns the y coordinate of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_zPos"),          tr("Returns the z coordinate of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_value_x"),		tr("Returns the x mapped coordinate of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_value_y"),		tr("Returns the y mapped coordinate of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_value_z"),		tr("Returns the z mapped coordinate of the triggered trigger"));
    argumentList << qMakePair(QString("trigger_value"),         tr("When trigger off-time is set, returns 127 when the trigger is trigged and 0 when the trigger is released"));
    argumentList << qMakePair(QString("trigger_distance"),		tr("Returns the distance between the triggered trigger and the cursor that triggers the trigger"));
    argumentList << qMakePair(QString("trigger_side"),          tr("Returns the 0 if trigger is triggered from left to right and 1 for the other side"));
    argumentList << qMakePair(QString("trigger_message_id"),	tr("Returns the ID of the message (each message generates an ascending ID)"));
    argumentList << qMakePair(QString("cursor_id"),             tr("Returns the ID of the running cursor"));
    argumentList << qMakePair(QString("cursor_group_id"),		tr("Returns the group name of the running cursor"));
    argumentList << qMakePair(QString("cursor_document_id"),	tr("Returns the document name of the running cursor"));
    argumentList << qMakePair(QString("cursor_label"),          tr("Returns the label of the running cursor"));
    argumentList << qMakePair(QString("cursor_xPos"),           tr("Returns the x coordinate of the running cursor"));
    argumentList << qMakePair(QString("cursor_yPos"),           tr("Returns the y coordinate of the running cursor"));
    argumentList << qMakePair(QString("cursor_zPos"),           tr("Returns the z coordinate of the running cursor"));
    argumentList << qMakePair(QString("cursor_value_x"),        tr("Returns the x mapped coordinate of the running cursor"));
    argumentList << qMakePair(QString("cursor_value_y"),        tr("Returns the y mapped coordinate of the running cursor"));
    argumentList << qMakePair(QString("cursor_value_z"),        tr("Returns the z mapped coordinate of the running cursor"));
    argumentList << qMakePair(QString("cursor_time"),           tr("Returns the current progression of the cursor on the curve (in seconds)"));
    argumentList << qMakePair(QString("cursor_time_percent"),	tr("Returns the current progression of the cursor on the curve (in percentages, from 0.0 to 1.0)"));
    argumentList << qMakePair(QString("cursor_angle"),          tr("Returne the angle of the cursor"));
    argumentList << qMakePair(QString("cursor_nb_loop"),        tr("Returns the number of loops done by the cursor on the curve"));
    argumentList << qMakePair(QString("cursor_message_id"),		tr("Returns the ID of the message (each message generates an ascending ID)"));
    argumentList << qMakePair(QString("curve_id"),              tr("Returns the ID of curve where the cursor runs on"));
    argumentList << qMakePair(QString("curve_group_id"),        tr("Returns the group name of curve where the cursor runs on"));
    argumentList << qMakePair(QString("curve_document_id"),		tr("Returns the document name of curve where the cursor runs on"));
    argumentList << qMakePair(QString("curve_label"),           tr("Returns the label of curve where the cursor runs on"));
    argumentList << qMakePair(QString("curve_xPos"),            tr("Returns the x coordinate of curve where the cursor runs on"));
    argumentList << qMakePair(QString("curve_yPos"),            tr("Returns the y coordinate of curve where the cursor runs on"));
    argumentList << qMakePair(QString("curve_zPos"),            tr("Returns the z coordinate of curve where the cursor runs on"));
    argumentList << qMakePair(QString("collision_curve_id"),            tr("Returns the ID of the collided curve"));
    argumentList << qMakePair(QString("collision_curve_group_id"),		tr("Returns the group name of the collided curve"));
    argumentList << qMakePair(QString("collision_curve_document_id"),	tr("Returns the document name of the collided curve"));
    argumentList << qMakePair(QString("collision_curve_label"),         tr("Returns the label of the collided curve"));
    argumentList << qMakePair(QString("collision_curve_xPos"),          tr("Returns the x coordinate of the collided curve"));
    argumentList << qMakePair(QString("collision_curve_yPos"),          tr("Returns the y coordinate of the collided curve"));
    argumentList << qMakePair(QString("collision_curve_zPos"),          tr("Returns the z coordinate of the collided curve"));
    argumentList << qMakePair(QString("collision_xPos"),        tr("Returns the x coordinate of the collision between the cursor and the curve"));
    argumentList << qMakePair(QString("collision_yPos"),        tr("Returns the y coordinate of the collision between the cursor and the curve"));
    argumentList << qMakePair(QString("collision_value_x"),		tr("Returns the x mapped coordinate of the collision between the cursor and the curve"));
    argumentList << qMakePair(QString("collision_value_y"),		tr("Returns the y mapped coordinate of the collision between the cursor and the curve"));
    argumentList << qMakePair(QString("collision_distance"),	tr("Returns the distance between the collision and the cursor"));
    argumentList << qMakePair(QString("timetag"),               tr("Set an OSC Timetag (compliant with Internet NTP timestamps) to message"));
    argumentList << qMakePair(QString("status"),                tr("Returns the playback status of score (\"play\"), \"stop\" or \"fastrewind\")"));
    argumentList << qMakePair(QString("nb_triggers"),           tr("Returns the number of triggers in the current score"));
    argumentList << qMakePair(QString("nb_cursors"),            tr("Returns the number of cursors in the current score"));
    argumentList << qMakePair(QString("nb_curves"),             tr("Returns the number of curves in the current score"));
    argumentList << qMakePair(QString("global_time"),           tr("Returns the elapsed time in seconds"));
    argumentList << qMakePair(QString("global_time_verbose"),	tr("Returns the elapsed time as displayed in Transport bar"));
    for(quint16 i = 0 ; i < argumentList.count() ; i++) {
        for(quint16 treeIndex = 0 ; treeIndex < trees.count() ; treeIndex++)
            trees.at(treeIndex).first->addItem(argumentList.at(i).first + QString(" - ") + argumentList.at(i).second);
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
        messagePattern += getItem(ui->hostIpCombo, "ip_out") + ":" + getItem(ui->portCombo, 57120) + getItem(ui->addressOscCombo, "/iannix", "/");
    else if((protocol == "udp") || (protocol == "tcp"))
        messagePattern += getItem(ui->hostIpCombo, "ip_out") + ":" + getItem(ui->portCombo, 57120);
    else if(protocol == "midi")
        messagePattern += getItem(ui->hostMidiCombo, "midi_out") + getItem(ui->addressMidiCombo, "/cc", "/");

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
        setPattern(messagePatternItems.first(), refreshText);
}

void ExtOscPatternEditor::setPattern(const QVector<QByteArray > & messagePatternItems, bool refreshText) {
    itemLock = true;
    bool first = true;
    quint16 valueIndex = 0;
    patternNbValues = 6;
    foreach(const QByteArray & messagePatternItem, messagePatternItems) {
        if(first) {
            QUrl urlMessage = QUrl(messagePatternItem, QUrl::TolerantMode);
            if(urlMessage.isValid())    ui->patternEdit->setStyleSheet("");
            else                        ui->patternEdit->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");

            setCurrentItem(ui->protocolCombo, ui->protocolLabel, urlMessage.scheme().toLower());

            if((urlMessage.scheme().toLower() == "osc") || (urlMessage.scheme().toLower() == "http")) {
                setCurrentItem(ui->hostIpCombo,     ui->hostOSCLabel,    urlMessage.host());
                setCurrentItem(ui->portCombo,       ui->portLabel,       QString::number(urlMessage.port()));
                setCurrentItem(ui->addressOscCombo, ui->addressOSCLabel, urlMessage.path());

                ui->hostMidiCombo->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMidiCombo->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                for(quint16 i = 0 ; i < trees.count() ; i++) {
                    trees.at(i).first ->setVisible(true);
                    trees.at(i).second->setVisible(true);
                    trees.at(i).second->setText(tr("VALUE %1").arg(i+1));
                }
            }
            else if((urlMessage.scheme() == "udp") || (urlMessage.scheme() == "tcp")) {
                setCurrentItem(ui->hostIpCombo, ui->hostOSCLabel, urlMessage.host());
                setCurrentItem(ui->portCombo,   ui->portLabel, QString::number(urlMessage.port()));
                ui->addressOscCombo->setVisible(false);
                ui->addressOSCLabel->setVisible(false);
                ui->hostMidiCombo->setVisible(false);
                ui->hostMIDILabel->setVisible(false);
                ui->addressMidiCombo->setVisible(false);
                ui->addressMIDILabel->setVisible(false);
                for(quint16 i = 0 ; i < trees.count() ; i++) {
                    trees.at(i).first ->setVisible(true);
                    trees.at(i).second->setVisible(true);
                    trees.at(i).second->setText(tr("VALUE %1").arg(i+1));
                }
            }
            else if(urlMessage.scheme() == "midi") {
                setCurrentItem(ui->hostMidiCombo,    ui->hostMIDILabel,    urlMessage.host());
                setCurrentItem(ui->addressMidiCombo, ui->addressMIDILabel, urlMessage.path());
                ui->hostIpCombo->setVisible(false);
                ui->hostOSCLabel->setVisible(false);
                ui->portCombo->setVisible(false);
                ui->portLabel->setVisible(false);
                ui->addressOscCombo->setVisible(false);
                ui->addressOSCLabel->setVisible(false);

                trees.at(0).second->setText(tr("MIDI CHANNEL"));
                if(urlMessage.path().toLower() == "/note") {
                    trees.at(1).second->setText(tr("NOTE NUMBER"));
                    trees.at(2).second->setText(tr("VELOCITY"));
                    trees.at(2).first->setVisible(true);
                    trees.at(2).second->setVisible(true);
                    patternNbValues = 3;
                }
                else if(urlMessage.path().toLower() == "/pgm") {
                    trees.at(1).second->setText(tr("PROGRAM ID"));
                    trees.at(2).first->setVisible(false);
                    trees.at(2).second->setVisible(false);
                    patternNbValues = 2;
                }
                else if(urlMessage.path().toLower() == "/cc") {
                    trees.at(1).second->setText(tr("CONTROLLER ID"));
                    trees.at(2).second->setText(tr("VALUE"));
                    trees.at(2).first->setVisible(true);
                    trees.at(2).second->setVisible(true);
                    patternNbValues = 3;
                }
                else if(urlMessage.path().toLower() == "/bend") {
                    trees.at(1).second->setText(tr("VALUE"));
                    trees.at(2).first->setVisible(true);
                    trees.at(2).second->setVisible(true);
                    patternNbValues = 2;
                }
                else
                    patternNbValues = 3;
                for(quint16 i = 3 ; i < trees.count() ; i++) {
                    trees.at(i).first ->setVisible(false);
                    trees.at(i).second->setVisible(false);
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
                    trees.at(i).second->setVisible(true);
                    trees.at(i).second->setText(tr("VALUE %1").arg(i+1));
                }
            }
            first = false;
        }
        else {
            if(valueIndex < trees.count()) {
                if(valueIndex < patternNbValues)    setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second, messagePatternItem, false);
                else                                setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second, "",                 false);
            }
            valueIndex++;
        }
    }
    for(; valueIndex < patternNbValues ; valueIndex++)
        setCurrentItem(trees.at(valueIndex).first, trees.at(valueIndex).second, "", false);

    itemLock = false;
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
}
