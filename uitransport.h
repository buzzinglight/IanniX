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

#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include "nxdocument.h"

namespace Ui {
    class UiTransport;
}

class UiTransport : public QWidget {
    Q_OBJECT

public:
    explicit UiTransport(QWidget *parent = 0);
    ~UiTransport();

public slots:
    const QString getTime() const;
    void setPerfScheduler(const QString & val);
    const QString getPerfCpu() const;
    void setPerfCpu(quint16 cpu);
    const QString getPerfScheduler() const;
    void setPerfOpenGL(const QString & val);
    const QString getPerfOpenGL() const;
    void setPlay_pause(bool state);
    qreal getSpeed() const;
    void setSpeed(qreal val);
    void updateTransport(QString, QString);

public slots:
    void actionPlay_pause()       { emit(actionRoutePlay_pause()); }
    void actionFast_rewind()      { emit(actionRouteFast_rewind()); }
    void actionLogo()             { emit(actionRouteLogo()); }
    void actionGoto()             { emit(actionRouteGoto()); }
    void actionSetScheduler()     { emit(actionRouteSetScheduler()); }
    void actionSetOpenGL()        { emit(actionRouteSetOpenGL()); }
    void actionSpeedSlider();
    void actionSpeed();

private:
    bool speedLock;

signals:
    void actionRoutePlay_pause();
    void actionRouteFast_rewind();
    void actionRouteLogo();
    void actionRouteGoto();
    void actionRouteSetScheduler();
    void actionRouteSetOpenGL();
    void actionRouteSpeed();
    void actionRoutePresentation();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UiTransport *ui;
};

#endif // TRANSPORT_H
