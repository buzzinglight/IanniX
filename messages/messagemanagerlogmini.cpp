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

void MessageManagerLogMini::logSend(const MessageLog &log, QStringList *sentMessage) {
    if((ui->enable->isChecked()) && (canDisplay)) {
        ui->log->setText(log.getVerboseMessage());
        canDisplay = false;
    }
    if(sentMessage)
        sentMessage->append(log.getVerboseMessage());
}
void MessageManagerLogMini::logReceive(const MessageLog &log, QStringList *sentMessage) {
    logSend(log, sentMessage);
}

void MessageManagerLogMini::timerEvent(QTimerEvent *) {
    canDisplay = true;
}

