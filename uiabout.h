#ifndef UIABOUT_H
#define UIABOUT_H

#include <QWidget>
#include <QDesktopWidget>

namespace Ui {
    class UiAbout;
}

class UiAbout : public QWidget {
    Q_OBJECT

public:
    explicit UiAbout(QWidget *parent = 0);
    ~UiAbout();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UiAbout *ui;
};

#endif // UIABOUT_H
