/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

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

#ifndef UISPLASHSCREEN_H
#define UISPLASHSCREEN_H

#include <QFrame>
#include <QPainter>
#include <QPixmap>
#include <QDesktopWidget>
#include <QApplication>

class UiSplashScreen : public QFrame {
    Q_OBJECT

public:
    explicit UiSplashScreen(const QPixmap&);

public:
    void showMessage(const QString& _message, const QFont &_font, int _messageAlignment = Qt::AlignCenter, const QColor& _messageColor = Qt::white);

private:
    void paintEvent(QPaintEvent* e);
    QPixmap  pixmap;
    QString  message;
    int      messageAlignment;
    QColor   messageColor;
    QFont    messageFont;
    
signals:
    
public slots:
    
};

#endif // UISPLASHSCREEN_H
