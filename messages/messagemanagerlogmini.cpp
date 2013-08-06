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

