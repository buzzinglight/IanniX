#include "uitimer.h"
#include "ui_uitimer.h"

UiTimer::UiTimer(NxObjectFactoryInterface *_factory, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiTimer) {
    ui->setupUi(this);
    factory = _factory;
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

UiTimer::~UiTimer() {
    delete ui;
}

void UiTimer::resizeEvent(QResizeEvent *) {
    ui->time->setStyleSheet(QString("font-size: %1px").arg(width() / 6));
    ui->time->resize(width(), height());
}

void UiTimer::updateTransport(QString time, QString) {
    if(isVisible()) {
        ui->time->setText(time);
    }
}
