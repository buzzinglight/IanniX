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

#ifndef UIMESSAGEBOX_H
#define UIMESSAGEBOX_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QDesktopWidget>
#include <QMessageBox>

namespace Ui {
class UiMessageBox;
}

class UiMessageBox : public QDialog {
    Q_OBJECT
    
public:
    explicit UiMessageBox(QWidget *parent = 0);
    ~UiMessageBox();

public:
    QPair<bool, bool> getCheckboxes();

public:
    qreal getDouble(const QString &title, const QString &description, qreal value, qreal min, qreal max, qreal step, quint16 decimals, const QString &suffix, bool *ok = 0);
    qreal getDouble(const QString &title, const QString &description, const QPixmap &pixmap, qreal value, qreal min, qreal max, qreal step, quint16 decimals, const QString &suffix, bool resample, bool *ok = 0);
    QString getText(const QString &title, const QString &description, const QString &value, bool *ok = 0);
    int display(const QString &title, const QString &description1, const QString &description2, const QString &description3, const QPixmap &pixmap, QDialogButtonBox::StandardButtons buttons, bool *ok = 0);
    int display(const QString &title, const QString &description, QDialogButtonBox::StandardButtons buttons, bool *ok = 0);
    void display(const QString &title, const QString &description);

private:
    Ui::UiMessageBox *ui;
};

#endif // UIMESSAGEBOX_H
