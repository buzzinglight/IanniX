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
}

MessageManagerLogMini::~MessageManagerLogMini() {
    delete ui;
}

void MessageManagerLogMini::logSend(const MessageLog &log, bool force) {
    if((ui->enable->isChecked()) && ((canDisplay) || (force))) {
        ui->log->setText(log.getVerboseMessage());
        canDisplay = false;
    }
}
void MessageManagerLogMini::logReceive(const MessageLog &log, bool force) {
    logSend(log, force);
}

void MessageManagerLogMini::timerEvent(QTimerEvent *) {
    canDisplay = true;
}

