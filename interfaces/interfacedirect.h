#ifndef INTERFACEDIRECT_H
#define INTERFACEDIRECT_H

#include <QWidget>
#include "misc/options.h"
#include "messages/messagemanager.h"

namespace Ui {
class InterfaceDirect;
}

class InterfaceDirect : public NetworkInterface
{
    Q_OBJECT
    
public:
    explicit InterfaceDirect(QWidget *parent = 0);
    ~InterfaceDirect();

private:
    UiBool enable;

public:
    bool send(const Message &message, QStringList *messageSent = 0);

private:
    Ui::InterfaceDirect *ui;
};

#endif // INTERFACEDIRECT_H
