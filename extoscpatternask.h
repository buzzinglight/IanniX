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

#ifndef EXTOSCPATTERNASK_H
#define EXTOSCPATTERNASK_H

#include <QDesktopServices>
#include <QDialog>
#include <QDesktopWidget>
#include "extoscpatterneditor.h"
#include "nxobject.h"
#include "extmessage.h"

namespace Ui {
    class ExtOscPatternAsk;
}

class ExtOscPatternAsk : public QDialog {
    Q_OBJECT

public:
    explicit ExtOscPatternAsk(QWidget *parent, QList<NxObject*> *_objects);
    ~ExtOscPatternAsk();

private:
    QList<NxObject*> *objects;
    QList<ExtOscPatternEditor*> patternLists;
protected:
    void changeEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *);

public:
    bool onlyCurves;
    const QString getMessagePatterns() const;

public slots:
    void actionAddMessage();
    void actionRemoveMessage(ExtOscPatternEditor *editor);
    void help() {
        QDesktopServices::openUrl(QUrl("file:///" + QFileInfo("Documentation/index.html").absoluteFilePath().replace("\\", "/") + "#messages", QUrl::TolerantMode));
    }

private:
    Ui::ExtOscPatternAsk *ui;
};

#endif // EXTOSCPATTERNASK_H
