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

#ifndef UITIMER_H
#define UITIMER_H

#include <QWidget>
#include <QMenu>
#include "misc/application.h"

namespace Ui {
class UiTimer;
}

class UiTimer : public QWidget {
    Q_OBJECT
    
public:
    explicit UiTimer(QWidget *parent = 0);
    ~UiTimer();

public:
    QAction *toolbarButton;
protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

public slots:
    void refreshTime(QString);
    
private:
    Ui::UiTimer *ui;
};

#endif // UITIMER_H
