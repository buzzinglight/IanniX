#ifndef UISPLASH_H
#define UISPLASH_H

#include <QWidget>
#include <QTimer>
#include <QDesktopWidget>

namespace Ui {
    class UiSplash;
}

class UiSplash : public QWidget {
    Q_OBJECT

public:
    explicit UiSplash(QWidget *parent = 0);
    ~UiSplash();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UiSplash *ui;
};

#endif // UISPLASH_H
