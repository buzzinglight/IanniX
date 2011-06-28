#ifndef EXTHTTPMANAGER_H
#define EXTHTTPMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include "extmessage.h"

class ExtHttpManager : public QObject, public ExtMessageManager {
    Q_OBJECT

private:
    QNetworkAccessManager *http;

public:
    ExtHttpManager(NxObjectFactoryInterface *_factory);

public:
    void send(const ExtMessage & message);

private slots:
    void parse(QNetworkReply*);
public slots:
    void parseService(const QUrl &url);
 };

#endif // EXTHTTPMANAGER_H
