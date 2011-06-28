#ifndef IANNIXAPP_H
#define IANNIXAPP_H

#include <QApplication>
#include "iannix.h"

class IanniXApp : public QApplication {
    Q_OBJECT

private:
    IanniX *iannix;

public:
    explicit IanniXApp(int &argc, char **argv);

protected:
    bool event(QEvent *);
};

#endif // IANNIXAPP_H
