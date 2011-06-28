#ifndef EXTOSCPATTERNASK_H
#define EXTOSCPATTERNASK_H

#include <QDesktopServices>
#include <QDialog>
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
protected:
    void changeEvent(QEvent *e);

public:
    bool onlyCurves;
    const QVector< QVector<QByteArray> > getMessagePatterns() const;

public slots:
    void actionAddMessage();
    void actionRemoveMessage();
    void help() {
        QDesktopServices::openUrl(QUrl("file:///" + QFileInfo("Documentation/index.html").absoluteFilePath().replace("\\", "/") + "#messages", QUrl::TolerantMode));
    }

private:
    Ui::ExtOscPatternAsk *ui;
};

#endif // EXTOSCPATTERNASK_H
