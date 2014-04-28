/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

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

#include "transport.h"
#include "ui_transport.h"

QString Transport::timeLocalStr         = "000:00.000";
qreal   Transport::timeLocal            = 0;
qreal   Transport::scoreSpeed           = 1;
qreal   Transport::perfSchedulerRefreshTime    = 0;
qreal   Transport::perfSchedulerCounterTime    = 0;
qreal   Transport::perfOpenGLRefreshTime       = 0;
qreal   Transport::perfOpenGLCounterTime       = 0;
qreal   Transport::renderMeasureAbsoluteValOld = 0;
QTime   Transport::renderMeasureAbsolute;
bool    Transport::forceTimeLocal = false;
qreal   Transport::perfCpu        = 0;
qreal   Transport::perfMem        = 0;
UiBool  Transport::timerOk = false;
UiTimer*  Transport::bigTimer = 0;
UiEditor* Transport::editor   = 0;

Transport::Transport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transport) {
    ui->setupUi(this);
    new TransportCpu(this);
    speedLock = false;
    toolbarButton = 0;

    Help::syncHelpWith(ui->timeEdit,   COMMAND_GOTO);
    Help::syncHelpWith(ui->ffButton,   COMMAND_FF);
    Help::syncHelpWith(ui->speedSpin,  COMMAND_SPEED);

    Transport::timerOk.setAction(ui->playButton);

    //Timer
    bigTimer = new UiTimer();
    editor   = new UiEditor();
    about    = new UiAbout();
}

Transport::~Transport() {
    delete ui;
}
void Transport::showEvent(QShowEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(true);
    QWidget::showEvent(e);
}
void Transport::closeEvent(QCloseEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(false);
    bigTimer->close();
    about->close();
    editor->close();
    QWidget::closeEvent(e);
}
void Transport::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        setFocus();
}




QLayout* Transport::getLogMini() const {
    return ui->spaceForLog;
}


void Transport::refreshPerformances() {
    if(isVisible()) {
        ui->perfCpuEdit->setText(QString::number(qRound(perfCpu)));
        if(perfCpu == 0)
            ui->perfCpuEdit->setVisible(false);
        else {
            ui->perfCpuEdit->setVisible(true);
            if(perfCpu < 70)
                ui->perfCpuEdit->setStyleSheet("");
            else if((70 <= perfCpu) && (perfCpu < 90))
                ui->perfCpuEdit->setStyleSheet("color: #FF8600;");
            else
                ui->perfCpuEdit->setStyleSheet("color: #FF2C00;");
        }
        if((!ui->perfSchedulerEdit->hasFocus()) && (timerOk))
            ui->perfSchedulerEdit->setText(QString::number(qRound(1000.0F * perfSchedulerRefreshTime / perfSchedulerCounterTime)));
        if(!ui->perfOpenGLEdit->hasFocus())
            ui->perfOpenGLEdit->setText(QString::number(qRound(1.0F * perfOpenGLCounterTime / perfOpenGLRefreshTime)));
    }
    perfSchedulerRefreshTime = 0;
    perfSchedulerCounterTime = 0;
    perfOpenGLRefreshTime = 0;
    perfOpenGLCounterTime = 0;
}
const QString & Transport::getTimeLocalStr() {
    timeLocalStr = "";

    quint16 min = timeLocal / 60;
    if(min < 10) timeLocalStr += "00";
    else if(min < 100) timeLocalStr += "0";
    timeLocalStr += QString::number(min) + ":";

    quint8 sec = qFloor(timeLocal) % 60;
    if(sec < 10) timeLocalStr += "0";
    timeLocalStr += QString::number(sec) + ":";

    quint16 milli = (Transport::timeLocal - qFloor(timeLocal)) * 1000;
    if(milli < 10)       timeLocalStr += "00";
    else if(milli < 100) timeLocalStr += "0";
    timeLocalStr += QString::number(milli);

    return timeLocalStr;
}

void Transport::refreshTime() {
    getTimeLocalStr();
    if((!ui->timeEdit->hasFocus()) && (isVisible()))
        ui->timeEdit->setText(timeLocalStr);
    bigTimer->refreshTime(timeLocalStr);
}

void Transport::action() {
    if((sender() == ui->perfSchedulerEdit) && (ui->perfSchedulerEdit->hasFocus())) {
        qreal val = ui->perfSchedulerEdit->text().remove("ms").trimmed().toDouble();
        if(val > 0)
            emit(forceSchedulerTimer(val));
    }
    else if((sender() == ui->perfOpenGLEdit) && (ui->perfOpenGLEdit->hasFocus())) {
        qreal val = ui->perfOpenGLEdit->text().remove("fps").trimmed().toDouble();
        if(val > 0)
            emit(forceOpenGLtimer(val));
    }
    else if(sender() == ui->playButton) {
        if(ui->playButton->isChecked()) Application::current->execute(QString("%1").arg(COMMAND_PLAY), ExecuteSourceGui);
        else                            Application::current->execute(QString("%1").arg(COMMAND_STOP), ExecuteSourceGui);
    }
    else if(sender() == ui->speedSlider) {
        ui->speedSpinReset->setEnabled((ui->speedSpin->value() != 1));
        if(!speedLock)
            Application::current->execute(QString("%1 %2").arg(COMMAND_SPEED).arg((qreal)ui->speedSlider->value()/100.0F), ExecuteSourceGui);
    }
    else if(sender() == ui->speedSpin) {
        ui->speedSpinReset->setEnabled((ui->speedSpin->value() != 1));
        if(!speedLock)
            Application::current->execute(QString("%1 %2").arg(COMMAND_SPEED).arg(ui->speedSpin->value()), ExecuteSourceGui);
    }
    else if(sender() == ui->speedSpinReset) {
        ui->speedSpin->setValue(1);
    }
    else if(sender() == ui->ffButton) {
        Application::current->execute(QString("%1").arg(COMMAND_FF), ExecuteSourceGui);
    }
    else if(sender() == ui->logoButton) {
        about->show();
    }
    else if(sender() == ui->timeEdit) {
        QStringList transportTime = ui->timeEdit->text().split(":", QString::SkipEmptyParts);
        if(transportTime.count() == 2) {
            QStringList transportTime2 = transportTime.at(1).split(".", QString::SkipEmptyParts);
            if(transportTime2.count() == 2) {
                qreal milli = transportTime2.at(1).toUInt();
                qreal sec   = transportTime2.at(0).toUInt();
                qreal min   = transportTime.at(0).toUInt();
                Application::current->execute(QString("%1 %2").arg(COMMAND_GOTO).arg(min * 60 + sec + milli / 1000.F), ExecuteSourceGui);
            }
        }
    }
}

void Transport::setSpeed(qreal _scoreSpeed) {
    speedLock = true;
    scoreSpeed = _scoreSpeed;
    ui->speedSlider->setValue(scoreSpeed*100.);
    ui->speedSpin->setValue  (scoreSpeed);
    speedLock = false;
}


void TransportCpu::run() {
    while(isRunning()) {
#ifdef Q_OS_WIN
        Transport::perfCpu = 0;
        Transport::perfMem = 0;
#else
        QProcess process;
        process.start("ps", QStringList() << "-eo" << "pid,pcpu,pmem,command");
        process.waitForFinished();
        QStringList perfs = QString(process.readAllStandardOutput()).split("\n", QString::SkipEmptyParts);
        foreach(const QString &perf, perfs) {
            bool isPid = false;
            QStringList perfInfos = perf.split(" ", QString::SkipEmptyParts);
            for(quint16 i = 0 ; i < perfInfos.count() ; i++) {
                const QString &perfInfo = perfInfos.at(i);
                if((i== 0) && (perfInfo.toInt() == QCoreApplication::applicationPid()))
                    isPid = true;
                else if((isPid) && (i == 1))    Transport::perfCpu = perfInfo.toDouble();
                else if((isPid) && (i == 2))    Transport::perfMem = perfInfo.toDouble();
            }
            if(isPid)
                break;
        }
#endif
        sleep(3);
    }
}


const QString Transport::serialize() const {
    QString retour = "";
    foreach(const QString &command, propertiesToSerialize.value(NxObjectDispatchProperty::source))
        retour += "\trun(\"" + QString("%1 %2").arg(command).arg(getProperty(qPrintable(command)).toString()) + "\");\n";
    if(!retour.isEmpty())
        retour += "\n";
    return retour;
}
void Transport::dispatchProperty(const char *_property, const QVariant & value) {
    propertyChanged(_property);
    setProperty(_property, value);
}

