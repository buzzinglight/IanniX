/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (https://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    ui->time->setStyleSheet(QString("font-size: %1px").arg(width() / 7));
    ui->time->resize(width(), height());
    setMinimumHeight(width() / 7);
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
