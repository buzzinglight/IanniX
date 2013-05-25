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
