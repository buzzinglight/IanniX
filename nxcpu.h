#ifndef NXCPU_H
#define NXCPU_H

#include <QThread>
#include <QProcess>
#include <QCoreApplication>

class NxCpu : public QThread {
    Q_OBJECT
public:
    explicit NxCpu(QObject *parent = 0);

public:
    qreal cpu, mem;
protected:
    void run();

signals:
    
public slots:
    
};

#endif // NXCPU_H
