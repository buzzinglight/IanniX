#ifndef HELP_H
#define HELP_H

#include <QObject>
#include <QHash>

class HelpInfo {
public:
    explicit HelpInfo(const QString &_keyword = "", const QString &_title = "", const QString &_description = "", const QString &_syntax = "", const QString &_example = "", const QString &_snippet = "", const QString &_visuel = "") {
        keyword     = _keyword;
        title       = _title;
        description = _description;
        syntax      = _syntax;
        example     = _example;
        snippet     = _snippet;
        visuel      = _visuel;
    }
    QString keyword, title, description, syntax, visuel, snippet, example;
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
};

#endif // HELP_H
