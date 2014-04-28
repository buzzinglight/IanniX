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

#ifndef HELP_H
#define HELP_H

#include <QObject>
#include <QHash>
#include <QWidget>
#include <QByteArray>
#include <QAction>

class HelpInfo {
public:
    QString keyword, title, description, syntax;
    quint16 radix;

public:
    explicit HelpInfo(const QString &_keyword = "", const QString &_title = "", const QString &_description = "", const QString &_syntax = "") {
        keyword     = _keyword;
        title       = _title;
        description = _description;
        syntax      = _syntax;
    }
};

class HelpCategory {
public:
    explicit HelpCategory(const QString &_category = "", const QString &_description = "") {
        category    = _category;
        description = _description;
    }
public:
    QList<HelpInfo> infos;
    QString category, description;
};

class Help {
public:
    static QHash<QString, HelpCategory> categories;
    static QList<QByteArray> keywords;
public:
    static const HelpInfo getHelpFor(const QString &keyword, const QString &category = "commands");
    static void syncHelpWith(QWidget *widget, const QString &keyword, const QString &category = "commands");
    static void syncHelpWith(QAction *action, const QString &keyword, const QString &category = "commands");
};

#endif // HELP_H
