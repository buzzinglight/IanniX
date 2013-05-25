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

protected:
    void timerEvent(QTimerEvent *);
public:
    void logSend   (const MessageLog &log, QStringList *sentMessage = 0);
    void logReceive(const MessageLog &log, QStringList *sentMessage = 0);

private:
    Ui::MessageManagerLogMini *ui;
};

#endif // MESSAGEMANAGERLOGMINI_H
