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
