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

#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include <QTime>
#include <QProcess>
#include <QThread>
#include <QCoreApplication>
#include "misc/application.h"
#include "iannix_cmd.h"
#include "qmath.h"
#include "uitimer.h"
#include "uiabout.h"
#include "uieditor.h"

namespace Ui {
class Transport;
}

enum SchedulerActivity { SchedulerOff, SchedulerOn, SchedulerOneShot };

class TransportStatus {
public:
    QString status;
    quint16 nbTriggers, nbCursors, nbCurves;

public:
    explicit TransportStatus(quint16 _nbTriggers = 0, quint16 _nbCursors = 0, quint16 _nbCurves = 0, const QString &_status = QString()) {
        nbTriggers = _nbTriggers;
        nbCursors  = _nbCursors;
        nbCurves   = _nbCurves;
        status     = _status;
    }
};

class TransportCpu : public QThread {
    Q_OBJECT
protected:
    void run();
public:
    TransportCpu(QObject *parent) : QThread(parent) { start(); }
};


class Transport : public QWidget, public NxObjectDispatchProperty {
    Q_OBJECT

    Q_PROPERTY(qreal   zoom   READ getZoom      WRITE setZoom)
    Q_PROPERTY(qreal   speed  READ getSpeed     WRITE setSpeed)
    Q_PROPERTY(QString center READ getCenterStr WRITE setCenterStr)
    Q_PROPERTY(QString rotate READ getRotateStr WRITE setRotateStr)

public:
    explicit Transport(QWidget *parent = 0);
    ~Transport();

public:
    static qreal timeLocal, scoreSpeed;
    static qreal perfSchedulerRefreshTime, perfSchedulerCounterTime;
    static qreal perfOpenGLRefreshTime,    perfOpenGLCounterTime;
    static QString timeLocalStr;
    static qreal renderMeasureAbsoluteValOld;
    static QTime renderMeasureAbsolute;
    static bool forceTimeLocal;
    static qreal perfCpu, perfMem;
    static UiBool timerOk;
public:
    static UiTimer  *bigTimer;
    static UiEditor *editor;
    static const QString& getTimeLocalStr();
    UiAbout *about;
private:
    bool speedLock;

public:
    void refreshPerformances();
    void refreshTime();
    void setSpeed(qreal _scoreSpeed);
    QLayout* getLogMini() const;

public slots:
    void action();

signals:
    void forceOpenGLtimer(qreal);
    void forceSchedulerTimer(qreal);

public:
    QAction *toolbarButton;
protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *);

public:
    inline qreal getZoom() const { return Render::zoomValue; }
    inline void setZoom(qreal val) { Application::render->setZoom(val); }
    inline qreal getSpeed() const {
        return scoreSpeed;
    }
    inline QString getCenterStr() const {
        return QString("%1 %2").arg(-Render::axisCenterDest.x()).arg(-Render::axisCenterDest.y());
    }
    inline QString getRotateStr() const {
        return QString("%1 %2 %3").arg(Render::rotationDest.x()).arg(Render::rotationDest.y()).arg(Render::rotationDest.z());
    }
    inline void setCenterStr(const QString & pos) {
        QStringList posItems = pos.split(" ", QString::SkipEmptyParts);
        if(posItems.count() > 1)
            Application::render->centerOn(NxPoint(posItems.at(0).toDouble(), posItems.at(1).toDouble()));
    }
    inline void setRotateStr(const QString & pos) {
        QStringList posItems = pos.split(" ", QString::SkipEmptyParts);
        if(posItems.count() > 2)
            Application::render->rotateTo(NxPoint(posItems.at(0).toDouble(), posItems.at(1).toDouble(), posItems.at(2).toDouble()));
    }


public:
    const QString serialize() const;
    void dispatchProperty(const char *_property, const QVariant & value);
    inline const QVariant getProperty(const char *_property) const { return property(_property); }

private:
    Ui::Transport *ui;
};

#endif // TRANSPORT_H
