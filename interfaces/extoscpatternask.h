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

#ifndef EXTOSCPATTERNASK_H
#define EXTOSCPATTERNASK_H

#include <QDesktopServices>
#include <QDialog>
#include <QDesktopWidget>
#include "objects/nxobject.h"
#include "interfaces/extoscpatterneditor.h"
#include "messages/message.h"

namespace Ui {
    class ExtOscPatternAsk;
}

class ExtOscPatternAsk : public QDialog {
    Q_OBJECT

public:
    explicit ExtOscPatternAsk(QWidget *parent, QList<NxObject *> *_objects);
    ~ExtOscPatternAsk();

private:
    QList<NxObject*> *objects;
    QList<ExtOscPatternEditor*> patternLists;
protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);

public:
    bool onlyCurves;
    const QString getMessagePatterns() const;

public slots:
    void actionAddMessage();
    void actionRemoveMessage();
    void actionFieldFocus(QComboBox*,QPlainTextEdit*);

private:
    Ui::ExtOscPatternAsk *ui;
};

#endif // EXTOSCPATTERNASK_H
