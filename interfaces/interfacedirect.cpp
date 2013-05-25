#include "interfacedirect.h"
#include "ui_interfacedirect.h"

InterfaceDirect::InterfaceDirect(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceDirect) {
    ui->setupUi(this);

    //Interfaces link
    enable.setAction(ui->enable, "interfaceDirectEnable");
}

InterfaceDirect::~InterfaceDirect() {
    delete ui;
}

bool InterfaceDirect::send(const Message &message, QStringList *messageSent) {
    if(!enable)
        return false;

    QString command = message.getAsciiMessage();
    MessageManager::incomingMessage(MessageIncomming("direct", "", QVariant(), "", command, QStringList()));


    //Log in console
    MessageManager::logSend(message, messageSent);

    return true;
}
