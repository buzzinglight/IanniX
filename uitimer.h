#ifndef UITIMER_H
#define UITIMER_H

#include <QWidget>
#include "nxobjectfactoryinterface.h"

namespace Ui {
class UiTimer;
}

class UiTimer : public QWidget {
    Q_OBJECT
    
public:
    explicit UiTimer(NxObjectFactoryInterface *_factory, QWidget *parent = 0);
    ~UiTimer();

private:
    NxObjectFactoryInterface *factory;

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void updateTransport(QString, QString);
    
private:
    Ui::UiTimer *ui;
};

#endif // UITIMER_H
