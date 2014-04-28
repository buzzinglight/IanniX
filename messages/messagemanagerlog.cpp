/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

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

#include "messagemanagerlog.h"
#include "ui_messagemanagerlog.h"

MessageManagerLog::MessageManagerLog(QLayout *layout) :
    QWidget(0),
    ui(new Ui::MessageManagerLog) {
    ui->setupUi(this);
    logEnable = false;
    if(layout)
        layout->addWidget(this);

    ui->splitter->setSizes(QList<int>() << height() * 0.7 << height() * 0.3);
}

MessageManagerLog::~MessageManagerLog() {
    delete ui;
}

void MessageManagerLog::logSend(const MessageLog &log, QStringList*) {
    if(logEnable)
        ui->logSend->appendPlainText(Transport::timeLocalStr + " : " + log.getVerboseMessage());
}
void MessageManagerLog::logReceive(const MessageLog &log, QStringList*) {
    if(logEnable)
        ui->logReceive->appendPlainText(Transport::timeLocalStr + " : " + log.getVerboseMessage());
}

void MessageManagerLog::action() {
    if(sender() == ui->logSendCopy)
        QApplication::clipboard()->setText(ui->logSend->toPlainText());
    else if(sender() == ui->logReceiveCopy)
        QApplication::clipboard()->setText(ui->logReceive->toPlainText());
}
