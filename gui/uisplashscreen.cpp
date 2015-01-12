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

#include "uisplashscreen.h"

UiSplashScreen::UiSplashScreen(const QPixmap &_pixmap) :
    QFrame(0, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint) {
    pixmap = _pixmap;
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(pixmap.size());

    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - rect().center());

    QFont textFont("Arial");
    textFont.setPixelSize(13);
    showMessage(tr("version") + " " + QString(QCoreApplication::applicationVersion()) + " " + tr("beta"), textFont, Qt::AlignCenter, QColor(255, 255, 255, 150));

    show();
    QCoreApplication::processEvents();
}

void UiSplashScreen::showMessage(const QString& _message, const QFont &_font, int _messageAlignement, const QColor& _messageColor) {
    message  = _message;
    messageAlignment = _messageAlignement;
    messageColor  = _messageColor;
    messageFont   = _font;
    repaint();
}

void UiSplashScreen::paintEvent(QPaintEvent*) {
    QRect textRect(QRect(QPoint(115, 435), QSize(285, 70)));

    QPainter painter(this);
    painter.drawPixmap(rect(), pixmap);
    painter.setPen(messageColor);
    painter.setFont(messageFont);
    painter.drawText(textRect, messageAlignment, message);
}
