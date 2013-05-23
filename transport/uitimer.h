#ifndef UITIMER_H
#define UITIMER_H

#include <QWidget>
#include <QMenu>
#include "misc/application.h"

namespace Ui {
class UiTimer;
}

class UiTimer : public QWidget {
    Q_OBJECT
    
public:
    explicit UiTimer(QWidget *parent = 0);
    ~UiTimer();

public:
    QAction *toolbarButton;
protected:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

public slots:
    void refreshTime(QString);
    
private:
    Ui::UiTimer *ui;
};

#endif // UITIMER_H
