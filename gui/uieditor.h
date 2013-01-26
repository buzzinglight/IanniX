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

#ifndef UIEDITOR_H
#define UIEDITOR_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextCursor>
#include "misc/help.h"
#include "objects/nxobjectfactoryinterface.h"


namespace Ui {
    class UiEditor;
}

class UiEditor : public QMainWindow {
    Q_OBJECT

private:
    QFileInfo scriptFile;
    NxObjectFactoryInterface *factory;

public:
    explicit UiEditor(NxObjectFactoryInterface *_factory, QWidget *parent = 0);
    ~UiEditor();

public:
    void openFile(const QFileInfo &  _scriptFile);
protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);

public slots:
    void save();
    void cursorChanged();
    void scriptError(const QStringList &errors, qint16 line);

signals:
    void closed(bool);

private:
    Ui::UiEditor *ui;
};

#endif // UIEDITOR_H
