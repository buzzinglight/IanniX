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

#ifndef UIHELP_H
#define UIHELP_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QTextCursor>
#include <QTextBlock>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QClipboard>
#include "gui/uimessagebox.h"
#include "misc/help.h"
#include "misc/options.h"

namespace Ui {
class UiHelp;
}

class UiHelp : public QWidget {
    Q_OBJECT

private:
    QPlainTextEdit *currentTextEdit;
    QComboBox *currentCombo;
    QStringList statusTexts;
    QList< QPair<QString,HelpInfo> > messageTexts;
    QString statusTextOld;
    bool statusRefresh;
public:
    static quint16 oscPort;
    static UiHelp *statusHelpWidget;

public:
    explicit UiHelp(QWidget *parent = 0);
    ~UiHelp();

public:
    static void statusHelp(const QWidget *widget);
    void statusHelp();
    void scriptHelp(QPlainTextEdit *textEdit, const QStringList &lookCategories);
    void scriptHelp(QComboBox      *textEdit, const QStringList &lookCategories);
    void scriptHelp(const QString  &looking,  const QStringList &lookCategories);

public:
    UiBool visibility;
public slots:
    void statusHelp(QString _statusText);
    void messageHelp(QString _messageText);
    void linkClicked(QUrl);

protected:
    void timerEvent(QTimerEvent *);
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    
private:
    Ui::UiHelp *ui;
};

#endif // UIHELP_H
