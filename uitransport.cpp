/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "uitransport.h"
#include "ui_uitransport.h"

UiTransport::UiTransport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiTransport) {
    ui->setupUi(this);
    speedLock = false;
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

void UiTransport::setPerfCpu(quint16 cpu) {
    ui->perfCpuEdit->setText(QString::number(cpu));
    if(cpu == 0)
        ui->perfCpuEdit->setVisible(false);
    else {
        ui->perfCpuEdit->setVisible(true);
        if(cpu < 70)
            ui->perfCpuEdit->setStyleSheet("");
        else if((70 <= cpu) && (cpu < 90))
            ui->perfCpuEdit->setStyleSheet("color: #FF8600;");
        else
            ui->perfCpuEdit->setStyleSheet("color: #FF2C00;");
    }

}
const QString UiTransport::getPerfCpu() const {
    return ui->perfCpuEdit->text();
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
    if(!speedLock)
        ui->speedSpin->setValue((qreal)ui->speedSlider->value()/100.0F);
}
void UiTransport::actionSpeed() {
    speedLock = true;
    ui->speedSlider->setValue(getSpeed()*100.0F);
    speedLock = false;
    emit(actionRouteSpeed());
}

void UiTransport::updateTransport(QString time, QString lastMessage) {
    if(isVisible()) {
        ui->timeEdit->setText(time);
        ui->lastMessage->setText(lastMessage);
    }
}

qreal UiTransport::getSpeed() const {
    return ui->speedSpin->value();
}
void UiTransport::setSpeed(qreal val) {
    ui->speedSpin->setValue(val);
}
