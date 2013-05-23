#ifndef MESSAGEMANAGERLOGMINI_H
#define MESSAGEMANAGERLOGMINI_H

#include <QWidget>
#include "messagemanagerloginterface.h"

namespace Ui {
class MessageManagerLogMini;
}

class MessageManagerLogMini : public QWidget, public MessageManagerLogInterface {
    Q_OBJECT
    
public:
    explicit MessageManagerLogMini(QLayout *layout = 0);
    ~MessageManagerLogMini();

private:
    bool canDisplay;
    const MessageLog *lastMessage;

protected:
    void timerEvent(QTimerEvent *);
public:
    void logSend   (const MessageLog &log, bool force = false);
    void logReceive(const MessageLog &log, bool force = false);

private:
    Ui::MessageManagerLogMini *ui;
};

#endif // MESSAGEMANAGERLOGMINI_H
