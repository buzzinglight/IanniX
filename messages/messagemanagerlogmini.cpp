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

#include "messagemanagerlogmini.h"
#include "ui_messagemanagerlogmini.h"

MessageManagerLogMini::MessageManagerLogMini(QLayout *layout) :
    QWidget(0),
    ui(new Ui::MessageManagerLogMini) {
    ui->setupUi(this);
    canDisplay  = false;
    startTimer(200);
    if(layout)
        layout->addWidget(this);

    //Interfaces link
    Application::enableMiniLog.setAction(ui->enable, "interfaceEnableLog");
}

MessageManagerLogMini::~MessageManagerLogMini() {
    delete ui;
}

void MessageManagerLogMini::logSend(const MessageLog &log, QStringList *sentMessage) {
    if((canDisplay) && (Application::enableMiniLog)) {
        QString logged = Transport::timeLocalStr + " : " + log.getVerboseMessage();
        ui->log->setText(logged.replace("\t", " "));
        canDisplay = false;
    }
    if(sentMessage) {
        QString logged = Transport::timeLocalStr + " : " + log.getVerboseMessage();
        sentMessage->append(logged.replace("\t", " "));
    }
}
void MessageManagerLogMini::logReceive(const MessageLog &log, QStringList *sentMessage) {
    logSend(log, sentMessage);
}

void MessageManagerLogMini::timerEvent(QTimerEvent *) {
    canDisplay = true;
}

