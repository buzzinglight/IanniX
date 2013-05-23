#ifndef HELP_H
#define HELP_H

#include <QObject>
#include <QHash>
#include <QByteArray>

class HelpInfo {
public:
    QString keyword, title, description, syntax;

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
};

#endif // HELP_H
