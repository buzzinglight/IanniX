#include "nxcpu.h"

NxCpu::NxCpu(QObject *parent) :
    QThread(parent) {
    cpu = 0;
    mem = 0;
    start();
}

void NxCpu::run() {
    while(isRunning()) {
#ifdef Q_OS_WIN
        cpu = 0;
        mem = 0;
#else
        QProcess systemCommand1, systemCommand2;
        systemCommand1.setStandardOutputProcess(&systemCommand2);
        systemCommand1.start("ps", QStringList() << "-eo pid,pcpu,pmem,command");
        systemCommand1.waitForFinished();
        systemCommand2.start("grep", QStringList() << QString::number(QCoreApplication::applicationPid()));
        systemCommand2.waitForFinished();
        QStringList columns = QString(systemCommand2.readAllStandardOutput()).remove("\n").split(" ", QString::SkipEmptyParts);
        if(columns.count() >= 2) {
            cpu = columns[1].toDouble();
            mem = columns[2].toDouble();
        }
#endif
        sleep(3);
    }
}
