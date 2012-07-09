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

#ifndef IANNIXAPP_H
#define IANNIXAPP_H

#include <QApplication>
#include "iannix.h"

class IanniXApp : public QApplication {
    Q_OBJECT

private:
    IanniX *iannix;

public:
    explicit IanniXApp(int &argc, char **argv);
    void launch(int &argc, char **argv);
    void setHelp();
    void generateHelp();

protected:
    bool event(QEvent *);
};

#endif // IANNIXAPP_H
