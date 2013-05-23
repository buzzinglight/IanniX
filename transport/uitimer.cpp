#include "uitimer.h"
#include "ui_uitimer.h"

UiTimer::UiTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiTimer) {
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    toolbarButton = 0;
}

UiTimer::~UiTimer() {
    delete ui;
}

void UiTimer::resizeEvent(QResizeEvent *e) {
    QWidget::resizeEvent(e);
    ui->time->setStyleSheet(QString("font-size: %1px").arg(width() / 6));
    ui->time->resize(width(), height());
    setMinimumHeight(width() / 5);
}
void UiTimer::showEvent(QShowEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(true);
    QWidget::showEvent(e);
}
void UiTimer::closeEvent(QCloseEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(false);
    QWidget::closeEvent(e);
}

void UiTimer::refreshTime(QString time) {
    if(isVisible())
        ui->time->setText(time);
}
