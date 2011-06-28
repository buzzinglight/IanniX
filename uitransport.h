#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include "nxdocument.h"

namespace Ui {
    class UiTransport;
}

class UiTransport : public QWidget {
    Q_OBJECT

public:
    explicit UiTransport(QWidget *parent = 0);
    ~UiTransport();

public slots:
    const QString getTime() const;
    void setPerfScheduler(const QString & val);
    const QString getPerfScheduler() const;
    void setPerfOpenGL(const QString & val);
    const QString getPerfOpenGL() const;
    void setPlay_pause(bool state);
    qreal getSpeed() const;
    void setSpeed(qreal val);
    void updateTransport(QString, QString);

public slots:
    void actionPlay_pause()       { emit(actionRoutePlay_pause()); }
    void actionFast_rewind()      { emit(actionRouteFast_rewind()); }
    void actionLogo()             { emit(actionRouteLogo()); }
    void actionGoto()             { emit(actionRouteGoto()); }
    void actionSetScheduler()     { emit(actionRouteSetScheduler()); }
    void actionSetOpenGL()        { emit(actionRouteSetOpenGL()); }
    void actionSpeedSlider();
    void actionSpeed();

signals:
    void actionRoutePlay_pause();
    void actionRouteFast_rewind();
    void actionRouteLogo();
    void actionRouteGoto();
    void actionRouteSetScheduler();
    void actionRouteSetOpenGL();
    void actionRouteSpeed();
    void actionRoutePresentation();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UiTransport *ui;
};

#endif // TRANSPORT_H
