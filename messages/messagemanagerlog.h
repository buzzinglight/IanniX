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
    void logSend   (const MessageLog &log, bool force = false);
    void logReceive(const MessageLog &log, bool force = false);

private:
    Ui::MessageManagerLog *ui;
};

#endif // MESSAGEMANAGERLOG_H
