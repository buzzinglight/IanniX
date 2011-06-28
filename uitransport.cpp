#include "uitransport.h"
#include "ui_uitransport.h"

UiTransport::UiTransport(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::UiTransport) {
    ui->setupUi(this);
}

UiTransport::~UiTransport() {
    delete ui;
}

void UiTransport::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


const QString UiTransport::getTime() const {
    return ui->timeEdit->text();
}

void UiTransport::setPerfScheduler(const QString & val) {
    if(!ui->perfSchedulerEdit->hasFocus())
        ui->perfSchedulerEdit->setText(val);
}
const QString UiTransport::getPerfScheduler() const {
    return ui->perfSchedulerEdit->text();
}

void UiTransport::setPerfOpenGL(const QString & val) {
    if(!ui->perfOpenGLEdit->hasFocus())
        ui->perfOpenGLEdit->setText(val);
}
const QString UiTransport::getPerfOpenGL() const {
    return ui->perfOpenGLEdit->text();
}


void UiTransport::setPlay_pause(bool state) {
    ui->playButton->setChecked(state);
}

void UiTransport::actionSpeedSlider() {
    ui->speedSpin->setValue((qreal)ui->speedSlider->value()/100.0F);
}
void UiTransport::actionSpeed() {
    ui->speedSlider->setValue(getSpeed()*100.0F);
    emit(actionRouteSpeed());
}

void UiTransport::updateTransport(QString time, QString lastMessage) {
    ui->timeEdit->setText(time);
    ui->lastMessage->setText(lastMessage);
}

qreal UiTransport::getSpeed() const {
    return ui->speedSpin->value();
}
void UiTransport::setSpeed(qreal val) {
    ui->speedSpin->setValue(val);
}
