#ifndef MESSAGEMANAGERLOG_H
#define MESSAGEMANAGERLOG_H

#include <QWidget>
#include "messagemanagerloginterface.h"

namespace Ui {
class MessageManagerLog;
}

class MessageManagerLog : public QWidget, public MessageManagerLogInterface {
    Q_OBJECT

private:
    MessageManagerLog *log;

public:
    explicit MessageManagerLog(QLayout *layout = 0);
    ~MessageManagerLog();

public:
    bool logEnable;
    void logSend   (const MessageLog &log, QStringList *sentMessage = 0);
    void logReceive(const MessageLog &log, QStringList *sentMessage = 0);

private:
    Ui::MessageManagerLog *ui;
};

#endif // MESSAGEMANAGERLOG_H
