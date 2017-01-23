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

#include "help.h"

QHash<QString, HelpCategory> Help::categories;
QList<QByteArray>            Help::keywords;

const HelpInfo Help::getHelpFor(const QString &keyword, const QString &category) {
    if(categories.contains(category)) {
        foreach(const HelpInfo &info, categories.value(category).infos)
            if(info.keyword == keyword)
                return info;
    }
    return HelpInfo();
}

void Help::syncHelpWith(QWidget *widget, const QString &keyword, const QString &category) {
    if(categories.contains(category)) {
        for(quint16 i = 0 ; i < categories.value(category).infos.count() ; i++)
            if(categories.value(category).infos.at(i).keyword == keyword) {
                categories[category].infos[i].description += widget->toolTip() + "\n";
                while(widget != 0) {
                    if(!widget->statusTip().isEmpty()) {
                        categories[category].infos[i].title = widget->statusTip().split("|").first();
                        return;
                    }
                    widget = widget->parentWidget();
                }
            }
    }
}
void Help::syncHelpWith(QAction *action, const QString &keyword, const QString &category) {
    if(categories.contains(category)) {
        for(quint16 i = 0 ; i < categories.value(category).infos.count() ; i++)
            if(categories.value(category).infos.at(i).keyword == keyword) {
                categories[category].infos[i].description += action->toolTip() + "\n";
            }
    }
}
